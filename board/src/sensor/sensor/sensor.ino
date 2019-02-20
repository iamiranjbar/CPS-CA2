#define TEMPPIN 1

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  int temp=analogRead(TEMPPIN); // Reading data from the sensor.This voltage is stored as a 10bit number
  temp=(5.0*temp*1000.0)/(1024*10);

  /* 5*temp/1024 is to convert the 10 bit number to a voltage reading.

  This is multiplied by 1000 to convert it to millivolt.

  We then divide it by 10 beacuse each degree rise results in a 10 millivolt increase.

  */
  delay(500);

}
