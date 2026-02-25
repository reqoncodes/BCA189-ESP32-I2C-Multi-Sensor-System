#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

RTC_DS3231 rtc;
Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);   // SDA = 21, SCL = 22

  Serial.println("Initializing Devices...");

  // RTC
  if (!rtc.begin()) {
    Serial.println("❌ RTC not found!");
    while (1);
  }
  Serial.println("✅ RTC connected");

  // MPU6050
  if (!mpu.begin(0x69)) {
    Serial.println("❌ MPU6050 not found!");
    while (1);
  }
  Serial.println("✅ MPU6050 connected");

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("❌ OLED not found!");
    while (1);
  }
  Serial.println("✅ OLED connected");

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  Serial.println("System Ready!\n");
}

void loop() {

  DateTime now = rtc.now();

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // ---------------- SERIAL ----------------
  Serial.println("==================================");
  Serial.print("Time: ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.println(now.second());

  Serial.print("Accel X: "); Serial.println(a.acceleration.x);
  Serial.print("Accel Y: "); Serial.println(a.acceleration.y);
  Serial.print("Accel Z: "); Serial.println(a.acceleration.z);

  Serial.print("Gyro X: "); Serial.println(g.gyro.x);
  Serial.print("Gyro Y: "); Serial.println(g.gyro.y);
  Serial.print("Gyro Z: "); Serial.println(g.gyro.z);

  Serial.print("Temp: ");
  Serial.println(temp.temperature);
  Serial.println("==================================\n");

  // ---------------- OLED ----------------
  display.clearDisplay();

  display.setCursor(0, 0);
  display.print("Time:");
  display.print(now.hour());
  display.print(":");
  display.print(now.minute());
  display.print(":");
  display.print(now.second());

  display.setCursor(0, 10);
  display.print("AX:");
  display.print(a.acceleration.x);

  display.setCursor(0, 20);
  display.print("AY:");
  display.print(a.acceleration.y);

  display.setCursor(0, 30);
  display.print("AZ:");
  display.print(a.acceleration.z);

  display.setCursor(0, 40);
  display.print("GX:");
  display.print(g.gyro.x);

  display.setCursor(64, 10);
  display.print("GY:");
  display.print(g.gyro.y);

  display.setCursor(64, 20);
  display.print("GZ:");
  display.print(g.gyro.z);

  display.setCursor(64, 40);
  display.print("T:");
  display.print(temp.temperature);
  display.print("C");

  display.display();

  delay(2000);
}
