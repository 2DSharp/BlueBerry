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
#include <EEPROM.h>
#define LEFT 1
#define RIGHT 2
//#define TRIGGER 22
//#define RECEIVER 23
//#define RESET 26
#define LED_SEQUENCE 28

const char VIGILANCE_MODE = '1';
const char WALK_MODE = '2';
const char RC_MODE = '3';
const char RESET_MODE = 'r';
const char ALERT_RECEIVED = 's';
const char ABORT_ALERT = 'a';
int ledPin = 13;
char input;
bool motionDetected;
bool lightChanged;
int previousLightState;
int ldrCounter = 0;
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
  Serial1.begin(9600);
  Serial.begin(9600);
  Wire.begin(); 
  /*
   * Initializing the modules.
   */  
   unsigned char buff[4];

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(LED_SEQUENCE, OUTPUT);

  blinkLED(LED_SEQUENCE, 500, 4);
  Serial1.println("Project Blueberry!");
  unsigned char value;
 /* Serial.println("EEPROM value: ");
 for (int i =0; i <4; i++) {

   value = EEPROM.read(i);
   Serial1.println(value);
}
*/
  getPassword();
  showPassword();
  if (!checkPassword()) {
    setup();
    return;
  }

  showDefaultSelectionUI();
  getModePreference();
  mode = input;
  showSelectedModeDescription(mode);
  Serial1.println("-----");

  initialize(mode);

  Serial1.println("All set, let's roll!");
  blinkLED(LED_SEQUENCE, 1000, 2);
}

void initialize(char initMode) {
     
  Serial1.println("Initializing modules...");

  initUltrasonicSensor();
  initGSMMessageSender();

  switch(initMode) {
    
    case VIGILANCE_MODE:
      Serial1.println("Initializing Vigilance mode...");
      initLDRSensor();
      initPIRSensor();
      delay(120000);
      break;
    case RC_MODE:    
      Serial1.println("Initializing RC mode...");
      initMotorDriver();
      break;
    case WALK_MODE:
      Serial1.println("Initializing Walk mode...");
      initMotorDriver();
      initServo();
      break;
    case RESET_MODE:
      setup();
      break;
      return;
  }
}
void loop() {
  /* 
   * Run the Arduino loop, we need a trigger from the bluetooth
   */

  if (Serial1.read() == RESET_MODE) {

    initialize(RESET_MODE);
  }
  switch (mode) {
    
      case VIGILANCE_MODE:
    	  vigilanceMode();
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

