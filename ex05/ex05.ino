// ex05/ex05.ino
const int touchPin = T0;
const int ledPin = 2;
int brightness = 0;
int step = 3;
int speedGear = 1; // 1慢/2中/3快 三档位
bool lastTouch = false;
unsigned long debounceDelay = 50, lastDebounceTime = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // 触摸切换档位（复用防抖逻辑）
  int touchVal = touchRead(touchPin);
  bool currTouch = touchVal < 30;
  unsigned long now = millis();
  if (now - lastDebounceTime > debounceDelay && currTouch && !lastTouch) {
    speedGear = speedGear % 3 + 1; // 1→2→3→1循环
    lastDebounceTime = now;
  }
  lastTouch = currTouch;

  // 按档位修改呼吸延时
  int delayTime;
  switch (speedGear) {
    case 1: delayTime = 30; break;
    case 2: delayTime = 15; break;
    case 3: delayTime = 5; break;
    default: delayTime = 15;
  }

  // PWM呼吸逻辑
  analogWrite(ledPin, brightness);
  brightness += step;
  if (brightness <= 0 || brightness >= 255) step = -step;
  delay(delayTime);
}