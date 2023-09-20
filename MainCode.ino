#include <FastLED.h>


/************************
 * Sound 1 - Lasers
 * Sound 2 - Air Jet movement
 * Sound 3 - Warning Siren 
 * Sound 4 - Overload
 * Sound 5 - Electricity
 * Sound 6 - Robot
 ************************/

#define COLOR_ORDER GRB
#define CHIPSET     WS2812
#define BRIGHTNESS  255
#define FRAMES_PER_SECOND 60

int soundPins[] = {4, 5, 6, 7, 8, 9};
const int numSounds = 6;
const int NUM_LEDS = 8;
const int ledPin = 10;
bool gReverseDirection = false;

int colorPicker1;
int colorPicker2;
int colorPicker3;
int colorPicker4;

CRGB leds[NUM_LEDS];
CRGB colors[] = {CRGB::White, CRGB::Yellow, CRGB::Blue};

int randomDelay;
unsigned long lastSoundTime = 0;
unsigned long animationStartMillis[NUM_LEDS];
unsigned long animationDuration[NUM_LEDS];
unsigned long maxBrightnessDuration = 100; // Maximum brightness duration in milliseconds
int minDelay = 1500; // 2.5 minutes
int maxDelay = 3000; // 5 minutes
char *Tracks[] = {"Lasers","Jets","Warning","Overload","Electricity","Robot"};
int randoTrack;

void setup() 
{

FastLED.addLeds<CHIPSET, ledPin, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
randomSeed(analogRead(0)); // Initialize random seed
FastLED.show(); // Initialize LED with all LEDs off

for (int i =0; i < numSounds; i++){
  pinMode(soundPins[i], OUTPUT);
  digitalWrite(soundPins[i],HIGH);
  //  turn off sounds on start

}

Serial.begin(9600);
}


void loop() {

  unsigned long currentMillis = millis();
  
if (currentMillis - lastSoundTime >= randomDelay) {
    randomDelay = random(minDelay,maxDelay);
  // time between different animations and sounds

      randoTrack = random(0,numSounds);
      Serial.println(Tracks[randoTrack]);

      if (randoTrack == 0){
      Serial.println("Lasers");
      lasers();
      }
        else if (randoTrack == 1){
          Serial.println("Jets");
          airJets();
          }
          else if (randoTrack == 2){
            Serial.println("Warning");
            warning();
            }
            else if (randoTrack == 3){
              Serial.println("Overload");
              sparks();
              }
              else if (randoTrack == 4){
                Serial.println("Electricity");
                electricity();
              }
              else if (randoTrack == 5){
                Serial.println("Robot");
                lasers();
              }
              delay(randomDelay);
     }
     else {
      
      Serial.print("Waiting.....");
      Serial.print(randomDelay);
      Serial.println(" milliseconds");
      Serial.print("Current time ");
      Serial.println(currentMillis);   
      } 

     
}

////////////////////////////////////////ELECTRICITY/////////////////////////////

void electricity() {
  
  // This is just Confetti from the Examples file 
  // with different colors and added array in the pre setup
  // Random colored speckles that blink in and fade smoothly

  digitalWrite(soundPins[4],LOW); // Sound 5
  blackEvens(); // Turn even LEDs black/off
  FastLED.show();
  delay(29); // Silence in audio file at the start
  fadeToBlackBy(leds, NUM_LEDS, 10);

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i == 0 || i == 2 || i == 4 || i == 6) {
      int pos = i; // Set the position to the even index
      leds[pos] = colors[random8(3)];
      FastLED.show();
      delay(20);// set blink speed
    }
  }

  blackEvens(); // Turn even LEDs black/off
  FastLED.show();
  digitalWrite(soundPins[4],HIGH); // Sound 5 off
  lastSoundTime = millis();
}


////////////////////////////////////////SPARKS/////////////////////////////

void sparks() { 
  
  CRGB targetColor = CRGB::RoyalBlue;

digitalWrite(soundPins[3],LOW); // Sound 4 on
blackEvens(); // Turn even LEDs black/off
FastLED.show();
delay(115);


  for (int brightness = 0; brightness <= 255; brightness++) {
    for (int i=0;i <=NUM_LEDS -1; i++){
      if (i == 0 | i == 2| i == 4 | i == 6){    
      leds[i] = targetColor;
      leds[i].fadeToBlackBy(255 - brightness); //fade out
      FastLED.show();
      delay(1157 / 255);
      
      }
     }       
    }
  

 blackEvens(); // Turn even LEDs black/off
  FastLED.show();
  delay(77);
  

    for (int i=0;i <=NUM_LEDS -1; i++){
      if (i == 0 | i == 2| i == 4 | i == 6){    
      leds[i] = targetColor;
      FastLED.show(); 
      }
     }
delay(181);

 blackEvens(); // Turn even LEDs black/off
  FastLED.show();
  digitalWrite(soundPins[3],HIGH); // Sound 4 off
  lastSoundTime = millis();
  
}



////////////////////////////////////////LASERS/////////////////////////////

void lasers() { 


  CRGB targetColor = CRGB::DarkOrange;

 //trigger audio file 1
  digitalWrite(soundPins[0],LOW); // pins start @ 0 so sound number - 1
// fade from off to full color brightness
  for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0;i <=NUM_LEDS -1; i++){
      if (i == 0 | i == 2| i == 4 | i == 6){
    leds[i] = targetColor;
    }
      }
  }
   
FastLED.show(); 
delay(400);

