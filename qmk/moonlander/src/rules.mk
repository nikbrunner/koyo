# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
AUDIO_ENABLE = no
MOUSEKEY_ENABLE = no
ORYX_ENABLE = yes
TAP_DANCE_ENABLE = yes
SPACE_CADET_ENABLE = no
CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes
DYNAMIC_TAPPING_TERM_ENABLE = yes

# https://getreuer.info/posts/keyboards/achordion/index.html
SRC += features/achordion.c
