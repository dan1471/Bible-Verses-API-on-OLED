 # Bible Verses on OLED

This project fetches random Bible verses from the [Bible API](https://bible-api.com) and displays them on an OLED screen using an ESP32 microcontroller. It also includes a simple user interface for navigating through different menu options.

## Features

- **WiFi Connection Status:**
  - Displays connection status while connecting to WiFi.
  - Shows a message when WiFi is connected or if the connection fails.

- **Fetch Random Bible Verse:**
  - Fetches a random Bible verse from the Bible API.
  - Displays the verse and its reference on the OLED screen.
  - Supports scrolling through long verses using buttons.

- **User Interface (UI):**
  - Simple menu system for navigating through different options.
  - Progress bar displayed while fetching the verse.
  - Visual feedback for button presses.

- **Settings Menu:**
  - Placeholder for future settings options.

## Hardware Requirements

- ESP32 microcontroller
- 128x64 OLED display (I2C)
- Push buttons (3x) for menu navigation

## Wiring Diagram

| ESP32 Pin | OLED Pin | Button (Up) | Button (Down) | Button (Select) |
|-----------|----------|-------------|---------------|-----------------|
| 3.3V      | VCC      | 12          | 14            | 13              |
| GND       | GND      | GND         | GND           | GND             |
| 21        | SDA      |             |               |                 |
| 22        | SCL      |             |               |                 |

## Software Requirements

- Arduino IDE
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) library
- [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library) library
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson) library

## Installation

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/yourusername/Bible-Verses-on-OLED.git
   cd Bible-Verses-on-OLED
    Open the project in Arduino IDE:
        File -> Open -> Select Bible-Verses-on-OLED.ino

 2.**Install Required Libraries:**
       - Open Arduino IDE.
        -Go to Sketch -> Include Library -> Manage Libraries.
        -Search for and install Adafruit SSD1306, Adafruit GFX, and ArduinoJson.

 3.**Update WiFi Credentials:**
        -Open Bible-Verses-on-OLED.ino.
        -Update the ssid and password variables with your WiFi credentials.

 3.**Upload the Code:**
        -Connect your ESP32 to your computer.
        -Select the appropriate board and port from the Tools menu.
        -Click the upload button.

4.**Usage**

    -Power on the ESP32:
        -The OLED display will show the WiFi connection status.

    -Navigate the Menu:
        -Use the Up and Down buttons to navigate through the menu.
        -Press the Select button to choose an option.

5.**Fetch and Display Bible Verse:**
        -Select the Fetch Verse option from the menu.
        -The OLED will display a progress bar while fetching the verse.
        -Once fetched, the verse and its reference will be displayed.
        -Use the Up and Down buttons to scroll through long verses.

6.**Contributing**

**Contributions are welcome! Please feel free to submit a Pull Request.**
