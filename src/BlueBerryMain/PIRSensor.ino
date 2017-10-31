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
  Serial.println("Initializing PIR Sensor");
  pinMode(PIR_PIN, INPUT);
  digitalWrite(PIR_PIN, LOW);

  /* Allow a few seconds of calibration */
  Serial.print("Calibrating PIR sensor ");

  for(int i = 0; i < CALIBRATION_TIME; i++){
    
    Serial.print(".");
    delay(1000);
  }
  
  Serial.println(" done");
  Serial.println("PIR Sensor initialized");
  delay(50);
}
/*
 * Detect beginning of motion
 */
void detectMotionChange() {

    if(digitalRead(PIR_PIN) == HIGH){

    if(lockLow){
      //makes sure we wait for a transition to LOW before any further output is made:
      lockLow = false;

      motionDetected = true;
      Serial.println("Motion detected");  
      delay(1500);
    }
    takeLowTime = true;
  }

  if(digitalRead(PIR_PIN) == LOW){

    if(takeLowTime){
      lowIn = millis();          //save the time of the transition from high to LOW
      takeLowTime = false;       //make sure this is only done at the start of a LOW phase
    }
    //if the sensor is low for more than the given pause,
    //we assume that no more motion is going to happen
    if(!lockLow && millis() - lowIn > PAUSE){
      //makes sure this block of code is only executed again after
      //a new motion sequence has been detected
      lockLow = true;
      delay(50);
    }
  }
}
