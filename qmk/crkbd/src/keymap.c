#include QMK_KEYBOARD_H

enum layers {
    LY_BAS,
    LY_EXT,
    LY_SYM,
    LY_NUM_FN,
    LY_MED
};

enum custom_keycodes {
    SS_FATARROW = SAFE_RANGE,
};

enum tap_dance_codes {
    TD_EXT_GUI_A,
    TD_EXT_GUI_S,
    TD_EXT_GUI_D,
    TD_EXT_GUI_F,
    TD_MED_CTRLB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LY_BAS] = LAYOUT_split_3x5_3(
//    ┌─────────────────┬─────────────────┬────────────────────┬─────────────────┬───────────────┐   ┌──────────────────┬─────────────────┬─────────────────┬─────────────────┬─────────────────┐
//    │        q        │        w        │         e          │        r        │       t       │   │        y         │        u        │        i        │        o        │        p        │
//    ├─────────────────┼─────────────────┼────────────────────┼─────────────────┼───────────────┤   ├──────────────────┼─────────────────┼─────────────────┼─────────────────┼─────────────────┤
//    │        a        │        s        │   LT(LY_SYM, d)    │        f        │       g       │   │        h         │        j        │  LT(LY_SYM, k)  │        l        │        ;        │
//    ├─────────────────┼─────────────────┼────────────────────┼─────────────────┼───────────────┤   ├──────────────────┼─────────────────┼─────────────────┼─────────────────┼─────────────────┤
//    │ MT(MOD_LGUI, z) │ MT(MOD_LALT, x) │  MT(MOD_LCTL, c)   │ MT(MOD_LSFT, v) │       b       │   │        n         │ MT(MOD_RSFT, m) │ MT(MOD_RCTL, ,) │ MT(MOD_LALT, .) │ MT(MOD_LGUI, /) │
//    └─────────────────┴─────────────────┼────────────────────┼─────────────────┼───────────────┤   ├──────────────────┼─────────────────┼─────────────────┼─────────────────┴─────────────────┘
//                                        │ LT(LY_NUM_FN, esc) │ LT(LY_EXT, spc) │ MO(LY_NUM_FN) │   │ TD(TD_MED_CTRLB) │   HYPR_T(ent)   │       no        │
//                                        └────────────────────┴─────────────────┴───────────────┘   └──────────────────┴─────────────────┴─────────────────┘
  KC_Q               , KC_W               , KC_E                  , KC_R               , KC_T          ,     KC_Y             , KC_U               , KC_I                   , KC_O                 , KC_P                  ,
  KC_A               , KC_S               , LT(LY_SYM, KC_D)      , KC_F               , KC_G          ,     KC_H             , KC_J               , LT(LY_SYM, KC_K)       , KC_L                 , KC_SCLN               ,
  MT(MOD_LGUI, KC_Z) , MT(MOD_LALT, KC_X) , MT(MOD_LCTL, KC_C)    , MT(MOD_LSFT, KC_V) , KC_B          ,     KC_N             , MT(MOD_RSFT, KC_M) , MT(MOD_RCTL, KC_COMMA) , MT(MOD_LALT, KC_DOT) , MT(MOD_LGUI, KC_SLASH),
                                            LT(LY_NUM_FN, KC_ESC) , LT(LY_EXT, KC_SPC) , MO(LY_NUM_FN) ,     TD(TD_MED_CTRLB) , HYPR_T(KC_ENT)     , KC_NO
),

