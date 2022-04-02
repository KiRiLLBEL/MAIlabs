#include <stdlib.h>
#include <string.h>

#include "clause.h"

void createEqClause(clause *result, const char *arg1table, field *arg1,
                    const char *arg2table, field *arg2)
{
    (*result) = (struct_clause *)malloc(sizeof(struct_clause));
    (*result)->type = FEQ;
    strncpy((*result)->data.binarySimple.table1, arg1table, NAME_LENGTH);
    (*result)->data.binarySimple.arg1 = arg1;
    strncpy((*result)->data.binarySimple.table2, arg2table, NAME_LENGTH);
    (*result)->data.binarySimple.arg2 = arg2;
}

void createZeroClause(clause *result, const char *argTable, field *arg)
{
    (*result) = (struct_clause *)malloc(sizeof(struct_clause));
    (*result)->type = FZERO;
    strncpy((*result)->data.unarySimple.table, argTable, NAME_LENGTH);
    (*result)->data.unarySimple.arg = arg;
}

void createPosClause(clause *result, const char *argTable, field *arg)
{
    (*result) = (struct_clause *)malloc(sizeof(struct_clause));
    (*result)->type = FPOS;
    strncpy((*result)->data.unarySimple.table, argTable, NAME_LENGTH);
    (*result)->data.unarySimple.arg = arg;
}

void createAndClause(clause *result, clause *arg1, clause *arg2)
{
    (*result) = (struct_clause *)malloc(sizeof(struct_clause));
    (*result)->type = AND;
    (*result)->data.binaryComplex.clause1 = *arg1;
    (*result)->data.binaryComplex.clause2 = *arg2;
}

void freeClause(clause *clause)
{
    if ((*clause)->type == AND) {
        freeClause(&((*clause)->data.binaryComplex.clause1));
        freeClause(&((*clause)->data.binaryComplex.clause2));
    }
    free(*clause);
}

