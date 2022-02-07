# cBudget  

cBudget is a command-line app used for keeping track of a budget. Budget records are stored in a text file called "budget.txt."

cBudget may be freely distributed under the MIT license. See the LICENSE file for details.

## Building cBudget  

1. Download cBudget from GitHub.
2. Extract to your desired location (for example, extract the ZIP folder, cBudget-main, to C:\temp\).
3. Launch the Visual Studio Developer Command Prompt.
4. Navigate to the main project directory.
   - C:\temp\cBudget-main>cd c:\temp\cBudget-main
5. Build the source file.
   - C:\temp\cBudget-main>cl cBudget.c
6. An object file and an executable file should be created.
7. Run the program from the Developer Command Prompt.
   - C:\temp\cBudget-main>cBudget.
8. You should be presented with the program's main menu.

## Using cBudget  

cBudget is used by typing options at the command line. Budget records are saved in a text file called "budget.txt" and displayed on the command line when the appropriate options are entered.

You can do the following using the command line options:
- Create new records
- Display your budget
- Update an existing record
- Remove a record

When a record is edited or removed, cBudget moves the revised data to a temporary text file called "temp.txt." The original "budget.txt" file is then removed. Finally, "tempt.txt is renamed to "budget.txt."

A text file with some example budget records has been included at the project's root. It's called "budget.txt." Please note that each part of the budget record is stored on its own line in the text file. One budget record consists of the following fields:
- Date
- Amount
- Type (Expense or Income)
- Description

## Future Plans  

- Add input validation for each menu option.
- Add sorting and searching functions.
- Add a function that checks the file size and ensures too many records are not created.
