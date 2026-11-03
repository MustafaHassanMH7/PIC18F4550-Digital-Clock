# PIC18F4550 Tabanlı Dijital Saat | Digital Clock

**Embedded Systems · PIC Microcontrollers · Embedded C · 7-Segment Display · Proteus**

**Developer:** Mustafa Hassan Mohamed Hassan  
**Course:** EEM319 Mikroişlemciler  
**Project period:** 2024–2025 (original build records dated 17 December 2024 and 13 January 2025)

## Project overview

This educational digital-clock prototype uses the **PIC18F4550** microcontroller and a four-digit common-anode **7-segment display** to show hours and minutes. Firmware was developed in **mikroC PRO for PIC**, and the electronic circuit was designed in Proteus.

The repository contains the embedded C source, mikroC configuration, original compiled Intel HEX, and a technical review of the display multiplexing and timekeeping logic.

## Technical specifications

| Item | Implementation |
|---|---|
| Microcontroller | Microchip PIC18F4550 |
| Oscillator setting | 8 MHz in mikroC project file |
| Display | 4-digit common-anode 7-segment |
| Language and IDE | Embedded C / mikroC PRO for PIC |
| Segment lines | PORTB |
| Digit selection | PORTD |
| Multiplexing | `displayTime()` / `displayNumber()` |
| Time increment | Software loop counting with `Delay_ms(5)` |
| Circuit design | Proteus (original project, binary file not yet uploaded) |

## Files

- [`firmware/MyProject.c`](firmware/MyProject.c) — later C implementation with corrected timing comments; functionally equivalent timekeeping algorithm.
- [`firmware/MyProject.mcppi`](firmware/MyProject.mcppi) — mikroC project settings.
- [`firmware/MyProject.hex`](firmware/MyProject.hex) — Intel HEX output from the original archive; **not rebuilt for this publication**.
- [`original/MyProject_early_variant.c`](original/MyProject_early_variant.c) — earlier implementation for comparison.
- [`TECHNICAL_REVIEW.md`](TECHNICAL_REVIEW.md) — technical review and known limitations.
- [`KARIYER_PROJECT_TEXT.txt`](KARIYER_PROJECT_TEXT.txt) — concise Turkish project description.
- `.gitignore` — ignores generated IDE artifacts.

**Original binary assets not yet published here:** `simulation/clocke.pdsprj` (Proteus), `docs/Circuit_Overview.jpg` (presentation-derived image), and `docs/Sunum.pptx` (slides). These remain in the separately prepared local project archive and are **not** links to currently accessible GitHub files.

## How the firmware works

1. `setup()` configures PORTB and PORTD as outputs.
2. `displayNumber()` selects a display digit, outputs the segment code, and delays 5 ms.
3. `displayTime()` multiplexes the four digits for hours and minutes.
4. The main loop increments the minute variable after a fixed number of display refresh cycles.

## Technical verification and limitations

Build logs from the original source archive report successful compilation for PIC18F4550. That does **not** demonstrate accurate real-time clock operation or physical-hardware validation. No new compilation, Proteus run, or hardware timing measurement was performed while preparing this repository.

The later source uses 2,980 refresh cycles with four 5 ms waits per cycle, giving **approximately 59.6 seconds of nominal delay** before a one-minute increment, excluding program overhead. The earlier source uses 1,200 cycles (approximately 24 seconds). Neither is a calibrated timebase.

Potential improvements: hardware timer interrupts or an RTC, separate display refresh scheduling, and measured timing validation.

See [the technical review](TECHNICAL_REVIEW.md) for detailed findings.

## Project scope

This repository documents a student embedded-systems implementation and its source-code development, not a commercially validated timekeeping device.
