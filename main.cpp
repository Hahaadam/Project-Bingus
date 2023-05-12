#include "mbed.h"
#include "motor.h"
#include "tunes.h"
#include "pwm_tone.h"

#define TIME_PERIOD 2             //Constant compiler Values here 2 equates to 2ms or 500Hz base Frequency
#define DUTY 0.9                  //DUTY of 1.0=100%, 0.4=40% etc.,
const float SECOND  = 1000000;    //Second in micro    
const float FORWARD = 4.25;
const float TURN = 1;
const float STEPAWAY = 0.7;
const float SHIFT = 1.5;

DigitalIn microswitch1(D4);       //switch on back of bot
Motor Wheel(D13,D11,D9,D10);      //Instance of the Motor Class called 'Wheel' see motor.h and motor.cpp
DigitalIn myButton(USER_BUTTON);  //USER_BUTTON is the Blue Button on the NUCLEO Board
DigitalOut led_red(LED3);         //LED1 is the Green LED on the NUCLEO board
                                  //N.B. The RED LED is the POWER Indicator
                                  //and the Multicoloured LED indicates status of the ST-LINK Programming cycle																	
DigitalOut led_blue(LED2);
DigitalOut led_green(LED1);

//Variable 'duty' for programmer to use to vary speed as required set here to #define compiler constant see above
float duty=DUTY;


int main ()
{
  printf("ROCO104 Demonstration Robot Buggy Plymouth University 2022/23\n\r");

  Wheel.Period_in_ms(TIME_PERIOD);
  Wheel.Stop();
    while(myButton==0)
    {                       //Wait here for USER Button (Blue) on Nucleo Board (goes to zero when pressed
        led_red=0;              //and flash green LED whilst waiting
        wait_us(100*1000);
        led_red=1; 
        wait_us(100*1000);
		if (microswitch1){tone1();printf("Switch1\n\r");}
		
    }

    while(true)
    {
      Wheel.Speed(1,1);
      wait_us(FORWARD*SECOND);
      Wheel.Stop();
      Wheel.Speed(-1,-1);
      while(microswitch1==0);      
      Wheel.Stop();
      Wheel.Speed(1,1);
      wait_us(STEPAWAY*SECOND);
      Wheel.Stop();
      Wheel.Speed(1,-1);
      wait_us(TURN*SECOND);
      Wheel.Stop();
      Wheel.Speed(1,1);
      wait_us(SHIFT*SECOND);
      Wheel.Stop();
      Wheel.Speed(-1,1);
      wait_us(TURN*SECOND);
      Wheel.Speed(-1,-1);
      while(microswitch1==0);
      Wheel.Stop();

    }
}
