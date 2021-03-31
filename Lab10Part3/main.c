/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 03/24/2021
* Project: Lab Ten Part Three
* File: Main.c
* Description: This program prints "Current Temp. is" on the first line
* and then displays the temperature centered on the third line. It starts
* by showing the temp in C but that can be changed by pushing a button. The
* program will then show the temp in F.
**************************************************************************************/

#include "msp.h"
#include <stdio.h>


void SetupLEDs(void);
void SetupPort5Interrupts (void);
void adcsetup(void);
void print(void);
void printF(void);
void LCD_init(void);
void delay_micro(unsigned microsec);
void delay_ms(unsigned ms);
void delay_mili(unsigned ms);
void SysTick_Init (void);
void PulseEnablePin(void);
void pushNibble(uint8_t nibble);
void pushByte(uint8_t byte);
void commandWrite(uint8_t command);
void dataWrite(uint8_t data);


char name[20] = {'C','u','r','r','e','n','t',' ','T','e','m','p','.',' ','i','s'};
                                   //making one string to print to the screen

int result;
volatile int flag=0;
float volt,tempC,tempF;

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer



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

    SetupLEDs ( );                              //Sets up the LED as outputs
    SetupPort5Interrupts ( );                  //Initializes buttons that interrupt program
    NVIC->ISER[1] = 1 << ((PORT5_IRQn) & 31);  // Enable Port 5 interrupt on the NVIC
    __enable_interrupt ( );                   //Enable all interrupts that are turned on


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
                volt = result*.0002;                   //calculating voltage
                //printf ("Voltage is:\t%.3f\n", volt);
                tempC =(volt-.500)/.010;                //calculating Celcius
                tempF =(tempC*(9.0/5.0))+32.0;          //calculating Fehrenheit
                //printf ("Voltage is:\t%.3f degrees C\n", tempC);
                //printf ("Voltage is:\t%.3f degrees F\n\n", tempF);
                delay_ms(1000);                        // wait for next value- using Systick function

                commandWrite(0x96);                   //moving cursor to 7th spot on 3rd row
                delay_micro(100);

                if(flag==0){                         //checking to print c or f
                    print();
                }
                if(flag==1){
                    printF();
                }


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


/****| SetupLEDs Function | *****************************************
* Brief: This function initializes red LED built into the MSP432.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void SetupLEDs(void) {

    P1->DIR = BIT0;      //setting direction to output
    P1->OUT |= BIT0;    //turning the LED on
}


/****| SetupPort5Interrupts Function | *****************************************
* Brief: This function initializes P5.1, P5.2, and P5.4 as input
* whith the pull up resistors. It also sets them so the interrupts
* is triggered when the pin goes from high to low.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void SetupPort5Interrupts (void) {
P5->SEL0 &=~ BIT1;                        // Setup the P5.1 on the Launchpad as Input, Pull Up Resistor
P5->SEL1 &=~ BIT1;
P5->DIR &=~ BIT1;
P5->REN |= BIT1;
P5->OUT |= BIT1;                        //Input, Pull Up Resistor
P5->IES |= BIT1;                        //Set pin interrupt to trigger from high to low (starts high due to pull up resistor)
P5->IE |= BIT1;                         //Set interrupt on for P5.1
P5->IFG = 0;                             //Clear all Port 5 interrupt flags
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


/****| delay_miliFunction | *****************************************
* Brief: This function creates a delay for a selected
* number of milliseconds.
* param: N/A
* data: Accept one variable called ms that is used
* to calculate the delay.
* return:N/A
*************************************************************/

void delay_mili(unsigned ms)
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


/****| printFunction| *****************************************
* Brief: This function moves the value of tempC into he string
* temp and then prints that string to the LCD screen. It then
* prints the degree symbol followed by C.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void print(void){
    int j;
    char temp[4];

    sprintf(temp,"%.1f",tempC);     //moving tempc into temp string


    for(j=0;j<4;j++){
        dataWrite(temp[j]);        //print the ith letter to the screen
        delay_ms(10);
    }

    dataWrite(0xdf);              //printing the degree symbol
    delay_ms(10);

    dataWrite(0x43);             //print a capital c
    delay_ms(10);
}


/****| printF_Function| *****************************************
* Brief: This function moves the value of tempF into he string
* temp and then prints that string to the LCD screen. It then
* prints the degree symbol followed by F.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void printF(void){
    int j;
    char temp[4];

    sprintf(temp,"%.1f",tempF);  //moving tempf into temp string


    for(j=0;j<4;j++){
        dataWrite(temp[j]);      //print the ith letter to the screen
        delay_ms(10);
    }

    dataWrite(0xdf);           //printing the degree symbol
    delay_ms(10);

    dataWrite(0x46);          //print a capital f
    delay_ms(10);
}


/****| PORT5_IRQHandler Handler | *****************************************
* Brief: This handler checks to see which button caused the interrupt,
* then it checks to see of the button is pressed, pauses and checks
* again to debounce the button. It then sits in a wile statement if
* the button is being held. It then checks the value of flag and changes
* it so when it is incremented it will be the opposite of what it is
* now.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/

void PORT5_IRQHandler(void) {
if(P5->IFG & BIT1){
    if((P5IN & BIT1) == 0x00){                      //If P5.1 had an interrupt (comparing the status with the BIT)
        delay_mili (50);
        if((P5IN & BIT1) == 0x00){
            if((P5IN & BIT1) == 0x00){                      //If P5.1 had an interrupt (comparing the status with the BIT)
                delay_mili (50);
                    if((P5IN & BIT1) == 0x00){
                    while((P5IN & BIT1) == 0x00);          // if it is being held just wait here

                    }
                    }

          if(flag==0){
              flag = 0;                          //setting flag to 0 so when it is incremented it becomes 1
              P1->OUT ^= BIT0;                 //toggle LED
          }
          if(flag==1){
              flag = -1;                       //setting flag to -1 so when it is incremented it becomes 0
              P1->OUT ^= BIT0;                 //toggle LED
          }

}
}
}

flag++;
P5->IFG = 0;                              //Clear all flags
}
