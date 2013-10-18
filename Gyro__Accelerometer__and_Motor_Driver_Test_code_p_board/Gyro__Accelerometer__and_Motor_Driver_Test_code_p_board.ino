// This code will test the capabilities of Gyro, Accelerometer,
// and Motor Controllers.
// The pins are setup, analog readings are read from the accel.
// and gyro and printed to the serial module.
// Accordingly, PWM signals are output to motor controller.

#include <Stepper.h>

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
   Serial.println("|  Accelerometer Readings  |  Gyro Readings  |");
}

void loop()
{
  delay(50);  // too buffer for Serial module readability
  
  raw_dataAx = analogRead(analogAxIn);
  gravs = my_map((float)raw_dataAx, 0.0, 1023.0, -1.5, 1.5);  // gravitational units in range -1.5<g<1.5
  raw_dataGy = analogRead(analogGyIn);
  dps = map(raw_dataGy, 0, 1023, -500, 500);  // degrees/s units in range +/- 500 dps
  
  // Printing accel. readings in g's, then tab over for gyro readings in dps
  Serial.print("|  ");
  Serial.print(gravs);
  Serial.print("g  \t  ");
  Serial.println("dps  |");
  
}

float my_map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

