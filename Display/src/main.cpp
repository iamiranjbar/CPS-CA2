#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <AltSoftSerial.h>


// #define   CONTRAST_PIN   9
#define   BACKLIGHT_PIN  7
#define RxD 8
#define TxD 9
// #define   CONTRAST       110 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
AltSoftSerial altSerial;
String sensorData;
binaryFloat bn;
char lastUtData = '!';
char lastSensorData = '!';
int utiterator = 0;
bool utDataCompleted = false;
bool sensorDataCompleted = false;

typedef union{
  float fp;
  byte binary[4];
} binaryFloat;

void getSensorsData(){
  if(Serial.available() && lastSensorData != '@')   
  { 
    lastSensorData = Serial.read();
    if (lastSensorData != '@')    
      sensorData += lastSensorData;
  }

  if (lastSensorData == '@') {
    sensorData += '\0';
    sensorDataCompleted = true;
    lastSensorData = '!';
  }
}

void getUTData(){
  if(altSerial.available() && lastUtData != '#')
  { 
    lastUtData = altSerial.read();
    bn.binary[utiterator++] = lastUtData;
  }

  if (lastUtData == '#') {
    utDataCompleted = true;
    lastUtData = '!';
  }
  
  // Serial.println(bn.fp);
}

void setup()
{
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  Serial.begin ( 9600 );

  // Switch on the backlight and LCD contrast levels
  // pinMode(CONTRAST_PIN, OUTPUT);
  // analogWrite ( CONTRAST_PIN, CONTRAST );
  lcd.backlight();

  lcd.begin(16,4);               // initialize the lcd 
  lcd.home ();                   // go home
  altSerial.begin(9600); 
}

void loop()
{
  float UTdata = 0;
  getSensorsData();
  getUTData();
  if(utDataCompleted){
    UTdata = bn.fp;
    utDataCompleted = false;
  }
  
  lcd.println(sensorData);
  lcd.println(UTdata);
  delay(250);
  lcd.clear();

  if (sensorDataCompleted) {
    sensorDataCompleted = false;
    sensorData = "";
  }
}