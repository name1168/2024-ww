// ex09/ex09.ino
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "iPhone";
const char* password = "141586734q";
WebServer server(80);
const int touchPin = T0;

// 前端AJAX轮询页面
const char* htmlPage = R"HTML(
<!DOCTYPE html>
<body>
<h2>触摸传感器实时值</h2>
<p id="data">0</p >
<script>
function update(){
  fetch('/get')
    .then(res=>res.text())
    .then(v=>document.getElementById('data').innerText=v);
}
setInterval(update, 200);
</script>
</body>
)HTML";

void handleRoot() { server.send(200, "text/html", htmlPage); }
void handleGetData() {
  int val = touchRead(touchPin);
  server.send(200, "text/plain", String(val));
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.print("WiFi连接成功，设备IP：");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/get", handleGetData);
  server.begin();
}

void loop() {
  server.handleClient();
}