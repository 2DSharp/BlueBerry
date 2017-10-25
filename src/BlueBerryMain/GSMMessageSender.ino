/**
 * Interface for the GSM module and the main arduino
 * @author Dedipyaman Das
 * github.com/2DSharp/BlueBerry
 * @version 1.0/17 
 */
/**
 * This is not necessary
 * But since the main arduino connections went messy
 * And for some reason the GSM wasn't working with that one
 * Also that we had an extra Uno
 * This uno runs independently, checks if the other board wants to send an SMS
 */
#define TRIGGER 22

void initGSMMessageSender() {

  Serial.println("Starting GSM interface");
  pinMode(TRIGGER, OUTPUT);
  digitalWrite(TRIGGER, LOW);
  Serial.println("Initialized GSM interface");
}
/**
 * Talk to the other Arduino
 */
void sendAlert() {

  digitalWrite(TRIGGER, HIGH);
  delay(10000);
}
/**
 * To avoid continual alerts to the user
 */
void stopAlert() {

  digitalWrite(TRIGGER, HIGH);
}
