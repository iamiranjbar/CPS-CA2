#include <Arduino.h>
#include <Ultrasonic.h>
#include <Wire.h>

#define TEMPPIN 1
#define TRIGPIN 9
#define ECHOPIN 8

Ultrasonic ultrasonic(TRIGPIN, ECHOPIN); // (Trig PIN,Echo PIN)

void setup() {
  Serial.begin(9600);
}

void loop() {
  int temp=analogRead(TEMPPIN); // Reading data from the sensor.This voltage is stored as a 10bit number
  temp=(5.0*temp*1000.0)/(1024*10);
  Serial.println(temp);
  Serial.println(ultrasonic.Ranging(CM));
  String thisString = String(temp);
  Serial.println(thisString + " " + String(ultrasonic.Ranging(CM)));
  thisString = thisString + " " + String(ultrasonic.Ranging(CM));
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(thisString.c_str());              // sends x 
  Wire.endTransmission();    // stop transmitting

  /* 5*temp/1024 is to convert the 10 bit number to a voltage reading.

  This is multiplied by 1000 to convert it to millivolt.

  We then divide it by 10 beacuse each degree rise results in a 10 millivolt increase.

  */
  delay(250);
}