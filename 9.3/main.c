/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 03/18/2021
* Project: Lab Nine Part Three
* File: Main.c
* Description: This program uses GPIO interrupts to increment the seven segment
* LED. If button 1 is pressed the LED increases by one, if button 2 is pressed
* the LED is decremented by one. If the LED is at 9 and is incremented it goes
* to 0. If the LED is at 0 and is decremented it goes to 9.
**************************************************************************************/

#include <msp.h>

void SysTick_Init (void);
void pin_init(void);
void count(void);
void SetupPort5Interrupts (void);
void SysTick_delay (uint16_t delay);
void SetupLEDs(void);

volatile int intervalCnt =0;    //making a volatile variable as the counter


int main(void)
{

WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Halting the Watchdog

SetupLEDs();              //Sets up the LED as outputs
pin_init();                 //initializing the pins for the 7 segment LED
SetupPort5Interrupts ();  //Initializes buttons that interrupt program
NVIC->ISER[1] = 1 << ((PORT5_IRQn) & 31);  // Enable Port 5 interrupt on the NVIC
__enable_interrupt ( );                   //Enable all interrupts that are turned on
SysTick_Init ( );                  // initialize SysTick without interrupt
__enable_irq ( );                   // enable global interrupts


while (1)
{
    count();                 // calling the count function
}
}


