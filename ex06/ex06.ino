// ex06/ex06.ino
const int ledA = 2;   // PWM引脚1
const int ledB = 4;   // PWM引脚2
int valA = 0;
int step = 2;          // 这里去掉const，改成普通变量

void setup() {
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() {
  analogWrite(ledA, valA);
  analogWrite(ledB, 255 - valA); // 亮度反相关系
  valA += step;
  
  if (valA <= 0 || valA >= 255) {
    step = -step;
  }
  
  delay(10);
}