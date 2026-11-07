# 📌 ESP32 Reflex Arcade — Pinout & Hardware Architecture

This document details the exact hardware wiring, power distribution rails, and GPIO configurations for the **ESP32 Reflex Arcade** console.

---

## ⚡ Power Distribution Architecture

| Rail | Voltage Level | Connected Peripherals | Notes |
| :--- | :---: | :--- | :--- |
| **VIN** | ~5.0V (USB VBUS) | LM393 IR Obstacle Sensor, HC-SR501 PIR Sensor | Supplies adequate headroom for comparator circuits |
| **3V3** | 3.3V (ESP32 LDO) | SSD1306 OLED, TTP223 Touch Sensor, LDR Divider | Standard ESP32 CMOS logic level rail |
| **GND** | 0V (Common Ground) | All modules, sensors, and passive components | Must share a single, unified breadboard ground plane |

> ⚠️ **Critical Power Rule:**  
> The **LM393 IR Obstacle Sensor** must be powered from **VIN (5V)**. Running it on 3.3V often starves the LM393 comparator reference voltage, leading to persistent floating reads and false shield triggers.

---

## 🗺️ Master Pin Mapping Table

| Component | Component Pin | ESP32 GPIO | Direction | Signal Type / Logic | Hardware Notes |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **SSD1306 OLED** | `VCC` | `3V3` | Power | 3.3V DC | Screen power supply |
| | `GND` | `GND` | Power | 0V Ground | Common ground |
| | `SCL` | `GPIO 22` | Output | I2C Clock | Hardware I2C Master |
| | `SDA` | `GPIO 21` | In / Out | I2C Data | Hardware I2C Data |
| **TTP223 Touch** | `VCC` | `3V3` | Power | 3.3V DC | Touch pad supply |
| | `GND` | `GND` | Power | 0V Ground | Common ground |
| | `Q / OUT` | `GPIO 4` | Input | Digital (Active-HIGH) | Configured with internal pull-down |
| **LM393 IR Sensor** | `VCC` | `VIN` | Power | ~5.0V DC | High-threshold supply |
| | `GND` | `GND` | Power | 0V Ground | Common ground |
| | `OUT` | `GPIO 18` | Input | Digital (Active-LOW) | Pulls LOW when hand gesture is detected |
| **HC-SR501 PIR** | `VCC` | `VIN` | Power | ~5.0V DC | PIR sensor operating power |
| | `GND` | `GND` | Power | 0V Ground | Common ground |
| | `OUT` | `GPIO 19` | Input | Digital (Active-HIGH) | Output signal is 3.3V logic compliant |
| **LDR Sensor** | Node `LDR/10k` | `GPIO 34` | Input | Analog Voltage | Input-only ADC1 pin (0 - 4095) |
| **Active Buzzer** | `VCC / (+)` | `GPIO 23` | Output | Digital Pulse | Switched HIGH/LOW for audio beeps |
| | `GND / (-)` | `GND` | Power | 0V Ground | Common ground return |

---

## 📐 Circuit Detail & Voltage Dividers

### 1. LDR Ambient Light Sensor Circuit
```text
           3V3 (3.3V)
               │
              [ ]  LDR (Photoresistor)
               │
               ├───► To ESP32 GPIO 34 (ADC1_CH6)
               │
             
               │
              GND (0V)
