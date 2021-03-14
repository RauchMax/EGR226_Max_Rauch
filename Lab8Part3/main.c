#include "msp.h"
#include <stdio.h>

void keypad_init (void);                // prototype for GPIO initialization
uint8_t  Keypad_Read(void);              // prototype for keypad scan function
void Print_Keys (void);                 // Print Key pressed
void changeSpeed(void);
void SysTick_delay (uint16_t delay);   // prototyping the systick function
uint8_t num, pressed;


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    // Configure GPIO for PWM output
     //P5->DIR |= BIT6;    // P2.4 set TA0.1
     P5->SEL0 |= BIT6;
     P5->SEL1 &= ~(BIT6);
     P5->DIR |= BIT6;    // P2.4 set TA0.1

    //int DC,input;
     keypad_init ( );
    //pwm_init(DC);


    TIMER_A2->CCR[0] = (10000 - 1);
    TIMER_A2->CCTL[1] = 0b0000000001110000;
    TIMER_A2->CTL = 0b0000001000010100;



/*
    while(1){
        DC = input*100;
                TIMER_A2->CCR[1] = DC;           // CCR1 PWM duty cycle
    }

    */

    while ( 1 )
        {
        pressed =  Keypad_Read(); // Call Function to read Keypad
        if ( pressed )          //checking button state
        Print_Keys ( );
        changeSpeed();
        SysTick_delay (10);    // 10ms delay through the loop before reading keypad again
        //__delay_cycles(30000);
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
             P4SEL1 &= ~0x0F;  //  configure P4.0 -4.3  GPIO
             P4DIR &= ~0x0F;   //  make P4.0 -4.3 input
             P4REN |= 0x0F;    //  enable pull resistors on P4.0 -4.3
             P4OUT |= 0x0F;   // P4.0 -4.3 are a pull-up

             P4SEL0 &= ~0x70;
             P4SEL1 &= ~0x70;  //  configure P4.4 -4.6  GPIO
             P4DIR  &= ~0x70;   //  make P4.0 -4.3 input



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


void changeSpeed(void){
    int DC;


        if(num == 1){
           DC = 9000;
        }

        if(num == 2){
           DC = 8000;
        }

        if(num == 3){
           DC = 7000;
        }

        if(num == 4){
           DC = 6000;
        }

        if(num == 5){
            DC = 5000;
        }

        if(num == 6){
            DC = 4000;
        }

        if(num == 7){
            DC = 3000;
        }

        if(num == 8){
            DC = 2000;
        }

        if(num == 9){
            DC = 1000;
        }
        if(num == 11){
            DC = 10000;
        }

        if(num == 12){
            DC = 10000;
        }

        if(num == 10){
            DC = 10000;
        }



    TIMER_A2->CCR[1] = DC;           // CCR1 PWM duty cycle

}



void SysTick_delay (uint16_t delay)
{ // Systick delay function
SysTick -> LOAD = ((delay * 3000) - 1); //delay for 1 msecond per delay value
SysTick -> VAL = 0; // any write to CVR clears it
while ( (SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
}
