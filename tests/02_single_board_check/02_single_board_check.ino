const unsigned long SERIAL_BAUDRATE = 115200;
const unsigned long MESSAGE_INTERVAL_MS = 2000;

unsigned long messageCounter = 0;

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  delay(1000);

  // Pokaz pusty wiersz, zeby start programu byl czytelny w Monitorze portu.
  Serial.println();

  // Pokaz podstawowe informacje o plytce ESP32.
  Serial.println("Single board check");
  Serial.println("==================");
  Serial.print("Chip model: ");
  Serial.println(ESP.getChipModel());
  Serial.print("CPU frequency MHz: ");
  Serial.println(ESP.getCpuFreqMHz());
  Serial.print("Flash size bytes: ");
  Serial.println(ESP.getFlashChipSize());
  Serial.println();

  // Ten test nie uruchamia LoRa i jest bezpieczny bez anteny.
  Serial.println("LoRa radio is not started in this sketch.");
  Serial.println("No antenna is needed for this test.");
  Serial.println();
}

void loop() {
  messageCounter++;

  // Pokaz, ze program caly czas dziala.
  Serial.print("Board is running. Message ");
  Serial.println(messageCounter);

  // Poczekaj dwie sekundy przed kolejnym komunikatem.
  delay(MESSAGE_INTERVAL_MS);
}
