#ifndef _NANOSQL_ITERATOR_H_
#define _NANOSQL_ITERATOR_H_

#include "tuple.h"
#include "table.h"
#include "clause.h"

typedef enum {
    TABLE,
    JOIN,
    SELECT,
    FIXED
} iterator_type;

typedef struct tag_iterator {
    iterator_type type;
    bool notEOI;

    union {
        struct {
            table *table;
            byte  *tuple;
        } table;

        struct {
            struct tag_iterator *args;
            size_t numArgs;
        } join;

        struct {
            struct tag_iterator *from;
            clause *clause;
        } select;

        struct {
            struct tag_iterator *from;
        } fixed;
    } tuples;
} iterator;

void createTableIterator(iterator *iter, table *table);
void createJoinIterator(iterator *iter, int numTables, table *tables);
void createJoinIteratorI(iterator *iter, int numIters, iterator *from);
void createSelectIterator(iterator *iter, iterator *from, clause *clause);
void createFixedIterator(iterator *iter, iterator *from);
void freeIterator(iterator *iter);
bool first(iterator *iter);
bool next(iterator *iter);
byte *get(iterator *iter, const char *tableName, const field *field);
bool test(iterator *iter, clause *clause);
int  selectCount(iterator *iter);

#endif

