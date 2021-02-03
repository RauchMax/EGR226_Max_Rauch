/**************************************************************************************
* Author: Max Rauch
* Course: EGR 226 - 902
* Date: 02/1/2021
* Project: Lab Two Part Two
* File: Main.c
* Description: This is a program that works as a search engine for a database of books
* The user decides on what file name to input then on how they would like to search.
* After they choose a search method their input is scanned and compared to all of the
* books in the data base. If there is a match the book and all of its information is
* printed to the screen. The user is then asked if they want to search again.
**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

                        //creating a structure to hold the read in information
struct book {
char title [255];
char author_name [50];
char ISBN [10];
int pages;
int year_published;
};


int parse_file(char filename[], struct book book_array[]);    //prototyping the functions
void print_book(struct book book_array[], int j);
void search_title (struct book book_array[], int num, char search_title[] );
void search_ISBN (struct book book_array[], int num, char search_ISBN[] );
void search_author (struct book book_array[], int num, char search_author[] );

int main()
{
int status,check,exit,decision;
int number = 360;               //making arrays to hold user input
char filename[50];
char title[50];
char author[50];
char ISBN[50];
struct book bookarray[360];

printf("Enter the file name.\n");  //asking and scanning the file name to be searched
scanf("%s", &filename);
//printf("File: %s\n", filename);

do{
do{

parse_file(filename,bookarray);    //calling the parse file function
//printf("printing from main %s\n",book.author_name[0]);

printf("Choose a search by method:\n0 = Title\n1 = Author Name\n2 = ISBN\n");


    do{

    status = scanf("%d", &decision);   //checking the input to see if it is a number
    if (status == 0){

                                //if it isn't a number the user is asked to renter
        printf("ERROR: please enter a correct entry for an integer\n");
        fflush(stdin);         //if incorrect this flushes the incorrect input
    }
 }while(status == 0);


 if(decision == 0){
    fflush(stdin);
    printf("Please enter the title of the book you are looking for.\n"); //asking for the title
    fgets(title, sizeof(title), stdin);                //getting the string including spaces

    search_title (bookarray, number, title);     //calling the search title function
    //printf("You chose 0\n");
    check = 0;                                    //setting check = 0 so we can exit the loop
 }
 if(decision == 1){
    fflush(stdin);
    printf("Please enter the author of the book you are looking for.\n"); //asking for the author
    fgets(author, sizeof(author), stdin);                 //getting the string including spaces
    search_author (bookarray, number, author);     //calling the search author function
    //printf("You chose 1\n");
    check = 0;                                    //setting check = 0 so we can exit the loop
 }
 if(decision == 2){
    printf("Please enter the ISBN of the book you are looking for.\n"); //asking for the ISBN
    scanf("%s", &ISBN);                           //getting the ISBN
    //printf("ISBN entered: %s\n",ISBN);
    search_ISBN (bookarray, number, ISBN);     //calling the search ISBN function
    check = 0;                                    //setting check = 0 so we can exit the loop
 }
 if(decision != 0 && decision != 1 && decision != 2){ //error checking so inly 0-2 work for decisions
    printf("Enter a valid integer.\n");
    check = 1;
 }


}while(check == 1);

printf("Would you like to search again?\n");  //checking to see if they want to search again
printf("Enter 1 for yes or 0 for no.\n");
scanf("%d", &exit);                           //scanning in their answer

}while(exit == 1);

printf("Exiting, have a nice day.\n");
    return 0;
}


/****| parse_fileFunction | *****************************************
* Brief: This function Sift through a file of books to populate
* an empty book array
* param:
* data:
* (char*) filename: file to open and parse
* (book*) book_array: array of book structures to populate
* return: (int) parse status, 1 if successful, 0 otherwise.
*************************************************************/

