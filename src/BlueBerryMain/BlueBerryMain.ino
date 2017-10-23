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
int previousLightState;
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
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  initGSMMessageSender();
  initLDRSensor();
  initUltrasonicSensor();
  initPIRSensor();
  initMotorDriver();

  Serial.println("All set, let's roll!");
  digitalWrite(ledPin, HIGH);
}

void loop() {
  /* 
   * Run the Arduino loop, we need a trigger from the bluetooth
   * TODO: set up modes
   */
   motionDetected = false;
   if (hasStateChanged()) {
     alert();
     delay(60000);
   }

   delay(500);
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

  Serial.println("Anomaly detected");
  sendSMSAlert();
  makeNoise();
}



