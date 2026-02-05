#!/bin/bash

# Get the directory of this script and the project root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"

# Source utilities using absolute path
source "$PROJECT_DIR/utils.sh"

# Enable strict mode
set -euo pipefail

# Get paths from config
QMK_DIR=$(eval echo "$(get_config '.paths.qmk_dir')")
# Combine QMK_DIR with the keymap path
KEYMAP_DIR="$QMK_DIR/$(get_config '.paths.keymap_dirs.moonlander')"

# Create the keymap directory if it doesn't exist
mkdir -p "$(dirname "$KEYMAP_DIR")"

if [[ "$DEBUG" == "true" ]]; then
    debug_log "Paths:"
    debug_log "  SCRIPT_DIR: $SCRIPT_DIR"
    debug_log "  PROJECT_DIR: $PROJECT_DIR"
    debug_log "  QMK_DIR: $QMK_DIR"
    debug_log "  KEYMAP_DIR: $KEYMAP_DIR"
fi

verify_files() {
    local dir=$1
    local files=("config.h" "keymap.c" "rules.mk")

    for file in "${files[@]}"; do
        if [[ ! -f "$dir/$file" ]]; then
            error_log "Required file $file not found in $dir"
            return 1
        else
            success_log "Found $file in $dir"
        fi
    done

}

cleanup() {
    debug_log "Cleaning up..."

    if [[ -e "$KEYMAP_DIR" ]]; then
        rm -rf "$KEYMAP_DIR"
        success_log "Removed existing keymap directory"
    fi
}

debug_log "Script directory: $SCRIPT_DIR"
debug_log "QMK directory: $QMK_DIR"
debug_log "Keymap directory: $KEYMAP_DIR"

# Ensure cleanup happens on script exit
trap cleanup EXIT

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
    if ! qmk flash -kb zsa/moonlander -km koyo; then
        error_log "Failed to compile/flash firmware"
        exit 1
    fi

    success_log "Successfully flashed firmware!"
}

main
