#include <Wire.h>

#define motorPin1A 3
#define motorPin1B 5
#define motorPin2A 6
#define motorPin2B 9
#define motorPin3A 10
#define motorPin3B 11


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motorPin1A, OUTPUT);
  pinMode(motorPin1B, OUTPUT);
  pinMode(motorPin2A, OUTPUT);
  pinMode(motorPin2B, OUTPUT);
  pinMode(motorPin3A, OUTPUT);
  pinMode(motorPin3B, OUTPUT);

  analogWrite(motorPin1A, 0);
  analogWrite(motorPin2A, 0);
  analogWrite(motorPin3A, 0);

  analogWrite(motorPin1B, 0);
  analogWrite(motorPin2B, 0);
  analogWrite(motorPin3B, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(motorPin1A, 255);
  analogWrite(motorPin2A, 220);
  analogWrite(motorPin3B, 0);
  delay(3000);

  analogWrite(motorPin1B, 0);
  analogWrite(motorPin2B, 0);
  analogWrite(motorPin3B, 0);
  delay(1000);

}
