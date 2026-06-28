#include <WiFi.h>
#include <time.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#if __has_include("wifi_secrets.h")
#include "wifi_secrets.h"
#else
#define WIFI_NAME_VALUE "CHANGE_ME"
#define WIFI_PASSWORD_VALUE "CHANGE_ME"
#endif

const char* WIFI_NAME = WIFI_NAME_VALUE;
const char* WIFI_PASSWORD = WIFI_PASSWORD_VALUE;

const unsigned long SERIAL_BAUDRATE = 115200;
const unsigned long ONE_SECOND_MS = 1000;
const unsigned long WIFI_TIMEOUT_MS = 20000;

const int OLED_WIDTH = 128;
const int OLED_HEIGHT = 64;
const int OLED_RESET_PIN = 16;
const int FIRST_OLED_ADDRESS = 0x3C;
const int SECOND_OLED_ADDRESS = 0x3D;

const int PIN_PAIR_COUNT = 4;
const int SDA_PINS[PIN_PAIR_COUNT] = {4, 21, 5, 17};
const int SCL_PINS[PIN_PAIR_COUNT] = {15, 22, 4, 5};

const char* TIME_ZONE = "CET-1CEST,M3.5.0,M10.5.0/3";
const char* NTP_SERVER = "pool.ntp.org";

unsigned long lastDisplayUpdateMs = 0;
int oledAddress = FIRST_OLED_ADDRESS;
int oledSdaPin = 4;
int oledSclPin = 15;
bool timeIsReady = false;

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
  Serial.println("OLED NTP time test started.");

  if (!initializeDisplay()) {
    while (true) {
      delay(1000);
    }
  }

  showMessage("Connecting", "to WiFi...");

  if (!connectToWiFi()) {
    showMessage("WiFi failed", "Check name/pass");

    while (true) {
      delay(1000);
    }
  }

  showMessage("Getting time", "from internet");
  timeIsReady = initializeTime();

  if (!timeIsReady) {
    showMessage("Time failed", "Try reset");

    while (true) {
      delay(1000);
    }
  }

  showCurrentTime();
}

void loop() {
  unsigned long currentMillis = millis();

  // Aktualizuj ekran raz na sekunde.
  if (currentMillis - lastDisplayUpdateMs >= ONE_SECOND_MS) {
    lastDisplayUpdateMs = currentMillis;
    showCurrentTime();
  }
}

bool initializeDisplay() {
  Serial.println("Searching for OLED display...");

  if (!findOledConnection()) {
    Serial.println("No OLED display was found on I2C.");
    return false;
  }

  Serial.print("OLED pins found. SDA=");
  Serial.print(oledSdaPin);
  Serial.print(" SCL=");
  Serial.println(oledSclPin);

  Serial.print("OLED address found: 0x");
  Serial.println(oledAddress, HEX);

  if (!display.begin(SSD1306_SWITCHCAPVCC, oledAddress)) {
    Serial.println("OLED library could not start the display.");
    return false;
  }

  display.clearDisplay();
  display.display();
  return true;
}

bool connectToWiFi() {
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_NAME);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

  unsigned long startTimeMs = millis();

  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - startTimeMs > WIFI_TIMEOUT_MS) {
      Serial.println("WiFi connection timeout.");
      return false;
    }

    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("WiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}

bool initializeTime() {
  // Ustaw polska strefe czasu razem z automatyczna zmiana czasu letniego.
  configTzTime(TIME_ZONE, NTP_SERVER);

  struct tm timeInfo;

  // Poczekaj maksymalnie 10 sekund na czas z internetu.
  if (!getLocalTime(&timeInfo, 10000)) {
    Serial.println("Could not get time from NTP server.");
    return false;
  }

  Serial.println("Time synchronized.");
  return true;
}

void showCurrentTime() {
  struct tm timeInfo;

  if (!getLocalTime(&timeInfo)) {
    Serial.println("Time is not available.");
    return;
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Current time");

  display.setTextSize(2);
  display.setCursor(16, 20);
  printTwoDigits(timeInfo.tm_hour);
  display.print(":");
  printTwoDigits(timeInfo.tm_min);
  display.print(":");
  printTwoDigits(timeInfo.tm_sec);

  display.setTextSize(1);
  display.setCursor(22, 52);
  display.print(timeInfo.tm_mday);
  display.print(".");
  display.print(timeInfo.tm_mon + 1);
  display.print(".");
  display.print(timeInfo.tm_year + 1900);

  display.display();

  Serial.print("Current time: ");
  printTwoDigitsToSerial(timeInfo.tm_hour);
  Serial.print(":");
  printTwoDigitsToSerial(timeInfo.tm_min);
  Serial.print(":");
  printTwoDigitsToSerial(timeInfo.tm_sec);
  Serial.println();
}

void showMessage(const char* firstLine, const char* secondLine) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 14);
  display.println(firstLine);
  display.setCursor(0, 34);
  display.println(secondLine);
  display.display();
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
