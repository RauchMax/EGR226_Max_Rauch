/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 03/18/2021
* Project: Lab Nine Part Two
* File: Main.c
* Description: This program uses SysTick with interrupts to increment a counter that
* is used to change the number displayed on a seven segment LED. SysTick is set to
* count down every .5 second and an interrupt is triggered where the counter is
* incremented. The count is then checked and used to set the 7 segment LED equal to
* the counter. It counts up from 0 to 9 and then restarts at 0.
**************************************************************************************/

#include <msp.h>

void SysTick_Init (void);
void pin_init(void);
void count(void);

volatile int intervalCnt =0;    //making a volatile variable as the counter


int main(void)
{

WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Halting the Watchdog


pin_init();        //initializing the pins for the 7 segment LED

SysTick_Init ( ); // initialize SysTick with interrupt
__enable_irq ( ); // enable global interrupts


while (1)
{

    count();       // calling the count function

}
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


/****| SysTick_initFunction | *****************************************
* Brief: This function initializes the systick timer with interrupts
* and sets the reload valuse equal to .5 seconds.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void SysTick_Init (void) { //initialization of systic timer
SysTick -> CTRL = 0; // disable SysTick During step
SysTick -> LOAD = 1500000; // reload value for 0.5s interrupts
SysTick -> VAL = 0; // any write to current clears it
SysTick -> CTRL = 0x00000007; // enable SysTick, 3MHz, Interrupts
}



/****| SysTick_Handler Handler | *****************************************
* Brief: This handler delays increments the counter by one.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void SysTick_Handler (void) {
intervalCnt++ ;               // increment counter by 1
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

}
