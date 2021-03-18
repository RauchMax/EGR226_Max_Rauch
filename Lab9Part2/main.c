#include <msp.h>

void SysTick_Init (void);
void pin_init(void);
void count(void);

volatile int intervalCnt =0;


int main(void)
{

WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Halting the Watchdog


pin_init();

SysTick_Init ( ); // initialize SysTick with interrupt
__enable_irq ( ); // enable global interrupts


while (1)
{

    count();

    /*
if ( (intervalCnt % 2) == 0)
P6->OUT ^= BIT6; // Toggle pin 4 every second
P3->OUT ^= BIT0;
P1->OUT ^= BIT6;
P1->OUT ^= BIT7;
P5->OUT ^= BIT0;
if ( (intervalCnt % 4) == 0)
P6->OUT ^= BIT7; // Toggle pin 5 every 2 seconds
P5->OUT ^= BIT7;
*/
}
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
SysTick -> LOAD = 1500000; // reload value for 0.5s interrupts
SysTick -> VAL = 0; // any write to current clears it
SysTick -> CTRL = 0x00000007; // enable SysTick, 3MHz, Interrupts
}


void SysTick_Handler (void) {
intervalCnt++ ; // increment interval timer by 0.5 s
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

}
