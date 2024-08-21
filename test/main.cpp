#include <Arduino.h>
#include <DHT.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Wire.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET 4

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire, OLED_RESET);

const int ledPin = PC13;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  for(int i=1;i<=5;++i){
    // digitalWrite(ledPin, LOW);
    digitalWrite(ledPin, HIGH);
    delay(1000*i);
    Serial.println("Done!");
  }
  return;
}