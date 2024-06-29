#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Display Object
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Button pins
const int buttonUpPin = 12;
const int buttonDownPin = 14;
const int buttonSelectPin = 13;
int buttonUpState = 0;
int buttonDownState = 0;
int buttonSelectState = 0;

// WiFi Credentials
const char* ssid = "Droid O'clock ";
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

void setup() {
  Serial.begin(115200);

  // Setup the OLED Display and initialize
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Setup buttons
  pinMode(buttonUpPin, INPUT_PULLUP);
  pinMode(buttonDownPin, INPUT_PULLUP);
  pinMode(buttonSelectPin, INPUT_PULLUP);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  displayWiFiConnecting();
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
  }
  if (WiFi.status() == WL_CONNECTED) {
    displayWiFiConnected();
  } else {
    displayWiFiFailed();
  }

  displayMenu();
}

void loop() {
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

  // Wait for WiFi connection
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(URL);
    int httpCode = http.GET();

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
      }
    } else {
      Serial.printf("HTTP GET request failed with error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}

void displayVerse() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, -scrollOffset);
  display.print("Reference: ");
  display.println(verseReference);
  display.println(verseText);
  display.display();
}

void displayMenu() {
  display.clearDisplay();
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
}

void executeMenuAction() {
  if (selectedItem == 0) {
    fetchVerse();
  } else if (selectedItem == 1) {
    displaySettings();
  }
}

void displaySettings() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("Settings Menu");
  display.display();
  delay(2000);
  displayMenu();
}

void displayProgressBar() {
  display.clearDisplay();
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
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Connecting to WiFi...");
  display.display();
}

void displayWiFiConnected() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("WiFi Connected!");
  display.display();
}

void displayWiFiFailed() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("WiFi Connection Failed");
  display.display();
}
