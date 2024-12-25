#!/bin/bash

# Get the directory of this script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Enable strict mode
set -euo pipefail

# Flags
DRY_RUN=${DRY_RUN:-false}
DEBUG=${DEBUG:-false}

# Source utilities using absolute path
source "$SCRIPT_DIR/utils.sh"

# Get paths from config with debug output
debug_log "Reading config from: $SCRIPT_DIR/config.yml"

# Before continuing reading from config, check for yq
check_yq() {
    debug_log "Checking yq installation..."

    if ! command -v yq &>/dev/null; then
        debug_log "Warning: yq not found"

        if [[ "$DRY_RUN" == "true" ]]; then
            debug_log "Would prompt to install yq"
            return
        fi

        prompt_log "Would you like to install yq now? (y/n)"
        read -r response

        if [[ "$response" =~ ^[Yy]$ ]]; then
            if command -v brew &>/dev/null; then
                brew install yq
                success_log "yq installed successfully via Homebrew"
            elif command -v apt-get &>/dev/null; then
                sudo apt-get update && sudo apt-get install -y yq
                success_log "yq installed successfully via apt"
            else
                error_log "No supported package manager found. Please install yq manually:"
                error_log "Homebrew: brew install yq"
                error_log "Apt: sudo apt-get install yq"
                exit 1
            fi
        else
            warning_log "Please install yq manually before continuing"
            exit 1
        fi
    else
        success_log "yq found"
    fi
}

check_keymap() {
    debug_log "Checking keymap-drawer installation..."

    if ! command -v keymap &>/dev/null; then
        debug_log "Warning: keymap-drawer not found"

        if [[ "$DRY_RUN" == "true" ]]; then
            debug_log "Would prompt to install keymap-drawer"
            return
        fi

        prompt_log "Would you like to install keymap-drawer now? (y/n)"
        read -r response

        if [[ "$response" =~ ^[Yy]$ ]]; then
            if command -v pip3 &>/dev/null; then
                pipx install keymap-drawer
                success_log "keymap-drawer installed successfully via pip3"
            else
                error_log "pipx not found. Please install pipx (`brew install pipx`) and then install keymap-drawer:"
                error_log "pipx install keymap-drawer"
                exit 1
            fi
        else
            warning_log "Please install keymap-drawer manually before continuing"
            exit 1
        fi
    else
        success_log "keymap-drawer found"
    fi
}


# Get and expand paths
QMK_DIR=$(eval echo "$(get_config '.paths.qmk_dir')")
REPO_DIR=$(eval echo "$(get_config '.paths.repo_dir')")

# Handle script files with proper quoting and expansion
# shellcheck disable=SC2207
SCRIPT_FILES=($(get_config '.paths.script_files[]' | sed "s|^|$SCRIPT_DIR/|"))

# Debug output
if [[ "$DEBUG" == "true" ]]; then
    debug_log "Paths from config:"
    debug_log "  QMK_DIR: $QMK_DIR"
    debug_log "  REPO_DIR: $REPO_DIR"
    debug_log "  SCRIPT_FILES:"
    printf '    - %s\n' "${SCRIPT_FILES[@]}"
fi

check_qmk() {
    debug_log "Checking QMK installation..."
    
    # First check if qmk CLI is available
    if ! command -v qmk &>/dev/null; then
        debug_log "Warning: QMK CLI not found"

        if [[ "$DRY_RUN" == "true" ]]; then
            debug_log "Would prompt to install QMK CLI"
            return
        fi

        prompt_log "Would you like to install QMK CLI now? (y/n)"
        read -r response

        if [[ "$response" =~ ^[Yy]$ ]]; then
            if command -v python3 &>/dev/null; then
                python3 -m pip install --user qmk
                success_log "QMK CLI installed successfully"
            else
                error_log "Python3 not found. Please install Python3 and pip before continuing"
                exit 1
            fi
        else
            warning_log "Please install QMK CLI manually before continuing"
            exit 1
        fi
    else
        success_log "QMK CLI found"
    fi

    # Then check QMK firmware directory
    if [[ ! -d "$QMK_DIR" ]]; then
        debug_log "Warning: QMK firmware not found at $QMK_DIR"

        if [[ "$DRY_RUN" == "true" ]]; then
            debug_log "Would prompt to clone QMK firmware"
            return
        fi

        prompt_log "Would you like to clone and setup QMK firmware now? (y/n)"
        read -r response

        if [[ "$response" =~ ^[Yy]$ ]]; then
            # Configure QMK home directory
            qmk config user.qmk_home="$QMK_DIR"
            
            # Run QMK setup
            if ! qmk setup -y; then
                error_log "Failed to setup QMK firmware"
                exit 1
            fi
            success_log "QMK firmware setup completed successfully"
        else
            warning_log "Please setup QMK firmware manually before continuing"
            exit 1
        fi
    else
        success_log "QMK firmware found"
        # Even if directory exists, ensure it's properly setup
        if [[ "$DRY_RUN" == "false" ]]; then
            debug_log "Ensuring QMK firmware is properly setup..."
            qmk config user.qmk_home="$QMK_DIR"
            if ! qmk setup -y; then
                error_log "Failed to setup existing QMK firmware"
                exit 1
            fi
            success_log "QMK firmware is properly setup"
        fi
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
    check_yq
    check_keymap
    check_qmk
    setup_permissions
    setup_symlink

    if [[ "$DRY_RUN" == "true" ]]; then
        success_log "Dry run completed - no changes were made"
    else
        success_log "Setup completed successfully!"
    fi

    success_log "You can now use the 'koyo' command."
}

main
