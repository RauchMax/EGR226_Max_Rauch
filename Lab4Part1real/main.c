/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 02/14/2021
* Project: Lab Four Part One
* File: Main.c
* Description: This program makes the RGB LED on the MSP432
* cycle to the next color with the push of the pushbutton switch.
* This program will not cycle through the colors if the button is
* held down, and if the MSP432 is restarted it will start with red.
**************************************************************************************/

#include "msp.h"

void delayMs(int n);

int main(void)
{
    int counter =1;


    P1SEL0 &= ~0x12;
    P1SEL1 &= ~0x12;  // 1) configure P1.4 and P1.1 as GPIO
    P1DIR &= ~0x12;  // 2) make P1.4 and P1.1 inputs
    P1REN |= 0x12;  // 3) enable pull resistors on P1.4 and P1.1
    P1OUT |= 0x12; // P1.4 and P1.1 are pull-up


    P2SEL1 &= ~7;
    P2SEL0 &= ~7;
    P2DIR |= 7;
    P2OUT &= ~7;

    while(1) {

        if ((P1IN & BIT1) == 0x00) //check of button pushed
        { __delay_cycles(3000); //pause for 10 m-sec for switch bounce
        if ((P1IN & BIT1) == 0x00) //check of button is still pushed
        {
            if ((P1IN & BIT1) == 0x00) //check of button pushed
                    { __delay_cycles(3000); //pause for 10 m-sec for switch bounce
                    if ((P1IN & BIT1) == 0x00) //check of button is still pushed
                    {
                        while((P1IN & BIT1) == 0x00);
                    }
                    }
        if(counter ==3){
            counter =4;
        }
        if(counter > 4){
            counter = 1;
        }
        P2->OUT = counter & 7;
        delayMs(500);
        counter++;
        }
    }
}
}
void delayMs(int n){
    int i,j;

    for (j=0; j<n; j++)
        for(i=250; i >0; i--);
}
