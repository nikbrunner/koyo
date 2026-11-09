#undef TAPPING_TERM

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
#define FLOW_TAP_TERM 80

// =============================================================================
// Combo Configuration
// https://docs.qmk.fm/features/combo
// =============================================================================

// Time window for combo key presses (ms)
#define COMBO_TERM 35

// Enable combo_should_trigger() to limit combos to their layer
#define COMBO_SHOULD_TRIGGER

// =============================================================================
// Layer Configuration
// =============================================================================

// Use 8-bit layer state to save memory (max 8 layers)
// https://docs.qmk.fm/squeezing_avr#layers
#define LAYER_STATE_8BIT

// =============================================================================
// RGB Configuration
// =============================================================================

#define RGB_MATRIX_STARTUP_SPD 60

// =============================================================================
// USB Configuration
// =============================================================================

#define USB_SUSPEND_WAKEUP_DELAY 0
