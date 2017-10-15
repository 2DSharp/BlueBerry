#define LDR_Pin A0
int LDRReading;
int initialReading;
/**
 * Initializing the sensor with default values
 */
void initLDRSensor() {
  Serial.println("Starting LDR Sensor");
  detectLightChange(0, readLightState());
}
/**
 * Reads the current analog value of the input light source
 */
int readLightState(){

  return analogRead(LDR_Pin);
}
/**
 * Check if any significant light change
 */
bool detectLightChange(int counter, int lastReading) {
  
  if (counter > 2) {
    return (abs(lastReading - readLightState())) > 100;
  }
}

