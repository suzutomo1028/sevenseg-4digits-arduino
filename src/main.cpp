#include <Arduino.h>

                    // A, B, C, D, E, F, G, DT
const int segPins[] = {3, 4, 5, 6, 7, 8, 9, 10};

const bool number[10][7] = {
//  A, B, C, D, E, F, G
  { 1, 1, 1, 1, 1, 1, 0 },  //  0
  { 0, 1, 1, 0, 0, 0, 0 },  //  1
  { 1, 1, 0, 1, 1, 0, 1 },  //  2
  { 1, 1, 1, 1, 0, 0, 1 },  //  3
  { 0, 1, 1, 0, 0, 1, 1 },  //  4
  { 1, 0, 1, 1, 0, 1, 1 },  //  5
  { 1, 0, 1, 1, 1, 1, 1 },  //  6
  { 1, 1, 1, 0, 0, 0, 0 },  //  7
  { 1, 1, 1, 1, 1, 1, 1 },  //  8
  { 1, 1, 1, 1, 0, 1, 1 }   //  9
};

                    // D1, D2, D3, D4
const int digPins[] = {A4, A3, A2, A0};

const int swPin = 2;

int count = 0;

void increase()
{
  int sw = digitalRead(swPin);

  if (sw == LOW) {
    count++;
    count %= 10000;
  }
}

void dispNumber(int n)
{
  for (int i = 0; i <= 6; i++) {
    digitalWrite(segPins[i], !number[n][i]);
  }
}

void pickDigit(int d)
{
  switch (d) {
    case 1:
      digitalWrite(digPins[0], HIGH);
      digitalWrite(digPins[1], LOW);
      digitalWrite(digPins[2], LOW);
      digitalWrite(digPins[3], LOW);
      break;

    case 2:
      digitalWrite(digPins[0], LOW);
      digitalWrite(digPins[1], HIGH);
      digitalWrite(digPins[2], LOW);
      digitalWrite(digPins[3], LOW);
      break;

    case 3:
      digitalWrite(digPins[0], LOW);
      digitalWrite(digPins[1], LOW);
      digitalWrite(digPins[2], HIGH);
      digitalWrite(digPins[3], LOW);
      break;

    case 4:
      digitalWrite(digPins[0], LOW);
      digitalWrite(digPins[1], LOW);
      digitalWrite(digPins[2], LOW);
      digitalWrite(digPins[3], HIGH);
      break;

    default:
      break;
  }
}

void setup()
{
  for (int i = 0; i <= 7; i++) {
    pinMode(segPins[i], OUTPUT);
    digitalWrite(segPins[i], HIGH); // 消灯
  }
  
  for (int d = 0; d <= 3; d++) {
    pinMode(digPins[d], OUTPUT);
    digitalWrite(digPins[d], LOW);  // 消灯
  }

  pinMode(swPin, INPUT_PULLUP);
  attachInterrupt(swPin, increase, FALLING);
}

void loop()
{
  pickDigit(1);
  dispNumber(count / 1000);
  delay(5);

  pickDigit(2);
  dispNumber((count % 1000) / 100);
  delay(5);

  pickDigit(3);
  dispNumber((count % 100) / 10);
  delay(5);

  pickDigit(4);
  dispNumber(count % 10);
  delay(5);
}
