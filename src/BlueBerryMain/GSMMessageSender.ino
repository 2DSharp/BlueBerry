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

void initGSMMessageSender() {

  Serial.println("Starting GSM interface");
  Wire.beginTransmission(8);
  Wire.write('g');
  Wire.endTransmission();    
  
  Wire.requestFrom(8, 6);    
  /**
   * Check if the GSM module was initialized
   */
  if (Wire.available()) {

    char messageStatus = Wire.read();

    while (messageStatus != '1') {
      messageStatus = Wire.read();
    }
  
  }
  Serial.println("Initialized GSM interface");
}
/**
 * Talk to the other Arduino
 */
void sendAlert() {
  
  Serial1.println("Sending alert");
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write('m');              // sends one byte
  Wire.endTransmission();    // stop transmitting
  
}



