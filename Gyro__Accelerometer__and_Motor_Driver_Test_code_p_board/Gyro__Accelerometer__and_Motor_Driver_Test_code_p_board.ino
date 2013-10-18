// This code will test the capabilities of Gyro, Accelerometer,
// and Motor Controllers.
// The pins are setup, analog readings are read from the accel. X-AXIS
// and gyro and printed to the serial module.
// Accordingly, PWM signals are output to motor controller.

#include <Stepper.h> // Will be driving a Stepper motor
#define STEPS XXX // set to number of steps on motor


//Stepper stepper(STEPS, 8, 9 , 10, 11);

int motorPin = 3; // PWM capable
int analogAxIn = A0;
int analogGyIn = A5;

int raw_dataAx;
int raw_dataGy;

int motorSpeed; // in RPMs
int motorSteps; // number of steps

float gravs;  // gravitational units
float dps;  // degrees per second

float my_map(float x, float in_min, float in_max, float out_min, float out_max);

void setup()
{
   pinMode(motorPin, OUTPUT); 
  // stepper.setSpeed(motorSpeed); // sets speed of motor to 30 RPMS ...
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
  Serial.print(dps);
  Serial.println(" dps  |");
  
  //Drive stepper motor fast when dps is large, smaller as dps decreases
  // Maximum 60 RPM, minimum 5RPM (?)
 // motorSpeed = map(dps, -500, 500, 5, 60);
 // stepper.setSpeed(motorSpeed);
  // Number of steps determined 
  
}

float my_map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

