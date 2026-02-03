const int firstBtnPin = 2; 
const int redLedPin = 12; 
const int greenLedPin = 11; 
const int blueLedPin = 13; 

volatile int ledState = 0;

volatile byte redState = LOW;
volatile byte greenState = LOW;
volatile byte blueState = LOW;

void buttonInterrupt() {
  Serial.print("Led State: ");
  Serial.println(ledState);

  switch(ledState) {
    case 0:

      redState = HIGH;
      greenState = HIGH;
      blueState = HIGH;
      
      digitalWrite(redLedPin, redState);
      digitalWrite(greenLedPin, greenState);
      digitalWrite(blueLedPin, blueState);

      ledState = 1;
      break;
    case 1:
      
      redState = HIGH;
      greenState = HIGH;
      blueState = LOW;

      digitalWrite(redLedPin, redState);
      digitalWrite(greenLedPin, greenState);
      digitalWrite(blueLedPin, blueState);
      
      ledState = 2;
      break;
    case 2:
      redState = LOW;
      greenState = HIGH;
      blueState = HIGH;

      digitalWrite(redLedPin, redState);
      digitalWrite(greenLedPin, greenState);
      digitalWrite(blueLedPin, blueState);

      ledState = 3;
      break;
    default:
      redState = HIGH;
      greenState = LOW;
      blueState = HIGH;

      digitalWrite(redLedPin, redState);
      digitalWrite(greenLedPin, greenState);
      digitalWrite(blueLedPin, blueState);

      ledState = 0;
      break;
  }
}

void setup() {
  Serial.begin(9600);
  // Buttons
  pinMode(firstBtnPin, INPUT_PULLUP);

  // LEDs
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(blueLedPin, LOW);  

  // Configurando rotina de interrupcao
  attachInterrupt(digitalPinToInterrupt(firstBtnPin), buttonInterrupt, FALLING);
}

void loop() {
  while(Serial.available() == 0) {}
  String opString = Serial.readString();
  opString.trim();


  if(opString == "blue"){
    blueState = !blueState;
    digitalWrite(blueLedPin, blueState);
  }  else if (opString == "red"){
    redState = !redState;
    digitalWrite(redLedPin, redState);
  } else if (opString == "green") {
    greenState = !greenState;
    digitalWrite(greenLedPin, greenState);
  }
}
