#include <FastLED.h>

/************************
 * Sound 1 - Lasers
 * Sound 2 - Air Jet movement
 * Sound 3 - Warning Siren 
 * Sound 4 - Sparks
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


CRGB leds[NUM_LEDS];
CRGB colors[] = {CRGB::White, CRGB::Yellow, CRGB::Blue};
unsigned long randomDelay;
unsigned long lastSoundTime;
int minDelay = 15000; // 2.5 minutes
int maxDelay = 30000; // 5 minutes
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

Serial.print("Random Delay ");
Serial.println(randomDelay);
Serial.print("Time since last sound ");
Serial.println(lastSoundTime);

unsigned long currentMillis = millis();
  
if (currentMillis - lastSoundTime >= randomDelay) {
// choose random sound
     randoTrack = random(0,numSounds); 
     
      

      if (randoTrack == 0){
        Serial.println("Lasers");
        lasers();
        randomDelay = random(minDelay,maxDelay);
      }
        else if (randoTrack == 1){
          Serial.println("Jets");
          airJets();
          randomDelay = random(minDelay,maxDelay);
        }
          else if (randoTrack == 2){
            Serial.println("Warning");
            Warning();
            randomDelay = random(minDelay,maxDelay);
          }
            else if (randoTrack == 3){
              Serial.println("Sparks");
              sparks();
              randomDelay = random(minDelay,maxDelay);
            }
              else if (randoTrack == 4){
                Serial.println("Electricity");
                electricity();
                randomDelay = random(minDelay,maxDelay);
              }
                else if(randoTrack == 5){
                  Serial.println("Robot");
                  lasers();
                  randomDelay = random(minDelay,maxDelay);
                }
}
    else{ // if timer not met
      Serial.print("Waiting.....");
      Serial.print(randomDelay);
      Serial.println(" milliseconds");
      delay(1000);// stop the serial spam
      Serial.print("Current count ");
      Serial.println(currentMillis);   
    }
}
////////////////////////////////////////LASERS/////////////////////////////

void lasers() { 


  CRGB targetColor = CRGB::DarkOrange;
 //trigger audio file 1
  digitalWrite(soundPins[0],LOW); // Play sound 1(0)
  delay(300); // delay to allow for silence at start of sound file
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
  digitalWrite(soundPins[0],HIGH); //stop the sound
  lastSoundTime = millis();  
  return;
}

////////////////////////////////////////JETS/////////////////////////////


void airJets() { 
  
  CRGB targetColor = CRGB::Cyan;

  digitalWrite(soundPins[1],LOW); //Turn sound 2 on
  delay(200); // delay to allow for silence at start of sound file
  blackEvens(); // Turn even LEDs black/off
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
  return;
}


///////////////////////////////WARNING///////////////////////////////////////

void Warning() {

int brightSteps = 220;
digitalWrite(soundPins[2],LOW);

// 256 brigness steps x 4 makes this too long for the sound length
// at least that's the conclusion I came to after too many hours
// trying to get this to work.
// 220 was perfect, but trying to loop it caused repeat of the sound 
// so it's just pasted additional times...eh it works

 
 for (int i = 0; i < brightSteps; i++) {
   leds[0,2,4,6].r = i;
   FastLED.show();
   delay(500 /brightSteps);
 }
 // Fade the LED out
 for (int i = brightSteps; i >= 0; i--) {
   leds[0,2,4,6].r = i;
   FastLED.show();
   delay(500 /brightSteps);
 }

/////////////////////////////////////////////2
 for (int i = 0; i < brightSteps; i++) {
   leds[0].r = i;
   leds[2].r = i;
   leds[4].r = i;
   leds[6].r = i;
   FastLED.show();
   delay(500 /brightSteps);
 }
 // Fade the LED out
 for (int i = brightSteps; i >= 0; i--) {
   leds[0].r = i;
   leds[2].r = i;
   leds[4].r = i;
   leds[6].r = i;
   FastLED.show();
   delay(500 /brightSteps);

/////////////////////////////////////////////3
 }
  for (int i = 0; i < brightSteps; i++) {
   leds[0].r = i;
   leds[2].r = i;
   leds[4].r = i;
   leds[6].r = i;
   FastLED.show();
   delay(500 /brightSteps);
 }
 // Fade the LED out
 for (int i = brightSteps; i >= 0; i--) {
   leds[0].r = i;
   leds[2].r = i;
   leds[4].r = i;
   leds[6].r = i;
   FastLED.show();
   delay(500 /brightSteps);
 }
/////////////////////////////////////////////4 
  for (int i = 0; i < 200; i++) {
   leds[0].r = i;
   leds[2].r = i;
   leds[4].r = i;
   leds[6].r = i;
   FastLED.show();
   delay(500 /brightSteps);
 }
 // Fade the LED out
 for (int i = brightSteps; i >= 0; i--) {
   leds[0].r = i;
   leds[2].r = i;
   leds[4].r = i;
   leds[6].r = i;
   FastLED.show();
   delay(500 /brightSteps);
 }
blackEvens(); // Turn even LEDs black/off
digitalWrite(soundPins[2],HIGH); 
lastSoundTime = millis();  
return;
}

////////////////////////////////////////SPARKS/////////////////////////////

void sparks() { 

int fileLength = 1368;
  
  CRGB targetColor = CRGB::RoyalBlue;

digitalWrite(soundPins[3],LOW); // Sound 4 on
bool soundTriggered = true;



//fade from black to target
 for (int i = 0; i <=2; i++){
    for (int brightness = 0; brightness <= 255; brightness++) {
      for (int j = 0; j < NUM_LEDS; j++) {
        if (j % 2 == 0) { // Only update even-indexed LEDs (0, 2, 4, 6)
         leds[j] = blend(CRGB::Black, targetColor,brightness);
        }
      }
      FastLED.show();
      delay((fileLength / 2) / 256);
    }

    // Fade from target back to black
    for (int brightness = 255; brightness >= 0; brightness--) {
      for (int j = 0; j < NUM_LEDS; j++) {
        if (j % 2 == 0) { // Only update even-indexed LEDs (0, 2, 4, 6)
          leds[j] = blend(CRGB::Black, targetColor,brightness);
        }
      }
      FastLED.show();
      delay((fileLength / 2) / 256);
    }
    }


 blackEvens(); // Turn even LEDs black/off

   if (soundTriggered) {
    digitalWrite(soundPins[3], HIGH); // Sound 4 off
    soundTriggered = true;
   }
   
  lastSoundTime = millis();  
  return;
}


////////////////////////////////////////ELECTRICITY/////////////////////////////

void electricity() {
  
  // This is just Confetti from the Examples file 
  // with different colors and added array in the pre setup
  // Random colored speckles that blink in and fade smoothly

  digitalWrite(soundPins[4],LOW); // Sound 5
  blackEvens(); // Turn even LEDs black/off
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
  digitalWrite(soundPins[4],HIGH); // Sound 5 off
  lastSoundTime = millis();  
  return;
}

////////////////////////////////////////ROBOT/////////////////////////////

void robot(){
  digitalWrite(soundPins[5],LOW); // Sound 6
  delay(3000);


  blackEvens(); // Turn even LEDs black/off
  digitalWrite(soundPins[5],HIGH); // turn off LEDS
  lastSoundTime = millis();  
  return;

  
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
