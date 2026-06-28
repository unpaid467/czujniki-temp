# Single Board Check

Use this test when only one LilyGO TTGO LoRa board is connected by USB.

This test does not start the LoRa radio and does not send any radio packets.
It is safe to run without an antenna.

## Hardware

- one LilyGO TTGO LoRa V1.3 board
- USB cable connected to the computer
- no BME/BMP280 sensor
- no Dupont wires
- no LoRa antenna required for this test

## Arduino IDE Settings

- Board: `ESP32 Dev Module`
- Port: `COM3`
- Serial Monitor speed: `115200`

## Sketch

Open:

```text
tests/02_single_board_check/02_single_board_check.ino
```

Upload it to the connected board.

## Expected Serial Monitor Output

You should see:

```text
Single board check
==================
Chip model: ...
CPU frequency MHz: ...
Flash size bytes: ...

LoRa radio is not started in this sketch.
No antenna is needed for this test.

Board is running. Message 1
Board is running. Message 2
Board is running. Message 3
```

## What This Confirms

- the board can be programmed
- USB Serial works on `COM3`
- the ESP32 is running the uploaded sketch
- the project is ready for the next hardware step

Do not run LoRa sender sketches until an antenna is connected.
