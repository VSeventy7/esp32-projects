# Product Requirements

## Users

The owner building a first ESP32 display project. This is based on the user's request in chat.

## Problem and goal

The user wants a simple, useful first build using the ESP32 and OLED already selected. The goal is a small Wi-Fi status screen showing connection state and the assigned IP address.

## Must-have scope

- Join the user's Wi-Fi network using credentials configured locally.
- Show connecting and disconnected/retrying states.
- When connected, show the local IPv4 address.
- Use only the ESP32 and OLED as electronic modules; no additional sensors are required.

## Out of scope

- Sensor readings, Raspberry Pi integration, cloud dashboards, or other monitor features for this first build.
- Displaying the Wi-Fi name or password; the user requested connection state and IP only.

## Success and acceptance criteria

- PlatformIO builds the firmware for the generic ESP32 Dev Module.
- On the physical setup, the OLED shows connection progress, then `Connected` and the current local IP after Wi-Fi joins.
- If Wi-Fi is unavailable, the OLED reports the disconnected/retrying state.
- No Wi-Fi password or real credential is committed to the public repository.

## Verified hardware facts

- Board photo: 30-pin ESP32 DevKit-style board with ESP-WROOM-32D module marking; board pin labels include 3V3, GND, D21, and D22.
- Display product listing: Robocraze 0.96-inch, 128×64, four-pin I²C OLED, listed for 3.3–5 V.
- Display controller is uncertain: the listing's description says SSD1315 while its FAQ also says SSD1306. Initial firmware uses the SSD1306-compatible U8g2 constructor; hardware verification is pending.

## Timeline

- 2026-11-10 18:39 IST: Recorded the user-selected first build and verified hardware facts from the conversation and product listing.
