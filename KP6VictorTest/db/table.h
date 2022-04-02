#ifndef _NANOSQL_TABLE_H_
#define _NANOSQL_TABLE_H_

#include "tuple.h"

#define INIT_TUPLES 1

typedef struct {
    char name[NAME_LENGTH];
    tuple_type *type;
    size_t numTuples;
    size_t allocated;
    byte *tuples;
} table;

void createTable(table *table, const char *name, tuple_type *scheme);
void destroyTable(table *table);
byte *insertTuple(table *table);
void deleteTuple(table *table, byte *tuple);

#endif

