#include "Servo_mod.h"


void servoRun(int from_, int to_);

Servo myServo;

uint32_t servoSpeed = 20;  // in millisecs

void servoRun(int from_, int to_) {

  static int pos = 0;
  Serial.print("Servo moving from: ");
  Serial.print(from_);
  Serial.print(" to: ");
  Serial.println(to_);

  if ( to_ > from_ ) {
    //  Serial.println(" to > from ");
    myServo.attach(servoPin);
    for ( int x = from_; x < to_; x++ ) {
      myServo.write(x);
      delay(servoSpeed);
    }
    myServo.detach();  // avoid jiggering
  }

  else {
    // Serial.println(" to < from ");
    myServo.attach(servoPin);
    for ( int x = from_; x >= to_; x-- ) {
      myServo.write(x);
      delay(servoSpeed);
    }
    myServo.detach();  // avoid jiggering
  }
  Serial.println();
}
