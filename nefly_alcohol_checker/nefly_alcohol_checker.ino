#include <Nefry.h>

#define heaterSelPin A1

void setup() {
  Nefry.enableSW();

  pinMode(heaterSelPin, OUTPUT);  // set the heaterSelPin as digital output.
  digitalWrite(heaterSelPin, LOW); // Start to heat the sensor
  Nefry.ndelay(2000);
}

void loop() {
  float airValue = 0;

  /*--- Get a average data by testing 100 times ---*/
  for (int x = 0 ; x < 100 ; x++) {
    airValue = airValue + analogRead(A0);
  }
  airValue = 4095.0 - (airValue / 100.0);
  /*-----------------------------------------------*/
  
  //スイッチが押されたらアルコールチェック
  if (Nefry.readSW()) {
    alcohol_check(airValue, 200.0);
  }

  Nefry.print("sensor_value = ");
  Nefry.println(airValue);

  Nefry.ndelay(1000);
}

void alcohol_check(float airValue, float threshold) {
  float breathValue = 0;

  Nefry.println("\n-息を吐いて!-");
  for (int x = 1 ; x <= 6 ; x++) { // 3秒間繰り返す
    if (x % 2) {
      int cnt = x / 2 + 1;
      Nefry.print(String(cnt) + " ");
    }
    breathValue = breathValue + analogRead(A0);
    Nefry.ndelay(500);
  }
  breathValue = 4095 - breathValue / 6.0;
  Nefry.println("\nair = " +  String(airValue));
  Nefry.println("breath = " +  String(breathValue));

  if (threshold < (breathValue - airValue)) {
    Nefry.println("【OUT!!】");
  } else {
    Nefry.println("【SAFE】");
  }
  
  Nefry.println("------------");
  Nefry.ndelay(5000);
}
