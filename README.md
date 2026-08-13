# IOT-based-Tilt-Level-Monitoring-System
# ESP32 Tilt Monitoring & Control System

## Overview

An IoT-based real-time tilt monitoring system developed using an **ESP32 and MPU6050** to detect angular displacement and provide immediate safety alerts. The system displays the tilt angle locally on an **OLED display** and provides remote monitoring through a **Wi-Fi-based web interface**.

## Features

* Real-time tilt angle measurement using MPU6050
* MPU6050 interfaced with ESP32 using **I2C**
* Tilt-angle calculation using accelerometer data
* Software low-pass filtering for smoother readings
* **30° threshold-based SAFE/DANGER detection**
* Buzzer alert during unsafe tilt conditions
* Real-time OLED display
* Wi-Fi connectivity using ESP32
* Embedded web server for remote monitoring
* Browser-based live tilt-angle display

## Hardware

* ESP32 Development Board
* MPU6050 Accelerometer/Gyroscope
* 0.96" SSD1306 OLED Display
* Buzzer
* USB Power Supply

## Software & Technologies

* **Embedded C/C++**
* Arduino IDE
* ESP32
* I2C
* Wi-Fi
* HTTP/WebServer
* MPU6050
* SSD1306 OLED

## System Architecture

```text
        MPU6050
           │
          I2C
           ↓
        ESP32
     ┌─────┼──────┐
     ↓     ↓      ↓
   OLED  Buzzer  Wi-Fi
                  │
                  ↓
            Web Dashboard
```

## Working

1. MPU6050 measures acceleration along the X, Y and Z axes.
2. ESP32 reads the sensor data through I2C.
3. The firmware calculates the tilt angle using accelerometer values.
4. A low-pass filtering technique is applied to reduce sudden fluctuations.
5. The filtered angle is compared with a **30° safety threshold**.
6. If the tilt exceeds the threshold, the buzzer is activated and the OLED displays **DANGER**.
7. Otherwise, the system displays **SAFE**.
8. ESP32 hosts a web server and provides the current tilt value through the `/data` endpoint.
9. A browser periodically requests the latest value and displays the angle remotely.

## Pin Connections

| Component   | ESP32   |
| ----------- | ------- |
| MPU6050 SDA | GPIO 21 |
| MPU6050 SCL | GPIO 22 |
| Buzzer      | GPIO 19 |
| OLED SDA    | GPIO 21 |
| OLED SCL    | GPIO 22 |

## Running the Project

1. Install the required libraries in Arduino IDE.
2. Select the appropriate ESP32 board.
3. Replace the Wi-Fi credentials in the code with your own credentials.
4. Upload `tilt_monitoring.ino` to the ESP32.
5. Open the Serial Monitor at **115200 baud**.
6. Note the IP address printed by the ESP32.
7. Open the IP address in a browser connected to the same Wi-Fi network.
8. Monitor the tilt angle in real time.

## Future Improvements

* Multi-axis/3D tilt monitoring
* Improved filtering such as Kalman filtering
* Mobile application integration
* Cloud-based data logging
* Automatic machine-control/shutdown mechanism
* Additional industrial safety features

## Applications

* Industrial safety monitoring
* Crane and heavy-equipment tilt detection
* Vehicle tilt monitoring
* Robotics and automation
* Construction-site safety
* Structural stability monitoring
