const int ledPin = 10;

void setup() {

}

void loop() {
  for (int i = 0; i < 256; i++) {
    analogWrite(ledPin, i);
    delay(10);
  }
  for (int i = 255; i > -1; i--) {
    analogWrite(ledPin, i);
    delay(10);
  }
}