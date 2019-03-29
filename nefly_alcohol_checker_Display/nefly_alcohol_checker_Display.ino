#include <Nefry.h>
#include <NefryDisplay.h>
#include <NefrySetting.h>

#define heaterSelPin A1

void setting() {
  Nefry.disableDisplayStatus();
}
NefrySetting nefrySetting(setting);

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

  NefryDisplay.clear();
  NefryDisplay.setFont(ArialMT_Plain_24);
  NefryDisplay.drawString(0, 10, "In the air");
  NefryDisplay.setFont(ArialMT_Plain_16);
  NefryDisplay.drawString(0, 45, String(airValue));
  NefryDisplay.display();

  Nefry.print("sensor_value = ");
  Nefry.println(airValue);

  Nefry.ndelay(1000);
}

void alcohol_check(float airValue, float threshold) {
  float breathValue = 0;

  NefryDisplay.clear();
  NefryDisplay.setFont(ArialMT_Plain_24);
  NefryDisplay.drawString(0, 0, "Ready...");
  NefryDisplay.display();
  Nefry.ndelay(1000);
  NefryDisplay.clear();
  NefryDisplay.drawString(0, 0, "Breathe");
  NefryDisplay.drawString(60, 24, "Out!");
  NefryDisplay.display();
  NefryDisplay.setFont(ArialMT_Plain_16);

  Nefry.println("\n-息を吐いて!-");
  for (int x = 1 ; x <= 6 ; x++) { // 3秒間繰り返す
    if (x % 2) {
      int cnt = x / 2 + 1;
      Nefry.print(String(cnt) + " ");
      NefryDisplay.drawString(30 * cnt, 45,  String(cnt));
      NefryDisplay.display();
    }
    breathValue = breathValue + analogRead(A0);
    Nefry.ndelay(500);
  }
  breathValue = 4095 - breathValue / 6.0;
  Nefry.println("\nair = " +  String(airValue));
  Nefry.println("breath = " +  String(breathValue));

  NefryDisplay.clear();
  NefryDisplay.setFont(ArialMT_Plain_24);
  if (threshold < (breathValue - airValue)) {
    NefryDisplay.drawString(0, 10, "OUT!!");
    Nefry.println("【OUT!!】");
  } else {
    NefryDisplay.drawString(0, 10, "SAFE");
    Nefry.println("【SAFE】");
  }
  NefryDisplay.setFont(ArialMT_Plain_16);
  NefryDisplay.drawString(0, 45,  String(airValue));
  NefryDisplay.drawString(60, 45,  "/");
  NefryDisplay.drawString(70, 45,  String(breathValue));
  NefryDisplay.display();
  Nefry.println("------------");
  Nefry.ndelay(5000);
}
