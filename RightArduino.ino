#include <SoftwareSerial.h>
#define rxPin 2 // TX and RX pins for the software serial used to relay messages
#define txPin 3
String incomingMessage = ""; // for incoming serial data
SoftwareSerial portOne(rxPin, txPin);
int baud = 9600;  // Choose Baud Rate

void setup() {
  Serial.begin(baud); // opens serial port, sets data rate to 9600 bps
  portOne.begin(baud); // opens software serial port for relay
}

void loop() {
  // reply only when you receive data:
  if (portOne.available()){
    Serial.write(portOne.read());
  }
  if (Serial.available() > 0) {
    // read the incoming message:
    incomingMessage = Serial.readStringUntil('\n');
    if (incomingMessage.charAt(0) == 'l'){
      portOne.println(incomingMessage);
      Serial.println("Sent " + incomingMessage + " to LEFT Arduino");
    }
    if(incomingMessage.charAt(0) == 'r'){
      Serial.print("The RIGHT Arduino is doing action: ");
      
      // Compare the second character of the message received to do the corresponding action
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