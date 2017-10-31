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
/**
#define GSM_TRIGGER 6
#define NOTIFIER 7
//#define VIGILANCE 8
//#define WALK 9
#define RESET 10
*/
int alertStatus = 0;

const char ALERT_RECEIVED = 's';
const char ABORT_ALERT = 'a';
char messageStatus = '0';

char number[15] = "7005308234";
char message[200] =  "There seems to be some disturbance in your house, maybe you should check it out.";

void setup() {
  /**
   * Begin the wired connection from the master to the slave
   * Address 8 is what the both communicate with
   */
  Wire.begin(8);
  /**
   * Execute the request to send alert message
   */
  Wire.onReceive(receiveMessageRequest);
  /**
   * The status of the alert, to control the alarm and alert frequency
   */
  Wire.onRequest(sendAlertStatus); // register event
  
  Serial.begin(9600);
}
/**
 * Sends an SMS and calls the user alerting them of any anomaly in their house
 */
bool sendAlert(char number[15], char message[200] ) {

  Serial.println("Received alert request");

  while (!sendSMSAlert(number, message) && !fakePhoneCall(number)) {
    /**
     * Keep trying
     */
    messageStatus = '0';
  }
  /**
   * Sets the message status to ALERT_RECEIVED for the alarm to go off
   * alertStatus = 1 makes sure no subsequent alerts are sent before the previous alarm
   * is responed to.
   */
  alertStatus = 1;
  messageStatus = ALERT_RECEIVED;
  delay(1000);

  return true;
}
/**
 * Wire connection to  write to the mega board
 */
void sendAlertStatus() {
  
  Wire.write(messageStatus);
}
/**
 * Wire connection for reading the request from the mega board
 * Sends alerts accordingly
 */
void receiveMessageRequest(int howMany) {
  
  char request = Wire.read();

  if (request == 'g') {

    initGSMModule();
  }
  /**
   * To avoid sending continual messages
   */
  if (request == 'm' && alertStatus != 1) {
    
    alertStatus = sendAlert(number, message);
   }
}

void loop() {
  /** 
   * Cancel the alarm?
   */
  if (messageStatus == ABORT_ALERT) {

    messageStatus = '1';
  }
  if (receivePhoneCallFromSpecificNumber(number)) {

    messageStatus = ABORT_ALERT;
    alertStatus = 0;
    delay(1000);
  }
}
