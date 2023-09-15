#include <FastLED.h>

#define NUM_LEDS 6
#define DATA_PIN 10

CRGB leds[NUM_LEDS];



int sound_1 = 4;
int sound_2 = 5;
int sound_3 = 6;
int sound_4 = 7;
int sound_5 = 8;
int sound_6 = 9;


String song;
int randomdelay;

void setup() {
  // put your setup code here, to run once:

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100); // Adjust this value for desired overall brightness
  randomSeed(analogRead(0)); // Seed the random number generator

Serial.begin(9600);
pinMode(sound_1, OUTPUT);
pinMode(sound_2, OUTPUT);
pinMode(sound_3, OUTPUT);
pinMode(sound_4, OUTPUT);
pinMode(sound_5, OUTPUT);
pinMode(sound_6, OUTPUT);

digitalWrite(DATA_PIN, LOW);
digitalWrite(sound_1,HIGH);
digitalWrite(sound_2,HIGH);
digitalWrite(sound_3,HIGH);
digitalWrite(sound_4,HIGH);
digitalWrite(sound_5,HIGH);
digitalWrite(sound_6,HIGH);


Serial.print("All off");
}

void loop() {
  // put your main code here, to run repeatedly:

    song = Serial.available();
    song.trim();
    Serial.print("Song is = ");
    Serial.println(song);
    randomdelay = random(5000,15000);
    delay(randomdelay);
 

Dimmer();
  
  song = random(1,6);
 
 
  if(song=="1")
  {
    digitalWrite(sound_1,LOW);
    digitalWrite(sound_2,HIGH);
    digitalWrite(sound_3,HIGH);
    digitalWrite(sound_4,HIGH);
    digitalWrite(sound_5,HIGH);
    digitalWrite(sound_6,HIGH);
    Serial.println("Track 1");
    delay(5000);
  }

  else if(song=="2")
  {
    digitalWrite(sound_1,HIGH);
    digitalWrite(sound_2,LOW);
    digitalWrite(sound_3,HIGH);
    digitalWrite(sound_4,HIGH);
    digitalWrite(sound_5,HIGH);
    digitalWrite(sound_6,HIGH);
    Serial.println("Track 2");
    delay(2000);
  }

    else if(song=="3")
  {
    digitalWrite(sound_1,HIGH);
    digitalWrite(sound_2,HIGH);
    digitalWrite(sound_3,LOW);
    digitalWrite(sound_4,HIGH);
    digitalWrite(sound_5,HIGH);
    digitalWrite(sound_6,HIGH);
    Serial.println("Track 3");
    delay(6000);
  }

    else if(song=="4")
  {
    digitalWrite(sound_1,HIGH);
    digitalWrite(sound_2,HIGH);
    digitalWrite(sound_3,HIGH);
    digitalWrite(sound_4,LOW);
    digitalWrite(sound_5,HIGH);
    digitalWrite(sound_6,HIGH);
    Serial.println("Track 4");
    delay(2000);
    }

    else if(song=="5")
  {
    digitalWrite(sound_1,HIGH);
    digitalWrite(sound_2,HIGH);
    digitalWrite(sound_3,HIGH);
    digitalWrite(sound_4,HIGH);
    digitalWrite(sound_5,LOW);
    digitalWrite(sound_6,HIGH);
    Serial.println("Track 5");
    delay(3000);
  }

    else if(song=="6")
  {
    digitalWrite(sound_1,HIGH);
    digitalWrite(sound_2,HIGH);
    digitalWrite(sound_3,HIGH);
    digitalWrite(sound_4,HIGH);
    digitalWrite(sound_5,HIGH);
    digitalWrite(sound_6,LOW);
    Serial.println("Track 6");
    delay(3000);
  }

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

void Dimmer() // 
{
// Set LEDs to random color and brightness
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(random(256), random(256), random(256));
    FastLED.show();
    delay(50); // Delay to visually appreciate the random colors
  }

  // Randomly determine whether to blink slowly or quickly
  bool slowBlink = random(2) == 0;

  // Randomly choose the number of LEDs to flicker quickly
  int numLEDsToFlickerQuickly = random(1, 2); // 1 or 2

  // Ensure at least 3 LEDs are turned on and they are unique
  int numLEDsToKeepOn = max(3, random(NUM_LEDS - numLEDsToFlickerQuickly + 1));
  int indices[NUM_LEDS]; // Array to store LED indices
  for (int i = 0; i < NUM_LEDS; i++) {
    indices[i] = i; // Fill the array with indices 0 to NUM_LEDS-1
  }
  shuffleArray(indices, NUM_LEDS); // Shuffle the indices randomly

  // Turn off all LEDs initially
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();

  // Turn on at least 3 unique LEDs with random colors
  for (int i = 0; i < numLEDsToKeepOn; i++) {
    int index = indices[i];
    leds[index] = CRGB(random(256), random(256), random(256)); // Random color
  }

  // Flicker selected LEDs with changing colors
  for (int i = 0; i < numLEDsToFlickerQuickly; i++) {
    int index = random(NUM_LEDS);
    for (int j = 0; j < 10; j++) { // Change colors quickly for 10 iterations
      leds[index] = CRGB(random(256), random(256), random(256)); // Change color
      FastLED.show();
      delay(100); // Delay to control the color change speed
    }
    leds[index] = CRGB::Black; // Turn off the LED
  }

  // Randomly flash some LEDs and dim others
  for (int i = 0; i < NUM_LEDS; i++) {
    if (random(2) == 0) { // 50% chance to flash
      leds[i] = CRGB::White; // Flash with full brightness (white)
      FastLED.show();
      if (slowBlink) {
        delay(random(800, 2000)); // Random delay for slow blinking
      } else {
        delay(random(50, 500)); // Random delay for quick blinking
      }
      leds[i] = CRGB::Black; // Turn off the LED
      FastLED.show();
    } else {
      // Dim the LED to 0 at a lower speed
      for (int b = 255; b >= 0; b--) {
        leds[i].fadeToBlackBy(random(1, 4)); // Random dim speed
        FastLED.show();
        delay(20); // Delay to control the slower dimming speed
      }
    }
  }

}



