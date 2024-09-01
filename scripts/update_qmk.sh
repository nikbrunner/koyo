#!/usr/bin/env bash

QMK_FIRMWARE_REPO=~/repos/nikbrunner/qmk_firmware
KOYO_REPO=~/repos/nikbrunner/koyo

CRKBD_KEYMAPS_DIR=$QMK_FIRMWARE_REPO/keyboards/crkbd/keymaps/koyo
KOYO_QMK_DIR=$KOYO_REPO/qmk
KOYO_ASSETS_DIR=$KOYO_REPO/assets

KEYMAP_NAME=keymap.c
KD_CONFIG_PATH=$KOYO_ASSETS_DIR/kd_config.yaml
KD_LAYOUT_PATH=$KOYO_ASSETS_DIR/kd_layout.yaml
LAYOUT_SVG_PATH=$KOYO_ASSETS_DIR/layout.svg

# Function to copy keymaps to koyo/qmk folder
copy_keymaps() {
    echo "Copying keymaps..."
    cp -r "${CRKBD_KEYMAPS_DIR}"/* "${KOYO_QMK_DIR}"
}

# Function to update keymap yaml from keymap.c
update_layout_yaml() {
    echo "Updating layout to YAML..."
    qmk c2json --no-cpp "${CRKBD_KEYMAPS_DIR}/${KEYMAP_NAME}" | keymap --config "${KD_CONFIG_PATH}" parse -q - >"${KD_LAYOUT_PATH}"
}

# Function to generate layout.svg from layout yaml
update_svg_layout() {
    echo "Updating SVG layout..."
    keymap --config "${KD_CONFIG_PATH}" draw "${KD_LAYOUT_PATH}" >"${LAYOUT_SVG_PATH}"
}

copy_keymaps
update_layout_yaml
update_svg_layout

if [[ $(git -C "${KOYO_REPO}" diff --exit-code) ]]; then
    echo "Update complete. Changes detected. 🧑‍🔧"
    lazygit
else
    echo "No changes detected. ✅"
fi
