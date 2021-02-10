/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 02/3/2021
* Project: Lab Three Part Three
* File: Main.c
* Description: This program makes the red LED on the MSP432
* flash at a variable rate. The user can decide the rate.
**************************************************************************************/


#include "msp.h"


/**
 * main.c
 */
void main(void)
{
    //stop watchdog timer (WDT is uded to break you out if unwanted loops)

	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	//configure variable for loop maintenance
	P1->DIR = BIT0;

	//Temporary variable for for loop maintenance
	int i;
	while(1){
	    P1->OUT ^= BIT0;      //toggle LED status
	    for(i=2000; i>0; i--);  //Crude delay
	}

}
