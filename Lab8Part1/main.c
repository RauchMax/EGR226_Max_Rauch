/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 03/12/2021
* Project: Lab Eight Part One
* File: Main.c
* Description: This program uses systick timer to create a pseudo analog signal.
* This program has a variable that is used to control the duty cycle of a dc
* motor. The user has to pause the program then enter a number between 1-99. A
* value of 10 represents a DC of .1 and a value of 90 represents a DC of .9.
**************************************************************************************/

#include "msp.h"


void SysTick_Init (void);    //prototyping the systick initialization


void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	SysTick_Init ();     // initializing systick

	int DC;              //making duty cycle variable

	while(1){

	    P2OUT |= BIT3;         // turn motor on

	    SysTick -> LOAD = ((DC * 3000) -1 ); //delay for DC milliseconds
	    SysTick -> VAL = 0;
	    while ( (SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET

	    P2OUT &= ~BIT3;                     // turn motor off

	    SysTick -> LOAD = (((100-DC) * 3000) - 1); //delay for delay for the off time of the duty cycle
	    SysTick -> VAL = 0;
	    while ( (SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET

	}
}

/****| SysTick_InitFunction | *****************************************
* Brief: This function initializes the SysTick timer.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void SysTick_Init (void)
{

    SysTick -> CTRL = 0;             // disable SysTick During step
    SysTick -> LOAD = 0x00FFFFFF;   // max reload value
    SysTick -> VAL = 0;             // any write to current clears it
    SysTick -> CTRL = 0x00000005;  // enable systick, 3MHz, No
                                   //Interrupts


    P2SEL0 &= ~BIT3;
    P2SEL1 &= ~BIT3;  //  configure P2.3 GPIO
    P2DIR |= BIT3;   //  make P2.3 output
    P2OUT |= BIT3;   //set P2.3 to 1

}

