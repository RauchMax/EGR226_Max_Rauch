#include <msp.h>

void SysTick_Init (void);
void pin_init(void);
void count(void);
void SetupPort5Interrupts (void);
void SysTick_delay (uint16_t delay);
void SetupLEDs(void);

volatile int intervalCnt =0;


int main(void)
{

WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Halting the Watchdog

SetupLEDs();
pin_init();
SetupPort5Interrupts ();
NVIC->ISER[1] = 1 << ((PORT5_IRQn) & 31);  // Enable Port 5 interrupt on the NVIC
__enable_interrupt ( );                   //Enable all interrupts that are turned on
SysTick_Init ( ); // initialize SysTick with interrupt
__enable_irq ( ); // enable global interrupts


while (1)
{
    count();
}
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

void SetupPort5Interrupts (void) {
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

void SysTick_Init (void) { //initialization of systic timer
SysTick -> CTRL = 0; // disable SysTick During step
SysTick -> LOAD = 0x00FFFFFF; // reload value for 0.5s interrupts
SysTick -> VAL = 0; // any write to current clears it
SysTick -> CTRL = 0x00000005; // enable SysTick, 3MHz, Interrupts
}

void SysTick_delay (uint16_t delay)
    { // Systick delay function
    SysTick -> LOAD = ((delay * 3000) - 1); //delay for 1 msecond per delay value
    SysTick -> VAL = 0; // any write to CVR clears it
    while ( (SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
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

void count(void){

    if (intervalCnt ==  0){
        P6->OUT &= ~BIT7;  //G
        P5->OUT |= BIT7;   //A
        P3->OUT |= BIT0;   //B
        P1->OUT |= BIT6;   //C
        P1->OUT |= BIT7;   //D
        P5->OUT |= BIT0;   //E
        P6->OUT |= BIT6;   //F
    }

    if (intervalCnt ==  1){
        P6->OUT &= ~BIT7;  //G
        P5->OUT &= ~BIT7;   //A
        P3->OUT |= BIT0;   //B
        P1->OUT |= BIT6;   //C
        P1->OUT &= ~BIT7;   //D
        P5->OUT &= ~BIT0;   //E
        P6->OUT &= ~BIT6;   //F
       }

    if (intervalCnt ==  2){
        P6->OUT |= BIT7;   //G
        P5->OUT |= BIT7;   //A
        P3->OUT |= BIT0;   //B
        P1->OUT &= ~BIT6;   //C
        P1->OUT |= BIT7;   //D
        P5->OUT |= BIT0;   //E
        P6->OUT &= ~BIT6;   //F
       }

    if (intervalCnt ==  3){
        P6->OUT |= BIT7;  //G
        P5->OUT |= BIT7;   //A
        P3->OUT |= BIT0;   //B
        P1->OUT |= BIT6;   //C
        P1->OUT |= BIT7;   //D
        P5->OUT &= ~BIT0;   //E
        P6->OUT &= ~BIT6;   //F
       }

    if (intervalCnt ==  4){
        P6->OUT |= BIT7;   //G
        P5->OUT &= ~BIT7;   //A
        P3->OUT |= BIT0;   //B
        P1->OUT |= BIT6;   //C
        P1->OUT &= ~BIT7;   //D
        P5->OUT &= ~BIT0;   //E
        P6->OUT |= BIT6;   //F
       }

    if (intervalCnt ==  5){
        P6->OUT |= BIT7;   //G
        P5->OUT |= BIT7;   //A
        P3->OUT &= ~BIT0;   //B
        P1->OUT |= BIT6;   //C
        P1->OUT |= BIT7;   //D
        P5->OUT &= ~BIT0;   //E
        P6->OUT |= BIT6;   //F
       }

    if (intervalCnt ==  6){
        P6->OUT |= BIT7;   //G
        P5->OUT |= BIT7;   //A
        P3->OUT &= ~BIT0;   //B
        P1->OUT |= BIT6;   //C
        P1->OUT |= BIT7;   //D
        P5->OUT |= BIT0;   //E
        P6->OUT |= BIT6;   //F
       }

    if (intervalCnt ==  7){
        P6->OUT &= ~BIT7;  //G
        P5->OUT |= BIT7;   //A
        P3->OUT |= BIT0;   //B
        P1->OUT |= BIT6;   //C
        P1->OUT &= ~BIT7;   //D
        P5->OUT &= ~BIT0;   //E
        P6->OUT &= ~BIT6;   //F
       }

    if (intervalCnt ==  8){
        P6->OUT |= BIT7;   //G
        P5->OUT |= BIT7;   //A
        P3->OUT |= BIT0;   //B
        P1->OUT |= BIT6;   //C
        P1->OUT |= BIT7;   //D
        P5->OUT |= BIT0;   //E
        P6->OUT |= BIT6;   //F
       }

    if (intervalCnt ==  9){
        P6->OUT |= BIT7;   //G
        P5->OUT |= BIT7;   //A
        P3->OUT |= BIT0;   //B
        P1->OUT |= BIT6;   //C
        P1->OUT |= BIT7;   //D
        P5->OUT &= ~BIT0;   //E
        P6->OUT |= BIT6;   //F
       }

    if (intervalCnt > 9){
        intervalCnt = 0;
       }

    if (intervalCnt < 0){
            intervalCnt = 9;
           }

}
