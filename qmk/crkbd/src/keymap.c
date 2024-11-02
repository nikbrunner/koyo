#include QMK_KEYBOARD_H
#include "features/achordion.h"

enum layers {
    LY_BAS,
    LY_EXT,
    LY_SYM,
    LY_NUM,
    LY_FUN,
    LY_MED
};

enum custom_keycodes {
    SS_TILD_SLSH = SAFE_RANGE,
    SS_VIM_WA,
    SS_TODO,
    SS_BCD,
};

enum tap_dance_codes {
    TD_EXT_GUI_A,
    TD_EXT_GUI_S,
    TD_EXT_GUI_D,
    TD_EXT_GUI_F
};

// KEYMAP ===============================================================================
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LY_BAS] = LAYOUT_split_3x5_3(
//    ┌───────────┬───────────┬────────────────┬─────────────────┬─────────────────┐   ┌─────────────┬────────────┬────────────────┬───────────┬───────────┐
//    │     q     │     w     │       e        │        r        │        t        │   │      y      │     u      │       i        │     o     │     p     │
//    ├───────────┼───────────┼────────────────┼─────────────────┼─────────────────┤   ├─────────────┼────────────┼────────────────┼───────────┼───────────┤
//    │     a     │     s     │ LT(LY_SYM, d)  │        f        │        g        │   │      h      │     j      │ LT(LY_SYM, k)  │     l     │     ;     │
//    ├───────────┼───────────┼────────────────┼─────────────────┼─────────────────┤   ├─────────────┼────────────┼────────────────┼───────────┼───────────┤
//    │ LGUI_T(z) │ LALT_T(x) │   LCTL_T(c)    │    LSFT_T(v)    │        b        │   │      n      │ RSFT_T(m)  │   RCTL_T(,)    │ LALT_T(.) │ RGUI_T(/) │
//    └───────────┴───────────┼────────────────┼─────────────────┼─────────────────┤   ├─────────────┼────────────┼────────────────┼───────────┴───────────┘
//                            │ LT(LY_FUN, no) │ LT(LY_NUM, esc) │ LT(LY_EXT, spc) │   │ HYPR_T(ent) │ MEH_T(tab) │ LT(LY_MED, no) │
//                            └────────────────┴─────────────────┴─────────────────┘   └─────────────┴────────────┴────────────────┘
  KC_Q         , KC_W         , KC_E              , KC_R               , KC_T               ,     KC_Y           , KC_U          , KC_I              , KC_O           , KC_P           ,
  KC_A         , KC_S         , LT(LY_SYM, KC_D)  , KC_F               , KC_G               ,     KC_H           , KC_J          , LT(LY_SYM, KC_K)  , KC_L           , KC_SCLN        ,
  LGUI_T(KC_Z) , LALT_T(KC_X) , LCTL_T(KC_C)      , LSFT_T(KC_V)       , KC_B               ,     KC_N           , RSFT_T(KC_M)  , RCTL_T(KC_COMM)   , LALT_T(KC_DOT) , RGUI_T(KC_SLSH),
                                LT(LY_FUN, KC_NO) , LT(LY_NUM, KC_ESC) , LT(LY_EXT, KC_SPC) ,     HYPR_T(KC_ENT) , MEH_T(KC_TAB) , LT(LY_MED, KC_NO)
),

