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
GSMVoiceCall vcs;
/**
 * The calling number to the GSM module
 */
char numtel[15];

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
/**
 * Calling the user, cut it once received
 */
 bool fakePhoneCall(char number[15]) {
 /**
   * Get the phone number as a dependency
   */
  Serial.print("Calling to : ");
  Serial.println(number);
  Serial.println();
  bool callSuccess = false;
    // Check if the receiving end has picked up the call
  if (vcs.voiceCall(number)) {
    Serial.println("Call Established. Cutting the line once someone receives it");
    delay(1000);
    /**
     * Hanging up the call once they pick up
     */
    if (vcs.getvoiceCallStatus() == TALKING);
    
    vcs.hangCall();
    Serial.println("Call completed");
    callSuccess = true;
  }
  delay(20000);
  return callSuccess;
 }
 
 bool receivePhoneCallFromSpecificNumber(char number[15]) {
  /**
   * Get the phone number as a dependency
   */
   switch (vcs.getvoiceCallStatus()) {
    case IDLE_CALL:
      /** 
       *  Nothing's going on
       */
       return false;
      break;

    case RECEIVINGCALL: 
      /**
       * Someone's calling
       */
      Serial.println("RECEIVING CALL");

      // Retrieve the calling number
      vcs.retrieveCallingNumber(numtel, 15);

      // Print the calling number
      Serial.print("Number:");
      Serial.println(numtel);
      Serial.println("Success");
      vcs.hangCall();
      return true;
      /**
       * The calling number is same as the expected number
       */
      if (strcmp(number,numtel) == 0) {

      }
      vcs.hangCall();
      break;

    case TALKING:  // In this case the call would be established

      vcs.hangCall();
      Serial.println("Hanging up and waiting for the next call.");
      break;
  }
  delay(1000);
  return false;
 }
