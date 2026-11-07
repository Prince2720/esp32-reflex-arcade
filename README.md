# 🕹️ ESP32 Reflex Arcade

<p align="center">
  <img src="https://img.shields.io/badge/Platform-ESP32-blue?style=for-the-badge&logo=espressif" alt="ESP32 Badge">
  <img src="https://img.shields.io/badge/Language-C++%20/%20Arduino-00979D?style=for-the-badge&logo=arduino" alt="Arduino Badge">
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="MIT License">
  <img src="https://img.shields.io/badge/Hardware-Physical%20Computing-orange?style=for-the-badge" alt="Physical Computing">
</p>

An interactive, environment-aware physical arcade console engineered around the **ESP32 DevKit V1**. Moving away from standard mechanical push-buttons, this project integrates contactless IR gesture inputs, ambient light adaptation, capacitive touch controls, and passive motion proximity wake-up.

---

## 🌟 Key Features

* 🖐️ **Contactless Gesture Shielding:** Wave your hand over an **LM393 IR Obstacle Sensor** to trigger an in-game force field.
* 🌘 **Dynamic Dark/Light Mode:** Integrated **LDR** monitors ambient lighting conditions in real-time, automatically flipping the SSD1306 display between standard and inverted contrast modes.
* 🚶‍♂️ **Passive Wake-Up:** An **HC-SR501 PIR sensor** conserves power by putting the console into sleep mode, automatically waking it when human presence is detected nearby.
* ⚡ **Capacitive Movement:** Ultra-responsive lane switching powered by a **TTP223 touch sensor**.
* 🔊 **Retro 8-Bit Audio:** Dedicated active buzzer generating dynamic frequency beeps for score ticks, shield activations, and collisions.
* ⏱️ **Non-Blocking Logic:** Written completely without blocking `delay()` functions, utilizing clean state machines and `millis()` timestamp intervals for smooth frame rendering.

---

## 🛠️ Hardware Bill of Materials (BOM)

| Component | Quantity | Purpose | Logic / Power |
| :--- | :---: | :--- | :--- |
| **ESP32 DevKit V1** (30-pin) | 1 | Microcontroller & Game Logic Engine | 5V / 3.3V Logic |
| **0.96" I2C OLED Display** (SSD1306) | 1 | 128x64 Monochrome Game Rendering | 3.3V / I2C (SDA/SCL) |
| **LM393 IR Obstacle Sensor** | 1 | Contactless Gesture Detection (Shield) | VIN (5V) / Digital Out |
| **TTP223 Capacitive Touch Module** | 1 | Player Input / Movement Toggle | 3.3V / Digital Out |
| **HC-SR501 PIR Motion Sensor** | 1 | Human Presence / Power Management | 5V / Digital Out (3.3V safe) |
| **LDR (Photoresistor) + 10kΩ Resistor** | 1 | Ambient Room Lighting Voltage Divider | 3.3V / Analog Out |
| **Active/Passive Buzzer** | 1 | 8-Bit Audio Feedback | 3.3V / Digital Control |
| **Half-Size Breadboard & Jumper Wires** | 1 | Prototyping & Connections | N/A |

---

## 📌 Pin Configuration & Wiring

| Peripheral Pin | ESP32 Pin | Function | Notes |
| :--- | :--- | :--- | :--- |
| **OLED SDA** | `GPIO 21` | I2C Data | Default ESP32 I2C bus |
| **OLED SCL** | `GPIO 22` | I2C Clock | Default ESP32 I2C bus |
| **TTP223 Touch OUT** | `GPIO 4` | Player Switch Lane | Digital Input (`INPUT_PULLDOWN`) |
| **IR Sensor OUT** | `GPIO 18` | Shield Activate | Powered via `VIN` for stable comparator trigger |
| **PIR Sensor OUT** | `GPIO 19` | Proximity Wake-up | Digital Input |
| **LDR Voltage Divider** | `GPIO 34` | Ambient Light ADC | Read via ADC1 (`analogRead`) |
| **Buzzer (+)** | `GPIO 23` | Sound Output | Digital Output |

> ⚠️ **Important Hardware Note:** Ensure the LM393 IR sensor's VCC pin is connected directly to **VIN (5V USB rail)** rather than 3.3V to ensure stable comparator thresholds and eliminate false sensor triggers.

---

## 🚀 Getting Started

### Prerequisites
* [Arduino IDE](https://www.arduino.cc/en/software) (v2.0 or later)
* ESP32 Board Core installed via the Arduino Boards Manager:
  ```text
  [https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json](https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json)
