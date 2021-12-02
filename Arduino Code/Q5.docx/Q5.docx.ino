#include <LiquidCrystal.h>
  const int RS = 13, E = 12, D4 = 8, D5 = 9, D6 = 10, D7 = 11;
  LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
  int enablePin = 5;
  int in1Pin = 6;
  int in2Pin = 7;
  int adcPin = A0;
  int T,sp;
  float c = 0,a = 0,b = 0;
    // External Interrupt
  void ISRHandler() {
    a = millis();
    c = a - b;
    b = a;
    }
void setup() {
  // put your setup code here, to run once:
  attachInterrupt(0, ISRHandler, RISING);
  pinMode(enablePin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(adcPin, INPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("MohammadBarabadi");
  lcd.setCursor(0, 1);
  lcd.print("9723015");
  delay(2000);
  lcd.clear();
}
void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(10, 0);
  lcd.print(c);
  T = analogRead(adcPin);
  lcd.setCursor(0, 0);
  lcd.print("TMP=");
  lcd.print(T * 0.488);
  if (T * 0.488 < 60)
  {
    sp = 0;
    lcd.setCursor(8, 1);
    lcd.print("         ");
  }
  else if (T * 0.488 > 60 & T * 0.488 < 90)
  {
    sp = map(T * 0.488, 60, 90, 0, 255);
    lcd.setCursor(8, 1);
    lcd.print("         ");
  }
  else if(T * 0.488 > 90)
  {
    sp = 255;
    if(T * 0.488 > 125)
    {
      lcd.setCursor(8, 1);
      lcd.print("Danger!!!");
    }
    else
    {
    lcd.setCursor(8, 1);
      lcd.print("         ");
    }
  }
  lcd.setCursor(0, 1);
  lcd.print("PWM=");
  lcd.print(sp);
  analogWrite(enablePin, sp);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in1Pin, HIGH);
}
