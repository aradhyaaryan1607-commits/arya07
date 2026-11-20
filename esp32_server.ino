#include <WiFi.h>
#include <WebServer.h>

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";

const int LED_PIN = 2;      // built-in LED on most ESP32 boards
const int SENSOR_PIN = 34;  // any ADC pin

WebServer server(80);
bool ledOn = false;

void addCors() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Private-Network", "true");
  server.sendHeader("Access-Control-Allow-Methods", "GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "*");
}

void handleStatus() {
  addCors();
  String json = "{\"led\":" + String(ledOn ? 1 : 0) +
                ",\"sensor\":" + String(analogRead(SENSOR_PIN)) + "}";
  server.send(200, "application/json", json);
}

void handleLed() {
  addCors();
  ledOn = server.arg("state") == "1";
  digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
  server.send(200, "application/json", "{\"ok\":true}");
}

void handlePreflight() {
  addCors();
  server.send(204);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nESP32 address: " + WiFi.localIP().toString());

  server.on("/api/status", HTTP_GET, handleStatus);
  server.on("/api/led", HTTP_GET, handleLed);
  server.onNotFound(handlePreflight);  // answers OPTIONS preflight requests
  server.begin();
}

void loop() {
  server.handleClient();
}
