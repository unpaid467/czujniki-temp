# Wiring

## Future BME/BMP280 Wiring

Use this wiring after the sensor pins are soldered:

| BME/BMP280 pin | ESP32 pin |
| --- | --- |
| VIN | 3V3 |
| GND | GND |
| SCL | GPIO22 |
| SDA | GPIO21 |

## Notes

- Connect power only when the wiring is clear.
- Use 3V3 for the sensor module unless the exact module documentation says
  otherwise.
- Do not continue with Stage 2 until the solder joints are complete.
