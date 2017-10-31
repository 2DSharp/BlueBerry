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
#include <Wire.h>

#define GSM_TRIGGER 6
#define NOTIFIER 7
//#define VIGILANCE 8
//#define WALK 9
#define RESET 10
char modeEnabled;
int alertStatus = 0;
int counter = 0;
char input;
const char ALERT_RECEIVED = 's';
const char ABORT_ALERT = 'a';
char messageStatus = '0';

char number[15] = "7005308234";
char message[200] =  "There seems to be some disturbance in your house, maybe you should check it out.";

void setup() {

  /**
   * GSM_TRIGGER comes out of the main Arduino Mega board
   * The input determines if an SMS is necessary
   */
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveMessageRequest); // register event
  Wire.onRequest(sendAlertStatus); // register event

  Serial.begin(9600);
  initGSMModule();
}

bool sendAlert(char number[15], char message[200] ) {

  Serial.println("Received alert request");

  while (!sendSMSAlert(number, message) && !fakePhoneCall(number)) {
  /**
   * Maybe notify the main board about the success?
   *  
   * delay(2000);
   * digitalWrite(NOTIFIER, HIGH);
   */
   messageStatus = '0';
  }

  messageStatus = ALERT_RECEIVED;
  delay(1000);

  return true;
}

void sendAlertStatus() {
  
  Wire.write(messageStatus);
}

void receiveMessageRequest(int howMany) {

  char request = Wire.read();    // receive byte as an integer

  if (request == 'm' && alertStatus != 1) {
    /**
     * To avoid sending continual messages
     * Repeat this every 5 times
     */
    alertStatus = sendAlert(number, message);
   }
}

void loop() {
  /**
   * Set the phone number to send the sms to and a not-so panicking message.
   */
  /** 
   * Cancel the alarm?
   */
  if (receivePhoneCallFromSpecificNumber(number)) {

    messageStatus = ABORT_ALERT;
    alertStatus = 0;
    //return;
  }
}
