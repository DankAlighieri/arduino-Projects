const int ledPin = 10;
const int ldrPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int valorLdr = analogRead(ldrPin);

  //int valorMapeado = (valorLdr/1023.0) * 255;
  
  int valorMapeado = map(valorLdr, 0, 1023, 0, 255);

  Serial.println(valorMapeado);

  analogWrite(ledPin, valorMapeado);

  delay(100);
}