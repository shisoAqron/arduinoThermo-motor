#include "Thermistor.h"
Thermistor t1 = Thermistor(0,3435,298,10,10.00);

void setup(){
  Serial.begin(9600);
}

void loop() {
  Serial.println(t1.calc_milliTemp());
  delay(10);
}

