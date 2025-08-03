#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
//Stateful Gesture
enum GestureState { CENTERED, LEFT, RIGHT, UP, DOWN };
GestureState currentGesture = CENTERED;
GestureState newGesture = CENTERED;

void setup() {
  Serial.begin(115200);
  if (!bno.begin()) {
    Serial.println("BNO055 not detected. Can't proceed!");
    while (1);
  }
  delay(1000);
}

//Function Mapping
void moveRight() {Serial.println("Moving Right");}
void moveLeft() {Serial.println("Moving Left");}
void moveUp() {Serial.println("Moving Up");}
void moveDown() {Serial.println("Moving Down");}

void hover() { Serial.println("Hovering"); }

void loop() {
  // Get acceleration (m/s^2)
  imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);

  float ax = accel.x();
  float ay = accel.y();
  float az = accel.z();

  if (ax > 3) newGesture = RIGHT;
  else if (ax < -3) newGesture = LEFT;
  else if (ay > 3) newGesture = UP;
  else if (ay < -3) newGesture = DOWN;
  else newGesture = CENTERED;

/*
  // Detect tilt
  if (ax > 3) Serial.println("Tilt Right");
  else if (ax < -3) Serial.println("Tilt Left");
  else if (ay > 3) Serial.println("Tilt Up");
  else if (ay < -3) Serial.println("Tilt Down");
  else Serial.println("Centered");
*/

  if (newGesture != currentGesture) {
    currentGesture = newGesture;
    switch (currentGesture) {
        case RIGHT: moveRight(); break;
        case LEFT:  moveLeft(); break;
        case UP:    moveUp(); break;
        case DOWN:  moveDown(); break;
        case CENTERED: hover(); break;
    }
}

/*
  // Debug values
  Serial.print("AX: "); Serial.print(ax);
  Serial.print(" AY: "); Serial.print(ay);
  Serial.print(" AZ: "); Serial.println(az);
*/

  delay(100);
}
