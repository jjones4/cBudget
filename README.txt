Simple Command Line Budget App Written in C

Note that there is no input validation yet.

The type of transaction is either e (expense) or i (income).

A session with this app might look something like:

C:\Temp>cBudget

Enter transaction date, mm/dd/yyyy: 01/28/2022
Enter transaction amount: 32.50
Enter transaction type, e or i: e
Enter transaction description: Gas

Enter transaction date, mm/dd/yyyy: 01/29/2022
Enter transaction amount: 721.26
Enter transaction type, e or i: i
Enter transaction description: Paycheck

Enter transaction date, mm/dd/yyyy: q

Date            Amount          Type            Description
----            ------          ----            -----------
01/28/2022      32.50           e               Gas
01/29/2022      721.26          i               Paycheck


C:\Temp>cBudget
