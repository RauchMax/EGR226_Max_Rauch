/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 02/23/2021
* Project: Lab Five Part Two
* File: Main.c
* Description: This program makes a circuit of green, yellow and red LEDs
* flash a color for one second then switch to the next color while
* holding an external pushbutton switch. This program will continuously cycle
* through the colors while the button is held down. If the button is released,
* that color will stay lit, and if the MSP432 is restarted it will start with green.
**************************************************************************************/

#include "msp.h"

   int counter =1;    //setting counter = to 1 so the program starts with green

   void init(void);      // prototyping the initialization function
   void forward(void);   // prototyping the forward function
   void SysTick_delay (uint16_t delay);   // prototyping the systick function


int main(void)
{

    init();      //calling the initialization function

    while(1) {

        forward();   //calling the forward function
}
}

void init(void){

                           //initialization of systic timer
          SysTick -> CTRL = 0; // disable SysTick During step
          SysTick -> LOAD = 0x00FFFFFF; // max reload value
          SysTick -> VAL = 0; // any write to current clears it
          SysTick -> CTRL = 0x00000005; // enable systic, 3MHz, No Interrupts

          P3SEL0 &= ~BIT0;
          P3SEL1 &= ~BIT0;  //  configure P3.0  GPIO
          P3DIR &= ~BIT0;   //  make P3.0 input
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
      if(counter ==3){   // changing counter to 4 so only the red LED will turn on
          counter =4;
      }
      if(counter > 4){   // if counter get past 4 reset to loop through green, yellow, red
          counter = 1;
      }                        //setting the color of the LED based on the counter
      P4->OUT = counter & 7;   //while counter=1 LED=green,,counter=2 LED=yellow,,counter=4 LED=red
      //__delay_cycles(3000000);
      SysTick_delay (1000);        //delaying with SysTick for 1 second so each color is on for 1 second
      if ((P3IN & BIT0) == 0x00) //check of button pushed
               { __delay_cycles(3000);    //pause for switch bounce
              if ((P3IN & BIT0) == 0x00) //check of button is still pushed
              {
      counter++;     // incrementing the counter
              }
      }
  }
  }

}


void SysTick_delay (uint16_t delay)
{ // Systick delay function
SysTick -> LOAD = ((delay * 3000) - 1); //delay for 1 msecond per delay value
SysTick -> VAL = 0; // any write to CVR clears it
while ( (SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
}

