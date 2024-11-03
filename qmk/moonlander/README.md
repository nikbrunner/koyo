# kōyō for the ZSA Moonlander via QMK

## Differences

Since `LY_FUN` and `LY_MED` are the least used functionalities for me, I
positioned these on the native layout (`crkbd`) to the inner most thumbs. Due
to the differing positioning of the thumb clusters on the moonlander, I
positioned the native most inner thumb to the outer most thumb on the
moonlander, because the inner most thumb is hard to reach for me on the
Moonlander.
It is a change, but comfort is more import to me in that case that consistency.
The goal is that the resting position of the most-used keys/functionalities is
the same on both layouts.

This means in practice, it looks like this:

**CRKBD**
```c
MO(LY_FUN) | LT(LY_NUM, KC_ESC) | LT(LY_EXT, KC_SPC) --- HYPR_T(KC_ENT) | MEH_T(KC_TAB) | MO(LY_MED)  
```

**MOONLANDER**
```c
LT(LY_NUM, KC_ESC) | LT(LY_EXT, KC_SPC) | MO(LY_FUN) --- MO(LY_MED) | HYPR_T(KC_ENT) | MEH_T(KC_TAB)
```
