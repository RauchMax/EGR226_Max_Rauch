/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 03/2/2021
* Project: Lab Seven Part Two
* File: Main.c
* Description: This program prints MAX to the first row of a 4x16 LCD
* centered. Then it prints RAUCH centered to the second row of the LCD.
* It the prints EGR centered on the third row, and 226 centered on the
* fourth row.
**************************************************************************************/

#include "msp.h"
#include <stdio.h>

void adcsetup(void);
void print(void);

void LCD_init(void);                   // This is the initialization sequence
void delay_micro(unsigned microsec); // SysTick timer generate delay in microseconds.
void delay_ms(unsigned ms);          // SysTick timer generate a delay in
                                    //milliseconds.
void SysTick_Init (void);
void PulseEnablePin(void);         // This function will sequence the Enable (E) pin
void pushNibble(uint8_t nibble);       // This function pushes 1 nibble onto the data
                                       // pins and pulses the Enable pin
void pushByte(uint8_t byte);
                                         // This function first pushes the most significant 4 bits of the
                                       // byte onto the data pins by calling the pushNibble() function.
                                      // Next, it pushes the least significant 4 bits onto the data pins
                                      // by calling the pushNibble() function
void commandWrite(uint8_t command);    // Writing one byte of command by calling the
                                        // pushByte() function with the command
                                        //parameter
void dataWrite(uint8_t data);           // Writing one byte of DATA by calling the
                                          // pushByte() function with the
                                         //data parameter
char name[20] = {'C','u','r','r','e','n','t',' ','T','e','m','p','.',' ','i','s'};
                                   //making one string to print to the screen

int result;
float volt,tempC,tempF;

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

         //P3SEL0 &= ~0x06;
         //P3SEL1 &= ~0x06;  //  configure P4.2 & 4.3  GPIO
         //P3DIR |= 0x06;   //  make P4.2 & 4.3 output
         //P3OUT &= ~0x06;
         //P3OUT |= BIT3;

        P2SEL0 &= ~0x30;
        P2SEL1 &= ~0x30;  //  configure P2.4 & P2.5 GPIO
        P2DIR |= 0x30;   //  make P2.4 & P2.5 output
        P2OUT &= ~0x30;

         P4SEL0 &= ~0xF0;
         P4SEL1 &= ~0xF0;  //  configure P4.4 & P4.7  GPIO
         P4DIR |= 0xF0;   //  make P4.4 & P4.7 output
         P4OUT &= ~0xF0;  // set P4.4 & P4.7 to 0

    SysTick_Init ();   //initializing systick
    LCD_init();       //initializing the lcd
    adcsetup();

    int i=0;


    commandWrite(0x80); // changing the cursor to the 1st position in the first row
    delay_micro(100);

    for(i=0;i<16;i++){
        dataWrite(name[i]);  //print the ith letter to the screen
        delay_ms(10);
    }


    while(1){

                ADC14->CTL0 |=1;                       //start a conversion
                while(!ADC14->IFGR0);                  // wait until conversion complete
                result = ADC14->MEM[5];                // immediately store value in a variable
                //printf ("Value is:\t%d\n", result);
                volt = result*.0002;
                //printf ("Voltage is:\t%.3f\n", volt);
                tempC =(volt-.500)/.010;
                tempF =(tempC*(9.0/5.0))+32.0;
                printf ("Voltage is:\t%.3f degrees C\n", tempC);
                //printf ("Voltage is:\t%.3f degrees F\n\n", tempF);
                delay_ms(1000);                        // wait for next value- using Systick function

                commandWrite(0x96);
                delay_micro(100);

                print();


    }
}

/****| LCD_initFunction | *****************************************
* Brief: This function initializes the LCD
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void LCD_init(void){    //following the start up sequence

     commandWrite(3);
     delay_ms(100);
     commandWrite(3);
     delay_micro(200);
     commandWrite(3);
     delay_ms(100);
     commandWrite(2);
     delay_micro(100);
     commandWrite(0x28);
     delay_micro(100);
     delay_micro(100);
     commandWrite(0x0F);
     delay_micro(100);
     commandWrite(0x01);
     delay_micro(100);
     commandWrite(0x06);
     delay_ms(10);

}



/****| SysTick_InitFunction | *****************************************
* Brief: This function initializes the Systick timer
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void SysTick_Init (void) //initialization of systic timer
{
SysTick -> CTRL = 0;             // disable SysTick During step
SysTick -> LOAD = 0x00FFFFFF; // max reload value
SysTick -> VAL = 0;             // any write to current clears it
SysTick -> CTRL = 0x00000005; // enable systic, 3MHz, No
                               //Interrupts
}


/****| delay_microFunction | *****************************************
* Brief: This function creates a delay for a selected
* number of microseconds.
* param: N/A
* data: Accept one variable called microsecond that is used
* to calculate the delay.
* return:N/A
*************************************************************/

