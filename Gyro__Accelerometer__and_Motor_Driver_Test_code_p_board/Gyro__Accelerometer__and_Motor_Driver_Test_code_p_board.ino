// This code will test the capabilities of Gyro, Accelerometer,
// and Motor Controllers.
// The pins are setup, analog readings are read from the accel.
// and gyro and printed to the serial module.
// Accordingly, PWM signals are output to motor controller.


int motorPin = 9;
int analogAxIn = A0;
int analogGyIn = A5;

void setup()
{
   pinMode(motorPin, OUTPUT); 
}

void loop()
{
  
}
