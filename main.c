#include <stdio.h>
#include <stdlib.h>


struct book {
char title [255];
char author_name [50];
char ISBN [10];
int pages;
int year_published;
};

int parse_file(char filename[], struct book book_array[]);
void print_book(struct book book_array[] );

int main()
{
char filename[50];
struct book bookarray[360];

parse_file(filename,bookarray);
//printf("printing from main %s\n",book.author_name[0]);


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

printf("Test title is %s\n",book_array[4].title);
printf("Test author is %s\n",book_array[4].author_name);
printf("Test ISBN is %s\n",book_array[4].ISBN);
printf("Test page is %d\n",book_array[4].pages);
printf("Test Year is %d\n",book_array[4].year_published);
 return 1;
}
