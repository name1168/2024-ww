// ex04/ex04.ino
const int touchPin = T0;    // ESP32触摸引脚T0(GPIO4)
const int ledPin = 2;       // 板载LED引脚
bool ledState = LOW;
bool lastTouchState = false;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; // 50ms软件防抖

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int touchValue = touchRead(touchPin);
  bool currentTouch = (touchValue < 30); // 触摸阈值判定
  unsigned long currentTime = millis();

  // 防抖逻辑+上升沿检测（仅触摸瞬间翻转状态）
  if (currentTime - lastDebounceTime > debounceDelay) {
    if (currentTouch == true && lastTouchState == false) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
      lastDebounceTime = currentTime;
    }
  }
  lastTouchState = currentTouch;
}