// connect motor controller pins to Arduino digital pins
// motor one
int enA = 6;
int in1 = 50;
int in2 = 51;
// motor two
int enB = 7;
int in3 = 52;
int in4 = 53;
void setup()
{
  // set all the motor control pins to outputs
//  pinMode(enA, OUTPUT);
  //pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
}
void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  
  Serial.println("turn on motor A");
  digitalWrite(13, HIGH);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  digitalWrite(13, LOW);
  
   //set speed to 200 out of possible range 0~255
  analogWrite(enA, 500);

  //delay(1000);
  Serial.println("turn on motor B");

  
  digitalWrite(13, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  digitalWrite(13, LOW);
  analogWrite(enB, 500);
  
  delay(2000);
  
  Serial.println("now turn off motors");
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(10000);
}
void demoTwo()
{
  // this function will run the motors across the range of possible speeds
  // note that maximum speed is determined by the motor itself and the operating voltage
  // the PWM values sent by analogWrite() are fractions of the maximum speed possible 
  // by your hardware
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  // accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++)
  {
      analogWrite(enB, i);
    analogWrite(enA, i);
    //analogWrite(enB, i);
    delay(20);
  } 
  // decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i)
  {
    analogWrite(enB, i);
    analogWrite(enA, i);
  
    delay(20);
  } 
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
}
void loop()
{
  demoOne();
/*  delay(2000);
  Serial.println("Redoing. Waaaait! ");
  demoTwo();
  delay(1000);
*/
}
