#include QMK_KEYBOARD_H
#include "features/achordion.h"
#include "version.h"

#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE

enum layers {
  LY_BAS,
  LY_EXT,
  LY_SYM,
  LY_NUM,
  LY_FUN,
  LY_MED
};

enum custom_keycodes {
  SS_TILD_SLSH = ML_SAFE_RANGE,
  SS_VIM_WA,
  SS_TODO,
  SS_BCD,
  SS_FATARROW,
};

enum tap_dance_codes {
  TD_EXT_GUI_A,
  TD_EXT_GUI_S,
  TD_EXT_GUI_D,
  TD_EXT_GUI_F
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LY_BAS] = LAYOUT_moonlander(
//    ┌───┬─────────────────┬─────────────────┬─────────────────┬─────────────────┬───┬───┐   ┌───┬───┬─────────────────┬─────────────────┬─────────────────┬─────────────────┬───┐
//    │   │                 │                 │                 │                 │   │   │   │   │   │                 │                 │                 │                 │   │
//    ├───┼─────────────────┼─────────────────┼─────────────────┼─────────────────┼───┼───┤   ├───┼───┼─────────────────┼─────────────────┼─────────────────┼─────────────────┼───┤
//    │   │        q        │        w        │        e        │        r        │ t │   │   │   │ y │        u        │        i        │        o        │        p        │   │
//    ├───┼─────────────────┼─────────────────┼─────────────────┼─────────────────┼───┼───┤   ├───┼───┼─────────────────┼─────────────────┼─────────────────┼─────────────────┼───┤
//    │   │        a        │        s        │  LT(LY_SYM, d)  │        f        │ g │   │   │   │ h │        j        │  LT(LY_SYM, k)  │        l        │        ;        │   │
//    ├───┼─────────────────┼─────────────────┼─────────────────┼─────────────────┼───┼───┘   └───┼───┼─────────────────┼─────────────────┼─────────────────┼─────────────────┼───┤
//    │   │ MT(MOD_LGUI, z) │ MT(MOD_LALT, x) │ MT(MOD_LCTL, c) │ MT(MOD_LSFT, v) │ b │           │ n │ MT(MOD_RSFT, m) │ MT(MOD_RCTL, ,) │ MT(MOD_LALT, .) │ MT(MOD_RGUI, /) │   │
//    ├───┼─────────────────┼─────────────────┼─────────────────┼─────────────────┼───┤           ├───┼─────────────────┼─────────────────┼─────────────────┼─────────────────┼───┤
//    │   │                 │                 │   MO(LY_FUN)    │ LT(LY_NUM, esc) │   │           │   │   MEH_T(tab)    │ LT(LY_MED, no)  │                 │                 │   │
//    └───┴─────────────────┴─────────────────┴─────────────────┼─────────────────┼───┼───┐   ┌───┼───┼─────────────────┼─────────────────┴─────────────────┴─────────────────┴───┘
//                                                              │ LT(LY_EXT, spc) │   │   │   │   │   │   HYPR_T(ent)   │
//                                                              └─────────────────┴───┴───┘   └───┴───┴─────────────────┘
  KC_TRANSPARENT , KC_TRANSPARENT     , KC_TRANSPARENT     , KC_TRANSPARENT     , KC_TRANSPARENT     , KC_TRANSPARENT , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT     , KC_TRANSPARENT         , KC_TRANSPARENT       , KC_TRANSPARENT         , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_Q               , KC_W               , KC_E               , KC_R               , KC_T           , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_Y           , KC_U               , KC_I                   , KC_O                 , KC_P                   , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_A               , KC_S               , LT(LY_SYM, KC_D)   , KC_F               , KC_G           , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_H           , KC_J               , LT(LY_SYM, KC_K)       , KC_L                 , KC_SCLN                , KC_TRANSPARENT,
  KC_TRANSPARENT , MT(MOD_LGUI, KC_Z) , MT(MOD_LALT, KC_X) , MT(MOD_LCTL, KC_C) , MT(MOD_LSFT, KC_V) , KC_B           ,                                       KC_N           , MT(MOD_RSFT, KC_M) , MT(MOD_RCTL, KC_COMMA) , MT(MOD_LALT, KC_DOT) , MT(MOD_RGUI, KC_SLASH) , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_TRANSPARENT     , KC_TRANSPARENT     , MO(LY_FUN)         , LT(LY_NUM, KC_ESC) , KC_TRANSPARENT ,                                       KC_TRANSPARENT , MEH_T(KC_TAB)      , LT(LY_MED, KC_NO)      , KC_TRANSPARENT       , KC_TRANSPARENT         , KC_TRANSPARENT,
                                                                                  LT(LY_EXT, KC_SPC) , KC_TRANSPARENT , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT , HYPR_T(KC_ENT)
),

