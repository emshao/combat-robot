#include <Wire.h>
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h> 
/*import libraries for adafruit*/

#define I2C_SDA A4
#define I2C_SCL A5

//micros function - polling: find pulse width. use pulseIn - check in order
//pin change interrupt - interrupt: externally generated event in hardware -> function: interrupt handler
//mbus protocol??

Adafruit_BNO055 bno = Adafruit_BNO055(55);

Servo wheelOne;
Servo wheelTwo;
Servo wheelThree;
int thetaPin = 7;
int forwardPin = 8;
int sidePin = 9;

float m1;
float m2;
float m3;

int ser1;
int ser2;
int ser3; 

float xVal;

void setup() {
  //indicate which pins read SDA/SCL
  Serial.begin(9600);
  Wire.begin(I2C_SDA);
  Wire.begin(I2C_SCL);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);

  //initialize wheels
  wheelOne.attach(2);
  wheelTwo.attach(3);
  wheelThree.attach(4);
  calib();

  //initialize remote signals
  pinMode(forwardPin, INPUT); 
  pinMode(sidePin, INPUT);
  pinMode(thetaPin, INPUT);

  sensorEvent();

//  while(xVal>355 || xVal<5){
//    rotateRight();
//    sensorEvent();
//    printXVal();
//  }
  calib();
}

void loop() {
  sensorEvent();
  printXVal();

  //900-2100 is around working range

  //theta inputs
  long thetaDuration = pulseIn(thetaPin, HIGH);
  //Serial.println(thetaDuration);
  float thetaVal = map((float)thetaDuration, 1940.0, 950.0, -1.0, 1.0);
  
  //forward inputs
  long fwdDuration = pulseIn(forwardPin, HIGH);
  //Serial.println(fwdDuration);
  float fwdVal = map((float)fwdDuration, 1000.0, 1980.0, -1.0, 1.0);

  //side inputs
  long sideDuration = pulseIn(sidePin, HIGH);
  //Serial.println(sideDuration);
  float sideVal = map((float)sideDuration, 1080.0, 2030.0, -1.0, 1.0);

//  if(fwdDuration>1400 && fwdDuration<1600 && sideDuration>1400 && sideDuration<1600 && thetaDuration>1350 && thetaDuration <1550){
//    wheelOne.writeMicroseconds(1500);
//    wheelTwo.writeMicroseconds(1500);
//    wheelThree.writeMicroseconds(1500);
//    }
//else{
//    kiwiFunct(fwdVal, sideVal, thetaVal);
//    convertToMS();
//    wheelOne.writeMicroseconds(ser1);
//    wheelTwo.writeMicroseconds(ser2);
//    wheelThree.writeMicroseconds(ser3);
//  }

   sensorEvent();
   printXVal();

  //adjust(xVal);

  kiwiFunct(fwdVal, sideVal, thetaVal);
  convertToMS();
  
  printSer();
  wheelOne.writeMicroseconds(ser1); 
  wheelTwo.writeMicroseconds(ser2);
  wheelThree.writeMicroseconds(ser3);

}

void kiwiFunct(float fwdVal, float sideVal, float thetaVal){
  m1 = .5 * sideVal -sqrt(3)/2 * fwdVal + thetaVal;
  m2 = .5 * sideVal + sqrt(3)/2 * fwdVal + thetaVal;
  m3 = -1 * sideVal + thetaVal;
}


void convertToMS(){
  float avg1 = (m1)/3.0;
  float avg2 = (m2)/3.0;
  float avg3 = (m3)/3.0;
  
  ser1 = (int)(map(avg1, -1, 1, 1000, 2000));
  ser2 = (int)(map(avg2, -1, 1, 1000, 2000));
  ser3 = (int)(map(avg3, -1, 1, 1000, 2000));
 }


//takes value v between a and b and maps to corresponding value in range c-d
float map(float v, float a, float b, float c, float d){
  return (v-a) * (d-c) / (b-a) + c;
}

void adjust(float xVal){
  while(xVal>5 && xVal<355){
  
    if(180>xVal && xVal>5){
      rotateLeft();
    }
    if(355>xVal && xVal>=180){
      rotateRight();
    }
    
  sensorEvent();
  printXVal();
  }
}

void rotateLeft(){
  wheelOne.writeMicroseconds(1300);
  wheelTwo.writeMicroseconds(1300);
  wheelThree.writeMicroseconds(1300);
  delay(50);
  calib();
}

void rotateRight(){
  wheelOne.writeMicroseconds(1700);
  wheelTwo.writeMicroseconds(1700);
  wheelThree.writeMicroseconds(1700);
  delay(50);
  calib();
}

void calib(){
  wheelOne.writeMicroseconds(1500);
  wheelTwo.writeMicroseconds(1500);
  wheelThree.writeMicroseconds(1500);
}

void printSer(){
  Serial.println(ser1);
  Serial.println(ser2);
  Serial.println(ser3);
}

/* Get a new sensor event */ 
void sensorEvent(){
  sensors_event_t event; 
  bno.getEvent(&event);
  xVal = event.orientation.x;
}

/* Display sensor floating point data */
void printXVal(){
  Serial.print("xVal: " );
  Serial.println(xVal, 4);
}
