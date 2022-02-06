/*
 *
 * Name:       cBudget
 *
 * Purpose:    Keep track of a simple budget in a text file.
 *
 *             Each budget record will have the following:
 *
 *             ID, Date, Amount, Type, and Description
 *
 * Author:     jjones4
 *
 * Copyright (c) 2022 Jerad Jones
 * This file is part of cBudget.  cBudget may be freely distributed
 * under the MIT license.  For all details and documentation, see
 * https://github.com/jjones4/cBudget
 *
 */

/* Preprocessing directives */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS     8192
#define NUM_FIELDS      4
#define MAX_LINES	32767
#define DATE_LEN        15
#define AMOUNT_LEN      15
#define TYPE_LEN        15
#define DESCRIPTION_LEN 115
#define FILE_NAME       "budget.txt"
#define TEMP_FILE	"temp.txt"

/* Function prototypes - CRUD operations */
void create_record(FILE* fp);
void read_budget(FILE* fp);
void update_record(FILE* fp, FILE* temp_pointer);
void delete_record(FILE* fp, FILE* temp_pointer);
int read_str(char str[], int n);

int main(void)
{
   FILE* fp;
   FILE* temp_pointer;
   int num_records = 0;

   /* Loop to keep returning to main menu */
   while(1) {

      char clear_input[2];

      if(num_records > MAX_RECORDS) {
         printf("Too many records\n");
         exit (EXIT_FAILURE);
      }

      /* Menu */
      printf("\nChoose from the following options:\n");
      printf("\n\t(1) Display your budget\n\t(2) Create a new record");
      printf("\n\t(3) Delete a record\n\t(4) Update an existing record");
      printf("\n\t(5) Quit\n");
      printf("\nType your option: ");

      /* Display full budget (option 1) */
      int c = getchar();
      if(c == '1') {

         /* Open file stream for budget data text file */
         fp = fopen(FILE_NAME, "r");
         if(fp == NULL) {
            printf("Can't open %s\n", FILE_NAME);
            exit(EXIT_FAILURE);
         }

         printf("\n");
         read_budget(fp);
      }
   
      /* Create new budget record (option 2) */
      else if(c == '2') {

         /* Open file stream for budget data text file */
         fp = fopen(FILE_NAME, "a+");
         if(fp == NULL) {
            printf("Can't open %s\n", FILE_NAME);
            exit(EXIT_FAILURE);
         }

         create_record(fp);
      }

      /* Remove a record (option 3) */
      else if(c == '3') {

         /* Open file stream for budget data text file */
         fp = fopen(FILE_NAME, "r");
         if(fp == NULL) {
            printf("Can't open %s\n", FILE_NAME);
            exit(EXIT_FAILURE);
         }

         /* 
          * Open temp file for holding data after the record
          * has been removed
          */
         temp_pointer = fopen(TEMP_FILE, "w");
         if(temp_pointer == NULL) {
            printf("Can't open %s\n", TEMP_FILE);
            exit(EXIT_FAILURE);
         }
         
         delete_record(fp, temp_pointer);
      }

      /* Update an existing record (option 4) */
      else if(c == '4') {

         /* Open file stream for budget data text file */
         fp = fopen(FILE_NAME, "r");
         if(fp == NULL) {
            printf("Can't open %s\n", FILE_NAME);
            exit(EXIT_FAILURE);
         }

         /* 
          * Open temp file for holding data after the record
          * has been removed
          */
         temp_pointer = fopen(TEMP_FILE, "w");
         if(temp_pointer == NULL) {
            printf("Can't open %s\n", TEMP_FILE);
            exit(EXIT_FAILURE);
         }
         
         update_record(fp, temp_pointer);
      }

      /* Exit program (option 5) */
      else if(c == '5') {

         fclose(fp);
         exit(EXIT_SUCCESS);
      }
      /* Check for invalid option */
      else {

         read_str(clear_input, 1);
         printf("\nYou entered an invalid option. Try again.\n");
         continue;
      }

      num_records++;
   }

   fclose(fp);
   return 0;
}

