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

void setup() {

  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, LOW);
  /**
   * GSM_TRIGGER comes out of the main Arduino Mega board
   * The input determines if an SMS is necessary
   */
  pinMode(GSM_TRIGGER, INPUT);
  pinMode(NOTIFIER, OUTPUT);
  
  digitalWrite(13, LOW);
  digitalWrite(NOTIFIER, LOW);
  
  Serial.begin(9600);
 // initGSMModule();

  Wire.begin();
  
  Serial.println("Project BlueBerry\n- A dog is a man's best friend");
  Serial.println("Bark, Bark - Waking up...");  
  
  Serial.println("Enter the number of the mode you'd like to make it work in: ");
  Serial.println("1. Vigilance mode\n2. Walk mode \n3. RC Car mode");
  for(;;) {
    
    input = Serial.read();
    if (input == '1' || input == '2' || input == '3') {

      break;
    }
  }
  delay(1000);
  
  Wire.beginTransmission(8); // transmit to device #8

  switch (input) {
    
    case '1':
      Serial.println("Vigilance mode:\n Activates all of its senses to detect if something's wrong when you are not around.");
      Wire.write('v');
      break;

    case '2':
      Serial.println("Walking mode:\n\n Take your dog for a walk!");
      Wire.write('w');
      break; 

     case '3':
      Serial.println("RC Mode: run your dog like a car!");
      Wire.write('b');
      break;
  }

  Wire.endTransmission();
  Wire.requestFrom(8, 100);
  
  for (;;) {

    if (Wire.available()) {
        modeEnabled = Wire.read(); // receive a byte as character
        break;
    }
  }

  switch (modeEnabled) {

    case 'v': 
      Serial.println("Vigilance mode activated");
      break;
    case 'w':
      Serial.println("Walking mode activated");
      break;
    case 'b':
      Serial.println("RC locomotive mode activated");
      break;
  }
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
}

void loop() {
  digitalWrite(NOTIFIER, LOW);
  digitalWrite(RESET, LOW);  
  input = Serial.read();

  
  if (input == 'r') {

    Wire.beginTransmission(8);
    Wire.write('r');
    Wire.endTransmission();
    digitalWrite(RESET, HIGH);
    
    setup();
    return;
  }

  else if (modeEnabled == 'b') { 

    Serial.print("bluetooth");
    if (Serial.available()) {

    input = Serial.read();

    if (input == 'r') {
      setup();
      return;
    }
    Wire.beginTransmission(8);

    Wire.write(input);
    Wire.endTransmission();
    }
    return;
  }
  digitalWrite(NOTIFIER, LOW);

  /**
   * Set the phone number to send the sms to and a not-so panicking message.
   */
  char number[15] = "7005308234";
  char message[200] =  "There seems to be some disturbance in your house, maybe you should check it out.";
  /**
   * Cancel the alarm?
   */
  if (receivePhoneCallFromSpecificNumber(number)) {
    
    digitalWrite(NOTIFIER, LOW);
    //
    alertStatus = 0;
    //return;
  }
  if (alertStatus == 1) {
    digitalWrite(NOTIFIER, HIGH);
  }
  /**
   * The master control wants to alert the user
   */
  if (digitalRead(GSM_TRIGGER) == HIGH && alertStatus != 1) {
    /**
     * To avoid sending continual messages
     * Repeat this every 5 times
     */
    Serial.println("Received alert request");
    digitalWrite(13, HIGH);
 
    if (sendSMSAlert(number, message) && fakePhoneCall(number)) {
      /**
       * Maybe notify the main board about the success?
       */
      
      delay(2000);
      digitalWrite(NOTIFIER, HIGH);
      alertStatus = 1;
    } else {
      /**
       * The alert failed, try again
       */
      Serial.println("Alert failed, trying again");
      digitalWrite(NOTIFIER, LOW);
      loop();
    }
    delay(1000);
  }
}
