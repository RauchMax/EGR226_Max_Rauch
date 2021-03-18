#include "msp.h"


void SetupLEDs(void);
void SetupPort1Interrupts (void);
void Sys_init (void);
void SysTick_delay (uint16_t delay);
void timer_init(void);

volatile int DC = 10000;

void main(void)
{
WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer


SetupLEDs ( );                              //Sets up the LEDs as outputs
SetupPort1Interrupts ( );                  //Initializes buttons that interrupt program
NVIC->ISER[1] = 1 << ((PORT5_IRQn) & 31);  // Enable Port 5 interrupt on the NVIC
__enable_interrupt ( );                   //Enable all interrupts that are turned on

int check = DC;

Sys_init ();
timer_init();
TIMER_A2->CCR[1] = DC;

while (1)
{
    check = DC;
}
}


void timer_init(void){

    // Configure GPIO for PWM output
    P5->SEL0 |= BIT6;
    P5->SEL1 &= ~(BIT6);
    P5->DIR |= BIT6;    // set P5.6 to output

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
P5->SEL0 &=~ BIT2;                       // Setup the P1.4 on the Launchpad as Input, Pull Up Resistor
P5->SEL1 &=~ BIT2;
P5->DIR &=~ BIT2;
P5->REN |= BIT2;
P5->OUT |= BIT2;                         //Input, Pull Up Resistor
P5->IES |= BIT2;                         //Set pin interrupt to trigger from high to low (starts high due to pull up resistor)
P5->IE |= BIT2;                          //Set interrupt on for P1.4
P5->IFG = 0;                             //Clear all Port 1 interrupt flags
}


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

          if(DC<=0){
              DC = 11000;
          }
          P1->OUT ^= BIT0;
          DC = DC - 1000;
          TIMER_A2->CCR[1] = DC;
                                                       //P3->OUT ^= BIT0;                           //Turn Green On
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

        if(DC >= 10000){
            DC = -1000;
        }
        P1->OUT ^= BIT0;
        DC = DC + 1000;
        TIMER_A2->CCR[1] = DC;

}
}
}

if(P5->IFG & BIT2){
    if((P5IN & BIT2) == 0x00){                      //If P5.1 had an interrupt (comparing the status with the BIT)
          SysTick_delay (50);
            if((P5IN & BIT2) == 0x00){
                TIMER_A2->CCR[1] = 10000;
            }
            }
}

P5->IFG = 0;                              //Clear all flags
}


void SysTick_delay (uint16_t delay)
    { // Systick delay function
    SysTick -> LOAD = ((delay * 3000) - 1); //delay for 1 msecond per delay value
    SysTick -> VAL = 0; // any write to CVR clears it
    while ( (SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
    }