/* Update an existing record */
void update_record(FILE* fp, FILE* temp_pointer) {

   int i = 1, file_line_num = 0, line_num = 1, ctr = 0, option = 0;

   /* Declare arrays for original records */
   char date_str[DATE_LEN + 2], amount_str[AMOUNT_LEN + 2];
   char type_str[TYPE_LEN + 2], desc_str[DESCRIPTION_LEN + 2];

   /* Declare arrays for updated records */
   char new_date_str[DATE_LEN + 2], new_amount_str[AMOUNT_LEN + 2];
   char new_type_str[TYPE_LEN + 2], new_desc_str[DESCRIPTION_LEN + 2];

   char clear_input[2];

   while(1) {
      printf("\nEnter the line number of the record you want to update: ");
   
      scanf("%d", &line_num);

      if(line_num > 32767 || line_num < 1) {
         printf("\nInvalid line number\n\n");
         continue;
      }

      while(1) {

         printf("\nChoose from the following options:\n");
         printf("\n\t(1) Change the date\n\t(2) Change the amount");
         printf("\n\t(3) Change the type\n\t(4) Change the description");
         printf("\n\nType your option: ");

         read_str(clear_input, 1);
         scanf("%d", &option);

         if(option > NUM_FIELDS || option < 1) {
            printf("Invalid option\n\n");
            continue;
         }

         read_str(clear_input, 1);

         /* Calculate file's line number that will be modified */
         file_line_num = line_num * NUM_FIELDS - 3 + option - 1;

         /* If user is trying to change the date field */
         if(file_line_num % NUM_FIELDS == 1) {
            printf("\nEnter the new date: ");
            read_str(new_date_str, DATE_LEN);
         }
         /* If user is trying to change the amount field */
         else if(file_line_num % NUM_FIELDS == 2) {
            printf("\nEnter the new amount: ");
            read_str(new_amount_str, AMOUNT_LEN);
         }
         /* If user is trying to change the type field */
         else if(file_line_num % NUM_FIELDS == 3) {
            printf("\nEnter the new type: ");
            read_str(new_type_str, TYPE_LEN);
         }
         /* If user is trying to change the description field */
            else if(file_line_num % NUM_FIELDS == 0) {
            printf("\nEnter the new description: ");
            read_str(new_desc_str, DESCRIPTION_LEN);
         }

         while(!feof(fp)) {

            /* Too many records, stop */
            if(i > 32767) {
               printf("Too many records\n");
               exit(EXIT_FAILURE);
            }

            /* First, fifth, ninth, etc. lines of file are dates */
            if(fgets(date_str, DATE_LEN, fp) == NULL)
               break;

            /* Skip line at given line number when populating temp file */
            ctr++;
            if(ctr != file_line_num) {
               fprintf(temp_pointer, "%s", date_str);
            }
            /* Populate temp file with new date given by user */
            else {
               fprintf(temp_pointer, "%s", new_date_str);
               fprintf(temp_pointer, "\n");
            }
            i++;
               
            /* Second, sixth, tenth, etc. lines of file are amounts */
               

            if(fgets(amount_str, AMOUNT_LEN, fp) == NULL)
               break;

            /* Skip line at given line number when populating temp file */
            ctr++;
            if(ctr != file_line_num) {
               fprintf(temp_pointer, "%s", amount_str);
            }
            /* Populate temp file with new amount given by user */
            else {
               fprintf(temp_pointer, "%s", new_amount_str);
               fprintf(temp_pointer, "\n");
            }
            i++;
               
            /* Third, seventh, elevent, etc. lines of file are types */
            if(fgets(type_str, TYPE_LEN, fp) == NULL)
               break;

                  

            /* Skip line at given line number when populating temp file */
            ctr++;
            if(ctr != file_line_num) {
               fprintf(temp_pointer, "%s", type_str);
            }
            /* Populate temp file with new type given by user */
            else {
               fprintf(temp_pointer, "%s", new_type_str);
               fprintf(temp_pointer, "\n");
            }
            i++;
               
            /* Fourth, eighth, twelfth, etc. lines of file are descriptions */
            if(fgets(desc_str, DESCRIPTION_LEN, fp) == NULL)
               break;

            /* Skip line at given line number when populating temp file */
            ctr++;
            if(ctr != file_line_num) {
               fprintf(temp_pointer, "%s", desc_str);
            }
            /* Populate temp file with new description given by user */
            else {
               fprintf(temp_pointer, "%s", new_desc_str);
               fprintf(temp_pointer, "\n");
            }
            i++;
         }

         fclose(temp_pointer);
         fclose(fp);
         remove(FILE_NAME);
         rename(TEMP_FILE, FILE_NAME);
         printf("\nRecord %d successfully updated!\n", line_num);
         return;
      }
   }
}

