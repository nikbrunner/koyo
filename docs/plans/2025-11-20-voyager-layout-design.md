# Voyager Layout Design

## Overview

Port the existing Corne (crkbd) layout to the ZSA Voyager keyboard with the addition of a dedicated number row. The Voyager's extra row and columns will be used minimally to maintain familiar hand positioning while gaining direct number access.

## Physical Layout

**Voyager dimensions:** 6 columns × 4 rows per side + 2 thumb keys per side

**Key positioning strategy:**
- Top row: Dedicated numbers (1-0)
- Middle 3 rows: Same 5-column alpha layout as Corne
- Outer columns: Empty (KC_NO) to maintain Corne-like hand positioning
- Thumb cluster: 2 keys per side (vs Corne's 3, but we only use 2 functionally anyway)

## Base Layer (LY_BAS)

```
Row 1: [NO] 1    2    3    4    5         6    7    8    9    0    [NO]
Row 2: [NO] q    w    e    r    t         y    u    i    o    p    [NO]
Row 3: [NO] a    s    d    f    g         h    j    k    l    ;    [NO]
Row 4: [NO] z    x    c    v    b         n    m    ,    .    /    [NO]
Thumbs:     ESC  SPC                      ENT  CTRLB
```

**Home row mods (same as Corne):**
- Left: GUI(z), ALT(x), CTL(c), SFT(v)
- Right: SFT(m), CTL(,), ALT(.), GUI(/)

**Layer taps:**
- d/k: LT(LY_SYM, d/k)
- ESC: LT(LY_NUM_FN, KC_ESC)
- SPC: LT(LY_EXT, KC_SPC)
- ENT: HYPR_T(KC_ENT)
- CTRLB: TD(TD_MED_CTRLB) - tap for Ctrl+B, hold for media layer

## Layer Strategy

All five layers from Corne are preserved:
1. **LY_BAS**: Base QWERTY + numbers
2. **LY_EXT**: Navigation & macOS shortcuts
3. **LY_SYM**: Programming symbols
4. **LY_NUM_FN**: Numpad + F-keys
5. **LY_MED**: Media & system controls

**Number row behavior:** Always passes through to 1-0 on all layers. This means numbers are always accessible regardless of active layer.

## Layer Details

### EXT Layer (Navigation)
- Same macOS shortcuts (CMD+q/w/e/r/t/g, etc.)
- Arrow keys in right home position (left/down/up/right on h/j/k/l)
- Tap dances for GUI combinations (TD_EXT_GUI_A/S/D/F)
- Tab navigation and CapsWord toggle

### SYM Layer (Programming Symbols)
- All symbols in same positions as Corne
- Left side: operators and special chars (^, +, #, %, $, !, -, &, ?, |, ~, _, *, @)
- Right side: brackets and quotes (<, {, ", }, >, =, [, ', ], :, \, (, `, ), /)
- Fat arrow macro (=>) on right thumb

### NUM_FN Layer (Numbers + Functions)
- Left hand: F-keys (F1-F12) with home row mods on F5-F8
- Right hand: Numpad with operators (+, =, -, *, :, /)
- Home row mods on numpad: SFT(4), CTL(5), ALT(6)
- Top row numbers still accessible for quick single digits

### MED Layer (Media & System)
- Volume controls (vold/mute/volu)
- Media playback (prev/play/next)
- Brightness controls (brid/briu)
- RGB controls (RM_HUED/RM_TOGG/RM_HUEU)
- System functions (QK_BOOT for flashing, lock screen)
- Dynamic macros (DT_UP/DT_DOWN/DT_PRNT)

## Feature Preservation

**Combos:**
- I+O = Backspace (all layers)
- J+K = Left bracket
- K+L = Right bracket
- 8+9 = Backspace (NUM_FN layer)
- "+} = Backspace (SYM layer)

**Tap dances:**
- TD_EXT_GUI_A: Tap for CMD+A, hold for GUI
- TD_EXT_GUI_S: Tap for CMD+S, hold for ALT
- TD_EXT_GUI_D: Tap for CMD+D, hold for CTL
- TD_EXT_GUI_F: Tap for CMD+F, hold for SFT
- TD_MED_CTRLB: Tap for CTRL+B, hold for media layer

**Tapping term adjustments:**
- GUI(z), ALT(x), ALT(.), GUI(/) get +15ms (same as Corne)

**Chordal hold:**
- Same implementation as Corne
- Layer thumbs and HYPR_T always hold when chorded
- Handedness defined for proper opposite-hand detection

## Implementation Notes

- Use existing QMK firmware in `~/repos/qmk/qmk_firmware/keyboards/zsa/voyager/`
- Copy structure from `qmk/moonlander/` directory in koyo repo
- Preserve all custom keycodes (SS_FATARROW)
- Maintain all tap dance, combo, and chordal hold logic
- Update koyo CLI to support `./koyo voyager flash` command
- Generate SVG layout using keymap-drawer

## Benefits

1. **Direct number access**: No layer holding needed for numbers
2. **Familiar positioning**: Outer columns stay empty, maintaining Corne muscle memory
3. **Full feature parity**: All combos, tap dances, and macros work identically
4. **Simplified thumbs**: Two functional keys per side (vs Corne's 3 with 2 used)
5. **No conflicts**: Number row doesn't interfere with existing layer system