[LY_EXT] = LAYOUT_split_3x5_3(
//    ┌──────────────────┬──────────────────┬──────────────────┬──────────────────┬─────────┐   ┌──────┬─────────┬───────────┬───────────┬─────────┐
//    │     LGUI(q)      │     LGUI(w)      │     LGUI(e)      │     LGUI(r)      │ LGUI(t) │   │  no  │ RALT(u) │  LGUI(`)  │ LGUI(tab) │ HYPR(p) │
//    ├──────────────────┼──────────────────┼──────────────────┼──────────────────┼─────────┤   ├──────┼─────────┼───────────┼───────────┼─────────┤
//    │ TD(TD_EXT_GUI_A) │ TD(TD_EXT_GUI_S) │ TD(TD_EXT_GUI_D) │ TD(TD_EXT_GUI_F) │ LGUI(g) │   │ left │  down   │    up     │   rght    │ HYPR(;) │
//    ├──────────────────┼──────────────────┼──────────────────┼──────────────────┼─────────┤   ├──────┼─────────┼───────────┼───────────┼─────────┤
//    │     LGUI(z)      │     LGUI(x)      │     LGUI(c)      │     LGUI(v)      │ LGUI(b) │   │  no  │ CW_TOGG │ LSFT(tab) │    tab    │   no    │
//    └──────────────────┴──────────────────┼──────────────────┼──────────────────┼─────────┤   ├──────┼─────────┼───────────┼───────────┴─────────┘
//                                          │        no        │        no        │   no    │   │  no  │   no    │    no     │
//                                          └──────────────────┴──────────────────┴─────────┘   └──────┴─────────┴───────────┘
  LGUI(KC_Q)       , LGUI(KC_W)       , LGUI(KC_E)       , LGUI(KC_R)       , LGUI(KC_T) ,     KC_NO   , RALT(KC_U) , LGUI(KC_GRV) , LGUI(KC_TAB) , HYPR(KC_P)   ,
  TD(TD_EXT_GUI_A) , TD(TD_EXT_GUI_S) , TD(TD_EXT_GUI_D) , TD(TD_EXT_GUI_F) , LGUI(KC_G) ,     KC_LEFT , KC_DOWN    , KC_UP        , KC_RGHT      , HYPR(KC_SCLN),
  LGUI(KC_Z)       , LGUI(KC_X)       , LGUI(KC_C)       , LGUI(KC_V)       , LGUI(KC_B) ,     KC_NO   , CW_TOGG    , LSFT(KC_TAB) , KC_TAB       , KC_NO        ,
                                        KC_NO            , KC_NO            , KC_NO      ,     KC_NO   , KC_NO      , KC_NO
),

[LY_SYM] = LAYOUT_split_3x5_3(
//    ┌───┬───┬────┬──────┬──────┐   ┌────┬────┬────┬───┬───┐
//    │ ^ │ + │ #  │  %   │  $   │   │ <  │ {  │ "  │ } │ > │
//    ├───┼───┼────┼──────┼──────┤   ├────┼────┼────┼───┼───┤
//    │ ! │ - │ &  │  ?   │  |   │   │ =  │ [  │ '  │ ] │ : │
//    ├───┼───┼────┼──────┼──────┤   ├────┼────┼────┼───┼───┤
//    │ ~ │ _ │ *  │  @   │  no  │   │ \  │ (  │ `  │ ) │ / │
//    └───┴───┼────┼──────┼──────┤   ├────┼────┼────┼───┴───┘
//            │ no │ lalt │ lctl │   │ => │ no │ no │
//            └────┴──────┴──────┘   └────┴────┴────┘
  KC_CIRC , KC_PLUS , KC_HASH , KC_PERC , KC_DLR  ,     KC_LABK     , KC_LCBR , KC_DQUO , KC_RCBR , KC_RABK ,
  KC_EXLM , KC_MINS , KC_AMPR , KC_QUES , KC_PIPE ,     KC_EQUAL    , KC_LBRC , KC_QUOT , KC_RBRC , KC_COLN ,
  KC_TILD , KC_UNDS , KC_ASTR , KC_AT   , KC_NO   ,     KC_BSLS     , KC_LPRN , KC_GRV  , KC_RPRN , KC_SLASH,
                      KC_NO   , KC_LALT , KC_LCTL ,     SS_FATARROW , KC_NO   , KC_NO
),

