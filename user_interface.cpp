/*****************************************************************
//
//  NAME:        Loelle Lam
//
//  HOMEWORK:    Project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 11, 2022
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   Creates a user interface which allows access to view and
//   edit information from the linked list through the menu options.
//
****************************************************************/

#include <iostream>
#include <string>
#include "record.h"
#include "llist.h"

using namespace std;

void getaddress(char [], int);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Enables users to interact with the linked list by
//                 selecting menu options.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : success
//
****************************************************************/

int main(int argc, char* argv[])
{
    string input;
    int input_len;
    int account_no;
    int return_value;
    char name[30];
    char address[50];
    int exit_program;
    int exit_loop;

    exit_program = 0;
 
    cout << "Welcome to Bank Database Application!" << endl;

    llist mylist;

    do
    {
        cout << endl << "Choose a menu option from the list below by typing"
                        " its name or a subset of its name." << endl;
        cout << "add: Add a new record in the database" << endl;
        cout << "printall: Print all records in the database" << endl;
        cout << "find: Find record with a specified account #" << endl;
        cout << "delete: Delete existing record from the database"
                " using the account # as a key" << endl;
        cout << "quit: Quit the program" << endl << endl;

        getline(cin, input);
        input_len = input.length();

        if (input_len == 0)
        {
            cout << "Error: Invalid option. Try again." << endl;
        }
        else if (input_len <= 3 && input.compare(0, 3, "add", 0, input_len) == 0)
        {
            exit_loop = 0;
            do
            {
                cout << "Enter account number: ";
                cin >> account_no;
                if (account_no > 0)
                {
                    cin.ignore(100, '\n');
                    exit_loop = 1;
                }
                else
                {
                    cout << "Error. Please enter a positive integer." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                }
            }
            while (exit_loop == 0);

            cout << "Enter name: ";
            cin.get(name, 30);
            cin.ignore();

            cout << "Enter address (Hit <enter> twice when done):" << endl;
            getaddress(address, 50);
            mylist.addRecord(account_no, name, address);
            cout << "New record added" << endl;
        }
        else if (input_len <= 8 && input.compare(0, 8, "printall", 0, input_len) == 0)
        {
            cout << "Record list:" << endl;
            mylist.printAllRecords();
        }
        else if (input_len <= 4 && input.compare(0, 4, "find", 0, input_len) == 0)
        {
            exit_loop = 0;
            do
            {
                cout << "Enter account number: ";
                cin >> account_no;
                if (account_no > 0)
                {
                    cin.ignore(100, '\n');
                    exit_loop = 1;
                }
                else
                {
                    cout << "Error. Please enter a positive integer." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                }
            }
            while (exit_loop == 0);

            return_value = mylist.findRecord(account_no);
            if (return_value == -1)
            {
                cout << "Record not found" << endl;
            }
        }
        else if (input_len <= 6 && input.compare(0, 6, "delete", 0, input_len) == 0)
        {
            exit_loop = 0;
            do
            {
                cout << "Enter account number: ";
                cin >> account_no;
                if (account_no > 0)
                {
                    cin.ignore(100, '\n');
                    exit_loop = 1;
                }
                else
                {
                    cout << "Error. Please enter a positive integer." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                }
            }
            while (exit_loop == 0);

            return_value = mylist.deleteRecord(account_no);
            if (return_value == 0)
            {
                cout << "Successfully deleted record" << endl;
            }
            else
            {
                cout << "Failed to delete record" << endl;
            }
        }
        else if (input_len <= 4 && input.compare(0, 4, "quit", 0, input_len) == 0)
        {
            cout << "Exiting the program" << endl;
            exit_program = 1;
        }
        else
        {
            cout << "Error: Invalid option. Try again." << endl;
        }
    }
    while (exit_program == 0);

    return 0;
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   Obtains the address information. Able to
//                 process multi-line addresses.
//
//  Parameters:    address (char []) : Stores the address
//                 size (int) : max size of address
//
//  Return values:  none
//
****************************************************************/

void getaddress(char address [], int size)
{
    int i = 0;

#ifdef DEBUG
    cout << endl << "DEBUG: Called getaddress() with parameters:" << endl;
    cout << "  address : \"" << address << "\"" << endl;
    cout << "  size : " << size << endl;
#endif

    do
    {
        cin.get(address[i]);
        i++;
    }
    while (i < size && (address[i - 1] != '\n' || address[i - 2] != '\n'));
    address[i - 2] = '\0';
}