/****| SetupLEDs Function | *****************************************
* Brief: This function initializes red LED built into the MSP432.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void SetupLEDs(void) {

    P1->DIR = BIT0;
}



/****| SetupPort5Interrupts Function | *****************************************
* Brief: This function initializes P5.1, and P5.4 as input
* whith the pull up resistors. It also sets them so the interrupts
* is triggered when the pin goes from high to low.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void SetupPort5Interrupts (void) {
P5->SEL0 &=~ BIT1;                        // Setup the P5.1 on the Launchpad as Input, Pull Up Resistor
P5->SEL1 &=~ BIT1;
P5->DIR &=~ BIT1;
P5->REN |= BIT1;
P5->OUT |= BIT1;                        //Input, Pull Up Resistor
P5->IES |= BIT1;                        //Set pin interrupt to trigger from high to low (starts high due to pull up resistor)
P5->IE |= BIT1;                         //Set interrupt on for P5.1
P5->SEL0 &=~ BIT4;                       // Setup the P5.4 on the Launchpad as Input, Pull Up Resistor
P5->SEL1 &=~ BIT4;
P5->DIR &=~ BIT4;
P5->REN |= BIT4;
P5->OUT |= BIT4;                         //Input, Pull Up Resistor
P5->IES |= BIT4;                         //Set pin interrupt to trigger from high to low (starts high due to pull up resistor)
P5->IE |= BIT4;                          //Set interrupt on for P5.4
P5->IFG = 0;                             //Clear all Port 5 interrupt flags
}


/****| Pin_init Function | *****************************************
* Brief: This function initializes all of the pins that are
* hooked up to the seven segment LED.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void pin_init(void){
    P6->SEL0 &=~ (BIT6 | BIT7); // Set pin 4 & 5 as GPIO
    P6->SEL1 &=~ (BIT6 | BIT7); // Set pin 4 & 5 as GPIO
    P6->DIR |= (BIT6 | BIT7); // Set pin 4 & 5 as OUTPUTS
    P6->OUT &=~ (BIT6 | BIT7);

    P3->SEL0 &=~ (BIT0); // Set pin 4 & 5 as GPIO
    P3->SEL1 &=~ (BIT0); // Set pin 4 & 5 as GPIO
    P3->DIR |= (BIT0); // Set pin 4 & 5 as OUTPUTS
    P3->OUT &=~ (BIT0);

    P5->SEL0 &=~ (BIT0 | BIT7); // Set pin 4 & 5 as GPIO
    P5->SEL1 &=~ (BIT0 | BIT7); // Set pin 4 & 5 as GPIO
    P5->DIR |= (BIT0 | BIT7); // Set pin 4 & 5 as OUTPUTS
    P5->OUT &=~ (BIT0 | BIT7);

    P1->SEL0 &=~ (BIT6 | BIT7); // Set pin 4 & 5 as GPIO
    P1->SEL1 &=~ (BIT6 | BIT7); // Set pin 4 & 5 as GPIO
    P1->DIR |= (BIT6 | BIT7); // Set pin 4 & 5 as OUTPUTS
    P1->OUT &=~ (BIT6 | BIT7);
}



/****| Systick_initFunction | *****************************************
* Brief: This function initializes the SysTick timer without interrupts.
* It also sets the reload value to its maximum value.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void SysTick_Init (void) { //initialization of systic timer
SysTick -> CTRL = 0; // disable SysTick During step
SysTick -> LOAD = 0x00FFFFFF; // reload value for 0.5s interrupts
SysTick -> VAL = 0; // any write to current clears it
SysTick -> CTRL = 0x00000005; // enable SysTick, 3MHz, Interrupts
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



/****| PORT5_IRQHandler Handler | *****************************************
* Brief: This handler checks to see which button caused the interrupt,
* then it checks to see of the button is pressed, pauses and checks
* again to debounce the button. It then sits in a wile statement if
* the button is being held. If the signal was from button 1 it increments
* the count by one, if the signal was from button 2 it decrements the count
* by one. It also toggles the LED every time a button is pressed for a visual
*  of the interrupt.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/


void PORT5_IRQHandler(void) {
if(P5->IFG & BIT1){
    if((P5IN & BIT1) == 0x00){                      //If P5.1 had an interrupt (comparing the status with the BIT)
        SysTick_delay (50);
        if((P5IN & BIT1) == 0x00){
            if((P5IN & BIT1) == 0x00){                      //If P5.1 had an interrupt (comparing the status with the BIT)
                    SysTick_delay (50);
                    if((P5IN & BIT1) == 0x00){
                    while((P5IN & BIT1) == 0x00); // if it is being held just wait here

                    }
                    }

            P1->OUT ^= BIT0;
            intervalCnt++;


}
}
}
if(P5->IFG & BIT4){                       //If P5.4 had an interrupt (comparing the status with the BIT)
    if((P5IN & BIT4) == 0x00){                      //If P5.1 had an interrupt (comparing the status with the BIT)
        SysTick_delay (50);
        if((P5IN & BIT4) == 0x00){
            if((P5IN & BIT4) == 0x00){                      //If P5.1 had an interrupt (comparing the status with the BIT)
                      SysTick_delay (50);
                      if((P5IN & BIT4) == 0x00){
                       while((P5IN & BIT4) == 0x00); // if it is being held just wait here

                               }
                               }

            P1->OUT ^= BIT0;
            intervalCnt--;

}
}
}


P5->IFG = 0;                              //Clear all flags
}



/****| Count Function | *****************************************
* Brief: This function checks the value of the volatile counter
* and then turns on the correct pins to set the seven segment
* LED to display the value of the counter. If the counter gets
* above nine it resets it so it will start at 0.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void count(void){

    if (intervalCnt ==  0){    //displaying 0 on 7 segment LED
        P6->OUT &= ~BIT7;  //G off
        P5->OUT |= BIT7;   //A on
        P3->OUT |= BIT0;   //B on
        P1->OUT |= BIT6;   //C on
        P1->OUT |= BIT7;   //D on
        P5->OUT |= BIT0;   //E on
        P6->OUT |= BIT6;   //F on
    }

    if (intervalCnt ==  1){   //displaying 1 on 7 segment LED
        P6->OUT &= ~BIT7;  //G off
        P5->OUT &= ~BIT7;  //A off
        P3->OUT |= BIT0;   //B on
        P1->OUT |= BIT6;   //C on
        P1->OUT &= ~BIT7;  //D off
        P5->OUT &= ~BIT0;  //E off
        P6->OUT &= ~BIT6;  //F off
       }

    if (intervalCnt ==  2){   //displaying 2 on 7 segment LED
        P6->OUT |= BIT7;   //G on
        P5->OUT |= BIT7;   //A on
        P3->OUT |= BIT0;   //B on
        P1->OUT &= ~BIT6;  //C off
        P1->OUT |= BIT7;   //D on
        P5->OUT |= BIT0;   //E on
        P6->OUT &= ~BIT6;  //F off
       }

    if (intervalCnt ==  3){    //displaying 3 on 7 segment LED
        P6->OUT |= BIT7;   //G on
        P5->OUT |= BIT7;   //A on
        P3->OUT |= BIT0;   //B on
        P1->OUT |= BIT6;   //C on
        P1->OUT |= BIT7;   //D on
        P5->OUT &= ~BIT0;  //E off
        P6->OUT &= ~BIT6;  //F off
       }

    if (intervalCnt ==  4){   //displaying 4 on 7 segment LED
        P6->OUT |= BIT7;   //G on
        P5->OUT &= ~BIT7;  //A off
        P3->OUT |= BIT0;   //B on
        P1->OUT |= BIT6;   //C on
        P1->OUT &= ~BIT7;  //D off
        P5->OUT &= ~BIT0;  //E off
        P6->OUT |= BIT6;   //F on
       }

    if (intervalCnt ==  5){    //displaying 5 on 7 segment LED
        P6->OUT |= BIT7;   //G on
        P5->OUT |= BIT7;   //A on
        P3->OUT &= ~BIT0;  //B off
        P1->OUT |= BIT6;   //C on
        P1->OUT |= BIT7;   //D on
        P5->OUT &= ~BIT0;  //E off
        P6->OUT |= BIT6;   //F on
       }

    if (intervalCnt ==  6){   //displaying 6 on 7 segment LED
        P6->OUT |= BIT7;   //G on
        P5->OUT |= BIT7;   //A on
        P3->OUT &= ~BIT0;  //B off
        P1->OUT |= BIT6;   //C on
        P1->OUT |= BIT7;   //D on
        P5->OUT |= BIT0;   //E on
        P6->OUT |= BIT6;   //F on
       }

    if (intervalCnt ==  7){   //displaying 7 on 7 segment LED
        P6->OUT &= ~BIT7;  //G off
        P5->OUT |= BIT7;   //A on
        P3->OUT |= BIT0;   //B on
        P1->OUT |= BIT6;   //C on
        P1->OUT &= ~BIT7;  //D off
        P5->OUT &= ~BIT0;  //E off
        P6->OUT &= ~BIT6;  //F off
       }

    if (intervalCnt ==  8){    //displaying 8 on 7 segment LED
        P6->OUT |= BIT7;   //G on
        P5->OUT |= BIT7;   //A on
        P3->OUT |= BIT0;   //B on
        P1->OUT |= BIT6;   //C on
        P1->OUT |= BIT7;   //D on
        P5->OUT |= BIT0;   //E on
        P6->OUT |= BIT6;   //F on
       }

    if (intervalCnt ==  9){    //displaying 9 on 7 segment LED
        P6->OUT |= BIT7;   //G on
        P5->OUT |= BIT7;   //A on
        P3->OUT |= BIT0;   //B on
        P1->OUT |= BIT6;   //C on
        P1->OUT |= BIT7;   //D on
        P5->OUT &= ~BIT0;  //E off
        P6->OUT |= BIT6;   //F on
       }

    if (intervalCnt > 9){  //resetting the counter
        intervalCnt = 0;
       }

    if (intervalCnt < 0){    //resetting the counter
            intervalCnt = 9;
           }

}
