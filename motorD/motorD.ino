#define PIN_IN1  7
#define PIN_IN2  8
#define PIN_VREF 9 // PWM
 
void setup(){
  pinMode(PIN_IN1,OUTPUT); 
  pinMode(PIN_IN2,OUTPUT); 
}
 
void loop(){
      
    // power MAX
    analogWrite(PIN_VREF,255); 
 
    // 正方向
    digitalWrite(PIN_IN1,HIGH);
    digitalWrite(PIN_IN2,LOW);
    delay(5000);
 
    // ブレーキ
    //digitalWrite(PIN_IN1,HIGH);
    //digitalWrite(PIN_IN2,HIGH);

    // ストップしないと発熱する
    digitalWrite(PIN_IN1,LOW);
    digitalWrite(PIN_IN2,LOW);
    delay(200);
    
    // 逆回転
    digitalWrite(PIN_IN1,LOW);
    digitalWrite(PIN_IN2,HIGH);    
    delay(5000);

    // ブレーキ
    //digitalWrite(PIN_IN1,HIGH);
    //digitalWrite(PIN_IN2,HIGH);
                
    // ストップ
    digitalWrite(PIN_IN1,LOW);
    digitalWrite(PIN_IN2,LOW);
    delay(200);
}
