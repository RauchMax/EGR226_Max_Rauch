/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 03/2/2021
* File: Main.c
* Description: This program reads a standard twelve key keypad
* and prints a four digit code to the screen with the press of
* the pound key. It does not count the * as a valid digit. If less
* than four valid digits are entered it asks for four digits. It
* should be able to accept many digits and just print the last four.
*  It will not print multiple numbers if the button is held down.
**************************************************************************************/

#include "msp.h"

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

void Scroll(void);

char string[20] = {'L','A','B','O','R','A','T','O','R','Y',' ','O','V','E','R'};
int i=0,j=0,a=0,m=0,k=0;
int n = 144;

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

         //P3SEL0 &= ~0x06;
         //P3SEL1 &= ~0x06;  //  configure P4.2 & 4.3  GPIO
         //P3DIR |= 0x06;   //  make P4.2 & 4.3 output
         //P3OUT &= ~0x06;
         //P3OUT |= BIT3;

        P2SEL0 &= ~0x30;
        P2SEL1 &= ~0x30;  //  configure P4.2 & 4.3  GPIO
        P2DIR |= 0x30;   //  make P4.2 & 4.3 output
        P2OUT &= ~0x30;

         P4SEL0 &= ~0xF0;
         P4SEL1 &= ~0xF0;  //  configure P4.2 & 4.3  GPIO
         P4DIR |= 0xF0;   //  make P4.2 & 4.3 output
         P4OUT &= ~0xF0;

    SysTick_Init ();
    LCD_init();

    //int i=0,j=0,a=0,m=0,k=0;
    //int n = 144;


    commandWrite(0x80);
    delay_micro(100);



    while(1){

        Scroll();
      }
}

void Scroll(void){

    if(m==0){

            if(i>14){
                i=j;
                j++;
                //m++;

                delay_ms(700);
                commandWrite(0x80);
                delay_micro(100);
                //LCD_init();
                commandWrite(0x01);
               // delay_micro(100);

            }
            dataWrite(string[i]);
            delay_ms(10);

            i++;

            if(j>14){
                m=1;
                a=0;
                k=0;
                n=144;
            }

    }

    if(m==1){

            if(k >= a){
                k=0;
                a++;
                //m++;
                n--;
                delay_ms(700);
                commandWrite(n);
                delay_micro(100);

            }

            dataWrite(string[k]);
            delay_ms(10);
            k++;

            if(a>15){
                m=0;
                j=0;
                i=0;
                commandWrite(0x80);
                delay_micro(100);

            }
        }
}

void LCD_init(void){

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





void SysTick_Init (void) //initialization of systic timer
{
SysTick -> CTRL = 0;             // disable SysTick During step
SysTick -> LOAD = 0x00FFFFFF; // max reload value
SysTick -> VAL = 0;             // any write to current clears it
SysTick -> CTRL = 0x00000005; // enable systic, 3MHz, No
                               //Interrupts
}



void delay_micro(uint32_t microsecond)
{
SysTick -> LOAD = (microsecond*3 - 1); // delay*3
SysTick -> VAL = 0; //clears counter
while((SysTick -> CTRL & 0x00010000) == 0);
}



void delay_ms(unsigned ms)
{
SysTick -> LOAD = (ms*3000 - 1); // delay*3000
SysTick -> VAL = 0; //clears counter
while((SysTick -> CTRL & 0x00010000) == 0);
}



void PulseEnablePin (void)
{
P2OUT &=~BIT5;     // make sure pulse starts out at 0V
delay_micro(10);
P2OUT |=BIT5;
delay_micro(10);
P2OUT &=~BIT5;
delay_micro(10);
}



void pushNibble (uint8_t nibble)
{
P4OUT &=~0xF0;                 // clear P4.4-P4.7
P4OUT |= (nibble & 0x0F) << 4; // port pins P4.4 - P4.7 wired to D4 - D7
PulseEnablePin();
}



void pushByte (uint8_t byte)
{
uint8_t nibble;
nibble = (byte & 0xF0) >> 4;
pushNibble(nibble);
nibble = byte & 0x0F;
pushNibble(nibble);
delay_micro(100);
}



void commandWrite(uint8_t command){
    P2OUT &= ~BIT4;
    pushByte (command);
}



void dataWrite(uint8_t data){
    P2OUT |= BIT4;
    pushByte (data);
}
