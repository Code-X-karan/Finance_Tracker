#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
void input_is_negative(int amt)
{
    if (amt < 0)
    {
        cout << "Income or expense can never is negative ";
        exit(0);
    }
}
void date(int day, int month, int year)
{

    // Leap year check
    bool isLeap = false;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        isLeap = true;
    }

    // Validate the date
    bool isValid = true;

    if (month < 1 || month > 12)
    {
        isValid = false;
    }
    else
    {
        int daysInMonth[] = {31, 28, 31, 30, 31, 30,
                             31, 31, 30, 31, 30, 31};

        if (isLeap)
        {
            daysInMonth[1] = 29; // February in leap year
        }

        if (day < 1 || day > daysInMonth[month - 1])
        {
            isValid = false;
        }
    }

    // Output date validity
    if (isValid)
    {
        cout << "\nYou entered: " << day << "/" << month << "/" << year << endl;
    }
    else
    {
        cout << "The entered date is invalid.\n";
        exit(0);
    }
}
void blank_inputs(string &input1, string &input2) // this will check is category and description data is null or not
{
    if (input1.empty() || input1[0] == ' ')
    {
        input1 = "**";
    }
    if (input2.empty() || input2[0] == ' ')
    {
        input2 = "**";
    }
}
class logo // this class will print main logo
{
public:
    void print_logo()
    {
        cout << R"(
  ____                                             _______
 / ___|      __  __       __ _         _ __       |_______|
 \___ \     |  \/  |     / _  |       | | _) )       | |
  ___) |    | |\/| |    | (_| |       | |  \ \       | |
 |____/     |_|  |_|     \__ _|       | |   \ \      |_|
         ____
        / ___|       __ _        __   __       __
        \___ \      / _  |       \ \ / /     / _ \
         ___) |    | (_| |        \ V /      |  _/
        |____/      \__ _|         \_/       \___|


                                   Copyright Code-X-Karan. All rights reserved
)";
    }
};
class add_income // this class is used for add or updating the total income
{
public:
    float income;
    string note, income_category, result;
    int day, month, year;

    void income_inputs() // this is the function which take input from user
    {

        cout << "Enter day: ";
        cin >> day;
        cout << "Enter month: ";
        cin >> month;
        cout << "Enter year: ";
        cin >> year;
        date(day, month, year);                                                   // calling  a function for verify is DD-MM-YY is correct
        result = to_string(day) + "-" + to_string(month) + "-" + to_string(year); // concating all DD-MM-YY in single var
        cout << "Enter Your income: ";
        cin >> income; // taking input of income
        input_is_negative(income);
        cin.ignore();
        cout << "Enter the Income category: "; //  income source
        getline(cin, income_category);
        cout << "Enter Description for expense: "; // for add additional info of income
        getline(cin, note);
        blank_inputs(income_category, note);
    }

