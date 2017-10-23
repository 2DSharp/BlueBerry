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
#define GSM_TRIGGER 6
#define NOTIFIER 7

void setup() {
  
  Serial.begin(9600);
  /**
   * GSM_TRIGGER comes out of the main Arduino Mega board
   * The input determines if an SMS is necessary
   */
  pinMode(GSM_TRIGGER, INPUT);
  initGSMModule();
}

void loop() {
  /**
   * The master control wants to alert the user
   */
  if (digitalRead(GSM_TRIGGER) == HIGH) {
    /** Set the phone number to send the sms to and a not-so panicking attack.     **/
    char number[15] = "7005308234";
    char message[200] =  "There seems to be some disturbance in your house, maybe you should check it out.";

    if (sendSMSAlert(number, message)) {
      /**
       * Maybe notify the main board about the success?
       */
      digitalWrite(NOTIFIER, HIGH);

    } else {

      digitalWrite(NOTIFIER, HIGH);
    }
    
  delay(1000);
}
