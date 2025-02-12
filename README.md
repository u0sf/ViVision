# ViVision

## Overview
ViVision is an ESP8266-based project that utilizes the TCS34725 color sensor to detect colors and display real-time RGB readings on a web server. The system also attempts to match the detected color with predefined color names for better readability.

## Features
- Reads color data (Red, Green, Blue) from the TCS34725 sensor.
- Converts RGB values into human-readable color names.
- Hosts a web server on ESP8266 to display real-time color readings.
- Dynamically updates color data on the webpage.

## Components Required
- ESP8266 (e.g., NodeMCU, Wemos D1 Mini)
- TCS34725 Color Sensor
- Jumper Wires
- Power Source (e.g., USB cable or battery)

## Wiring Connections
### TCS34725 Sensor:
- **VCC** → 3.3V on ESP8266
- **GND** → GND
- **SDA** → D2 (GPIO4)
- **SCL** → D1 (GPIO5)

## Installation & Setup
### 1. Install Required Libraries:
Ensure the following libraries are installed in the Arduino IDE:
- `Adafruit_TCS34725` (for sensor communication)
- `ESP8266WiFi` (for WiFi connectivity)
- `ESP8266WebServer` (for running the web server)

### 2. Flash the Code
Upload the Arduino sketch to ESP8266 using the Arduino IDE.

### 3. Connect to WiFi
Modify the SSID and PASSWORD in the code to connect to your local network.

### 4. Access the Web Server
Once the ESP8266 is connected, it will display its IP address in the serial monitor. Open a web browser and enter this IP to view the color data.

## How It Works
1. The ESP8266 continuously reads color data from the TCS34725 sensor.
2. The RGB values are compared against a predefined list of common colors.
3. The ESP8266 hosts a web server where the detected color is displayed along with its RGB values.
4. The webpage refreshes dynamically to show real-time color updates.

## Future Improvements
- Add support for additional color spaces (HSV, HEX).
- Improve color matching accuracy.
- Enhance the web UI for a better user experience.
- Implement MQTT for IoT integration.

## License
This project is open-source under the MIT License.

