/*
 *
 * Name:    iBudget
 *
 * Purpose: Keep track of a simple budget in a text file.
 *
 *          Each budget record will have the following,
 *          where e = expense, and i = income.
 *
 *          Date	Amount		Type		Description
 *          ____        ______          ____            ___________
 *
 *          mm/dd/yyyy	$xxxxxxx.yy	e/i	        Description of record
 *
 *
 * Author:  jjones4
 *
 */

/* Preprocessing directives */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS     100
#define DATE_LEN        10
#define AMOUNT_LEN      10
#define TYPE_LEN        1
#define DESCRIPTION_LEN 50
#define NUM_TABS        6

/* Function prototypes (declarations) */
int read_str(char str[], int n);
void display_budget(char budget_records[MAX_RECORDS][DATE_LEN \
   + AMOUNT_LEN + TYPE_LEN + DESCRIPTION_LEN + NUM_TABS + 1], int n);

int main(void)
{
   char records[MAX_RECORDS][DATE_LEN + AMOUNT_LEN + TYPE_LEN \
      + DESCRIPTION_LEN + NUM_TABS + 1];
   char date_str[DATE_LEN + 1], amount_str[AMOUNT_LEN + 1];
   char type_str[TYPE_LEN + 1], desc_str[DESCRIPTION_LEN + 1];
   int month, day, year, num_records = 0;
   float amount;

   while(1) {

      if(num_records == MAX_RECORDS) {
         printf("Too many records\n");
         return (EXIT_FAILURE);
      }

      printf("\n");

      printf("Enter transaction date, mm/dd/yyyy: ");
      read_str(date_str, DATE_LEN);
      
      /* Enter q or Q to exit */
      if(strcmp(date_str, "Q") == 0 || strcmp(date_str, "q") == 0) {

         /* If user quits immediately, do not print records */
         if(num_records == 0) {
            break;
         }

         /* Print records when user quits */
         display_budget(&records[0], num_records);

         break;
      }

      printf("Enter transaction amount: ");
      read_str(amount_str, AMOUNT_LEN);

      /* Enter q or Q to exit */
      if(strcmp(amount_str, "Q") == 0 || strcmp(amount_str, "q") == 0) {

         /* If user quits immediately, do not print records */
         if(num_records == 0) {
            break;
         }

         /* Print records when user quits */
         display_budget(&records[0], num_records);

         break;
      }

      printf("Enter transaction type, e or i: ");
      read_str(type_str, TYPE_LEN);

      /* Enter q or Q to exit */
      if(strcmp(type_str, "Q") == 0 || strcmp(type_str, "q") == 0) {

         /* If user quits immediately, do not print records */
         if(num_records == 0) {
            break;
         }

         /* Print records when user quits */
         display_budget(&records[0], num_records);

         break;
      }

      printf("Enter transaction description: ");
      read_str(desc_str, DESCRIPTION_LEN);

      /* Enter q or Q to exit */
      if(strcmp(desc_str, "Q") == 0 || strcmp(desc_str, "q") == 0) {

         /* Print records when user quits */
         display_budget(&records[0], num_records);

         break;
      }

      /* Fill the records array with each part of the record */
      int i = 0;
      for(i = 0; i < DATE_LEN + AMOUNT_LEN + TYPE_LEN + DESCRIPTION_LEN + NUM_TABS;) {

         int j = 0;

         /* Fill the record array with the date */
         while(j < DATE_LEN) {
            records[num_records][i] = date_str[j];
            i++;
            j++;
         }
         records[num_records][i] = '\t';
         i++;

         /* Fill the record array with the amount */
         j = 0;
         while(amount_str[j] != '\0') {
            records[num_records][i] = amount_str[j];
            i++;
            j++;
         }
         records[num_records][i] = '\t';
         i++;
         records[num_records][i] = '\t';
         i++;

         /* Fill the record array with the type */
         j = 0;
         while(j < TYPE_LEN) {
            records[num_records][i] = type_str[j];
            i++;
            j++;
         }
         records[num_records][i] = '\t';
         i++;
         records[num_records][i] = '\t';
         i++;

         /* Fill the record array with the description */
         j = 0;
         while(j < DESCRIPTION_LEN) {
            records[num_records][i] = desc_str[j];
            i++;
            j++;
         }
         records[num_records][i] = '\t';
         i++;
         records[num_records][i] = '\t';
         i++;
      }
      records[num_records][i] = '\0';
      num_records++;
   }

   return 0;
}

/* read_str stores input data into given array */
int read_str(char s[], int n) {

   int c, i = 0;

   while((c = getchar()) != '\n') {
      if(i < n) {
         s[i++] = c;
      }
   }
   s[i] = '\0';

   return i;
}

/* Display budget */
void display_budget(char records[MAX_RECORDS][DATE_LEN \
   + AMOUNT_LEN + TYPE_LEN + DESCRIPTION_LEN + NUM_TABS + 1], int n) {

   printf("\nDate\t\tAmount\t\tType\t\tDescription\n");
   printf("----\t\t------\t\t----\t\t-----------\n");

   int j, i = 0;
   for(int i = 0; i < n; i++) {

      j = 0;
      while(records[i][j] != '\0') {
         printf("%c", records[i][j]);
          j++;
      }
      printf("\n");
   }

   printf("\n");
}
