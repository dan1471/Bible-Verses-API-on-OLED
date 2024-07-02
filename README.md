 

## Contributing

## Feel free to  send to me some money to +254703778685
# Arduino OLED Bible Verse Display

This project uses an ESP32/ESP8266 microcontroller to fetch random Bible verses from an online API and display them on an OLED screen. The device also shows the current date and time when idle and includes features like WiFi credential management via a smartphone, sound alerts, and smooth transitions between verses.

## Features

- Display random Bible verses from the Bible API
- Show current date, time, and brand name when idle
- Sound alerts for key actions
- OTA updates to change WiFi credentials via a smartphone without hardcoding
- Smooth transitions for better user experience

## Hardware Required

- ESP32 or ESP8266 microcontroller
- OLED Display (SSD1306)
- Push buttons (x3)
- Buzzer or speaker
- Breadboard and connecting wires

## Libraries Required

Install the following libraries via Arduino Library Manager:

- `WiFi`
- `HTTPClient`
- `ArduinoJson`
- `Wire`
- `Adafruit GFX Library`
- `Adafruit SSD1306`
- `NTPClient`
- `WiFiUdp`
- `ESPAsyncWebServer`
- `AsyncTCP` (ESP32) or `ESPAsyncTCP` (ESP8266)
- `ESPAsyncWiFiManager`
- `Ticker`
- `ESP8266Tone` (if using ESP8266)

## Circuit Diagram

Connect the components as follows:

- **OLED Display**
  - VCC to 3.3V
  - GND to GND
  - SCL to D1 (ESP8266) or SCL (ESP32)
  - SDA to D2 (ESP8266) or SDA (ESP32)

- **Buttons**
  - Button 1 (Up) to GPIO 12 and GND
  - Button 2 (Down) to GPIO 14 and GND
  - Button 3 (Select) to GPIO 13 and GND

- **Buzzer**
  - Positive to GPIO 5
  - Negative to GND

## Setup Instructions

1. **Clone the Repository**

   ```sh
   git clone https://github.com/dan1471/Bible-Verses-API-on-OLED.git
   cd Arduino-OLED-Bible-Verse-Display
    Open the Project in Arduino IDE

2. **Open Arduino-OLED-Bible-Verse-Display.ino in the Arduino IDE.**

    - Install Required Libraries

    - Go to Sketch > Include Library > Manage Libraries... and install the required libraries listed above.

    - Upload the Code

3.**Connect your ESP32/ESP8266 to your computer and select the appropriate board and port in the Arduino IDE. Then click the upload button.**

    - Connect to WiFi
       - After uploading the code, the device will create a WiFi access point named "AutoConnectAP".
       - Connect to this WiFi network using your smartphone or computer.
       - Open a web browser and navigate to 192.168.4.1.
       - Enter your WiFi credentials and save them.

 4.**Using the Device**
        - Buttons: Use the buttons to navigate the menu and fetch new Bible verses.
        - Sound Alert: A sound will play when fetching a new verse.
        - Idle Screen: The display will show the current date, time, and brand name when idle.

 5.**Customization**

You can customize the project by modifying the following sections in the code:

    - API Endpoint: Change the URL variable to fetch verses from a different source.
    -  Font and Display Settings: Adjust the font, text size, and contrast in the displayVerse(), displayMenu(), and displayIdleScreen() functions.

