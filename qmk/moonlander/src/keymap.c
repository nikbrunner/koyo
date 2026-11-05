#include QMK_KEYBOARD_H
#include "../../shared/aliases.h"
#include "keymap.generated.h"

#include "../../shared/hooks.h"

// Handedness of every key, for Chordal Hold
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_moonlander(
        'L', 'L', 'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'L',    'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',             'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',             'R', 'R', 'R', 'R', 'R', 'R',
                      'L', 'L', 'L',         'R', 'R', 'R'
    );
