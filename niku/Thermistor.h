#ifndef Thermistor_h
#define Thermistor_h

class Thermistor {
  public:
    Thermistor(int pin,float B, float To, float R0, float R1);
    int calc_milliTemp();

  private:
    float B, T0, R0, R1;
    int pin;
};

#endif

