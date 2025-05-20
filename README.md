# ESP32 Button-to-Signal Communication (ESP-NOW)

This project uses two ESP32 boards:
- **Sender** with a button
- **Receiver** with an LED/output pin

When the button is pressed on the sender ESP32, the receiver instantly turns on an LED for 1 second using ESP-NOW.

---

## 📦 Requirements
- 2x ESP32 Boards
- 1x Push Button
- 1x LED + Resistor (or any output pin)
- Arduino IDE with ESP32 board package

---

## 🛠️ Setup Instructions

### 🔌 Hardware
**Sender (Button ESP32):**
- Button between `GPIO 4` and GND

**Receiver (LED ESP32):**
- LED connected to `GPIO 2` and GND via a resistor

---

## 🔗 Step-by-Step Guide

### 1. Get the Receiver MAC Address
- Flash the `receiver.ino` sketch.
- Open Serial Monitor and find the MAC address of the receiver using:
```cpp
Serial.println(WiFi.macAddress());
