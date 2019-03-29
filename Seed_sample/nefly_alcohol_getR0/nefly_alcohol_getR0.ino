#include <Nefry.h>
#include <NefryDisplay.h>
#include <NefrySetting.h>

#define heaterSelPin A1

void setting() {
  Nefry.disableDisplayStatus();
}
NefrySetting nefrySetting(setting);

void setup() {
  //    pinMode(heaterSelPin,OUTPUT);   // set the heaterSelPin as digital output.
  //    digitalWrite(heaterSelPin,LOW); // Start to heat the sensor
  //    Nefry.ndelay(2000);
}

void loop() {
  float sensor_volt;
  float RS_air; //  Get the value of RS via in a clear air
  float sensorValue;

  /*--- Get a average data by testing 100 times ---*/
  for (int x = 0 ; x < 100 ; x++)
  {
    sensorValue = sensorValue + analogRead(A1);
  }
  sensorValue = sensorValue / 100.0;
  //    sensorValue = analogRead(A1);
  /*-----------------------------------------------*/

  sensor_volt = sensorValue / 4095.0 * 5.0;
  RS_air = sensor_volt / (5.0 - sensor_volt); // omit *R16
  Nefry.print("sensor_value = ");
  Nefry.println(sensorValue);
  Nefry.print("sensor_volt = ");
  Nefry.print(sensor_volt);
  Nefry.println("V");
  Nefry.print("RS_air = ");
  Nefry.println(RS_air);

  NefryDisplay.clear();
  NefryDisplay.setFont(ArialMT_Plain_24);
  NefryDisplay.drawString(0, 40, String(RS_air));
  NefryDisplay.display();
  Nefry.ndelay(1000);
}