[LY_EXT] = LAYOUT_moonlander(
//    ┌───┬──────────────────┬──────────────────┬──────────────────┬──────────────────┬─────────┬───┐   ┌───┬───────────────┬───────────────┬────────────┬────────────┬───────────────┬───┐
//    │   │                  │                  │                  │                  │         │   │   │   │               │               │            │            │               │   │
//    ├───┼──────────────────┼──────────────────┼──────────────────┼──────────────────┼─────────┼───┤   ├───┼───────────────┼───────────────┼────────────┼────────────┼───────────────┼───┤
//    │   │     LGUI(q)      │     LGUI(w)      │     LGUI(e)      │     LGUI(r)      │ LGUI(t) │   │   │   │ LGUI(LCTL(c)) │ LGUI(LSFT(c)) │ LGUI(bspc) │ LALT(bspc) │               │   │
//    ├───┼──────────────────┼──────────────────┼──────────────────┼──────────────────┼─────────┼───┤   ├───┼───────────────┼───────────────┼────────────┼────────────┼───────────────┼───┤
//    │   │ TD(TD_EXT_GUI_A) │ TD(TD_EXT_GUI_S) │ TD(TD_EXT_GUI_D) │ TD(TD_EXT_GUI_F) │ LGUI(g) │   │   │   │     left      │     down      │     up     │    rght    │       :       │   │
//    ├───┼──────────────────┼──────────────────┼──────────────────┼──────────────────┼─────────┼───┘   └───┼───────────────┼───────────────┼────────────┼────────────┼───────────────┼───┤
//    │   │     LGUI(z)      │     LGUI(x)      │     LGUI(c)      │     LGUI(v)      │ LGUI(b) │           │               │    CW_TOGG    │ LSFT(tab)  │    tab     │ LALT(LGUI(i)) │   │
//    ├───┼──────────────────┼──────────────────┼──────────────────┼──────────────────┼─────────┤           ├───────────────┼───────────────┼────────────┼────────────┼───────────────┼───┤
//    │   │                  │                  │                  │                  │         │           │               │   LSFT(tab)   │  LGUI(`)   │            │               │   │
//    └───┴──────────────────┴──────────────────┴──────────────────┼──────────────────┼─────────┼───┐   ┌───┼───────────────┼───────────────┼────────────┴────────────┴───────────────┴───┘
//                                                                 │                  │         │   │   │   │               │   LGUI(tab)   │
//                                                                 └──────────────────┴─────────┴───┘   └───┴───────────────┴───────────────┘
  KC_TRANSPARENT , KC_TRANSPARENT   , KC_TRANSPARENT   , KC_TRANSPARENT   , KC_TRANSPARENT   , KC_TRANSPARENT , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT   , KC_TRANSPARENT   , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT   , KC_TRANSPARENT,
  KC_TRANSPARENT , LGUI(KC_Q)       , LGUI(KC_W)       , LGUI(KC_E)       , LGUI(KC_R)       , LGUI(KC_T)     , KC_TRANSPARENT ,     KC_TRANSPARENT , LGUI(LCTL(KC_C)) , LGUI(LSFT(KC_C)) , LGUI(KC_BSPC)  , LALT(KC_BSPC)  , KC_TRANSPARENT   , KC_TRANSPARENT,
  KC_TRANSPARENT , TD(TD_EXT_GUI_A) , TD(TD_EXT_GUI_S) , TD(TD_EXT_GUI_D) , TD(TD_EXT_GUI_F) , LGUI(KC_G)     , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_LEFT          , KC_DOWN          , KC_UP          , KC_RIGHT       , KC_COLN          , KC_TRANSPARENT,
  KC_TRANSPARENT , LGUI(KC_Z)       , LGUI(KC_X)       , LGUI(KC_C)       , LGUI(KC_V)       , LGUI(KC_B)     ,                                       KC_TRANSPARENT   , CW_TOGG          , LSFT(KC_TAB)   , KC_TAB         , LALT(LGUI(KC_I)) , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_TRANSPARENT   , KC_TRANSPARENT   , KC_TRANSPARENT   , KC_TRANSPARENT   , KC_TRANSPARENT ,                                       KC_TRANSPARENT   , LSFT(KC_TAB)     , LGUI(KC_GRV)   , KC_TRANSPARENT , KC_TRANSPARENT   , KC_TRANSPARENT,
                                                                            KC_TRANSPARENT   , KC_TRANSPARENT , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT   , LGUI(KC_TAB)
),

