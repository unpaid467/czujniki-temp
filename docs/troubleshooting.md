# Troubleshooting

## COM3 Is Busy

If a tool cannot open `COM3`, close Arduino IDE Serial Monitor or any other
program that may be using the port.

Only one program can usually use a serial port at the same time.

## Serial Monitor Shows Nothing

Check:

- baud rate is `115200`
- correct port is selected: `COM3`
- board is connected by USB
- sketch was uploaded successfully

## Upload Fails

Check:

- board selection: `ESP32 Dev Module`
- port selection: `COM3`
- USB cable supports data, not only charging
