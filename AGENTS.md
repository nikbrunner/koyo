# AGENTS.md for kōyō

## Commands
- `./koyo setup`: Install and configure project dependencies
- `./koyo setup --dry-run`: Validate setup without making changes
- `./koyo moonlander flash`: Flash Moonlander keyboard
- `./koyo crkbd flash`: Flash Corne keyboard
- `./koyo chocofi flash`: Flash Chocofi keyboard (RP2040, compiles .uf2 and auto-copies)
- `./koyo voyager flash`: Flash Voyager keyboard
- `./koyo update keymap`: Generate board keymaps and the layout SVG from `keymap.yml`
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

## Keymap
- `keymap.yml` is the layout of every board; `./koyo update keymap` generates `qmk/*/src/keymap.generated.h` and `assets/layout.svg` from it, so never edit those two by hand
- For any key, layer, combo or tap dance change, and before every commit that touches `keymap.yml` or a `keymap.c`, use the `repo-layout` skill

## QMK Framework Notes
- All keyboards (Moonlander, Corne, Chocofi, and Voyager) use QMK's Chordal Hold for tap-hold features
- When implementing tap-hold functionality, use the `get_chordal_hold()` function

## Prerequisites
- QMK firmware
- keymap-drawer for SVG generation
- python3 for the keymap generator (standard library only)
- yq for YAML processing
- zsh shell
- git