[LY_SYM] = LAYOUT_moonlander(
//    ┌───┬───┬───┬───┬──────────┬──────────┬───┐   ┌───┬───┬────┬───┬───┬───┬───┐
//    │   │   │   │   │          │          │   │   │   │   │    │   │   │   │   │
//    ├───┼───┼───┼───┼──────────┼──────────┼───┤   ├───┼───┼────┼───┼───┼───┼───┤
//    │   │ ^ │ + │ # │    %     │    $     │   │   │   │ < │ {  │ " │ } │ > │   │
//    ├───┼───┼───┼───┼──────────┼──────────┼───┤   ├───┼───┼────┼───┼───┼───┼───┤
//    │   │ ! │ - │ & │    ?     │    |     │   │   │   │ = │ [  │ ' │ ] │ : │   │
//    ├───┼───┼───┼───┼──────────┼──────────┼───┘   └───┼───┼────┼───┼───┼───┼───┤
//    │   │ ~ │ _ │ * │    @     │    ~/    │           │ \ │ (  │ ` │ ) │ / │   │
//    ├───┼───┼───┼───┼──────────┼──────────┤           ├───┼────┼───┼───┼───┼───┤
//    │   │   │   │   │ LALT(no) │          │           │   │ => │   │   │   │   │
//    └───┴───┴───┴───┼──────────┼──────────┼───┐   ┌───┼───┼────┼───┴───┴───┴───┘
//                    │ LCTL(no) │ LGUI(no) │   │   │   │   │    │
//                    └──────────┴──────────┴───┘   └───┴───┴────┘
  KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_CIRC        , KC_PLUS        , KC_HASH        , KC_PERC        , KC_DLR         , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_LABK        , KC_LCBR        , KC_DQUO        , KC_RCBR        , KC_RABK        , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_EXLM        , KC_MINUS       , KC_AMPR        , KC_QUES        , KC_PIPE        , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_EQUAL       , KC_LBRC        , KC_QUOTE       , KC_RBRC        , KC_COLN        , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_TILD        , KC_UNDS        , KC_ASTR        , KC_AT          , SS_TILD_SLSH   ,                                       KC_BSLS        , KC_LPRN        , KC_GRAVE       , KC_RPRN        , KC_SLASH       , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , LALT(KC_NO)    , KC_TRANSPARENT ,                                       KC_TRANSPARENT , SS_FATARROW    , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT,
                                                                      LCTL(KC_NO)    , LGUI(KC_NO)    , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT
),

