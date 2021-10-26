#include <SoftwareSerial.h>
#define rxPin 2 // TX and RX pins for the software serial used to relay messages
#define txPin 3
#define vibOutPin 5

int power;
int sensitivity = 255;
boolean VibrationIsOn = false;
unsigned long prevTime = 0;        // will store last time it was updated
int delayON;
int delayOFF;
int vib_cycle; // used as a variable to keep track of the vibration pattern in while loops
int number_of_pulses; // defines the number of pulses for each vibration pattern
String incomingMessage = ""; // for incoming serial data

SoftwareSerial portOne(rxPin, txPin);
int baud = 9600;  // Choose Baud Rate

void setup() {
  Serial.begin(baud); // opens serial port, sets data rate to 9600 bps
  portOne.begin(baud); // opens software serial port for relay
  pinMode(vibOutPin, OUTPUT); // define a pin as output
}

void loop() {
  // reply only when you receive data:
  if (portOne.available()) {
    Serial.write(portOne.read());
  }
  if (Serial.available() > 0) {
    // read the incoming message:
    incomingMessage = Serial.readStringUntil('\n');

    //write to both Right and Left
    if (incomingMessage.charAt(0) == 'a') {
      portOne.println(incomingMessage);

      Serial.print("Both Arduinos are doing action: ");
      if (incomingMessage.charAt(1) == '0') {
        Serial.println("ALARM");
      } else if (incomingMessage.charAt(1) == '1') {
        Serial.println("Starting navigation");
      } else if (incomingMessage.charAt(1) == '2') {
        Serial.println("Wrong turn or direction");
      } else if (incomingMessage.charAt(1) == '3') {
        Serial.println("Location lost");
      } else if (incomingMessage.charAt(1) == '4') {
        Serial.println("Arriving at destination on the right");
      } else if (incomingMessage.charAt(1) == '5') {
        Serial.println("Arriving at destination on the left");
      } else {
        Serial.println("INVALID ACTION");
      }

      Stereo_processMessage(incomingMessage.charAt(1), sensitivity);
    }

    // write to left
    if (incomingMessage.charAt(0) == 'l') {
      portOne.println(incomingMessage);
      //Serial.println("Sent " + incomingMessage + " to LEFT Arduino");
    }

    //write to right
    if (incomingMessage.charAt(0) == 'r') {
      Serial.print("The RIGHT Arduino is doing action: ");
      // Compare the second character of the message received to do the corresponding action

      if (incomingMessage.charAt(1) == '1') {
        Serial.println("Turn Right, now");
      } else if (incomingMessage.charAt(1) == '2') {
        Serial.println("Turn Right, in advance");
      } else {
        Serial.println("INVALID ACTION");
      }

      processMessage(incomingMessage.charAt(1), sensitivity);


    }
    delay(10);
  }

}

void processMessage(char code, int sensitivity)
{
  vib_cycle = 1;

  if (code == '1') { // right turn , now
    number_of_pulses = 5;

    for (int i = 1; i <= 2 * number_of_pulses; i++) {
      if (i % 2 == 0) {
        analogWrite(vibOutPin, sensitivity);
        delay(400);
        analogWrite(vibOutPin, 0);
        delay(120);
      }
      else {
        analogWrite(vibOutPin, sensitivity);
        delay(100);
        analogWrite(vibOutPin, 0);
        delay(120);
      }
    }
  }

  else if (code == '2') { // right turn in advance
    number_of_pulses = 4;

    power = 0.85 * sensitivity;
    for (int i = 1; i <= number_of_pulses; i++) {
      analogWrite(vibOutPin, power);
      delay(100);
      analogWrite(vibOutPin, 0);
      delay(100);
      if (i == 2) delay(100);
    }
  }

}


void Stereo_processMessage(char code, int sensitivity) // function called for stereo haptic patterns, ie where both bracelets vibrate simultenously
{
  vib_cycle = 1;

  if (code == '0') { // Alarm / signal to get off the bus/metro
    number_of_pulses = 15;
    power = 1.0 * sensitivity;

    for (int i = 1; i <= number_of_pulses; i++) {
      analogWrite(vibOutPin, power);
      delay(300);
      analogWrite(vibOutPin, 0);
      delay(100);
    }
  }

  if (code == '1') { // start navigation
    power = 0.90 * sensitivity;
    analogWrite(vibOutPin, power);
    delay(1000);
    analogWrite(vibOutPin, 0);
  }

  else if (code == '2') { //wrong turn or direction
    number_of_pulses = 5;
    for (int i = 1; i <= 2 * number_of_pulses; i++) {
      if (i % 2 == 0) {
        analogWrite(vibOutPin, sensitivity);
        delay(400);
        analogWrite(vibOutPin, 0);
        delay(120);
      }
      else {
        analogWrite(vibOutPin, sensitivity);
        delay(100);
        analogWrite(vibOutPin, 0);
        delay(120);
      }
    }
  }

  else if (code == '3') { //location lost
    number_of_pulses = 8;
    power = 0.90 * sensitivity;

    for (int i = 1; i <= number_of_pulses; i++) {
      analogWrite(vibOutPin, power);
      delay(200);
      analogWrite(vibOutPin, 0);
      delay(400);
    }
  }

  else if (code == '4') { //arriving at desination located on the right
    number_of_pulses = 8;
    power = 1.0 * sensitivity;

    for (int i = 1; i <= number_of_pulses; i++) {
      analogWrite(vibOutPin, power);
      delay(150);
      analogWrite(vibOutPin, 0);
      delay(150);
      if (i % 2 == 0) delay(300);
    }
  }

  else if (code == '5') { //arriving at desination located on the left
    number_of_pulses = 3;
    power = 1.0 * sensitivity;
    delay(600);
    for (int i = 1; i <= number_of_pulses; i++) {
      analogWrite(vibOutPin, power);
      delay(150);
      analogWrite(vibOutPin, 0);
      delay(750);
    }
  }


}
