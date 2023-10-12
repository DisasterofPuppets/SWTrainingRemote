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
const int NUM_LEDS = 9;
const int ledPin = 10;
bool gReverseDirection = false;
const int largeLEDS = 5;
const int smallLEDS =4;


CRGB leds[NUM_LEDS];
CRGB colors[] = {CRGB::White, CRGB::Yellow, CRGB::Blue};
unsigned long randomDelay;
unsigned long lastSoundTime;
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

blackALL();
delay(500);

Serial.print("Random Delay ");
Serial.println(randomDelay);
Serial.print("Time since last sound ");
Serial.println(lastSoundTime);

unsigned long currentMillis = millis();

//if (currentMillis - lastSoundTime >= 1111111111111111111111111111) { // testing waiting period animation on smaller leds
if (currentMillis - lastSoundTime >= randomDelay) {
// choose random sound
randoTrack = random(0,numSounds); 
//randoTrack = 5; // For testing
     

      

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
                  robot();
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
      int Rando = random(smallLEDS + 1,NUM_LEDS);
      Serial.print("Rando is ");
      Serial.println(Rando); 
      //testLEDS(); uncomment this and comment out below to confirm you have all leds wired and working
       randomSmall(Rando);
    }
}


////////////////////////////////////////LASERS/////////////////////////////
void lasers(){


  //trigger audio file 1
  digitalWrite(soundPins[0],LOW); // Play sound 1(0)
//delay for silence at start of audio
delay(300);

//Move LED along strip First shot
    for (int i = 0; i < largeLEDS; i++) {
      leds[i] = CRGB::Red;
      FastLED.show();
      delay(20);
      leds[i] = CRGB::Black;
      delay(20);
      FastLED.show();
    }
    //delay between shots
    delay(800);

//2nd shot
    for (int i = 0; i < largeLEDS; i++) {
      leds[i] = CRGB::Red;
      FastLED.show();
      delay(20);
      leds[i] = CRGB::Black;
      delay(20);
      FastLED.show();
    }
    //delay between shots
    delay(800);
//3rd
    for (int i = 0; i < largeLEDS; i++) {
      leds[i] = CRGB::Red;
      FastLED.show();
      delay(20);
      leds[i] = CRGB::Black;
      delay(20);
      FastLED.show();
    }
    //delay between shots
    delay(50);
//4th
    for (int i = 0; i < largeLEDS; i++) {
      leds[i] = CRGB::Red;
      FastLED.show();
      delay(20);
      leds[i] = CRGB::Black;
      delay(20);
      FastLED.show();
    }

  digitalWrite(soundPins[0],HIGH); //stop the sound
  lastSoundTime = millis();  
  return;
}

////////////////////////////////////////JETS/////////////////////////////
void airJets() { 
  
  CRGB targetColor = CRGB::Cyan;

  digitalWrite(soundPins[1],LOW); //Turn sound 2 on
  delay(200); // delay to allow for silence at start of sound file
  blackLarge(); // Turn large LEDs black/off
  delay(200);


// fade from off to full color brightness

  for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0; i < largeLEDS; i++){
          leds[i] = targetColor;
    }
  }
   
  FastLED.show(); 
  delay(283);

  blackLarge(); // Turn large LEDs black/off
  delay(100);

  for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0;i < largeLEDS; i++){
          leds[i] = targetColor;
    }

  }
    
  FastLED.show(); 
  delay(316);

  blackLarge(); // Turn large LEDs black/off
  delay(100);
    

  for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0;i < largeLEDS; i++){
    leds[i] = targetColor;
    }
  }
  FastLED.show(); 
  delay(503);    

  blackLarge(); // Turn large LEDs black/off
  delay(100);
    

  for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0;i < largeLEDS; i++){
    leds[i] = targetColor;
      }
  }
  FastLED.show(); 
  delay(690);    

  digitalWrite(soundPins[1],HIGH); //Turn sound off again
  lastSoundTime = millis();  
  return;
}

///////////////////////////////WARNING///////////////////////////////////////

