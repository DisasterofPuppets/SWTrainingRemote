//moved crystal led to own pin
//remove the crystal function trigger as it doesn't work as expected yet

#include <FastLED.h>

/************************Disaster of Puppets 2023*****************
 * Sound 1 - Lasers
 * Sound 2 - Air Jet movement
 * Sound 3 - Warning Siren 
 * Sound 4 - Sparks
 * Sound 5 - Electricity
 * Sound 6 - Robot
 *****************************************************************/

#define COLOR_ORDER GRB
#define CHIPSET     WS2812
#define BRIGHTNESS  255
#define FRAMES_PER_SECOND 60
bool gReverseDirection = false;

int soundPins[] = {4, 5, 6, 7, 8, 9}; // connections from Arduino to DY-SV8F board
const int numSounds = 6;             // number of sounds loaded on the DY-SV8F board
const int NUM_LEDS = 10;              // Total amount of LEDS on a full model this should be 12 + 1 for the Crystal LED
const int ledPin = 10;              // LED Pin on arduino
const int LED = 1;                  // Crystal LED (one strip with one led)
const int crystalPin = 3;   
const int largeLEDS = 5;            // for the full model this should be 6
const int smallLEDS = 4;            //for the full model this should be 6
int previousNumber = 0;             // Used so we don't play the same main animation / sound  twice in a row
int previousRando = 0;              // Used so we don't play the same intermission in a row

CRGB leds[NUM_LEDS];
CRGB cleds[LED];
CRGB colors[] = {CRGB::White, CRGB::Yellow, CRGB::Blue}; // for function to randomly select a color
unsigned long randomDelay;
unsigned long lastSoundTime;
unsigned long lastCrystalTime;
unsigned long crystalInterval = 10;
int minDelay = 1000; // 1 seconds change this to set the minimum time between main animations
int maxDelay = 2000; // 2 seconds change this to set the minimum time between main animations
int randoTrack;
int Rando;

void setup() 
{

FastLED.addLeds<CHIPSET, ledPin, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
FastLED.addLeds<CHIPSET, crystalPin, COLOR_ORDER>(cleds, LED).setCorrection( TypicalLEDStrip );
randomSeed(analogRead(0)); // Initialize random seed
FastLED.show(); // Initialize LED strip with all LEDs off

// make sure all sounds are off
for (int i =0; i < numSounds; i++){
  pinMode(soundPins[i], OUTPUT);
  digitalWrite(soundPins[i],HIGH);
  //  turn off sounds on start

}

Serial.begin(9600);
}