int parse_file(char filename[], struct book book_array[]) {
 FILE* infile = fopen(filename, "r"); // Attempt to open file
 if (infile == NULL) // Return 0 (failure) if file could not open
 return 0;

 char buffer[512]; // Create temporary string buffer variable
 int i = 0; // Indexer for book array

 while (fgets(buffer, 512, infile)) { // Loop collecting each line from the file
 char * ptr = strtok(buffer,","); // Parse string by commas and newline
 if(strcmp(ptr,"N/A")) // Validate string
 strcpy(book_array[i].title,ptr);// First parse is title

 ptr = strtok(NULL,",\n");
 if(strcmp(ptr,"N/A"))// Validate string
 strcpy(book_array[i].author_name,ptr);// second parse is author


 ptr = strtok(NULL,",\n");
 if(strcmp(ptr,"N/A"))// Validate string
 strcpy(book_array[i].ISBN,ptr);// third parse is ISBN


 ptr = strtok(NULL,",\n");
 if(strcmp(ptr,"N/A"))// Validate string
 book_array[i].pages = atoi(ptr); //using atoi function to convert the string to an int


 ptr = strtok(NULL,",\n");
  if(strcmp(ptr,"N/A"))// Validate string
 book_array[i].year_published = atoi(ptr); //using atoi function to convert the string to an int
 i++;
 }

 return 1;
}

/****| print_bookFunction | *****************************************
* Brief: This function takes an array of books and a number. The
* functions goes to that element of the array and prints that
* books information.
* param:
* data: a full array of books and an int of the specific book
* return: N/A prints from function
*************************************************************/

void print_book(struct book book_array[],int j ){

printf("\nThe title is %s\n",book_array[j].title);
printf("The author is %s\n",book_array[j].author_name);
printf("The ISBN is %s\n",book_array[j].ISBN);
printf("The page is %d\n",book_array[j].pages);
printf("The Year is %d\n\n",book_array[j].year_published);
 return;

}

/****| search_titleFunction | *****************************************
* Brief: This function takes a full array of books a number and a string.
* It first takes the "\n" off of the end of the string and then compares
* that string to every book title in the array. If there is a match it
* calls the print_book function.
* param:
* data: structure array of all books, int of number of books
*  and a string of the user input
* return: N/A prints from function
*************************************************************/

void search_title (struct book book_array[], int num, char search_title[] ){

int i,len;
char* p;

                             //checking if there is a \n that got saved with the string

len = strlen(search_title);
                             //setting len = to the length of the string
if(len > 0 && search_title[len-1] == '\n'){
                             //if the length is > 0 and it ends in \n remove the \n
    search_title[len-1] = '\0';
}



for(i=0; i<num; i++){           //comparing all of the titles to the input string
p = strstr(book_array[i].title,search_title);

if(p){                         //checking to see if p is null or if a match was found
    printf("Matched Title\n"); // if there was then calling the print function
    print_book(book_array,i);  // with the specific i that was matched
}
}

return;
}

/****| search_ISBNFunction | *****************************************
* Brief: This function takes a full array of books a number and a string.
* It compares the string to every books ISBN number in the array.
* If there is a match it calls the print_book function.
* param:
* data: structure array of all books, int of number of books
*  and a string of the user input
* return: N/A prints from function
*************************************************************/

void search_ISBN (struct book book_array[], int num, char search_ISBN[] ){

int i,comp=1;

for(i=0; i<num; i++){  //comparing all of the ISBNs to the input string
    comp = strcmp(search_ISBN, book_array[i].ISBN);
if(comp == 0){                 //if there is a match cop is 0
    printf("Matched ISBN\n");  //the print book function is called with i
    print_book(book_array,i);
}
}

return;
}

/****| search_authorFunction | *****************************************
* Brief: This function takes a full array of books a number and a string.
* It first takes the "\n" off of the end of the string and then compares
* that string to every book author in the array. If there is a match it
* calls the print_book function.
* param:
* data: structure array of all books, int of number of books
*  and a string of the user input
* return: N/A prints from function
*************************************************************/

void search_author (struct book book_array[], int num, char search_author[]){

int i,len;
char* l;

                             //checking if there is a \n that got saved with the string

len = strlen(search_author);
                             //setting len = to the length of the string
if(len > 0 && search_author[len-1] == '\n'){
                             //if the length is > 0 and it ends in \n remove the \n
    search_author[len-1] = '\0';
}


for(i=0; i<num; i++){    //comparing all of the authors to the input string
l = strstr(book_array[i].author_name,search_author);

if(l){                          //checking to see if l is null or if a match was found
    printf("Matched Author\n"); // if there was then calling the print function
    print_book(book_array,i);   // with the specific i that was matched
}
}

return;
}