[LY_NUM] = LAYOUT_moonlander(
//    ┌───┬────────────┬──────┬──────┬──────┬──────┬───┐   ┌───┬───┬───┬───┬───┬───┬───┐
//    │   │            │      │      │      │      │   │   │   │   │   │   │   │   │   │
//    ├───┼────────────┼──────┼──────┼──────┼──────┼───┤   ├───┼───┼───┼───┼───┼───┼───┤
//    │   │            │      │      │      │ TODO │   │   │   │ + │ 7 │ 8 │ 9 │ * │   │
//    ├───┼────────────┼──────┼──────┼──────┼──────┼───┤   ├───┼───┼───┼───┼───┼───┼───┤
//    │   │    lgui    │ lalt │ lctl │ lsft │      │   │   │   │ = │ 4 │ 5 │ 6 │ : │   │
//    ├───┼────────────┼──────┼──────┼──────┼──────┼───┘   └───┼───┼───┼───┼───┼───┼───┤
//    │   │ HYPR_T(no) │      │      │      │ BCD- │           │ - │ 1 │ 2 │ 3 │ / │   │
//    ├───┼────────────┼──────┼──────┼──────┼──────┤           ├───┼───┼───┼───┼───┼───┤
//    │   │            │      │      │      │      │           │   │ 0 │ , │   │   │   │
//    └───┴────────────┴──────┴──────┼──────┼──────┼───┐   ┌───┼───┼───┼───┴───┴───┴───┘
//                                   │      │      │   │   │   │   │ . │
//                                   └──────┴──────┴───┘   └───┴───┴───┘
  KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , SS_TODO        , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_PLUS        , KC_7           , KC_8           , KC_9           , KC_ASTR        , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_LGUI        , KC_LALT        , KC_LCTL        , KC_LSFT        , KC_TRANSPARENT , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_EQUAL       , KC_4           , KC_5           , KC_6           , KC_COLN        , KC_TRANSPARENT,
  KC_TRANSPARENT , HYPR_T(KC_NO)  , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , SS_BCD         ,                                       KC_MINUS       , KC_1           , KC_2           , KC_3           , KC_SLASH       , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,                                       KC_TRANSPARENT , KC_0           , KC_COMMA       , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT,
                                                                      KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT , KC_DOT
),

[LY_FUN] = LAYOUT_moonlander(
//    ┌───┬──────────┬──────────┬───────────┬────────────┬───┬───┐   ┌───┬───┬────┬─────┬─────┬─────┬───┐
//    │   │          │          │           │            │   │   │   │   │   │    │     │     │     │   │
//    ├───┼──────────┼──────────┼───────────┼────────────┼───┼───┤   ├───┼───┼────┼─────┼─────┼─────┼───┤
//    │   │          │          │           │            │   │   │   │   │   │ f9 │ f10 │ f11 │ f12 │   │
//    ├───┼──────────┼──────────┼───────────┼────────────┼───┼───┤   ├───┼───┼────┼─────┼─────┼─────┼───┤
//    │   │ left_GUI │ left_ALT │ left_CTRL │ left_SHIFT │   │   │   │   │   │ f5 │ f6  │ f7  │ f8  │   │
//    ├───┼──────────┼──────────┼───────────┼────────────┼───┼───┘   └───┼───┼────┼─────┼─────┼─────┼───┤
//    │   │          │          │           │            │   │           │   │ f1 │ f2  │ f3  │ f4  │   │
//    ├───┼──────────┼──────────┼───────────┼────────────┼───┤           ├───┼────┼─────┼─────┼─────┼───┤
//    │   │          │          │           │            │   │           │   │    │     │     │     │   │
//    └───┴──────────┴──────────┴───────────┼────────────┼───┼───┐   ┌───┼───┼────┼─────┴─────┴─────┴───┘
//                                          │            │   │   │   │   │   │    │
//                                          └────────────┴───┴───┘   └───┴───┴────┘
  KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT , KC_F9          , KC_F10         , KC_F11         , KC_F12         , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_LEFT_GUI    , KC_LEFT_ALT    , KC_LEFT_CTRL   , KC_LEFT_SHIFT  , KC_TRANSPARENT , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT , KC_F5          , KC_F6          , KC_F7          , KC_F8          , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,                                       KC_TRANSPARENT , KC_F1          , KC_F2          , KC_F3          , KC_F4          , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,                                       KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT,
                                                                      KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT
),

