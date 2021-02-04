#include "msp.h"


/**
 * main.c
 */
void main(void)
{
    //stop watchdog timer (WDT is uded to break you out if unwanted loops)

	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	//configure variable for loop maintenance
	P1->DIR = BIT0;

	//Temporary variable for for loop maintenance
	int i,j;
	//scanf("%d", &j);
	while(1){
	    P1->OUT ^= BIT0;      //toggle LED status
	    for(i=j; i>0; i--);  //Crude delay
	}

}
