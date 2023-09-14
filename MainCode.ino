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

Serial.begin(9600);
pinMode(sound_1, OUTPUT);
pinMode(sound_2, OUTPUT);
pinMode(sound_3, OUTPUT);
pinMode(sound_4, OUTPUT);
pinMode(sound_5, OUTPUT);
pinMode(sound_6, OUTPUT);


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
  if (Serial.available())
  {
    song = Serial.available();
    song.trim();
    Serial.print("Song is = ");
    Serial.println(song);
    randomdelay = random(1000,8000);
    delay(randomdelay);
  }
  
  song = random(1,8);
 
  //song ="1";
  
  if(song=="1")
  {
    digitalWrite(sound_1,LOW);
    digitalWrite(sound_2,HIGH);
    digitalWrite(sound_3,HIGH);
    digitalWrite(sound_4,HIGH);
    digitalWrite(sound_5,HIGH);
    digitalWrite(sound_6,HIGH);
    Serial.println("Track 1");
    delay(3000);
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
    delay(3000);
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
    delay(1000);
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
