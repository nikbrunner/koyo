// Generated from keymap.yml by `./koyo update keymap`. Edit keymap.yml, never this file.
#pragma once

enum layers {
    LY_BAS,
    LY_EXT,
    LY_SYM,
    LY_NUM_FN,
    LY_MED,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LY_BAS] = LAYOUT_split_3x5_3(
  KC_Q               , KC_W               , KC_E               , KC_R               , KC_T , KC_Y , KC_U               , KC_I                   , KC_O                 , KC_P,
  KC_A               , KC_S               , LT(LY_SYM, KC_D)   , KC_F               , KC_G , KC_H , KC_J               , LT(LY_SYM, KC_K)       , KC_L                 , KC_SCLN,
  MT(MOD_LGUI, KC_Z) , MT(MOD_LALT, KC_X) , MT(MOD_LCTL, KC_C) , MT(MOD_LSFT, KC_V) , KC_B , KC_N , MT(MOD_RSFT, KC_M) , MT(MOD_RCTL, KC_COMMA) , MT(MOD_LALT, KC_DOT) , MT(MOD_RGUI, KC_SLASH),
  KC_NO , LT(LY_EXT, KC_SPC) , LT(LY_NUM_FN, KC_ESC) , LT(LY_MED, KC_BSPC) , HYPR_T(KC_ENT) , KC_NO
),

[LY_EXT] = LAYOUT_split_3x5_3(
  LGUI(KC_Q)       , LGUI(KC_W)       , LGUI(KC_E)       , LGUI(KC_R)       , LGUI(KC_T) , KC_NO   , RALT(KC_U) , KC_NO        , KC_NO   , KC_NO,
  TD(TD_EXT_GUI_A) , TD(TD_EXT_GUI_S) , TD(TD_EXT_GUI_D) , TD(TD_EXT_GUI_F) , LGUI(KC_G) , KC_LEFT , KC_DOWN    , KC_UP        , KC_RGHT , HYPR(KC_SCLN),
  LGUI(KC_Z)       , LGUI(KC_X)       , LGUI(KC_C)       , LGUI(KC_V)       , LGUI(KC_B) , KC_NO   , CW_TOGG    , LSFT(KC_TAB) , KC_TAB  , KC_NO,
  KC_NO , KC_NO , KC_NO , LGUI(KC_GRV) , LGUI(KC_TAB) , KC_NO
),

[LY_SYM] = LAYOUT_split_3x5_3(
  KC_CIRC , KC_PLUS , KC_HASH , KC_PERC , KC_DLR  , KC_LABK  , KC_LCBR , KC_DQUO , KC_RCBR , KC_RABK,
  KC_EXLM , KC_MINS , KC_AMPR , KC_QUES , KC_PIPE , KC_EQUAL , KC_LBRC , KC_QUOT , KC_RBRC , KC_COLN,
  KC_TILD , KC_UNDS , KC_ASTR , KC_AT   , KC_NO   , KC_BSLS  , KC_LPRN , KC_GRV  , KC_RPRN , KC_SLASH,
  KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO
),

[LY_NUM_FN] = LAYOUT_split_3x5_3(
  KC_F9               , KC_F10              , KC_F11              , KC_F12              , KC_NO , KC_PLUS  , KC_7               , KC_8               , KC_9               , KC_ASTR,
  MT(MOD_LGUI, KC_F5) , MT(MOD_LALT, KC_F6) , MT(MOD_LCTL, KC_F7) , MT(MOD_LSFT, KC_F8) , KC_NO , KC_EQUAL , MT(MOD_RSFT, KC_4) , MT(MOD_RCTL, KC_5) , MT(MOD_RALT, KC_6) , KC_COLN,
  KC_F1               , KC_F2               , KC_F3               , KC_F4               , KC_NO , KC_MINUS , KC_1               , KC_2               , KC_3               , KC_SLASH,
  KC_NO , KC_NO , KC_NO , C(KC_B) , KC_0 , KC_NO
),

[LY_MED] = LAYOUT_split_3x5_3(
  G(C(KC_Q)) , KC_VOLD , KC_MUTE , KC_VOLU , QK_BOOT , KC_NO , RM_HUED    , RM_TOGG , RM_HUEU   , KC_PRINT_SCREEN,
  KC_NO      , KC_MPRV , KC_MPLY , KC_MNXT , KC_NO   , KC_NO , G(KC_MINS) , G(KC_0) , G(KC_EQL) , KC_NO,
  KC_NO      , KC_BRID , KC_NO   , KC_BRIU , KC_NO   , KC_NO , DT_DOWN    , DT_PRNT , DT_UP     , KC_NO,
  KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO
),
};

const uint16_t PROGMEM LY_BAS_CMB_BRACKET_LEFT[] = {KC_J, LT(LY_SYM, KC_K), COMBO_END};
const uint16_t PROGMEM LY_BAS_CMB_BRACKET_RIGHT[] = {LT(LY_SYM, KC_K), KC_L, COMBO_END};
const uint16_t PROGMEM LY_NUM_FN_CMB_COMMA[] = {KC_1, KC_2, COMBO_END};
const uint16_t PROGMEM LY_NUM_FN_CMB_DOT[] = {KC_2, KC_3, COMBO_END};

combo_t key_combos[] = {
    COMBO(LY_BAS_CMB_BRACKET_LEFT, KC_LBRC),
    COMBO(LY_BAS_CMB_BRACKET_RIGHT, KC_RBRC),
    COMBO(LY_NUM_FN_CMB_COMMA, KC_COMMA),
    COMBO(LY_NUM_FN_CMB_DOT, KC_DOT),
};
