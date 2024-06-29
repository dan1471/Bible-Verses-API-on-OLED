###📖 Random Bible Verses Display on OLED

Welcome to the Random Bible Verses Display project! This project fetches and displays random Bible verses from the Bible API on an OLED display every minute. It includes features for scrolling through the verses using physical buttons. Perfect for a daily dose of inspiration!
✨ Features

   - Displays a new random Bible verse every minute.
   - Scrollable text using up and down buttons.
    - Simple setup with WiFi credentials.
    - Clear and readable text on a 128x64 OLED display.

###🛠 Hardware Requirements

   - ESP32 Development Board
    -128x64 OLED Display (e.g., Adafruit SSD1306)
    -Push Buttons (x2)
    -Connecting Wires

###📋 Installation

   - Clone the Repository

    bash

git clone https://github.com/your-username/Bible-Verses-API-on-OLED.git
cd Bible-Verses-API-on-OLED

Set Up Your Development Environment

    Install the Arduino IDE if you haven't already.
    Install the required libraries:
        Adafruit GFX Library
        Adafruit SSD1306 Library
        ArduinoJson Library

Connect Your Hardware

    Connect the OLED display to your ESP32.
    Connect the buttons to the specified GPIO pins.

Configure WiFi Credentials

    Open main.ino and update the WiFi SSID and password:

    cpp

        const char* ssid = "Your_SSID";
        const char* password = "Your_Password";

    Upload the Code
        Select your ESP32 board and the correct COM port in the Arduino IDE.
        Upload the code to your ESP32.

🔄 How It Works

    WiFi Connection
        The ESP32 connects to your WiFi network using the provided credentials.

    Fetching Verses
        A random Bible verse is fetched from the Bible API every minute.

    Displaying Verses
        The verse is displayed on the OLED screen. You can scroll through the text using the up and down buttons.

🚀 Quick Start

    Power up your ESP32 and ensure it's connected to your WiFi network.
    The OLED display will start showing a new random Bible verse every minute.
    Use the up and down buttons to scroll through longer verses.

🖼 Project Showcase

OLED Display with Bible Verse
🤝 Contributing

Feel free to fork this repository and contribute! If you encounter any issues or have suggestions for improvements, please open an issue or submit a pull request.
📄 License

This project is licensed under the MIT License. See the LICENSE file for details.
🌟 Acknowledgements

Special thanks to fredmunyao1 for the original project this was forked from!
