/**
 * Photosensitive Light Resisting Diode
 * @author Dedipyaman Das
 * github.com/2DSharp/BlueBerry
 * @version 1.0/17
 */
/**
 * 
 * Gives out analog values depending on the amount of light around
 */
#define LDR_Pin A0

int LDRReading;
int initialReading;
/**
 * Initializing the sensor with default values
 * Since we are checking change.
 */
void initLDRSensor() {

  Serial.println("Initializing LDR Sensor...");
  pinMode(LDR_Pin, INPUT);
  /**
   * Setting an initial reading for reference to the next iterations
   */
  previousLightState = readLightState();
  delay(2000);
  Serial.println("LDR initialized");
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
bool detectLightChange(int lastReading, int currentReading) {
  
  int change = abs(lastReading - currentReading);
  return change > 10;
}

