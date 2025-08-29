# libhmk

This repository contains libraries for building a Hall-effect keyboard firmware.

## Table of Contents

- [Features](#features)
- [Limitations](#limitations)
- [Getting Started](#getting-started)
- [Development](#development)
- [Porting](#porting)
- [Acknowledgements](#acknowledgements)

## Features

- [x] **Analog Input**: Customizable actuation point for each key and many other features.
- [x] **Rapid Trigger**: Register a key press or release based on the change in key position and the direction of that change
- [x] **Continuous Rapid Trigger**: Deactivate Rapid Trigger only when the key is fully released.
- [x] **Null Bind (SOCD + Rappy Snappy)**: Monitor 2 keys and select which one is active based on the chosen behavior.
- [x] **Dynamic Keystroke**: Assign up to 4 keycodes to a single key. Each keycode can be assigned up to 4 actions for 4 different parts of the keystroke.
- [x] **Tap-Hold**: Send a different keycode depending on whether the key is tapped or held.
- [x] **Toggle**: Toggle between key press and key release. Hold the key for normal behavior.
- [x] **N-Key Rollover**: Support for N-Key Rollover and automatically fall back to 6-Key Rollover in BIOS.
- [x] **Automatic Calibration**: Automatically calibrate the analog input without requiring user intervention.
- [x] **EEPROM Emulation**: No external EEPROM required. Emulate EEPROM using the internal flash memory.
- [x] **Web Configurator**: Configure the firmware using [hmkconf](https://github.com/peppapighs/hmkconf) without needing to recompile the firmware.
- [x] **Tick Rate**: Customizable tick rate for Tap-Hold and Dynamic Keystroke.
- [x] **8kHz Polling Rate**: Support for 8kHz polling rate on some microcontrollers (e.g., AT32F405xx).
- [x] **Gamepad**: Support for XInput gamepad mode, allowing the keyboard to be used as a game controller.

## Limitations

- **RGB Lighting**: The firmware does not support RGB lighting.

## Getting Started

### Prerequisites

- [PlatformIO](https://platformio.org/)
- [Python 3](https://www.python.org/)

### Building the Firmware

1. Clone the repository:

   ```bash
   git clone https://github.com/peppapighs/libhmk.git
   ```

2. Open the project in PlatformIO, such as through Visual Studio Code.

3. Run `python setup.py -k <YOUR_KEYBOARD>` to generate the `platformio.ini` file.

4. Wait for PlatformIO to finish initializing the environment.

5. Build the firmware using either `pio run` in the PlatformIO Core CLI or through the PlatformIO IDE's "Build" option. The firmware binaries will be generated in the `.pio/build/<YOUR_KEYBOARD>/` directory with the following files:

   - `firmware.bin`: The binary firmware file
   - `firmware.elf`: The ELF firmware file

6. Flash the firmware to your keyboard using your preferred method (e.g., DFU, ISP). If your keyboard has a DFU bootloader, you can set `upload_protocol = dfu` in `platformio.ini` and use the command `pio run --target upload` or the PlatformIO IDE's "Upload" option while the keyboard is in DFU mode.

## Development

The development branch is `dev`, which contains the latest features and bug fixes. The corresponding `dev` branch of [hmkconf](https://github.com/peppapighs/hmkconf/tree/dev) deployed at [https://hmkdev.prasertsuk.com](https://hmkdev.prasertsuk.com) is required to configure the `dev` branch of the firmware. To contribute, please create a pull request against the `dev` branch.

### Developing a New Keyboard

To develop a new keyboard, create a new directory under `keyboards/` with your keyboard's name. This directory should include the following files:

- `keyboard.json`: A JSON file containing metadata about your keyboard, used for both firmware compilation and the web configurator. Refer to [`scripts/schema/keyboard.schema.json`](scripts/schema/keyboard.schema.json) for the schema.
- `config.h` (Optional): Additional configuration header for your keyboard to define custom configurations beyond what's specified in `keyboard.json`.

You can use an existing keyboard implementation as a reference. If your keyboard hardware isn't currently supported by the firmware, you'll need to implement the necessary drivers and features. See the [Porting](#porting) section for more details.

### Debugging

In addition to the debugging options provided by PlatformIO, you can use the `log_printf` function to log messages to the console. The function is available when you run the `setup.py` with the flag `--log` to enable logging. The function uses [`eyalroz/printf`](https://github.com/eyalroz/printf) as a backend for text formatting.

The log messages will be sent to the HID interface, which can be viewed in [hid_listen](https://www.pjrc.com/teensy/hid_listen.html), [QMK CLI](https://docs.qmk.fm/cli_commands#qmk-console), or [QMK Toolbox](https://qmk.fm/toolbox) (buggy, not recommended).

## Porting

### Hardware Driver Structure

Hardware drivers follow this directory structure:

- [`hardware/`](hardware/): Contains hardware-specific header files. Each subdirectory should also contain an `info.json` file that describes the PlatformIO configuration, TinyUSB configuration, and additional metadata. Refer to [`scripts/schema/driver.schema.json`](scripts/schema/driver.schema.json) for the schema.
- [`include/hardware/`](include/hardware/): Contains hardware driver interface headers that declare functions to be implemented
- [`src/hardware/`](src/hardware/): Contains hardware driver implementations of the functions declared in the header files
- [`linker/`](linker/): Contains linker scripts for supported microcontrollers

You can refer to existing hardware drivers as examples when implementing support for new hardware.

## Acknowledgements

- [hathach/tinyusb](https://github.com/hathach/tinyusb) for the USB stack.
- [qmk/qmk_firmware](https://github.com/qmk/qmk_firmware) for inspiration, including EEPROM emulation and matrix scanning.
- [@riskable](https://github.com/riskable) for pioneering custom Hall-effect keyboard firmware development.
- [@heiso](https://github.com/heiso/) for his [macrolev](https://github.com/heiso/macrolev) and his helpfulness throughout the development process.
- [Wooting](https://wooting.io/) for pioneering Hall-effect gaming keyboards and introducing many advanced features based on analog input.
- [GEONWORKS](https://geon.works/) for the Venom 60HE PCB and inspiring the web configurator.
- [@eyalroz](https://github.com/eyalroz) for his work on the printf library and its integration into the firmware.
