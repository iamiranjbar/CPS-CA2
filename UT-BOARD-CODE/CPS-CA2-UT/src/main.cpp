#include <Arduino.h>

#include <Wire.h>


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
  Serial.print("X = ");
  Serial.print(get_data_from_registers(10));
  Serial.print("      Y = ");
  Serial.println(get_data_from_registers(40));
}


float get_data_from_registers(int begin_register)
{
  union data byte_to_float;
  for (int i = 0; i < 4; i++)
  {
    Wire.beginTransmission(110);
    Wire.write(begin_register + i);
    Wire.endTransmission();
    Wire.requestFrom(110, 1);
    byte_to_float.bytes[i] = Wire.read();
  }
  return byte_to_float.result;
}