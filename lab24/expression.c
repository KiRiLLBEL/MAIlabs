#include <stdio.h>
#include <stdlib.h>

#include "printer.h"
#include "expression.h"

int expression_create_unary(Expression *result, Token *operator, Expression arg)
{
    if (((*result) = (Expression) malloc(sizeof(Tree)))) {
        (*result)->arity = UNARY;
        (*result)->left = arg;
        (*result)->right = NULL;
        
        int err = token_copy(&((*result)->data), operator);
        if (err) {
            expression_destroy(result);
            return EXPRESSION_ERROR;
        }
        return EXPRESSION_SUCCESS;
    } else {
        return EXPRESSION_ERROR;
    }
}

int expression_create_binary(Expression *result, Token *operator, Expression arg_left, Expression arg_right)
{
    if (((*result) = (Expression) malloc(sizeof(Tree)))) {
        (*result)->arity = BINARY;
        (*result)->left = arg_left;
        (*result)->right = arg_right;
        
        int err = token_copy(&((*result)->data), operator);
        if (err) {
            expression_destroy(result);
            return EXPRESSION_ERROR;
        }
        return EXPRESSION_SUCCESS;
    } else {
        return EXPRESSION_ERROR;
    }
}

int expression_create_terminal(Expression *result, Token *arg)
{
    if (((*result) = (Expression) malloc(sizeof(Tree)))) {
        (*result)->arity = TERMINAL;
        (*result)->left = NULL;
        (*result)->right = NULL;
        
        int err = token_copy(&((*result)->data), arg);
        if (err) {
            expression_destroy(result);
            return EXPRESSION_ERROR;
        }
        return EXPRESSION_SUCCESS;
    } else {
        return EXPRESSION_ERROR;
    }
}

int expression_destroy(Expression *expr)
{
    if (*expr) {
        token_free(&((*expr)->data));
        
        expression_destroy(&((*expr)->left));
        expression_destroy(&((*expr)->right));
    }
    
    free(*expr);
    *expr = NULL;
    
    return EXPRESSION_SUCCESS;
}
