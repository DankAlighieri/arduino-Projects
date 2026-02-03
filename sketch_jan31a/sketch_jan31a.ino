const int ledPin = 13;
const int btnPin = 12;

byte ledState = 0;
byte lastBtnState;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  Serial.println("Iniciando botao com debounce");
  digitalWrite(ledPin, LOW);
}

void loop() {
  if ((millis() - lastDebounceTime) >= debounceDelay) {
    byte btnState = digitalRead(btnPin);
    if (btnState != lastBtnState) {
      lastDebounceTime = millis();
      lastBtnState = btnState;
      if (!btnState) {
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
      }
    }
  }
}