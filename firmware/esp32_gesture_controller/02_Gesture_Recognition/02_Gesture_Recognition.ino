#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
//Stateful Gesture
enum GestureState { CENTERED, LEFT, RIGHT, UP, DOWN };
GestureState currentGesture = CENTERED;
GestureState newGesture = CENTERED;

//Tilt Thresholds
float onThreshold = 3.0;
float offThreshold = 2.0; // Slightly lower for hysteresis

//Double Tap Thresholds
float tapThreshold = 15.0; // m/s², tune this
unsigned long lastTapTime = 0;
unsigned long doubleTapWindow = 300; // ms
bool firstTapDetected = false;



void setup() 
{
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

void detectTilt(float ax, float ay)
{
  if (currentGesture == CENTERED) {
    if (ax > onThreshold) newGesture = RIGHT;
    else if (ax < -onThreshold) newGesture = LEFT;
    else if (ay > onThreshold) newGesture = UP;
    else if (ay < -onThreshold) newGesture = DOWN;
  } 
  else if (currentGesture == RIGHT && ax < offThreshold) {
    newGesture = CENTERED;
  }
  else if (currentGesture == LEFT && ax > -offThreshold) {
    newGesture = CENTERED;
  }
  else if (currentGesture == UP && ay < offThreshold) {
    newGesture = CENTERED;
  }
  else if (currentGesture == DOWN && ay > -offThreshold) {
    newGesture = CENTERED;
  }
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
}

void detectDoubleTap(float ax, float ay, float az)
{
  float magnitude = sqrt(ax * ax + ay * ay + az * az);

    if (magnitude > tapThreshold) {
      unsigned long now = millis();

      if (!firstTapDetected) {
        firstTapDetected = true;
        lastTapTime = now;
      } 
      else if (now - lastTapTime <= doubleTapWindow) {
        Serial.println("Double tap detected!");
        firstTapDetected = false; // reset
      } 
      else {
        // Too slow, treat as new first tap
        lastTapTime = now;
      }
    }
}

void loop() 
{
  // Get acceleration (m/s^2)
  imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  float ax = accel.x();
  float ay = accel.y();
  float az = accel.z();

  detectTilt(ax, ay);
  detectDoubleTap(ax, ay, az);

  delay(10);
}

/*
  // Debug values
  Serial.print("AX: "); Serial.print(ax);
  Serial.print(" AY: "); Serial.print(ay);
  Serial.print(" AZ: "); Serial.println(az);
  delay(100);
*/

  
