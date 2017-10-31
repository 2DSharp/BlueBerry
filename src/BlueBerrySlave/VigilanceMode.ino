/**
 * Vigilante mode
 * Intrusion detection and notification system
 */
void vigilanteMode() {
  /**
   * The notification was sent
   * Make some noise till they ask you to stop
   */

  Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8
  /**
   * Check if there was some input from the slave device
   */
  if (Wire.available()) {
    
    char messageStatus = Wire.read();
    if (messageStatus == ALERT_RECEIVED)  {
          
      makeNoise();
      vigilanteMode();
      return;
    }

    else if (messageStatus == ABORT_ALERT) {
      /**
       * Stop the buzzer
       * Wait for 2 minutes
       */
      noTone(8);
      delay(120000);
    }
    else {
      /**
       * Keep checking if some motion was detected
       */
      motionDetected = false;
      
      if (hasStateChanged()) {

	Serial.println("Anomaly detected");
	/**
	 * Send an alert as long as the status of the message doesn't change
	 */
	while (messageStatus != ALERT_RECEIVED) {
	  
	  sendAlert();
	  messageStatus = Wire.read();
	}
      }
    }
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