/* Remove a record */
void delete_record(FILE* fp, FILE* temp_pointer) {

   int line_num = 0, file_line_num = 0, ctr = 0;
   int option;

   /* Declare arrays for each part of record */
   char date_str[DATE_LEN + 2], amount_str[AMOUNT_LEN + 2];
   char type_str[TYPE_LEN + 2], desc_str[DESCRIPTION_LEN + 2];
   char clear_input[2];

   while(1) {

      printf("Enter the line number of the record you want to remove: ");
   
      scanf("%d", &line_num);

      if(line_num > MAX_RECORDS || line_num < 1) {
         printf("\nInvalid line number\n\n");
         continue;
      }
   
      printf("\nYou are about to remove line %d. Are you sure? (Y/y, N/n): ", 
              line_num);

      /* Clear input */
      read_str(clear_input, 1);

      option = getchar();
      if(option == 'Y' || option == 'y') {

         file_line_num = line_num * NUM_FIELDS - 3;

         /*
          * Copy all contents of budget.txt to temporary file exept the lines
          * of the record you want to delete
          */
         while(!feof(fp)) {

            /* Too many records, stop */
            if(ctr > MAX_LINES) {
               printf("Too many records\n");
               exit(EXIT_FAILURE);
            }

            /* First, fifth, ninth, etc. lines of file are dates */
            if(fgets(date_str, DATE_LEN, fp) == NULL)
               break;
                  
            /* Skip lines at given line number when populating temp file */
            ctr++;
            if(ctr != file_line_num) {
               fprintf(temp_pointer, "%s", date_str);
            }

            /* Second, sixth, tenth, etc. lines of file are amounts */
            if(fgets(amount_str, AMOUNT_LEN, fp) == NULL)
               break;

            /* Skip lines at given line number when populating temp file */
            ctr++;
            if(ctr != file_line_num + 1) {
               fprintf(temp_pointer, "%s", amount_str);
            }
            
            /* Third, seventh, elevent, etc. lines of file are types */
            if(fgets(type_str, TYPE_LEN, fp) == NULL)
               break;

            /* Skip lines at given line number when populating temp file */
            ctr++;
            if(ctr != file_line_num + 2) {
               fprintf(temp_pointer, "%s", type_str);
            }
            
            /* Fourth, eighth, twelfth, etc. lines of file are descriptions */
            if(fgets(desc_str, DESCRIPTION_LEN, fp) == NULL)
               break;

            /* Skip lines at given line number when populating temp file */
            ctr++;
            if(ctr != file_line_num + 3) {
               fprintf(temp_pointer, "%s", desc_str);
            }
         }

         /* Close files so record deletion is saved */
         fclose(fp);
         fclose(temp_pointer);

         /* Rename temp file to original budget file name */
         remove(FILE_NAME);
         rename(TEMP_FILE, FILE_NAME);

         printf("\nRecord %d cleared successfully!\n", line_num);
         read_str(clear_input, 1);
         return;
      }
      else {
         printf("\nNo records removed!\n");
         read_str(clear_input, 1);
         fclose(fp);
         fclose(temp_pointer);
         return;
      }
   }
}

