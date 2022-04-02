#ifndef _NANOSQL_IO_H_
#define _NANOSQL_IO_H_

#include <stdio.h>

#include "table.h"

void printTable(table *table);
void saveTable(table *table, FILE *f);
void loadTable(table *table, FILE *f);

#endif