[LY_NUM_FN] = LAYOUT_split_3x5_3(
//    ┌──────────────────┬──────────────────┬──────────────────┬──────────────────┬────┐   ┌──────┬─────────────────┬─────────────────┬─────────────────┬───┐
//    │        f9        │       f10        │       f11        │       f12        │ no │   │  +   │        7        │        8        │        9        │ * │
//    ├──────────────────┼──────────────────┼──────────────────┼──────────────────┼────┤   ├──────┼─────────────────┼─────────────────┼─────────────────┼───┤
//    │ MT(MOD_LGUI, f5) │ MT(MOD_LALT, f6) │ MT(MOD_LCTL, f7) │ MT(MOD_LSFT, f8) │ no │   │  =   │ MT(MOD_RSFT, 4) │ MT(MOD_RCTL, 5) │ MT(MOD_RALT, 6) │ : │
//    ├──────────────────┼──────────────────┼──────────────────┼──────────────────┼────┤   ├──────┼─────────────────┼─────────────────┼─────────────────┼───┤
//    │        f1        │        f2        │        f3        │        f4        │ no │   │  -   │        1        │        2        │        3        │ / │
//    └──────────────────┴──────────────────┼──────────────────┼──────────────────┼────┤   ├──────┼─────────────────┼─────────────────┼─────────────────┴───┘
//                                          │        no        │        no        │ no │   │ C(b) │       ent       │       no        │
//                                          └──────────────────┴──────────────────┴────┘   └──────┴─────────────────┴─────────────────┘
  KC_F9               , KC_F10              , KC_F11              , KC_F12              , KC_NO ,     KC_PLUS  , KC_7               , KC_8               , KC_9               , KC_ASTR ,
  MT(MOD_LGUI, KC_F5) , MT(MOD_LALT, KC_F6) , MT(MOD_LCTL, KC_F7) , MT(MOD_LSFT, KC_F8) , KC_NO ,     KC_EQUAL , MT(MOD_RSFT, KC_4) , MT(MOD_RCTL, KC_5) , MT(MOD_RALT, KC_6) , KC_COLN ,
  KC_F1               , KC_F2               , KC_F3               , KC_F4               , KC_NO ,     KC_MINUS , KC_1               , KC_2               , KC_3               , KC_SLASH,
                                              KC_NO               , KC_NO               , KC_NO ,     C(KC_B)  , KC_ENT             , KC_NO
),

[LY_MED] = LAYOUT_split_3x5_3(
//    ┌─────────┬──────┬──────┬──────┬─────────┐   ┌────┬─────────┬─────────┬─────────┬──────────────┐
//    │ G(C(q)) │ vold │ mute │ volu │ QK_BOOT │   │ no │ RM_HUED │ RM_TOGG │ RM_HUEU │ pRINT_SCREEN │
//    ├─────────┼──────┼──────┼──────┼─────────┤   ├────┼─────────┼─────────┼─────────┼──────────────┤
//    │   no    │ mprv │ mply │ mnxt │   no    │   │ no │  G(-)   │  G(0)   │  G(=)   │      no      │
//    ├─────────┼──────┼──────┼──────┼─────────┤   ├────┼─────────┼─────────┼─────────┼──────────────┤
//    │   no    │ bRID │  no  │ bRIU │   no    │   │ no │ DT_DOWN │ DT_PRNT │  DT_UP  │      no      │
//    └─────────┴──────┼──────┼──────┼─────────┤   ├────┼─────────┼─────────┼─────────┴──────────────┘
//                     │  no  │  no  │   no    │   │ no │   no    │   no    │
//                     └──────┴──────┴─────────┘   └────┴─────────┴─────────┘
  G(C(KC_Q)) , KC_VOLD , KC_MUTE , KC_VOLU , QK_BOOT ,     KC_NO , RM_HUED    , RM_TOGG , RM_HUEU   , KC_PRINT_SCREEN,
  KC_NO      , KC_MPRV , KC_MPLY , KC_MNXT , KC_NO   ,     KC_NO , G(KC_MINS) , G(KC_0) , G(KC_EQL) , KC_NO          ,
  KC_NO      , KC_BRID , KC_NO   , KC_BRIU , KC_NO   ,     KC_NO , DT_DOWN    , DT_PRNT , DT_UP     , KC_NO          ,
                         KC_NO   , KC_NO   , KC_NO   ,     KC_NO , KC_NO      , KC_NO
)
};

