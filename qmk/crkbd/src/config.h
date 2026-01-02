#pragma once

// =============================================================================
// Split Keyboard Configuration
// =============================================================================

#define MASTER_LEFT

// =============================================================================
// Tap-Hold Configuration
// https://docs.qmk.fm/tap_hold
// =============================================================================

// Base timeout for tap vs hold decision (ms)
// https://docs.qmk.fm/tap_hold#tapping-term
#define TAPPING_TERM 165

// Enable per-key tapping term customization via get_tapping_term()
// https://docs.qmk.fm/tap_hold#tapping-term
#define TAPPING_TERM_PER_KEY

// Opposite hands rule - same-hand chords tap, cross-hand chords can hold
// https://docs.qmk.fm/tap_hold#chordal-hold
#define CHORDAL_HOLD

// Apply modifier immediately on keydown for responsive Shift+Click, Ctrl+Click
// https://docs.qmk.fm/tap_hold#speculative-hold
#define SPECULATIVE_HOLD

// =============================================================================
// Combo Configuration
// https://docs.qmk.fm/features/combo
// =============================================================================

// Time window for combo key presses (ms)
#define COMBO_TERM 35

// =============================================================================
// RGB Configuration
// =============================================================================

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif
