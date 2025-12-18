#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int gasPin = A1;
const int ledRedPin = 2;
const int ledGreenPin = 3;
const int buzzerPin = 6;

const int threshold = 300;
const int freqMin = 3450;
const int freqMax = 3850;

uint16_t gasValue;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(ledGreenPin, HIGH);

  lcd.init();
  lcd.backlight();
}

void loop() {
  gasValue = analogRead(gasPin);

  lcd.setCursor(0, 0);
  lcd.print("Gas: ");
  lcd.print(gasValue);
  lcd.print("    ");

  if (gasValue > threshold) {
    lcd.setCursor(0, 1);
    lcd.print("Status: ALERT ");

    for (int f = freqMin; f <= freqMax; f += 3) {
        tone(buzzerPin, f);
        digitalWrite(ledRedPin, f > (freqMax + freqMin) / 2);
        delay(1);
    }

    for (int f = freqMax; f >= freqMin; f -= 3) {
        tone(buzzerPin, f);
        digitalWrite(ledRedPin, f > (freqMax + freqMin) / 2);
        delay(1);
    }
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Status: OK    ");
    noTone(buzzerPin);
    digitalWrite(ledRedPin, LOW);
}