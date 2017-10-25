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
#define LEFT 1
#define RIGHT 2
#define RECEIVER 23

int ledPin = 13;
bool motionDetected;
bool lightChanged;
int previousLightState;
int ldrCounter = 0;
/**
 * Setting as global for the Ultrasonic to access
 */
int lastDistance;
int currentSpeed = 0;
int direction;
void setup() {
  /*
   * Beginning the Serial.
   */
  Serial.begin(9600);
  /*
   * Initializing the modules.
   */
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  initGSMMessageSender();
  initLDRSensor();
  initUltrasonicSensor();
  initPIRSensor();
  initMotorDriver();
  initServo();
  
  Serial.println("All set, let's roll!");
  digitalWrite(ledPin, HIGH);
}

void loop() {
  /* 
   * Run the Arduino loop, we need a trigger from the bluetooth
   * TODO: set up modes
   */
   vigilanteMode();
   //walkMode();
   delay(500);
}
/**
 * Vigilante mode
 * Intrusion detection and notification system
 */
void vigilanteMode() {
  /**
   * The notification was sent
   * Make some noise till they ask you to stop
   */
  if (digitalRead(RECEIVER) == HIGH) {

    stopAlert();
    makeNoise();
    return;
  }
  /**
   * Keep checking if some motion was detected
   */
  motionDetected = false;
  if (hasStateChanged()) {
    Serial.println("Anomaly detected");
    sendAlert();
    //delay(60000);
  }
}
/**
 * Checks if any state has been changed.
 * This assumes that everything around will be at complete rest
 */
boolean hasStateChanged() {
  /** 
   * Detecting any motion, light or distance change
   */
  detectMotionChange();
  /**
   * Putting a counter to start counting from the second iteration
   * Analog has fragile results
   */
  int currentLightState = readLightState(); 
  int lightChanged = detectLightChange(previousLightState, currentLightState);
  
  previousLightState = currentLightState;
  
  int distanceChanged = detectDistanceChange(lastDistance);
  lastDistance = calculateDistance();
  /**
   * We need 2 out of 3 to be confirmed of some anomaly.
   * The bitwise doesn't seem to be particularly performant
   */
  Serial.println("Motion");
  Serial.println(motionDetected);
  Serial.println("Light");
  Serial.println(lightChanged);
  Serial.println("Distance");
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

}
/**
 * The friendly walk mode is basically an obstacle avoiding mode
 * Can be used for taking the dog out for a walk.
 * Guidance for the blind, if you may.
 */
void walkMode() {
  /**
   * Keep moving forward as long as the path is clear
   */
  if (pathClear()) {
    
    moveForward(currentSpeed, 255);
    currentSpeed = getMotorSpeed();
  }
  
  else {

    brake(1000);
    Serial.println("Braking");
    /**
     * Analyse
     */
    int clearDirection;
    bool val;
    if (lookRight()) {
      //Serial.println(val);
      returnToMean();
      clearDirection = RIGHT;
    }

    else if (lookLeft()) {

      returnToMean();
      clearDirection = LEFT;
    }

    returnToMean();
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
  if (!pathClear()){
    
    turn(direction);
    steer(direction);
  }
  
  else {

    brake(1000);
  }
}
