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
String s1;
String s2;

typedef union{
  float fp;
  byte binary[4];
} binaryFloat;

void getSensorsData(){
  s1 ="";
  s2 ="";
  char c= '!';
  bool seen = false;
  while(Serial.available() && c != '@')   
  { 
    if(c == ' '){
      seen = true;
    }
    c = Serial.read();
    if (c!='@' && c!=' '){
      if(seen)  
        s2 += c;
      else
        s1 += c;
    }
  }
  s1 += '\0';
  s2 += '\0';
  Serial.println(s1);
  Serial.println(s2);
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
  lcd.setCursor(0, 0);
  lcd.println(UTdata);
  lcd.setCursor(0, 1);
  lcd.println(s1);
  lcd.setCursor(0, 2);
  lcd.println(s2);
  delay(100);
  lcd.clear();
}