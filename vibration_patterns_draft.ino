#define vibOutPin 3

int power;
int counter = 0;
int sensitivity = 255;
int start = 1;


void setup() {
  // put your setup code here, to run once:
  pinMode(vibOutPin, OUTPUT); // define a pin as output
  Serial.begin(9600);
}

void loop() {

  if (start == 1) {
    for (int k = 1; k <= 3; k++) {
      processMessage(k, sensitivity);
      delay(1000);
    }
    start = 0;
  }



}


void processMessage(int code, int sensitivity)
{
  if (code == 1) { // right/left turn

    for (int i = 1; i <= 10; i++) {
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

  else if (code == 2) { // right left turn in advance
    power = 0.85 * sensitivity;
    for (int i = 1; i <= 4; i++) {
      analogWrite(vibOutPin, power);
      delay(100);
      analogWrite(vibOutPin, 0);
      delay(100);
      if (i == 2) delay(100);
    }
  }

  else if (code == 3) { // start navigation
    power = 0.90 * sensitivity;
    analogWrite(vibOutPin, power);
    delay(1000);
    analogWrite(vibOutPin, 0);
  }

}
