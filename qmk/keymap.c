/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum custom_keycodes {
    SS_TILD_SLSH = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SS_TILD_SLSH:
            if (record->event.pressed) {
                SEND_STRING("~/");
            } else {
                // when keycode is released
            }
            break;
    }

    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌───────────┬───────────┬───────────┬────────────┬────────────┐   ┌─────────────┬────────────┬───────────┬───────────┬───────────┐
//    │     q     │     w     │     e     │     r      │     t      │   │      y      │     u      │     i     │     o     │     p     │
//    ├───────────┼───────────┼───────────┼────────────┼────────────┤   ├─────────────┼────────────┼───────────┼───────────┼───────────┤
//    │     a     │     s     │     d     │     f      │     g      │   │      h      │     j      │     k     │     l     │     ;     │
//    ├───────────┼───────────┼───────────┼────────────┼────────────┤   ├─────────────┼────────────┼───────────┼───────────┼───────────┤
//    │ LGUI_T(z) │ LALT_T(x) │ LCTL_T(c) │ LSFT_T(v)  │     b      │   │      n      │ RSFT_T(m)  │ RCTL_T(,) │ LALT_T(.) │ RGUI_T(/) │
//    └───────────┴───────────┼───────────┼────────────┼────────────┤   ├─────────────┼────────────┼───────────┼───────────┴───────────┘
//                            │ LT(3, no) │ LT(2, esc) │ LT(1, spc) │   │ LT(5, bspc) │ LT(2, ent) │ LT(4, no) │
//                            └───────────┴────────────┴────────────┘   └─────────────┴────────────┴───────────┘
[0] = LAYOUT_split_3x5_3(
  KC_Q         , KC_W         , KC_E         , KC_R          , KC_T          ,     KC_Y           , KC_U          , KC_I            , KC_O           , KC_P           ,
  KC_A         , KC_S         , KC_D         , KC_F          , KC_G          ,     KC_H           , KC_J          , KC_K            , KC_L           , KC_SCLN        ,
  LGUI_T(KC_Z) , LALT_T(KC_X) , LCTL_T(KC_C) , LSFT_T(KC_V)  , KC_B          ,     KC_N           , RSFT_T(KC_M)  , RCTL_T(KC_COMM) , LALT_T(KC_DOT) , RGUI_T(KC_SLSH),
                                LT(3, KC_NO) , LT(2, KC_ESC) , LT(1, KC_SPC) ,     LT(5, KC_BSPC) , LT(2, KC_ENT) , LT(4, KC_NO)
),

//    ┌─────────┬─────────┬─────────┬─────────┬─────────┐   ┌──────┬────────┬───────────┬───────────┬────┐
//    │ LGUI(q) │ LGUI(w) │ LGUI(e) │ LGUI(r) │ LGUI(t) │   │  no  │ LAG(i) │  LGUI(`)  │ LGUI(tab) │ no │
//    ├─────────┼─────────┼─────────┼─────────┼─────────┤   ├──────┼────────┼───────────┼───────────┼────┤
//    │  lgui   │  lalt   │  lctl   │  lsft   │   no    │   │ left │  down  │    up     │   rght    │ no │
//    ├─────────┼─────────┼─────────┼─────────┼─────────┤   ├──────┼────────┼───────────┼───────────┼────┤
//    │ LGUI(z) │ LGUI(x) │ LGUI(c) │ LGUI(v) │ LGUI(b) │   │  no  │   no   │ LSFT(tab) │    tab    │ no │
//    └─────────┴─────────┼─────────┼─────────┼─────────┤   ├──────┼────────┼───────────┼───────────┴────┘
//                        │   no    │   no    │  TO(0)  │   │ del  │   no   │    no     │
//                        └─────────┴─────────┴─────────┘   └──────┴────────┴───────────┘
[1] = LAYOUT_split_3x5_3(
  LGUI(KC_Q) , LGUI(KC_W) , LGUI(KC_E) , LGUI(KC_R) , LGUI(KC_T) ,     KC_NO   , LAG(KC_I) , LGUI(KC_GRV) , LGUI(KC_TAB) , KC_NO,
  KC_LGUI    , KC_LALT    , KC_LCTL    , KC_LSFT    , KC_NO      ,     KC_LEFT , KC_DOWN   , KC_UP        , KC_RGHT      , KC_NO,
  LGUI(KC_Z) , LGUI(KC_X) , LGUI(KC_C) , LGUI(KC_V) , LGUI(KC_B) ,     KC_NO   , KC_NO     , LSFT(KC_TAB) , KC_TAB       , KC_NO,
                            KC_NO      , KC_NO      , TO(0)      ,     KC_DEL  , KC_NO     , KC_NO
),

