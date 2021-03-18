#include "msp.h"


void SetupLEDs(void);
void SetupPort1Interrupts (void);
void Sys_init (void);
void SysTick_delay (uint16_t delay);
void timer_init(void);

void main(void)
{
WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer
SetupLEDs ( );                              //Sets up the LEDs as outputs
SetupPort1Interrupts ( );                  //Initializes buttons that interrupt program
NVIC->ISER[1] = 1 << ((PORT5_IRQn) & 31);  // Enable Port 5 interrupt on the NVIC
__enable_interrupt ( );                   //Enable all interrupts that are turned on


Sys_init ();



while (1)
{
;                                         // Hardware is doing all the work, so nothing more to do in this while loop
}
}


void timer_init(void){
    TIMER_A2->CCR[0] = (10000 - 1);           // PWM Period (# cycles of clock)
    TIMER_A2->CCTL[1] = 0b0000000001110000;  // CCR1 reset/set mode 7
    TIMER_A2->CTL = 0b0000001000010100;       // SMCLK, Up Mode, clear TAR to start
}


void Sys_init (void)
{
                                   //initialization of systic timer
             SysTick -> CTRL = 0; // disable SysTick During step
             SysTick -> LOAD = 0x00FFFFFF; // max reload value
             SysTick -> VAL = 0; // any write to current clears it
             SysTick -> CTRL = 0x00000005; // enable systic, 3MHz, No Interrupts


}


void SetupLEDs(void) {
    /*
P3->SEL0 &=~ BIT0;                          // Setup the LED2 on the Launchpad as GPIO, Output, Off
P3->SEL1 &=~ BIT0;
P3->DIR |= BIT0;
P3->OUT &=~ BIT0;
P3->SEL0 &=~ BIT1;                        // Setup the LED2 on the Launchpad as GPIO, Output, Off
P3->SEL1 &=~ BIT1;
P3->DIR |= BIT1;
P3->OUT &=~ BIT1;
*/

    P1->DIR = BIT0;
}

void SetupPort1Interrupts (void) {
P5->SEL0 &=~ BIT1;                        // Setup the P1.1 on the Launchpad as Input, Pull Up Resistor
P5->SEL1 &=~ BIT1;
P5->DIR &=~ BIT1;
P5->REN |= BIT1;
P5->OUT |= BIT1;                        //Input, Pull Up Resistor
P5->IES |= BIT1;                        //Set pin interrupt to trigger from high to low (starts high due to pull up resistor)
P5->IE |= BIT1;                         //Set interrupt on for P1.1
P5->SEL0 &=~ BIT4;                       // Setup the P1.4 on the Launchpad as Input, Pull Up Resistor
P5->SEL1 &=~ BIT4;
P5->DIR &=~ BIT4;
P5->REN |= BIT4;
P5->OUT |= BIT4;                         //Input, Pull Up Resistor
P5->IES |= BIT4;                         //Set pin interrupt to trigger from high to low (starts high due to pull up resistor)
P5->IE |= BIT4;                          //Set interrupt on for P1.4
P5->IFG = 0;                             //Clear all Port 1 interrupt flags
}


void PORT5_IRQHandler(void) {
if(P5->IFG & BIT4){
    if((P5IN & BIT1) == 0x00){                      //If P5.1 had an interrupt (comparing the status with the BIT)
        SysTick_delay (10);
        if((P5IN & BIT1) == 0x00){
                                                       //P3->OUT ^= BIT0;                           //Turn Green On
        P1->OUT ^= BIT0;
}}}
if(P5->IFG & BIT4){                       //If P5.4 had an interrupt (comparing the status with the BIT)
    if((P5IN & BIT4) == 0x00){                      //If P5.1 had an interrupt (comparing the status with the BIT)
        SysTick_delay (10);
        if((P5IN & BIT4) == 0x00){
                                                   //P3->OUT ^= BIT0;                           //Turn Green On
        P1->OUT ^= BIT0;
}}}
P5->IFG = 0;                              //Clear all flags
}


void SysTick_delay (uint16_t delay)
    { // Systick delay function
    SysTick -> LOAD = ((delay * 3000) - 1); //delay for 1 msecond per delay value
    SysTick -> VAL = 0; // any write to CVR clears it
    while ( (SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
    }
