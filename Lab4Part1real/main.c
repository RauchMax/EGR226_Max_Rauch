#include "msp.h"

int DebounceSwitch1(void);
//void Port1_Initb(void);
//void LED_Initb(void);

/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer




    P1SEL0 &= ~0x12;
    P1SEL1 &= ~0x12;  // 1) configure P1.4 and P1.1 as GPIO
    P1DIR &= ~0x12;  // 2) make P1.4 and P1.1 inputs
    P1REN |= 0x12;  // 3) enable pull resistors on P1.4 and P1.1
    P1OUT |= 0x12; // P1.4 and P1.1 are pull-up


    P2->SEL1 &= ~BIT0; // configure P2.2-P2.0 as simple I/O
    P2->SEL0 &= ~BIT0;
    P2->DIR |= BIT0; // P2.2-2.0 set as output
    P2->OUT &= ~BIT0; // turn all three LEDs on

    P2->SEL1 &= ~BIT1; // configure P2.2-P2.0 as simple I/O
    P2->SEL0 &= ~BIT1;
    P2->DIR |= BIT1; // P2.2-2.0 set as output
    P2->OUT &= ~BIT1; // turn all three LEDs on

    P2->SEL1 &= ~BIT2; // configure P2.2-P2.0 as simple I/O
    P2->SEL0 &= ~BIT2;
    P2->DIR |= BIT2; // P2.2-2.0 set as output
    P2->OUT &= ~BIT2; // turn all three LEDs on

    //int color = 1;

    while(1)
    {
        int pin_Value = 0; //initialize variable as low
        int color;

        for(color=1; color<5; color++)
        {
        if(color==4){
            color =1;
        }

        if ((P1IN & BIT1) == 0x00) //check of button pushed
        { __delay_cycles(3000); //pause for 10 m-sec for switch bounce
        if ((P1IN & BIT1) == 0x00) //check of button is still pushed
        pin_Value = color;
        }
        if( pin_Value==1){
        P2OUT &= ~BIT1;
        P2OUT &= ~BIT2;
        P2OUT |= BIT0; //Toggle P2 LED
        P2OUT &= ~BIT1;
        P2OUT &= ~BIT2;
        //color=2;
        __delay_cycles(2000000);
        }
        if(pin_Value==2){
        P2OUT &= ~BIT0;
        P2OUT &= ~BIT2;
        P2OUT |= BIT1; //Toggle P2 LED
        P2OUT &= ~BIT0;
        P2OUT &= ~BIT2;
        //color=3;
        __delay_cycles(2000000);
        }
        if(pin_Value==3){
        P2OUT &= ~BIT1;
        P2OUT &= ~BIT0;
        P2OUT |= BIT2; //Toggle P2 LED
        P2OUT &= ~BIT1;
        P2OUT &= ~BIT0;
        //color=1;
        __delay_cycles(2000000);
        }
        }
    }

    }

//}
