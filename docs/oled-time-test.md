# OLED Time Test

This test displays a simple clock on the built-in OLED display.

It does not use LoRa and does not use the BME/BMP280 sensor.

## Required Arduino Libraries

Install these in Arduino IDE Library Manager:

- `Adafruit SSD1306`
- `Adafruit GFX Library`

`Wire` is included with the ESP32 Arduino core.

## Hardware

- one LilyGO TTGO LoRa V1.3 board
- USB cable connected to the computer
- no LoRa antenna required, because this sketch does not start LoRa
- no BME/BMP280 sensor
- no Dupont wires

## Sketch

Open:

```text
tests/03_oled_time_test/03_oled_time_test.ino
```

Upload it to the connected board.

## How The Clock Works

The sketch starts at:

```text
12:00:00
```

Every time one second passes, the program adds one second to the displayed
time.

This is done with `millis()`. `millis()` returns how many milliseconds have
passed since the ESP32 started running the sketch.

## Important Limitation

This is not real current wall-clock time.

The ESP32 does not know the real date and time by itself after reset. This test
is only a simple running clock:

- it starts from `12:00:00`
- it updates every second
- it resets back to `12:00:00` after reset or power loss
- it may slowly drift because it is not synchronized to the internet or an RTC

Later, real time can be added using Wi-Fi and NTP, or using an RTC module.

## Expected Result

The OLED should show:

```text
OLED time test

12:00:01
12:00:02
12:00:03
```

The Serial Monitor also prints the same time at `115200` baud.
