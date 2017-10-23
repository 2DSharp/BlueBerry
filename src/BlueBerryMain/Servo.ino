/**
 * Interface for the GSM module and the main arduino
 * @author Dedipyaman Das
 * github.com/2DSharp/BlueBerry
 * @version 1.0/17 
 */
#include <Servo.h>

Servo HorizontalServo;  
/**
 * Initializing position from 0
 */
int pos = 0;    

void initServo() {
  /** 
   * HorizontalServo goes to pin 9
   */
  HorizontalServo.attach(9); 
}

void horizontalLookOut(bool pause) {
  /**
   * Check if some one wants to pause the movement
   */
  if (pause == false) {
    /**
     * Keep looking around 0 to 180 degrees
     */
    for (pos = 0; pos <= 180; pos++) {
    
      HorizontalServo.write(pos);
      // The speed
      delay(15);
    }
    /**
     * Come back from 180 to 0 degrees
     */
    for (pos = 180; pos >= 0; pos--) {

      HorizontalServo.write(pos);
      delay(15);
    }
  }
}