//    ┌───┬───┬─────┬───────┬──────────────┐   ┌─────┬───────┬─────┬───┬───┐
//    │ ^ │ + │  #  │   %   │      $       │   │  <  │   {   │  "  │ } │ > │
//    ├───┼───┼─────┼───────┼──────────────┤   ├─────┼───────┼─────┼───┼───┤
//    │ ! │ - │  &  │   ?   │      |       │   │  =  │   [   │  '  │ ] │ : │
//    ├───┼───┼─────┼───────┼──────────────┤   ├─────┼───────┼─────┼───┼───┤
//    │ ~ │ _ │  *  │   @   │ SS_TILD_SLSH │   │  \  │   (   │  `  │ ) │ / │
//    └───┴───┼─────┼───────┼──────────────┤   ├─────┼───────┼─────┼───┴───┘
//            │     │ TO(0) │              │   │     │ TO(0) │     │
//            └─────┴───────┴──────────────┘   └─────┴───────┴─────┘
[2] = LAYOUT_split_3x5_3(
  KC_CIRC , KC_PLUS , KC_HASH , KC_PERC , KC_DLR       ,     KC_LT   , KC_LCBR , KC_DQUO , KC_RCBR , KC_GT  ,
  KC_EXLM , KC_MINS , KC_AMPR , KC_QUES , KC_PIPE      ,     KC_EQL  , KC_LBRC , KC_QUOT , KC_RBRC , KC_COLN,
  KC_TILD , KC_UNDS , KC_ASTR , KC_AT   , SS_TILD_SLSH ,     KC_BSLS , KC_LPRN , KC_GRV  , KC_RPRN , KC_SLSH,
                      KC_TRNS , TO(0)   , KC_TRNS      ,     KC_TRNS , TO(0)   , KC_TRNS
),

//    ┌──────────┬─────────┬──────┬──────┬─────┐   ┌──────┬──────┬──────┬──────┬──────┐
//    │    no    │   no    │  no  │  no  │ no  │   │ kp_+ │ kp_7 │ kp_8 │ kp_9 │ kp_* │
//    ├──────────┼─────────┼──────┼──────┼─────┤   ├──────┼──────┼──────┼──────┼──────┤
//    │   lgui   │  lalt   │ lctl │ lsft │ no  │   │ kp_= │ kp_4 │ kp_5 │ kp_6 │  :   │
//    ├──────────┼─────────┼──────┼──────┼─────┤   ├──────┼──────┼──────┼──────┼──────┤
//    │ HYPR(no) │ MEH(no) │  no  │  no  │ no  │   │ kp_- │ kp_1 │ kp_2 │ kp_3 │ kp_/ │
//    └──────────┴─────────┼──────┼──────┼─────┤   ├──────┼──────┼──────┼──────┴──────┘
//                         │      │      │     │   │      │ kp_0 │      │
//                         └──────┴──────┴─────┘   └──────┴──────┴──────┘
[3] = LAYOUT_split_3x5_3(
  KC_NO       , KC_NO      , KC_NO   , KC_NO   , KC_NO   ,     KC_PPLS , KC_P7 , KC_P8   , KC_P9 , KC_PAST,
  KC_LGUI     , KC_LALT    , KC_LCTL , KC_LSFT , KC_NO   ,     KC_PEQL , KC_P4 , KC_P5   , KC_P6 , KC_COLN,
  HYPR(KC_NO) , MEH(KC_NO) , KC_NO   , KC_NO   , KC_NO   ,     KC_PMNS , KC_P1 , KC_P2   , KC_P3 , KC_PSLS,
                             KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_P0 , KC_TRNS
),

