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
[LY_BAS] = LAYOUT_moonlander(
  KC_ESC  , KC_1 , KC_2 , KC_3             , KC_4 , KC_5 , KC_NO , KC_NO , KC_6 , KC_7 , KC_8             , KC_9 , KC_0    , KC_MINS,
  KC_TAB  , KC_Q , KC_W , KC_E             , KC_R , KC_T , KC_NO , KC_NO , KC_Y , KC_U , KC_I             , KC_O , KC_P    , KC_EQL,
  KC_LSFT , KC_A , KC_S , LT(LY_SYM, KC_D) , KC_F , KC_G , KC_NO , KC_NO , KC_H , KC_J , LT(LY_SYM, KC_K) , KC_L , KC_SCLN , KC_RSFT,
  KC_LCTL , MT(MOD_LGUI, KC_Z) , MT(MOD_LALT, KC_X) , MT(MOD_LCTL, KC_C) , MT(MOD_LSFT, KC_V) , KC_B  , KC_N  , MT(MOD_RSFT, KC_M) , MT(MOD_RCTL, KC_COMMA) , MT(MOD_LALT, KC_DOT) , MT(MOD_RGUI, KC_SLASH) , KC_RCTL,
  KC_NO   , KC_NO              , KC_NO              , KC_NO              , KC_NO              , KC_NO , KC_NO , KC_NO              , KC_NO                  , KC_NO                , KC_NO                  , KC_NO,
  LT(LY_EXT, KC_SPC) , LT(LY_NUM_FN, KC_ESC) , KC_NO , KC_NO , LT(LY_MED, KC_BSPC) , HYPR_T(KC_ENT)
),

[LY_EXT] = LAYOUT_moonlander(
  KC_TRNS , KC_TRNS    , KC_TRNS    , KC_TRNS    , KC_TRNS    , KC_TRNS    , KC_NO , KC_NO , KC_TRNS , KC_TRNS    , KC_TRNS , KC_TRNS , KC_TRNS       , KC_TRNS,
  KC_TRNS , LGUI(KC_Q) , LGUI(KC_W) , LGUI(KC_E) , LGUI(KC_R) , LGUI(KC_T) , KC_NO , KC_NO , KC_NO   , RALT(KC_U) , KC_NO   , KC_NO   , KC_NO         , KC_TRNS,
  KC_TRNS , EXT_A      , EXT_S      , EXT_D      , EXT_F      , LGUI(KC_G) , KC_NO , KC_NO , KC_LEFT , KC_DOWN    , KC_UP   , KC_RGHT , HYPR(KC_SCLN) , KC_TRNS,
  KC_TRNS , LGUI(KC_Z) , LGUI(KC_X) , LGUI(KC_C) , LGUI(KC_V) , LGUI(KC_B) , KC_NO , CW_TOGG , LSFT(KC_TAB) , KC_TAB , KC_NO , KC_TRNS,
  KC_NO   , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO      , KC_NO , KC_NO   , KC_NO        , KC_NO  , KC_NO , KC_NO,
  KC_NO , KC_NO , KC_NO , KC_NO , LGUI(KC_GRV) , LGUI(KC_TAB)
),

[LY_SYM] = LAYOUT_moonlander(
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_NO , KC_NO , KC_TRNS  , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_TRNS , KC_CIRC , KC_PLUS , KC_HASH , KC_PERC , KC_DLR  , KC_NO , KC_NO , KC_LABK  , KC_LCBR , KC_DQUO , KC_RCBR , KC_RABK , KC_TRNS,
  KC_TRNS , KC_EXLM , KC_MINS , KC_AMPR , KC_QUES , KC_PIPE , KC_NO , KC_NO , KC_EQUAL , KC_LBRC , KC_QUOT , KC_RBRC , KC_COLN , KC_TRNS,
  KC_TRNS , KC_TILD , KC_UNDS , KC_ASTR , KC_AT , KC_NO , KC_BSLS , KC_LPRN , KC_GRV , KC_RPRN , KC_SLASH , KC_TRNS,
  KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO , KC_NO , KC_NO   , KC_NO   , KC_NO  , KC_NO   , KC_NO    , KC_NO,
  KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO
),

[LY_NUM_FN] = LAYOUT_moonlander(
  KC_TRNS , KC_TRNS             , KC_TRNS             , KC_TRNS             , KC_TRNS             , KC_TRNS , KC_NO , KC_NO , KC_TRNS  , KC_TRNS            , KC_TRNS            , KC_TRNS            , KC_TRNS , KC_TRNS,
  KC_TRNS , KC_F9               , KC_F10              , KC_F11              , KC_F12              , KC_NO   , KC_NO , KC_NO , KC_PLUS  , KC_7               , KC_8               , KC_9               , KC_ASTR , KC_TRNS,
  KC_NO   , MT(MOD_LGUI, KC_F5) , MT(MOD_LALT, KC_F6) , MT(MOD_LCTL, KC_F7) , MT(MOD_LSFT, KC_F8) , KC_NO   , KC_NO , KC_NO , KC_EQUAL , MT(MOD_RSFT, KC_4) , MT(MOD_RCTL, KC_5) , MT(MOD_RALT, KC_6) , KC_COLN , KC_TRNS,
  KC_TRNS , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_NO , KC_MINUS , KC_1  , KC_2  , KC_3  , KC_SLASH , KC_TRNS,
  KC_NO   , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO , KC_NO    , KC_NO , KC_NO , KC_NO , KC_NO    , KC_NO,
  KC_NO , KC_NO , KC_NO , KC_NO , C(KC_B) , KC_0
),

