#include <Arduino.h>

#include <Wire.h>

#define XSTART 10
#define YSTART 40
#define BYTENUMBER 4

float get_data_from_registers(int i);

void setup() {
  Wire.begin();
  Wire.beginTransmission(110);
  Wire.write(0);
  Wire.write(1);
  Wire.endTransmission();
  Serial.begin(9600);
}

union data
{
  byte bytes[4];
  float result;
};


void loop() {  // put delay for avoid invalid pairing of (x,y) s
  float x = get_data_from_registers(XSTART);
  float y = get_data_from_registers(YSTART);
  // Serial.print("X = ");
  // Serial.print(x);
  // Serial.print("      Y = ");
  // Serial.println(y);
  float res = pow(x, 2) + pow(y, 2);
  byte* b = (byte*) &res;
  Serial.write(b, 4);
}


float get_data_from_registers(int begin_register)
{
  union data byte_to_float;
  for (int i = 0; i < BYTENUMBER; i++)
  {
    Wire.beginTransmission(110);
    Wire.write(begin_register + i);
    Wire.endTransmission();
    Wire.requestFrom(110, 1);
    byte_to_float.bytes[i] = Wire.read();
  }
  return byte_to_float.result;
}