#include "msp.h"


void pwm_init(int dc);
//int DC;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	int DC;

	//pwm_init(DC);

	//DC = (Input * 1000);

	while(1){
	    //pwm_init(DC);

	    // Configure GPIO for PWM output
	            P5->DIR |= BIT6;    // P2.4 set TA0.1
	            P5->SEL0 |= BIT6;
	            P5->SEL1 &= ~(BIT6);


	            TIMER_A2->CCR[0] = (10000 - 1);                    // PWM Period (# cycles of clock)
	            TIMER_A2->CCTL[1] = 0b0000000001110000;        // CCR1 reset/set mode 7
	            TIMER_A2->CCR[1] = DC;                          // CCR1 PWM duty cycle
	            TIMER_A2->CTL = 0b0000001000010100;           // SMCLK, Up Mode, clear TAR to start


	            TIMER_A2->CTL = 0x0214;                       // SMCLK, Up Mode, clear TAR to start
	            TIMER_A2->CTL = TASSEL_2 | MC_1 | TACLR;       // SMCLK, Up Mode, clear TAR to start


	}
}


void pwm_init(int dc){
                        // Configure GPIO for PWM output
    P5->DIR |= BIT6;    // P2.4 set TA0.1
    P5->SEL0 |= BIT6;
    P5->SEL1 &= ~(BIT6);


    TIMER_A2->CCR[0] = (1000 - 1);                    // PWM Period (# cycles of clock)
    TIMER_A2->CCTL[1] = 0b0000000001110000;        // CCR1 reset/set mode 7
    TIMER_A2->CCR[1] = dc;                          // CCR1 PWM duty cycle
    TIMER_A2->CTL = 0b0000001000010100;           // SMCLK, Up Mode, clear TAR to start


    TIMER_A2->CTL = 0x0214;                       // SMCLK, Up Mode, clear TAR to start
    TIMER_A2->CTL = TASSEL_2 | MC_1 | TACLR;       // SMCLK, Up Mode, clear TAR to start
}
