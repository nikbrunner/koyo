#!/usr/bin/env bash

KOYO_REPO=~/repos/nikbrunner/koyo
KOYO_ASSETS_DIR=$KOYO_REPO/assets

KEYMAP_NAME="${KOYO_REPO}/qmk/crkbd/src/keymap.c"
KD_CONFIG_PATH=$KOYO_ASSETS_DIR/kd_config.yaml
KD_LAYOUT_PATH=$KOYO_ASSETS_DIR/kd_layout.yaml
LAYOUT_SVG_PATH=$KOYO_ASSETS_DIR/layout.svg

# Function to update keymap yaml from keymap.c
update_layout_yaml() {
    echo "Updating layout to YAML..."
    qmk c2json --no-cpp "${KEYMAP_NAME}" | keymap --config "${KD_CONFIG_PATH}" parse -q - >"${KD_LAYOUT_PATH}"
}

# Function to generate layout.svg from layout yaml
update_svg_layout() {
    echo "Updating SVG layout..."
    keymap --config "${KD_CONFIG_PATH}" draw "${KD_LAYOUT_PATH}" >"${LAYOUT_SVG_PATH}"
}

update_layout_yaml
update_svg_layout

if [[ $(git -C "${KOYO_REPO}" diff --exit-code) ]]; then
    echo "Update complete. Changes detected. 🧑‍🔧"
    # Create commit with changes
    git -C "${KOYO_REPO}" add .
    git -C "${KOYO_REPO}" commit -m "chore: update layout.svg"
    git -C "${KOYO_REPO}" push --force-with-lease
else
    echo "No changes detected. ✅"
fi
