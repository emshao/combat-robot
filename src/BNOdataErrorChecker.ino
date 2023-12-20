#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

// Constants
#define BNO055_ADDRESS (0x28)
#define BNO055_ID (0xA0)
Adafruit_BNO055 bno = Adafruit_BNO055(BNO055_ID, BNO055_ADDRESS);

// Initialize BNO sensor
#define I2C_SDA A4
#define I2C_SCL A5

float previousYaw;

void setup() {
  Serial.begin(9600);                         // Initialize serial communication
  Wire.begin();                               // Initialize I2C communication
  
  if(!bno.begin()) {                          // Check to see if BNO exists
    Serial.print("No BNO055 detected!");
    while(1);
  }
  bno.setExtCrystalUse(true);

  previousYaw = getSensorData();

}

void loop() {
  float yaw = getSensorData(); 
  float yawError = cleanIMUData(yaw, previousYaw); 
  
  // if correct, should be an angle between -180 and 180
  // negative angle = robot turn to its left
  // positive angle = robot turn to its right 

  // printYaw(yaw);
  // printError(yawError);
}



printYaw(float yaw){
  Serial.print("X orientation: ");    // will get 16-bit signed integer value
  Serial.println(yaw);                // range from -180 to 180 *degrees*
}

printYawError(float yawError){
  Serial.print("Angle of error: ");
  Serial.print(yawError);
  if(yawError>0){
    Serial.println("    Turn Right");
  }
  else {
    Serial.println("    Turn Left");
  }
}




getSensorData() {
  sensors_event_t event;
  bno.getEvent(&event);
  float yaw = event.orientation.x;
  return yaw;
}



cleanIMUData(float current, float prev) {
  // calculate error magnitude
  float error = abs(current - prev);
  if(error > 180) {
    error = 360 - error;
  }

  // calculate error direction
  boolean inRight = false;
  if(current > prev) {
    inRight = true;
  }
  if((prev > 180) && (current < (prev-180))) {
    inRight = true;
  }

  // reverse error direction if needed
  if(inRight){
    error = -1 * error // the robot needs to go left
  }

  return error; // error is positive if the robot needs to turn to its right, 
                // error is negative if the robot needs to turn to its left
}
