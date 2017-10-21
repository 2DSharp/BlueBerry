/**
 * Project BlueBerry Main controller
 * @author Dedipyaman Das
 * github.com/2DSharp/BlueBerry
 * @version 1.0/17 
 */
/**
 * Project BlueBerry's main sketch that integrates the other sketches
 * Upon compilation, it automagically includes all the dependencies.
 * This program runs the Arduino Mega and is responsible for running
 * the entire robot.
 */
int ledPin = 13;
bool motionDetected;
bool lightChanged;
int ldrCounter = 0;
/**
 * Setting as global for the Ultrasonic to access
 */
  //int lastDistance;
  int currentSpeed = 0;

void setup() {
  /*
   * Beginning the Serial.
   */
  Serial.begin(9600);
  /*
   * Initializing the modules.
   */
  //initLDRSensor();
  initUltrasonicSensor();
  //initPIRSensor();
  //initMotorDriver();
  //initGSMModule();
}

void loop() {
  /* 
   * Run the Arduino loop, we need a trigger from the bluetooth
   * TODO: set up modes
   */
   Serial.println("Distance: ");
   if (calculateDistance() > 10) {
    moveForward(currentSpeed, 255);
   }
   delay(500);
  
}
/**
 * Checks if any state has been changed.
 * This assumes that everything around will be at complete rest
 */


