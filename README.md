# ESP32 Projects

PlatformIO firmware projects for the generic 30-pin ESP32 DevKit with an ESP-WROOM-32D module.

## First project: Wi-Fi status OLED

The firmware displays Wi-Fi connection state and the ESP32's local IP address on a Robocraze 0.96-inch, 128×64, four-pin I²C OLED.

### Hardware

| OLED pin | ESP32 pin |
| --- | --- |
| GND | GND |
| VDD | 3V3 |
| SCK | D22 / GPIO22 (I²C clock) |
| SDA | D21 / GPIO21 |

The display is powered from the ESP32's 3.3 V pin. Disconnect USB power before changing wires.

### VS Code and PlatformIO

1. Open this repository folder in VS Code with the PlatformIO IDE extension installed.
2. Copy `include/secrets.example.h` to `include/secrets.h` and enter the Wi-Fi name and password in the local copy. `secrets.h` is ignored by Git.
3. Build and upload the `esp32dev` PlatformIO environment.
4. Open PlatformIO's Serial Monitor at 115200 baud for connection messages.

The screen shows `Connecting...` while joining, `Not connected` while retrying, and `Connected` with the assigned IP address after joining. It intentionally does not display the Wi-Fi name or password.

## Timeline

- 2026-11-10 18:39 IST: Added the first PlatformIO Wi-Fi status display project and documented its hardware, safe local credential setup, and expected screen states.
