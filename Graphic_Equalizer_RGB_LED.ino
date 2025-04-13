// Added comments for clarity and improved readability
#include <FastGPIO.h>
#include "FastLED.h"

// Define the number of LEDs and the data pin
#define NUM_LEDS 39
#define DATA_PIN 3

// Define analog and digital pins
byte analogPin = 0;
byte strobePin = 2;
byte resetPin = 3;

// Array to hold spectrum values
byte spectrumValue[8];

// LED array
CRGB leds[NUM_LEDS];
byte lead_dot = 0;

void setup() {
  // Initialize the LED strip
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);

  // Set the strobe pin to LOW initially
  FastGPIO::Pin<2>::setOutput(LOW);
}

void loop() {
  // Reset the strobe pin
  FastGPIO::Pin<2>::setOutput(HIGH);
  FastGPIO::Pin<2>::setOutput(LOW);

  // Read spectrum values
  for (byte j = 0; j <= 7; j++) {
    FastGPIO::Pin<4>::setOutput(LOW);
    delayMicroseconds(30); // Allow the output to settle
    spectrumValue[j] = map(analogRead(analogPin), 20, 1023, 0, 255);
    FastGPIO::Pin<4>::setOutput(HIGH);
  }

  // Check if values are below noise level
  if (isBelowNoiseLevel()) {
    blank();
  } else {
    updateLEDs();
  }
}

// Function to check if spectrum values are below noise level
bool isBelowNoiseLevel() {
  for (byte i = 0; i < 6; i++) {
    if (spectrumValue[i] > 17) {
      return false;
    }
  }
  return true;
}

// Function to update LEDs based on spectrum values
void updateLEDs() {
  for (byte i = 0; i <= 5; i++) {
    leds[i] = CRGB::Gold;
    leds[i].nscale8_video(spectrumValue[0]);
  }
  for (byte i = 6; i <= 11; i++) {
    leds[i] = CRGB::Blue;
    leds[i].nscale8_video(spectrumValue[1]);
  }
  for (byte i = 12; i <= 18; i++) {
    leds[i] = CRGB::Red;
    leds[i].nscale8_video(spectrumValue[2]);
    FastLED.show();
  }
  for (byte i = 19; i <= 24; i++) {
    leds[i] = CRGB::Green;
    leds[i].nscale8_video(spectrumValue[3]);
  }
  for (byte i = 25; i <= 30; i++) {
    leds[i] = CRGB::Purple;
    leds[i].nscale8_video(spectrumValue[4]);
  }
  for (byte i = 31; i <= 39; i++) {
    leds[i] = CRGB::Yellow;
    leds[i].nscale8_video(constrain(spectrumValue[5] + spectrumValue[6] - 20, 0, 255));
    FastLED.show();
  }
}

// Function to turn off all LEDs
void blank() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

// Function to create a sine wave effect
void sine() {
  int bpm = 20;
  leds[lead_dot].b = 50;
  lead_dot = beatsin8(bpm, 0, NUM_LEDS);
  FastLED.show();
  EVERY_N_MILLISECONDS(100) {
    fadeToBlackBy(leds, NUM_LEDS, 64);
  }
}
