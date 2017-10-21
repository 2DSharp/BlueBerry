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
int lastDistance;
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
  initMotorDriver();
  //initGSMModule();
}

void loop() {
  /* 
   * Run the Arduino loop, we need a trigger from the bluetooth
   * TODO: set up modes
   */
   Serial.println("Distance: ");
   Serial.println(calculateDistance());

  
}
/**
 * Checks if any state has been changed.
 * This assumes that everything around will be at complete rest
 */
boolean hasStateChanged() {
  /** 
   * Detecting any motion, light or distance change
   */
  motionDetected = detectMotionChange();
  /**
   * Putting a counter to start counting from the second iteration
   * Analog has fragile results
   */
  ldrCounter++;
  lightChanged = detectLightChange(ldrCounter, readLightState());
  
  int distanceChanged = detectDistanceChange(lastDistance);
  lastDistance = calculateDistance();
  /**
   * We need 2 out of 3 to be confirmed of some anomaly.
   * The bitwise doesn't seem to be particularly performant
   */
  Serial.println(motionDetected);
  Serial.println(lightChanged);
  Serial.println(distanceChanged);
  int totalSensorValue = motionDetected + lightChanged + distanceChanged;
  /**
   * Passed if >= 2, alert user.
   */
  return totalSensorValue >= 2;
}
/**
 * Alerts user- vigilante mode
 */
void alert() {

  Serial.println("Anomaly detected");
  sendSMSAlert("7005308234", "There was some problem detected around your device");
  /*bark();
  
  */
}