[LY_MED] = LAYOUT_moonlander(
//    ┌───┬───────────────┬──────┬──────┬──────┬─────────┬───┐   ┌───┬───┬──────────────────────────────┬───────────────────────────────┬────────────────────────────┬───┬───┐
//    │   │               │      │      │      │         │   │   │   │   │                              │                               │                            │   │   │
//    ├───┼───────────────┼──────┼──────┼──────┼─────────┼───┤   ├───┼───┼──────────────────────────────┼───────────────────────────────┼────────────────────────────┼───┼───┤
//    │   │ LGUI(LCTL(q)) │ vold │ mute │ volu │ QK_BOOT │   │   │   │   │           RGB_HUD            │            RGB_TOG            │          RGB_HUI           │   │   │
//    ├───┼───────────────┼──────┼──────┼──────┼─────────┼───┤   ├───┼───┼──────────────────────────────┼───────────────────────────────┼────────────────────────────┼───┼───┤
//    │   │               │ mprv │ mply │ mnxt │ MEH(k)  │   │   │   │   │           LGUI(-)            │            LGUI(0)            │          LGUI(=)           │   │   │
//    ├───┼───────────────┼──────┼──────┼──────┼─────────┼───┘   └───┼───┼──────────────────────────────┼───────────────────────────────┼────────────────────────────┼───┼───┤
//    │   │               │      │      │      │         │           │   │ QK_DYNAMIC_TAPPING_TERM_DOWN │ QK_DYNAMIC_TAPPING_TERM_PRINT │ QK_DYNAMIC_TAPPING_TERM_UP │   │   │
//    ├───┼───────────────┼──────┼──────┼──────┼─────────┤           ├───┼──────────────────────────────┼───────────────────────────────┼────────────────────────────┼───┼───┤
//    │   │               │      │      │      │         │           │   │                              │                               │                            │   │   │
//    └───┴───────────────┴──────┴──────┼──────┼─────────┼───┐   ┌───┼───┼──────────────────────────────┼───────────────────────────────┴────────────────────────────┴───┴───┘
//                                      │      │         │   │   │   │   │                              │
//                                      └──────┴─────────┴───┘   └───┴───┴──────────────────────────────┘
  KC_TRANSPARENT , KC_TRANSPARENT   , KC_TRANSPARENT      , KC_TRANSPARENT      , KC_TRANSPARENT      , KC_TRANSPARENT , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT               , KC_TRANSPARENT                , KC_TRANSPARENT             , KC_TRANSPARENT , KC_TRANSPARENT,
  KC_TRANSPARENT , LGUI(LCTL(KC_Q)) , KC_AUDIO_VOL_DOWN   , KC_AUDIO_MUTE       , KC_AUDIO_VOL_UP     , QK_BOOT        , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT , RGB_HUD                      , RGB_TOG                       , RGB_HUI                    , KC_TRANSPARENT , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_TRANSPARENT   , KC_MEDIA_PREV_TRACK , KC_MEDIA_PLAY_PAUSE , KC_MEDIA_NEXT_TRACK , MEH(KC_K)      , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT , LGUI(KC_MINUS)               , LGUI(KC_0)                    , LGUI(KC_EQUAL)             , KC_TRANSPARENT , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_TRANSPARENT   , KC_TRANSPARENT      , KC_TRANSPARENT      , KC_TRANSPARENT      , KC_TRANSPARENT ,                                       KC_TRANSPARENT , QK_DYNAMIC_TAPPING_TERM_DOWN , QK_DYNAMIC_TAPPING_TERM_PRINT , QK_DYNAMIC_TAPPING_TERM_UP , KC_TRANSPARENT , KC_TRANSPARENT,
  KC_TRANSPARENT , KC_TRANSPARENT   , KC_TRANSPARENT      , KC_TRANSPARENT      , KC_TRANSPARENT      , KC_TRANSPARENT ,                                       KC_TRANSPARENT , KC_TRANSPARENT               , KC_TRANSPARENT                , KC_TRANSPARENT             , KC_TRANSPARENT , KC_TRANSPARENT,
                                                                                  KC_TRANSPARENT      , KC_TRANSPARENT , KC_TRANSPARENT ,     KC_TRANSPARENT , KC_TRANSPARENT , KC_TRANSPARENT
)
};

