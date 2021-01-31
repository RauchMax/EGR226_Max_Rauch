#include <stdio.h>
#include <stdlib.h>


struct book {
char title [255];
char author_name [50];
char ISBN [10];
int pages;
int year_published;
};

/*
struct author{
char word1[50];
char word2[50];
char word3[50];
char word4[50];
};
*/

int parse_file(char filename[], struct book book_array[]);
void print_book(struct book book_array[], int j);
void search_title (struct book book_array[], int num, char search_title[] );
void search_ISBN (struct book book_array[], int num, char search_ISBN[] );
void search_author (struct book book_array[], int num, char search_author[] );

int main()
{
int status,check,exit,decision;
int number = 360;
char filename[50];
char title[50];
char author[50];
char ISBN[50];
struct book bookarray[360];
//struct author authorarray[10];

do{
do{

parse_file(filename,bookarray);
//printf("printing from main %s\n",book.author_name[0]);

printf("Choose a search by method:\n0 = Title\n1 = Author Name\n2 = ISBN\n");


    do{

    status = scanf("%d", &decision);   //checking the input to see if it is a number
    if (status == 0){     //i am checking this in the main because my function is
                                    //type int and cant accept a character
                                //if it isn't a number the user is asked to renter
        printf("ERROR: please enter a correct entry for an integer\n");
        fflush(stdin);         //if incorrect this flushes the incorrect input
    }
 }while(status == 0);


 if(decision == 0){
    fflush(stdin);
    printf("Please enter the title of the book you are looking for.\n");
    fgets(title, sizeof(title), stdin);

    search_title (bookarray, number, title);
    //printf("You chose 0\n");
    check = 0;
 }
 if(decision == 1){
    fflush(stdin);
    printf("Please enter the author of the book you are looking for.\n");
    fgets(author, sizeof(author), stdin);
    search_author (bookarray, number, author);
    //printf("You chose 1\n");
    check = 0;
 }
 if(decision == 2){
    printf("Please enter the ISBN of the book you are looking for.\n");
    scanf("%s", &ISBN);
    //printf("ISBN entered: %s\n",ISBN);
    search_ISBN (bookarray, number, ISBN);
    //printf("You chose 2\n");
    check = 0;
 }
 if(decision != 0 && decision != 1 && decision != 2){
    printf("Enter a valid integer.\n");
    check = 1;
 }
/*
parse_file(filename,bookarray);
//printf("printing from main %s\n",book.author_name[0]);
*/
//print_book(bookarray);


}while(check == 1);

printf("Would you like to search again?\n");
printf("Enter 1 for yes or 0 for no.\n");
scanf("%d", &exit);

}while(exit == 1);

printf("Exiting, have a nice day.\n");
    return 0;
}


/*-----------------------------------------------------------
* Function: parse_file
* Description: Sift through a file of books to populate
* an empty book array
* Inputs:
* (char*) filename: file to open and parse
* (book*) book_array: array of book structures to
* populate
* Outputs:
* (int) parse status, 1 if successful, 0 otherwise.
*---------------------------------------------------------*/
int parse_file(char filename[], struct book book_array[]) {
 FILE* infile = fopen("Books.txt", "r"); // Attempt to open file
 if (infile == NULL) // Return 0 (failure) if file could not open
 return 0;

 char buffer[512]; // Create temporary string buffer variable
 int i = 0; // Indexer for book array

 while (fgets(buffer, 512, infile)) { // Loop collecting each line from the file
 char * ptr = strtok(buffer,","); // Parse string by commas and newline
 if(strcmp(ptr,"N/A")) // Validate string
 strcpy(book_array[i].title,ptr);// First parse is title

 ptr = strtok(NULL,",\n");
 if(strcmp(ptr,"N/A"))
 strcpy(book_array[i].author_name,ptr);
 // Todo: Handle null value

 ptr = strtok(NULL,",\n");
 if(strcmp(ptr,"N/A"))
 strcpy(book_array[i].ISBN,ptr);
 // Todo: Handle null value

 ptr = strtok(NULL,",\n");
 if(strcmp(ptr,"N/A"))
 book_array[i].pages = atoi(ptr);
 // Todo: Handle null value

 ptr = strtok(NULL,",\n");
  if(strcmp(ptr,"N/A"))
 book_array[i].year_published = atoi(ptr);
 // Todo: Handle null value
 i++;
 }
/*
printf("Test title is %s\n",book_array[1].title);
printf("Test author is %s\n",book_array[1].author_name);
printf("Test ISBN is %s\n",book_array[1].ISBN);
printf("Test page is %d\n",book_array[1].pages);
printf("Test Year is %d\n",book_array[1].year_published);
*/
//print_book(book_array);
 return 1;
}


void print_book(struct book book_array[],int j ){

printf("\nThe title is %s\n",book_array[j].title);
printf("The author is %s\n",book_array[j].author_name);
printf("The ISBN is %s\n",book_array[j].ISBN);
printf("The page is %d\n",book_array[j].pages);
printf("The Year is %d\n\n",book_array[j].year_published);
 return;

}



void search_title (struct book book_array[], int num, char search_title[] ){

int i,comp=1;


int len = strlen(search_title);
// len-1 is the last character before the original \0
if(len > 0 && search_title[len-1] == '\n'){
    // remove the new-line by ending the string sooner
    search_title[len-1] = '\0';
}



for(i=0; i<num; i++){
    comp = strcmp(search_title, book_array[i].title);
if(comp == 0){
    printf("Matched Title\n");
    print_book(book_array,i);
}
}

return;
}



void search_ISBN (struct book book_array[], int num, char search_ISBN[] ){

int i,comp=1;

for(i=0; i<num; i++){
    comp = strcmp(search_ISBN, book_array[i].ISBN);
if(comp == 0){
    printf("Matched ISBN\n");
    print_book(book_array,i);
}
}

return;
}


void search_author (struct book book_array[], int num, char search_author[]){

int i,comp=1;


int len = strlen(search_author);
// len-1 is the last character before the original \0
if(len > 0 && search_author[len-1] == '\n'){
    // remove the new-line by ending the string sooner
    search_author[len-1] = '\0';
}


for(i=0; i<num; i++){
    comp = strcmp(search_author, book_array[i].author_name);
if(comp == 0){
    printf("Matched author\n");
    print_book(book_array,i);
}
}

/*
char * ptr = strtok(buffer," "); // Parse string by space
 if(strcmp(ptr,"N/A")) // Validate string
 strcpy(book_array[i].title,ptr);// First parse is title
*/

return;
}
