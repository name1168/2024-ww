// ex07/ex07.ino
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "iPhone";
const char* password = "141586734q";
WebServer server(80);
const int ledPin = 2;
int pwmVal = 0;

// 网页前端（带滑动条）
const char* htmlPage = R"HTML(
<!DOCTYPE html>
<html>
<body>
<h3>LED无极调光</h3>
<input type="range" min="0" max="255" id="slider" value="0">
<p>当前亮度：<span id="val">0</span></p >
<script>
const slider = document.getElementById('slider');
const valText = document.getElementById('val');
slider.oninput = function(){
  let v = this.value;
  valText.innerText = v;
  fetch(`/set?pwm=${v}`);
}
</script>
</body>
</html>
)HTML";

void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleSetPWM() {
  if (server.hasArg("pwm")) {
    pwmVal = server.arg("pwm").toInt();
    analogWrite(ledPin, pwmVal);
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.print("WiFi连接成功，设备IP：");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/set", handleSetPWM);
  server.begin();
}

void loop() {
  server.handleClient();
}