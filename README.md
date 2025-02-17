# 📡 Project: Audio Wattmeter with OLED Display and Temperature Sensor

## 📖 Description

This project aims to measure the output power of an audio amplifier based on a 4 Ω or 8 Ω load.
The values are displayed on two 0.96" OLED screens via the I2C protocol.
A **DS18B20** sensor monitors the temperature, activating a fan if a critical threshold is reached.

The system is based on an **Arduino Nano**, utilizing a **diode bridge**, a **voltage divider**, and an **analog reading** for voltage measurement.

The load can operate up to >250W.

## 🛠️ Features

- Power measurement and display for **two separate channels** (left/right)
- Display on **two OLED screens**
- Activation of a cooling fan based on temperature

### To-do

- **Real-time monitoring** via serial output

## 📷 Project Photos

![IMG_4635](https://github.com/user-attachments/assets/8eafffcc-8349-46ea-a188-e03a429097c2)

![IMG_4634(1)(1)(1)](https://github.com/user-attachments/assets/81507dc6-3a02-46e4-b54d-dbf04c9cb168)

## 🔧 Bill of Materials (BOM)

| Quantity | Component                | Reference / Value |
| -------- | ------------------------ | ----------------- |
| 1        | Arduino Nano             | ATmega328P        |
| 1        | Temperature Sensor  | DS18B20       |
| 2        | 0.96" OLED I2C Display   | SSD1306           |
| 1        | Diode Bridge             | 1N4007 x4         |
| 1        | Filtering Capacitor      | 20uF 50V          |
| 2        | Voltage Divider Resistors | 82KΩ + 10KΩ      |
| 1        | 5V Fan                  | 120mm        |
| 1        | Fan Relay                | 5V               |
| 2        | Security Relay                | 5V               |
| 2        | Audio Connection Terminals | Jack / Banana  |
| 4        | 100W Resistor | 2.7Ω  |
| 2        | 100W Resistor | 15Ω  |
| 2        | 100W Resistor | 2.5KΩ  |
| 2        | SPDT Switch | 1321S ON ON  |
| 1        | LED + resistor | Red 2.5mm + 10kΩ  |

## 📜 Installation & Wiring

1. **Connections**:
   - **DS18B20** to **D12**
   - **OLED Displays** to **I2C (A4, A5)**
   - **Voltage Divider** to **A0 and A1**
   - **Fan Output** to **D4**
   - **Security relay R channel** to **D2**
   - **Security relay L channel** to **D3**
   - **Temperature indicator LED** to **D8**
2. **Upload the program** via Arduino IDE
3. **Observe the displayed values** on the OLEDs

---

### Inspirations :

http://tolisdiy.com/2021/03/30/compact-stereo-dummy-load-for-amplifier-testing/
https://andydoz.blogspot.com/2016/04/arduino-audio-wattmeter.html