    void Saving_income() // this  function will save total income in file
    {
        ofstream saving_income;
        saving_income.open("Data.csv", ios::app);                                                                // --. opening a csv sheet in append mode
        saving_income << result << "," << income << "," << income_category << "," << note << "," << "I" << "\n"; // seprate value by comma and line terminator at end for next line
        cout << "\nIncome added Successfully";
        saving_income.close();
    }
};
class add_expense : public add_income // make a expenses class and inherite the income file
{
public:
    float expense;
    int expense_day, expense_month, expense_year;
    string expense_note, expense_category, Expense_date;
    void expense_inputs() // taking expense input from user
    {
        cout << "Enter day: ";
        cin >> expense_day;
        cout << "Enter month: ";
        cin >> expense_month;
        cout << "Enter year: ";
        cin >> expense_year;
        date(expense_day, expense_month, expense_year);                                                         // calling  a function for verify is DD-MM-YY is correct
        Expense_date = to_string(expense_day) + "-" + to_string(expense_month) + "-" + to_string(expense_year); // concating all DD-MM-YY in single var
        cout << "Enter amount for expense: ";
        cin >> expense; // take expense input
        input_is_negative(expense);
        cin.ignore();
        cout << "Enter the Expense category: "; // where the money is spend
        getline(cin, expense_category);
        cout << "Description for expense: "; // expenses description
        getline(cin, expense_note);
        blank_inputs(expense_category, expense_note);
    }
    void Saving_expenses()
    {
        ofstream saving_expense;
        saving_expense.open("Data.csv", ios::app);
        saving_expense << Expense_date << "," << expense << "," << expense_category << "," << expense_note << "," << "E" << "\n"; // saving expenses to file
        cout << "Expense Saved in file";
        saving_expense.close();
    }
};
class View_transaction : public add_expense // this class is used for show all entry in terminal
{
public:
    void header() //  making a header of data
    {
        cout << "\n============================================================================================================\n";
        cout << "\t\t\t\t\t\tTransactions\n";
        cout << "============================================================================================================\n\n";
        cout << left << setw(25) << "Date" << left << setw(25) << "Amount" << left << setw(25) << "Category" << left << setw(25) << "Note" << left << setw(2) << "I/E\n";
        cout << "============================================================================================================\n\n";
    }
    void display()
    {
        string line;
        ifstream data;
        data.open("Data.csv");
        if (!data.is_open())
        {
            cout << "Something is wrong ! The file deleted or renamed";
        }
        else
        {
            header();

            while (getline(data, line))
            {
                stringstream ss(line);
                string cell;

                while (getline(ss, cell, ','))
                {
                    cout << left << setw(25) << cell;
                }
                cout << endl;
            }
            data.close();
        }
    }
};
class data_analyze : public View_transaction // this class is used for analyze the data
{
public:
    void analyzing()
    {
        string line;
        ifstream data;
        data.open("Data.csv");
        if (!data.is_open())
        {
            cout << "Something is wrong ! The file deleted or renamed";
        }
        else
        {
            string line;
            float totalIncome = 0.0f;
            float totalExpenditure = 0.0f;
            float Balance_left = 0.0f;
            float savePercent;

            while (getline(data, line))
            {
                stringstream ss(line);
                string cell;
                int colIndex = 0;
                float amount = 0.0;
                string type;

                while (getline(ss, cell, ','))
                {
                    if (colIndex == 1)
                    {

                        amount = stof(cell);
                    }
                    else if (colIndex == 4)
                    {
                        type = cell;
                    }
                    colIndex++;
                }

                // Accumulate based on type
                if (type == "I")
                {
                    totalIncome += amount;
                }
                else if (type == "E")
                {
                    totalExpenditure += amount;
                }
            }

            data.close();

            // Output results

            cout << "Total Income: " << totalIncome << endl;
            cout << "Total Expenditure: " << totalExpenditure << endl;
            Balance_left = totalIncome - totalExpenditure;
            cout << "Balance left: " << Balance_left << endl;
            savePercent = (Balance_left * 100) / totalIncome;
            cout << "Your saving percentage rate is " << savePercent << endl;
            if (savePercent <= 10)
            {
                cout << "Suggestion: Try to save at least 10% of your income." << endl;
            }
            else if (savePercent <= 20)
            {
                cout << "Suggestion: Good start! Aim for 20% for more stability." << endl;
            }
            else if (savePercent <= 30)
            {
                cout << "Suggestion: You're doing well. Consider investing part of your savings." << endl;
            }
            else if (savePercent <= 40)
            {
                cout << "Suggestion: Great job! You re on the path to financial independence." << endl;
            }
            else if (savePercent <= 50)
            {
                cout << "Suggestion: Impressive! You could look into long-term investments." << endl;
            }
            else
            {
                cout << "Suggestion: Excellent saving habit! You re financially disciplined." << endl;
            }
        }
    }
};
int main()
{
    logo access;
    data_analyze access2;
    access.print_logo(); // this function will call the logo/heading of software
    while (true)         // this will run the program until user exit
    {

        int choice; // this will take input what user want to select from dashboard
        cout << R"(
     ___________________________________
    |             MAIN MENU             |
    |___________________________________|
    | 1.  Add/Update Income             |
    | 2.  Add Expenses                  |
    | 3.  View Transactions             |
    | 4.  View Reports                  |
    | 5.  Exit                          |
    |___________________________________|

    )";
        cout << "\n Enter your option no: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            access2.income_inputs();
            access2.Saving_income();
            break;
        case 2:
            access2.expense_inputs();
            access2.Saving_expenses();
            break;
        case 3:
            access2.display();
            break;
        case 4:
            access2.analyzing();
            break;
        case 5:
            cout << "\n Exiting........\n";
            cout << "Done \n";
            exit(0);
            break;

        default:
            cout << "\n Input is not valid \n";
        }
    }
}
