#include "msp.h"
#include <stdio.h>
#include <string.h>

void findpin(void);
void checkpin(void);
void keypad_init (void); // prototype for GPIO initialization
uint8_t  Keypad_Read(void); // prototype for keypad scan subroutine
void Print_Keys (void); // Print Key pressed
void SysTick_delay (uint16_t delay);   // prototyping the systick function
uint8_t num, pressed;
char Pin[10];
char Code[10];
int counter = 0;
int n=0,j=0;
int check = 1;


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    keypad_init ( );

    printf("Please enter a four digit code.\n");

    //while(check ==1){
    //findpin();
    //}

    while ( 1 )
    {
        if (check ==1){
            findpin();
        }
        if (check == 0){
            checkpin();
        }

    //checkpin();

    }
}

void findpin(void){

        pressed =  Keypad_Read(); // Call Function to read Keypad
        if ( pressed ){



            if(num == 12){
                if(counter<4){
                    printf("Please reenter a 4 digit code\n");
                    Code[n-4] = 0;
                    Code[n-3] = 0;
                    Code[n-2] = 0;
                    Code[n-1] = 0;

                }

                          //strcpy(Pin, Code);
                          printf(" Code = %d %d %d %d\n", Code[n-4], Code[n-3], Code[n-2], Code[n-1]);
                          printf(" Pin = %d %d %d %d\n", Pin[j-4], Pin[j-3], Pin[j-2], Pin[j-1]);
                          //printf("Please enter the pin again\n");
                          //n=0;
                          counter = 0;
                          //if((Code[n-4] == 0) && (Code[n-3] == 0) && (Code[n-2] == 0) && (Code[n-1] == 0)){
                          if((Code[n-4] == Code[n-3] == Code[n-2] == Code[n-1]) == 1){
                              strcpy(Pin, Code);
                              printf(" Code = %d %d %d %d\n", Code[n-4], Code[n-3], Code[n-2], Code[n-1]);
                              printf(" Pin = %d %d %d %d\n", Pin[j-4], Pin[j-3], Pin[j-2], Pin[j-1]);
                              printf("Please enter the pin again\n");
                              n=0;
                              j=0;
                              check = 0;
                          }
                         // check = 0;
                  }
            if(num<10){
                Code[n] = num;
                counter++;
                j++;
                n++;
            }
            if(num == 11){
                Code[n] = 0;
                counter++;
                j++;
                n++;
            }
        Print_Keys ( );
        __delay_cycles(30000); // 10ms delay through the loop before reading keypad again

        }


    }

void checkpin(void){

        pressed =  Keypad_Read(); // Call Function to read Keypad
        if ( pressed ){



            if(num == 12){
                if(n<4){
                    printf("Please enter a 4 digit code\n");
                    Code[n-4] = 0;
                    Code[n-3] = 0;
                    Code[n-2] = 0;
                    Code[n-1] = 0;

                }

                printf(" Code = %d %d %d %d\n", Code[n-4], Code[n-3], Code[n-2], Code[n-1]);
                printf(" Pin = %d %d %d %d\n", Pin[j-4], Pin[j-3], Pin[j-2], Pin[j-1]);

                          //strcpy(Pin, Code);
               // if ( strcmp (Pin, Code) == 0 ){
                if(Pin[j-1] == Code[n-1]){
                    printf("Entries were identical\n");
                }
                //if ( strcmp (Pin, Code ) == 1 ){
                if(Pin[j-1] != Code[n-1]){
                    printf("Entries were not identical\n");
                }
                         // printf(" Code = %d %d %d %d\n", Code[n-4], Code[n-3], Code[n-2], Code[n-1]);
                          //printf(" Pin = %d %d %d %d\n", Pin[n-4], Pin[n-3], Pin[n-2], Pin[n-1]);
                          n=0;
                          //j=0;
                  }
            if(num<10){
                Code[n] = num;
                counter++;
                j++;
                n++;
            }
            if(num == 11){
                Code[n] = 0;
                counter++;
                j++;
                n++;
            }
        Print_Keys ( );
        __delay_cycles(30000); // 10ms delay through the loop before reading keypad again

        }


    }

void keypad_init (void)
{
                            //initialization of systic timer
             SysTick -> CTRL = 0; // disable SysTick During step
             SysTick -> LOAD = 0x00FFFFFF; // max reload value
             SysTick -> VAL = 0; // any write to current clears it
             SysTick -> CTRL = 0x00000005; // enable systic, 3MHz, No Interrupts

             P4SEL0 &= ~0x0F;
             P4SEL1 &= ~0x0F;  //  configure P3.0  GPIO
             P4DIR &= ~0x0F;   //  make P3.0 input
             P4REN |= 0x0F;    //  enable pull resistors on P3.0
             P4OUT |= 0x0F;   // P3.0 is a pull-up

             P4SEL0 &= ~0x70;
             P4SEL1 &= ~0x70;  //  configure P3.0  GPIO
             P4DIR  &= ~0x70;   //  make P3.0 input



}


uint8_t  Keypad_Read(void)
{
uint8_t col, row;
for ( col = 0; col < 3; col++ )
{

P4->DIR = 0x00; // Set Columns to inputs
P4->DIR |= BIT ( 4 + col ); // Set column 3 to output
P4->OUT &=~ BIT ( 4 + col ); // Set column 3 to LOW

SysTick_delay (10); // Delay the while loop
row = P4->IN & 0x0F; // read all rows
while ( !(P4IN & BIT0) | !(P4IN & BIT1) | !( P4IN & BIT2) | !( P4IN & BIT3) );
if (row != 0x0F) break; // if one of the input is low, some key is pressed.
}

P2->DIR = 0x00;           // Set Columns to inputs

if ( col == 3)
return 0;


if (row == 0x0E) num = col + 1; // key in row 0
if (row == 0x0D) num = 3 + col +1; // key in row 1
if (row == 0x0B) num = 6 + col +1; // key in row 2
if (row == 0x07) num = 9 + col+1; // key in row 3



return 1;

}


void Print_Keys (void)
{
    if(num < 10 ){
               printf("%d\n", num);
       }

       if(num == 10){
           printf("*\n");
       }
       if(num == 11){
           printf("0\n");
       }
       if(num == 12){
               printf("#\n");
       }


}


    void SysTick_delay (uint16_t delay)
    { // Systick delay function
    SysTick -> LOAD = ((delay * 3000) - 1); //delay for 1 msecond per delay value
    SysTick -> VAL = 0; // any write to CVR clears it
    while ( (SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
    }
