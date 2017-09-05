#include <PID_v1.h>
#include "Thermistor.h"

double Setpoint = 70;
double Input, Output;
PID myPID(&Input, &Output, &Setpoint, 80, 0, 0, DIRECT);

Thermistor t1 = Thermistor(0,3435,298,10,10.00);

void setup() {
  Serial.begin(9600) ;

  myPID.SetOutputLimits(0, 1000);
  myPID.SetMode(AUTOMATIC);

}

void loop() {
  Serial.println(t1.calc_milliTemp());
  delay(10);
}
