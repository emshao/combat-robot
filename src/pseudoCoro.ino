#include packages needed

void setup() {
  // put your setup code here, to run once:

  set up BNO connections
  set up motor connections (declare outputs)
  set up receiver input connections (declare inputs)
  
  calibration tests (declare the current 0, spin to max on each side)

  set everything to center (aka no voltage difference, centered at angle)
  
}

void loop() {
  // put your main code here, to run repeatedly:

  check if deviating IMU
  if yes --> fix
    run error check
    run error fixing calculators
    give signal to motors

  check if has inputs coming in 
  if yes --> excute with the given input
    run conversion
    run creating KIWI numbers
    give signal to motors
  
}
