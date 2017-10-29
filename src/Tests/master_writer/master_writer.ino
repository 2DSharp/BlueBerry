// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
  Wire.beginTransmission(8); // transmit to device #8
  for (;;) {
    if (Serial.available()) {
      char c = Serial.read();
      Wire.write(c);
      break;
    }
  }
  Wire.endTransmission();    // stop transmitting
  Serial.println("Done");
//  x++;
  delay(500);
}

byte x = 0;

void loop() {

  Serial.println("HUH");
  if (Serial.available() ) {
    char input = Serial.read();
    Serial.println(input);
    Wire.beginTransmission(8);
    Wire.write(input);
    Wire.endTransmission();
    }
}
