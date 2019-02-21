#include <Arduino.h>
#include <Ultrasonic.h>
#include <Wire.h>

#define TEMPPIN 1
#define TRIGPIN 9
#define ECHOPIN 8

Ultrasonic ultrasonic(TRIGPIN, ECHOPIN);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int temp=analogRead(TEMPPIN); 
  temp=(5.0*temp*1000.0)/(1024*10);
  // Serial.println(temp);
  // Serial.println(ultrasonic.Ranging(CM));
  String thisString = String(temp);
  // Serial.println(thisString + " " + String(ultrasonic.Ranging(CM)));
  thisString = thisString + " " + String(ultrasonic.Ranging(CM));
  thisString+= "@";
  // Serial.println(thisString);
  Serial.write(thisString.c_str(), thisString.length());
  delay(250);
}