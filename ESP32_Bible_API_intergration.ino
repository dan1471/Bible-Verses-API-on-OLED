#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMono9pt7b.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <ESPAsyncWiFiManager.h>
#include <Ticker.h>

// OLED Display Object
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Button pins
const int buttonUpPin = 12;
const int buttonDownPin = 14;
const int buttonSelectPin = 13;
int buttonUpState = 0;
int buttonDownState = 0;
int buttonSelectState = 0;

// Sound pin
const int soundPin = 5;

// WiFi Credentials
const char* ssid = "Droid O'clock";
const char* password = "2024_Kenya";

// URL Endpoint for the API
String URL = "https://bible-api.com/?random=verse";

String verseText;
String verseReference;
int scrollOffset = 0;
int maxScrollOffset = 0;

// Menu variables
const int menuItems = 2;
int selectedItem = 0;
String menu[menuItems] = {"Fetch Verse", "Settings"};

// NTP Client for time synchronization
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000);

// OTA Web Server
AsyncWebServer server(80);
DNSServer dns;

// Idle screen ticker
Ticker ticker;

void setup() {
  Serial.begin(115200);

  // Setup the OLED Display and initialize
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  // Setup buttons
  pinMode(buttonUpPin, INPUT_PULLUP);
  pinMode(buttonDownPin, INPUT_PULLUP);
  pinMode(buttonSelectPin, INPUT_PULLUP);

  // Setup sound pin
  pinMode(soundPin, OUTPUT);

  // Connect to WiFi with error handling
  AsyncWiFiManager wifiManager(&server, &dns);
  displayWiFiConnecting();
  if (!wifiManager.autoConnect("AutoConnectAP")) {
    displayWiFiFailed();
    while (true); // Halt the program if WiFi fails to connect
  }

  // Initialize NTP Client
  timeClient.begin();

  displayWiFiConnected();

  // Start ticker for idle screen
  ticker.attach(10, displayIdleScreen);

  displayMenu();
}

void loop() {
  // Update NTP Client
  timeClient.update();

  // Read button states
  buttonUpState = digitalRead(buttonUpPin);
  buttonDownState = digitalRead(buttonDownPin);
  buttonSelectState = digitalRead(buttonSelectPin);

  // Menu navigation
  if (buttonUpState == LOW) {
    selectedItem = (selectedItem - 1 + menuItems) % menuItems;
    displayMenu();
    delay(200); // Debounce delay
  } else if (buttonDownState == LOW) {
    selectedItem = (selectedItem + 1) % menuItems;
    displayMenu();
    delay(200); // Debounce delay
  } else if (buttonSelectState == LOW) {
    executeMenuAction();
    delay(200); // Debounce delay
  }
}

void fetchVerse() {
  // Display progress bar
  displayProgressBar();

  // Check if WiFi is connected before making the HTTP request
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(URL);
    int httpCode = http.GET();

    if (httpCode > 0) { // Check for HTTP response
      if (httpCode == HTTP_CODE_OK) {
        String JSON_Data = http.getString();
        DynamicJsonDocument doc(2048);
        DeserializationError error = deserializeJson(doc, JSON_Data);
        if (!error) {
          JsonObject obj = doc.as<JsonObject>();
          verseReference = obj["reference"].as<String>();
          verseText = obj["text"].as<String>();
          int textHeight = (verseText.length() / 21 + 1) * 8;
          maxScrollOffset = textHeight - 64;
          scrollOffset = 0;
          displayVerse();
        } else {
          Serial.println("Failed to parse JSON!");
          displayError("JSON Parsing Error");
        }
      } else {
        Serial.printf("HTTP GET failed, error: %d\n", httpCode);
        displayError("HTTP Request Failed");
      }
    } else {
      Serial.printf("HTTP GET request failed with error: %s\n", http.errorToString(httpCode).c_str());
      displayError("HTTP Request Failed");
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
    displayError("No WiFi Connection");
  }

  // Play sound alert
  tone(soundPin, 1000, 200);
}

void displayVerse() {
  ticker.detach(); // Stop idle screen ticker
  display.clearDisplay();
  display.setFont(&FreeMono9pt7b); // Set custom font
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 16);
  display.print("Ref: ");
  display.println(verseReference);
  display.println(verseText);
  display.display();
  ticker.attach(10, displayIdleScreen); // Restart idle screen ticker after 10 seconds
}

void displayMenu() {
  ticker.detach(); // Stop idle screen ticker
  display.clearDisplay();
  display.setFont(&FreeMono9pt7b); // Set custom font
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  for (int i = 0; i < menuItems; i++) {
    if (i == selectedItem) {
      display.print("> ");
    } else {
      display.print("  ");
    }
    display.println(menu[i]);
  }
  display.display();
  ticker.attach(10, displayIdleScreen); // Restart idle screen ticker after 10 seconds
}

void executeMenuAction() {
  if (selectedItem == 0) {
    fetchVerse();
  } else if (selectedItem == 1) {
    displaySettings();
  }
}

void displaySettings() {
  ticker.detach(); // Stop idle screen ticker
  display.clearDisplay();
  display.setFont(&FreeMono9pt7b); // Set custom font
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("Settings Menu");
  display.display();
  delay(2000);
  displayMenu();
}

void displayProgressBar() {
  ticker.detach(); // Stop idle screen ticker
  display.clearDisplay();
  display.setFont(&FreeMono9pt7b); // Set custom font
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Fetching Verse...");
  for (int i = 0; i < 128; i++) {
    display.drawLine(0, 10, i, 10, SSD1306_WHITE);
    display.display();
    delay(10);
  }
}

void displayWiFiConnecting() {
  display.clearDisplay();
  display.setFont(&FreeMono9pt7b); // Set custom font
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 16);
  display.println("Connecting to WiFi...");
  display.display();
}

void displayWiFiConnected() {
  display.clearDisplay();
  display.setFont(&FreeMono9pt7b); // Set custom font
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 16);
  display.println("WiFi Connected!");
  display.display();
}

void displayWiFiFailed() {
  display.clearDisplay();
  display.setFont(&FreeMono9pt7b); // Set custom font
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 16);
  display.println("WiFi Connection Failed");
  display.display();
}

void displayIdleScreen() {
  display.clearDisplay();
  display.setFont(&FreeMono9pt7b); // Set custom font
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  // Display current date and time
  display.setCursor(0, 16);
  display.print("Date: ");
  display.println(timeClient.getFormattedDate());
  display.print("Time: ");
  display.println(timeClient.getFormattedTime());
  
  // Display brand name
  display.setCursor(0, 48);
  display.println("Mr Arduino");
  
  display.display();
}

void displayError(const char* errorMsg) {
  ticker.detach(); // Stop idle screen ticker
  display.clearDisplay();
  display.setFont(&FreeMono9pt7b); // Set custom font
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 16);
  display.println(errorMsg);
  display.display();
  delay(3000);
  displayMenu(); // Return to menu after error display
}
