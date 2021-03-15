/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 03/12/2021
* Project: Lab Eight Part Three
* File: Main.c
* Description: This program uses timer A to create a PWM signal that is used
* to slow down or speed up a dc motor. The input for this program is from a
* standard twelve key keypad. Pressing the 1 key will set the duty cycle to
* .1, pressing the 2 will make the DC .2. This is true for 1-9, after that
* pressing a 0 will turn the motor off or pressing * or # will set the motor
* to full speed.
**************************************************************************************/

#include "msp.h"
#include <stdio.h>

void keypad_init (void);                // prototype for GPIO initialization
uint8_t  Keypad_Read(void);              // prototype for keypad scan function
void changeSpeed(void);
void timer_init(void);
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


     keypad_init ( );
     timer_init();


    while ( 1 )
        {
        pressed =  Keypad_Read(); // Call Function to read Keypad
        if ( pressed )          //checking button state
        changeSpeed();
        SysTick_delay (10);    // 10ms delay through the loop before reading keypad again

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



/****| keypad_initFunction | *****************************************
* Brief: This function initializes the keypad pins and the
* SysTick timer.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

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


/****| keypad_readFunction | *****************************************
* Brief: This function reads the keypad and sets the global
* variable num to the number that coincides with a 4x3 matrix.
* It also returns a 0 if nothing was pressed or a 1 if a key
* was pressed.
* param: N/A
* data: This is a void function so it has no input, but it
* sets a global variable and returns a value of 1 or 0 which
* is used to tell if a button has been pressed.
* return:N/A
*************************************************************/

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




/****| changespeedFunction | *****************************************
* Brief: This function takes the input from the keypad and uses
* it to set the duty cycle variable to the required duty cycle
* for that specific key. Then it changes timer A2 CCR1 to that
* duty cycle.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

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
            DC = 0;
        }

        if(num == 10){
            DC = 0;
        }



    TIMER_A2->CCR[1] = DC;           // CCR1 PWM duty cycle

}

/****| SysTick_delayFunction | *****************************************
* Brief: This function delays the program for 1 millisecond
* per value of the variable.
* param: N/A
* data: This function accepts one variable called delay that
* is used to set the load register.
* return:N/A
*************************************************************/

void SysTick_delay (uint16_t delay)
{ // Systick delay function
SysTick -> LOAD = ((delay * 3000) - 1); //delay for 1 msecond per delay value
SysTick -> VAL = 0; // any write to CVR clears it
while ( (SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
}

