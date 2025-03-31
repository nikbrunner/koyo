# CLAUDE.md for kōyō

## Commands
- `./koyo setup`: Install and configure project dependencies
- `./koyo setup --dry-run`: Validate setup without making changes
- `./koyo moonlander flash`: Flash Moonlander keyboard
- `./koyo crkbd flash`: Flash Corne keyboard
- `./koyo update svg`: Update layout SVG
- `./koyo update qmk`: Update QMK firmware
- `./koyo --debug <command>`: Run with verbose logging

## Code Style Guidelines
- Shell scripts use `set -euo pipefail` for strict error handling
- Use modular approach with separate script files for related functions
- Follow existing color-coded output patterns:
  - Blue: Debug, Cyan: Prompts, Yellow: Warnings, Green: Success, Red: Errors
- Maintain project structure with keyboard-specific code in dedicated subdirectories
- Use absolute paths when referring to files
- Utilize utility functions from `utils.sh` for consistent logging and operations
- Test thoroughly with `--dry-run` before implementing changes

## Prerequisites
- QMK firmware
- keymap-drawer for SVG generation
- yq for YAML processing
- zsh shell
- git