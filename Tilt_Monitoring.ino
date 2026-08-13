Iot Project Code 

#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* WIFI */
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

WebServer server(80);

/* MPU */
MPU6050 mpu;

/* OLED */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(128, 64, &Wire, -1);

/* BUZZER */
#define BUZZER 19

float angleX;
float filteredAngle = 0;

/* -------- WEB PAGE -------- */
String webpage = R"rawliteral(
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body style="text-align:center;">
<h2>Tilt Monitor</h2>
<h1 id="angle">0</h1>

<script>
setInterval(function(){
fetch('/data')
.then(res => res.text())
.then(val => {
document.getElementById("angle").innerHTML = val + "°";
});
}, 1000);
</script>

</body>
</html>
)rawliteral";

/* -------- HANDLERS -------- */
void handleRoot() {
  server.send(200, "text/html", webpage);
}

void handleData() {

  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  angleX = atan2(ax, sqrt(ay*ay + az*az)) * 180 / PI;

  filteredAngle = 0.9 * filteredAngle + 0.1 * angleX;

  /* BUZZER */
  if(abs(filteredAngle) > 30)
    digitalWrite(BUZZER, HIGH);
  else
    digitalWrite(BUZZER, LOW);

  /* OLED DISPLAY */
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0,0);
  display.println("Tilt Monitor");

  display.setCursor(0,20);
  display.print("Angle: ");
  display.println(filteredAngle);

  display.setCursor(0,40);
  if(abs(filteredAngle) > 30)
    display.println("DANGER");
  else
    display.println("SAFE");

  display.display();

  server.send(200, "text/plain", String(filteredAngle));
}

/* -------- SETUP -------- */
void setup() {

  Serial.begin(115200);

  Wire.begin(21,22);

  mpu.initialize();

  pinMode(BUZZER, OUTPUT);

  /* OLED INIT */
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED FAIL");
    while(true);
  }

  display.clearDisplay();

  /* WIFI */
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/data", handleData);

  server.begin();
}

/* -------- LOOP -------- */
void loop() {
  server.handleClient();
}
