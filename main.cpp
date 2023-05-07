/*
Simple Routine for Nucleo Board for ROCO104 Buggy Motor Control and Microswitches
Heavy edit from previous ROCO103PP code
Now for PRO101 February 2023 - M R Simpson
Motor Class can now be instansiated with all four pins needed to control the H Bridge
with a member functions as follows

Motor::Speed(float A, Float B) range -0.1 to +1.0 to give full reverse to full forward for A/B motors
Motor::Stop()       STOP
Motor::Fwd(float)   Forward but floating point number (range 0.0 to 1.0)
Motor::Rev(float)   Reverse but floating point number (range 0.0 to 1.0)

Plymouth University
M.Simpson 31st October 2016
Edited 03/02/2017
Edited 06/12/2018
Edited 21/02/2023
*/
// code runs of NUCLEO-F429ZI
#include "mbed.h"
#include "motor.h"
#include "tunes.h"
#include "pwm_tone.h"

#define TIME_PERIOD 2             //Constant compiler Values here 2 equates to 2ms or 500Hz base Frequency
#define DUTY 0.9                  //DUTY of 1.0=100%, 0.4=40% etc.,

DigitalIn microswitch1(D4);       //switch on back of bot
DigitalIn microswitch2(D3);       //unused pin

Motor Wheel(D13,D11,D9,D10);      //Instance of the Motor Class called 'Wheel' see motor.h and motor.cpp

DigitalIn myButton(USER_BUTTON);  //USER_BUTTON is the Blue Button on the NUCLEO Board

DigitalOut led_red(LED3);         //LED1 is the Green LED on the NUCLEO board
                                  //N.B. The RED LED is the POWER Indicator
                                  //and the Multicoloured LED indicates status of the ST-LINK Programming cycle
																	
DigitalOut led_blue(LED2);
DigitalOut led_green(LED1);

//Variable 'duty' for programmer to use to vary speed as required set here to #define compiler constant see above
float duty=DUTY;
//
int main ()
{
  printf("ROCO104 Demonstration Robot Buggy Plymouth University 2022/23\n\r");

  Wheel.Period_in_ms(TIME_PERIOD);//Set frequency of the PWMs

  //
  //--------------------------- your strategy goes between the two dashed lines ---------------------------------------------   
  //
    Wheel.Stop();

    close_encounter(2);     //tune to play Announce start!
    //twinkle(2);           //see tunes.h for alternatives or make your own!
    //jingle_bells(2);

    while(myButton==0)
    {                       //Wait here for USER Button (Blue) on Nucleo Board (goes to zero when pressed)
        led_red=0;              //and flash green LED whilst waiting
        wait_us(100*1000);
        led_red=1; 
        wait_us(100*1000);
        //Test Microswitches with two different tones see tunes.cpp tunes.h or flash (led1 and led2) onboard LEDs
				if (microswitch1){tone1();printf("Switch1\n\r");}
				if (microswitch2){tone2();printf("Switch2\n\r");}
    }
    testroutine();

    while(true)                             //Repeat the following forever NB always true!
    {	
      

            // YOUR LINES OF CODE for your stratagy go between HERE! +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // Remember to use plenty of comments by using:-
            // Single line
            /*
            multiple
            lines
            */





            // and HERE! +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    } //end of while loop!
}     //end of main()
void testroutine()
{
  Wheel.Speed(1,1);
  wait_us(100*1000);
  Wheel.Stop();
  Wheel.Speed(1,0);
  wait_us(100*1000);
  Wheel.Stop();
  Wheel.Speed(1,1);
  wait_us(100*1000);
  Wheel.Stop();
  Wheel.Speed(0,1);
  wait_us(100*1000);
  Wheel.Stop();
}


//NB following HELP notes here.....
/*
//Consider these lines of code to Accelerate the motors
      for (float i=0.5f; i<=1.0f; i+=0.01f) //Accelerate  from 50% to 100%
      { 
        Wheel.Speed(i,i);
        wait(0.1f);
      }
*/
