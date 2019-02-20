#include <Arduino.h>
#include <Ultrasonic.h>

#define TEMPPIN 1

Ultrasonic ultrasonic(9,8); // (Trig PIN,Echo PIN)

void setup() {
  Serial.begin(9600);
}

void loop() {
  float temp=analogRead(TEMPPIN); // Reading data from the sensor.This voltage is stored as a 10bit number
  temp=(5.0*temp*1000.0)/(1024*10);
  Serial.println(temp);
  Serial.println(ultrasonic.Ranging(CM));

  /* 5*temp/1024 is to convert the 10 bit number to a voltage reading.

  This is multiplied by 1000 to convert it to millivolt.

  We then divide it by 10 beacuse each degree rise results in a 10 millivolt increase.

  */
  delay(500);
}