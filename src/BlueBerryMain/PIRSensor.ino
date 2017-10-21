/**
 * The sensor's output pin goes to HIGH if motion is present.
 * However, even if motion is present it goes to LOW from time to time, 
 * which might give the impression no motion is present. 
 * This program deals with this issue by ignoring LOW-phases shorter than a given time, 
 * assuming continuous motion is present during these phases.  
 *
 * the time we give the sensor to calibrate (10-60 secs according to the datasheet)
 */
#define CALIBRATION_TIME 30
/**
 *the time when the sensor outputs a low impulse
 */
long unsigned int lowIn;
/**
 * The amount of milliseconds the sensor has to be low
 * before we assume all motion has stopped
 */
#define PAUSE 500

#define PIR_PIN 48


boolean lockLow = true;
boolean takeLowTime;


int startTime;
int stopTime;
/*
 * Setting up the PIR
 */
void initPIRSensor(){
  Serial.println("Starting PIR Sensor");
  pinMode(PIR_PIN, INPUT);
  digitalWrite(PIR_PIN, LOW);

  /* Allow a few seconds of calibration */
  Serial.print("Calibrating PIR sensor ");

  for(int i = 0; i < CALIBRATION_TIME; i++){
    
    Serial.print(".");
    delay(1000);
  }
  
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
}
/*
 * Detect beginning of motion
 */
bool detectMotionChange() {

  return digitalRead(PIR_PIN) == HIGH ;
}
/* 
 * This keeps record of start and stop of motion
 */
void PIRMotionCounter(bool motionDetect) {
  /**
   * Run it only if motion was detected
   * Control inverted to the main calling function
   */
  if (motionDetect) {
    if(lockLow){
      /**
       * Makes sure we wait for a transition to LOW before any further output is made.
       */
      lockLow = false;

      startTime = millis()/1000;
      
      Serial.println("---");
      Serial.print("Motion detected at ");
      Serial.print(startTime);
      delay(1000);
      Serial.println(" sec");
      
      delay(50);
    }
  takeLowTime = true;
}

if(digitalRead(PIR_PIN) == LOW){

  if(takeLowTime){
    /*
     * Save the time of the transition from high to LOW
     */
    lowIn = millis();
    /*
     * Make sure this is only done at the start of a LOW phase
     */
    takeLowTime = false;       
  }
  /*
   * if the sensor is low for more than the given PAUSE,
   * we assume that no more motion is going to happen
   */
  if(!lockLow && millis() - lowIn > PAUSE){
    /* 
     * makes sure this block of code is only executed again after
     * a new motion sequence has been detected
     */ 
    lockLow = true;
    stopTime = (millis() - PAUSE)/1000;
    Serial.print("Motion ended at ");      

    Serial.println(" sec");
    delay(50);
  }
 }
}
