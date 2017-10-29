// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
char x;
char resu;
int res = 0;
int mode;
void setup() {
    Serial.begin(9600);           // start serial for output

  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  
  if (res == 0) {
    setup();
  }
  
  //Serial.println(x);
}

void loop() {
    Serial.println("huh?");
    Wire.begin(8);                // join i2c bus with address #8
    Wire.onReceive(receiveOtherEvent); // register event
    //Serial.write(resu);
    delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {

   x = Wire.read();
  res = 1;// receive byte as an integer
   mode = 2;
  Serial.println(x);         // print the integer

 if (x == 'a') {
  Serial.println("hello");
 }
}

char receiveOtherEvent(int howMany) {

  char resu = Wire.read();
  Serial.println(resu);
}