// COMBOS
// ============================================================================
const uint16_t PROGMEM LY_BAS_CMB_BACKSPACE[]     = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM LY_BAS_CMB_BRACKET_LEFT[]  = {KC_J, LT(LY_SYM, KC_K), COMBO_END};
const uint16_t PROGMEM LY_BAS_CMB_BRACKET_RIGHT[] = {LT(LY_SYM, KC_K), KC_L, COMBO_END};

const uint16_t PROGMEM LY_NUM_CMB_BACKSPACE[]     = {KC_8, KC_9, COMBO_END};
const uint16_t PROGMEM LY_NUM_CMB_DOT[]     = {KC_2, KC_3, COMBO_END};
const uint16_t PROGMEM LY_NUM_CMB_COMMA[]     = {KC_1, KC_2, COMBO_END};

combo_t key_combos[] = {
    COMBO(LY_BAS_CMB_BACKSPACE, KC_BSPC),
    COMBO(LY_BAS_CMB_BRACKET_LEFT, KC_LBRC),
    COMBO(LY_BAS_CMB_BRACKET_RIGHT, KC_RBRC),

    COMBO(LY_NUM_CMB_BACKSPACE, KC_BSPC),
    COMBO(LY_NUM_CMB_DOT, KC_DOT),
    COMBO(LY_NUM_CMB_COMMA, KC_COMMA)
};

void matrix_scan_user(void) {
    achordion_task();
}

// https://getreuer.info/posts/keyboards/achordion/index.html
bool achordion_chord(
        uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record,
        uint16_t other_keycode, keyrecord_t *other_record
) {
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

    case SS_FATARROW:
      if (record->event.pressed) {
        SEND_STRING("=>");
      }
      break;
    }

    return true;
}

  // TAP DANCE
  // ============================================================================
  enum tab_dance_events {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    MORE_TAPS
  };

  uint8_t dance_step(tap_dance_state_t * state) {
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

  void on_td_ext_gui_a(tap_dance_state_t * state, void *user_data) {
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

  void reset_td_ext_gui_a(tap_dance_state_t * state, void *user_data) {
    unregister_code(KC_LGUI);
  }

  void on_td_ext_gui_s(tap_dance_state_t * state, void *user_data) {
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

  void reset_td_ext_gui_s(tap_dance_state_t * state, void *user_data) {
    unregister_code(KC_LALT);
  }

  void on_td_ext_gui_d(tap_dance_state_t * state, void *user_data) {
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

  void reset_td_ext_gui_d(tap_dance_state_t * state, void *user_data) {
    unregister_code(KC_LCTL);
  }

  void on_td_ext_gui_f(tap_dance_state_t * state, void *user_data) {
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

  void reset_td_ext_gui_f(tap_dance_state_t * state, void *user_data) {
    unregister_code(KC_LSFT);
  }

tap_dance_action_t tap_dance_actions[] = {
    [TD_EXT_GUI_A] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_td_ext_gui_a, reset_td_ext_gui_a),
    [TD_EXT_GUI_S] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_td_ext_gui_s, reset_td_ext_gui_s),
    [TD_EXT_GUI_D] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_td_ext_gui_d, reset_td_ext_gui_d),
    [TD_EXT_GUI_F] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, on_td_ext_gui_f, reset_td_ext_gui_f),
};
