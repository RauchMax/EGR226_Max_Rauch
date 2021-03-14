#include "msp.h"


void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	// Configure GPIO for PWM output
     P5->SEL0 |= BIT6;
     P5->SEL1 &= ~(BIT6);
     P5->DIR |= BIT6;    // P2.4 set TA0.1

	int DC,input;


	TIMER_A2->CCR[0] = (10000 - 1);
	TIMER_A2->CCTL[1] = 0b0000000001110000;
	TIMER_A2->CTL = 0b0000001000010100;




	while(1){
	    DC = input*100;
	            TIMER_A2->CCR[1] = DC;           // CCR1 PWM duty cycle
	}
}

