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
//  FILE:        record.h
//
//  DESCRIPTION:
//   This is a header file that contains the structure of a
//   record.
//
//
****************************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record
{
    int                accountno;
    char               name[30];
    char               address[50];
    struct record*     next;
};

#endif
