#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

#include "token.h"

#define EXPRESSION_SUCCESS 0
#define EXPRESSION_ERROR  -1

typedef enum {
    UNARY,   // Унарные операторы (-5)
    BINARY,  // Бинарные операторы (2 + 2)
    TERMINAL // Терминалы (== "значения": x, y, 55)
} NodeType;

typedef struct tagTree Tree;
struct tagTree {
    NodeType arity;
    Token data;
    Tree *left;
    Tree *right;
};
typedef Tree *Expression;

int expression_create_unary(Expression *result, Token *op, Expression arg);
int expression_create_binary(Expression *result, Token *op, Expression arg1, Expression arg2);
int expression_create_terminal(Expression *result, Token *arg);

int expression_destroy(Expression *expr);

#endif // __EXPRESSION_H__
