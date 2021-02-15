/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 02/14/2021
* Project: Lab Four Part Two
* File: Main.c
* Description: This program makes the RGB LED on the MSP432
* flash a color for one second then switch to the next color while
* holding pushbutton switch. This program will continuously cycle through
* the colors while the button is held down. If the button is released, that
* color will stay lit, and if the MSP432 is restarted it will start with red.
**************************************************************************************/

#include "msp.h"



int main(void)
{
    int counter =1;


    P1SEL0 &= ~0x12;
    P1SEL1 &= ~0x12;  // 1) configure P1.4 and P1.1 as GPIO
    P1DIR &= ~0x12;  // 2) make P1.4 and P1.1 inputs
    P1REN |= 0x12;  // 3) enable pull resistors on P1.4 and P1.1
    P1OUT |= 0x12; // P1.4 and P1.1 are pull-up


    P2SEL1 &= ~7;   // configure P2.0 through P2.2 as GPIO
    P2SEL0 &= ~7;   // make P2.0 through P2.2 inputs
    P2DIR |= 7;     // setting direction as output
    P2OUT &= ~7;    //  setting all LEDs to off

    while(1) {

        if ((P1IN & BIT1) == 0x00) //check of button pushed
        { __delay_cycles(3000); //pause for switch bounce
        if ((P1IN & BIT1) == 0x00) //check of button is still pushed
        {
        if(counter ==3){   // changing counter to 4 so only the blue LED will turn on
            counter =4;
        }
        if(counter > 4){   // if counter get past 4 reset to loop through Red,green and blue
            counter = 1;
        }                        //setting the color of the LED based on the counter
        P2->OUT = counter & 7;   //while counter=1 LED=red,,counter=2 LED=green,,counter=4 LED=blue
        __delay_cycles(3000000);  //delaying for 1 second so each color is on for 1 second
        counter++;     // incrementing the counter
        }
    }
}
}

