/**
 * SMS Sending using GSM module
 * @author Dedipyaman Das
 * github.com/2DSharp/BlueBerry
 * @version 1.0/17 
 */
/**
 * This program is responsible for sending SMS alerts to a number
 *
 * Circuit:
 * GSM shield
 * SIM card that can send SMS
 */
#include <GSM.h>
/**
 * Set this PIN number if set in the SIM
 */
#define SIM_PIN_NUMBER ""
/**
 * Initializing the library instance
 */
GSM gsmAccess;
GSM_SMS sms;

void initGSMModule() {
  
  Serial.println("Initializing GSM Module...");
  /**
   * Set connection state to not connected first
   */
  boolean notConnected = true;
  /**
   * Start GSM shield
   * Pass the PIN it as a parameter of begin() in quotes
   */
  while (notConnected) {
    /**
     * Check if connected
     */
    if (gsmAccess.begin(SIM_PIN_NUMBER) == GSM_READY) {
      
      notConnected = false;
    }
    else {
      
      Serial.println("Not connected");
    }
  }
  /**
   * Done
   */
  Serial.println("GSM initialized");
}

/**
 * Sending SMS
 * @param char[15]
 * @param message[200]
 */
bool sendSMSAlert(char number[15], char message[200]) {
  /**
   * Get the phone number and message as dependencies
   */
  Serial.println(number);
  /**
   * Get the message as depenency
   */
  Serial.println("SENDING");
  Serial.println();
  Serial.println("Message:");
  Serial.println(message);
  /**
   * Prepare the message
   */
  sms.beginSMS(number);
  sms.print(message);
  /** 
   * Send
   */
  sms.endSMS();
  Serial.println("\nCOMPLETE!\n");
  delay(1000);
  return true;
}
