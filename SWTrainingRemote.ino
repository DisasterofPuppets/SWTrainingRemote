// Flashed using ESP32 board - DOIT ESP32 DEVKIT V1
// When uploading you need to press the BOOT button when Serial is connecting

/* HARDWARE LIST ///////////////////////////////////////////////////////////

- ESP32 (I'm using a 'DOIT ESP32 DEVKIT V1' board. You may need to double check pin numbers as they may differ from the wiring diagram)
- WS2812B Individually Addressible LED Strip (or similar)
- DY-SV8F Amplifier board
- 4 Ohm 5W Speaker
- Reed Switch

*///////////////////////////////////////////////////////////////////////////


/************************Disaster of Puppets 2023*****************
 * Sound 1 - Lasers
 * Sound 2 - Air Jet movement
 * Sound 3 - Warning Siren 
 * Sound 4 - Sparks
 * Sound 5 - Electricity
 * Sound 6 - Robot
 *****************************************************************/

//////////////////////////////////////////////////////////// INCLUDES
#include <FastLED.h>        //LED CONTROL LIBRARY
//////////////////////////////////////////////////////////// DEFINES

// HARDWARE PINS

/* Pins 34,35, 36 and 39 are input only (These may differ for your ESP32)
   Builtin LED is GPIO2
*/
const int ledPin = 15; // Pin for controlling the LED stip on the ESP32 (GPI12)
const int crystalSwitch = 32; // Pin for controlling the LED stip on the ESP32 (GPI04)


int soundPins[] = {13, 14, 27, 26, 25, 33}; // connections from Arduino to DY-SV8F board (D13,D12,D14,D27,D26,D25)

// HARDWARE SETTINGS

const int numSounds = 6; //number of sounds on the DY-SV8F

// FASTLED SETTINGS

const int NUM_LEDS = 10;  // Amount of LEDS in the Strip (For a full model this would be 12 + 1 for the crystal
// Dont fall into the trap of trying to address the last LED as the number above. While we define the real world amount of LEDS here, 
// Arduino usually addresses them from 0 - 9 (in the case of 10 being declared)
const int largeLEDS = 5; // Amount of LEDS in the larger holes (6 for full model)
const int smallLEDS = 4; // Amount of LEDS in the smaller holes (6 for full model)
//We aren't counting the final LED as part of the smallLEDS or LargLEDS
//Make sure these add up to the NUM_LEDS -1)

//Let's make it easier for my brain when referencing the LEDS

int SLED = (NUM_LEDS - largeLEDS); // in this case 10 - 5 = 5

// Visually here is my setup

// 1   2   3   4   5   6   7   8   9   10 // How the LEDS are physically on the Strip
// 0   1   2   3   4   5   6   7   8   9  // How Arduino references each led on the strip
// L   L   L   L   L   s   s   s   s   C  // My wiring, 5 large, 4 small, last one for the crystal

#define COLOR_ORDER GRB
#define CHIPSET     WS2812
bool gReverseDirection = false;

CRGB leds[NUM_LEDS];
CRGB colors[] = {CRGB::White, CRGB::Yellow, CRGB::Blue}; // for function to randomly select a color

// TIMERS and MISC

unsigned long randomDelay;           // holds random delay number
unsigned long lastSoundTime;        // holds last time run in each function
int randoTrack;                     // holds the random track selection
int Rando;                          // holds the random intermission setting

int minDelay = 10000; // 10 seconds change this to set the minimum time between main animations
int maxDelay = 20000; // 20 seconds change this to set the minimum time between main animations

int previousNumber = 0;             // Used so we don't play the same main animation / sound  twice in a row
int previousRando = 0;              // Used so we don't play the same intermission in a row


//////////////TASKS