blackEvens(); // Turn even LEDs black/off
FastLED.show();
delay(809);

  for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0;i <=NUM_LEDS -1; i++){
      if (i == 0 | i == 2| i == 4 | i == 6){
    leds[i] = targetColor;
    }
      }
  }
    
FastLED.show(); 
delay(485);

blackEvens(); // Turn even LEDs black/off
FastLED.show();
delay(304);
    

  for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0;i <=NUM_LEDS -1; i++){
      if (i == 0 | i == 2| i == 4 | i == 6){
    leds[i] = targetColor;
    }
      }
  }
FastLED.show(); 
delay(370);    

 blackEvens(); // Turn even LEDs black/off
  FastLED.show();
  delay(100);

for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0;i <=NUM_LEDS -1; i++){
      if (i == 0 | i == 2| i == 4 | i == 6){
    leds[i] = targetColor;
    }
      }
  }

FastLED.show(); 
delay(449);

  blackEvens(); // Turn even LEDs black/off
  digitalWrite(soundPins[0],HIGH); // turn off LEDS
  lastSoundTime = millis();
  FastLED.show();

}

////////////////////////////////////////JETS/////////////////////////////


void airJets() { 
  
  CRGB targetColor = CRGB::Cyan;

  digitalWrite(soundPins[1],LOW); //Turn sound 2 on
  blackEvens(); // Turn even LEDs black/off
  FastLED.show();
  delay(200);


// fade from off to full color brightness
  for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0;i <=NUM_LEDS -1; i++){
      if (i == 0 | i == 2| i == 4 | i == 6){
    leds[i] = targetColor;
    }
      }
  }
   
FastLED.show(); 
delay(283);

blackEvens(); // Turn even LEDs black/off
FastLED.show();
delay(100);

  for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0;i <=NUM_LEDS -1; i++){
      if (i == 0 | i == 2| i == 4 | i == 6){
    leds[i] = targetColor;
    }
      }
  }
    
FastLED.show(); 
delay(316);

blackEvens(); // Turn even LEDs black/off
FastLED.show();
delay(100);
    

  for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0;i <=NUM_LEDS -1; i++){
      if (i == 0 | i == 2| i == 4 | i == 6){
    leds[i] = targetColor;
    }
      }
  }
FastLED.show(); 
delay(503);    

blackEvens(); // Turn even LEDs black/off
FastLED.show();
delay(100);
    

  for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0;i <=NUM_LEDS -1; i++){
      if (i == 0 | i == 2| i == 4 | i == 6){
    leds[i] = targetColor;
    }
      }
  }
FastLED.show(); 
delay(690);    

blackEvens(); // Turn even LEDs black/off
digitalWrite(soundPins[1],HIGH); //Turn sound off again
lastSoundTime = millis();
FastLED.show();


}
 
////////////////////////////////////////WARNING/////////////////////////////

void warning() { //Sound 3
  // Define the duration of the fade (in milliseconds)
  unsigned long fadeDuration = 800;

  // Number of steps in the fade
  int numSteps = 256;

  // Calculate the time interval between each step
  unsigned long stepInterval = fadeDuration / numSteps;

  //trigger audio file 3
  digitalWrite(soundPins[2],LOW); // pins start @ 0 so sound number - 1
    for (int brightness = 0; brightness <= 255; brightness++) {
    // Set the LED brightness for odd-numbered LEDs
    for (int i = 0; i <= NUM_LEDS -1; i += 2) {
      leds[i] = CRGB(brightness, 0, 0); // Red with specified brightness
    }

    FastLED.show(); // Display this frame
    delay(stepInterval);
  }

  for (int brightness = 255; brightness >= 0; brightness--) {
    // Set the LED brightness for odd-numbered LEDs
    for (int i = 0; i <= NUM_LEDS -1; i += 2) {
      leds[i] = CRGB(brightness, 0, 0); // Red with specified brightness
    }

    FastLED.show(); // Display this frame
    delay(stepInterval);

  }
      for (int brightness = 0; brightness <= 255; brightness++) {
    // Set the LED brightness for odd-numbered LEDs
    for (int i = 0; i <= NUM_LEDS -1; i += 2) {
      leds[i] = CRGB(brightness, 0, 0); // Red with specified brightness
    }

    FastLED.show(); // Display this frame
    delay(stepInterval);
  }

  for (int brightness = 255; brightness >= 0; brightness--) {
    // Set the LED brightness for odd-numbered LEDs
    for (int i = 0; i <= NUM_LEDS -1; i += 2) {
      leds[i] = CRGB(brightness, 0, 0); // Red with specified brightness
    }

    FastLED.show(); // Display this frame
    delay(stepInterval);
 
  }

digitalWrite(soundPins[2],HIGH); //Turn sound off again
lastSoundTime = millis();  
FastLED.show();

}

//////////////////////////////////BLACK EVENS/////////////////

void blackEvens(){
      for (int i = 0; i <= NUM_LEDS -1; i++){
      if (i == 0 | i == 2| i == 4 | i == 6){
      leds[i] = CRGB::Black;
      FastLED.show(); 
       }
    }
}

////////////////////////////////////////ROBOT/////////////////////////////

void robot(){
  digitalWrite(soundPins[5],LOW); // Sound 6
  delay(3000);


  blackEvens(); // Turn even LEDs black/off
  FastLED.show();
  digitalWrite(soundPins[5],HIGH); // turn off LEDS
  lastSoundTime = millis();
  delay(10);
  
}
