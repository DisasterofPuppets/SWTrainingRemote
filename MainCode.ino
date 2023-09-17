int SOUND_PINS[] = {4, 5, 6, 7, 8, 9};
int numSounds = 6;

unsigned long soundDelay;
unsigned long lastSoundTime = 0;
unsigned long minTime = 300000;
unsigned long maxTime = 600000;

void setup() 
{
  for (int i = 0; i < numSounds; i++) {
    pinMode(SOUND_PINS[i], OUTPUT);
    digitalWrite(SOUND_PINS[i], HIGH);
  }

  Serial.begin(9600);
}
void loop() {
  unsigned long currentMillis = millis();

  // Check if it's time to play a sound
  if (currentMillis - lastSoundTime >= soundDelay) {
    int randomSoundIndex = random(0, numSounds);
    playSound(randomSoundIndex);
    lastSoundTime = currentMillis;
    soundDelay = random(minTime,maxTime);
  }
  else {
    //display the counter till next sound
    Serial.print("Counter: ");
    Serial.println(currentMillis); 
    Serial.print("Delay: ");
    Serial.println(soundDelay); 
  }
}


void redFlash(){
  
}

void playSound(int soundIndex) {
  if (soundIndex >= 0 && soundIndex < numSounds) {
    for (int i = 0; i < numSounds; i++) {
      digitalWrite(SOUND_PINS[i], HIGH); // Turn off all sounds
    }
    digitalWrite(SOUND_PINS[soundIndex], LOW); // Turn on the selected sound
    Serial.print("Playing Sound ");
    Serial.println(soundIndex + 1);
    delay(1000); // Adjust the duration as needed (1 second in this example)
    digitalWrite(SOUND_PINS[soundIndex], HIGH); // Turn off the selected sound
  }
}
