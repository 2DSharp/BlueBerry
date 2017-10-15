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

void setup() {
  /*
   * Beginning the Serial.
   */
  Serial.begin(9600);
  /*
   * Initializing the modules.
   */
  initPIRSensor();
  initLDRSensor();
  initUltrasonicSensor();
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
  int totalSensorValue = motionDetected + lightChanged + distanceChanged;
  /**
   * Passed if >= 2, alert user.
   */
  return totalSensorValue >= 2;
}

void alert() {

  Serial.print("Anomaly detected");
  /*bark();
    sendSMSAlert();
  */
}
void loop() {
  /* 
   * Run the Arduino loop
   */
  if (hasStateChanged()) {

    alert();
  }

}


