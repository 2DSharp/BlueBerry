/**
 * Ultrasonic Sensor Driver
 * @author Dedipyaman Das
 * github.com/2DSharp/BlueBerry
 * @version 1.0/17
 * 
 */
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
  Serial.println("Initializing Ultrasonic Sensor...");
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
  Serial.println("Ultrasonic sensor initialized");
}
/**
 * Returns true if a distance change was detected 
 */
bool detectDistanceChange(int lastDistance) {
  /**
   * The accuracy seems to be quite convincing
   * 10 seems to be significant
   */
  // Serial.println(lastDistance);
   return abs(calculateDistance() - lastDistance) > 10;
}
/**
 * Calculates the approx distance with Ultrasonic
 */
int calculateDistance() {
  /**
   * Echo duration set, use the PWM pins
   */
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
   * Receive the wave
   * Calculate duration
   */
  duration = pulseIn(ECHO_PIN, HIGH);
  /**
   * Calculate distance from duration
   */
  distance = (duration/2) / 29.1;
  
  if (distance >= 300 || distance <= 2){
    Serial.println("Out of range");
    
  }
  else {

    return distance;
  }
}

bool pathClear() {

  return calculateDistance() > 10;
}
