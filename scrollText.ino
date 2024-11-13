#include <MD_Parola.h>     // Include MajicDesigns Parola library
#include <MD_MAX72xx.h>    // Include MajicDesigns MAX72xx LED matrix library
#include <SPI.h>           // Include Arduino SPI library

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW   // Set hardware type for MAX7219
#define MAX_DEVICES 16                      // Total number of modules (8 per row, 2 rows)

#define CS_PIN 10                           // Define Chip Select (CS) pin

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup(void) 
{
  // Initialize the display
  display.begin(2);
  // Set up two independent zones
  display.setZone(0, 8, 15);    // Zone 1 for the bottom row (modules 8-15)
  display.setZone(1, 0, 7);     // Zone 0 for the top row (modules 0-7)
  
  display.setIntensity(1);      // Set brightness (0-15)
  display.displayClear();       // Clear the display
  
  // Define text and scroll effect for each zone
  display.displayZoneText(0, "HEJ", PA_LEFT, 50, 0, PA_SCROLL_LEFT);   // Scroll text on top row
  display.displayZoneText(1, "QUEENS", PA_LEFT, 50, 0, PA_SCROLL_LEFT); // Scroll text on bottom row
}

void loop(void) 
{
  // Animate each zone independently
  if (display.displayAnimate()) {
    // Restart the text display in each zone after scrolling completes
    display.displayReset(0);
    display.displayReset(1);
  }
}