---
name: repo-layout
description: Change the kōyō layout through keymap.yml and regenerate every board's keymap and the layout SVG. Use for any key, layer, combo or tap dance change, and before any commit that touches keymap.yml or a qmk/*/src/keymap.c.
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

## The keymap.c files

Each board's `keymap.c` holds the behaviour: `enum tap_dance_codes` and its callbacks, `get_tapping_term`, `get_chordal_hold`, RGB, and any per-board hooks. `enum tap_dance_codes` comes before `#include "keymap.generated.h"`; everything that uses `LY_*` comes after it. Code that names a board-only layer lives only in those boards' `keymap.c` (e.g. `combo_should_trigger()` with `LY_GAM` in the Voyager's), since the other boards have no such enum value.

A new tap dance has three parts: its entry in `enum tap_dance_codes` and its `tap_dance_actions` entry with callbacks in all four `keymap.c` files, plus a label in `qmk_keycode_map` in `assets/kd_config.yaml` (e.g. `TD(TD_EXT_GUI_A): { t: "Gui+ A", h: GUI }`).

## Steps

1. Edit `keymap.yml`, and the `keymap.c` files where the change adds behaviour. Done when every keycode the change introduces is either a QMK keycode or defined in all four `keymap.c` files.
2. Run `./koyo update keymap`. Done when it prints both success lines; a malformed row, an unknown board name or a combo key missing from its layer stops it with a message naming the culprit.
3. Run `./koyo check` (`check.sh`). It works on a copy of the working tree and verifies that the generated files match `keymap.yml`, that every hand-written `case` in the `keymap.c` files still names a key in `keymap.yml` (an orphaned `case` compiles but never matches), and that all four boards compile. Done when it prints `All checks passed`; each failure names the stale file, the orphaned `case` or the board with its compiler error.
4. Render the SVG and look at it. `qlmanage` thumbnails crop tall SVGs; use headless Chrome with the size from the SVG's `viewBox`, writing to a temp dir:

   ```sh
   "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome" --headless --hide-scrollbars \
     --window-size=<w>,<h> --screenshot=<temp dir>/layout.png "file://$PWD/assets/layout.svg"
   ```

   Done when every changed layer reads correctly in the PNG. A raw label (`TD(...)`, a bare keycode) gets a readable one in `qmk_keycode_map` in `assets/kd_config.yaml`.

## On commit

`keymap.yml`, the generated headers and `assets/layout.svg` travel together in one commit, and `./koyo check` passes before it. The Lefthook pre-push hook runs `./check.sh --ref HEAD` and blocks a push that fails it.