// TAPPING TERM ============================================================================
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LGUI, KC_Z):
        case MT(MOD_LALT, KC_X):
        case MT(MOD_LALT, KC_DOT):
        case MT(MOD_RGUI, KC_SLASH):
            return TAPPING_TERM + 15;

        
        default:
            return TAPPING_TERM;
    }
}

// COMBO ================================================================================
// Backspace
const uint16_t PROGMEM LY_BAS_CMB_BACKSPACE[]     = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM LY_NUM_FN_CMB_BACKSPACE[]  = {KC_8, KC_9, COMBO_END};
const uint16_t PROGMEM LY_SYM_CMB_BACKSPACE[]     = {KC_DQUO , KC_RCBR, COMBO_END};

// Brackets
const uint16_t PROGMEM LY_BAS_CMB_BRACKET_LEFT[]  = {KC_J, LT(LY_SYM, KC_K), COMBO_END};
const uint16_t PROGMEM LY_BAS_CMB_BRACKET_RIGHT[] = {LT(LY_SYM, KC_K), KC_L, COMBO_END};

// Punctuation on NUM layer
const uint16_t PROGMEM LY_NUM_FN_CMB_COMMA[]  = {KC_1, KC_2, COMBO_END};
const uint16_t PROGMEM LY_NUM_FN_CMB_DOT[]    = {KC_2, KC_3, COMBO_END};

// 0 on NUM layer
const uint16_t PROGMEM LY_NUM_FN_CMB_0[] = {MT(MOD_RCTL, KC_5), MT(MOD_RALT, KC_6), COMBO_END};

combo_t key_combos[] = {
    // Backspace
    COMBO(LY_BAS_CMB_BACKSPACE, KC_BSPC),
    COMBO(LY_NUM_FN_CMB_BACKSPACE, KC_BSPC),
    COMBO(LY_SYM_CMB_BACKSPACE, KC_BSPC),

    // Brackets
    COMBO(LY_BAS_CMB_BRACKET_LEFT, KC_LBRC),
    COMBO(LY_BAS_CMB_BRACKET_RIGHT, KC_RBRC),

    // Punctuation on NUM layer
    COMBO(LY_NUM_FN_CMB_COMMA, KC_COMMA),
    COMBO(LY_NUM_FN_CMB_DOT, KC_DOT),

    // 0 on NUM layer
    COMBO(LY_NUM_FN_CMB_0, KC_0),
};

// Chordal Hold implementation
bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                     uint16_t other_keycode, keyrecord_t* other_record) {
    // Define which keys should always hold when chorded
    switch (tap_hold_keycode) {
        // Left hand
        case MO(LY_NUM_FN):
        case LT(LY_EXT, KC_SPC):

        // Right hand
        case HYPR_T(KC_ENT):
        case TD(TD_MED_CTRLB):
            return true;
    }
    
    // Otherwise defer to the opposite hands rule (default behavior)
    return get_chordal_hold_default(tap_hold_record, other_record);
}

// Optional: Define handedness for keys
// If you don't define this, QMK will attempt to guess based on the keyboard layout
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_split_3x5_3(
        'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R',
                'L', 'L', 'L',    'R', 'R', 'R'
    );

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SS_FATARROW:
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            break;
    }
    return true;
}

// TAP DANCE ============================================================================
enum tab_dance_events {
    //
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    MORE_TAPS
};

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) {
            return SINGLE_TAP;
        } else {
            return SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        if (!state->pressed) {
            return DOUBLE_TAP;
        } else {
            return DOUBLE_HOLD;
        }
    }
    return MORE_TAPS;
}

