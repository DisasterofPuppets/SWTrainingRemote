int SOUND_1 = 4; //0
int SOUND_2 = 5; //1
int SOUND_3 = 6; //2
int SOUND_4 = 7; //3
int SOUND_5 = 8; //4
int SOUND_6 = 9; //5
int runonce = 0;
int numSongs = 6;

unsigned long minTimer = 300000; // minimum minutes between sounds 5 minutes
unsigned long maxTimer = 600000; // maximum minutes between sounds 10 minutes

void setup() 
{
  
  pinMode (SOUND_1, OUTPUT);
  pinMode (SOUND_2, OUTPUT);
  pinMode (SOUND_3, OUTPUT);
  pinMode (SOUND_4, OUTPUT);
  pinMode (SOUND_5, OUTPUT);
  pinMode (SOUND_6, OUTPUT);
  
  digitalWrite(SOUND_1, HIGH); 
  digitalWrite(SOUND_2, HIGH); 
  digitalWrite(SOUND_3, HIGH); 
  digitalWrite(SOUND_4, HIGH); 
  digitalWrite(SOUND_5, HIGH); 
  digitalWrite(SOUND_6, HIGH); 
  
  Serial.begin(9600); // open the serial port at 9600 bps
}


void loop()
{
  if (runonce == 0)
    {
        playrandom();
        runonce = 1;
    }
  else 
    {

    Serial.print("Delaying ");
    unsigned long silence = random(minTimer,maxTimer);
    Serial.println(silence);
    delay(random(silence));
    playrandom();
    }
}
void playrandom() {

  int songNumber = random(1,6);
  Serial.println(songNumber);

  if (songNumber == 1){
  digitalWrite(SOUND_1, LOW); 
  Serial.println("Playing Sound 1"); 
  delay(1050);
  digitalWrite(SOUND_1, HIGH); 
}

  if (songNumber == 2){
  digitalWrite(SOUND_2, LOW); 
  Serial.println("Playing Sound 2"); 
  delay(2642);
  digitalWrite(SOUND_2, HIGH); 
}

  if (songNumber == 3){
  digitalWrite(SOUND_3, LOW); 
  Serial.println("Playing Sound 3"); 
  delay(4060);
  digitalWrite(SOUND_3, HIGH); 
}

  if (songNumber == 4){
  digitalWrite(SOUND_4, LOW); 
  Serial.println("Playing Sound 4"); 
  delay(1315);
  digitalWrite(SOUND_4, HIGH); 
}

  if (songNumber == 5){
  digitalWrite(SOUND_5, LOW); 
  Serial.println("Playing Sound 5"); 
  delay(2362);
  digitalWrite(SOUND_5, HIGH); 
}

  if (songNumber == 6){
  digitalWrite(SOUND_6, LOW); 
  Serial.println("Playing Sound 6"); 
  delay(3990);
  digitalWrite(SOUND_6, HIGH); 
  }
}