[LY_EXT] = LAYOUT_split_3x5_3(
//    ┌──────────────────┬──────────────────┬──────────────────┬──────────────────┬─────────┐   ┌───────────┬───────────┬────────────┬────────────┬────────┐
//    │     LGUI(q)      │     LGUI(w)      │     LGUI(e)      │     LGUI(r)      │ LGUI(t) │   │  G(C(c))  │  G(S(c))  │ LGUI(bspc) │ LALT(bspc) │   no   │
//    ├──────────────────┼──────────────────┼──────────────────┼──────────────────┼─────────┤   ├───────────┼───────────┼────────────┼────────────┼────────┤
//    │ TD(TD_EXT_GUI_A) │ TD(TD_EXT_GUI_S) │ TD(TD_EXT_GUI_D) │ TD(TD_EXT_GUI_F) │ LGUI(g) │   │   left    │   down    │     up     │    rght    │   :    │
//    ├──────────────────┼──────────────────┼──────────────────┼──────────────────┼─────────┤   ├───────────┼───────────┼────────────┼────────────┼────────┤
//    │     LGUI(z)      │     LGUI(x)      │     LGUI(c)      │     LGUI(v)      │ LGUI(b) │   │    no     │  CW_TOGG  │     no     │     no     │ LAG(i) │
//    └──────────────────┴──────────────────┼──────────────────┼──────────────────┼─────────┤   ├───────────┼───────────┼────────────┼────────────┴────────┘
//                                          │        no        │        no        │   no    │   │ LGUI(tab) │ LSFT(tab) │  LGUI(`)   │
//                                          └──────────────────┴──────────────────┴─────────┘   └───────────┴───────────┴────────────┘
  LGUI(KC_Q)       , LGUI(KC_W)       , LGUI(KC_E)       , LGUI(KC_R)       , LGUI(KC_T) ,     G(C(KC_C))   , G(S(KC_C))   , LGUI(KC_BSPC) , LALT(KC_BSPC) , KC_NO    ,
  TD(TD_EXT_GUI_A) , TD(TD_EXT_GUI_S) , TD(TD_EXT_GUI_D) , TD(TD_EXT_GUI_F) , LGUI(KC_G) ,     KC_LEFT      , KC_DOWN      , KC_UP         , KC_RGHT       , KC_COLN  ,
  LGUI(KC_Z)       , LGUI(KC_X)       , LGUI(KC_C)       , LGUI(KC_V)       , LGUI(KC_B) ,     KC_NO        , CW_TOGG      , LSFT(KC_TAB)   , KC_TAB         , LAG(KC_I),
                                        KC_NO            , KC_NO            , KC_NO      ,     LGUI(KC_TAB) , LSFT(KC_TAB) , LGUI(KC_GRV)
),

[LY_SYM] = LAYOUT_split_3x5_3(
//    ┌───┬───┬──────────┬──────────┬──────────┐   ┌──────────┬──────────┬──────────┬───┬───┐
//    │ ^ │ + │    #     │    %     │    $     │   │    <     │    {     │    "     │ } │ > │
//    ├───┼───┼──────────┼──────────┼──────────┤   ├──────────┼──────────┼──────────┼───┼───┤
//    │ ! │ - │    &     │    ?     │    |     │   │    =     │    [     │    '     │ ] │ : │
//    ├───┼───┼──────────┼──────────┼──────────┤   ├──────────┼──────────┼──────────┼───┼───┤
//    │ ~ │ _ │    *     │    @     │    ~/    │   │    \     │    (     │    `     │ ) │ / │
//    └───┴───┼──────────┼──────────┼──────────┤   ├──────────┼──────────┼──────────┼───┴───┘
//            │ LALT(no) │ LCTL(no) │ LGUI(no) │   │ LGUI(no) │ LCTL(no) │ LALT(no) │
//            └──────────┴──────────┴──────────┘   └──────────┴──────────┴──────────┘
  KC_CIRC , KC_PLUS , KC_HASH     , KC_PERC     , KC_DLR       ,     KC_LT       , KC_LCBR     , KC_DQUO     , KC_RCBR , KC_GT  ,
  KC_EXLM , KC_MINS , KC_AMPR     , KC_QUES     , KC_PIPE      ,     KC_EQL      , KC_LBRC     , KC_QUOT     , KC_RBRC , KC_COLN,
  KC_TILD , KC_UNDS , KC_ASTR     , KC_AT       , SS_TILD_SLSH ,     KC_BSLS     , KC_LPRN     , KC_GRV      , KC_RPRN , KC_SLSH,
                      LALT(KC_NO) , LCTL(KC_NO) , LGUI(KC_NO)  ,     LGUI(KC_NO) , LCTL(KC_NO) , LALT(KC_NO)
),

