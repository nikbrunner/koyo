#!/bin/bash

set -euo pipefail

# Flags
DRY_RUN=${DRY_RUN:-false}

# Paths
QMK_DIR=~/repos/nikbrunner/qmk_firmware
REPO_DIR=~/repos/nikbrunner/koyo
SCRIPT_FILES=(
    "./koyo"
    "./qmk/moonlander/flash.sh"
    "./qmk/crkbd/flash.sh"
)

debug_log() {
    echo -e "${BLUE}DRY-RUN:${NC} $1"
}

prompt_log() {
    echo -e "${CYAN}$1${NC}"
}

warning_log() {
    echo -e "${YELLOW}$1${NC}"
}

success_log() {
    echo -e "${GREEN}$1${NC}"
}

check_qmk() {
    debug_log "Checking QMK installation..."
    if [[ ! -d "$QMK_DIR" ]]; then
        debug_log "Warning: QMK firmware not found at $QMK_DIR"

        if [[ "$DRY_RUN" == "true" ]]; then
            debug_log "Would prompt to clone QMK firmware"
            return
        fi

        prompt_log "Would you like to clone it now? (y/n)"
        read -r response

        if [[ "$response" =~ ^[Yy]$ ]]; then
            git clone https://github.com/qmk/qmk_firmware.git "$QMK_DIR"
            success_log "QMK firmware cloned successfully"
        else
            warning_log "Please clone QMK firmware manually before flashing"
            exit 1
        fi
    else
        success_log "QMK firmware found"
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
                success_log "Made $script executable"
            fi
        else
            warning_log "$script not found"
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
            success_log "Removed existing symlink"
        fi
    fi

    if [[ "$DRY_RUN" == "true" ]]; then
        debug_log "Would create symlink: $REPO_DIR/koyo -> /usr/local/bin/koyo"
    else
        sudo ln -s "$REPO_DIR/koyo" "/usr/local/bin/koyo"
        success_log "Created symlink for koyo command"
    fi
}

check_zsh() {
    debug_log "Checking ZSH configuration..."
    if [[ ! -f ~/.zshrc ]]; then
        error_log "Error: ~/.zshrc not found"
        exit 1
    fi
    success_log "ZSH configuration found"
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
        warning_log "Running in dry-run mode - no changes will be made"
    fi

    debug_log "Starting Koyo keyboard setup..."

    check_zsh
    check_qmk
    setup_permissions
    setup_symlink

    if [[ "$DRY_RUN" == "true" ]]; then
        # echo -e "\n${YELLOW}Dry run completed - no changes were made${NC}"
        success_log "Dry run completed - no changes were made"
    else
        success_log "Setup completed successfully!"
    fi
    success_log "You can now use the 'koyo' command."
}

main
