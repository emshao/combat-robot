#include <Wire.h> // provides functions using I2C communication protocol

// input pins from remote controller
#define motorR0 9
#define motorR1 6
#define motorL0 5
#define motorL1 3
#define motorB0 10
#define motorB1 11


#define ch1input 4
#define ch2input 7
#define ch4input 8



void setup() {
  // put your setup code here, to run once:

  // PWM signals from receiver
  long ch1Rside = 0.0;
  long ch2Rfwd = 0.0;
  long ch4Lside = 0.0;

  // input pins from receiver
  pinMode(ch1input, INPUT);
  pinMode(ch2input, INPUT);
  pinMode(ch4input, INPUT);

  // Motor outputs
  int motorValues[] = [0, 0, 0, 0, 0, 0]

  // outputs pins to L239D drivers
  pinMode(motorR0, OUTPUT);
  pinMode(motorR1, OUTPUT);
  pinMode(motorL0, OUTPUT);
  pinMode(motorL1, OUTPUT);
  pinMode(motorB0, OUTPUT);
  pinMode(motorB1, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  // PWM values from receiver -- note to read these pin numbers, seems like they are not precise
  
  ch1Rside = pulseIn(ch1input, HIGH);
  ch2Rfwd = pulseIn(ch2input, HIGH);
  ch4Lside = pulseIn(ch4input, HIGH);

  // 

  // motor values 0 to 255
  analogWrite(motorR0, motorValues[0]);
  analogWrite(motorR1, motorValues[1]);
  analogWrite(motorL0, motorValues[2]);
  analogWrite(motorL1, motorValues[3]);
  analogWrite(motorB0, motorValues[4]);
  analogWrite(motorB1, motorValues[5]);

}


void setDriveVals(int* motorVals, int* percentage) {
  // len(mV) = 6, len(per) = 3
  for (int i = 0; i < 3; i++) {

    if (percentage[i]<0) {
      motorVals[2*i] = 0;
      motorVals[2*i+1] = 255*percentage[i];
    } else {
      motorVals[2*i] = 255*percentage[i];
      motorVals[2*i+1] = 0;
    }
    
  }
}

// left controller is to spin left and right 
// set left as 

void setSpinLeft(int* motorVals, int strength) {
  for (int i = 0; i < 3; i++) {
    motorVals[2*i] = 0;
    motorVals[2*i+1] = 255*strength;
  }
}

void setSpinRight(int* motorVals, int strength) {
  for (int i = 0; i < 3; i++) {
    motorVals[2*i] = 255*strength;
    motorVals[2*i+1] = 0;
  }
}




