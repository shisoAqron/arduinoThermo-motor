#include <PID_v1.h>
#include "Thermistor.h"

#define PIN_IN1  7
#define PIN_IN2  8
#define PIN_VREF 9 // PWM

double Setpoint = 390;
double Input, Output;
PID myPID(&Input, &Output, &Setpoint, 80, 0, 0, DIRECT);

Thermistor t1 = Thermistor(0, 3435, 298, 10, 10.00);

void setup() {
  Serial.begin(9600) ;

  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);

  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);

  myPID.SetOutputLimits(0, 255);
  myPID.SetMode(AUTOMATIC);

}

void loop() {
  Input = t1.calc_milliTemp();
  myPID.Compute();

  Serial.print("temp:");
  Serial.print(Input);
  Serial.print(" output(pwm):");
  Serial.println(Output);
  
  
  analogWrite(PIN_VREF,Output);
  delay(1);
}
