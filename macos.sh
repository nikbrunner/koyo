#!/usr/bin/env bash

# Apply the macOS keyboard settings the layout relies on.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/utils.sh"

ACTIVATE_SETTINGS=/System/Library/PrivateFrameworks/SystemAdministration.framework/Resources/activateSettings

defaults write -g com.apple.keyboard.fnState -bool true
defaults write -g KeyRepeat -int 2
defaults write -g InitialKeyRepeat -int 15
defaults write -g ApplePressAndHoldEnabled -bool false

# System shortcuts kept off for Karabiner and the layout, by symbolic hotkey ID:
# zoom and contrast (15-26), screenshots (28-31, 184), Mission Control (32-34),
# show desktop (36), input source (60, 61), Spaces (79-82, 118), 164 has no key
for id in 15 16 17 18 19 20 21 22 23 24 25 26 28 29 30 31 32 33 34 36 60 61 79 80 81 82 118 164 184; do
    defaults write com.apple.symbolichotkeys AppleSymbolicHotKeys -dict-add "$id" '<dict><key>enabled</key><false/></dict>'
done

"$ACTIVATE_SETTINGS" -u || warning_log "Could not apply the settings right away"
success_log "macOS keyboard settings written. Log out and back in so every app picks them up."
