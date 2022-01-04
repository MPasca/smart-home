#include "pitches.h"
#include "songs.h"

#include <SPI.h>
#include "DHT.h"
#include <MFRC522.h>


#define SS_PIN 10

#define proximitySensor A1
#define triggerPin 9

int distance;
long duration;

#define buzzerPin A0

#define RED 6
#define GREEN 7
#define YELLOW 8

#define TEMP '1'
#define STATUS '2'

#define buttonPin 3
int buttonState = 0;

#define DHTTYPE DHT11
#define DHTPIN 2
float humidity;
float temperature;

DHT dht(DHTPIN, DHTTYPE);
MFRC522 rfid(SS_PIN, 5);

unsigned char ID[4] = {0xE3, 0x8, 0xAC, 0x34};
char message;
bool isLocked;

void setup() {
  isLocked = true;
  analogReference(DEFAULT); //setarea tensiunii de referinta la tensiunea default

  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(triggerPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(proximitySensor, INPUT); // Sets the echoPin as an INPUT

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  digitalWrite(RED, HIGH);

  Serial.begin(9600);
  
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522

  dht.begin();
  digitalWrite(triggerPin, LOW);
  digitalWrite(triggerPin, HIGH);
}

void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
   
  duration = pulseIn(proximitySensor, HIGH);
  distance = duration * 0.034 / 2;

 
  buttonState = digitalRead(buttonPin);
  
  if (rfid.PICC_IsNewCardPresent()){
    if (rfid.PICC_ReadCardSerial()){
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
       
      bool ok = 1;
      for (int i = 0; i < rfid.uid.size; i++) {
        if(rfid.uid.uidByte[i] != ID[i]){
          ok = 0;
          
          Serial.println("SOMEONE IS TRYING TO BREAK YOUR HOUSE");
          Serial.println("BE CAREFUL! you gon GET BANKRUPT");
          
          for(int i = 0; i <= 5; i++){
            digitalWrite(YELLOW, HIGH);
            digitalWrite(GREEN, HIGH);
            digitalWrite(RED, HIGH);
            alarm();
            delay(500);
            noTone(buzzerPin);
            digitalWrite(YELLOW, LOW);
            digitalWrite(GREEN, LOW);
            digitalWrite(RED,LOW);
          }  
          break;
        }
        
      }
      
      if(ok == 1){
        isLocked = !isLocked;
      }

      if(isLocked){
          digitalWrite(RED, HIGH);
          digitalWrite(GREEN, LOW);
      }else{
          digitalWrite(RED, LOW);
          digitalWrite(GREEN, HIGH);
      }
      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
    }
  }

  if(!isLocked && distance < 20){
    digitalWrite(YELLOW, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);                       // wait for a second
    digitalWrite(YELLOW, LOW);    // turn the LED off by making the voltage LOW
    delay(500);                       // wait for a second
  }else if( isLocked && distance < 20){
    Serial.println("SOMEONE IS IN YOUR HOUSE");
    alarm();
    delay(500);
    noTone(buzzerPin);
  }

  if(Serial.available()){
    message = Serial.read();
    Serial.println(message);
    if(message == TEMP){
      Serial.print("current temp: ");
      Serial.print(temperature);
      Serial.print("; humidity: ");
      Serial.println(humidity);
    }
    if(message == STATUS){
       if(isLocked){
          Serial.println("current status: locked");
      }else{
          Serial.println("current status: unlocked");
      }
    }
  }

  if (buttonState == HIGH){
    Serial.println("you've got visitors");
    doorbell();
     
  }
  
  
}

/*
float readTempInCelsius(int count, int pin) {
  // citeste temperatura de count ori de pe pinul analogic pin
  float sumTemp = 0;
  for (int i =0; i < count; i++) {
    int reading = analogRead(pin);
    float voltage = reading * resolutionADC;
    float tempCelsius = (voltage - 0.5) / resolutionSensor ;
    // scade deplasament, converteste in grade C
    sumTemp = sumTemp + tempCelsius; // suma temperaturilor
  }
  return sumTemp / (float)count; // media returnata
}
*/

void doorbell(){
    int song_choice = random(5);
    
    switch (song_choice) {
      case 0:
        play_song(haircutLength,haircut,haircutDurations,haircutTempo);
        break;
      case 1:
        play_song(marioLength,mario,marioDurations,marioTempo);
        break;
      case 2:
        play_song(miiLength,mii,miiDurations,miiTempo);
        break;
      case 3:
        play_song(hpLength,hp,hpDurations,hpTempo);
        break;
      case 4:
        play_song(takeonmeLength,takeonme,takeonmeDurations,takeonmeTempo);
        break;
      default:
        play_song(miiLength,mii,miiDurations,miiTempo);
        break;
    }
}

void play_song(int num_notes, int melody[], int noteDurations[], int tempo) {

  for (int i = 0; i < num_notes; i++) {
    int duration = 0;
   
    if (noteDurations[i] > 0) {
      duration = tempo / noteDurations[i];
    }
    else if (noteDurations[i] < 0) {
      duration = tempo / abs(noteDurations[i]) * 1.5;
    }
    tone(buzzerPin, melody[i], duration);
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerPin);
  }
}

void alarm(){
    tone(buzzerPin,2200);
    tone(buzzerPin,1000);
    tone(buzzerPin,500);
    tone(buzzerPin,200);
    tone(buzzerPin,500);
}
