/**
HC-SR04 Ping distance sensor
VCC to Arduino 5V
GND to Arduino GND
Echo to Arduino pin 13
Trig to Arduino pin 12
*/
#define TRIG_PIN 12 
#define ECHO_PIN 13

void initUltrasonicSensor() {
  /**
   * TRIG_PIN sends an ultrasonic wave
   */
  pinMode(TRIG_PIN, OUTPUT);
  /** 
   * ECHO_PIN receives the echo from the object
   */
  pinMode(ECHO_PIN, INPUT);
  /** 
   * Get a default value for beginning the loop
   */
  lastDistance = calculateDistance();
}
/**
 * Returns true if a distance change was detected 
 */
bool detectDistanceChange(int lastDistance) {
  /**
   * The accuracy seems to be quite convincing
   * 2 seems to be significant
   */
  return abs(calculateDistance() - lastDistance) > 2;
}
int calculateDistance() {
  
  long duration, distance;
  /**
   * Send the wave 
   */
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  /**
   * Receive the echo-ed wave
   */
  duration = pulseIn(ECHO_PIN, HIGH);
  /**
   * Taking the analog value in meters
   */
  distance = (duration/2) / 29.1;

  return distance; 
}
