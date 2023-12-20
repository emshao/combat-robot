#include <Wire.h>
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h> 

#define I2C_SDA A4
#define I2C_SCL A5

Adafruit_BNO055 bno = Adafruit_BNO055(55);
Servo gravitySensor;
float newgD;

void setup() {
  //tell microcontroller which pins read SDA/SCL
  Serial.begin(9600);
  Wire.begin(I2C_SDA);
  Wire.begin(I2C_SCL);

  //initializes sensor
  Serial.println("Orientation Sensor Test"); Serial.println("");
  if(!bno.begin())
  {
    Serial.print("Oops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);

  gravitySensor.attach(5);
  gravitySensor.write(90);
}

void loop() {
  //Get a new sensor event
  sensors_event_t event; 
  bno.getEvent(&event);
  newgD = event.orientation.z;

  //orientation.z will give gravity direction
  Serial.print("Gravity Direction: ");
  Serial.println(newgD, 4);


  if(newgD < 0){
    gravitySensor.writeMicroseconds(1500);
    delay(10);
    sensors_event_t event; 
    bno.getEvent(&event);
    newgD = event.orientation.z;
  }

  while(newgD > 0){
    gravitySensor.writeMicroseconds(1500);
    delay(10);
    newgD = event.orientation.z;
    sensors_event_t event; 
    bno.getEvent(&event);
    newgD = event.orientation.z;
  }

}
