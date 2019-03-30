#include <Nefry.h>
#define heaterSelPin A1

void setup() {
    // Serial.begin(9600); //デフォルトで115200bps
    pinMode(heaterSelPin,OUTPUT);
    digitalWrite(heaterSelPin,LOW);
    delay(2000);
}

void loop() {
    float sensor_volt;
    float RS_air; //  Get the value of RS via in a clear air
    float sensorValue;

/*--- Get a average data by testing 100 times ---*/
    for(int x = 0 ; x < 100 ; x++)
    {
        sensorValue = sensorValue + analogRead(A0);
    }
    sensorValue = sensorValue/100.0;
/*-----------------------------------------------*/

    sensor_volt = sensorValue/4095.0*5.0;
    RS_air = sensor_volt/(5.0-sensor_volt); // omit *R16
    Nefry.print("sensor_volt = ");
    Nefry.print(sensor_volt);
    Nefry.println("V");
    Nefry.print("RS_air = ");
    Nefry.println(RS_air);
    Nefry.ndelay(1000);
}
