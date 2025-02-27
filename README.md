
# 🌱 Plant Monitoring System

A **Smart Plant Monitoring System** using **Arduino/ESP8266**, **DHT11 sensor**, **LDR**, and **soil moisture sensor** to automate irrigation and monitor environmental conditions. The system sends data to **Blynk** for remote monitoring and triggers a **buzzer** if critical thresholds are met.

## 📷 Project Overview
![Project Banner](https://your-image-url.com)  <!-- Replace with actual image URL -->

## 🚀 Features
- 📡 **Real-time monitoring** of **temperature, humidity, and soil moisture**.
- 🌞 **Light Intensity Detection** using an **LDR**.
- 💧 **Automatic irrigation control** using a **relay**.
- 🔔 **Buzzer alerts** for dry soil or disconnection.
- 📱 **Blynk App integration** for remote control and monitoring.
- 🖥️ **LCD Display (16x2 I2C)** for real-time sensor values.

## 🛠️ Hardware Requirements
- **ESP8266 / Arduino Uno**
- **DHT11 Temperature & Humidity Sensor**
- **Soil Moisture Sensor**
- **LDR (Light Dependent Resistor)**
- **Relay Module**
- **Buzzer**
- **16x2 LCD with I2C Module**
- **Jumper Wires, Breadboard**
- **5V Power Supply**

🎮 Blynk Dashboard Setup

1. Download the Blynk App from the Play Store or App Store.
2. Create a new project and select ESP8266.
3. Add Widgets:

  -Value Displays (V1 = Humidity, V2 = Temperature, V3 = Soil Moisture)
  
  -Switch (for manual irrigation control)

  -Notification Alert

4. Copy the Blynk Auth Token and update it in the code.

## 🚨 Alert Conditions


Soil Moisture < 20% → Buzzer ON, Irrigation ON.

Soil Moisture > 90% → Irrigation OFF.

LDR Value = 0 → Circuit Disconnected Alert.



