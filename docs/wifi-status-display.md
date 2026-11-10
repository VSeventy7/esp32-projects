# Wi-Fi Status OLED

## Purpose

Show whether the ESP32 is connected to Wi-Fi and, when connected, its local IPv4 address.

## Hardware and connections

- Controller: generic 30-pin ESP32 DevKit carrying an ESP-WROOM-32D module.
- Display: Robocraze 0.96-inch, 128×64, four-pin I²C OLED.
- `GND` → ESP32 `GND`.
- `VDD` → ESP32 `3V3`.
- `SCK` → ESP32 `D22` / GPIO22 (I²C clock).
- `SDA` → ESP32 `D21` / GPIO21.

## Screen states

- `Connecting...` while joining the configured network.
- `Not connected` / `Retrying...` after a connection attempt times out.
- `Connected` and the current local IP address after the ESP32 joins.
- A setup prompt when Wi-Fi credentials have not been configured.

The screen omits the network name and credentials. Credentials belong in the ignored local file `include/secrets.h`, copied from `include/secrets.example.h`.

## Implementation notes

The firmware uses the Arduino framework through PlatformIO and U8g2 for the OLED. The vendor listing identifies SSD1315 in the description but also mentions SSD1306 in its FAQ, so the firmware starts with U8g2's SSD1306 128×64 I²C constructor. It scans the common I²C addresses 0x3C and 0x3D. The controller choice remains an assumption until the display is confirmed working on the user's hardware.

## Validation

Firmware build and hardware upload are pending on the user's laptop and physical ESP32/OLED. No Wi-Fi credentials are stored in the repository.

## Timeline

- 2026-11-10 18:39 IST: Added the initial feature description, connection map, UI states, credential handling, and noted the vendor's conflicting controller information.