[LY_NUM] = LAYOUT_split_3x5_3(
//    ┌──────┬──────┬──────┬──────┬─────────┐   ┌──────┬──────┬──────┬──────┬──────┐
//    │  no  │  no  │  no  │  no  │ SS_TODO │   │ kp_+ │ kp_7 │ kp_8 │ kp_9 │ kp_* │
//    ├──────┼──────┼──────┼──────┼─────────┤   ├──────┼──────┼──────┼──────┼──────┤
//    │ lgui │ lalt │ lctl │ lsft │   no    │   │ kp_= │ kp_4 │ kp_5 │ kp_6 │  :   │
//    ├──────┼──────┼──────┼──────┼─────────┤   ├──────┼──────┼──────┼──────┼──────┤
//    │  no  │  no  │  no  │  no  │ SS_BCD  │   │ kp_- │ kp_1 │ kp_2 │ kp_3 │ kp_/ │
//    └──────┴──────┼──────┼──────┼─────────┤   ├──────┼──────┼──────┼──────┴──────┘
//                  │      │      │         │   │  ,   │ kp_0 │  .   │
//                  └──────┴──────┴─────────┘   └──────┴──────┴──────┘
  KC_NO   , KC_NO   , KC_NO   , KC_NO   , SS_TODO ,     KC_PPLS  , KC_P7 , KC_P8  , KC_P9 , KC_PAST,
  KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , KC_NO   ,     KC_PEQL  , KC_P4 , KC_P5  , KC_P6 , KC_COLN,
  KC_NO   , KC_NO   , KC_NO   , KC_NO   , SS_BCD  ,     KC_PMNS  , KC_P1 , KC_P2  , KC_P3 , KC_PSLS,
                      KC_TRNS , KC_TRNS , KC_TRNS ,     KC_COMMA , KC_P0 , KC_DOT
),

[LY_FUN] = LAYOUT_split_3x5_3(
//    ┌──────┬──────┬──────┬──────┬────┐   ┌────┬────┬─────┬─────┬─────┐
//    │  no  │  no  │  no  │  no  │ no │   │ no │ f9 │ f10 │ f11 │ f12 │
//    ├──────┼──────┼──────┼──────┼────┤   ├────┼────┼─────┼─────┼─────┤
//    │ rgui │ lalt │ rctl │ rsft │ no │   │ no │ f5 │ f6  │ f7  │ f8  │
//    ├──────┼──────┼──────┼──────┼────┤   ├────┼────┼─────┼─────┼─────┤
//    │  no  │  no  │  no  │  no  │ no │   │ no │ f1 │ f2  │ f3  │ f4  │
//    └──────┴──────┼──────┼──────┼────┤   ├────┼────┼─────┼─────┴─────┘
//                  │  no  │  no  │ no │   │ no │ no │ no  │
//                  └──────┴──────┴────┘   └────┴────┴─────┘
  KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO ,     KC_NO , KC_F9 , KC_F10 , KC_F11 , KC_F12,
  KC_RGUI , KC_LALT , KC_RCTL , KC_RSFT , KC_NO ,     KC_NO , KC_F5 , KC_F6  , KC_F7  , KC_F8 ,
  KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO ,     KC_NO , KC_F1 , KC_F2  , KC_F3  , KC_F4 ,
                      KC_NO   , KC_NO   , KC_NO ,     KC_NO , KC_NO , KC_NO
),

