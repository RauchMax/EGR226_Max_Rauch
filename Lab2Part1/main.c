/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 01/18/2021
* Project: Lab One Part One
* File: Main.c
* Description: This is a program that prints out the color code of a resistor
* based on the entered number code that is entered. The program will then ask
* the user if they would like to add another number code or be done. If an invalid
* code is entered the program will catch it and ask for another entry.
**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void prompt(void);            //prototyping the functions
int CalcResistorColors(int);
void getColorBands(char*, char*, char*, char*);
void calcResistance(char, char, char, char);



int main()
{
int status,exit;
int Input;

do{

prompt();        //calling the prompt function to print and ask for input


 do{

    status = scanf("%d", &Input);   //checking the input to see if it is a number
    if (status == 0){     //i am checking this in the main because my function is
                                    //type int and cant accept a character
                                //if it isn't a number the user is asked to renter
        printf("ERROR: please enter a correct entry for an integer\n");
        fflush(stdin);         //if incorrect this flushes the incorrect input
    }
 }while(status == 0);         //if it is a number it is printed to the screen

   printf("You entered %d\n",Input);

CalcResistorColors(Input);          //calling the resistor color function

printf("Do you want to enter a new code? If yes enter 1, if no enter 0.\n");
scanf("%d",&exit);             //checking to see if the user wants to try again

}while(exit ==1);

printf("Thank You. Exiting Program.\n");  //if not the program exits

    return 0;
}


/****| promptFunction | *****************************************
* Brief: This function prints out the resistor codes and
* asks the user for input.
* param: N/A
* data: N/A
* return:N/A
*************************************************************/


void prompt(void)
{

printf("--------------------Resistor Codes---------------------\n");
 printf("|Character| Color | Band 1 & 2 | Band 3    | Band 4  |\n");
 printf("| K       | Black | 0          |*1         |+/- 1%%   |\n");
 printf("| N       | Brown | 1          |*10        |+/- 2%%   |\n");
 printf("| R       | Red   | 2          |*100       |         |\n");
 printf("| O       | Orange| 3          |*1,000     |         |\n");
 printf("| Y       | Yellow| 4          |*10,000    |         |\n");
 printf("| G       | Green | 5          |*100,000   |+/- 0.5%% |\n");
 printf("| B       | Blue  | 6          |*1,000,000 |+/- 0.25%%|\n");
 printf("| V       | Violet| 7          |*10,000,000|+/- 0.1%% |\n");
 printf("| E       | Grey  | 8          |           |+/- 0.05%%|\n");
 printf("| W       | White | 9          |           |         |\n");
 printf("| D       | Gold  |            |           |+/- 5%%   |\n");
 printf("| S       | Silver|            |           |+/- 10%%  |\n");
 printf("-------------------------------------------------------\n\n");

 printf("Would you like to convert a color-code to a resistance value or determine the color-code from a resistance value.\n");
                 //printing the chart and asking for input
return;
}


/****| CalcResistorFunction | *****************************************
* Brief: This function takes the input and checks to see if it
* is in the correct range. If it is it separates the digits of the
* number and saves them into an array, while counting the total digits.
* It prints the array and uses it to find the first two colors. It uses
* the counter to find the third color. If the input is in the wrong range
* it asks and takes in new input while error checking then repeats.
* param:
* data: one integer.
* return: N/A prints from function
*************************************************************/


int CalcResistorColors(int color)
{
    int j,n,i,status, count=0,check =0,counting;
    int arry[10];

    counting = color;   //setting counting = to the input
                       //this had to be done so i could could separate the digits and
    do{                //still use the original input

    if(color >= 1 && color <=99000000){  //checking to see if the int is in the right range
        printf("Integer in correct range.\n");
        check = 0;  //setting check equal to 0 to exit the loop

while(counting > 0)  //making a loop that splits the int and counts the digits
    {
        i = counting % 10;  //spliting last digit from the int
        count++;            //adding to the count for each digit
        counting = counting / 10;
        //printf("%d\n",i);  //was used for debuging
    }
printf("# of digits = %d\n",count);


for (i = count-1; i >= 0; i--) { //looping for the number of digits in the int
  arry[i] = color%10;            //enter each digit of the int into an array
  color = color/10;
}


for (j = 0; j < count; j++ ) {   //printing each element of the array
      printf("Element[%d] = %d\n", j, arry[j] );
   }
check =0;

printf("The color code is: ");   //printing the output

for(n=0; n<2; n++)           //finding the first two colors based on what number
{                            //is stored in the first two elements of the array
    if(arry[n]==0)
    {
        printf("Black - ");
    }
     if(arry[n]==1)
    {
        printf("Brown - ");
    }
     if(arry[n]==2)
    {
        printf("Red - ");
    }
     if(arry[n]==3)
    {
        printf("Orange - ");
    }
     if(arry[n]==4)
    {
        printf("Yellow - ");
    }
     if(arry[n]==5)
    {
        printf("Green - ");
    }
     if(arry[n]==6)
    {
        printf("Blue - ");
    }
     if(arry[n]==7)
    {
        printf("Violet - ");
    }
     if(arry[n]==8)
    {
        printf("Gray - ");
    }
     if(arry[n]==9)
    {
        printf("White - ");
    }
}

if (count == 2)             //finding the third color based on the total
{                           //number of digits
    printf("Black\n");
}
if (count == 3)
{
    printf("Brown\n");
}
if (count == 4)
{
    printf("Red\n");
}
if (count == 5)
{
    printf("Orange\n");
}
if (count == 6)
{
    printf("Yellow\n");
}
if (count == 7)
{
    printf("Green\n");
}
if (count == 8)
{
    printf("Blue\n");
}
if (count == 9)
{
    printf("Violet\n");
}

    }


                                          //if input is outside of range asking for new input
else if ( color < 1 || color > 99000000){
    printf("Integer outside of range. Enter valid integer.\n");

    do{

    status = scanf("%d", &color); //rechecking if the input is a number because it is already in the function
    if (status == 0){

        printf("ERROR: please enter a correct entry for an integer\n");
        fflush(stdin);
    }
 }while(status == 0);
    counting = color;   //resetting counting = to the new input
    check = 1;          // setting check = 1 so the function reloops with the new input
}
    }while (check == 1);

return;
    }
