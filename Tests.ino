
int ledPin = 9;    // LED connected to digital pin 9

void setup() {
  // nothing happens in setup
}

void loop() {
  // fade in from min to max in increments of 5 points:
  analogWrite(ledPin, 255);
  delay(500);
  analogWrite(ledPin, 0);
  delay(1500);
  analogWrite(ledPin, 255);
  delay(500);
  analogWrite(ledPin, 0);

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}