void on_td_ext_gui_a(tap_dance_state_t *state, void *user_data) {
    uint8_t dance = dance_step(state);
    switch (dance) {
        case SINGLE_TAP:
            register_code(KC_LGUI);
            register_code(KC_A);
            unregister_code(KC_A);
            unregister_code(KC_LGUI);
            break;
        case SINGLE_HOLD:
            register_code(KC_LGUI);
            break;
    }
}

void reset_td_ext_gui_a(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_LGUI);
}

void on_td_ext_gui_s(tap_dance_state_t *state, void *user_data) {
    uint8_t dance = dance_step(state);
    switch (dance) {
        case SINGLE_TAP:
            register_code(KC_LGUI);
            register_code(KC_S);
            unregister_code(KC_S);
            unregister_code(KC_LGUI);
            break;
        case SINGLE_HOLD:
            register_code(KC_LALT);
            break;
    }
}

void reset_td_ext_gui_s(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_LALT);
}

void on_td_ext_gui_d(tap_dance_state_t *state, void *user_data) {
    uint8_t dance = dance_step(state);
    switch (dance) {
        case SINGLE_TAP:
            register_code(KC_LGUI);
            register_code(KC_D);
            unregister_code(KC_D);
            unregister_code(KC_LGUI);
            break;
        case SINGLE_HOLD:
            register_code(KC_LCTL);
            break;
    }
}

void reset_td_ext_gui_d(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_LCTL);
}

void on_td_ext_gui_f(tap_dance_state_t *state, void *user_data) {
    uint8_t dance = dance_step(state);
    switch (dance) {
        case SINGLE_TAP:
            register_code(KC_LGUI);
            register_code(KC_F);
            unregister_code(KC_F);
            unregister_code(KC_LGUI);
            break;
        case SINGLE_HOLD:
            register_code(KC_LSFT);
            break;
    }
}

void reset_td_ext_gui_f(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_LSFT);
}

void on_td_med_ctrlb(tap_dance_state_t *state, void *user_data) {
    uint8_t dance = dance_step(state);
    switch (dance) {
        case SINGLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_B);
            unregister_code(KC_B);
            unregister_code(KC_LCTL);
            break;
        case SINGLE_HOLD:
            layer_on(LY_MED);
            break;
    }
}

void reset_td_med_ctrlb(tap_dance_state_t *state, void *user_data) {
    layer_off(LY_MED);
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_EXT_GUI_A] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_td_ext_gui_a, reset_td_ext_gui_a),
    [TD_EXT_GUI_S] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_td_ext_gui_s, reset_td_ext_gui_s),
    [TD_EXT_GUI_D] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_td_ext_gui_d, reset_td_ext_gui_d),
    [TD_EXT_GUI_F] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_td_ext_gui_f, reset_td_ext_gui_f),
    [TD_MED_CTRLB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_td_med_ctrlb, reset_td_med_ctrlb),
};

// RGB LAYER LIGHTING ============================================================================
// https://getreuer.info/posts/keyboards/palettefx/index.html
layer_state_t layer_state_set_user(layer_state_t state) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);

    switch (get_highest_layer(state)) {
        case LY_BAS:
            rgb_matrix_sethsv_noeeprom(15, 255, 255);   // Orange
            break;
        case LY_EXT:
            rgb_matrix_sethsv_noeeprom(200, 255, 255);  // Purple
            break;
        case LY_SYM:
            rgb_matrix_sethsv_noeeprom(85, 255, 255);   // Green
            break;
        case LY_NUM_FN:
            rgb_matrix_sethsv_noeeprom(170, 255, 255);  // Blue
            break;
        case LY_MED:
            rgb_matrix_sethsv_noeeprom(0, 255, 255);    // Red
            break;
    }
    return state;
}