//    ┌────┬────┬────┬────┬─────┐   ┌────┬──────┬──────┬─────────┬──────────┐
//    │ no │ f7 │ f8 │ f9 │ f12 │   │ no │  no  │  no  │   no    │    no    │
//    ├────┼────┼────┼────┼─────┤   ├────┼──────┼──────┼─────────┼──────────┤
//    │ no │ f4 │ f5 │ f6 │ f11 │   │ no │ rsft │ rctl │  lalt   │   rgui   │
//    ├────┼────┼────┼────┼─────┤   ├────┼──────┼──────┼─────────┼──────────┤
//    │ no │ f1 │ f2 │ f3 │ f10 │   │ no │  no  │  no  │ MEH(no) │ HYPR(no) │
//    └────┴────┼────┼────┼─────┤   ├────┼──────┼──────┼─────────┴──────────┘
//              │ no │ no │ no  │   │ no │  no  │  no  │
//              └────┴────┴─────┘   └────┴──────┴──────┘
[4] = LAYOUT_split_3x5_3(
  KC_NO , KC_F7 , KC_F8 , KC_F9 , KC_F12 ,     KC_NO , KC_NO   , KC_NO   , KC_NO      , KC_NO      ,
  KC_NO , KC_F4 , KC_F5 , KC_F6 , KC_F11 ,     KC_NO , KC_RSFT , KC_RCTL , KC_LALT    , KC_RGUI    ,
  KC_NO , KC_F1 , KC_F2 , KC_F3 , KC_F10 ,     KC_NO , KC_NO   , KC_NO   , MEH(KC_NO) , HYPR(KC_NO),
                  KC_NO , KC_NO , KC_NO  ,     KC_NO , KC_NO   , KC_NO
),

//    ┌────┬──────┬──────┬──────┬────────┐   ┌────┬─────────┬─────────┬─────────┬────┐
//    │ no │ vold │ mute │ volu │   no   │   │ no │ RGB_HUD │ RGB_TOG │ RGB_HUI │ no │
//    ├────┼──────┼──────┼──────┼────────┤   ├────┼─────────┼─────────┼─────────┼────┤
//    │ no │ mprv │ mply │ mnxt │ MEH(k) │   │ no │ LGUI(-) │ LGUI(0) │ LGUI(=) │ no │
//    ├────┼──────┼──────┼──────┼────────┤   ├────┼─────────┼─────────┼─────────┼────┤
//    │ no │  no  │  no  │  no  │   no   │   │ no │ DT_DOWN │ DT_PRNT │  DT_UP  │ no │
//    └────┴──────┼──────┼──────┼────────┤   ├────┼─────────┼─────────┼─────────┴────┘
//                │  no  │  no  │   no   │   │ no │   no    │   no    │
//                └──────┴──────┴────────┘   └────┴─────────┴─────────┘
[5] = LAYOUT_split_3x5_3(
  KC_NO , KC_VOLD , KC_MUTE , KC_VOLU , KC_NO     ,     KC_NO , RGB_HUD       , RGB_TOG    , RGB_HUI      , KC_NO,
  KC_NO , KC_MPRV , KC_MPLY , KC_MNXT , MEH(KC_K) ,     KC_NO , LGUI(KC_MINS) , LGUI(KC_0) , LGUI(KC_EQL) , KC_NO,
  KC_NO , KC_NO   , KC_NO   , KC_NO   , KC_NO     ,     KC_NO , DT_DOWN       , DT_PRNT    , DT_UP        , KC_NO,
                    KC_NO   , KC_NO   , KC_NO     ,     KC_NO , KC_NO         , KC_NO
)
};

const uint16_t PROGMEM togg_layer_ext_combo[] = { LT(1, KC_SPC), LT(5, KC_BSPC), COMBO_END };
const uint16_t PROGMEM togg_layer_sym_combo[] = { LT(2, KC_ESC), LT(2, KC_ENT), COMBO_END };
const uint16_t PROGMEM togg_caps_word_combo[] = { LSFT_T(KC_V), RSFT_T(KC_M), COMBO_END };

combo_t key_combos[] = {
    COMBO(togg_layer_ext_combo, TO(1)),
    COMBO(togg_layer_sym_combo, TO(2)),
    COMBO(togg_caps_word_combo, CW_TOGG),
};

