#ifndef _NANOSQL_CLAUSE_H_
#define _NANOSQL_CLAUSE_H_

#include <stdbool.h>

#include "tuple.h"

typedef enum {
    FEQ,
    FZERO,
    FPOS,
    AND
} clause_type;

typedef struct tag_clause {
    clause_type type;
    union {
        struct {
            char table1[NAME_LENGTH];
            field *arg1;
            char table2[NAME_LENGTH];
            field *arg2;
        } binarySimple;

        struct {
            char table[NAME_LENGTH];
            field *arg;
        } unarySimple;

        struct {
            struct tag_clause *clause1;
            struct tag_clause *clause2;
        } binaryComplex;
    } data;
} struct_clause;

typedef struct_clause *clause;

void createEqClause(clause *result, const char *arg1table, field *arg1,
                    const char *arg2table, field *arg2);
void createZeroClause(clause *result, const char *argTable, field *arg);
void createPosClause(clause *result, const char *argTable, field *arg);
void createAndClause(clause *result, clause *arg1, clause *arg2);
void freeClause(clause *clause);

#endif

