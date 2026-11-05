#!/bin/bash

# Build and flash one board. Usage: flash.sh <voyager|moonlander|crkbd|chocofi>

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

source "$PROJECT_DIR/utils.sh"

set -euo pipefail

BOARD=${1:?Usage: flash.sh <board>}
DEBUG=${DEBUG:-false}

QMK_DIR=$(eval echo "$(get_config '.paths.qmk_dir')")
KEYMAP_PATH=$(get_config ".paths.keymap_dirs.$BOARD")
if [[ "$KEYMAP_PATH" == "null" ]]; then
    error_log "No keymap directory configured for $BOARD"
    exit 1
fi
KEYMAP_DIR="$QMK_DIR/$KEYMAP_PATH"
KEYBOARD=${KEYMAP_PATH#keyboards/}
KEYBOARD=${KEYBOARD%/keymaps/*}
KEYMAP=${KEYMAP_PATH##*/}

if [[ "$DEBUG" == "true" ]]; then
    debug_log "QMK_DIR: $QMK_DIR"
    debug_log "KEYMAP_DIR: $KEYMAP_DIR"
    debug_log "KEYBOARD: $KEYBOARD"
    debug_log "KEYMAP: $KEYMAP"
fi

remove_link() {
    if [[ -L "$KEYMAP_DIR" ]]; then
        rm "$KEYMAP_DIR"
    elif [[ -e "$KEYMAP_DIR" ]]; then
        error_log "$KEYMAP_DIR is not a link: move it away, then flash again"
        return 1
    fi
}

wait_for_rp2040() {
    local volume=$1 file=$2 timeout=30 elapsed=0

    warning_log "Put the Chocofi into bootloader mode (double-tap reset button)"
    echo -e "Waiting for RP2040 drive to mount at ${CYAN}$volume${NC}..."

    while [[ ! -d "$volume" ]]; do
        sleep 1
        elapsed=$((elapsed + 1))
        if [[ $elapsed -ge $timeout ]]; then
            error_log "Timeout: RP2040 drive not detected after ${timeout}s"
            error_log "The .uf2 file is at: $file"
            error_log "You can manually copy it to the RP2040 drive."
            return 1
        fi
    done

    success_log "RP2040 drive detected!"
}

# The Chocofi builds as a Corne on an RP2040 and flashes by copying to its USB drive
flash_chocofi() {
    local file="$QMK_DIR/.build/crkbd_rev1_${KEYMAP}_rp2040_ce.uf2"
    local volume="/Volumes/RPI-RP2"

    if ! qmk compile -kb "$KEYBOARD" -km "$KEYMAP" -e CONVERT_TO=rp2040_ce; then
        error_log "Failed to compile firmware"
        exit 1
    fi
    success_log "Firmware compiled: $file"

    wait_for_rp2040 "$volume" "$file" || exit 1

    echo "Copying firmware to RP2040 drive..."
    if ! cp "$file" "$volume/"; then
        error_log "Failed to copy firmware to RP2040 drive"
        error_log "You can manually copy: $file"
        exit 1
    fi
}

main() {
    if [[ ! -d "$QMK_DIR" ]]; then
        error_log "QMK directory not found at $QMK_DIR: run koyo setup"
        exit 1
    fi

    # Regenerate board keymaps and the layout SVG from keymap.yml
    "$PROJECT_DIR/update_keymap.sh"

    remove_link
    mkdir -p "$(dirname "$KEYMAP_DIR")"
    ln -s "$SCRIPT_DIR/$BOARD/src" "$KEYMAP_DIR"
    trap remove_link EXIT

    cd "$QMK_DIR"

    echo "Compiling and flashing firmware..."
    if [[ "$BOARD" == "chocofi" ]]; then
        flash_chocofi
    elif ! qmk flash -kb "$KEYBOARD" -km "$KEYMAP"; then
        error_log "Failed to compile/flash firmware"
        exit 1
    fi

    success_log "Successfully flashed firmware!"
}

main
