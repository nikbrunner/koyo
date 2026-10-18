#!/usr/bin/env bash

# Exit on any error
set -euo pipefail

# Get the directory of this script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Source utilities
source "$SCRIPT_DIR/utils.sh"

KEYMAP_PATH=$SCRIPT_DIR/keymap.yml
KD_CONFIG_PATH=$SCRIPT_DIR/assets/kd_config.yaml
LAYOUT_SVG_PATH=$SCRIPT_DIR/assets/layout.svg

WORK_DIR=$(mktemp -d)
trap 'rm -rf "$WORK_DIR"' EXIT

if ! yq -o=json "$KEYMAP_PATH" | python3 -I "$SCRIPT_DIR/generate_keymap.py" "$SCRIPT_DIR" "$WORK_DIR"; then
    error_log "Failed to generate from keymap.yml"
    exit 1
fi
success_log "Board keymaps generated"

LAYER_NAMES=()
while IFS= read -r name; do
    LAYER_NAMES+=("$name")
done < "$WORK_DIR/layer_names.txt"

if ! keymap --config "$KD_CONFIG_PATH" parse -q "$WORK_DIR/keymap.json" -l "${LAYER_NAMES[@]}" -o "$WORK_DIR/drawing.yaml" ||
    ! yq -o=json '.layers.COMBO_LABELS' "$WORK_DIR/drawing.yaml" | python3 -I "$SCRIPT_DIR/generate_keymap.py" combos "$WORK_DIR" ||
    ! yq -i 'del(.layers.COMBO_LABELS) | .combos = load("'"$WORK_DIR"'/drawing_combos.json")' "$WORK_DIR/drawing.yaml" ||
    ! keymap --config "$KD_CONFIG_PATH" draw "$WORK_DIR/drawing.yaml" > "$LAYOUT_SVG_PATH"; then
    error_log "Failed to generate SVG layout"
    exit 1
fi
success_log "SVG layout updated successfully"
