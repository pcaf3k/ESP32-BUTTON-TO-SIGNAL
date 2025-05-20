#include <esp_now.h>
#include <WiFi.h>

const int outputPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, LOW);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb([](const uint8_t *mac, const uint8_t *incomingData, int len) {
    String msg = String((char *)incomingData);
    Serial.println("Received: " + msg);
    if (msg == "BUTTON_PRESSED") {
      digitalWrite(outputPin, HIGH);
      delay(1000); // Keep LED ON for 1s
      digitalWrite(outputPin, LOW);
    }
  });
}

void loop() {
  // nothing here
}
