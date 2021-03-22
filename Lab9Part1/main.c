/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 03/18/2021
* Project: Lab Nine Part One
* File: Main.c
* Description: This program uses timer A to create a PWM signal that is used
* to slow down or speed up a dc motor. The input for this program is from taken
* from three external pushbuttons. Pushing button one increases the motors speed
* by 10%. Pushing button two decreases the motors speed by 10%, and pushing the
* third button turns the motor off.
**************************************************************************************/

#include "msp.h"


void SetupLEDs(void);
void SetupPort5Interrupts (void);
void Sys_init (void);
void SysTick_delay (uint16_t delay);
void timer_init(void);

volatile int DC = 10000;

void main(void)
{
WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer


SetupLEDs ( );                              //Sets up the LED as outputs
SetupPort5Interrupts ( );                  //Initializes buttons that interrupt program
NVIC->ISER[1] = 1 << ((PORT5_IRQn) & 31);  // Enable Port 5 interrupt on the NVIC
__enable_interrupt ( );                   //Enable all interrupts that are turned on

int check = DC;                        // making a variable thats value can be checked in the debug

Sys_init ();                        //initializing systick
timer_init();                       //initializing timer A
TIMER_A2->CCR[1] = DC;             //setting timer A duty cycle to 100%

while (1)
{
    check = DC;                   //setting the check variable = to the global variable that is updated in the handler
                                  // so i can make sure it is moving by 10% in debug window.
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

    // Configure GPIO for PWM output
    P5->SEL0 |= BIT6;
    P5->SEL1 &= ~(BIT6);
    P5->DIR |= BIT6;    // set P5.6 to output

    TIMER_A2->CCR[0] = (10000 - 1);           // PWM Period (# cycles of clock)
    TIMER_A2->CCTL[1] = 0b0000000001110000;  // CCR1 reset/set mode 7
    TIMER_A2->CTL = 0b0000001000010100;       // SMCLK, Up Mode, clear TAR to start
}



/****| Sys_initFunction | *****************************************
* Brief: This function initializes the SysTick timer without interrupts.
* It also sets the reload value to its maximum value.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void Sys_init (void)
{
                                   //initialization of systic timer
             SysTick -> CTRL = 0; // disable SysTick During step
             SysTick -> LOAD = 0x00FFFFFF; // max reload value
             SysTick -> VAL = 0; // any write to current clears it
             SysTick -> CTRL = 0x00000005; // enable systic, 3MHz, No Interrupts


}


/****| SetupLEDs Function | *****************************************
* Brief: This function initializes red LED built into the MSP432.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void SetupLEDs(void) {

    P1->DIR = BIT0;      //setting direction to output
    P1->OUT |= BIT0;    //turning the LED on
}



/****| SetupPort5Interrupts Function | *****************************************
* Brief: This function initializes P5.1, P5.2, and P5.4 as input
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
P5->SEL0 &=~ BIT2;                       // Setup the P5.2 on the Launchpad as Input, Pull Up Resistor
P5->SEL1 &=~ BIT2;
P5->DIR &=~ BIT2;
P5->REN |= BIT2;
P5->OUT |= BIT2;                         //Input, Pull Up Resistor
P5->IES |= BIT2;                         //Set pin interrupt to trigger from high to low (starts high due to pull up resistor)
P5->IE |= BIT2;                          //Set interrupt on for P5.2
P5->IFG = 0;                             //Clear all Port 5 interrupt flags
}



/****| PORT5_IRQHandler Handler | *****************************************
* Brief: This handler checks to see which button caused the interrupt,
* then it checks to see of the button is pressed, pauses and checks
* again to debounce the button. It then sits in a wile statement if
* the button is being held. If the signal was from button 1 it increments
* DC by 10%, if the signal was from button 2 it decrements the DC by
* 10% and if the signal was from button 3 it turns the motor off. It also
* toggles the LED everytime a button is pressed for visual of the interrupt.
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
                    while((P5IN & BIT1) == 0x00);          // if it is being held just wait here

                    }
                    }

          if(DC<=0){
              DC = 11000;                   // if DC is off reset so next click it 100%
          }
          P1->OUT ^= BIT0;                   //toggling LED
          DC = DC - 1000;                    //incrementing DC by 10%
          TIMER_A2->CCR[1] = DC;             //Changing timer A duty cycle

}
}
}
if(P5->IFG & BIT4){                       //If P5.4 had an interrupt (comparing the status with the BIT)
    if((P5IN & BIT4) == 0x00){                      //If P5.4 had an interrupt (comparing the status with the BIT)
        SysTick_delay (50);
        if((P5IN & BIT4) == 0x00){
            if((P5IN & BIT4) == 0x00){                      //If P5.4 had an interrupt (comparing the status with the BIT)
                     SysTick_delay (50);
                     if((P5IN & BIT4) == 0x00){
                     while((P5IN & BIT4) == 0x00);      // if it is being held just wait here

                       }
                       }

        if(DC >= 10000){                  // if DC is at 100% rest so next is off
            DC = -1000;
        }
        P1->OUT ^= BIT0;                 //toggle LED
        DC = DC + 1000;                  //Decrementing DC by 10%
        TIMER_A2->CCR[1] = DC;           //Changing timer A duty cycle

}
}
}

if(P5->IFG & BIT2){
    if((P5IN & BIT2) == 0x00){                      //If P5.2 had an interrupt (comparing the status with the BIT)
          SysTick_delay (50);
            if((P5IN & BIT2) == 0x00){
                TIMER_A2->CCR[1] = 10000;          //turning timer A duty cycle to 0%
            }
            }
}

P5->IFG = 0;                              //Clear all flags
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
    SysTick -> LOAD = ((delay * 3000) - 1);  //delay for 1 msecond per delay value
    SysTick -> VAL = 0;                         // any write to CVR clears it
    while ( (SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
    }
