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

#include <Wire.h>
 
#define LEFT 1
#define RIGHT 2
#define TRIGGER 22
#define RECEIVER 23
#define RESET 26
#define LED_SEQUENCE 28
const char WALK_MODE = 'w';
const char VIGILANCE_MODE = 'v';
const char RESET_MODE = 'r';
const char RC_MODE = 'b';
int ledPin = 13;
bool motionDetected;
bool lightChanged;
int previousLightState;
int ldrCounter = 0;
int runningMode;
char mode;
/**
 * Setting as global for the Ultrasonic to access
 */
int lastDistance;
int currentSpeed = 0;
int direction;
int response = 0;
void setup() {
  /*
   * Beginning the Serial.
   */
  Serial.begin(9600);
  /*
   * Initializing the modules.
   */
  pinMode(RESET, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(RECEIVER, INPUT);
  pinMode(LED_SEQUENCE, OUTPUT);
  digitalWrite(LED_SEQUENCE, HIGH);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  delay(5000);
  Wire.onRequest(requestEvent);
  if (response == 0) {
    setup();
  }
  
  Serial.println("All set, let's roll!");
  digitalWrite(ledPin, HIGH);
}
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {

  mode = Wire.read();    // receive byte as an integer
  response = 1; // Can continue now
  initUltrasonicSensor();
  initGSMMessageSender();
  init(mode);
  
}
void requestEvent() 
{
  Wire.write(mode);
}
void init(char mode) {

  switch(mode) {
    
    case VIGILANCE_MODE:
      initLDRSensor();
      initPIRSensor();
      break;
    case RC_MODE:
      initMotorDriver();
      break;
    case WALK_MODE:
      initMotorDriver();
      initServo();
      break;
    case RESET_MODE:
      setup();
      break;
  }
}
void loop() {
  /* 
   * Run the Arduino loop, we need a trigger from the bluetooth
   * TODO: set up modes
   */
   digitalWrite(TRIGGER, LOW);
   if (digitalRead(RESET) == HIGH) {

    setup();
   }

   switch (mode) {
    
    case VIGILANCE_MODE:
      vigilanteMode();
      delay(1000);
      break;
      
    case WALK_MODE:
      digitalWrite(LED_SEQUENCE, HIGH);
      walkMode();
      delay(500); 
      break;
      
     case RC_MODE:
      rcMode();
      delay(500);
      break;
   }

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
  //Serial.println(digitalRead(RECEIVER));
  if (digitalRead(RECEIVER) == HIGH) {
    Serial.println("Receiver is high");
  //  stopAlert();
    makeNoise();
    
    //return;
  }
  /**
   * Keep checking if some motion was detected
   */
  else {
    Serial.println("Receiver is low");
    motionDetected = false;
    if (hasStateChanged()) {
      Serial.println("Anomaly detected");
      sendAlert();
     //delay(60000);
    }
    noTone(8); 
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
void rcMode() {

  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveRCCommand); // register event
  moveForward(currentSpeed, 255);
  currentSpeed = getMotorSpeed();
}

void receiveRCCommand(int howMany) {
  
  char rcDirection = Wire.read();

  switch(rcDirection) {

    case '6':
      turn(1);
      Serial.println("Turning left");
      digitalWrite(13, HIGH);
      delay(1500);
      break;
    case '7':
      turn(2);
      digitalWrite(13, LOW);
      Serial.println("Turning right");
      delay(1500);
      break;
     case '8':
      brake(1500);
      Serial.println("Braking");
      break; 
  }
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
  digitalWrite(LED_SEQUENCE, HIGH);
  if (pathClear(30)) {
    
    moveForward(currentSpeed, 255);
    currentSpeed = getMotorSpeed();
  }
  
  else {

    brake(1000);
    digitalWrite(LED_SEQUENCE, LOW);
    Serial.println("Braking");
   // moveBackward(100);
   // delay(2000);
   // brake(1000);
    /**
     * Analyse
     */
    int clearDirection;
    bool val;
    
    digitalWrite(LED_SEQUENCE, HIGH);
    if (lookRight()) {  
      //Serial.println(val);
      returnToMean();
      clearDirection = RIGHT;
    }

    else if (lookLeft()) {

      returnToMean();
      clearDirection = LEFT;
    }
    
    digitalWrite(LED_SEQUENCE, LOW);
    digitalWrite(LED_SEQUENCE, HIGH);
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
  if (!pathClear(30)){
    
    turn(direction);
    steer(direction);
  }
  
  else {

    brake(1000);
  }
}
