/**
 * Runs the servo
 * @author Dedipyaman Das
 * github.com/2DSharp/BlueBerry
 * @version 1.0/17 
 */
#include <Servo.h>

Servo HorizontalServo;  
/**
 * Initializing position from 0
 */
int pos = 90;    
boolean clear;

void initServo() {
  Serial.println("Initializing servo...");
  /** 
   * HorizontalServo goes to pin 9
   */
  HorizontalServo.attach(9);
  HorizontalServo.write(90);
  Serial.println("Servo initialized");
}

boolean lookLeft() {
  
  for (pos = 90; pos >= 0; pos--) {
    
    HorizontalServo.write(pos);
    // The speed
    if (pathClear()) {

      clear = true;
    }
    delay(12);
  }

  return clear;
}
boolean lookRight() {
  
  for (pos = 90; pos <= 180; pos++) {

    HorizontalServo.write(pos);
    if (pathClear()) {

      clear = true;
    }
    delay(12);
  }

  return clear;
  }

void returnToMean() {

  HorizontalServo.write(90);
  delay(1000);
}
