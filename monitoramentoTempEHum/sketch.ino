#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

const int ledPin = 13;
const int dhtPin = 14;
const int dhtType = 22;
const int ptnPin = 4;

const int ssdSCSLPin = 22;
const int ssdSDAPin = 21;
const int displayWidth = 128;
const int displayHeight = 64;
const int displayAddr = 0x3C;
const int yOffset = 15;

const float maxTemp = 50.0;

const float maxRes = 65520.0; // 2^16 adc resolution bits

byte ledState = LOW;

DHT dht(dhtPin, dhtType);

Adafruit_SSD1306 display(displayWidth, displayHeight, &Wire, -1);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

  if(!display.begin(SSD1306_SWITCHCAPVCC, displayAddr)) {
    Serial.println("Failed to initialize display!");
    for(;;);
  }

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  analogReadResolution(16);

  dht.begin();
}

void writeToDisplay(float temp, float hum, float threshold ) {
  // Reset display
  display.clearDisplay();
  
  // Write temp
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(1,1);
  display.print(F("Temperature: "));
  display.print(temp);
  display.print(F(" C"));

  // Write humidity
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(1, yOffset);
  display.print(F("Humidty: "));
  display.print(hum);
  display.print(F(" g/Kg"));

  // Write threshold
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(1, yOffset * 2);
  display.print(F("Max temp.: "));
  display.print(threshold);
  display.print(F(" C"));

  // Sends buffer to display controller
  display.display();
}

float readPotentiometer() {
  int rawValue = analogRead(ptnPin);
  
  return rawValue * (maxTemp/maxRes);
}

void loop() {
  float threshold = readPotentiometer();
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (temp > threshold) {
    if(!ledState) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
  } else {
    if(ledState) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
  }

  Serial.print("Max Temp: ");
  Serial.println(threshold);
  Serial.print("Read temp: ");
  Serial.println(temp);
  Serial.print("Read hum: ");
  Serial.println(hum);
  
  writeToDisplay(temp, hum, threshold);
  
  delay(10);
}