/* Save budget record into budget.txt */
void create_record(FILE* fp) {

   /* Declare arrays for each part of the record */
   char date_str[DATE_LEN + 2], amount_str[AMOUNT_LEN + 2];
   char type_str[TYPE_LEN + 2], desc_str[DESCRIPTION_LEN + 2];

   /* Clear input stream */
   char clear_input[2];
   read_str(clear_input, 1);

   printf("Enter transaction date (mm/dd/yyyy): ");
   read_str(date_str, DATE_LEN);
   printf("Enter transaction amount: ");
   read_str(amount_str, AMOUNT_LEN);
   printf("Enter transaction type (Expense/Income): ");
   read_str(type_str, TYPE_LEN);
   printf("Enter transaction description: ");
   read_str(desc_str, DESCRIPTION_LEN);

   /* Write record to budget.txt */
   fprintf(fp, "%s", date_str);
   fprintf(fp, "\n");
   fprintf(fp, "%s", amount_str);
   fprintf(fp, "\n");
   fprintf(fp, "%s", type_str);
   fprintf(fp, "\n");
   fprintf(fp, "%s", desc_str);
   fprintf(fp, "\n");

   printf("\nYour record was added successfully!\n");
   fclose(fp);
}

/* Display budget file entries on command line */
void read_budget(FILE* fp) {

   int i = 1, j = 1;

   /* Clear input stream */
   char clear_input[2];
   read_str(clear_input, 1);

   /* Declare arrays for each part of the record */
   char date_str[DATE_LEN + 2], amount_str[AMOUNT_LEN + 2];
   char type_str[TYPE_LEN + 2], desc_str[DESCRIPTION_LEN + 2];
         
   printf("%-9s%-15s%-15s%-10s%-115s\n", "ID   ", "Date", "Amount", "Type", "Description");
   printf("%-9s%-15s%-15s%-10s%-115s\n", "--", "----", "------", "----", "-----------");

   /* 
    * Fetch each part of record from file, store in it's respective
    * array, print each line
    */
   while(!feof(fp)) {
      
      /* Too many records to display, stop */
      if(i > 32767) {
         printf("Too many records\n");
         exit(EXIT_FAILURE);
      }

      /* First, fifth, ninth, etc. lines of file are dates */
      if(fgets(date_str, DATE_LEN, fp) == NULL)
         break;

      /* Remove new line character from fgets for displaying data */
      date_str[strlen(date_str) - 1] = '\0';
      i++;
      
      /* Second, sixth, tenth, etc. lines of file are amounts */
      if(fgets(amount_str, AMOUNT_LEN, fp) == NULL)
         break;

      /* Remove new line character from fgets for displaying data */
      amount_str[strlen(amount_str) - 1] = '\0';
      i++;
      
      /* Third, seventh, elevent, etc. lines of file are types */
      if(fgets(type_str, TYPE_LEN, fp) == NULL)
         break;

      /* Remove new line character from fgets for displaying data */
      type_str[strlen(type_str) - 1] = '\0';
      i++;
      
      /* Fourth, eighth, twelfth, etc. lines of file are descriptions */
      if(fgets(desc_str, DESCRIPTION_LEN, fp) == NULL)
         break;

      /* Remove new line character from fgets for displaying data */
      desc_str[strlen(desc_str) -1] = '\0';
      i++;
      
      /* Print a whole budget record (on one line) */
      printf("%-9d%-15s%-15s%-10s%-115s\n", j, date_str, amount_str, type_str, desc_str);
      j++;
   }
   fclose(fp);
}

/* Read user input, store part of record into its array */
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
