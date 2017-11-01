/**
 * Runs the dog like a RC car
 * @author Dedipyaman Das
 * github.com/2DSharp/BlueBerry
 * @version 1.0/17
 *
 * Sloppily written
 */

int dir;

void rcMode() {

  getter();
  runCommand(dir);
}

void getter() {
    
  char rcCommand = Serial1.read();
  switch(rcCommand) {

    case 'a':

      dir  = 1;
      break;
    case 'd':

      dir = 2;
      break;
     case 's':
      dir = 3;
      break;
    case 'x':
      dir = 4;
      break;
    
    case 'w':
      dir = 5;
      break;
  }
}
void runCommand(int type) {

  switch(type) {

    case 1:

      turn(LEFT);
      Serial1.println("Turning left");
      break;

    case 2:
      turn(RIGHT);
      Serial1.println("Turning right");
      break;

    case 3:
      moveBackward(150);
      Serial1.println("Reversing");
      break;

    case 4:

      brake(1000);
      currentSpeed = getMotorSpeed();
      Serial1.println("Braking");
      break;

    case 5:
      moveForward(currentSpeed, 255);
      currentSpeed = getMotorSpeed();
      Serial1.println("Accelerating");
      break;
  }
}


