#!/bin/bash

# Path to your QMK firmware directory
QMK_DIR=~/repos/nikbrunner/qmk_firmware
KEYMAP_DIR="$QMK_DIR/keyboards/zsa/moonlander/keymaps/koyo"

# Remove existing symlink or directory if it exists
rm -rf "$KEYMAP_DIR"

# Create symlink
ln -s "$(pwd)/src" "$KEYMAP_DIR"

# Change to QMK directory and compile/flash
cd "$QMK_DIR" || exit
make zsa/moonlander:koyo:flash

# Clean up: Remove the symlink after flashing
rm -rf "$KEYMAP_DIR"
