#include <Wire.h>
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h> 

Servo wheelOne;
Servo wheelTwo;
Servo wheelThree;
int thetaPin = 7;
int forwardPin = 8;
int sidePin = 9;

void setup() {
  Serial.begin(9600);
  Serial.println("Start");

  wheelOne.attach(2);
  wheelTwo.attach(3);
  wheelThree.attach(4);

}

void loop() {
  // put your main code here, to run repeatedly:

}
