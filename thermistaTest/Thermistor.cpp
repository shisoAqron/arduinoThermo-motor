#include "Arduino.h"
#include "Thermistor.h"

/*
 * 参考（そのままだけど）にしたサイトです
 * http://lab.yengawa.com/2014/06/24/arduino%E3%81%A8%E3%82%B5%E3%83%BC%E3%83%9F%E3%82%B9%E3%82%BF%E3%81%A7%E6%B8%A9%E5%BA%A6%E3%82%92%E6%B8%AC%E3%82%8B/
*/
//pinNum, B(k),T0(K), R0(kΩ),R1(kΩ)
Thermistor::Thermistor(int _pin, float _B, float _T0, float _R0, float _R1) {
  pin = _pin;
  B = _B;
  T0 = _T0;
  R0 = _R0;
  R1 = _R1;
}

int Thermistor::calc_milliTemp() {
  float rr1, t;
  float raw = analogRead(pin);
  rr1 = R1 * raw / (1024.0 - raw);
  t = 1 / (log(rr1 / R0) / B + (1 / T0));
  return (int)((t - 273.15) * 10.0); //unit 0.1 degree;
}
