#include <FastLED.h>

#define NUM_LEDS 6
#define DATA_PIN 10

CRGB leds[NUM_LEDS];

int soundPins[] = {4, 5, 6, 7, 8, 9};
int song = 0; // Store the selected song

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100); // Adjust this value for desired overall brightness
  randomSeed(analogRead(0)); // Seed the random number generator

  // Initialize sound pins
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(soundPins[i], OUTPUT);
    digitalWrite(soundPins[i], HIGH); // Turn off all sound modules initially
  }

  Serial.begin(9600);
  Serial.println("All off");
}

// Function to shuffle an array randomly
void shuffleArray(int arr[], int size) {
  for (int i = size - 1; i > 0; i--) {
    int j = random(0, i + 1);
    if (i != j) {
      // Swap elements at positions i and j
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
}

void loop() {
  // Select a random song (1 to 6)
  song = random(1, 7);
  Serial.print("Selected song: ");
  Serial.println(song);

  // Play the selected song
  playSong(song);

  // Run the LED pattern
  Dimmer();
}

void playSong(int songNumber) {
  // Turn off all sound modules initially
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(soundPins[i], HIGH);
  }

  // Turn on the sound module corresponding to the selected song
  if (songNumber >= 1 && songNumber <= NUM_LEDS) {
    digitalWrite(soundPins[songNumber - 1], LOW);
    Serial.print("Playing song ");
    Serial.println(songNumber);
  } else {
    Serial.println("Invalid song number");
  }

  // Add any additional logic for sound playback here
}

void Dimmer() {
  // Set one LED to be always on
  int alwaysOnLED = random(NUM_LEDS);
  bool alwaysOnBlink = false; // Flag to control blinking of always-on LED
  int alwaysOnColorChangeDelay = random(2000, 5000); // Random delay for color change

  // Randomly determine whether to blink slowly or quickly
  bool slowBlink = random(2) == 0;

  // Randomly choose the number of LEDs to flicker quickly
  int numLEDsToFlickerQuickly = random(1, 2); // 1 or 2

  // Ensure at least 2 more LEDs are turned on and they are unique
  int numLEDsToKeepOn = max(2, random(NUM_LEDS - numLEDsToFlickerQuickly));
  int indices[NUM_LEDS - 1]; // Array to store LED indices except the always-on LED

  // Fill the array with indices 0 to NUM_LEDS-1, excluding alwaysOnLED
  int j = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i != alwaysOnLED) {
      indices[j] = i;
      j++;
    }
  }

  shuffleArray(indices, NUM_LEDS - 1); // Shuffle the indices randomly

  // Turn on at least 2 unique LEDs with random colors
  for (int i = 0; i < numLEDsToKeepOn; i++) {
    int index = indices[i];
    leds[index] = CRGB(random(256), random(256), random(256)); // Random color
  }

  // Flicker selected LEDs with changing colors
  for (int i = 0; i < numLEDsToFlickerQuickly; i++) {
    int index = random(NUM_LEDS - 1); // Random index except the always on LED
    for (int j = 0; j < 10; j++) { // Change colors quickly for 10 iterations
      leds[indices[index]] = CRGB(random(256), random(256), random(256)); // Change color
      FastLED.show();
      delay(100); // Delay to control the color change speed
    }
    leds[indices[index]] = CRGB::Black; // Turn off the LED
  }

  // Blink or fade the always-on LED
  if (alwaysOnBlink) {
    if (slowBlink) {
      delay(random(800, 2000)); // Random delay for slow blinking
    } else {
      delay(random(50, 500)); // Random delay for quick blinking
    }
    alwaysOnBlink = !alwaysOnBlink;
  } else {
    // Dim the always-on LED to 0 at a lower speed
    for (int b = 255; b >= 0; b--) {
      leds[alwaysOnLED].fadeToBlackBy(random(1, 4)); // Random dim speed
      FastLED.show();
      delay(20); // Delay to control the slower dimming speed
    }
    delay(alwaysOnColorChangeDelay); // Delay before changing the color of always-on LED
    leds[alwaysOnLED] = CRGB(random(256), random(256), random(256)); // Random color
    FastLED.show();
    alwaysOnColorChangeDelay = random(2000, 5000); // Random delay for color change
  }
}