void crystalLED(void * parameters){
  for (;;){
//    Serial.println("Crystal LED");
//    Serial.println(digitalRead(crystalSwitch)); 
// CHECK IF THE SWITCH IS OPEN
  int switchState = digitalRead(crystalSwitch);
  if (switchState == 1){ // Open Closed is 0
    
    int someDelay = random(0,11);


// Fade the last LED from off to max brightness in green
    for (int i = 0; i <= 255; i++) {
      leds[NUM_LEDS -1] = CRGB(0, i, 0); // So we are only working with the very last LED in the strip
     FastLED.show();0
     vTaskDelay(someDelay / portTICK_PERIOD_MS);// Delay for smooth fading
    }

    someDelay= random(0,11);  // Fade the last LED from max brightness to off with the same color

    for (int i = 255; i >= 0; i--) {
      leds[NUM_LEDS -1] = CRGB(0, i, 0); // Set the green component to i for the last LED
      FastLED.show();
      vTaskDelay(someDelay / portTICK_PERIOD_MS);// Delay for smooth fading
    }
     vTaskDelay(1000 / portTICK_PERIOD_MS); // converts ticks to ms  in this case 1 second
   }

}

}    
///////////////////////////////////////////////////////////////////

void mainAnimation(void * parameters){
  for (;;){

      unsigned long currentMillis = millis();
      if (currentMillis - lastSoundTime >= randomDelay) {       // choose random sound without playing the same one in succession
        while (randoTrack == previousNumber){
        randoTrack = random(0,numSounds); 
      } 
      previousNumber = randoTrack;

      if (randoTrack == 0){
 //       Serial.println("Lasers");
 
        ////////////////////////////////////////LASERS/////////////////////////////

  //trigger audio file 1
  digitalWrite(soundPins[0],LOW); // Play sound 1(0)
  //delay for silence at start of audio
vTaskDelay(300 / portTICK_PERIOD_MS);

//Move LED along strip First shot
    for (int i = 0; i < largeLEDS; i++) { 
      
//using < largeLEDS allows us to assign 0 - 4 as the leds in question
// if we said i <= largeLEDS we would be saying 0 - 5 (which is one too many)

      leds[i] = CRGB::Red;
      FastLED.show();
vTaskDelay(20 / portTICK_PERIOD_MS);
      leds[i] = CRGB::Black;
vTaskDelay(20 / portTICK_PERIOD_MS);
      FastLED.show();
    }
    //delay between shots
vTaskDelay(800 / portTICK_PERIOD_MS);

//2nd shot
    for (int i = 0; i < largeLEDS; i++) {
      leds[i] = CRGB::Red;
      FastLED.show();
vTaskDelay(20 / portTICK_PERIOD_MS);
      leds[i] = CRGB::Black;
vTaskDelay(20 / portTICK_PERIOD_MS);
      FastLED.show();
    }
    //delay between shots
vTaskDelay(800 / portTICK_PERIOD_MS);
//3rd
    for (int i = 0; i < largeLEDS; i++) {
      leds[i] = CRGB::Red;
      FastLED.show();
vTaskDelay(20 / portTICK_PERIOD_MS);
      leds[i] = CRGB::Black;
vTaskDelay(20 / portTICK_PERIOD_MS);
      FastLED.show();
    }
    //delay between shots
vTaskDelay(50 / portTICK_PERIOD_MS);
//4th
    for (int i = 0; i < largeLEDS; i++) {
      leds[i] = CRGB::Red;
      FastLED.show();
vTaskDelay(20 / portTICK_PERIOD_MS);
      leds[i] = CRGB::Black;
vTaskDelay(20 / portTICK_PERIOD_MS);
      FastLED.show();
    }

  digitalWrite(soundPins[0],HIGH); //stop the sound
  lastSoundTime = millis();  
        
        randomDelay = random(minDelay,maxDelay);
      }
      else if (randoTrack == 1){
//        Serial.println("Jets");

        ////////////////////////////////////////JETS/////////////////////////////

CRGB targetColor = CRGB::Cyan;

  digitalWrite(soundPins[1],LOW); //Turn sound 2 on
vTaskDelay(200 / portTICK_PERIOD_MS); // delay to allow for silence at start of sound file
  for (int i = 0; i < largeLEDS; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }; // Turn large LEDs black/off
vTaskDelay(200 / portTICK_PERIOD_MS);


// fade from off to full color brightness

  for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0; i < largeLEDS; i++){
          leds[i] = targetColor;
    }
  }
   
  FastLED.show(); 
vTaskDelay(283 / portTICK_PERIOD_MS);

  for (int i = 0; i < largeLEDS; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }; // Turn large LEDs black/off
vTaskDelay(100 / portTICK_PERIOD_MS);

  for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0;i < largeLEDS; i++){
          leds[i] = targetColor;
    }

  }
    
  FastLED.show(); 
