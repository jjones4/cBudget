Simple Command Line Budget App Written in C

Note that there is no input validation yet.

The type of transaction is either e (expense) or i (income).

A session with this app might look something like:

C:\Temp>cBudget

Type (1) to see your budget, (2) to add a record, (3) to remove a record, or (4) to quit: 2

Enter transaction date, mm/dd/yyyy: 01/25/2022
Enter transaction amount: 4.65
Enter transaction type, e or i: Expense
Enter transaction description: Snacks

Record added successfully!

Type (1) to see your budget, (2) to add a record, or (3) to remove a record, or (4) to quit: 2

Enter transaction date, mm/dd/yyyy: 01/26/2022
Enter transaction amount: 2.75
Enter transaction type, e or i: Expense
Enter transaction description: Laundry

Type (1) to see your budget, (2) to add a record, or (3) to remove a record, or (4) to quit: 1

ID       Date           Amount         Type      Description
--       ----           ------         ----      -----------
1        01/05/2022     23.28          Expense   Gas
2        01/08/2022     125.23         Expense   Groceries
3        01/20/2022     500.00         Income    Paycheck
4        01/23/2022     3.75           Expense   Laundry
5        01/25/2022     4.65           Expense   Snacks
6        01/26/2022     2.75           Expense   Laundry

Type (1) to see your budget, (2) to add a record, or (3) to remove a record, or (4) to quit: 4

C:\Temp>cBudget
