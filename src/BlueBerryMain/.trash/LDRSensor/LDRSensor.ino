int LDR_Pin = A1; 
int LDRReading;
int initialReading;
/**
 * Initializing the sensor with default values
 */
void initLDRSensor() {
  detectLightChange(0, readLightState());
}
/**
 * Reads the current analog value of the input light source
 */
int readLightState(){

  LDRReading = analogRead(LDR_Pin);
  return LDRReading;
}
/**
 * Check if any significant light change
 */
bool detectLightChange(int counter, int lastReading) {
  
  if (counter > 2) {
    return (abs(lastReading - readLightState())) > 100;
  }
}

