#include <Wire.h>
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define I2C_SDA A4
#define I2C_SCL A5

Adafruit_BNO055 bno = Adafruit_BNO055(55);
float gd = 0;
Servo gravitySensor;
float angle = 90;

void setup() {
  gravitySensor.attach(5);
  gravitySensor.write(angle);
  Serial.begin(9600);
  Wire.begin(I2C_SDA);
  Wire.begin(I2C_SCL);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  if(!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);
  
}

void loop() {
  sensors_event_t event; 
  bno.getEvent(&event);
  
  Serial.print("Z: ");
  gd = event.orientation.z;
  Serial.println(gd, 4);

  if(gd > 0.0){
    gravitySensor.write(angle+(angle/10.0));
    angle+=(angle/10.0);               
    delay(15);
  }
  if(gd < 0.0){
    gravitySensor.write(angle-(angle/10.0));
    angle-=(angle/10.0);               
    delay(15);
  }
}
