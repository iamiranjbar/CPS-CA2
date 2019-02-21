#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>


#define   CONTRAST_PIN   9
#define   BACKLIGHT_PIN  7
#define   CONTRAST       110 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String s;

void recieveEvent(int bytes)
{  
  s = "";
  while(Wire.available())
  { 
    char c = Wire.read();
    s += String(c);
  }
}

void setup()
{
  Serial.begin ( 9600 );

  // Switch on the backlight and LCD contrast levels
  pinMode(CONTRAST_PIN, OUTPUT);
  analogWrite ( CONTRAST_PIN, CONTRAST );
  lcd.backlight();

  lcd.begin(16,4);               // initialize the lcd 
  lcd.home ();                   // go home
  lcd.setCursor ( 0, 1 );        // go to the next line   

  Wire.begin(9);
  Wire.onReceive(recieveEvent);
}

void loop()
{
  lcd.print(s);
}