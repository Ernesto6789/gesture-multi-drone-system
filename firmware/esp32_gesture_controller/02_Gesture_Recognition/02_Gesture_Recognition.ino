#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
//Stateful Gesture
enum GestureState { CENTERED, LEFT, RIGHT, UP, DOWN };
enum TwistState { TWIST_CENTERED, FORWARD, BACKWARD };

GestureState currentGesture = CENTERED;
TwistState currentTwistGesture = TWIST_CENTERED;
GestureState newGesture = CENTERED;
TwistState newTwistGesture = TWIST_CENTERED;

//Tilt Thresholds
float onThreshold = 3.0;
float offThreshold = 2.0; //Hysterisis

//Gryro Thresholds
float twistOnThreshold = 30;
float twistOffThreshold = 25; //Hysterisis

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
void moveForward(){Serial.println("Moving Foward");}
void moveBackward(){Serial.println("Moving Backward");}
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

void detectFowardBackMotion(float gz)
{
  if (currentTwistGesture == TWIST_CENTERED){
    if (gz > twistOnThreshold) newTwistGesture = FORWARD;
    else if (gz < -twistOnThreshold) newTwistGesture = BACKWARD;
  } 
  else if (currentTwistGesture == FORWARD && gz < twistOffThreshold){
    newTwistGesture = TWIST_CENTERED;
  } 
  else if (currentTwistGesture == BACKWARD && gz > -twistOffThreshold){
    newTwistGesture = TWIST_CENTERED;
  }

  if (newGesture != currentTwistGesture) {
    currentTwistGesture = newTwistGesture;
    switch (currentTwistGesture) {
        case FORWARD: moveForward(); break;
        case BACKWARD:  moveBackward(); break;
    }
  }
}


void loop() 
{
  // Get acceleration (m/s^2)
  imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  // Get gyro rotation (degrees/sec)
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

  float ax = accel.x();
  float ay = accel.y();
  float az = accel.z();
  float gz = gyro.z();

  detectTilt(ax, ay);
  detectFowardBackMotion(gz);
  delay(10);
}

/*
  // Debug values
  Serial.print("AX: "); Serial.print(ax);
  Serial.print(" AY: "); Serial.print(ay);
  Serial.print(" AZ: "); Serial.println(az);
  delay(100);
*/

  
