unsigned char buff[4];

void getPassword() {

  int j = 0;

  Serial1.println("Enter the PIN: ");

  for (;;) {
    while (Serial1.available() > 0) {
      buff[j] = Serial1.read();
      j++;
    }

    if (j >= 3) {

      break;
    }
  }
}

void setPassword() {
  
  for(int i=0; i<4; i++) {  
    EEPROM.update(i, buff[i]);
  }
}

bool checkPassword() {

  unsigned char value;
  
  for (int address = 0; address < 4; address++) {
    value = EEPROM.read(address);

    if (buff[address] != value) {

      return false;
    }
  }

  return true;
}

