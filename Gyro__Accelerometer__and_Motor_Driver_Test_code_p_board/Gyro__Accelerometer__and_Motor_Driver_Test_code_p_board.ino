// This code will test the capabilities of Gyro, Accelerometer,
// and Motor Controllers.
// The pins are setup, analog readings are read from the accel. X-AXIS
// and gyro and printed to the serial module.
// Accordingly, PWM signals are output to motor controller.

#define STEPS XXX // set to number of steps on motor
#define BACK_MAX_G -0.10
#define FRONT_MAX_G -1.02
#define PARALLEL_G -0.61


int stepPin = 3; // PWM capable
int dirPin = 4;
int analogAxIn = A0;
int analogGyIn = A5;

int i; // for loop counter
int raw_dataAx;
int raw_dataGy;

int motorSpeed; // in RPMs
int motorSteps; // number of steps
int dirMotor = HIGH; // set to high intially

float gravs;  // gravitational units
float dps;  // degrees per second

int sum_dataAx;
int av_dataAx;
int sum_dataGy;
int av_dataGy;

float my_map(float x, float in_min, float in_max, float out_min, float out_max);

void setup()
{
   pinMode(stepPin, OUTPUT); 
   pinMode(dirPin, OUTPUT);
   
   sum_dataAx =0;
   av_dataAx = 0;
   sum_dataGy = 0;
   av_dataGy = 0;
  // stepper.setSpeed(motorSpeed); // sets speed of motor to 30 RPMS ...
   Serial.begin(9600);
   Serial.println("|  Accelerometer Readings  |  Gyro Readings  |");
}

void loop()
{
  delay(50);  // too buffer for Serial module readability
  
   sum_dataAx =0;
   av_dataAx = 0;
   sum_dataGy = 0;
   av_dataGy = 0;
  
  for(i = 0; i<20; i++)
  {
    raw_dataAx = analogRead(analogAxIn);
    sum_dataAx += raw_dataAx;
  }
  
  av_dataAx = sum_dataAx / 20;
  gravs = my_map((float)av_dataAx, 0.0, 1023.0, -1.5, 1.5);  // gravitational units in range -1.5<g<1.5
  if (gravs < 0)
  {
    dirMotor = HIGH;  // this is to test
  }
  else if (gravs > 0)
  {
    dirMotor = LOW; // this is to test
  }
  
  for(i = 0; i<20; i++)
  {
    raw_dataGy = analogRead(analogGyIn);
    sum_dataGy += raw_dataGy;
  }
  av_dataGy = sum_dataGy / 20;
  dps = map(av_dataGy, 0, 4095, -500/4, 500/4);  // degrees/s units in range +/- 500 dps
  dps += 11*10; // Data filtering as zero tends to be around -11*10
  // Printing accel. readings in g's, then tab over for gyro readings in dps
  Serial.print("|  ");
  Serial.print(gravs);
  Serial.print("g  \t  ");
  Serial.print(dps);
  Serial.println(" dps  |");
  
  Serial.print("\t Stepping Motor... dirMotor = ");
  Serial.print(dirMotor);
  //Serial.print(raw_dataAx);
  //Serial.println(" raw analog  |");
  
  //Drive stepper motor fast when dps is large, smaller as dps decreases
  // Maximum 60 RPM, minimum 0RPM (?)
   motorSpeed = map(dps, -500/4, 500/4, 0, 60);
   Serial.print("  Speed = ");
   Serial.print(motorSpeed);
  // Number of steps determined by gravity angle - how close to parallel
  // Maximum number of steps 100 steps per second, Minimum number of steps 0 
   motorSteps = (int)my_map(gravs, -1.5, 1.5, 0.0, 100.0);
   Serial.print("  Steps");
   Serial.println(motorSteps);
   // Drive motor several steps, with delay in between steps
   digitalWrite(dirPin, dirMotor);
   for (i = 0; i < motorSteps; i++)
   {
     digitalWrite(stepPin, HIGH);
     delay(5);
     digitalWrite(stepPin, LOW);
     delay(5);
   }
   
  
}

float my_map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

