const unsigned long SERIAL_BAUDRATE = 115200;
const unsigned long MESSAGE_INTERVAL_MS = 1000;

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  delay(1000);

  Serial.println();
  Serial.println("========================");
  Serial.println("Pierwszy program dziala!");
  Serial.println("========================");
}

void loop() {
  // Wyslij prosty komunikat do Monitora portu szeregowego.
  Serial.println("ESP32 zyje :)");

  // Poczekaj sekunde przed kolejnym komunikatem.
  delay(MESSAGE_INTERVAL_MS);
}
