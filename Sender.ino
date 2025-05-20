#include <esp_now.h>
#include <WiFi.h>

uint8_t receiverMac[] = {0x24, 0x6F, 0x28, 0xXX, 0xXX, 0xXX}; // Replace with receiver's MAC
const int buttonPin = 4;
bool lastState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (!esp_now_add_peer(&peerInfo)) {
    Serial.println("Receiver added");
  }

  esp_now_register_send_cb([](const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
  });
}

void loop() {
  bool currentState = digitalRead(buttonPin);
  if (currentState == LOW && lastState == HIGH) {
    const char *msg = "BUTTON_PRESSED";
    esp_now_send(receiverMac, (uint8_t *)msg, strlen(msg) + 1);
    Serial.println("Button Pressed: Message Sent");
    delay(500);
  }
  lastState = currentState;
}
