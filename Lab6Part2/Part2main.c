/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 03/2/2021
* Project: Lab Six Part Two
* File: Main.c
* Description: This program reads a standard twelve key keypad
* and prints a four digit code to the screen with the press of
* the pound key. It does not count the * as a valid digit. If less
* than four valid digits are entered it asks for four digits. It
* should be able to accept many digits and just print the last four.
*  It will not print multiple numbers if the button is held down.
**************************************************************************************/

#include "msp.h"
#include <stdio.h>

void getcode (void);
void keypad_init (void); // prototype for GPIO initialization
uint8_t  Keypad_Read(void); // prototype for keypad scan subroutine
void Print_Keys (void); // Print Key pressed
void SysTick_delay (uint16_t delay);   // prototyping the systick function
uint8_t num, pressed;
int Code[50];
//int counter = 0;
int n=0;


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    keypad_init ( );                            //initializing the keypad

    printf("Please enter a four digit code.\n");



    while ( 1 )
    {
        getcode();                  //calling function to get the code
   }


}



void getcode (void){
    pressed =  Keypad_Read(); // Call Function to read Keypad
        if ( pressed ){
           // if(counter == 4){
                   // counter =0;
               // }
            if(num == 12){                          //checking for the pound key to be pressed
                if(n<4){
                    printf("Please enter a 4 digit code\n");    //if less than 4 inputs manualy set all to 0 and ask for reentry
                    Code[n-4] = 0;
                    Code[n-3] = 0;
                    Code[n-2] = 0;
                    Code[n-1] = 0;

                }
                          printf("Code = %d %d %d %d\n", Code[n-4], Code[n-3], Code[n-2], Code[n-1]);   //print the last 4 digits
                          n=0;                              //reset the count to 0 after sucsessful print
                  }
            if(num<10){
                Code[n] = num;   //if 1-9 are pressed set it equal to that space in the array
                //counter ++;
                n++;              // increment the counter
            }                     // 10 and 12 are ignored here because those aren't valid digits
            if(num == 11){      // if 0 is pressed set that space in the array = to 0
                Code[n] = 0;
                //counter ++;
                n++;            // increment the counter
            }
        Print_Keys ( );
        SysTick_delay (10);      // 10ms delay through the loop before reading keypad again
        //__delay_cycles(30000);
        //if(counter == 4){
           // counter =0;
       // }
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
             P4REN |= 0x0F;    //  enable pull resistors onP4.0 -4.3
             P4OUT |= 0x0F;   // P4.0 -4.3 is a pull-up

             P4SEL0 &= ~0x70;
             P4SEL1 &= ~0x70;  //  configure P4.4 -4.6  GPIO
             P4DIR  &= ~0x70;   //  make P4.4 -4.6  input



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
    if(num < 10 ){
               printf("%d\n", num);  //if its 1-9 just print it
       }

       if(num == 10){
           printf("*\n");     //if its 10 print the *
       }
       if(num == 11){
           printf("0\n");      // if its 11 print 0
       }
       if(num == 12){
               printf("#\n");     // if its 12 print #
       }


}


    void SysTick_delay (uint16_t delay)
    { // Systick delay function
    SysTick -> LOAD = ((delay * 3000) - 1); //delay for 1 msecond per delay value
    SysTick -> VAL = 0; // any write to CVR clears it
    while ( (SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
    }

