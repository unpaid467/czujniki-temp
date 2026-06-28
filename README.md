# GardenSensors

GardenSensors is a beginner-friendly environmental monitoring project based on
ESP32 and LoRa.

The final goal is to collect temperature, humidity and pressure measurements
from several places on a property and send them to a gateway.

## Current Status

Stage 1 is complete:

- upload sketches to ESP32
- use USB serial communication
- understand `setup()` and `loop()`

Stage 2 is blocked:

- the BME/BMP280 sensor pins are not soldered yet
- no code should assume that the sensor is electrically connected

Current safe work:

- single-board ESP32 check over USB Serial
- OLED display clock test without LoRa radio
- OLED real-time clock test using Wi-Fi and NTP
- no LoRa transmission until antennas are connected
- no BME/BMP280 testing until sensor pins are soldered

## Hardware

- 2 x LilyGO TTGO LoRa V1.3
- ESP32
- SX1276 LoRa 868 MHz
- 0.96 inch OLED
- 1 x BME/BMP280 module
- female-female Dupont wires

## Software

- Windows 11
- Arduino IDE 2.3.10
- ESP32 Arduino Core
- Board: ESP32 Dev Module
- Port: COM3
- Serial Monitor speed: 115200 baud

## Development Rules

Work in small steps:

1. Implement one small feature.
2. Verify that it works.
3. Explain why it works.
4. Commit.
5. Continue.

Do not mix hardware features in one test sketch.

## Repository Layout

```text
GardenSensors/
  README.md
  AGENTS.md
  transmitter/
  receiver/
  tests/
    01_serial_test/
    02_single_board_check/
    03_oled_time_test/
    04_oled_ntp_time_test/
    02_bme280_test/
    03_lora_test/
      sender/
      receiver/
  docs/
  diagrams/
```
