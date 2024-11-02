#!/bin/bash

# Colors
export RED='\033[0;31m'
export GREEN='\033[0;32m'
export YELLOW='\033[1;33m'
export BLUE='\033[0;34m'
export CYAN='\033[0;36m'
export NC='\033[0m' # No Color

# Logging functions
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

error_log() {
    echo -e "${RED}ERROR:${NC} $1"
}

get_config() {
    local key=$1
    yq eval "$key" "$(dirname "${BASH_SOURCE[0]}")/config.yml"
}

export -f debug_log
export -f prompt_log
export -f warning_log
export -f success_log
export -f error_log
export -f get_config
