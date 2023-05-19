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
//  FILE:        llist.h
//
//  DESCRIPTION:
//   A header file that includes the class definition with fields
//   and methods for the database.
//
//
****************************************************************/

#ifndef LLIST_H
#define LLIST_H

class llist
{
    private:
        record *    start;
        char        filename[20];
        int         readfile();
        int         writefile();
        void        cleanup();

    public:
        llist();
        llist(char[]);
        llist(llist &);
        ~llist();

        llist & operator=(const llist &);
        friend std::ostream& operator<<(std::ostream &, const llist &);

        void addRecord(int, char [ ],char [ ]);
        int findRecord(int);
        void printAllRecords();
        int deleteRecord(int);
};

#endif
