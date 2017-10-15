// Interval is how long we wait
// add const if this should never change
int interval=1000;
// Tracks the time since last event fired
unsigned long previousMillis=0;
 unsigned long avg;
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
   // Get snapshot of time
   unsigned long currentMillis = millis();
 
   // How much time has passed, accounting for rollover with subtraction!
   if ((unsigned long)(currentMillis - previousMillis) >= interval) {
      // It's time to do something!
      int a = 1;
      int b = 1;
      int c = 1;
      if ((b & c) | (a & (b ^ c))) {
        Serial.println(1);
      } 
      }
      Serial.print("\nTime: ");
      Serial.print(currentMillis-previousMillis);


      // Use the snapshot to set track time until next event
      previousMillis = currentMillis;
   }