vTaskDelay(316 / portTICK_PERIOD_MS);

  for (int i = 0; i < largeLEDS; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }; // Turn large LEDs black/off
vTaskDelay(100 / portTICK_PERIOD_MS);
    

  for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0;i < largeLEDS; i++){
    leds[i] = targetColor;
    }
  }
  FastLED.show(); 
vTaskDelay(503 / portTICK_PERIOD_MS); 

  for (int i = 0; i < largeLEDS; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }; // Turn large LEDs black/off
vTaskDelay(100 / portTICK_PERIOD_MS);
    

  for (int brightness = 0; brightness <= 255; brightness++){
    for (int i=0;i < largeLEDS; i++){
    leds[i] = targetColor;
      }
  }
  FastLED.show(); 
vTaskDelay(690 / portTICK_PERIOD_MS);

  digitalWrite(soundPins[1],HIGH); //Turn sound off again
  lastSoundTime = millis();  
        
        randomDelay = random(minDelay,maxDelay);
        }
      else if (randoTrack == 2){
//        Serial.println("Warning");

        ////////////////////////////////////////WARNING/////////////////////////////

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
vTaskDelay((500 / portTICK_PERIOD_MS) /brightSteps);
 }
 // Fade the LED out
 for (int i = brightSteps; i >= 0; i--) {
   leds[0].r = i;
   leds[1].r = i;
   leds[2].r = i;
   leds[3].r = i;
   leds[4].r = i;
   FastLED.show();
vTaskDelay((500 / portTICK_PERIOD_MS) /brightSteps);
 }

/////////////////////////////////////////////2
 for (int i = 0; i < brightSteps; i++) {
   leds[0].r = i;
   leds[1].r = i;
   leds[2].r = i;
   leds[3].r = i;
   leds[4].r = i;
   FastLED.show();
vTaskDelay((500 / portTICK_PERIOD_MS) /brightSteps);
 }
 // Fade the LED out
 for (int i = brightSteps; i >= 0; i--) {
   leds[0].r = i;
   leds[1].r = i;
   leds[2].r = i;
   leds[3].r = i;
   leds[4].r = i;
   FastLED.show();
vTaskDelay((500 / portTICK_PERIOD_MS) /brightSteps);

/////////////////////////////////////////////3
 }
  for (int i = 0; i < brightSteps; i++) {
   leds[0].r = i;
   leds[1].r = i;
   leds[2].r = i;
   leds[3].r = i;
   leds[4].r = i;
   FastLED.show();
vTaskDelay((500 / portTICK_PERIOD_MS) /brightSteps);
 }
 // Fade the LED out
 for (int i = brightSteps; i >= 0; i--) {
   leds[0].r = i;
   leds[1].r = i;
   leds[2].r = i;
   leds[3].r = i;
   leds[4].r = i;
   FastLED.show();
vTaskDelay((500 / portTICK_PERIOD_MS) /brightSteps);
 }
/////////////////////////////////////////////4 
  for (int i = 0; i < 200; i++) {
   leds[0].r = i;
   leds[1].r = i;
   leds[2].r = i;
   leds[3].r = i;
   leds[4].r = i;
   FastLED.show();
vTaskDelay((500 / portTICK_PERIOD_MS) /brightSteps);
 }
 // Fade the LED out
 for (int i = brightSteps; i >= 0; i--) {
   leds[0].r = i;
   leds[1].r = i;
   leds[2].r = i;
   leds[3].r = i;
   leds[4].r = i;
   FastLED.show();
vTaskDelay((500 / portTICK_PERIOD_MS) /brightSteps);
 }
