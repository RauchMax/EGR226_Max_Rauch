#include "msp.h"

int DebounceSwitch1(void);
void Port1_Initb(void);
/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer


	Port1_Initb();

	DebounceSwitch1();


}



int DebounceSwitch1(void)
{
int pin_Value = 0; //initialize variable as low
if ((P1IN & BIT1) == 0x00) //check of button pushed
{ __delay_cycles(45000); //pause for 15 m-sec for switch bounce
if ((P1IN & 0x02) == 0x00) //check of button is still pushed
pin_Value = 1;
}
return pin_Value; //return 1 if pushed- 0 if not pushed
}

void Port1_Initb(void)
{
P1SEL0 &= ~0x12;
P1SEL1 &= ~0x12;  // 1) configure P1.4 and P1.1 as GPIO
P1DIR &= ~0x12;  // 2) make P1.4 and P1.1 inputs
P1REN |= 0x12;  // 3) enable pull resistors on P1.4 and P1.1
P1OUT |= 0x12; // P1.4 and P1.1 are pull-up
}

