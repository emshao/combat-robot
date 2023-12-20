// Define the pin number
const int outputPin = 4; // Pin D4
const int outAnaPin = A4;

void setup() {
  // Initialize the digital pin as an output
  pinMode(outputPin, OUTPUT);
  pinMode(outAnaPin, OUTPUT);
}

void loop() {
  // Turn the pin on (HIGH)
  digitalWrite(outputPin, HIGH);
  
  // Wait for one second
  delay(1000);
  
  // Turn the pin off (LOW)
  digitalWrite(outputPin, LOW);
  
  // Wait for one second
  delay(1000);

  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(outAnaPin, brightness);
    delay(10); // Delay for smooth fading
  }

  analogWrite(outAnaPin, 0);
}
