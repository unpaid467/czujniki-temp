# OLED NTP Time Test

This test displays real current time on the built-in OLED display.

It uses Wi-Fi and NTP. NTP means Network Time Protocol. The ESP32 connects to
Wi-Fi, asks an internet time server for the current time, then updates the OLED
once per second.

It does not use LoRa and does not use the BME/BMP280 sensor.

## Required Arduino Libraries

Install these in Arduino IDE Library Manager:

- `Adafruit SSD1306`
- `Adafruit GFX Library`

`WiFi`, `time`, and `Wire` are included with the ESP32 Arduino core.

## Before Upload

Open:

```text
tests/04_oled_ntp_time_test/04_oled_ntp_time_test.ino
```

For private local use, create this file:

```text
tests/04_oled_ntp_time_test/wifi_secrets.h
```

Use this format:

```cpp
#ifndef WIFI_SECRETS_H
#define WIFI_SECRETS_H

#define WIFI_NAME_VALUE "YOUR_WIFI_NAME"
#define WIFI_PASSWORD_VALUE "YOUR_WIFI_PASSWORD"

#endif
```

Do not commit real Wi-Fi passwords to GitHub.

The repository includes `wifi_secrets.example.h` as a safe example.

## How It Works

The ESP32 does not know real time after reset.

This sketch does this:

1. starts the OLED display
2. connects to Wi-Fi
3. asks `pool.ntp.org` for current time
4. applies the Poland time zone
5. draws the time on the OLED every second

## Time Zone

The sketch uses:

```cpp
const char* TIME_ZONE = "CET-1CEST,M3.5.0,M10.5.0/3";
```

This means Central European Time with automatic summer time change.

## Expected Result

The OLED should show:

```text
Current time

14:37:05

28.6.2026
```

Serial Monitor at `115200` baud will also print the current time.
