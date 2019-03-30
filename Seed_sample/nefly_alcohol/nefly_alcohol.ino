#include <Nefry.h>
#define heaterSelPin A1

void setup() {
  pinMode(heaterSelPin, OUTPUT);  // set the heaterSelPin as digital output.
  digitalWrite(heaterSelPin, LOW); // Start to heat the sensor
  Nefry.ndelay(2000);
}

void loop() {
  float sensor_volt;
  float RS_gas; // Get value of RS in a GAS
  float RS_air = -100.0;  //ここに最初のテストコードで得られた値を入れる
  float ratio; // Get ratio RS_GAS/RS_air
  int sensorValue = analogRead(A0);
  sensor_volt = (float)sensorValue / 4095.0 * 5.0;
  RS_gas = sensor_volt / 5.0 - sensor_volt; // omit *R16

  /*-Replace the name "R0" with the value of R0 in the demo of First Test -*/
  ratio = RS_gas / RS_air; // ratio = RS/R0
  /*-----------------------------------------------------------------------*/

  Nefry.print("sensor_volt = ");
  Nefry.println(sensor_volt);
  Nefry.print("RS_ratio = ");
  Nefry.println(RS_gas);
  Nefry.print("Rs/R0 = ");
  Nefry.println(ratio);

  Nefry.print("\n");
  Nefry.ndelay(1000);
}