void loop() {

// first we want to turn on the continuous crystal animation
unsigned long currentMillis = millis();
if (currentMillis - lastCrystalTime >= crystalInterval){
    crystal();
    lastCrystalTime = currentMillis;
}

blackALL(); // clear all LEDS
delay(500);


/*
testLEDS(); // uncomment this and comment out below to confirm you have all leds wired and working
delay(10000);


//monitoring
Serial.print("Random Delay ");
Serial.println(randomDelay);
Serial.print("Time since last sound ");
Serial.println(lastSoundTime);
*/



//if (currentMillis - lastSoundTime >= 1111111111111111111111111111) { // testing waiting period animation on smaller leds
if (currentMillis - lastSoundTime >= randomDelay) {
// choose random sound without playing the same one in succession
     while (randoTrack == previousNumber){
     randoTrack = random(0,numSounds); 
    } 
    previousNumber = randoTrack;
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
      // set random animation without repeating the previously chosen
      while (Rando == previousRando){
        Rando = random(0,4); //Random number between 0 and 3
      }
      previousRando = Rando;
      intermission(Rando);
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
  
  for (int j = smallLEDS; j < NUM_LEDS -1 ; j++){ // -1 so Crsyatl LED is not changed
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
  fadeToBlackBy(leds, NUM_LEDS -1, 10); // -1 so Crsyatl LED is not changed

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

int brightness = 255;
blackALL();
delay(100);
  
  digitalWrite(soundPins[5],LOW); // Sound 6
delay(500);//silence at start of audio file

        // LEDs on 1
        for (int i = 0; i < largeLEDS; i++) {
          leds[i] = CRGB::White;
        }
        FastLED.show();
        delay(100);

        //off
        blackLarge();
        delay(100);

        // LEDs on 2
        for (int i = 0; i < largeLEDS; i++) {
          leds[i] = CRGB::White;
        }
        FastLED.show();
        delay(300);

        //off
        blackLarge();
        delay(50);

        // LEDs on 3
        for (int i = 0; i < largeLEDS; i++) {
          leds[i] = CRGB::White;
        }
        FastLED.show();
        delay(400);

        //off
        blackLarge();
        delay(100);

         // LEDs on 4
        for (int i = 0; i < largeLEDS; i++) {
          leds[i] = CRGB::White;
        }
        FastLED.show();
        delay(400);

         //off
        blackLarge();
        delay(200);

         // LEDs on 5 less bright
        for (int i = 0; i < largeLEDS; i++) {
          leds[i] = CRGB(brightness-150,brightness-150,brightness-150);
        }
        FastLED.show();
        delay(100);

  //off
        blackLarge();
        delay(100);

         // LEDs on 6 less bright again
        for (int i = 0; i < largeLEDS; i++) {
          leds[i] = CRGB(brightness-200,brightness-200,brightness-200);
        }
        FastLED.show();
        delay(100);

        blackLarge();
        delay(50);

         // LEDs on 7 less bright again
         for (int i = 0; i < largeLEDS; i++) {
          leds[i] = CRGB(brightness-200,brightness-200,brightness-200);
        }
          FastLED.show();
          delay(150);
        
        blackLarge();
        delay(10);

  digitalWrite(soundPins[5],HIGH); // turn off LEDS
  lastSoundTime = millis();  
  return;
  
}

///////////////////////////////////INTERMISSION//////////////

void intermission(int Rando){


int brightSteps = 220;

if (Rando == 0) { // SEQUENTIAL BLINK
Serial.println("Sequential Blink ");
  
  blackLarge();
  delay(100);

  for (int pass = 0; pass < 5; pass++) {  // Repeat the sequence 5 times
    // Generate random colors for each pass
    int randomR = random(256);
    int randomG = random(256);
    int randomB = random(256);

    // Fade in
    for (int j = 0; j < brightSteps; j++) {
      for (int i = 5; i <= 8; i++) {
        leds[i] = CRGB(randomR, randomG, randomB);
      }
      FastLED.show();
      delay(500 / brightSteps);
    }

    // Fade out
    for (int j = brightSteps; j >= 0; j--) {
      for (int i = 5; i <= 8; i++) {
        leds[i] = CRGB(randomR, randomG, randomB);
      }
      FastLED.show();
      delay(500 / brightSteps);
    }
  }
}

else if (Rando == 1) { // CHASE
  Serial.println("Sequential Chase ");
  blackLarge();
  delay(10);

  for (int i = smallLEDS + 1; i < NUM_LEDS -1 ; i++) {// -1 so Crsyatl LED is not changed
    int randomR = random(256);
    int randomG = random(256);
    int randomB = random(256);

    for (int j = 0; j < brightSteps; j++) {
      leds[i] = CRGB(randomR, randomG, randomB);
      FastLED.show();
      delay(100 / brightSteps);
    }

    // Fade the LED out
    for (int j = brightSteps; j >= 0; j--) {
      leds[i] = CRGB(randomR, randomG, randomB);
      FastLED.show();
      delay(100 / brightSteps);
    }
  }
}
else if (Rando == 2){ //random colors
  Serial.println("Random Colors ");
blackLarge();
delay(10);


  for (int i =smallLEDS +1; i < NUM_LEDS -1; i++){ // -1 so Crsyatl LED is not changed
    int randomR = random(256);
    int randomG = random(256);
    int randomB = random(256);
    
   
    // Turn on the LED with a random color
    leds[i] = CRGB(randomR, randomG, randomB);
    FastLED.show();

    // Delay for a duration to keep the LED on
    delay(500); // Adjust the delay duration as needed

    // Turn off the LED by setting it to black
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();
    }
}
else if (Rando == 3) { // sparkles
  Serial.println("Sparkles");
  blackLarge();
  delay(100);
  int selectedLED = random(smallLEDS + 1, NUM_LEDS -1); // -1 so Crsyatl LED is not changed
  int NL = -9999; // Initialize to a "null" value
  int NR = -9999; // Initialize to a "null" value

  if (selectedLED == 5) {
    NL = -9999; // NULL
    NR = 6;
  } else if (selectedLED == 6) {
    NL = 5;
    NR = 7;
  } else if (selectedLED == 7) {
    NL = 6;
    NR = 8;
  } else if (selectedLED == 8) {
    NL = 7;
    NR = -9999;
  }

  FastLED.show();
  delay(300);

  // Fade in the main LED
 // Fade in the main LED
  for (int bright = 0; bright < 256; bright++) {
    leds[selectedLED] = CRGB(bright, bright, bright);
    FastLED.show();
    delay(5); // Adjust delay for desired fading speed
  }

  // Fade in the neighboring LEDs to a lower brightness
  for (int bright = 0; bright < 201; bright++) {
    if (NL != -9999) {
      leds[NL] = CRGB(bright, bright, bright);
    }

    if (NR != -9999) {
      leds[NR] = CRGB(bright, bright, bright);
    }

    FastLED.show();
    delay(5); // Adjust delay for desired fading speed
  }

  // Delay after max brightness is reached
  delay(200);

  // Fade out all three LEDs
  for (int bright = 255; bright >= 0; bright--) {
    leds[selectedLED] = CRGB(bright, bright, bright);

    if (NL != -9999) {
      leds[NL] = CRGB(bright, bright, bright);
    }

    if (NR != -9999) {
      leds[NR] = CRGB(bright, bright, bright);
    }

    FastLED.show();
    delay(5); // Adjust delay for desired fading speed
  }
}
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
      for (int t = 0; t < NUM_LEDS -1 ; t++){ //-1 so we don't clear Crystal LED
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
      for (int i = smallLEDS+1; i < NUM_LEDS -1; i++){ //-1 so we don't clear the crystal LED
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }
}

//////////////////////////////////CRYSTAL///////////////////////

void crystal(){

int someDelay = random(0,11);
  

    cleds[0] = CRGB(0, 0, 0); // Turn off all LEDs
    FastLED.show();

  // Fade the last LED from off to max brightness in green
  for (int i = 0; i <= 255; i++) {
    cleds[0] = CRGB(0, i, 0); // Set the green component to i for the last LED
    FastLED.show();
    delay(someDelay); // Delay for smooth fading
  }

someDelay= random(0,11);  // Fade the last LED from max brightness to off with the same color

  for (int i = 255; i >= 0; i--) {
    cleds[0] = CRGB(0, i, 0); // Set the green component to i for the last LED
    FastLED.show();
    delay(someDelay); // Delay for smooth fading
  }

  lastCrystalTime = millis();  
  return;
}
