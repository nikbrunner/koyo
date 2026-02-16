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
KEYMAP_DIR="$QMK_DIR/$(get_config '.paths.keymap_dirs.chocofi')"

# RP2040 build output path
BUILD_DIR="$QMK_DIR/.build"
UF2_FILE="crkbd_rev1_koyo_chocofi_promicro_rp2040.uf2"

# Common RP2040 mount points on macOS
RP2040_VOLUME="/Volumes/RPI-RP2"

# Create the keymap directory if it doesn't exist
mkdir -p "$(dirname "$KEYMAP_DIR")"

if [[ "$DEBUG" == "true" ]]; then
    debug_log "Paths:"
    debug_log "  SCRIPT_DIR: $SCRIPT_DIR"
    debug_log "  PROJECT_DIR: $PROJECT_DIR"
    debug_log "  QMK_DIR: $QMK_DIR"
    debug_log "  KEYMAP_DIR: $KEYMAP_DIR"
    debug_log "  UF2_FILE: $UF2_FILE"
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

wait_for_rp2040() {
    local timeout=30
    local elapsed=0

    warn_log "Put the Chocofi into bootloader mode (double-tap reset button)"
    echo -e "Waiting for RP2040 drive to mount at ${CYAN}$RP2040_VOLUME${NC}..."

    while [[ ! -d "$RP2040_VOLUME" ]]; do
        sleep 1
        elapsed=$((elapsed + 1))
        if [[ $elapsed -ge $timeout ]]; then
            error_log "Timeout: RP2040 drive not detected after ${timeout}s"
            error_log "The .uf2 file is at: $BUILD_DIR/$UF2_FILE"
            error_log "You can manually copy it to the RP2040 drive."
            return 1
        fi
    done

    success_log "RP2040 drive detected!"
    return 0
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

    # Change to QMK directory and compile
    if ! cd "$QMK_DIR"; then
        error_log "Failed to change to QMK directory"
        exit 1
    fi

    echo "Compiling firmware..."
    if ! qmk compile -kb crkbd/rev1 -km koyo_chocofi -e CONVERT_TO=promicro_rp2040; then
        error_log "Failed to compile firmware"
        exit 1
    fi

    success_log "Firmware compiled: $BUILD_DIR/$UF2_FILE"

    # Wait for RP2040 drive and copy
    if wait_for_rp2040; then
        echo "Copying firmware to RP2040 drive..."
        if cp "$BUILD_DIR/$UF2_FILE" "$RP2040_VOLUME/"; then
            success_log "Successfully flashed firmware!"
        else
            error_log "Failed to copy firmware to RP2040 drive"
            error_log "You can manually copy: $BUILD_DIR/$UF2_FILE"
            exit 1
        fi
    fi
}

main
