#include <PID_v1.h>
#include "Thermistor.h"

#define PIN_IN1  7
#define PIN_IN2  8
#define PIN_VREF 9 // PWM

//かき混ぜないと，部分的に熱くなりすぎて超えそう
// 数段階に分けたほうがよさそう
int points[4] = {100, 150, 200, 300}; //加熱の段階
float timer = 1000.00 * 60.00 * 0.50; //特定温度で温める時間(ms)*(sec)*(min)
float offsetTime = 1000.00 * 60.00 * 0.10; //段階的に温める時間(ms)*(sec)*(min)
int index = 0;


// 加熱時間の管理とかフラグ
float startTime, heatTime;
boolean firstTouch = true;
boolean finished = false;

// PID用のライブラリとか
double Setpoint;
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

  Setpoint = points[0];
  heatTime = offsetTime;
}

void loop() {
  if (Input >= Setpoint) {
    if (firstTouch) {
      startTime = millis();
      firstTouch = false;
    }
  }

  if (elaspedTime(firstTouch, startTime) > heatTime) {
    if (index < sizeof(points) / sizeof(points[0]) - 1 ) { // 0,1,2
      index += 1;
      if (index == sizeof(points) / sizeof(points[0]) - 1) { // 2->3になったとき
        heatTime = timer;
        Serial.print("targetTempStart!!!!!:");
        Serial.println(heatTime / (60000.00));
      }
      firstTouch = true;
    } else {
      //終了
      Serial.println("end!!!!!!!!!!!");
      finished = true;
    }

  }

  if (!finished) {
    Setpoint = points[index];
    Input = t1.calc_milliTemp();
    myPID.Compute();

    printStatus();
    analogWrite(PIN_VREF, Output);
  }
  delay(1);
}

float elaspedTime(boolean ft, float startTime) {
  if (ft) {
    return 0.0;
  } else {
    float diff = millis() - startTime;
    return diff;
  }
}

void printStatus() {
  Serial.print("Setpoint:");
  Serial.print(Setpoint);
  Serial.print(" temp:");
  Serial.print(Input);
  Serial.print(" output(pwm):");
  Serial.print(Output);
  Serial.print(" elaspedTime:");
  Serial.println(elaspedTime(firstTouch, startTime));
}


