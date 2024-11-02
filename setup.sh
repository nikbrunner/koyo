#!/bin/bash

set -euo pipefail

# Flags
DRY_RUN=${DRY_RUN:-false}

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Paths
QMK_DIR=~/repos/nikbrunner/qmk_firmware
REPO_DIR=~/repos/nikbrunner/koyo
SCRIPT_FILES=(
    "./koyo"
    "./qmk/moonlander/flash.sh"
    "./qmk/crkbd/flash.sh"
)

debug_log() {
    if [[ "$DRY_RUN" == "true" ]]; then
        echo -e "${YELLOW}DRY-RUN:${NC} $1"
    else
        echo "$1"
    fi
}

check_qmk() {
    debug_log "Checking QMK installation..."
    if [[ ! -d "$QMK_DIR" ]]; then
        echo -e "${YELLOW}Warning: QMK firmware not found at $QMK_DIR${NC}"
        if [[ "$DRY_RUN" == "true" ]]; then
            debug_log "Would prompt to clone QMK firmware"
            return
        fi
        echo "Would you like to clone it now? (y/n)"
        read -r response
        if [[ "$response" =~ ^[Yy]$ ]]; then
            git clone https://github.com/qmk/qmk_firmware.git "$QMK_DIR"
            echo -e "${GREEN}QMK firmware cloned successfully${NC}"
        else
            echo -e "${YELLOW}Please clone QMK firmware manually before flashing${NC}"
        fi
    else
        echo -e "${GREEN}QMK firmware found${NC}"
    fi
}

setup_permissions() {
    debug_log "Setting up script permissions..."
    for script in "${SCRIPT_FILES[@]}"; do
        if [[ -f "$script" ]]; then
            if [[ "$DRY_RUN" == "true" ]]; then
                debug_log "Would make $script executable"
            else
                chmod +x "$script"
                echo -e "${GREEN}Made $script executable${NC}"
            fi
        else
            echo -e "${RED}Warning: $script not found${NC}"
        fi
    done
}

setup_symlink() {
    debug_log "Setting up command symlink..."
    if [[ -L "/usr/local/bin/koyo" ]]; then
        if [[ "$DRY_RUN" == "true" ]]; then
            debug_log "Would remove existing symlink"
        else
            sudo rm "/usr/local/bin/koyo"
            echo "Removed existing symlink"
        fi
    fi
    if [[ "$DRY_RUN" == "true" ]]; then
        debug_log "Would create symlink: $REPO_DIR/koyo -> /usr/local/bin/koyo"
    else
        sudo ln -s "$REPO_DIR/koyo" "/usr/local/bin/koyo"
        echo -e "${GREEN}Created symlink for koyo command${NC}"
    fi
}

check_zsh() {
    debug_log "Checking ZSH configuration..."
    if [[ ! -f ~/.zshrc ]]; then
        echo -e "${RED}Error: ~/.zshrc not found${NC}"
        exit 1
    fi
    echo -e "${GREEN}ZSH configuration found${NC}"
}

show_help() {
    echo "Usage: ./setup.sh [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  --dry-run    Show what would be done without making changes"
    echo "  --help       Show this help message"
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
    --dry-run)
        DRY_RUN=true
        shift
        ;;
    --help)
        show_help
        exit 0
        ;;
    *)
        echo "Unknown option: $1"
        show_help
        exit 1
        ;;
    esac
done

main() {
    if [[ "$DRY_RUN" == "true" ]]; then
        echo -e "${YELLOW}Running in dry-run mode - no changes will be made${NC}"
    fi

    echo "Starting Koyo keyboard setup..."

    # Run checks
    check_zsh
    check_qmk
    setup_permissions
    setup_symlink

    if [[ "$DRY_RUN" == "true" ]]; then
        echo -e "\n${YELLOW}Dry run completed - no changes were made${NC}"
    else
        echo -e "\n${GREEN}Setup completed successfully!${NC}"
    fi
    echo "You can now use the 'koyo' command."
}

main
