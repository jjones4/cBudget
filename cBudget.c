/*
 *
 * Name:       cBudget
 *
 * Purpose:    Keep track of a simple budget in a text file.
 *
 *             Each budget record will have the following:
 *
 *             Date        Amount          Type            Description
 *             ____        ______          ____            ___________
 *  
 *             mm/dd/yyyy  $xxxxxxx.yy	   Expense/Income  Description of record
 *
 *
 * Author:     jjones4
 *
 */


/* Preprocessing directives */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_RECORDS     10000
#define DATE_LEN        15
#define AMOUNT_LEN      15
#define TYPE_LEN        15
#define DESCRIPTION_LEN 115
#define FILE_NAME       "budget.txt"


/* Function prototypes (declarations) */
int read_str(char str[], int n);
void display_budget(FILE* fp, char date_str[], char amount_str[], char type_str[], char desc_str[]);
void save_data(FILE* fp, char date_str[], char amount_str[], char type_str[], char desc_str[]);


int main(void)
{
   FILE *fp;
   int num_records = 0;

   while(1) {
      char date_str[DATE_LEN + 2], amount_str[AMOUNT_LEN + 2];
      char type_str[TYPE_LEN + 2], desc_str[DESCRIPTION_LEN + 2];
      char clear_input[2];

      if(num_records > MAX_RECORDS) {

         printf("Too many records\n");
         exit (EXIT_FAILURE);
      }

      /* Open file stream for budget data text file */
      fp = fopen(FILE_NAME, "a+");
      if(fp == NULL) {
         printf("Can't open %s\n", FILE_NAME);
         exit(EXIT_FAILURE);
      }

      /* User menu */
      printf("\nType (1) to see your budget, (2) to add a record, or (3) to save and quit: ");
      
      int c = getchar();

      printf("\n");

      /* Display full budget file (option 1) */
      if(c == '1') {

         read_str(clear_input, 1);
         
         printf("%-15s%-15s%-10s%-115s\n", "Date", "Amount", "Type", "Description");
         printf("%-15s%-15s%-10s%-115s\n", "----", "------", "----", "-----------");
         display_budget(fp, date_str, amount_str, type_str, desc_str);
         printf("\n");
      }
   
      /* Create new budget record (option 2) */
      else if(c == '2') {

         read_str(clear_input, 1);

         printf("Enter transaction date (mm/dd/yyyy): ");
         read_str(date_str, DATE_LEN);
         printf("Enter transaction amount: ");
         read_str(amount_str, AMOUNT_LEN);
         printf("Enter transaction type (Expense/Income): ");
         read_str(type_str, TYPE_LEN);
         printf("Enter transaction description: ");
         read_str(desc_str, DESCRIPTION_LEN);

         save_data(fp, date_str, amount_str, type_str, desc_str);
      }

      /* Exit program (option 3) */
      else if(c == '3') {

         exit(EXIT_SUCCESS);
      }

      /* Check for invalid option */
      else {

         read_str(clear_input, 1);

         printf("You entered an invalid option. Try again.\n");
         continue;
      }

      num_records++;
   }

   fclose(fp);
   return 0;
}

/* Save budget record into budget.txt */
void save_data(FILE* fp, char date_str[], char amount_str[], char type_str[], char desc_str[]) {

   /* Write record to budget.txt */
   fprintf(fp, "%s", date_str);
   fprintf(fp, "\n");
   fprintf(fp, "%s", amount_str);
   fprintf(fp, "\n");
   fprintf(fp, "%s", type_str);
   fprintf(fp, "\n");
   fprintf(fp, "%s", desc_str);
   fprintf(fp, "\n");
}

/* Display budget file entries on command line */
void display_budget(FILE* fp, char date_str[], char amount_str[], char type_str[], char desc_str[]) {

   int i = 1;
   for(; ;) {
      
      /* Too many records to display, stop */
      if(i > 32767) {
         printf("Too many records\n");
         exit(EXIT_FAILURE);
      }

      /* First, fifth, ninth, etc. lines of file are dates */
      if(i % 4 == 1) {
         if(fgets(date_str, DATE_LEN, fp) == NULL)
            break;
         /* Remove new line character from fgets for displaying data */
         date_str[strlen(date_str) - 1] = '\0';
         i++;
      }
      /* Second, sixth, tenth, etc. lines of file are amounts */
      if(i % 4 == 2) {
         if(fgets(amount_str, AMOUNT_LEN, fp) == NULL)
            break;
         /* Remove new line character from fgets for displaying data */
         amount_str[strlen(amount_str) - 1] = '\0';
         i++;
      }
      /* Third, seventh, elevent, etc. lines of file are types */
      if(i % 4 == 3) {
         if(fgets(type_str, TYPE_LEN, fp) == NULL)
            break;
         /* Remove new line character from fgets for displaying data */
         type_str[strlen(type_str) - 1] = '\0';
         i++;
      }
      /* Fourth, eighth, twelfth, etc. lines of file are descriptions */
      if(i % 4 == 0) {
         if(fgets(desc_str, DESCRIPTION_LEN, fp) == NULL)
            break;
         /* Remove new line character from fgets for displaying data */
         desc_str[strlen(desc_str) -1] = '\0';
         i++;
      }

      /* Print a whole budget record (on one line) */
      printf("%-15s%-15s%-10s%-115s\n", date_str, amount_str, type_str, desc_str);
   }
}

/* Read user input; store part of record into array */
read_str(char s[], int n) {

   int c, i = 0;

   while((c = getchar()) != '\n') {
      if(i < n) {
         s[i++] = c;
      }
   }
   s[i] = '\0';

   return i;
}
