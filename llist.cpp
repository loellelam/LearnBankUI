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
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   Contains all the function definitions for the class member
//   functions in llist.h, including the constructor and
//   destructor.
//
****************************************************************/

#include <iostream>
#include <fstream>
#include "record.h"
#include "llist.h"

using namespace std;

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Constructor that calls setup methods at the
//                 beginning.
//
//  Parameters:    none
//
//  Return values:  none
//
****************************************************************/

llist::llist()
{
#ifdef DEBUG
    cout << endl << "DEBUG: Called llist()" << endl;
#endif

    int returnvalue;

    start = NULL;

    filename[0] = 'd';
    filename[1] = 'a';
    filename[2] = 't';
    filename[3] = 'a';
    filename[4] = '.';
    filename[5] = 't';
    filename[6] = 'x';
    filename[7] = 't';
    filename[8] = '\0';

    returnvalue = readfile();
    if (returnvalue == 0)
    {
        cout << "Successfully retrieved records" << endl;
    }
    else
    {
        cout << "Failed to retrieve records" << endl;
    }
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Constructor that calls setup methods at the
//                 beginning. Allows custom filename.
//
//  Parameters:    txtname (char []) : name of text file
//
//  Return values:  none
//
****************************************************************/

llist::llist(char txtname[])
{
#ifdef DEBUG
    cout << endl << "DEBUG: Called llist() with parameter:" << endl;
    cout << "  filename : " << txtname << endl;
#endif

    int returnvalue;
    int i = 0;

    start = NULL;

    while (txtname[i] != '\0')
    {
        this->filename[i] = txtname[i];
        i++;
    }
    this->filename[i] = '\0';

    returnvalue = readfile();
    if (returnvalue == 0)
    {
        cout << "Successfully retrieved records" << endl;
    }
    else
    {
        cout << "Failed to retrieve records" << endl;
    }

}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Copy constructor for llist.
//
//  Parameters:    list2 (llist &) : the list to copy from
//
//  Return values:  none
//
****************************************************************/

llist::llist(llist & list2)
{
#ifdef DEBUG
    cout << endl << "DEBUG: Called llist()" << endl;
#endif

    filename[0] = 'd';
    filename[1] = 'a';
    filename[2] = 't';
    filename[3] = 'a';
    filename[4] = '.';
    filename[5] = 't';
    filename[6] = 'x';
    filename[7] = 't';
    filename[8] = '\0';

    struct record * current = list2.start;

    while (current != NULL)
    {
        this->addRecord(current->accountno, current->name, current->address);
        current = current->next;
    }
}

/*****************************************************************
//
//  Function name: ~llist
//
//  DESCRIPTION:   Destructor that calls cleanup methods at the
//                 end.
//
//  Parameters:    none
//
//  Return values:  none
//
****************************************************************/

llist::~llist()
{
#ifdef DEBUG
    cout << endl << "DEBUG: Called ~llist()" << endl;
#endif

    int returnvalue;

    returnvalue = writefile();
    if (returnvalue == 0)
    {
        cout << "Successfully saved records" << endl;
    }
    else
    {
        cout << "Failed to save records" << endl;
    }

    cleanup();
}

/*****************************************************************
//
//  Function name: operator=
//
//  DESCRIPTION:   Overloaded assignment operator
//
//  Parameters:    list2 (llist &) : the list to copy from
//
//  Return values:  *this : reference to the list which may be
//                          assigned to another list
//
****************************************************************/

llist& llist::operator=(const llist & list2)
{
#ifdef DEBUG
    cout << endl << "DEBUG: Called operator=()" << endl;
#endif

    struct record * current = list2.start;

    while (current != NULL)
    {
        this->addRecord(current->accountno, current->name, current->address);
        current = current->next;
    }

    return *this;
}

/*****************************************************************
//
//  Function name: operator<<
//
//  DESCRIPTION:   Overloaded << operator to print contents of
//                 the database.
//
//  Parameters:    os (ostream &) : reference to output stream
//                 list2 (llist &) : the list to copy from
//
//  Return values:  os : reference to the output stream
//
****************************************************************/

ostream& operator<<(ostream & os, const llist & list2)
{
#ifdef DEBUG
    cout << endl <<  "DEBUG: Called operator<<()" << endl;
#endif

    struct record * current = list2.start;

    while (current != NULL)
    {
        cout << current->accountno << endl;
        cout << current->name << endl;
        cout << current->address << endl << endl;
        current = current->next;
    }

    return os;
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds a record to the database.
//
//  Parameters:    account_no (int) : account number
//                 name (char []) : name of account holder
//                 address (char []) : street address
//
//  Return values:  none
//
****************************************************************/

void llist::addRecord(int account_no, char name [], char address [])
{
    int done;
    struct record * current;
    struct record * next_record;
    struct record * new_record;
    int i;

#ifdef DEBUG
    cout << endl << "DEBUG: Called addRecord() with parameters:" << endl;
    cout << "  account_no : " << account_no << endl;
    cout << "  name : " << name << endl;
    cout << "  address : \"" << address << "\"" << endl;
#endif

    done = 0;
    current = start;
    new_record = new record();
    new_record->accountno = account_no;
    i = 0;
    while (name[i] != '\0')
    {
        new_record->name[i] = name[i];
        i++;
    }
    new_record->name[i] = '\0';
    i = 0;
    while (address[i] != '\0')
    {
        new_record->address[i] = address[i];
        i++;
    }
    new_record->address[i] = '\0';
    new_record->next = NULL;

    if (current == NULL)
    {
        start = new_record;
        done = 1;
    }
    else if (account_no < current->accountno)
    {
        new_record->next = start;
        start = new_record;
        done = 1;
    }

    while (done == 0)
    {
        next_record = current->next;

        if (next_record == NULL)
        {
            current->next = new_record;
            done = 1;
        }
        else if (account_no < next_record->accountno)
        {
            new_record->next = current->next;
            current->next = new_record;
            done = 1;
        }

        current = current->next;
    }
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Prints all records in the database.
//
//  Parameters:    none
//
//  Return values:  none
//
****************************************************************/

void llist::printAllRecords()
{

#ifdef DEBUG
    cout << endl << "DEBUG: Called printAllRecords()" << endl;
#endif

    struct record * current = start;

    while (current != NULL)
    {
        cout << current->accountno << endl;
        cout << current->name << endl;
        cout << current->address << endl << endl;
        current = current->next;
    }
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Searches for records in the database.
//
//  Parameters:    account_no (int) : account number
//
//  Return values:  0 : successfully found record
//                 -1 : record not found
//
****************************************************************/

int llist::findRecord(int account_no)
{

    int return_value;
    struct record * current;

#ifdef DEBUG
    cout << endl << "DEBUG: Called findRecord() with parameter:" << endl;
    cout << "  account_no : " << account_no << endl;
#endif

    return_value = -1;
    current = start;

    while (current != NULL && current->accountno <= account_no)
    {
        if (current->accountno == account_no)
        {
            cout << current->accountno << endl;
            cout << current->name << endl;
            cout << current->address << endl << endl;
            return_value = 0;
        }
        current = current->next;
    }

    return return_value;

}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Deletes records from the database.
//
//  Parameters:    account_no (int) : account number
//
//  Return values:  0 : successfully deleted record
//                 -1 : failed to delete record
//
****************************************************************/

int llist::deleteRecord(int account_no)
{

    int done;
    int return_value;
    struct record * current;
    struct record * prev_record;

#ifdef DEBUG
    cout << endl << "DEBUG: Called deleteRecord() with parameter:" << endl;
    cout << "  account_no : " << account_no << endl;
#endif

    done = 0;
    return_value = -1;
    current = start;
    prev_record = start;

    while (done == 0)
    {
        if (current == NULL)
        {
            done = 1;
        }
        else if (current->accountno == account_no)
        {
            if (current->accountno == start->accountno)
            {
                start = current->next;
                delete current;
                current = start;
            }
            else
            {
                prev_record->next = current->next;
                delete current;
                current = prev_record->next;
            }
            return_value = 0;
        }
        else if (current->accountno < account_no)
        {
            if (current->accountno != start->accountno)
            {
                prev_record = prev_record->next;
            }
            current = current->next;
        }
        else
        {
            done = 1;
        }
    }

    return return_value;

}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   Writes to a text file to save the records.
//
//  Parameters:    none
//
//  Return values:  0 : successfully opened file
//                 -1 : failed to open file
//
****************************************************************/

int llist::writefile()
{
    int status;
    struct record * current = start;
    ofstream fout (filename, ofstream::out);

#ifdef DEBUG
    cout << endl << "DEBUG: Called writefile()" << endl;
#endif

    if (fout.bad())
    {
        status = -1;
    }
    else
    {
        status = 0;
        while (current != NULL)
        {
            fout << current->accountno << endl;
            fout << current->name << endl;
            fout << current->address << endl << endl;
            current = current->next;
        }
        fout.close();
    }

    return status;
}


/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Retrieves records from the saved file.
//
//  Parameters:    none
//
//  Return values:  0 : successfully opened file
//                 -1 : failed to open file
//
****************************************************************/

int llist::readfile()
{

    ifstream fin (filename, ifstream::in);
    int status = -1;
    int i;
    char address[50];
    struct record * current;
    struct record * new_record;

#ifdef DEBUG
    cout << endl << "DEBUG: Called readfile()" << endl;
#endif

    if (fin)
    {
        status = 0;

        while (fin.good())
        {
            new_record = new record();

            if (fin >> new_record->accountno)
            {
                fin.ignore();

                fin.getline(new_record->name, 30);

                i = 0;
                do
                {
                    fin.get(address[i]);
                    i++;
                }
                while (i < 50 && (address[i - 1] != '\n' || address[i - 2] != '\n'));
                address[i - 2] = '\0';

                i = 0;
                while (address[i] != '\0')
                {
                    new_record->address[i] = address[i];
                    i++;
                }
                new_record->address[i] = '\0';

                if (start == NULL)
                {
                    start = new_record;
                    current = new_record;
                }
                else
                {
                    current->next = new_record;
                    current = current->next;
                }
            }
        }
        fin.close();
    }

    return status;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   Releases all allocated spaces in the heap
//                 memory. Assigns NULL to start.
//
//  Parameters:    none
//
//  Return values:  none
//
****************************************************************/

void llist::cleanup()
{

    struct record * current;
    struct record * next_record;

#ifdef DEBUG
    cout << endl << "DEBUG: Called cleanup()" << endl;
#endif

    current = start;

    while (current != NULL)
    {
        next_record = current->next;
        delete current;
        current = next_record;
    }

    start = NULL;
}

