/**
 * Photosensitive Light Resisting Diode
 * @author Dedipyaman Das
 * github.com/2DSharp/BlueBerry
 * @version 1.0/17
 * 
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
 */
void initLDRSensor() {

  Serial.println("Starting LDR Sensor");
  pinMode(LDR_Pin, INPUT);
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
  /* *NEEDS TO BE FIXED!* */
  Serial.println("Light: ");

  if (abs(lastReading - readLightState()) > 0) {
    Serial.println("Light changed!");
  }
  if (counter > 2) {
    return (abs(lastReading - readLightState())) > 100;
  }
}

