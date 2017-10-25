/**
 * Motor Controller Driver
 * @author Dedipyaman Das
 * github.com/2DSharp/BlueBerry
 * @version 1.0/17
 * 
 */
/**
 * Motor one - LEFT
 */
#define LEFT_SPEED 6
#define LEFT_FORWARD 50
#define LEFT_BACKWARD 51
/**
 * Motor two - RIGHT
 */
#define RIGHT_SPEED 7
#define RIGHT_FORWARD 53
#define RIGHT_BACKWARD 52
/**
 * Charge up the engine, set the right pins
 * Everything is in outputs
 */
int motorSpeed;

void initMotorDriver() {

  Serial.println("Starting motor engine...");
  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(RIGHT_SPEED, OUTPUT);

  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_BACKWARD, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_BACKWARD, OUTPUT);
  Serial.println("Motors active");

}
/** 
 * Makes the vehicle move forward to the speed based on the controller.
 * Gradual acceleration.
 * Forwards stay high, backwards stay low
 */
void moveForward(int minSpeed, int maxSpeed) {

  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);  
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_BACKWARD, LOW); 
  /**
   * Gradual acceleration from 0 to max speed
   */
  for (int i = minSpeed; i < maxSpeed; i++)  {

    motorSpeed = i;
    analogWrite(RIGHT_SPEED, i);
    analogWrite(LEFT_SPEED, i);
    delay(15);
  }
}
/**
 * Reverse motion, just in case
 * Lower acceleration to emulate real life scenario
 * Forwards stay low, backwards stay high
 */
void moveBackward(int speed) {

  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, HIGH);  
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, HIGH); 
  /**
   * Gradual acceleration from 0 to max speed
   */
  for (int i = 0; i < speed; i++)  {
    
    motorSpeed = i;
    analogWrite(RIGHT_SPEED, i);
    analogWrite(LEFT_SPEED, i);
    delay(40);
  } 
}
/**
 * Getter for the current speed of the motor
 * I can't stand global variables between scopes, sorry
 */
int getMotorSpeed() {

  return motorSpeed;
}
/**
 * Turns depending on the availability of space
 */
void turn(int direction) {

  if (direction == 1) {
    turnForwardLeft();
  }
  else if (direction == 2) {
    turnForwardRight();
  }
}
/** 
 * Turns the vehicle to the left
 * Slows down the left motor, keeps the right one running
 */
void turnForwardLeft() {
  /**
   * We need only forward motion for this one
   */
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);  
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_BACKWARD, LOW); 
  
  analogWrite(LEFT_SPEED, 0);
  analogWrite(RIGHT_SPEED, 150);
  delay(1000);
}
/** 
 * Turns the vehicle to the right
 * Slows down the right motor, keeps the left one running
 */
void turnForwardRight() {

  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD, LOW);  
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_BACKWARD, LOW); 

  analogWrite(RIGHT_SPEED, 0);
  analogWrite(LEFT_SPEED, 150);
}
/**
 * Stops the vehicle gradually depending on the current speed.
 */
void brake(int duration) {
  /**
   * Gradual deceleration from maximum speed to zero
   */
  for (int i = motorSpeed ; i >= 0; --i) {

    analogWrite(RIGHT_SPEED, i);
    analogWrite(LEFT_SPEED, i);
    delay(0);

    motorSpeed = i;
  }
  delay(duration);
}
/**
 * To be called just in case an obstacle comes out of nowhere
 * No gradual deceleration, immediate stoppage
 * Might damage the motors, use only when absolutely needed
 */
void emergencyBrake() {
  /** 
   * Turning of all motors
   */
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD, LOW);  
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACKWARD, LOW);  
}
