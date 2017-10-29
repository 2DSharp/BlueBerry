/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 90;    // variable to store the servo position

void setup() {
  Serial.begin (9600);
  pinMode(28, OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.println("Starting");
  
}

void loop() {

 digitalWrite(28, HIGH);
 delay(1000);
 for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
  
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(12);                       // waits 15ms for the servo to reach the position
  }
    Serial.write("working");
  myservo.write(90);
  
  delay(1000);
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(12);                       // waits 15ms for the servo to reach the position
  }
  myservo.write(90);

  
 digitalWrite(28, LOW);
 delay(1000);
}

