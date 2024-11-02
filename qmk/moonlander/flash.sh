#!/bin/bash

# Enable strict mode
set -euo pipefail

# Functions
debug_log() {
    if [[ "${DEBUG:-false}" == "true" ]]; then
        echo "DEBUG: $1"
    fi
}

error_log() {
    echo "ERROR: $1" >&2
}

verify_files() {
    local dir=$1
    local files=("config.h" "keymap.c" "rules.mk")

    for file in "${files[@]}"; do
        if [[ ! -f "$dir/$file" ]]; then
            error_log "Required file $file not found in $dir"
            return 1
        fi
    done
}

cleanup() {
    debug_log "Cleaning up..."
    if [[ -e "$KEYMAP_DIR" ]]; then
        rm -rf "$KEYMAP_DIR"
    fi
}

# Set up paths
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
QMK_DIR=~/repos/nikbrunner/qmk_firmware
KEYMAP_DIR="$QMK_DIR/keyboards/zsa/moonlander/keymaps/koyo"

# Enable debug logging if needed
# DEBUG=true ./flash.sh
debug_log "Script directory: $SCRIPT_DIR"
debug_log "QMK directory: $QMK_DIR"
debug_log "Keymap directory: $KEYMAP_DIR"

# Ensure cleanup happens on script exit
trap cleanup EXIT

# Main process
main() {
    # Verify QMK directory exists
    if [[ ! -d "$QMK_DIR" ]]; then
        error_log "QMK directory not found at $QMK_DIR"
        exit 1
    fi

    # Remove existing symlink if it exists
    cleanup

    # Create new symlink
    ln -s "$SCRIPT_DIR/src" "$KEYMAP_DIR"
    debug_log "Created symlink to keymap directory"

    # Verify required files exist
    if ! verify_files "$KEYMAP_DIR"; then
        exit 1
    fi

    # Change to QMK directory and compile/flash
    if ! cd "$QMK_DIR"; then
        error_log "Failed to change to QMK directory"
        exit 1
    fi

    echo "Compiling and flashing firmware..."
    if ! make zsa/moonlander:koyo:flash; then
        error_log "Failed to compile/flash firmware"
        exit 1
    fi

    echo "Successfully flashed firmware!"
}

# Run main function
main
