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

float my_map(float x, float in_min, float in_max, float out_min, float out_max);

void setup()
{
   pinMode(motorPin, OUTPUT); 
   Serial.begin(9600);
}

void loop()
{
  delay(50);  // too buffer for Serial module readability
  
  raw_dataAx = analogRead(analogAxIn);
  gravs = map(raw_dataAx, 0, 1023, -1.5, 1.5);  // gravitational units in range -1.5<g<1.5
  raw_dataGy = analogRead(analogGyIn);
  
  Serial.print("Accelerometer Reads: ");
  Serial.print(raw_dataAx);
  Serial.print(
  
}

float my_map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

