void showDefaultSelectionUI() {

  Serial1.println("Project BlueBerry\n- A dog is a man's best friend");
  Serial1.println("Bark, Bark - Waking up...");  
  
  Serial1.println("Enter the number of the mode you'd like to make it work in: ");
  Serial1.println("1. Vigilance mode\n2. Walk mode \n3. RC Car mode");

}

char getModePreference() {
  
  for(;;) {

    if (Serial1.available()) {
      input = Serial1.read();
      
      if (input == '1' || input == '2' || input == '3' || input == 'r') {
  
        break;
        return input;
      }
    }
  }
}

void showSelectedModeDescription(char input) {
  
  switch (input) {
    
    case VIGILANCE_MODE:
      Serial1.println("Vigilance mode:\n Activates all of its senses to detect if something's wrong when you are not around.");
      break;

    case WALK_MODE:
      Serial1.println("Walking mode:\n\n Take your dog for a walk!");
      break; 

     case RC_MODE:
      Serial1.println("RC Mode: run your dog like a car!");
      break;

     case RESET_MODE:
      setup();
      break;
  }
}

void blinkLED(int pin, int blinkSpeed, int times) {

  digitalWrite(pin, LOW);
  for (int i = 1; i <= times; i++) {
    digitalWrite(pin, HIGH);
    delay(blinkSpeed);
    digitalWrite(pin, LOW);
    delay(blinkSpeed);
  }
}


