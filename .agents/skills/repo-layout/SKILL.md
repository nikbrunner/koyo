---
name: repo-layout
description: Change the kōyō layout through keymap.yml and regenerate every board's keymap and the layout SVG. Use for any key, layer, combo, tap-hold or tap dance change, and before any commit that touches keymap.yml or a qmk/*/src/keymap.c.
---

# Layout

`keymap.yml` is the source of truth for the layout of all four boards (voyager, moonlander, crkbd, chocofi). `./koyo update keymap` (`update_keymap.sh` → `generate_keymap.py` → keymap-drawer) turns it into `qmk/<board>/src/keymap.generated.h` for every board and into `assets/layout.svg`.

## The keymap.yml model

- Each layer has five `rows` in the Voyager shape: four rows of twelve keys (outer key, five core keys `|` five core keys, outer key; the top row is all outer ring), then the thumbs: left two `|` right two.
- Keys are QMK keycodes, comma-separated. `XXXXXXX` is a dead key.
- Corne and Chocofi take the core and thumbs; Moonlander and Voyager take the outer ring too. Each board's LAYOUT macro is in `BOARDS` and its key mapping in `board_rows()`, both in `generate_keymap.py`.
- A layer with `boards: [...]` exists only on those boards. Elsewhere it leaves the layer enum, every key that references it becomes `KC_NO`, and every combo that references it is dropped. The drawing labels it, e.g. `LY_GAM (Voyager only)`.
- A combo is an entry under `combos:`, keyed by a name:

  ```yaml
  BRACKET_LEFT:
    layer: LY_BAS             # the layer holding its keys; places it in the drawing
    keys: KC_J, LT(LY_SYM, KC_K)  # written exactly as on that layer
    send: KC_LBRC
  ```

  QMK matches combos by keycode, so a combo fires on any layer where its keys exist. Its C array is `<layer>_CMB_<name>`.

- Lighting lives here too and is generated into the same headers. `palette` names HSV colours, a layer's `background` lights all its keys at `lighting.background_v`, its `highlights` paint keys written exactly as on that layer, and `lighting.mods` colours every other modifier and mod-tap. Colours come from Black Atom JPN Kōyō dark. A split board with per-key highlights needs `SPLIT_LAYER_STATE_ENABLE` in its `config.h`, or the right half keeps showing the base layer.

## The behaviour files

`qmk/shared/` holds the behaviour of every board. Names that `keymap.yml` uses (aliases, a tap dance enum) go in `aliases.h`, which comes before `keymap.generated.h`; the tap-hold and combo hooks go in `hooks.h`, which comes after it, since they use `LY_*`. Each board's `keymap.c` includes both and holds what differs per board: its `chordal_hold_layout`, and `#define GAMING_LAYER LY_GAM` on a board with the gaming layer. Other boards have no such enum value, so `hooks.h` guards that code with `#ifdef GAMING_LAYER`.

## Tap-hold

Pick the mechanism by latency. A mod-tap or layer-tap sends its tap on release. A tap dance waits out the full tapping term after every press, in case another tap follows, so it fits only a key that really acts on the tap count.

**Tap sends a modified keycode** (the EXT home row: tap Cmd-S, hold Alt). `MT()` keeps only a basic keycode, so the tap is intercepted:

- Name the key before the generated header (`#define EXT_S MT(MOD_LALT, KC_S)`) and use that name in `keymap.yml`. keymap-drawer splits a literal `MT(...)` into its tap and hold before it reads `qmk_keycode_map`, so the alias is what lets the drawing show the real tap: `EXT_S: { t: "Gui+ S", h: ALT }` in `assets/kd_config.yaml`.
- Send the tap from `process_record_user`, guarded by `record->tap.count && record->event.pressed`, and return `false`.

**Hooks that decide tap or hold.** Each needs its `*_PER_KEY` define in `config.h`, where one exists. `SPECULATIVE_HOLD`, `CHORDAL_HOLD` and `TAPPING_TERM_PER_KEY` apply to all four boards.

| Hook | Effect | Keys it suits |
| --- | --- | --- |
| `get_hold_on_other_key_press` | Settles as held the moment another key goes down, so a chord fires at once. A fast roll also becomes a hold. | Keys mostly chorded with others, on a layer where you are not typing prose (EXT home row) |
| `get_permissive_hold` | Settles as held when another key is tapped inside it, ending that key's wait for the timer. Rolls stay taps. | Layer thumbs that also type (EXT thumb on space) |
| `get_chordal_hold` | Returning `true` lets a same-hand chord hold; the default settles it as a tap. | Thumbs, and keys that combine with same-hand keys (EXT home row: F+D, F+C) |
| `get_speculative_hold` | Sends the modifier on keydown, before the decision. QMK's default covers Ctrl and Shift mod-taps; an override has to repeat that default for the keys it keeps. | Exclude keys mostly tapped for a shortcut, since each tap would flash the modifier first |
| `get_flow_tap_term` | Settles as tapped when pressed within `FLOW_TAP_TERM` of a typed letter. Returning 0 opts the key out. | Mods rarely held mid-typing (bottom-row Gui, Alt, Ctrl). Not Shift or layer keys, which need a hold right after a letter. `prev_keycode` opts out single sequences: left Ctrl right after HJKL, for repeated Ctrl+HJKL |

These settings interact, so check against QMK's `docs/tap_hold.md` at the checkout in `config.yml` (`paths.qmk_dir`).

**A new tap dance** has three parts: its entry in `enum tap_dance_codes` in `aliases.h`, its `tap_dance_actions` entry with callbacks in `hooks.h` (`TAP_DANCE_ENABLE = yes` in each `rules.mk`), plus a label in `qmk_keycode_map` (`TD(TD_NAME): { t: "Gui+ A", h: GUI }`).

## Steps

1. Edit `keymap.yml`, and `qmk/shared/` where the change adds behaviour. Done when every keycode the change introduces is either a QMK keycode or defined in `aliases.h`.
2. Run `./koyo update keymap`. Done when it prints both success lines; a malformed row, an unknown board name or a combo key missing from its layer stops it with a message naming the culprit.
3. Run `./koyo check` (`check.sh`). It works on a copy of the working tree and verifies that the generated files match `keymap.yml`, that keys land where each board expects them (`test_generate_keymap.py`), that every hand-written `case` with a literal keycode (`case LT(...)`, not an alias like `case EXT_S`) in `qmk/shared/` and the `keymap.c` files still names a key in `keymap.yml` (an orphaned `case` compiles but never matches), and that all four boards compile. Done when it prints `All checks passed`; each failure names the stale file, the wrong key position, the orphaned `case` or the board with its compiler error.
4. Render the SVG and look at it. `qlmanage` thumbnails crop tall SVGs; use headless Chrome with the size from the SVG's `viewBox`, writing to a temp dir:

   ```sh
   "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome" --headless --hide-scrollbars \
     --window-size=<w>,<h> --screenshot=<temp dir>/layout.png "file://$PWD/assets/layout.svg"
   ```

   Done when every changed layer reads correctly in the PNG. A raw label (`TD(...)`, a bare keycode) gets a readable one in `qmk_keycode_map` in `assets/kd_config.yaml`.

## On commit

`keymap.yml`, the generated headers and `assets/layout.svg` travel together in one commit, and `./koyo check` passes before it. The Lefthook pre-push hook runs `./check.sh --ref HEAD` and blocks a push that fails it.
