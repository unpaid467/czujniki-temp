#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const unsigned long SERIAL_BAUDRATE = 115200;
const unsigned long ONE_SECOND_MS = 1000;

const int OLED_WIDTH = 128;
const int OLED_HEIGHT = 64;
const int OLED_RESET_PIN = 16;
const int FIRST_OLED_ADDRESS = 0x3C;
const int SECOND_OLED_ADDRESS = 0x3D;

const int PIN_PAIR_COUNT = 4;
const int SDA_PINS[PIN_PAIR_COUNT] = {4, 21, 5, 17};
const int SCL_PINS[PIN_PAIR_COUNT] = {15, 22, 4, 5};

int currentHour = 12;
int currentMinute = 0;
int currentSecond = 0;

unsigned long lastClockUpdateMs = 0;
int oledAddress = FIRST_OLED_ADDRESS;
int oledSdaPin = 4;
int oledSclPin = 15;

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET_PIN);

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  delay(1000);

  // Zresetuj wyswietlacz OLED na plytce TTGO.
  pinMode(OLED_RESET_PIN, OUTPUT);
  digitalWrite(OLED_RESET_PIN, LOW);
  delay(20);
  digitalWrite(OLED_RESET_PIN, HIGH);

  Serial.println();
  Serial.println("OLED time test started.");
  Serial.println("Searching for OLED display...");

  if (!findOledConnection()) {
    Serial.println("No OLED display was found on I2C.");
    Serial.println("The screen may use different pins on this board version.");

    while (true) {
      delay(1000);
    }
  }

  Serial.print("OLED pins found. SDA=");
  Serial.print(oledSdaPin);
  Serial.print(" SCL=");
  Serial.println(oledSclPin);

  Serial.print("OLED address found: 0x");
  Serial.println(oledAddress, HEX);

  // Uruchom wyswietlacz OLED pod wykrytym adresem.
  if (!display.begin(SSD1306_SWITCHCAPVCC, oledAddress)) {
    Serial.println("OLED library could not start the display.");

    while (true) {
      delay(1000);
    }
  }

  display.clearDisplay();
  display.display();

  Serial.println("Time starts from 12:00:00 after every reset.");

  showTime();
}

void loop() {
  unsigned long currentMillis = millis();

  // Sprawdzaj czas bez blokowania programu dlugimi obliczeniami.
  if (currentMillis - lastClockUpdateMs >= ONE_SECOND_MS) {
    lastClockUpdateMs = currentMillis;
    addOneSecond();
    showTime();
  }
}

void addOneSecond() {
  currentSecond++;

  if (currentSecond >= 60) {
    currentSecond = 0;
    currentMinute++;
  }

  if (currentMinute >= 60) {
    currentMinute = 0;
    currentHour++;
  }

  if (currentHour >= 24) {
    currentHour = 0;
  }
}

bool findOledConnection() {
  for (int i = 0; i < PIN_PAIR_COUNT; i++) {
    oledSdaPin = SDA_PINS[i];
    oledSclPin = SCL_PINS[i];

    Serial.print("Checking pins SDA=");
    Serial.print(oledSdaPin);
    Serial.print(" SCL=");
    Serial.println(oledSclPin);

    Wire.end();
    Wire.begin(oledSdaPin, oledSclPin);
    delay(50);

    oledAddress = findOledAddress();

    if (oledAddress != 0) {
      return true;
    }
  }

  return false;
}

int findOledAddress() {
  if (isI2cDevicePresent(FIRST_OLED_ADDRESS)) {
    return FIRST_OLED_ADDRESS;
  }

  if (isI2cDevicePresent(SECOND_OLED_ADDRESS)) {
    return SECOND_OLED_ADDRESS;
  }

  return 0;
}

bool isI2cDevicePresent(int address) {
  Wire.beginTransmission(address);
  byte error = Wire.endTransmission();

  Serial.print("Check address 0x");
  Serial.print(address, HEX);
  Serial.print(": ");

  if (error == 0) {
    Serial.println("device found");
    return true;
  }

  Serial.println("no device");
  return false;
}

void showTime() {
  display.clearDisplay();

  // Ustaw kolor tekstu na bialy, bo wyswietlacz jest monochromatyczny.
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("OLED time test");

  display.setTextSize(2);
  display.setCursor(16, 24);
  printTwoDigits(currentHour);
  display.print(":");
  printTwoDigits(currentMinute);
  display.print(":");
  printTwoDigits(currentSecond);

  // Wyslij przygotowany obraz z pamieci ESP32 na wyswietlacz.
  display.display();

  Serial.print("Current displayed time: ");
  printTwoDigitsToSerial(currentHour);
  Serial.print(":");
  printTwoDigitsToSerial(currentMinute);
  Serial.print(":");
  printTwoDigitsToSerial(currentSecond);
  Serial.println();
}

void printTwoDigits(int value) {
  if (value < 10) {
    display.print("0");
  }

  display.print(value);
}

void printTwoDigitsToSerial(int value) {
  if (value < 10) {
    Serial.print("0");
  }

  Serial.print(value);
}
