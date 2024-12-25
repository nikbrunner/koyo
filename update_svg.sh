#!/usr/bin/env bash

# Exit on any error
set -e

KOYO_REPO=~/repos/nikbrunner/koyo
KOYO_ASSETS_DIR=$KOYO_REPO/assets

KEYMAP_NAME="${KOYO_REPO}/qmk/crkbd/src/keymap.c"
KD_CONFIG_PATH=$KOYO_ASSETS_DIR/kd_config.yaml
KD_LAYOUT_PATH=$KOYO_ASSETS_DIR/kd_layout.yaml
LAYOUT_SVG_PATH=$KOYO_ASSETS_DIR/layout.svg

# Function to check if required files exist
check_prerequisites() {
    local missing_files=()
    
    [[ ! -f "${KEYMAP_NAME}" ]] && missing_files+=("${KEYMAP_NAME}")
    [[ ! -f "${KD_CONFIG_PATH}" ]] && missing_files+=("${KD_CONFIG_PATH}")
    
    if [[ ${#missing_files[@]} -gt 0 ]]; then
        echo "Error: Required files not found:"
        printf '%s\n' "${missing_files[@]}"
        exit 1
    fi
}

# Function to update keymap yaml from keymap.c
update_layout_yaml() {
    echo "Updating layout to YAML..."
    if ! qmk c2json --no-cpp "${KEYMAP_NAME}" | keymap --config "${KD_CONFIG_PATH}" parse -q - >"${KD_LAYOUT_PATH}"; then
        echo "Error: Failed to update layout YAML"
        exit 1
    fi
}

# Function to generate layout.svg from layout yaml
update_svg_layout() {
    echo "Updating SVG layout..."
    if ! keymap --config "${KD_CONFIG_PATH}" draw "${KD_LAYOUT_PATH}" >"${LAYOUT_SVG_PATH}"; then
        echo "Error: Failed to generate SVG layout"
        exit 1
    fi
}

# Main execution
check_prerequisites

update_layout_yaml
update_svg_layout

if [[ $(git -C "${KOYO_REPO}" diff --exit-code) ]]; then
    echo "Update complete. Changes detected. 🧑‍🔧"
    # Create commit with changes
    if ! git -C "${KOYO_REPO}" add .; then
        echo "Error: Failed to stage changes"
        exit 1
    fi
    
    if ! git -C "${KOYO_REPO}" commit -m "chore: update layout.svg"; then
        echo "Error: Failed to commit changes"
        exit 1
    fi
    
    if ! git -C "${KOYO_REPO}" push --force-with-lease; then
        echo "Error: Failed to push changes"
        exit 1
    fi
else
    echo "No changes detected. ✅"
fi
