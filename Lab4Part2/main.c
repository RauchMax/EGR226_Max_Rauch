#include "msp.h"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	P2->SEL1 &= ~7; // configure P2.2-P2.0 as simple I/O
	P2->SEL0 &= ~7;
	P2->DIR |= 7; // P2.2-2.0 set as output
	P2->OUT |= 7; // turn all three LEDs on

	while (1)
	{
	P2->OUT ^= 7; // toggle P2.2-P2.0 all three LEDs
	//delayMs(500);
	__delay_cycles(500);
	}

}