void delay_micro(uint32_t microsecond)
{
SysTick -> LOAD = (microsecond*3 - 1); // delay*3
SysTick -> VAL = 0; //clears counter
while((SysTick -> CTRL & 0x00010000) == 0);
}


/****| delay_msFunction | *****************************************
* Brief: This function creates a delay for a selected
* number of milliseconds.
* param: N/A
* data: Accept one variable called ms that is used
* to calculate the delay.
* return:N/A
*************************************************************/

void delay_ms(unsigned ms)
{
SysTick -> LOAD = (ms*3000 - 1); // delay*3000
SysTick -> VAL = 0; //clears counter
while((SysTick -> CTRL & 0x00010000) == 0);
}


/****| PulseEnablePinFunction | *****************************************
* Brief: This function sets the E pin low, then sets it to
* high for 10 microseconds, then sets it back to low.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void PulseEnablePin (void)
{
P2OUT &=~BIT5;     // make sure pulse starts out at 0V
delay_micro(10);
P2OUT |=BIT5;     //pulse high
delay_micro(10);
P2OUT &=~BIT5;    //set backto low
delay_micro(10);
}


/****| pushNibbleFunction | *****************************************
* Brief: This function takes an 8 bit number and clears the
* first 4 bits. It then sets the d4-d7 pins equal to the least
* significant 4 bits.
* param: N/A
* data: Accepts one variable named nibble that has half of the
* data or command on it.
* return:N/A
*************************************************************/


void pushNibble (uint8_t nibble)
{
P4OUT &=~0xF0;                 // clear P4.4-P4.7
P4OUT |= (nibble & 0x0F) << 4; // port pins P4.4 - P4.7 wired to D4 - D7
PulseEnablePin();              // pulse the E pin
}


/****| pushByteFunction | *****************************************
* Brief: This function takes an 8 bit number and clears the
* last 4 bits then shifts the bits to the right by 4. It then
* calls pushNibble and sends it this number. Then it sets nibble
* equal to the last 4 digits of the original number and sends
* this number to pushNibble.
* param: N/A
* data: Accepts one variable named byte that has the data or
* command on it.
* return:N/A
*************************************************************/

void pushByte (uint8_t byte)
{
uint8_t nibble;
nibble = (byte & 0xF0) >> 4;   //shift bits over 4
pushNibble(nibble);           //give this value to pushNibble
nibble = byte & 0x0F;        // clear bytes 4-7
pushNibble(nibble);            // give bytes 0-3 to pushNibble
delay_micro(100);
}


/****| commandWriteFunction | *****************************************
* Brief: This function sets the RS pin to 0 for command.
* Then it calls pushByte and passes it the command.
* param: N/A
* data: Accepts one variable that contains the command.
* return:N/A
*************************************************************/

void commandWrite(uint8_t command){
    P2OUT &= ~BIT4;                    //set rs to 0
    pushByte (command);
}


/****| dataWriteFunction | *****************************************
* Brief: This function sets the RS pin to 1 for write.
* Then it calls pushByte and passes it the data that needs
* to be written.
* param: N/A
* data: Accepts one variable that contains the data that
* needs to be written.
* return:N/A
*************************************************************/

void dataWrite(uint8_t data){
    P2OUT |= BIT4;                //set rs to 1
    pushByte (data);
}


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


void print(void){
    int j;
    char temp[4];

    sprintf(temp,"%.1f",tempC);


    for(j=0;j<4;j++){
        dataWrite(temp[j]);  //print the ith letter to the screen
        delay_ms(10);
    }

    dataWrite(0xdf);
    delay_ms(10);

    dataWrite(0x43);
    delay_ms(10);
}
