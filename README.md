# Switch Bluetooth Controllers

A Python toolkit for scanning, connecting, and monitoring Nintendo Switch-compatible controllers (Pro Controller, Joy-Con, GameCube Controller) via Bluetooth. Designed to support controller detection, data monitoring, and feature exploration on multiple platforms using the [bleak](https://github.com/hbldh/bleak) Bluetooth library.
Some functions noted here may not be working right now so sorry 


> **Note:** This repository is intended as a universal base for all future tools and programs related to Nintendo Switch and compatible Bluetooth controllers. Contributions and extensions are welcome.

> **This repository contains portions of code or information derived from sources licensed as follows:**  
> **Copyright (c) 2025, Jacques Gagnon**  
> **SPDX-License-Identifier: Apache-2.0**

## Features

- **Bluetooth Device Scanning**: Quickly discover Nintendo Switch-compatible controllers around you.
- **Controller Monitoring**: View button presses and stick movements in real-time.
- **Interactive Mode**: Toggle debug/verbose output, rumble, LED indicators, and show raw report data during runtime (best on Linux/macOS).
- **Multi-platform Support**: Compatible with Windows(tested), Linux, and macOS(tested) (interactivity may be limited on Windows).
- **Extensible Mapping**: Supports both Joy-Con, Pro Controller, and GameCube Controller mappings.
- **Open for Extensions**: Designed to be a base for further Python tools for Nintendo and compatible Bluetooth controllers.

## Supported Controllers

- Nintendo Switch Pro Controller
- Nintendo Switch Joy-Con (L/R, only separately)
- Nintendo GameCube Controller

## Quick Start

### Requirements

- Python 3.7+ (tested in 3.12)
- [bleak](https://pypi.org/project/bleak/) (`pip install bleak`)

### Usage

```bash
python3 ns2-ble-monitor.py [options]
```

**Options:**

- `-d`, `--debug` Enable debug output
- `-v`, `--verbose` Enable verbose output

### Interactive Controls (during runtime)

- `r` Test rumble
- `1`-`8` Set player LED
- `d` Toggle debug mode
- `v` Toggle verbose mode
- `x` Show raw data (byte values)
- `Ctrl+C` Exit

> **Note:** Some interactive features may not work reliably on Windows due to OS limitations.

## Pairing Instructions

1. **Put controller in pairing mode:**
   - Pro Controller: Hold the small pairing button on top
   - Joy-Con: Hold the pairing button on the side
   - GameCube Controller: Hold the pairing button on the adapter
2. Ensure the controller is not already connected to another device.
3. Run the program and follow the on-screen instructions.

## Roadmap & Contribution

- Add support for combined Joy-Con mode
- Improved cross-platform keyboard interactivity
- Integrate advanced rumble/LED scripting

Contributions, issues, and feature requests are welcome!

## License

MIT License  
Parts of this repository are derived from sources licensed under Apache-2.0 (see notices above).

---

**This repository is for experimentation, learning, and controller interfacing. It is not affiliated with or endorsed by Nintendo.**