[LY_MED] = LAYOUT_moonlander(
  KC_TRNS , KC_TRNS    , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_NO , KC_NO , KC_TRNS , KC_TRNS    , KC_TRNS , KC_TRNS   , KC_TRNS         , KC_TRNS,
  KC_TRNS , G(C(KC_Q)) , KC_VOLD , KC_MUTE , KC_VOLU , QK_BOOT , KC_NO , KC_NO , KC_NO   , KC_NO      , RM_TOGG , KC_NO     , KC_PRINT_SCREEN , KC_TRNS,
  KC_TRNS , KC_NO      , KC_MPRV , KC_MPLY , KC_MNXT , KC_NO   , KC_NO , KC_NO , KC_NO   , G(KC_MINS) , G(KC_0) , G(KC_EQL) , KC_NO           , KC_TRNS,
  KC_TRNS , KC_NO , KC_BRID , KC_NO , KC_BRIU , KC_NO , KC_NO , DT_DOWN , DT_PRNT , DT_UP , KC_NO , KC_TRNS,
  KC_NO   , KC_NO , KC_NO   , KC_NO , KC_NO   , KC_NO , KC_NO , KC_NO   , KC_NO   , KC_NO , KC_NO , KC_NO,
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

layer_state_t layer_state_set_user(layer_state_t state) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    switch (get_highest_layer(state)) {
        case LY_BAS:
            rgb_matrix_sethsv_noeeprom(184, 130, 70);
            break;
        case LY_EXT:
            rgb_matrix_sethsv_noeeprom(236, 135, 70);
            break;
        case LY_SYM:
            rgb_matrix_sethsv_noeeprom(94, 150, 70);
            break;
        case LY_NUM_FN:
            rgb_matrix_sethsv_noeeprom(16, 215, 70);
            break;
        case LY_MED:
            rgb_matrix_sethsv_noeeprom(24, 95, 70);
            break;
    }
    return state;
}

static hsv_t key_highlight(uint8_t layer, keypos_t pos) {
    switch (layer) {
        case LY_BAS:
            switch (keymap_key_to_keycode(layer, pos)) {
                case KC_H:
                case KC_J:
                case LT(LY_SYM, KC_K):
                case KC_L:
                    return (hsv_t){27, 240, 228};
            }
            break;
        case LY_EXT:
            switch (keymap_key_to_keycode(layer, pos)) {
                case KC_LEFT:
                case KC_DOWN:
                case KC_UP:
                case KC_RGHT:
                    return (hsv_t){27, 240, 228};
            }
            break;
        case LY_SYM:
            switch (keymap_key_to_keycode(layer, pos)) {
                case KC_LPRN:
                case KC_RPRN:
                case KC_LBRC:
                case KC_RBRC:
                case KC_LCBR:
                case KC_RCBR:
                case KC_LABK:
                case KC_RABK:
                    return (hsv_t){27, 240, 228};
                case KC_DQUO:
                case KC_QUOT:
                case KC_GRV:
                    return (hsv_t){120, 190, 195};
                case KC_PLUS:
                case KC_MINS:
                case KC_ASTR:
                case KC_PERC:
                case KC_EXLM:
                case KC_AMPR:
                case KC_PIPE:
                case KC_CIRC:
                case KC_TILD:
                case KC_EQUAL:
                case KC_SLASH:
                    return (hsv_t){236, 135, 211};
            }
            break;
        case LY_NUM_FN:
            switch (keymap_key_to_keycode(layer, pos)) {
                case KC_0:
                case KC_1:
                case KC_2:
                case KC_3:
                case MT(MOD_RSFT, KC_4):
                case MT(MOD_RCTL, KC_5):
                case MT(MOD_RALT, KC_6):
                case KC_7:
                case KC_8:
                case KC_9:
                    return (hsv_t){120, 190, 195};
            }
            break;
        case LY_MED:
            switch (keymap_key_to_keycode(layer, pos)) {
                case KC_VOLD:
                case KC_MUTE:
                case KC_VOLU:
                case KC_MPRV:
                case KC_MPLY:
                case KC_MNXT:
                    return (hsv_t){184, 130, 215};
                case QK_BOOT:
                    return (hsv_t){251, 200, 254};
            }
            break;
    }
    // Looks through transparent keys, so the outer ring's mods stay lit on every layer
    uint16_t keycode = keymap_key_to_keycode(layer_switch_get_layer(pos), pos);
    return IS_MODIFIER_KEYCODE(keycode) || IS_QK_MOD_TAP(keycode) ? (hsv_t){24, 95, 225} : (hsv_t){0, 0, 0};
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led = g_led_config.matrix_co[row][col];
            if (led == NO_LED || led < led_min || led >= led_max) continue;
            hsv_t hsv = key_highlight(layer, (keypos_t){.col = col, .row = row});
            if (hsv.v == 0) continue;
            // rgb_matrix_set_color bypasses the board's brightness cap
            hsv.v = hsv.v * RGB_MATRIX_MAXIMUM_BRIGHTNESS / UINT8_MAX;
            rgb_t rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(led, rgb.r, rgb.g, rgb.b);
        }
    }
    return false;
}
