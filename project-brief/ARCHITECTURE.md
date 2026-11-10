# Architecture

## Hardware

- Generic 30-pin ESP32 DevKit-style board with an ESP-WROOM-32D module.
- Robocraze 0.96-inch 128×64 four-pin I²C OLED.
- I²C uses GPIO21 (SDA) and GPIO22 (SCL/SCK) on this generic ESP32 configuration.
- Power the display from the ESP32 3V3 output and share ground.

## Software stack

- VS Code with the PlatformIO IDE extension.
- PlatformIO environment `esp32dev`, Espressif 32 platform, Arduino framework.
- U8g2 library for the display; ESP32 Arduino Wi-Fi API for station mode.
- Firmware runs locally on the ESP32. No service, database, or network API is required.

## Data and credentials

- Wi-Fi SSID and password are supplied in local `include/secrets.h`, copied from `include/secrets.example.h`.
- `.gitignore` excludes `include/secrets.h`; do not commit or paste real credentials into chat.
- The only displayed network data is connection state and local IPv4 address.

## Runtime flow

1. Initialize I²C on GPIO21/GPIO22 and detect OLED at common address 0x3C or 0x3D.
2. Initialize the OLED and show a setup prompt if credentials are missing.
3. Join Wi-Fi in station mode and display connecting/retrying status.
4. On connection, display `Connected` and the current local IP; retry after a disconnect.

## Build and delivery

- Build/upload from VS Code using PlatformIO's `esp32dev` environment and the detected serial port.
- Do not push changes directly to `main`; use a feature branch and PR for delivery.
- Physical display/USB/upload verification remains pending until the user runs the firmware on their laptop and board.

## Timeline

- 2026-11-10 18:39 IST: Recorded the verified board/display, user's VS Code preference, PlatformIO/Arduino stack, safe local secrets, and initial firmware flow.
