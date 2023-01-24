#ifndef TABLE_H
#define TABLE_H
#include <stdio.h>
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#define MAXCHAR 128
typedef struct _Person{
    char surname[MAXCHAR];
    char initials[MAXCHAR];
    int numberOfThings;
    double allWeight;
    char waypoint[MAXCHAR];
    char departureTime[MAXCHAR];
    int transfer;
    int children;
} Person ;
int StrWrite(char * str, FILE *f);
int IntWrite(int * i, FILE *f);
int DblWrite(double * d, FILE *f);
int StrRead(char * str, FILE *f);
int IntRead(int * i, FILE *f);
int DblRead(double * d, FILE *f);
int addPerson (Person * p, FILE * f);
int OutPerson (Person * p, FILE * f);
#endif