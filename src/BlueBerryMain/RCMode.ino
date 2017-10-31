/**
 * Runs the dog like a RC car
 * @author Dedipyaman Das
 * github.com/2DSharp/BlueBerry
 * @version 1.0/17
 */
void rcMode() {

  char rcCommand = Serial1.read();
  switch(rcCommand) {

    case '6':
      turn(LEFT);
      Serial1.println("Turning left");
      delay(1500);
      break;
    case '7':
      turn(RIGHT);
      delay(1500);
      break;
     case '8':
      brake(1500);
      Serial1.println("Braking");
      break; 
    case '9':
      moveBackward(255);
      Serial1.println("Moving backwards");
      break;
    default: 
      moveForward(currentSpeed, 255);
      currentSpeed = getMotorSpeed();
      Serial1.println("Accelerating");
      break;

  }
}


