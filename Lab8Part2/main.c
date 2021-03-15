/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 03/12/2021
* Project: Lab Eight Part Two
* File: Main.c
* Description: This program uses timer A to create a PWM signal that is used
* to slow down or speed up a dc motor. The program needs to be paused and the
* input variable needs to be changed. This variable controlls the time off so
* a value of 90 is a duty cycle of .1 and a value of 10 is a duty cycle of .9.
* The input variable can take input from 0 to 100, 0 being full speed and 100
* being off.
**************************************************************************************/

#include "msp.h"

void timer_init(void);

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	// Configure GPIO for PWM output
     P5->SEL0 |= BIT6;
     P5->SEL1 &= ~(BIT6);
     P5->DIR |= BIT6;    // P2.4 set TA0.1

	int DC,input;


	timer_init();



	while(1){
	    DC = input*100;

	    TIMER_A2->CCR[1] = DC;           // CCR1 PWM duty cycle
	}
}

/****| timer_initFunction | *****************************************
* Brief: This function initializes the timer A. It sets timer
* A to up mode, to use  SMCLK, the number of cycles to count
* to, and reset/set mode.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void timer_init(void){
    TIMER_A2->CCR[0] = (10000 - 1);
    TIMER_A2->CCTL[1] = 0b0000000001110000;
    TIMER_A2->CTL = 0b0000001000010100;
}
