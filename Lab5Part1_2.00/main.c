/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 02/23/2021
* Project: Lab Five Part One
* File: Main.c
* Description: This program makes a circuit of green, yellow and red
* LEDs cycle to the next color with the push of an external pushbutton switch.
* This program will not cycle through the colors if the button is
* held down, and if the MSP432 is restarted it will start with green.
**************************************************************************************/

#include "msp.h"

int counter =1;   //setting counter = to 1 so the program starts with green

void init(void);         // prototyping the initialization function
void forward(void);    // prototyping the forward function

int main(void)
{

init();       //calling the initialization function


    while(1) {

        forward();   //calling the forward function
}
}

void init(void){
       P3SEL0 &= ~BIT0;
       P3SEL1 &= ~BIT0;  //  configure P3.0  GPIO
       P3DIR &= ~BIT0;   //  make P3.0 an input
       P3REN |= BIT0;    //  enable pull resistors on P3.0
       P3OUT |= BIT0;   // P3.0 is a pull-up


       P4SEL1 &= ~7;   // configure P4.0 through P4.2 as GPIO
       P4SEL0 &= ~7;   // make P4.0 through P4.2 inputs
       P4DIR |= 7;     // setting direction as output
       P4OUT &= ~7;   //  setting all LEDs to off
}


void forward(void){
         if ((P3IN & BIT0) == 0x00) //check of button pushed
            { __delay_cycles(3000);    //pause for switch bounce
            if ((P3IN & BIT0) == 0x00) //check of button is still pushed
            {
                if ((P3IN & BIT0) == 0x00) //check of button pushed again to see if it is being held down
                        { __delay_cycles(3000);    //pause for switch bounce
                        if ((P3IN & BIT0) == 0x00) //check of button is still pushed
                        {
                            while((P3IN & BIT0) == 0x00); // if it is being held just wait here
                        }
                        }
            if(counter ==3){  // changing counter to 4 so only the red LED will turn on
                counter =4;
            }
            if(counter > 4){    // if counter get past 4 reset to loop through green, yellow, red
                counter = 1;
            }                        //setting the color of the LED based on the counter
            P4->OUT = counter & 7;  //while counter=1 LED=green,,counter=2 LED=yellow,,counter=4 LED=red
            counter++;         // incrementing the counter
            }
        }

}
