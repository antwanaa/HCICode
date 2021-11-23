#include <ArduinoBLE.h>

#define rxPin 2 // TX and RX pins for the software serial used to relay messages
#define txPin 3
#define vibOutPin 5

#define extLedPin 2u

int power;
int sensitivity = 255;
boolean VibrationIsOn = false;
unsigned long prevTime = 0;        // will store last time it was updated
int delayON;
int delayOFF;
int vib_cycle; // used as a variable to keep track of the vibration pattern in while loops
int number_of_pulses; // defines the number of pulses for each vibration pattern
String incomingMessage = ""; // for incoming serial data
byte message[2];


BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin = LED_BUILTIN; // pin to use for the LED

int baud = 9600;  // Choose Baud Rate

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  while (!Serial);

  pinMode(vibOutPin, OUTPUT); // define a pin as output
  
  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);
  pinMode(extLedPin, OUTPUT);

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
}

void loop() {
  // listen for BLE peripherals to connect:
           

  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:

//      bleSerial.poll();
      if (switchCharacteristic.written()) {
          Serial.println("Something happened");

        if (switchCharacteristic.value()) {   // any value other than 0

          switchCharacteristic.readValue(message, 0x09);
          for(int i =0; i<=1; i++){
            Serial.print(message[i]);
            Serial.print(" ");
          }
          Serial.println();
          
          Serial.println("LED on");
          digitalWrite(extLedPin, HIGH);         // will turn the LED on
          Serial1.println("l1");

          delay(500);
        } else {                              // a 0 value
          Serial.println(F("LED off"));
          digitalWrite(extLedPin, LOW);          // will turn the LED off
        }
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
