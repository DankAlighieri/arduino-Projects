const int btnPin = 2;
const int redPin = 13;
const int greenPin = 12;
const int bluePin = 11;
const int lonePin = 10;
int segment = 0;

unsigned long lastDebounceTime = 0;
unsigned long debounceTime = 50; // 50ms

byte redLedState = LOW;
byte greenLedState = LOW;
byte blueLedState = LOW;
byte loneLedState = LOW;

byte lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  //attachInterrupt(digitalPinToInterrupt(btnPin), interruptHandler, FALLING);

  pinMode(btnPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(lonePin, OUTPUT);

  digitalWrite(redPin, redLedState);
  digitalWrite(greenPin, greenLedState);
  digitalWrite(bluePin, blueLedState);
  digitalWrite(lonePin, loneLedState);
}

void loop() {
  redLedState = !redLedState;
  digitalWrite(redPin, redLedState);
  delay(50);
  greenLedState = !greenLedState;
  digitalWrite(greenPin, greenLedState);
  delay(50);
  blueLedState = !blueLedState;
  digitalWrite(bluePin, blueLedState);
  delay(50);

  if ((millis() - lastDebounceTime) >= debounceTime) {
    byte reading = digitalRead(btnPin);
    if (reading != lastButtonState) {
      lastDebounceTime = millis();
      lastButtonState = reading;
      if (!reading) {
        loneLedState = !loneLedState;
        digitalWrite(lonePin, loneLedState);
        DDR &= ~(1 << 13);
      }
    }
  }

}
