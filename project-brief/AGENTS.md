# ESP32 Project Agent Rules

## Read first

- Read `project-brief/PRD.md` before product behavior changes.
- Read `project-brief/DESIGN_SYSTEM.md` before display UI changes.
- Read `project-brief/ARCHITECTURE.md` before hardware, toolchain, or structural changes.
- Read this file for project-specific workflows.

## Hardware and firmware

- Confirm exact board/module and component models and consult their documentation before changing wiring, pins, voltage, or peripherals.
- Label verified facts separately from assumptions. The current OLED controller is listed inconsistently by the vendor; verify behavior on the real display.
- Keep real Wi-Fi credentials only in the ignored local `include/secrets.h`. Never commit them or include them in logs or shared artifacts.
- Record each feature in `docs/` and add a dated Timeline entry to every Markdown document created or updated.
- Use the existing Notion Upcoming Tasks record for this project; keep status, decisions, validation, blockers, and any PR link current.
- Use PlatformIO with the Arduino framework unless the user approves a stack change.
- Do not claim a firmware build or hardware test succeeded until it has actually been performed.

## Git delivery

- Work on a feature branch. Do not push directly to `main`.
- Follow the shared AGENTS.md branch and PR rules for any requested push.
- Include validation performed and untested hardware behavior in the PR description.

## Timeline

- 2026-11-10 18:39 IST: Added project-specific hardware safety, secret handling, documentation, task tracking, and delivery rules.
