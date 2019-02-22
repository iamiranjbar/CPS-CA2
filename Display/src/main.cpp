#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <AltSoftSerial.h>


// #define   CONTRAST_PIN   9
#define   BACKLIGHT_PIN  7
// #define   CONTRAST       110 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
AltSoftSerial altSerial;
String s;

typedef union{
  float fp;
  byte binary[4];
} binaryFloat;

void getSensorsData(){
  s ="";
  char c= '!';
  while(Serial.available() && c != '@')   
  { 
    c = Serial.read();
    if (c!='@')    
      s += c;
  }
  Serial.println(s);
}

float getUTData(){
  binaryFloat bn;
  for(int i = 0; i < 4; i++)
  { 
    bn.binary[i] = altSerial.read();
    Serial.println(bn.binary[i]);
  }
  Serial.println(bn.fp);
  return bn.fp;
}

void setup()
{
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
  getSensorsData();
  float UTdata = getUTData();
  lcd.println(s);
  lcd.println(UTdata);
  delay(250);
  lcd.clear();
}