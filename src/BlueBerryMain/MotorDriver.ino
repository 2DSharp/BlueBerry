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
#define LEFT_FORWARD 7
#define LEFT_BACKWARD 9
/**
 * Motor two - RIGHT
 */
#define RIGHT_SPEED 10
#define RIGHT_FORWARD 11
#define RIGHT_BACKWARD 13
/**
 * Charge up the engine, set the right pins
 * Everything is in outputs
 */
void initMotorDriver() {

  Serial.println("Starting engine!");
  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(RIGHT_SPEED, OUTPUT);

  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_BACKWARD, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_BACKWARD, OUTPUT);  

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

    currentSpeed = i;
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
    
    currentSpeed = i;
    analogWrite(RIGHT_SPEED, i);
    analogWrite(LEFT_SPEED, i);
    delay(40);
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
  
  analogWrite(LEFT_SPEED, 10);
  analogWrite(RIGHT_SPEED, 100);
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

  analogWrite(RIGHT_SPEED, 10);
  analogWrite(LEFT_SPEED, 100);
}
/**
 * Stops the vehicle gradually depending on the current speed.
 */
void brake() {
  /**
   * Gradual deceleration from maximum speed to zero
   */
  for (int i = currentSpeed ; i >= 0; --i) {

    analogWrite(RIGHT_SPEED, i);
    analogWrite(LEFT_SPEED, i);
    delay(10);

    currentSpeed = i;
  }
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