digitalWrite(soundPins[2],HIGH); 
vTaskDelay(20 / portTICK_PERIOD_MS);
lastSoundTime = millis();  
        
        randomDelay = random(minDelay,maxDelay);
        }
      else if (randoTrack == 3){
//        Serial.println("Sparks");
        
        ////////////////////////////////////////SPARKS/////////////////////////////
        
// fileLength 1368ms
  
digitalWrite(soundPins[3],LOW); // Sound 4 on

//delay for silence at start of file)
vTaskDelay(300 / portTICK_PERIOD_MS);
          
for (int i = 0; i < largeLEDS; i++) {
    leds[i] = CRGB::Blue;
    FastLED.show();
}
vTaskDelay(400 / portTICK_PERIOD_MS);


for (int i = 0; i < largeLEDS; i++) {
    leds[i] = CRGB::Aqua;
    FastLED.show();
}
vTaskDelay(300 / portTICK_PERIOD_MS);


for (int i = 0; i < largeLEDS; i++) {
    leds[i] = CRGB::DarkBlue;
    FastLED.show();
}
vTaskDelay(600 / portTICK_PERIOD_MS);


for (int i = 0; i < largeLEDS; i++) {
    leds[i] = CRGB::Cyan;
    FastLED.show();
}
vTaskDelay(50 / portTICK_PERIOD_MS);

//strobe effect at end
for (int i = 0; i <=2; i++){
  
  for (int j = SLED; j < NUM_LEDS; j++){    
    
    // starts from the first small LED reference and total so the crystal led is uneffected
    // remember LEDS are referenced from 0 to minus 1 of the total, eg 10 leds = 0 - 9
    // as long as we use < NUM_LEDS instead of <= NUM_LEDS this works. 
    
    leds[j] = CRGB::White;
    FastLED.show();
vTaskDelay(10 / portTICK_PERIOD_MS);

    leds[j] = CRGB::Black;
    FastLED.show();
vTaskDelay(10 / portTICK_PERIOD_MS);
}
      
digitalWrite(soundPins[3], HIGH); // Sound 4 off
lastSoundTime = millis();  
        
        randomDelay = random(minDelay,maxDelay);
        }
}
      else if (randoTrack == 4){
//        Serial.println("Electricity");

        ////////////////////////////////////////ELECTRICITY/////////////////////////////

// This is just Confetti from the Examples file 
  // with different colors and added array in the pre setup
  // Random colored speckles that blink in and fade smoothly

  digitalWrite(soundPins[4],LOW); // Sound 5
    for (int i = SLED; i < NUM_LEDS; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }; // Turn small LEDs black/off
vTaskDelay(150 / portTICK_PERIOD_MS); // Silence in audio file at the start
  fadeToBlackBy(leds, NUM_LEDS -2, 10);

for (int j = 0; j < 32; j++){ // how many times to blink
  for (int i = 0; i < largeLEDS; i++) {
      leds[i] = colors[random8(3)];
      FastLED.show();
vTaskDelay(15 / portTICK_PERIOD_MS);// set blink speed
    }
} 
vTaskDelay(10 / portTICK_PERIOD_MS);
  digitalWrite(soundPins[4],HIGH); // Sound 5 off
  lastSoundTime = millis();  
     
        randomDelay = random(minDelay,maxDelay);
        }
      else if(randoTrack == 5){
//        Serial.println("Robot");

        ////////////////////////////////////////ROBOT/////////////////////////////

int brightness = 255;
   for (int t = 0; t < NUM_LEDS -2; t++){
      leds[t] = CRGB::Black;
      FastLED.show(); 
       }
vTaskDelay(100 / portTICK_PERIOD_MS);
  
  digitalWrite(soundPins[5],LOW); // Sound 6
vTaskDelay(500 / portTICK_PERIOD_MS);//silence at start of audio file

        // LEDs on 1
        for (int i = 0; i < largeLEDS; i++) {
          leds[i] = CRGB::White;
        }
        FastLED.show();
vTaskDelay(100 / portTICK_PERIOD_MS);

        //off
        for (int i = 0; i < largeLEDS; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }
vTaskDelay(100 / portTICK_PERIOD_MS);

        // LEDs on 2
        for (int i = 0; i < largeLEDS; i++) {
          leds[i] = CRGB::White;
        }
        FastLED.show();
vTaskDelay(300 / portTICK_PERIOD_MS);

        //off
        for (int i = 0; i < largeLEDS; i++){
          leds[i] = CRGB::Black;
          FastLED.show(); 
       }
vTaskDelay(50 / portTICK_PERIOD_MS);

        // LEDs on 3
        for (int i = 0; i < largeLEDS; i++) {
          leds[i] = CRGB::White;
        }
        FastLED.show();
vTaskDelay(400 / portTICK_PERIOD_MS);

        //off
        for (int i = 0; i < largeLEDS; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }
vTaskDelay(100 / portTICK_PERIOD_MS);

         // LEDs on 4
        for (int i = 0; i < largeLEDS; i++) {
          leds[i] = CRGB::White;
        }
        FastLED.show();
vTaskDelay(400 / portTICK_PERIOD_MS);

         //off
        for (int i = 0; i < largeLEDS; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }
vTaskDelay(200 / portTICK_PERIOD_MS);

         // LEDs on 5 less bright
        for (int i = 0; i < largeLEDS; i++) {
          leds[i] = CRGB(brightness-150,brightness-150,brightness-150);
        }
        FastLED.show();
vTaskDelay(100 / portTICK_PERIOD_MS);

  //off
        for (int i = 0; i < largeLEDS; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }
vTaskDelay(100 / portTICK_PERIOD_MS);

         // LEDs on 6 less bright again
        for (int i = 0; i < largeLEDS; i++) {
          leds[i] = CRGB(brightness-200,brightness-200,brightness-200);
        }
        FastLED.show();
vTaskDelay(100 / portTICK_PERIOD_MS);

        for (int i = 0; i < largeLEDS; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }
vTaskDelay(50 / portTICK_PERIOD_MS);

         // LEDs on 7 less bright again
         for (int i = 0; i < largeLEDS; i++) {
          leds[i] = CRGB(brightness-200,brightness-200,brightness-200);
        }
          FastLED.show();
vTaskDelay(150 / portTICK_PERIOD_MS);
        
        for (int i = 0; i < largeLEDS; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }

  digitalWrite(soundPins[5],HIGH); // turn off LEDS
  lastSoundTime = millis(); 
        
        randomDelay = random(minDelay,maxDelay);
        }
     }
  else{ // if timer not met
  /////////////////////////////////////////////INTERMISSION ANIMATIONS////////////////////////
  
 //     Serial.print("Waiting.....");
 //     Serial.print(randomDelay);
//      Serial.println(" milliseconds");
vTaskDelay(1000 / portTICK_PERIOD_MS);
//      Serial.print("Current count ");
//      Serial.println(currentMillis);  
      // set random animation without repeating the previously chosen
      while (Rando == previousRando){
        Rando = random(0,4); //Random number between 0 and 3
      }
      previousRando = Rando;
int brightSteps = 220;

if (Rando == 0) { // SEQUENTIAL BLINK
//Serial.println("Sequential Blink ");
  
   for (int i = 0; i < NUM_LEDS -2; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }
vTaskDelay(100 / portTICK_PERIOD_MS);

  for (int pass = 0; pass < 5; pass++) {  // Repeat the sequence 5 times
    // Generate random colors for each pass
    int randomR = random(256);
    int randomG = random(256);
    int randomB = random(256);

    // Fade in
    for (int j = 0; j < brightSteps; j++) {
      for (int i = 0; i < NUM_LEDS -2; i++) {
        leds[i] = CRGB(randomR, randomG, randomB);
      }
      FastLED.show();
vTaskDelay((500 / portTICK_PERIOD_MS) / brightSteps);
    }

    // Fade out
    for (int j = brightSteps; j >= 0; j--) {
      for (int i = 0; i <= NUM_LEDS -2; i++) {
        leds[i] = CRGB(randomR, randomG, randomB);
      }
      FastLED.show();
vTaskDelay((500 / portTICK_PERIOD_MS) / brightSteps);
    }
  }
}

else if (Rando == 1) { // CHASE
//  Serial.println("Sequential Chase ");
   for (int i = 0; i < NUM_LEDS -2; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }
vTaskDelay(10 / portTICK_PERIOD_MS);

  for (int i = 0; i < NUM_LEDS -2; i++) {
    int randomR = random(256);
    int randomG = random(256);
    int randomB = random(256);

    for (int j = 0; j < brightSteps; j++) {
      leds[i] = CRGB(randomR, randomG, randomB);
      FastLED.show();
vTaskDelay((100 / portTICK_PERIOD_MS) / brightSteps);
    }

    // Fade the LED out
    for (int j = brightSteps; j >= 0; j--) {
      leds[i] = CRGB(randomR, randomG, randomB);
      FastLED.show();
vTaskDelay((100 / portTICK_PERIOD_MS) / brightSteps);
    }
  }
}
else if (Rando == 2){ //random colors
//  Serial.println("Random Colors ");
   for (int i = 0; i < NUM_LEDS -2; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }
vTaskDelay(10 / portTICK_PERIOD_MS);


  for (int i = 0; i < NUM_LEDS -2; i++){
    int randomR = random(256);
    int randomG = random(256);
    int randomB = random(256);
    
   
    // Turn on the LED with a random color
    leds[i] = CRGB(randomR, randomG, randomB);
    FastLED.show();

    // Delay for a duration to keep the LED on
vTaskDelay(500 / portTICK_PERIOD_MS); // Adjust the delay duration as needed

    // Turn off the LED by setting it to black
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();
    }
}
else if (Rando == 3) { // sparkles
//  Serial.println("Sparkles");
   for (int i = 0; i < NUM_LEDS -2; i++){
       leds[i] = CRGB::Black;
      FastLED.show(); 
       }
vTaskDelay(100 / portTICK_PERIOD_MS);

  int selectedLED = random(0, NUM_LEDS -2); // so we don't get the crystal LED
  int NL = -9999; // Initialize to a "null" value
  int NR = -9999; // Initialize to a "null" value

   if (selectedLED == 0) {
    NL = NUM_LEDS-1; // 2nd last LED on the strip
    NR = selectedLED + 1;
   }
   
   else if (selectedLED == NUM_LEDS -2) {
    NL = selectedLED -1; // back one
    NR =  0;
   }  
   
   else{
    NL = selectedLED - 1; // NULL
    NR = selectedLED + 1;
   }

  FastLED.show();
vTaskDelay(300 / portTICK_PERIOD_MS);


 // Fade in the main LED
  for (int bright = 0; bright < 256; bright++) {
    leds[selectedLED] = CRGB(bright, bright, bright);
    FastLED.show();
vTaskDelay(5 / portTICK_PERIOD_MS);// Adjust delay for desired fading speed
  }

  // Fade in the neighboring LEDs to a lower brightness
  for (int bright = 0; bright < 201; bright++) {
      leds[NL] = CRGB(bright, bright, bright);
      leds[NR] = CRGB(bright, bright, bright);
    }


    FastLED.show();
vTaskDelay(5 / portTICK_PERIOD_MS); // Adjust delay for desired fading speed
  

  // Delay after max brightness is reached
vTaskDelay(200 / portTICK_PERIOD_MS);

  // Fade out all three LEDs
  for (int bright = 255; bright >= 0; bright--) {
      leds[selectedLED] = CRGB(bright, bright, bright);
      leds[NL] = CRGB(bright, bright, bright);
      leds[NR] = CRGB(bright, bright, bright);
    }

    FastLED.show();
vTaskDelay(5 / portTICK_PERIOD_MS);// Adjust delay for desired fading speed
  }
}
 
 }
}
//////////////////////////////////////////////////////////// SETUP

void setup(){

//////////////////TASK PRIORITY


xTaskCreate(
  crystalLED,     // function name
  "Crystal LED",  // task name
  1000,           // stack size
  NULL,           // task parameters
  1,              // priority (lower number = higher priority)
  NULL            // task handle
);

xTaskCreate(
  mainAnimation,     // function name
  "mainAnimation",  // task name
  1000,            // stack size
  NULL,            // task parameters
  10,              // priority (lower number = higher priority)
  NULL            // task handle
);

//FASTLED
FastLED.addLeds<CHIPSET, ledPin, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
randomSeed(analogRead(0)); // Initialize random seed
FastLED.show(); // Initialize LED strip with all LEDs off

// AUDIO

// make sure all sounds are off
for (int i =0; i < numSounds; i++){
  pinMode(soundPins[i], OUTPUT);
  digitalWrite(soundPins[i],HIGH);
  //  turn off sounds on start

}

pinMode(crystalSwitch,INPUT_PULLUP);

//SANITY DELAY
delay(1000);

//Serial.begin(9600); // for debugging
  
}

//////////////////////////////////////////////////////////// LOOP
void loop(){
    
}
