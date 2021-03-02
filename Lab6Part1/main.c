#include "msp.h"
#include <stdio.h>

void keypad_init (void); // prototype for GPIO initialization
uint8_t  Keypad_Read(void); // prototype for keypad scan subroutine
void Print_Keys (void); // Print Key pressed
void SysTick_delay (uint16_t delay);   // prototyping the systick function
uint8_t num, pressed;


void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	keypad_init ( );

	while ( 1 )
	{
	pressed =  Keypad_Read(); // Call Function to read Keypad
	if ( pressed )
	Print_Keys ( );
	__delay_cycles(30000); // 10ms delay through the loop before reading keypad again
	}


}


void keypad_init (void)
{
                            //initialization of systic timer
             SysTick -> CTRL = 0; // disable SysTick During step
             SysTick -> LOAD = 0x00FFFFFF; // max reload value
             SysTick -> VAL = 0; // any write to current clears it
             SysTick -> CTRL = 0x00000005; // enable systic, 3MHz, No Interrupts

             P4SEL0 &= ~0x0F;
             P4SEL1 &= ~0x0F;  //  configure P4.0 -4.6  GPIO
             P4DIR &= ~0x0F;   //  make P3.0 input
             P4REN |= 0x0F;    //  enable pull resistors on P3.0
             P4OUT |= 0x0F;   // P3.0 is a pull-up

             P4SEL0 &= ~0x70;
             P4SEL1 &= ~0x70;  //  configure P3.0  GPIO
             P4DIR  &= ~0x70;   //  make P3.0 input



}


uint8_t  Keypad_Read(void)
{
uint8_t col, row;
for ( col = 0; col < 3; col++ )
{

P4->DIR = 0x00; // Set Columns to inputs
P4->DIR |= BIT ( 4 + col ); // Set column 3 to output
P4->OUT &=~ BIT ( 4 + col ); // Set column 3 to LOW

SysTick_delay (10); // Delay the while loop
row = P4->IN & 0x0F; // read all rows
while ( !(P4IN & BIT0) | !(P4IN & BIT1) | !( P4IN & BIT2) | !( P4IN & BIT3) );
if (row != 0x0F) break; // if one of the input is low, some key is pressed.
}

P2->DIR = 0x00;           // Set Columns to inputs

if ( col == 3)
return 0;


if (row == 0x0E) num = col + 1; // key in row 0
if (row == 0x0D) num = 3 + col +1; // key in row 1
if (row == 0x0B) num = 6 + col +1; // key in row 2
if (row == 0x07) num = 9 + col+1; // key in row 3
return 1;
}

//We were given the read keypad code in lecture.


void Print_Keys (void)
{
        if(num < 10 ){           //if its 1-9 just print it
            printf("%d\n", num);
    }

    if(num == 10){             //if its 10 print the *
        printf("*\n");
    }
    if(num == 11){            // if its 11 print 0
        printf("0\n");
    }
    if(num == 12){            // if its 12 print #
            printf("#\n");
    }

}


    void SysTick_delay (uint16_t delay)
    { // Systick delay function
    SysTick -> LOAD = ((delay * 3000) - 1); //delay for 1 msecond per delay value
    SysTick -> VAL = 0; // any write to CVR clears it
    while ( (SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
    }

