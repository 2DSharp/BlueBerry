

void setup() {
  Serial.begin (9600);
  initUltrasonic();

}

void loop() {

  looper();
  delay(500);
}
