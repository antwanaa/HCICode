String incomingMessage = ""; // for incoming serial data
int baud = 9600;

void setup() {
  Serial.begin(baud); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // reply only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingMessage = Serial.readStringUntil('\n');
    if(incomingMessage.charAt(0) == 'l'){
      Serial.print("The LEFT Arduino is doing action: ");
      
      if(incomingMessage.charAt(1) == '1'){
        Serial.println("1");
      }else if(incomingMessage.charAt(1) == '2'){
        Serial.println("2");
      }else if(incomingMessage.charAt(1) == '3'){
        Serial.println("3");
      }else{
        Serial.println("INVALID ACTION");
      }

    }
    delay(10);
  }

}