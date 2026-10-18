---
name: repo-layout-drawing
description: Keep assets/layout.svg, the cross-board drawing of kōyō, in sync with the firmware. Use before any commit that touches a qmk/*/src/keymap.c, and when asked to update or check the layout drawing or kd_layout.yaml.
---

# Layout drawing

`assets/layout.svg` is the one picture of kōyō as a whole, across all boards. keymap-drawer renders it from `assets/kd_layout.yaml`, and that YAML is written by hand: nothing parses the keymaps, so every keymap change has to be carried over.

## The drawing model

- The drawing shows the 3x5+3 core every board shares, on the Corne physical layout. The Corne is only the template; the drawing stands for all four boards.
- Each layer is a list of 36 keys: three rows of ten (left five, then right five), then six thumbs in the same order as the thumb row of `qmk/crkbd/src/keymap.c` (`LAYOUT_split_3x5_3`, left to right).
- A layer that exists only on boards with more keys (outer ring, number row) is still drawn: its core keys as they are, and the layer name says so, e.g. `"LY_GAM (outer-key boards only)"`. The keys outside the core live in that board's keymap.c table.
- Tap-hold keys are `{ t: <tap>, h: <hold> }`. Combos are `{ p: [<pos>, <pos>], k: <key>, l: [<layer>] }`, with 0-based positions into the 36-key list.

## Steps

1. Read the keymaps of all boards: `qmk/{crkbd,chocofi,moonlander,voyager}/src/keymap.c`. Collect every layer, every key in the 3x5+3 core, every board-only layer, and every `COMBO(...)`.
2. Diff that against `assets/kd_layout.yaml`. Done when every layer, core key and combo from every board is either drawn identically or named as board-only in its layer label. When boards disagree on a core key, that is drift in the firmware, not the drawing: stop and ask Nik which board is right.
3. Edit the YAML.
4. Run `./koyo update svg`.
5. Render the SVG and look at it. `qlmanage` thumbnails crop tall SVGs; use headless Chrome with the size from the SVG's `viewBox`, writing to the scratchpad:

   ```sh
   "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome" --headless --hide-scrollbars \
     --window-size=<w>,<h> --screenshot=<scratchpad>/layout.png "file://$PWD/assets/layout.svg"
   ```

   Done when every changed layer reads correctly in the PNG, labels and thumbs included.

## On commit

A commit that changes a keymap.c without touching `kd_layout.yaml` is drift, unless the change cannot show in the drawing (tapping terms, chordal hold, RGB, `config.h`). Run steps 1–2 before every such commit, and carry the YAML and SVG changes in the same commit as the keymap change.
