#!/usr/bin/env bash

# Exit on any error
set -e

# Get the directory of this script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Source utilities
source "$SCRIPT_DIR/utils.sh"

# Get repo path from config
KOYO_REPO=$(eval echo "$(get_config '.paths.repo_dir')")
KOYO_ASSETS_DIR=$KOYO_REPO/assets

KD_CONFIG_PATH=$KOYO_ASSETS_DIR/kd_config.yaml
KD_LAYOUT_PATH=$KOYO_ASSETS_DIR/kd_layout.yaml
LAYOUT_SVG_PATH=$KOYO_ASSETS_DIR/layout.svg

if ! keymap --config "$KD_CONFIG_PATH" draw "$KD_LAYOUT_PATH" > "$LAYOUT_SVG_PATH"; then
    error_log "Failed to generate SVG layout"
    exit 1
fi

success_log "SVG layout updated successfully"
