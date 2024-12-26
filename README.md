# kōyō

![banner](./assets/banner.png)

- [Introduction](#introduction)
- [Features](#features)
- [CLI Tool](#cli-tool)
- [Layout](#layout)
- [Project Structure](#project-structure)
- [Prerequisites](#prerequisites)
- [Development](#development)
    - [Adding New Features](#adding-new-features)
    - [Testing](#testing)
- [Roadmap](#roadmap)
- [Resources](#resources)
- [Contributing](#contributing)
- [License](#license)

## Introduction

**kōyō** is a sleek, minimalistic keyboard layout, designed with a 36-key split configuration. Its name is inspired by the harmony and elegance of Japanese aesthetics and the calming feeling of autumn leaves.

> In Japanese, **kōyō (紅葉)** translates to "autumn leaves" and is used to describe the phenomenon of leaves changing color in the autumn season. The word is composed of two kanji characters: **kō (紅)** meaning "crimson" and **yō (葉)** meaning "leaf".

## Note

> [!NOTE]
> The layout in its current form is mainly focused for use in combination with MacOS.
> It can work on other operating systems, but the layout may not be optimized for them.
> In the future, I (hopefully) will be working on optimizing the layout for other operating systems.

## Features

### Core Layout

- QWERTY Base: Familiar layout to ease the transition while maintaining efficiency
- Compact 36-Key Design: Optimized for minimal finger movement and maximum ergonomics
- Strategic Alpha Placement: Bottom row alphas remain easily accessible without blocking home row access

### Layer Design

- Extended layer under space bar for frequently used tools
- Dual symbol layers (one per hand) with semantic arrangement
- Dedicated number and function key layers

### Thumb Cluster Philosophy

- Reserved for high-frequency, single-action keys (Space, Enter, Tab)
- Dual-purpose modifiers (MEH, HYPER) integrated with common actions
- Avoids sequential/repeated actions to prevent thumb fatigue
    - e.g. Backspace implemented as two-finger combo (I+O) to avoid repeated presses of thumb

### Navigation & Tools

- Vim-Inspired Navigation:
    - Arrow keys in familiar HJKL pattern
    - Navigation shortcuts following vim metaphors
        - `[` & `]` for often used navigation bindings are combos on the base layer
    - Extended layer provides quick access to common movements
- Efficient Symbol Access:
    - Symbols arranged in semantic pairs for intuitive access
    - Common programming symbols placed at strongest fingers
    - Consistent access pattern across both hands

### Special Features

- Integrated Shortcuts:
    - Quick access to common GUI commands
        - e.g. Put common GUI commands on left hand split to enable one hand use in combination with the right hand on mouse
    - Tab and window management controls
    - Media and system controls in dedicated layer
- Smart Tap Dancing:
    - Dual-function keys for extended capabilities
    - Context-aware modifier combinations
    - Reduced finger travel for common operations

### Quality of Life

- Achordion Integration: Smart handling of hold-tap actions
- Cross-Platform Compatibility: Works seamlessly across operating systems
- Customizable Function Layer: Easy access to F-keys and system functions

## Layout

![layout graphic](./assets/layout.svg)

## CLI Tool

The `koyo` CLI tool provides a streamlined interface for managing your keyboard configurations:

### Installation

```bash
# Clone the repository
git clone https://github.com/nikbrunner/koyo.git

# Run the setup script
./setup.sh
```

### Commands

#### Setup

```bash
# Standard setup
koyo setup

# Dry run to see what would happen
koyo setup --dry-run
```

#### Keyboard Operations

```bash
# Flash Moonlander keyboard
koyo moonlander flash

# Open Moonlander configuration in Oryx
koyo moonlander oryx

# Flash Corne keyboard
koyo crkbd flash
```

#### Update Operations

```bash
# Update layout SVG
koyo update svg

# Update QMK firmware
koyo update qmk
```

### Debug Mode

Add the `--debug` or `-d` flag to any command for verbose output:

```bash
koyo --debug moonlander flash
```

## Project Structure

```
koyo/
└── assets/            # Project assets
├── qmk/               # QMK configurations
│   ├── moonlander/    # Moonlander specific files
│   └── crkbd/         # Corne specific files
├── setup.sh           # Setup script
├── utils.sh           # Utility functions
├── help.sh            # Help documentation
├── update_svg.sh      # SVG update script
├── config.yml         # Configuration file
├── koyo               # koyo command
```

## Prerequisites

- `qmk` firmware
- `keymap-drawer` for SVG generation
- `yq` for YAML processing
- `zsh` shell
- `git`

## Development

### Adding New Features

1. Create a new branch for your feature
2. Implement your changes
3. Update documentation if necessary
4. Submit a pull request

### Testing

Before submitting changes:

1. Test all keyboard configurations
2. Verify CLI commands work as expected
3. Run setup script in dry-run mode

## Roadmap

- [x] `koyo moonlander flash` (Flashes the Moonlander Keybaord)
- [x] `koyo setup` (Sets up Prerequisites)
- [x] DRY up scripts
- [x] `koyo moonlander oryx` (Opens up Oryx Configurator Page)
- [x] `koyo corne flash` (Flashes the Corne Keyboard)
- [x] `koyo update svg` (Updates the SVG files)
- [x] `koyo update qmk` (Pulls latest Version of QMK firmware)
- [x] Ensure keymap-drawer is installed
- [x] Align layouts & purge unused or redundant stuff
- [x] Document differences between kōyō for CRKBD and Moonlander
- [x] Add note about current optimizations focused on MacOS
- [ ] Optimize Home Row Mods for MacOS
- [ ] Make Layout SVG OS agnostic
- [ ] Script to automatically update SVG
- [ ] SSOT for keymap. Script to generate `keymap.c` files from SSOT.

## Resources

- [urob](https://github.com/urob/zmk-config): timeless home row mods
- [infused-kim](https://github.com/infused-kim/zmk-config)
- [miryoku_zmk](https://github.com/manna-harbour/miryoku_zmk)
- [ZMK Docs](https://zmk.dev/docs)
- [Designing a Symbol Layer](https://getreuer.info/posts/keyboards/symbol-layer/index.html)
- [A guide to home row mods](https://precondition.github.io/home-row-mods#shift-thumb-keys)
- [Callum Mods](https://github.com/callum-oakley/qmk_firmware/tree/master/users/callum)
- [Jonas Hietala: I designed my own keyboard layout. Was it worth it?](https://www.jonashietala.se/blog/2023/11/02/i_designed_my_own_keyboard_layout_was_it_worth_it/)

## Contributing

Contributions are welcome! Please read through the existing issues and pull requests before creating new ones.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
