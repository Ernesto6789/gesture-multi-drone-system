#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);

void setup() {
  Serial.begin(115200);
  if (!bno.begin()) {
    Serial.println("BNO055 not detected. Can't proceed!");
    while (1);
  }
  delay(1000);
}

//Stateful Gesture
enum GestureState { CENTERED, LEFT, RIGHT, UP, DOWN };
GestureState currentGesture = CENTERED;

void loop() {
  // Get acceleration (m/s^2)
  imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  float ax = accel.x();
  float ay = accel.y();
  float az = accel.z();

/*
  // Detect tilt
  if (ax > 3) Serial.println("Tilt Right");
  else if (ax < -3) Serial.println("Tilt Left");
  else if (ay > 3) Serial.println("Tilt Up");
  else if (ay < -3) Serial.println("Tilt Down");
  else Serial.println("Centered");
*/

  GestureState newGesture = CENTERED;

  if (ax > 3) newGesture = RIGHT;
  else if (ax < -3) newGesture = LEFT;
  else if (ay > 3) newGesture = UP;
  else if (ay < -3) newGesture = DOWN;

  if (newGesture != currentGesture) {
      currentGesture = newGesture;

    if (currentGesture == RIGHT) Serial.println("Currrent Gesture: Tilted Right");
    else if (currentGesture == LEFT) Serial.println("Current Gesture: Tilted Left");
    else if (currentGesture == UP) Serial.println("Current Gesture: Tilted Up");
    else if (currentGesture == DOWN) Serial.println("Current Gesture: Tilted Down");
    else Serial.println("Gesture: Centered");
  }

/*
  // Debug values
  Serial.print("AX: "); Serial.print(ax);
  Serial.print(" AY: "); Serial.print(ay);
  Serial.print(" AZ: "); Serial.println(az);
*/

  delay(100);
}
