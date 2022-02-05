/*
 *
 * Name:       cBudget
 *
 * Purpose:    Keep track of a simple budget in a text file.
 *
 *             Each budget record will have the following:
 *
 *             ID          Date        Amount          Type            Description
 *             __          ____        ______          ____            ___________
 *  
 *             x           mm/dd/yyyy  $xxxxxxx.yy     Expense/Income  Description of record
 *
 *
 * Author:     jjones4
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


/* Function prototypes (declarations) */
int read_str(char str[], int n);
void display_budget(FILE* fp, char date_str[], char amount_str[], \
   char type_str[], char desc_str[]);
void save_data(FILE* fp, char date_str[], char amount_str[], \
   char type_str[], char desc_str[]);
void remove_record(FILE* fp, char date_str[], char amount_str[], \
   char type_str[], char desc_str[]);
void update_record(FILE* fp, char date_str[], char amount_str[], \
   char type_str[], char desc_str[]);


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

      /* User menu */
      printf("\nType (1) to see your budget, (2) to add a record, ");
      printf("(3) to remove a record, (4) to edit an existing record, ");
      printf("or (5) to quit: ");
      
      int c = getchar();

      printf("\n");

      /* Display full budget file (option 1) */
      if(c == '1') {

         /* Open file stream for budget data text file */
         fp = fopen(FILE_NAME, "r");
         if(fp == NULL) {
            printf("Can't open %s\n", FILE_NAME);
            exit(EXIT_FAILURE);
         }

         read_str(clear_input, 1);
         
         printf("%-9s%-15s%-15s%-10s%-115s\n", "ID   ", "Date", "Amount", "Type", "Description");
         printf("%-9s%-15s%-15s%-10s%-115s\n", "--", "----", "------", "----", "-----------");
         display_budget(fp, date_str, amount_str, type_str, desc_str);

         fclose(fp);
         printf("\n");
      }
   
      /* Create new budget record (option 2) */
      else if(c == '2') {

         /* Open file stream for budget data text file */
         fp = fopen(FILE_NAME, "a+");
         if(fp == NULL) {
            printf("Can't open %s\n", FILE_NAME);
            exit(EXIT_FAILURE);
         }

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

         fclose(fp);
      }

      /* Remove a record (option 3) */
      else if(c == '3') {

         /* Open file stream for budget data text file */
         fp = fopen(FILE_NAME, "r");
         if(fp == NULL) {
            printf("Can't open %s\n", FILE_NAME);
            exit(EXIT_FAILURE);
         }

         read_str(clear_input, 1);
         
         remove_record(fp, date_str, amount_str, type_str, desc_str);
         fclose(fp);
      }

      /* Update an existing record (option 4) */
      else if(c == '4') {

         /* Open file stream for budget data text file */
         fp = fopen(FILE_NAME, "a+");
         if(fp == NULL) {
            printf("Can't open %s\n", FILE_NAME);
            exit(EXIT_FAILURE);
         }

         read_str(clear_input, 1);
         
         update_record(fp, date_str, amount_str, type_str, desc_str);
         fclose(fp);
      }

      /* Exit program (option 5) */
      else if(c == '5') {

         fclose(fp);
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

/* Update an existing record */
void update_record(FILE* fp, char date_str[], char amount_str[], \
   char type_str[], char desc_str[]) {

   int i = 1, file_line_num = 0, line_num = 1, ctr = 0, option = 0;
   char clear_input[2], new_date_str[DATE_LEN + 2], new_amount_str[AMOUNT_LEN + 2];
   char new_type_str[TYPE_LEN + 2], new_desc_str[DESCRIPTION_LEN + 2];
   FILE* temp_pointer;

   /* Open temp file for budget data text file */
   temp_pointer = fopen(TEMP_FILE, "w");
   if(temp_pointer == NULL) {
      printf("Can't open %s\n", TEMP_FILE);
      exit(EXIT_FAILURE);
   }

   while(1) {
      printf("Enter the line number of the record you want to update: ");
   
      scanf("%d", &line_num);

      if(line_num > 32767 || line_num < 1) {
         printf("\nInvalid line number\n\n");
         continue;
      }

      while(1) {
         printf("\nType (1) to change the date, (2) to change the amount,");
         printf("(3) to change the type, or (4) to change the description: ");

         read_str(clear_input, 1);
         scanf("%d", &option);

         if(option > NUM_FIELDS || option < 1) {
            printf("Invalid option\n\n");
            continue;
         }

         read_str(clear_input, 1);
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
               if(i % NUM_FIELDS == 1) {

                  if(fgets(date_str, DATE_LEN, fp) == NULL)
                     break;
                  
                  if(!feof(fp)) {

                     ctr++;
                     /* Skip the lines at the given line number when populating
                        the temp file */
                     if(ctr != file_line_num) {
                        fprintf(temp_pointer, "%s", date_str);
                     }
                     else {
                        fprintf(temp_pointer, "%s", new_date_str);
                        fprintf(temp_pointer, "\n");
                     }
                  }
                  i++;
               }

               /* Second, sixth, tenth, etc. lines of file are amounts */
               if(i % NUM_FIELDS == 2) {

                  if(fgets(amount_str, AMOUNT_LEN, fp) == NULL)
                     break;

                  if(!feof(fp)) {

                     ctr++;
                     /* Skip the lines at the given line number when populating
                        the temp file */
                     if(ctr != file_line_num) {
                        fprintf(temp_pointer, "%s", amount_str);
                     }
                     else {
                        fprintf(temp_pointer, "%s", new_amount_str);
                        fprintf(temp_pointer, "\n");
                     }
                  }
                  i++;
               }
               /* Third, seventh, elevent, etc. lines of file are types */
               if(i % NUM_FIELDS == 3) {

                  if(fgets(type_str, TYPE_LEN, fp) == NULL)
                     break;

                  if(!feof(fp)) {

                     ctr++;
                     /* Skip the lines at the given line number when populating
                        the temp file */
                     if(ctr != file_line_num) {
                        fprintf(temp_pointer, "%s", type_str);
                     }
                     else {
                        fprintf(temp_pointer, "%s", new_type_str);
                        fprintf(temp_pointer, "\n");
                     }
                  }
                  i++;
               }
               /* Fourth, eighth, twelfth, etc. lines of file are descriptions */
               if(i % NUM_FIELDS == 0) {

                  if(fgets(desc_str, DESCRIPTION_LEN, fp) == NULL)
                     break;

                  if(!feof(fp)) {

                     ctr++;
                     /* Skip the lines at the given line number when populating
                        the temp file */
                     if(ctr != file_line_num) {
                        fprintf(temp_pointer, "%s", desc_str);
                     }
                     else {
                        fprintf(temp_pointer, "%s", new_desc_str);
                        fprintf(temp_pointer, "\n");
                     }
                  }
                  i++;
               }
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
void remove_record(FILE* fp, char date_str[], char amount_str[], \
   char type_str[], char desc_str[]) {

   int i = 1, j = 1, line_num = 0, file_line_num = 0, ctr = 0;
   int option;
   char clear_input[2];
   FILE* temp_pointer;

   /* Open temp file for budget data text file */
   temp_pointer = fopen(TEMP_FILE, "w");
   if(temp_pointer == NULL) {
      printf("Can't open %s\n", TEMP_FILE);
      exit(EXIT_FAILURE);
   }

   while(1) {
      printf("Enter the line number of the record you want to remove: ");
   
      scanf("%d", &line_num);

      if(line_num > 32767 || line_num < 1) {
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

         /* Copy all contents of budget.txt to temporary file exept the lines
            in the record you want to delete */
         while(!feof(fp)) {

            while(1) {

               /* Too many records, stop */
               if(i > 32767) {
                  printf("Too many records\n");
                  exit(EXIT_FAILURE);
               }

               /* First, fifth, ninth, etc. lines of file are dates */
               if(i % NUM_FIELDS == 1) {

                  if(fgets(date_str, DATE_LEN, fp) == NULL)
                     break;
                  
                  if(!feof(fp)) {

                     ctr++;
                     /* Skip the lines at the given line number when populating
                        the temp file */
                     if(ctr != file_line_num) {
                        fprintf(temp_pointer, "%s", date_str);
                     }
                  }
                  i++;
               }

               /* Second, sixth, tenth, etc. lines of file are amounts */
               if(i % NUM_FIELDS == 2) {
                  if(fgets(amount_str, AMOUNT_LEN, fp) == NULL)
                     break;

                  if(!feof(fp)) {

                     ctr++;
                     /* Skip the lines at the given line number when populating
                        the temp file */
                     if(ctr != file_line_num + 1) {
                        fprintf(temp_pointer, "%s", amount_str);
                     }
                  }
                  i++;
               }
               /* Third, seventh, elevent, etc. lines of file are types */
               if(i % NUM_FIELDS == 3) {
                  if(fgets(type_str, TYPE_LEN, fp) == NULL)
                     break;

                  if(!feof(fp)) {

                     ctr++;
                     /* Skip the lines at the given line number when populating
                        the temp file */
                     if(ctr != file_line_num + 2) {
                        fprintf(temp_pointer, "%s", type_str);
                     }
                  }
                  i++;
               }
               /* Fourth, eighth, twelfth, etc. lines of file are descriptions */
               if(i % NUM_FIELDS == 0) {
                  if(fgets(desc_str, DESCRIPTION_LEN, fp) == NULL)
                     break;

                  if(!feof(fp)) {

                     ctr++;
                     /* Skip the lines at the given line number when populating
                        the temp file */
                     if(ctr != file_line_num + 3) {
                        fprintf(temp_pointer, "%s", desc_str);
                     }
                  }
                  i++;
               }
            }
         }

         fclose(temp_pointer);
         fclose(fp);
         remove(FILE_NAME);
         rename(TEMP_FILE, FILE_NAME);

         printf("\nRecord %d cleared successfully!\n", line_num);
         read_str(clear_input, 1);
         return;
      }
      else {
         fclose(temp_pointer);
         fclose(fp);
         printf("\nNo records removed!\n");
         read_str(clear_input, 1);
         return;
      }
   }
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

   printf("\nYour record was added successfully!\n");
}

/* Display budget file entries on command line */
void display_budget(FILE* fp, char date_str[], char amount_str[], char type_str[], char desc_str[]) {

   int i = 1, j = 1;
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
      printf("%-9d%-15s%-15s%-10s%-115s\n", j, date_str, amount_str, type_str, desc_str);
      j++;
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
