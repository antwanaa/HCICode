int incomingByte = 0; // for incoming serial data

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // reply only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    delay(50);
    // say what you got:
    Serial.print("Antoine Arduino received: ");
    Serial.println(char(incomingByte));
  }

}