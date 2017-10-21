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
  Serial.println("Starting Ultrasonic Sensor");
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
   Serial.println(lastDistance);
   return abs(calculateDistance() - lastDistance) > 10;
}
int calculateDistance() {

  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;

  Serial.println(distance);
  if (distance >= 1000 || distance <= 2){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }

  return 0;
}

bool pathClear() {

  return calculateDistance() > 10;
}
