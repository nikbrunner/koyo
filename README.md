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
- [Resources](#resources)
- [Contributing](#contributing)
- [License](#license)

## Introduction

**kōyō** is a sleek, minimalistic keyboard layout, designed with a 36-key split configuration. Its name is inspired by the harmony and elegance of Japanese aesthetics and the calming feeling of autumn leaves.

> In Japanese, **kōyō (紅葉)** translates to "autumn leaves" and is used to describe the phenomenon of leaves changing color in the autumn season. The word is composed of two kanji characters: **kō (紅)** meaning "crimson" and **yō (葉)** meaning "leaf".

## Features

### Core Layout

- **QWERTY Base**: Familiar layout to ease the transition while maintaining efficiency
- **Compact 36-Key Design**: Optimized for minimal finger movement and maximum ergonomics
- **Strategic Alpha Placement**: Bottom row alphas remain easily accessible without blocking home row access

### Layer Design

- **Intuitive Layer Access**:
  - Extended layer under space bar for frequently used tools
  - Dual symbol layers (one per hand) with semantic arrangement
  - Dedicated number and function key layers

### Ergonomic Optimizations

- **Thumb Cluster Philosophy**:

  - Reserved for high-frequency, single-action keys (Space, Enter, Tab)
  - Avoids sequential/repeated actions to prevent thumb fatigue
  - Dual-purpose modifiers (MEH, HYPER) integrated with common actions

- **Smart Key Combinations**:
  - Backspace implemented as two-finger combo (I+O) to distribute load
  - Strategic use of home row mods for modifier access
  - Layer-tap combinations for efficient space utilization

### Navigation & Tools

- **Vim-Inspired Navigation**:

  - Arrow keys in familiar HJKL pattern
  - Navigation shortcuts following vim metaphors
  - Extended layer provides quick access to common movements

- **Efficient Symbol Access**:
  - Symbols arranged in semantic pairs for intuitive access
  - Common programming symbols placed at strongest fingers
  - Consistent access pattern across both hands

### Special Features

- **Integrated Shortcuts**:

  - Quick access to common GUI commands
  - Tab and window management controls
  - Media and system controls in dedicated layer

- **Smart Tap Dancing**:
  - Dual-function keys for extended capabilities
  - Context-aware modifier combinations
  - Reduced finger travel for common operations

### Quality of Life

- **Achordion Integration**: Smart handling of hold-tap actions
- **Cross-Platform Compatibility**: Works seamlessly across operating systems
- **Customizable Function Layer**: Easy access to F-keys and system functions

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

## Layout

![layout graphic](./assets/layout.svg)

## Project Structure

```
koyo/
├── setup.sh           # Setup script
├── utils.sh           # Utility functions
├── qmk/               # QMK configurations
│   ├── moonlander/    # Moonlander specific files
│   └── crkbd/         # Corne specific files
├── help.sh            # Help documentation
├── update_svg.sh      # SVG update script
├── config.yml         # Configuration file
└── assets/           # Project assets
```

## Prerequisites

- QMK Firmware
- `keymap-drawer` for SVG generation
- `yq` for YAML processing
- ZSH shell
- Git

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
