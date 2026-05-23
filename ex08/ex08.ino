// ex08/ex08.ino
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "iPhone";
const char* password = "141586734q";
WebServer server(80);
const int touchPin = T0;
const int ledPin = 2;
bool isArm = false;    // 布防状态
bool isAlarm = false;   // 报警状态
unsigned long alarmTick = 0;

// 网页按钮页面
const char* htmlPage = R"HTML(
<!DOCTYPE html>
<body>
<button onclick="fetch('/arm')">布防Arm</button>
<button onclick="fetch('/disarm')">撤防Disarm</button>
</body>
)HTML";

void handleRoot() { server.send(200, "text/html", htmlPage); }
void handleArm() { isArm = true; server.send(200, "text/plain", "已布防"); }
void handleDisarm() { isArm = false; isAlarm = false; digitalWrite(ledPin, LOW); server.send(200, "text/plain", "已撤防"); }

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.print("WiFi连接成功，设备IP：");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
}

void loop() {
  server.handleClient();
  // 布防状态下触发报警
  if (isArm && !isAlarm && touchRead(touchPin) < 30) {
    isAlarm = true;
  }
  // 报警高频闪烁
  if (isAlarm) {
    if (millis() - alarmTick > 100) {
      digitalWrite(ledPin, !digitalRead(ledPin));
      alarmTick = millis();
    }
  }
}