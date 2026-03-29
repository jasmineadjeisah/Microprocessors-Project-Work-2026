#include <LiquidCrystal.h>

// INPUT
int potPin = A0;

// OUTPUTS
int ledCry = 10;      // LED1
int ledNoise = 9;     // LED2
int ledSilent = 8;    // LED3
int buzzer = 11;

// BUTTON
int buttonPin = 2;    // Mute button
bool mute = false;

// LCD (16x2)
LiquidCrystal lcd(13, 12, 7, 6, 5, 4);

// THRESHOLDS
int noiseLevel = 200;
int cryLevel = 500;

void setup() {
  // LEDs
  pinMode(ledCry, OUTPUT);
  pinMode(ledNoise, OUTPUT);
  pinMode(ledSilent, OUTPUT);
  
  // Buzzer
  pinMode(buzzer, OUTPUT);
  
  // Button 
  pinMode(3, INPUT);

  // Serial monitor
  Serial.begin(9600);

  // LCD setup
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("SYSYTEM BEGIN");
  delay(1500);
  lcd.clear();
}

void loop() {
  int value = analogRead(potPin);
  int buttonState = digitalRead(buttonPin);

  // PUSHBUTTON
  if (buttonState == LOW) {
    mute = !mute;
    delay(300); // delay
  }

  // Display potentiometer value
  lcd.setCursor(0, 1);
  lcd.print("Value:");
  lcd.print(value);
  lcd.print("   "); // clear digits

  Serial.println(value);

  // LOGIC STATE
  if (value >= cryLevel) {
    // CRY DETECTED
    digitalWrite(ledCry, HIGH);
    digitalWrite(ledNoise, LOW);
    digitalWrite(ledSilent, LOW);

    lcd.setCursor(0, 0);
    lcd.print("INFANT CRY! ");

    if (!mute) {
      tone(buzzer, 700);
    } else {
      noTone(buzzer);
    }

  } else if (value >= noiseLevel) {
    // NORMAL NOISE
    digitalWrite(ledCry, LOW);
    digitalWrite(ledNoise, HIGH);
    digitalWrite(ledSilent, LOW);

    lcd.setCursor(0, 0);
    lcd.print("NOISE ");

    if (!mute) {
      tone(buzzer, 400);
    } else {
      noTone(buzzer);
    }

  } else {
    // SILENT
    digitalWrite(ledCry, LOW);
    digitalWrite(ledNoise, LOW);
    digitalWrite(ledSilent, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("QUIET  ");

    noTone(buzzer);
  }

  delay(200);
}