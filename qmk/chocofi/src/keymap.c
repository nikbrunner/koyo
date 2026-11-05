#include QMK_KEYBOARD_H

#define EXT_A MT(MOD_LGUI, KC_A)
#define EXT_S MT(MOD_LALT, KC_S)
#define EXT_D MT(MOD_LCTL, KC_D)
#define EXT_F MT(MOD_LSFT, KC_F)

#include "keymap.generated.h"

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

// Chordal Hold implementation
bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                     uint16_t other_keycode, keyrecord_t* other_record) {
    // Define which keys should always hold when chorded
    switch (tap_hold_keycode) {
        // Left hand
        case LT(LY_NUM_FN, KC_ESC):
        case LT(LY_EXT, KC_SPC):
        case EXT_A:
        case EXT_S:
        case EXT_D:
        case EXT_F:

        // Right hand
        case HYPR_T(KC_ENT):
        case LT(LY_MED, KC_BSPC):
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

// EXT HOME ROW ============================================================================
// Tapped: GUI + the letter. Held: the key's modifier.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case EXT_A:
        case EXT_S:
        case EXT_D:
        case EXT_F:
            if (record->tap.count && record->event.pressed) {
                tap_code16(G(QK_MOD_TAP_GET_TAP_KEYCODE(keycode)));
                return false;
            }
            break;
    }
    return true;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case EXT_A:
        case EXT_S:
        case EXT_D:
        case EXT_F:
            return true;
        default:
            return false;
    }
}

bool get_speculative_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Mostly tapped, so speculating would flash Ctrl or Shift before each GUI shortcut
        case EXT_D:
        case EXT_F:
            return false;
    }
    const uint8_t mods = mod_config(QK_MOD_TAP_GET_MODS(keycode));
    return (mods & (MOD_LCTL | MOD_LSFT)) == (mods & MOD_HYPR);
}

// A key tapped while the EXT thumb is down settles the thumb as held
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    return keycode == LT(LY_EXT, KC_SPC);
}

// Shift and SYM keys stay out: camelCase and symbols need a hold right after a letter
uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    switch (keycode) {
        case MT(MOD_LGUI, KC_Z):
        case MT(MOD_LALT, KC_X):
        case MT(MOD_LCTL, KC_C):
        case MT(MOD_RCTL, KC_COMMA):
        case MT(MOD_LALT, KC_DOT):
        case MT(MOD_RGUI, KC_SLASH):
            return is_flow_tap_key(prev_keycode) ? FLOW_TAP_TERM : 0;
        default:
            return 0;
    }
}
