#include <stdlib.h>
#include <string.h>

#include "iterator.h"

void createTableIterator(iterator *iter, table *table)
{
    iter->type = TABLE;
    iter->tuples.table.table = table;
    iter->tuples.table.tuple = table->tuples;
}

void createJoinIterator(iterator *iter, int numTables, table *tables)
{
    iter->type = JOIN;
    iter->tuples.join.numArgs = numTables;
    iter->tuples.join.args = (iterator *)malloc(numTables * sizeof(iterator));
    for (int i = 0; i < numTables; ++i) {
        createTableIterator(iter->tuples.join.args + i, tables + i);
    }
}

void createJoinIteratorI(iterator *iter, int numIters, iterator *from)
{
    iter->type = JOIN;
    iter->tuples.join.numArgs = numIters;
    iter->tuples.join.args = from;
}

void createSelectIterator(iterator *iter, iterator *from, clause *clause)
{
    iter->type = SELECT;
    iter->tuples.select.from = from;
    iter->tuples.select.clause = clause;
}

void createFixedIterator(iterator *iter, iterator *from)
{
    iter->type = FIXED;
    iter->tuples.fixed.from = from;
}

void freeIterator(iterator *iter)
{
    switch (iter->type) {
        case TABLE:
            break;

        case JOIN:
            for (int i = 0; i < iter->tuples.join.numArgs; ++i) {
                freeIterator(iter->tuples.join.args + i);
            }
            free(iter->tuples.join.args);
            break;

        case SELECT:
            freeIterator(iter->tuples.select.from);
            freeClause(iter->tuples.select.clause);
            break;

        case FIXED:
            freeIterator(iter->tuples.fixed.from);
            break;
    }
}

bool first(iterator *iter)
{
    switch (iter->type) {
        case TABLE:
            iter->tuples.table.tuple = iter->tuples.table.table->tuples;
            iter->notEOI = (iter->tuples.table.table->numTuples != 0);
            return iter->notEOI;

        case JOIN:
            ;
            bool notEmpty = true;
            for (int i = 0; i < iter->tuples.join.numArgs; ++i) {
                notEmpty = notEmpty && first(iter->tuples.join.args + i);
            }
            iter->notEOI = notEmpty;
            return notEmpty;

        case SELECT:
            ;
            bool notEOI = first(iter->tuples.select.from);
            while (notEOI && !test(iter->tuples.select.from, iter->tuples.select.clause)) {
                notEOI = next(iter->tuples.select.from);
            }
            iter->notEOI = notEOI;
            return notEOI;

        case FIXED:
            return true;
    }
}

bool next(iterator *iter)
{
    switch (iter->type) {
        case TABLE:
            iter->tuples.table.tuple += iter->tuples.table.table->type->size;
            iter->notEOI = (iter->tuples.table.tuple !=
                            iter->tuples.table.table->tuples + iter->tuples.table.table->numTuples * iter->tuples.table.table->type->size);
            return iter->notEOI;

        case JOIN:
            if (iter->notEOI) {
                int i = 0;
                while ((i < iter->tuples.join.numArgs) && !iter->tuples.join.args[i].notEOI)
                    ++i;
                if (i == iter->tuples.join.numArgs) {
                    iter->notEOI = false;
                    return false;
                }
                bool notEOI = next(iter->tuples.join.args + i);
                for (int j = 0; j < i; ++j) {
                    first(iter->tuples.join.args + j);
                }
                if ((i == iter->tuples.join.numArgs - 1) && !notEOI) {
                    iter->notEOI = false;
                }
            }
            return iter->notEOI;

        case SELECT:
            ;
            bool notEOI = next(iter->tuples.select.from);
            while (notEOI && !test(iter->tuples.select.from, iter->tuples.select.clause)) {
                notEOI = next(iter->tuples.select.from);
            }
            iter->notEOI = notEOI;
            return notEOI;

        case FIXED:
            return false;
    }
}

byte *get(iterator *iter, const char *tableName, const field *field)
{
    switch (iter->type) {
        case TABLE:
            if (strncmp(tableName, iter->tuples.table.table->name, NAME_LENGTH) == 0) {
                return elem(iter->tuples.table.tuple, field);
            } else {
                return NULL;
            }

        case JOIN:
            ;
            byte *result;
            for (int i = 0; i < iter->tuples.join.numArgs; ++i) {
                if ((result = get(iter->tuples.join.args + i, tableName, field)) != NULL) {
                    return result;
                }
            }
            return NULL;

        case SELECT:
            return get(iter->tuples.select.from, tableName, field);
            break;

        case FIXED:
            return get(iter->tuples.fixed.from, tableName, field);
    }
}

bool test(iterator *iter, clause *clause)
{
    switch ((*clause)->type) {
        case FEQ:
            if ((*clause)->data.binarySimple.arg1->type == INTEGER && (*clause)->data.binarySimple.arg2->type == INTEGER) {
                return (*(int *) get(iter, (*clause)->data.binarySimple.table1, (*clause)->data.binarySimple.arg1) ==
                        *(int *) get(iter, (*clause)->data.binarySimple.table2, (*clause)->data.binarySimple.arg2));
            } else if ((*clause)->data.binarySimple.arg1->type == LOGICAL &&
                       (*clause)->data.binarySimple.arg2->type == LOGICAL) {
                return (*(bool *) get(iter, (*clause)->data.binarySimple.table1, (*clause)->data.binarySimple.arg1) ==
                        *(bool *) get(iter, (*clause)->data.binarySimple.table2, (*clause)->data.binarySimple.arg2));
            } else if ((*clause)->data.binarySimple.arg1->type == VARCHAR &&
                       (*clause)->data.binarySimple.arg2->type == VARCHAR) {
                return ((*clause)->data.binarySimple.arg1->size == (*clause)->data.binarySimple.arg2->size) &&
                       !strncmp((char *) get(iter, (*clause)->data.binarySimple.table1, (*clause)->data.binarySimple.arg1),
                                (char *) get(iter, (*clause)->data.binarySimple.table2, (*clause)->data.binarySimple.arg2),
                                (*clause)->data.binarySimple.arg1->size);
            } else
                return false;

        case FZERO:
            if ((*clause)->data.unarySimple.arg->type == INTEGER) {
                return (*(int *) get(iter, (*clause)->data.unarySimple.table, (*clause)->data.unarySimple.arg) == 0);
            } else if ((*clause)->data.unarySimple.arg->type == LOGICAL) {
                return (! *(bool *) get(iter, (*clause)->data.unarySimple.table, (*clause)->data.unarySimple.arg));
            } else
                return false;

        case FPOS:
            if ((*clause)->data.unarySimple.arg->type == INTEGER) {
                return (*(int *)get(iter, (*clause)->data.unarySimple.table, (*clause)->data.unarySimple.arg) > 0);
            } else if ((*clause)->data.unarySimple.arg->type == LOGICAL) {
                return (*(bool *)get(iter, (*clause)->data.unarySimple.table, (*clause)->data.unarySimple.arg));
            } else
                return false;

        case AND:
            return test(iter, &((*clause)->data.binaryComplex.clause1)) &&
                   test(iter, &((*clause)->data.binaryComplex.clause2));
    }
    return true;
}

int selectCount(iterator *iter)
{
    int i = 0;
    bool notEOI = first(iter);

    while (notEOI) {
        ++i;
        notEOI = next(iter);
    }

    return i;
}

