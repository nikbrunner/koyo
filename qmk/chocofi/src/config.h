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

// Enable per-key permissive hold via get_permissive_hold()
// https://docs.qmk.fm/tap_hold#permissive-hold
#define PERMISSIVE_HOLD_PER_KEY

// Enable per-key hold on other key press via get_hold_on_other_key_press()
// https://docs.qmk.fm/tap_hold#hold-on-other-key-press
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// Window after a typed letter in which a tap-hold key settles as tapped (ms)
// https://docs.qmk.fm/tap_hold#flow-tap
#define FLOW_TAP_TERM 150

// =============================================================================
// Combo Configuration
// https://docs.qmk.fm/features/combo
// =============================================================================

// Time window for combo key presses (ms)
#define COMBO_TERM 35

// =============================================================================
// RGB Configuration
// =============================================================================

// The right half reads the active layer to pick its key highlights
#define SPLIT_LAYER_STATE_ENABLE
