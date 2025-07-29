#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
Adafruit_BMP280 bmp;

float baseX = 0, baseY = 0, baseZ = 0;
int sampleCount = 0;
unsigned long startTime;
bool calibrated = false;

void setup() {
  Serial.begin(115200);
  bno.begin();
  startTime = millis();
}

void loop() {
  sensors_event_t event;
  bno.getEvent(&event);

  if (!calibrated && millis() - startTime < 3000) {
    // Calibration window: collect samples
    baseX += event.orientation.x;
    baseY += event.orientation.y;
    baseZ += event.orientation.z;
    sampleCount++;
    Serial.println("Calibrating...");
  } 
  
  else if (!calibrated && sampleCount > 0) {
    // Finalize calibration
    baseX /= sampleCount;
    baseY /= sampleCount;
    baseZ /= sampleCount;
    sampleCount = 0;
    calibrated = true;

    Serial.println("Calibration complete.");
    Serial.print("Base X: "); Serial.println(baseX);
    Serial.print("Base Y: "); Serial.println(baseY);
    Serial.print("Base Z: "); Serial.println(baseZ);
  }

  if (calibrated) {
    // Normal usage mode
    float deltaX = event.orientation.x - baseX;
    float deltaY = event.orientation.y - baseY;
    float deltaZ = event.orientation.z - baseZ;

    // Gesture detection
    if (deltaX > 15) Serial.println("Tilted Right");
    else if (deltaX < -15) Serial.println("Tilted Left");
    else Serial.println("Centered");

    // Print live values
    Serial.print("Raw X: "); Serial.print(event.orientation.x);
    Serial.print(" | Base X: "); Serial.print(baseX);
    Serial.print(" | ΔX: "); Serial.println(deltaX);

    Serial.print("Raw Y: "); Serial.print(event.orientation.y);
    Serial.print(" | Base Y: "); Serial.print(baseY);
    Serial.print(" | ΔY: "); Serial.println(deltaY);

    Serial.print("Raw Z: "); Serial.print(event.orientation.z);
    Serial.print(" | Base Z: "); Serial.print(baseZ);
    Serial.print(" | ΔZ: "); Serial.println(deltaZ);

    Serial.println("-----------");
  }

  delay(50);
}