[LY_MED] = LAYOUT_split_3x5_3(
//    ┌─────────┬──────┬──────┬──────┬────────┐   ┌────┬─────────┬─────────┬─────────┬────┐
//    │ C(G(q)) │ vold │ mute │ volu │   no   │   │ no │ RGB_HUD │ RGB_TOG │ RGB_HUI │ no │
//    ├─────────┼──────┼──────┼──────┼────────┤   ├────┼─────────┼─────────┼─────────┼────┤
//    │   no    │ mprv │ mply │ mnxt │ MEH(k) │   │ no │ LGUI(-) │ LGUI(0) │ LGUI(=) │ no │
//    ├─────────┼──────┼──────┼──────┼────────┤   ├────┼─────────┼─────────┼─────────┼────┤
//    │   no    │  no  │  no  │  no  │   no   │   │ no │ DT_DOWN │ DT_PRNT │  DT_UP  │ no │
//    └─────────┴──────┼──────┼──────┼────────┤   ├────┼─────────┼─────────┼─────────┴────┘
//                     │  no  │  no  │   no   │   │ no │   no    │   no    │
//                     └──────┴──────┴────────┘   └────┴─────────┴─────────┘
  C(G(KC_Q)) , KC_VOLD , KC_MUTE , KC_VOLU , KC_NO     ,     KC_NO , RGB_HUD       , RGB_TOG    , RGB_HUI      , KC_NO,
  KC_NO      , KC_MPRV , KC_MPLY , KC_MNXT , MEH(KC_K) ,     KC_NO , LGUI(KC_MINS) , LGUI(KC_0) , LGUI(KC_EQL) , KC_NO,
  KC_NO      , KC_NO   , KC_NO   , KC_NO   , KC_NO     ,     KC_NO , DT_DOWN       , DT_PRNT    , DT_UP        , KC_NO,
                         KC_NO   , KC_NO   , KC_NO     ,     KC_NO , KC_NO         , KC_NO
)
};
// clang-format on

// Tapping Term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_Z):
        case LALT_T(KC_X):
        case LALT_T(KC_DOT):
        case RGUI_T(KC_SLSH):
            return TAPPING_TERM + 15;
        case LT(LY_SYM, KC_D):
        case LT(LY_SYM, KC_K):
        case LSFT_T(KC_V):
        case RSFT_T(KC_M):
            return TAPPING_TERM - 15;
        default:
            return TAPPING_TERM;
    }
}

// COMBO ================================================================================
const uint16_t PROGMEM LY_BAS_CMB_BACKSPACE[]     = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM LY_NUM_CMB_BACKSPACE[]     = {KC_P8, KC_P9, COMBO_END};
const uint16_t PROGMEM LY_BAS_CMB_BRACKET_LEFT[]  = {KC_J, LT(LY_SYM, KC_K), COMBO_END};
const uint16_t PROGMEM LY_BAS_CMB_BRACKET_RIGHT[] = {LT(LY_SYM, KC_K), KC_L, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    COMBO(LY_BAS_CMB_BACKSPACE, KC_BSPC),
    COMBO(LY_NUM_CMB_BACKSPACE, KC_BSPC),
    COMBO(LY_BAS_CMB_BRACKET_LEFT, KC_LBRC),
    COMBO(LY_BAS_CMB_BRACKET_RIGHT, KC_RBRC),
};
// clang-format on

void matrix_scan_user(void) {
    achordion_task();
}

// https://getreuer.info/posts/keyboards/achordion/index.html
bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    // Exclude the following keycodes from the opposite-hand check.
    switch (tap_hold_keycode) {
        case LT(LY_FUN, KC_NO):
        case LT(LY_NUM, KC_ESC):
        case LT(LY_EXT, KC_SPC):
        case HYPR_T(KC_ENT):
        case MEH_T(KC_TAB):
        case LT(LY_MED, KC_NO):
            return true;
    }

    return achordion_opposite_hands(tap_hold_record, other_record);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // https://getreuer.info/posts/keyboards/achordion/index.html
    if (!process_achordion(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case SS_TILD_SLSH:
            if (record->event.pressed) {
                SEND_STRING("~/");
            }
            break;
        case SS_VIM_WA:
            if (record->event.pressed) {
                tap_code(KC_ESC);
                SEND_STRING(":wa");
                tap_code(KC_ENT);
            }
            break;
        case SS_TODO:
            if (record->event.pressed) {
                SEND_STRING("TODO");
            }
            break;
        case SS_BCD:
            if (record->event.pressed) {
                SEND_STRING("BCD-");
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

// clang-format off
tap_dance_action_t tap_dance_actions[] = {
    [TD_EXT_GUI_A] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_td_ext_gui_a, reset_td_ext_gui_a),
    [TD_EXT_GUI_S] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_td_ext_gui_s, reset_td_ext_gui_s),
    [TD_EXT_GUI_D] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_td_ext_gui_d, reset_td_ext_gui_d),
    [TD_EXT_GUI_F] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_td_ext_gui_f, reset_td_ext_gui_f),
};
