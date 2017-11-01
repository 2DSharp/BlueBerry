unsigned char buff[4];

void getPassword() {

  int j = 0;

  Serial1.println("Enter the PIN: ");

  for (;;) {
    while (Serial1.available() > 0) {
      buff[j] = Serial1.read();
      j++;
    }

    if (j >= 4) {

      break;
    }
  }
}

void showPassword() {
  unsigned char value;
  
  for (int address = 0; address < 4; address++) {
    value = EEPROM.read(address);

    Serial1.println(value);
  }
}

void setPassword() {

  Serial1.println("New PIN set: ");
  for(int i=0; i<4; i++) {  
    
    EEPROM.update(i, buff[i]-'0');
    Serial1.print(buff[i]-'0');
  }
}

bool checkPassword() {

  unsigned char value;
  
  for (int address = 0; address < 4; address++) {
    value = EEPROM.read(address);

    if (buff[address]-'0' != value) {

      return false;
    }
  }

  return true;
}