void Warning() {

int brightSteps = 220;
digitalWrite(soundPins[2],LOW);

// 256 brightness steps x 4 makes this too long for the sound length
// at least that's the conclusion I came to after too many hours
// trying to get this to work.
// 220 was perfect, but trying to loop it caused repeat of the sound 
// so it's just pasted additional times...eh it works now

 
 for (int i = 0; i < brightSteps; i++) {
   leds[0].r = i;
   leds[1].r = i;
   leds[2].r = i;
   leds[3].r = i;
   leds[4].r = i;
   FastLED.show();
   delay(500 /brightSteps);
 }
 // Fade the LED out
 for (int i = brightSteps; i >= 0; i--) {
   leds[0].r = i;
   leds[1].r = i;
   leds[2].r = i;
   leds[3].r = i;
   leds[4].r = i;
   FastLED.show();
   delay(500 /brightSteps);
 }

/////////////////////////////////////////////2
 for (int i = 0; i < brightSteps; i++) {
   leds[0].r = i;
   leds[1].r = i;
   leds[2].r = i;
   leds[3].r = i;
   leds[4].r = i;
   FastLED.show();
   delay(500 /brightSteps);
 }
 // Fade the LED out
 for (int i = brightSteps; i >= 0; i--) {
   leds[0].r = i;
   leds[1].r = i;
   leds[2].r = i;
   leds[3].r = i;
   leds[4].r = i;
   FastLED.show();
   delay(500 /brightSteps);

/////////////////////////////////////////////3
 }
  for (int i = 0; i < brightSteps; i++) {
   leds[0].r = i;
   leds[1].r = i;
   leds[2].r = i;
   leds[3].r = i;
   leds[4].r = i;
   FastLED.show();
   delay(500 /brightSteps);
 }
 // Fade the LED out
 for (int i = brightSteps; i >= 0; i--) {
   leds[0].r = i;
   leds[1].r = i;
   leds[2].r = i;
   leds[3].r = i;
   leds[4].r = i;
   FastLED.show();
   delay(500 /brightSteps);
 }
/////////////////////////////////////////////4 
  for (int i = 0; i < 200; i++) {
   leds[0].r = i;
   leds[1].r = i;
   leds[2].r = i;
   leds[3].r = i;
   leds[4].r = i;
   FastLED.show();
   delay(500 /brightSteps);
 }
 // Fade the LED out
 for (int i = brightSteps; i >= 0; i--) {
   leds[0].r = i;
   leds[1].r = i;
   leds[2].r = i;
   leds[3].r = i;
   leds[4].r = i;
   FastLED.show();
   delay(500 /brightSteps);
 }
digitalWrite(soundPins[2],HIGH); 
delay(20);
lastSoundTime = millis();  
return;
}

////////////////////////////////////////SPARKS/////////////////////////////
void sparks() { 

// fileLength 1368ms
  
digitalWrite(soundPins[3],LOW); // Sound 4 on

//delay for silence at start of file)
delay(300);
          
for (int i = 0; i < largeLEDS; i++) {
    leds[i] = CRGB::Blue;
    FastLED.show();
}
delay(400);


for (int i = 0; i < largeLEDS; i++) {
    leds[i] = CRGB::Aqua;
    FastLED.show();
}
delay(300);


for (int i = 0; i < largeLEDS; i++) {
    leds[i] = CRGB::DarkBlue;
    FastLED.show();
}
delay(600);


for (int i = 0; i < largeLEDS; i++) {
    leds[i] = CRGB::Cyan;
    FastLED.show();
}
delay(50);

//strobe effect at end
for (int i = 0; i <=2; i++){
  
  for (int j = smallLEDS; j < NUM_LEDS; j++){
    leds[j] = CRGB::White;
    FastLED.show();
    delay(10);

    leds[j] = CRGB::Black;
    FastLED.show();
    delay(10);
   }
}
      
digitalWrite(soundPins[3], HIGH); // Sound 4 off
lastSoundTime = millis();  
return;
}

////////////////////////////////////////ELECTRICITY/////////////////////////////
void electricity(){  
  // This is just Confetti from the Examples file 
  // with different colors and added array in the pre setup
  // Random colored speckles that blink in and fade smoothly

  digitalWrite(soundPins[4],LOW); // Sound 5
  blackSmall(); // Turn small LEDs black/off
  delay(150); // Silence in audio file at the start
  fadeToBlackBy(leds, NUM_LEDS, 10);

for (int j = 0; j < 32; j++){ // how many times to blink
  for (int i = 0; i < largeLEDS; i++) {
      leds[i] = colors[random8(3)];
      FastLED.show();
      delay(15);// set blink speed
    }
} 
delay(10);
  digitalWrite(soundPins[4],HIGH); // Sound 5 off
  lastSoundTime = millis();  
  return;
}

////////////////////////////////////////ROBOT/////////////////////////////

void robot(){
  digitalWrite(soundPins[5],LOW); // Sound 6
  delay(3000);


  digitalWrite(soundPins[5],HIGH); // turn off LEDS
  lastSoundTime = millis();  
  return;

  
}

///////////////////////////////////RANDOM SMALL//////////////

void randomSmall(int Rando){

Serial.println("Random Small is playing ");

Serial.print("Random number is : ");
Serial.println(Rando);

 
  leds[Rando] = CRGB::White;
  FastLED.show();
  
  delay(10);

  leds[Rando] = CRGB::Black;
  FastLED.show();

  delay(10);
}

////////////////////////TEST LEDS//////////////////////
void testLEDS(){

  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Red;
    FastLED.show();
  }
  delay(300);
}

//////////////////////////////////BLACK ALL/////////////////

void blackALL(){
      for (int t = 0; t < NUM_LEDS; t++){
      leds[t] = CRGB::Black;
      FastLED.show(); 
       }
    }

//////////////////////////////////BLACK LARGE/////////////////

void blackLarge(){
      for (int i = 0; i < largeLEDS; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }
}

//////////////////////////////////BLACK SMALL/////////////////

void blackSmall(){
      for (int i = smallLEDS+1; i < NUM_LEDS; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }
}
