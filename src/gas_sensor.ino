#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int gasPin = A1;
const int ledRedPin = 2;
const int ledGreenPin = 3;
const int buzzerPin = 6;

const int threshold = 330;
const int freqMin = 3450;
const int freqMax = 3850;

uint16_t gasValue;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcdInitializeAnimation();
}

void loop() {
  gasValue = analogRead(gasPin);
  updateLCD();

  if (gasValue > threshold) {
    alertMode();
  } else {
    normalMode();
  }
}

void lcdInitializeAnimation() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas Sensor");

  lcd.setCursor(0, 1);
  lcd.print("Initializing");

  for (int i = 0; i < 3; i++) {
    delay(800);
    lcd.print(".");
  }

  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("      Done!    ");

  delay(500);
  lcd.clear();
}

void updateLCD() {
  lcd.setCursor(0, 0);
  lcd.print("Gas: ");
  lcd.print(gasValue);
  lcd.print("    ");
}

void alertMode() {
  lcd.setCursor(0, 1);
  lcd.print("Status: ALERT ");

  digitalWrite(ledGreenPin, LOW);

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
}

void normalMode() {
  lcd.setCursor(0, 1);
  lcd.print("Status: OK    ");
  noTone(buzzerPin);
  digitalWrite(ledRedPin, LOW);
  digitalWrite(ledGreenPin, HIGH);
}