#include <MD_Parola.h>      // Include Parola library for LED matrix control
#include <MD_MAX72xx.h>     // Include MAX72xx library for LED matrix control
#include <SPI.h>            // Include SPI library for Arduino
#include <WiFiS3.h>         // Include WiFi library for Arduino Uno R4 WiFi

// LED Matrix settings
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 16
#define CS_PIN 10

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// WiFi credentials
const char* ssid = "RelationBrand";
const char* password = "33knall!hatt";

void setup(void) {
  Serial.begin(115200);
  display.begin(2);                   // Initialize display with two zones
  display.setZone(0, 8, 15);          // Zone 1: bottom row (modules 8-15)
  display.setZone(1, 0, 7);           // Zone 0: top row (modules 0-7)
  display.setIntensity(1);            // Set brightness
  display.displayClear();             // Clear the display

  // Display initial messages
  display.displayZoneText(0, "T-CENTRALEN", PA_LEFT, 50, 0, PA_NO_EFFECT);   
  display.displayZoneText(1, "Entren mot Katarinavägen stänger tidigare söndagar-torsdagar 27 okt – 3 december", PA_LEFT, 1, 0, PA_SCROLL_LEFT); 

  // Check if the WiFi module is available
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi module failed to initialize!");
    while (true);  // Halt execution if WiFi module isn't found
  }

  // Attempt to connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
  printWifiStatus();
}

void loop(void) {
  // Only animate LED matrix display in the loop
  if (display.displayAnimate()) {
    // Restart scrolling message on Zone 1
    if (display.getZoneStatus(1)) {
      display.displayReset(1);
    }
  }

  // Optional: Check WiFi connection status every loop
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected. Attempting to reconnect...");
    WiFi.begin(ssid, password);
  }
  
  delay(1000);  // Adjust as needed for updating intervals
}

void printWifiStatus() {
  // Print WiFi connection details
  Serial.print("Connected to SSID: ");
  Serial.println(WiFi.SSID());

  // Display IP address and RSSI (signal strength)
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}