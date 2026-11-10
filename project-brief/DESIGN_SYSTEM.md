# Display Design System

## Scope

This is a compact monochrome OLED interface, not a web or mobile UI. The display is 128×64 pixels and the user requested only Wi-Fi connection status and IP address.

## Current screen design

- Use the OLED's monochrome pixels with clear foreground/background contrast.
- Keep one short title at the top, a prominent connection state in the middle, and the IP or next-step hint on the bottom line.
- Use built-in U8g2 sans-serif fonts that fit the display; avoid animation and decorative graphics that reduce legibility.
- Do not show the Wi-Fi network name or password.
- Show concise ASCII labels to avoid font encoding issues.

These choices are a simple first-pass layout derived from the 128×64 display and requested content; the user can adjust them after seeing the first upload.

## Timeline

- 2026-11-10 18:39 IST: Defined a minimal text-first layout for the first Wi-Fi status screen, derived from the user's requested content and OLED size.
