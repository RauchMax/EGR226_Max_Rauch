/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 03/24/2021
* Project: Lab Ten Part Two
* File: Main.c
* Description: This program uses the ADC and the temp sensor to
* print the temperature to the screen. This program displays the temp
* twice a second, and shows both Celsius and Fahrenheit.
**************************************************************************************/


#include "msp.h"
#include <stdio.h>

void adcsetup(void);
void delaymilli(unsigned ms);
void SysTick_Init (void);

int result;
float volt,tempC,tempF;

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    adcsetup();
    SysTick_Init ();
    printf("Start\n");

    while(1){
        ADC14->CTL0 |=1;                       //start a conversion
        while(!ADC14->IFGR0);                  // wait until conversion complete
        result = ADC14->MEM[5];                // immediately store value in a variable
        //printf ("Value is:\t%d\n", result);
        volt = result*.0002;                    //calculating volt
        //printf ("Voltage is:\t%.3f\n", volt);
        tempC =(volt-.500)/.010;                //calculating temp in C
        tempF =(tempC*(9.0/5.0))+32.0;           //calculating temp in F
        printf ("Voltage is:\t%.3f degrees C\n", tempC);
        printf ("Voltage is:\t%.3f degrees F\n\n", tempF);
        delaymilli(1000);                       // wait for next value- using Systick function
    }
}


/****| adcsetupFunction| *****************************************
* Brief: This function initializes the ADC to use MCLK, 14 bit
* resolution, A0 input and pin 5.5.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void adcsetup(void)
{
ADC14->CTL0 = 0x00000010;             //power on and disabled during configuration
ADC14->CTL0 |= 0x04D80300;           // S/H pulse mode, MCLCK, 32 sample clocks,
                                     //sw trigger, /4 clock divide
ADC14->CTL1 = 0x00000030;           // 14-bit resolution
ADC14->MCTL[5] = 0;                 // A0 input, single ended, vref=avcc
P5->SEL1 |= BIT5;                   // configure pin 5.5 for AO
P5->SEL0 |= BIT5;
ADC14->CTL1 |= 0x00050000;           //start converting at mem reg 5
ADC14->CTL0 |= 2;                   //enable ADC after configuration
}


/****| SysTick_InitFunction | *****************************************
* Brief: This function initializes the Systick timer
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


/****| delay_milliFunction | *****************************************
* Brief: This function creates a delay for a selected
* number of milliseconds.
* param: N/A
* data: Accept one variable called ms that is used
* to calculate the delay.
* return:N/A
*************************************************************/


void delaymilli(unsigned ms)
{
SysTick -> LOAD = (ms*3000 - 1); // delay*3000
SysTick -> VAL = 0; //clears counter
while((SysTick -> CTRL & 0x00010000) == 0);
}
