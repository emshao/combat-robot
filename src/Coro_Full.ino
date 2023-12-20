#include <Wire.h>
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h> 

#define I2C_SDA A4
#define I2C_SCL A5

Adafruit_BNO055 bno = Adafruit_BNO055(55);
float diff = 0;
Servo wheelOne;
Servo wheelTwo;
Servo wheelThree;
int forwardPin = 8;
int sidePin = 9;

float m1;
float m2;
float m3;
float m4;
float m5;
float m6;

int ser1;
int ser2;
int ser3; 

void setup() {
  //tell microcontroller which pins read SDA/SCL
  Serial.begin(9600);
  Wire.begin(I2C_SDA);
  Wire.begin(I2C_SCL);

  //initializes sensor
  Serial.println("Orientation Sensor Test"); Serial.println("");
  if(!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);

  //initializes wheels
  wheelOne.attach(4);
  wheelOne.writeMicroseconds(1500);
  wheelTwo.attach(5);
  wheelTwo.writeMicroseconds(1500);
  wheelThree.attach(6);
  wheelThree.writeMicroseconds(1500);

  //initializes remote signals
  pinMode(forwardPin, INPUT); 
  pinMode(sidePin, INPUT);
}

void loop() {
  //Get a new sensor event
  sensors_event_t event; 
  bno.getEvent(&event);

  //orientation.x gives tilt/position in x direction in degrees
//  Serial.print("X: ");
//  float xVal = event.orientation.x;
//  Serial.print(xVal, 4);

  //angle for kiwi drive
//  diff = 360-xVal;
//  Serial.print("\tCurrent 0: ");
//  Serial.print(diff, 4);
//  Serial.println("");

  //forward inputs
  long fwdDuration = pulseIn(forwardPin, HIGH);
  //Serial.println(fwdDuration);
  float fwdVal = map((float)fwdDuration, 1900.0, 900.0, -1.0, 1.0);
  Serial.println(fwdVal);

  //side inputs
  long sideDuration = pulseIn(sidePin, HIGH);
  //Serial.println(sideDuration);
  float sideVal = map((float)sideDuration, 1050.0, 2030.0, -1.0, 1.0);
  //Serial.println(sideVal);

  //change to driving outputs
  if(fwdDuration>1300 && fwdDuration<1500 && sideDuration>1400 && sideDuration<1600){
    wheelOne.writeMicroseconds(1500);
    wheelTwo.writeMicroseconds(1500);
    wheelThree.writeMicroseconds(1500);
    }
  else{
    kiwiFunct(fwdVal, sideVal);
    convertToMS();
    wheelOne.writeMicroseconds(ser1);
    wheelTwo.writeMicroseconds(ser2);
    wheelThree.writeMicroseconds(ser3);
  }
}

void kiwiFunct(float fwdVal, float sideVal){
     m1 = -sqrt(3)/2 * fwdVal;
     m2 = sqrt(3)/2 * fwdVal;
     m3 = 0;
     m4 = .5 * sideVal;
     m5 = .5 * sideVal;
     m6 = -1 * sideVal;
}

void convertToMS(){
//  test cases
//  ser1 = (int)(map(m1, -1, 1, 1000, 2000));
//  ser2 = (int)(map(m2, -1, 1, 1000, 2000));
//  ser3 = (int)(map(m3, -1, 1, 1000, 2000));

//  ser1 = (int)(map(m4, -1, 1, 1000, 2000));
//  ser2 = (int)(map(m5, -1, 1, 1000, 2000));
//  ser3 = (int)(map(m6, -1, 1, 1000, 2000));
  
  float avg1 = (m1+m4)/2.0;
  float avg2 = (m2+m5)/2.0;
  float avg3 = (m3+m6)/2.0;
  
  ser1 = (int)(map(avg1, -1, 1, 1000, 2000));
  ser2 = (int)(map(avg2, -1, 1, 1000, 2000));
  ser3 = (int)(map(avg3, -1, 1, 1000, 2000));
}

float map(float v, float a, float b, float c, float d){
  return (v-a) * (d-c) / (b-a) + c;
}
