# BCA189-ESP32-I2C-Multi-Sensor-System

This project demonstrates an I2C multi-module system using ESP32.

## Modules Used

- DS3231 RTC (0x68)
- MPU6050 (0x69)
- OLED SSD1306 (0x3C)

## Features

- Real-time clock display
- Accelerometer & gyroscope readings
- OLED display output
- Serial monitor output

## Wiring

ESP32:
- SDA → GPIO 21
- SCL → GPIO 22

## Libraries Required

- RTClib
- Adafruit MPU6050
- Adafruit GFX
- Adafruit SSD1306
- Adafruit Unified Sensor
