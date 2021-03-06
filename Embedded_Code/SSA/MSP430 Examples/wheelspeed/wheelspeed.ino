/*Component: Suspension System Array
 * Portion: Wheel Speed
 * This code is used to calculate wheel speed.
 */
#include "Wire.h"
#include "msp430.h"

int Read_Hall();
int initiateTimer();
int end_Timer();
int wheel_speed();
int hall_pin = 13;
float initial_time = 0;
float end_time = 0;
float time_difference = 0;

int w_speed=0;
int KV = 0;


void setup()
{
  /* Hall Sensor Setup*/
  pinMode(hall_pin, INPUT);
  /*interrupt setup for the hall sensor to be excecuted in FALLING state*/
 // attachInterrupt(digitalPinToInterrupt(hall_pin),pin_ISR,FALLING);
  Serial.begin(9600);
  //Serial.print("end of setup");
}

/* function calcs wheel speed */
float Wheel_speed(float time_difference_micro)
{
  /* the tire radius is 18 inches */
  float wheel_diameter = 18;
  float circumf = 0;
  float half_rotation = 0;
  float time_in_millisecs = 0;
  float wheel_speed_f = 0;
  float hours = 0;
  float miles = 0;
  /* The circumf is the distance for a full rotation */
  circumf = (3.14159 * wheel_diameter);
  /* half_rotation is distance for a half rotation*/
  half_rotation = circumf/2;

  /*time diff in microseconds*/
  Serial.print("time diff micro: ");
  Serial.println(time_difference_micro);

  /*microseconds to hours conversion*/
  float power = pow(10,9);
  power = power * 3.6;
  hours = time_difference_micro / power;
  Serial.print("hours conversion: ");
  Serial.println(hours, 5);

  /*half rotation*/
  Serial.print("half rotation: ");
  Serial.println(half_rotation); 
  
  /*half rotations to miles*/
  miles = circumf / 63360;
  Serial.print("miles: ");
  Serial.println(miles, 5);
  
  /*Wheel speed for this half of a rotation*/
  /*convert from rotations per microsecond to miles per hour*/
  wheel_speed_f = miles / hours;
  Serial.print("wheel speed in miles per hours: ");
  Serial.println(wheel_speed_f, 4);
  
  return wheel_speed_f;
}

/* Interrupt function to calculate the wheel speed */


/* Start the timer in the loop */
void loop()
{
    float wheel_speed_final = 0;
    if(KV == 0)
    {
        initial_time = micros();
        Serial.print("Initial time: ");
        Serial.println(initial_time, DEC);
        delay(10);
        KV = 1;// variable set to one to not take the initial time again
    }
    if(digitalRead(hall_pin) == LOW)
    {
      end_time = micros();
      Serial.print("End time: ");
      Serial.println(end_time, DEC);
      delay(10);
      time_difference = end_time - initial_time;
      Serial.print("time difference: ");
      Serial.println(time_difference);
      wheel_speed_final= Wheel_speed(time_difference);
      Serial.print("wheel speed in main: ");
      Serial.println(wheel_speed_final, 4);
      Serial.println(" ");
      Serial.println(" "); 
      KV = 0;// resetting variable to 0 to take the initial time 
    }
   
}
