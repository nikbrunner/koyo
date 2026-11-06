#pragma once

// Tap-hold and combo behaviour of every board. A board with a gaming layer defines
// GAMING_LAYER before including this file.

// TAPPING TERM ============================================================================
// g_tapping_term, not TAPPING_TERM: the DT_* keys change it at runtime
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LGUI, KC_Z):
        case MT(MOD_LALT, KC_X):
        case MT(MOD_LALT, KC_DOT):
        case MT(MOD_RGUI, KC_SLASH):
            return g_tapping_term + 15;

        default:
            return g_tapping_term;
    }
}

#ifdef COMBO_SHOULD_TRIGGER
// The number row on base shares its keycodes with these combos, which belong to LY_NUM_FN only
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if (combo->keys == LY_NUM_FN_CMB_COMMA || combo->keys == LY_NUM_FN_CMB_DOT) {
        return layer_state_is(LY_NUM_FN);
    }
#    ifdef GAMING_LAYER
    return !layer_state_is(GAMING_LAYER);
#    else
    return true;
#    endif
}
#endif

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
#ifdef GAMING_LAYER
        // Binds under this thumb must fire at once in a game, while typing keeps fast Esc rolls
        case LT(LY_NUM_FN, KC_ESC):
            return layer_state_is(GAMING_LAYER);
#endif
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
        case MT(MOD_LCTL, KC_C):
            // Repeated Ctrl+HJKL presses Ctrl again right after the previous H, J, K or L
            switch (prev_keycode) {
                case KC_H:
                case KC_J:
                case LT(LY_SYM, KC_K):
                case KC_L:
                    return 0;
            }
            return is_flow_tap_key(prev_keycode) ? FLOW_TAP_TERM : 0;
        case MT(MOD_LGUI, KC_Z):
        case MT(MOD_LALT, KC_X):
        case MT(MOD_RCTL, KC_COMMA):
        case MT(MOD_LALT, KC_DOT):
        case MT(MOD_RGUI, KC_SLASH):
            return is_flow_tap_key(prev_keycode) ? FLOW_TAP_TERM : 0;
        default:
            return 0;
    }
}
