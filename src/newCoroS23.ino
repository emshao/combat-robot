#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

// Constants
#define BNO055_ADDRESS (0x28)                                       // I2C address of BNO055 sensor
#define BNO055_ID (0xA0)                                            // ID of BNO055 sensor
Adafruit_BNO055 bno = Adafruit_BNO055(BNO055_ID, BNO055_ADDRESS);   // Create BNO055 sensor object

// Initialize BNO sensor
#define I2C_SDA A4
#define I2C_SCL A5

// PWM pins: 3, 5, 6, 9, 10, 11
// these pins connect the red and black wires of the nano to the motor
// send opposite signals to the motors (figure out how this works)
#define motorPin1A 3
#define motorPin1B 5
#define motorPin2A 6
#define motorPin2B 9
#define motorPin3A 10
#define motorPin3B 11

// define input pins from remote controller
#define rightFwd 4    // channel 2
#define rightSide 7   // channel 1
#define leftSide 8  // channel 4
// weapon is channel 3






void setup() {
  Serial.begin(9600);                         // Initialize serial communication
  Wire.begin();                               // Initialize I2C communication
  
  if(!bno.begin()) {                          // Check to see if BNO exists
    Serial.print("No BNO055 detected!");
    while(1);
  }
  bno.setExtCrystalUse(true);

  pinMode(motorPin1A, OUTPUT);                // Initialize all motor output pins
  pinMode(motorPin1B, OUTPUT);
  pinMode(motorPin2A, OUTPUT);
  pinMode(motorPin2B, OUTPUT);
  pinMode(motorPin3A, OUTPUT);
  pinMode(motorPin3B, OUTPUT);

  pinMode(rightFwd, INPUT);                   // Initialize all remote controller input pins
  pinMode(rightSide, INPUT);
  pinMode(leftSide, INPUT);

  // calibrationTest();                          // Make sure all motors can turn, make sure a signal is read from the remote controller
  // setAllToZero();                             // Set the angle set point to zero, set all motors to stop turning
  
}


float previousYaw = getSensorData();

void loop() {
  // getting raw data
  unsigned long anglePulse = pulseIn(leftSide, HIGH);    // get raw data from remote controller
  unsigned long fwdPulse = pulseIn(rightFwd, HIGH);
  unsigned long sidePulse = pulseIn(rightSide, HIGH);
  float yaw = getSensorData();                           // get raw data from IMU sensor

  // standardizing raw data
  float angleVal = cleanRemoteControlData(anglePulse);   // NOT IMPLEMENTED yet
  float fwdVal = cleanRemoteControlData(fwdPulse);
  float sideVal = cleanRemoteControlData(sidePulse);
  float yawError = cleanIMUData(yaw, previousYaw);

  // do math to get motor outputs, remember that they should be integers between 0-255!!
  int[] motorOutputs = getMotorOutputValues(fwdVal, sideVal, yawError);

  // writing outputs to motors
  analogWrite(motorPin1A, motorOutputs[0]);
  analogWrite(motorPin1B, motorOutputs[1]); 
  analogWrite(motorPin2A, motorOutputs[2]);
  analogWrite(motorPin2B, motorOutputs[3]);
  analogWrite(motorPin3A, motorOutputs[4]);
  analogWrite(motorPin3B, motorOutputs[5]);

  // update previousYaw with angleVal if we do decide to turn
  
}





getSensorData() {
  sensors_event_t event;
  bno.getEvent(&event);
  float yaw = event.orientation.x;
  return yaw;
}



cleanRemoteControlData(unsigned long pulseVal) {
  float outcome = 0; // change!
  return float;
}



cleanIMUData(float current, float prev) {
  // calculate error magnitude
  float error = abs(current - prev);
  if(error > 180) {error = 360 - error;}
  
  // reverse error direction if needed
  if((current > prev) || ((prev > 180) && (current < (prev-180)))){
    error = -1 * error // the robot needs to go left
  }
  return error; 
}
