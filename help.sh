#!/bin/bash

# Logging functions
log_header() {
    echo -e "${CYAN}$1:${NC}"
}

log_option() {
    echo -e "  ${GREEN}$1${NC} $2"
}

log_command() {
    echo -e "  ${GREEN}$1${NC} - $2"
}

log_subcommand() {
    echo -e "    ${BLUE}$1${NC} - $2"
}

log_example() {
    echo -e "  ${BLUE}$1${NC}"
}

show_help() {
    log_header "Usage"
    echo -e "koyo [-d|--debug] <command> [options]"
    echo ""

    log_header "Options"
    log_option "-d, --debug" "Enable debug output"
    echo ""

    log_header "Commands"
    log_command "help" "Show this help message"
    log_command "setup" "Setup Koyo environment"
    log_subcommand "--dry-run" "Show what would be done without making changes"
    log_command "update" "Command to update various related aspects"
    log_subcommand "svg" "Update the layout svg image"
    echo ""

    log_header "Keyboard Commands"

    log_command "moonlander" "ZSA Moonlander commands"
    log_subcommand "flash" "Flash the keyboard with current configuration"
    log_subcommand "oryx" "Open the layout in the Oryx configurator"

    log_command "crkbd" "Corne keyboard commands"
    log_subcommand "flash" "Flash the keyboard with current configuration"
    echo ""

    log_header "Examples"

    log_example "koyo setup"
    log_example "koyo setup --dry-run"
    log_example "koyo moonlander flash"
    log_example "koyo --debug moonlander flash"
    log_example "koyo crkbd flash"
}

export -f show_help
