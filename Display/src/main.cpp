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
  s += '\0';
  Serial.println(s);
}

float getUTData(){
  binaryFloat bn;
  char c= '!';
  int i = 0;
  while(altSerial.available() && c != '#')
  { 
    c = altSerial.read();
    bn.binary[i++] = c;
    Serial.println(bn.binary[i]);
  }
  Serial.println(bn.fp);
  return bn.fp;
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
  getSensorsData();
  float UTdata = getUTData();
  lcd.println(s);
  lcd.println(UTdata);
  delay(250);
  lcd.clear();
}