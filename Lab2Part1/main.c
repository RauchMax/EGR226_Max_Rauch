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
void getColorBands(char *Col1, char *Col2, char *Col3, char *Col4);
void calcResistance(char, char, char, char);



int main()
{
char color1,color2,color3,color4;
int status,exit,check;
int Input,decision;

do{

prompt();        //calling the prompt function to print and ask for input

do{
 do{

    status = scanf("%d", &decision);   //checking the input to see if it is a number
    if (status == 0){
                                //if it isn't a number the user is asked to renter
        printf("ERROR: please enter a correct entry for an integer\n");
        fflush(stdin);         //if incorrect this flushes the incorrect input
    }
 }while(status == 0);

   //printf("You entered %d\n",Input);
if(decision == 1){  // checking to see if they chose option 1
check = 0;
printf("Enter an integer between 1 and 99,000,000 for a color code.\n");
do{

    status = scanf("%d", &Input);   //checking the input to see if it is a number
    if (status == 0){     //i am checking this in the main because my function is
                                    //type int and cant accept a character
                                //if it isn't a number the user is asked to renter
        printf("ERROR: please enter a correct entry for an integer\n");
        fflush(stdin);         //if incorrect this flushes the incorrect input
    }
 }while(status == 0);
CalcResistorColors(Input);          //calling the resistor color function
check = 0;
}
if(decision == 0){ // checking to see if they chose option 0
printf("Please enter four color characters.\n");
scanf(" %c %c %c %c", &color1, &color2, &color3, &color4); //scanning the characters
//printf("character 1 is %c\n",color1);

getColorBands(&color1, &color2, &color3, &color4); //calling the getcolorband function

printf("character 1 after function is %c\n",color1); //printing the characters after the function
printf("character 2 after function is %c\n",color2);
printf("character 3 after function is %c\n",color3);
printf("character 4 after function is %c\n",color4);

calcResistance(color1, color2, color3, color4);  // calling the calcResistor function

check = 0;
}
if(decision != 0 && decision != 1){ // checking to see if they entered a number other than 1 or 0
printf("Enter 0 or 1\n");
check = 1;
}
}while(check ==1); // running loop until valid input

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
 printf("| D       | Gold  |            |*0.1       |+/- 5%%   |\n");
 printf("| S       | Silver|            |*0.01      |+/- 10%%  |\n");
 printf("-------------------------------------------------------\n\n");

 printf("Would you like to convert a color-code to a resistance value or determine the color-code from a resistance value.\n");
 printf("Enter 0 for color-code to a resistance value or 1 for determining the color-code from a resistance value.\n");
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



/****| GetColorBandsFunction | *****************************************
* Brief: This function takes 4 pointers to characters as parameters. This
* function compares each character to an array of characters to see if it
* is valid. It asks for new input if a character is invalid. It scans in
* the new input and prints it to the screen. Since  these are called by
* reference this function can “return” all 4 values of user input in one
* function call.
* param:
* data: 4 painters to characters
* return: N/A prints from function
*************************************************************/

void getColorBands(char *Col1, char *Col2, char *Col3, char *Col4){
    /*
printf("test Col1 is %c\n", *Col1);
printf("test Col2 is %c\n", *Col2);
printf("test Col3 is %c\n", *Col3);
printf("test Col4 is %c\n", *Col4);
*Col1 = 'K';
*/
int i,test1=0,test2=0,test3=0,test4=0;

char Letters12[12] = {'K','N','R','O','Y','G','B','V','E','W'};
char Letters3[12] = {'K','N','R','O','Y','G','B','V','D','S'};
char Letters4[12] = {'K','N','G','B','V','E','D','S'};

// creating arrays of the valid input for color 1,2
//creating two more arrays of valid input for colors 3 and 4

do{
for (i = 0; i<12; i++){
    //printf("test array[%d] = %c\n",i,Letters[i]);
    if(*Col1 == Letters12[i]){
    test1 = 1;
    printf("working\n\n"); //running through the array to see if color 1 matches any
    }
}
if(test1 == 0){
    printf("Please enter a valid character for color 1.\n");
    fflush(stdin);
    scanf("%c",&*Col1);
    printf("new Col1 is %c\n", *Col1);
    test1 = 0;
}
}while(test1 == 0); //if color 1 doesn't match asking for new input and scanning it in
                    //doing this loop until there is valid input
do{
for (i = 0; i<12; i++){
    if(*Col2 == Letters12[i]){
    test2 = 1;
    printf("working\n\n"); //running through the array to see if color 2 matches any
    }
}
if(test2 == 0){
    printf("Please enter a valid character for color 2.\n");
    fflush(stdin);
    scanf("%c",&*Col2);
    printf("new Col2 is %c\n", *Col2);
    test2 = 0;
}
}while(test2 == 0); //if color 2 doesn't match asking for new input and scanning it in
                    //doing this loop until there is valid input
do{
for (i = 0; i<12; i++){
    if(*Col3 == Letters3[i]){
    test3 = 1;
    printf("working\n\n"); //running through the array to see if color 3 matches any
    }
}
if(test3 == 0){
    printf("Please enter a valid character for color 3.\n");
    fflush(stdin);
    scanf("%c",&*Col3);
    printf("new Col3 is %c\n", *Col3);
    test3 = 0;
}
}while(test3 == 0); //if color 3 doesn't match asking for new input and scanning it in
                    //doing this loop until there is valid input
do{
for (i = 0; i<12; i++){
    if(*Col4 == Letters4[i]){
    test4 = 1;
    printf("working\n\n"); //running through the array to see if color 4 matches any
    }
}
if(test4 == 0){
    printf("Please enter a valid character for color 4.\n");
    fflush(stdin);
    scanf("%c",&*Col4);
    printf("new Col4 is %c\n", *Col4);
    test4 = 0;
}
}while(test4 == 0); //if color 4 doesn't match asking for new input and scanning it in
                    //doing this loop until there is valid input
return;
}


/****| calcResistanceFunction | *****************************************
* Brief: This function takes 4 characters as parameters. This
* function compares each character to an array of characters. When there is
* a match it prints the corresponding number for the first character. When
* the second character matches it saves the spot in the array as j. When
* the third character matches it prints the jth number times the ith multiplier.
* The forth character is used to find the corresponding tolerance, and the whole
* resistance and tolerance are printed to the screen.
* param:
* data: 4 characters
* return: N/A prints from function
*************************************************************/

void calcResistance(char Col1, char Col2, char Col3, char Col4){
int i,j,k;
char Letters[12] = {'K','N','R','O','Y','G','B','V','E','W','D','S'};
//made array of all posible characters
int Numbers [12] = {0,1,2,3,4,5,6,7,8,9,0,0};
//made an array of the numbers
int Mult[12] = {1,10,100,1000,10000,100000,1000000,10000000,1,1,.1,.01};
//made an array of the multipliers

printf("The resistor value is ");

for(i=0; i<12; i++){ //checking to see when color 1 matches a letter
    if(Col1 == Letters[i]){
        printf("%d",Numbers[i]); //when it matches it prints that number
    }
}

for(i=0; i<12; i++){ //checking to see when color 2 matches a letter
    if(Col2 == Letters[i]){
        //printf("%d",Numbers[i]);
        j = i;
    }  //when it matches it sets j equal to i to save that location in the array
}



for(i=0; i<12; i++){ //checking to see when color 3 matches a letter
    if(Col3 == Letters[i]){
        printf("%d Ohms ",Numbers[j]*Mult[i]);
    }
} //when it matches it prints the number that matched color 2 times the multiplier of color 3

for(i=0; i<12; i++){  //checking to see when color 4 matches a letter
    if(Col4 == Letters[i]){
        k=i;
    }  //when it matches it sets k equal to i to save that location in the array
}

//checking to see what k is equal to and printing the corresponding tolerance
if(k==0){
   printf("with a tolerance of +/- 1%%\n");
}
if(k==1){
   printf("with a tolerance of +/- 2%%\n");
}
if(k==5){
   printf("with a tolerance of +/- 0.5%%\n");
}
if(k==6){
   printf("with a tolerance of +/- 0.25%%\n");
}
if(k==7){
   printf("with a tolerance of +/- 0.1%%\n");
}
if(k==8){
   printf("with a tolerance of +/- 0.05%%\n");
}
if(k==10){
   printf("with a tolerance of +/- 5%%\n");
}
if(k==11){
   printf("with a tolerance of +/- 10%%\n");
}
if(k==3){
   printf("\n");
}
if(k==4){
   printf("\n");
}
if(k==9){
   printf("\n");
}

//printf("j = %d\n",j);

return;
}
