//PortC interrupt control A0-A3  and PortB D11,D12 are used to read the  6 channel inputs
#include<Servo.h>
Servo channel1,channel2,channel3,channel4;// Aieloron,Elevation,throttle,Yaw

//variables used to read input from channel 1,2,3 ,4,5,6
unsigned long  counter_1,counter_2,counter_3,counter_4,counter_5,counter_6, current_count; 
byte last_CH1_state,last_CH2_state,last_CH3_state,last_CH4_state,last_CH5_state,last_CH6_state;

//initial Variable declaration  for 6 channel outputs
float channel1Output=1500,channel2Output=1500,channel3Output=1000,channel4Output=1500,channel5Output=1000,channel6Output=1000;
float final1Out=1500,final2Out=1500,final3Out=1000,final4Out=1500;

//for compass 
#include <Wire.h>
#include <MechaQMC5883.h>
int x,y,z,azimuth,compass_initial,compass_current;
int p_mag=-5,yaw_change=0;
MechaQMC5883 qmc;

//for GPS 
#include "TinyGPS++.h"
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data
float initial_lat=0,initial_lng=0,current_lat=0,current_lng=0;
float p_lat=1,p_lng=1,Ail_change=0,Ele_change=0;
