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

  pinMode(TRIGGER, OUTPUT);
}
/**
 * Talk to the other Arduino
 */
void sendSMSAlert() {

  digitalWrite(TRIGGER, HIGH);
}

