/**
 * The friendly walk mode is basically an obstacle avoiding mode
 * Can be used for taking the dog out for a walk.
 * Guidance for the blind, if you may.
 * 
 * @author Dedipyaman Das
 * github.com/2DSharp/BlueBerry
 * @version 1.0/17
 */
void walkMode() {
  /**
   * Keep moving forward as long as the path is clear
   */
  digitalWrite(LED_SEQUENCE, HIGH);
  if (pathClear(30)) {
    
    moveForward(currentSpeed, 255);
    currentSpeed = getMotorSpeed();
  }
  
  else {

    brake(1000);
    digitalWrite(LED_SEQUENCE, LOW);
    /**
     * Analyse
     */
    int clearDirection;
    bool val;
    
    digitalWrite(LED_SEQUENCE, HIGH);
    if (lookRight()) {  
      //Serial1.println(val);
      returnToMean(RIGHT);
      clearDirection = RIGHT;
    }

    else if (lookLeft()) {

      returnToMean(LEFT);
      clearDirection = LEFT;
    }

    blinkLED(LED_SEQUENCE, 1000, 2);
    steer(clearDirection);
  }
}
/**
 * Steers the locomotive with the predetermined side
 * Use ultrasonic to see path clearance
 */
void steer(int direction) {
  /**
   * The ultrasonic keeps looking from the mean position for clearance
   */
  if (!pathClear(30)){
    
    turn(direction);
    steer(direction);
  }
  
  else {

    brake(1000);
  }
}
