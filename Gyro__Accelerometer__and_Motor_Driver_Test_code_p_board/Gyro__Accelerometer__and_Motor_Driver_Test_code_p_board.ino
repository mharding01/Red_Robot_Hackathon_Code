// This code will test the capabilities of Gyro, Accelerometer,
// and Motor Controllers.
// The pins are setup, analog readings are read from the accel.
// and gyro and printed to the serial module.
// Accordingly, PWM signals are output to motor controller.


int motorPin = 9;
int analogAxIn = A0;
int analogGyIn = A5;

int raw_dataAx;
int raw_dataGy;

float gravs;  // gravitational units
float dps;  // degrees per second

void setup()
{
   pinMode(motorPin, OUTPUT); 
   Serial.begin(9600);
}

void loop()
{
  delay(50);  // too buffer for Serial module readability
  
  raw_dataAx = analogRead(analogAxIn);
  map
  raw_dataGy = analogRead(analogGyIn);
  
  Serial.print("Accelerometer Reads: ");
  Serial.print(raw_dataAx);
  Serial.print(
  
}
