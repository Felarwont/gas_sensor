const int gasPin = A1;
const int ledRedPin = 2;
const int ledGreenPin = 3;
const int buzzerPin = 6;

const int threshold = 300;
const int freqMin = 3450;
const int freqMax = 3850;

uint16_t gasValue;

void setup() {
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(ledGreenPin, HIGH);
}

void loop() {
  gasValue = analogRead(gasPin);

  if (gasValue > threshold) {
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
    noTone(buzzerPin);
    digitalWrite(ledRedPin, LOW);
}