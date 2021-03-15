/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 03/2/2021
* Project: Lab Seven Part Two
* File: Main.c
* Description: This program prints MAX to the first row of a 4x16 LCD
* centered. Then it prints RAUCH centered to the second row of the LCD.
* It the prints EGR centered on the third row, and 226 centered on the
* fourth row.
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

/*
	TIMER_A2->CCR[0] = (10000 - 1);
	TIMER_A2->CCTL[1] = 0b0000000001110000;
	TIMER_A2->CTL = 0b0000001000010100;
*/
	timer_init();



	while(1){
	    DC = input*100;

	    TIMER_A2->CCR[1] = DC;           // CCR1 PWM duty cycle
	}
}

/****| timer_initFunction | *****************************************
* Brief: This function initializes the LCD
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void timer_init(void){
    TIMER_A2->CCR[0] = (10000 - 1);
    TIMER_A2->CCTL[1] = 0b0000000001110000;
    TIMER_A2->CTL = 0b0000001000010100;
}
