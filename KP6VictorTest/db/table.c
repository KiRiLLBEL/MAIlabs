#include <stdlib.h>
#include <string.h>

#include "table.h"

//const size_t INIT_TUPLES = 64;

void createTable(table *table, const char *name, tuple_type *scheme)
{
    strncpy(table->name, name, NAME_LENGTH);
    table->type = scheme;
    table->tuples = (byte *)malloc(INIT_TUPLES * (scheme->size));
    table->numTuples = 0;
    table->allocated = INIT_TUPLES;
}

void destroyTable(table *table)
{
    destroyScheme(table->type);
    free(table->tuples);
}

byte *insertTuple(table *table)
{
    if (table->numTuples == table->allocated) {
        table->tuples = (byte *)realloc(table->tuples, 2 * table->allocated * table->type->size);
        table->allocated = 2 * table->allocated;
    }
    return table->tuples + (table->numTuples++) * table->type->size;
}

void deleteTuple(table *table, byte *tuple)
{
    //  memmove(tuple, tuple + table->type->size,
    //    table->tuples + (--(table->numTuples)) * table->type->size - tuple);
    for (byte *p = tuple; p < (table->tuples + table->type->size * (table->numTuples - 1));
            p += table->type->size) {
        memcpy(p, p + table->type->size, table->type->size);
    }
    table->numTuples--;
}

