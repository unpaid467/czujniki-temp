# Project Instructions

This project is for learning embedded development from the beginning.

Priorities:

- simple code
- readable examples
- small working stages
- comments that explain the purpose of each important line
- no premature optimization
- no advanced abstractions unless they become necessary later

Use Arduino IDE compatible C++.

Use English names for variables and functions.

Use Polish comments in sketches. ASCII Polish comments are acceptable.

Prefer functions over classes at this stage.

## Current Stage

Stage 1, serial communication, is complete.

Stage 2, BME/BMP280 testing, is blocked until the sensor pins are soldered.

Do not assume that the BME/BMP280 sensor is connected yet.

## Coding Guidelines

Good names:

- `temperature`
- `humidity`
- `pressure`
- `measurementCounter`
- `deviceId`
- `packetCounter`
- `readSensor()`
- `sendPacket()`
- `printMeasurements()`
- `initializeSensor()`
- `initializeLoRa()`

Avoid:

- unnecessary macros
- templates
- inheritance
- design patterns
- unnecessary classes

## Commit Policy

Prefer many small commits.

Example commits:

- Initialize project
- Add serial communication test
- Add BME280 detection
- Add LoRa sender
- Add LoRa receiver
