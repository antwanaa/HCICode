//#include <HardwareBLESerial.h>
#include <ArduinoBLE.h>

#define rxPin 2 // TX and RX pins for the software serial used to relay messages
#define txPin 3
#define vibOutPin 21u //21u pin A7

#define blueLedPin 24u
#define redLedPin 22u

int power;
int sensitivity = 255;
boolean VibrationIsOn = false;
unsigned long prevTime = 0;        // will store last time it was updated
int delayON;
int delayOFF;
int vib_cycle; // used as a variable to keep track of the vibration pattern in while loops
int number_of_pulses; // defines the number of pulses for each vibration pattern
String incomingMessage = ""; // for incoming serial data
byte message;


BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin = LED_BUILTIN; // pin to use for the LED

//SoftwareSerial portOne(rxPin, txPin);
int baud = 9600;  // Choose Baud Rate

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  //  portOne.begin(baud); // opens software serial port for relay
  pinMode(vibOutPin, OUTPUT); // define a pin as output

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  digitalWrite(blueLedPin, HIGH);
  digitalWrite(redLedPin, LOW);

  

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("LED");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characeristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

  Serial.println("BLE LED Peripheral");
  digitalWrite(redLedPin, HIGH);
}

void loop() {
  // listen for BLE peripherals to connect:


  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");

    // print the central's MAC address:
    Serial.println(central.address());

    digitalWrite(blueLedPin, LOW);
    delay(100);
    digitalWrite(blueLedPin, HIGH);
    delay(100);
    digitalWrite(blueLedPin, LOW);
    delay(100);
    digitalWrite(blueLedPin, HIGH);   
    delay(100);
    digitalWrite(blueLedPin, LOW);

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:


      if (switchCharacteristic.written()) {
        Serial.println("Something happened");


        if (switchCharacteristic.value()) {   // any value other than 0
          switchCharacteristic.readValue(message);
          digitalWrite(blueLedPin, LOW);


          if (message == 0xA0) {
            incomingMessage = "a0";
          } else if (message == 0xA1) {
            incomingMessage = "a1";
          } else if (message == 0xA2) {
            incomingMessage = "a2";
          } else if (message == 0xA3) {
            incomingMessage = "a3";
          } else if (message == 0xA4) {
            incomingMessage = "a4";
          } else if (message == 0xA5) {
            incomingMessage = "a5";
          } else if (message == 0xB1) {
            incomingMessage = "r1";
          } else if (message == 0xB2) {
            incomingMessage = "r2";
          } else if (message == 0xC1) {
            incomingMessage = "l1";
          } else if (message == 0xC2) {
            incomingMessage = "l2";
          } else {
            Serial.print("ELSE was done, message was not as intended: ");
            Serial.println(message);
          }

          Serial.println("Message received: " + String(message));
          Serial.println("translated message: " + incomingMessage);

          if (incomingMessage.charAt(0) == 'a') {
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
            Serial.print("The LEFT Arduino is doing action: ");
            // Compare the second character of the message received to do the corresponding action
            if (incomingMessage.charAt(1) == '1') {
              Serial.println("Turn Left, now");
            } else if (incomingMessage.charAt(1) == '2') {
              Serial.println("Turn Left, in advance");
            } else {
              Serial.println("INVALID ACTION");
            }
            processMessage(incomingMessage.charAt(1), sensitivity);
          }

          // write to right
          if (incomingMessage.charAt(0) == 'r') {
//            Serial1.println(incomingMessage);
            //Serial.println("Sent " + incomingMessage + " to LEFT Arduino");
          }
          Serial.println("----------------------------------");
        }
        delay(10);
      }
    }
    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    digitalWrite(blueLedPin, HIGH);
    Serial.println(central.address());
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