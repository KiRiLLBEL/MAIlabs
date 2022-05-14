#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "printer.h"
#include "transform.h"

int sum_create(Expression *expr, Token *t, int n, bool first)
{
    Expression tmp;

    Token plus  = { .type = OPERATOR, .data = { .operator_name = '+' } };
    Token minus = { .type = OPERATOR, .data = { .operator_name = '-' } };
    Token zero  = { .type = INTEGER,  .data = { .value_int = 0 } };

    int err = TRANSORMATION_SUCCESS;

    if (n == 0) {
        err = expression_create_terminal(expr, &zero);
        if (err) {
            return TRANSORMATION_ERROR;
        }
        return TRANSORMATION_SUCCESS;
    }

    err = expression_create_terminal(expr, t);
    if (err) {
        return TRANSORMATION_ERROR;
    }

    if (n < 0 && first) {
        err = expression_create_unary(expr, &minus, *expr);
        if (err) {
            return TRANSORMATION_ERROR;
        }
    }

    if (n > 1) {
        err = sum_create(&tmp, t, n - 1, false);
        if (err) {
            expression_destroy(&tmp);
            return TRANSORMATION_ERROR;
        }
        err = expression_create_binary(expr, &plus, *expr, tmp);
        if (err) {
            expression_destroy(&tmp);
            return TRANSORMATION_ERROR;
        }
    } else if (n < -1) {
        err = sum_create(&tmp, t, n + 1, false);
        if (err) {
            expression_destroy(&tmp);
            return TRANSORMATION_ERROR;
        }
        err = expression_create_binary(expr, &minus, *expr, tmp);
        if (err) {
            expression_destroy(&tmp);
            return TRANSORMATION_ERROR;
        }
    }

    return TRANSORMATION_SUCCESS;
}

int transform1(Expression *expr)
{
    Token bracket = { .type = BRACKET, .data = { .is_left_bracket = 0 } };
    Expression tmp;
    int err = sum_create(&tmp, &((*expr)->left->data), (*expr)->right->data.data.value_int, true);
    if (err) {
        expression_destroy(&tmp);
        return TRANSORMATION_ERROR;
    }
    err = expression_create_unary(&tmp, &bracket, tmp);
    if (err) {
        expression_destroy(&tmp);
        return TRANSORMATION_ERROR;
    }
    expression_destroy(expr);
    *expr = tmp;
    return TRANSORMATION_SUCCESS;
}

int transform2(Expression *expr)
{
    Expression tmp;
    Token bracket = { .type = BRACKET, .data = { .is_left_bracket = 0 } };
    int err = sum_create(&tmp, &((*expr)->left->right->data), (*expr)->right->data.data.value_int, true);
    if (err) {
        expression_destroy(&tmp);
        return TRANSORMATION_ERROR;
    }
    err = expression_create_unary(&tmp, &bracket, tmp);
    if (err) {
        expression_destroy(&tmp);
        return TRANSORMATION_ERROR;
    }
    Expression left = (*expr)->left->left;
    (*expr)->left->left = NULL;
    expression_destroy(&((*expr)->left));
    (*expr)->left = left;
    expression_destroy(&((*expr)->right));
    (*expr)->right = tmp;
    return TRANSORMATION_SUCCESS;
}

int transform3(Expression *expr)
{
    Expression tmp;
    Token bracket = { .type = BRACKET, .data = { .is_left_bracket = 0 } };
    int err = expression_create_unary(&tmp, &bracket, (*expr)->left);
    if (err) {
        expression_destroy(&tmp);
        return TRANSORMATION_ERROR;
    }
    (*expr)->left = tmp;
    return TRANSORMATION_SUCCESS;
}
int transform4(Expression *expr) {
    Expression tmp;
    Token bracket = { .type = BRACKET, .data = { .is_left_bracket = 0 } };
    Token minus = {.type = OPERATOR, .data = {.operator_name = '-'}};
    if (((*expr)->right->data.type == BRACKET) && ((*expr)->left->data.type == BRACKET)) {
        if(((*expr)->right->left->data.type == OPERATOR && (*expr)->right->left->data.data.operator_name == '-' && (*expr)->right->left->arity == UNARY) && ((*expr)->left->left->data.type == OPERATOR && (*expr)->left->left->data.data.operator_name == '-' && (*expr)->left->left->arity == UNARY)) {
            Expression left = (*expr)->left->left->left;
            (*expr)->left->left = NULL;
            expression_destroy(&((*expr)->left));
            (*expr)->left = left;
            Expression right = (*expr)->right->left->left;
            (*expr)->right->left = NULL;
            expression_destroy(&((*expr)->right));
            (*expr)->right = right;
            return TRANSORMATION_SUCCESS;
        }
        else if (((*expr)->right->left->data.type == OPERATOR && (*expr)->right->left->arity == UNARY && (*expr)->right->left->data.data.operator_name == '-')) {
            Expression right = (*expr)->right->left->left;
            (*expr)->right->left = NULL;
            expression_destroy(&((*expr)->right));
            (*expr)->right = right;
            int err = expression_create_unary(&tmp, &bracket, (*expr));
            if (err) {
                expression_destroy(&tmp);
                return TRANSORMATION_ERROR;
            }
            err = expression_create_unary(&tmp, &minus, tmp);
            if (err) {
                expression_destroy(&tmp);
                return TRANSORMATION_ERROR;
            }
            err = expression_create_unary(&tmp, &bracket, tmp);
            if (err) {
                expression_destroy(&tmp);
                return TRANSORMATION_ERROR;
            }
            (*expr) = tmp;
            return TRANSORMATION_SUCCESS;
        } else if ((*expr)->left->left->data.type == OPERATOR && (*expr)->left->left->data.data.operator_name == '-' && (*expr)->left->left->arity == UNARY) {
            Expression left = (*expr)->left->left->left;
            (*expr)->left->left = NULL;
            expression_destroy(&((*expr)->left));
            (*expr)->left = left;
            int err = expression_create_unary(&tmp, &bracket, (*expr));
            if (err) {
                expression_destroy(&tmp);
                return TRANSORMATION_ERROR;
            }
            err = expression_create_unary(&tmp, &minus, tmp);
            if (err) {
                expression_destroy(&tmp);
                return TRANSORMATION_ERROR;
            }
            err = expression_create_unary(&tmp, &bracket, tmp);
            if (err) {
                expression_destroy(&tmp);
                return TRANSORMATION_ERROR;
            }
            (*expr) = tmp;
            return TRANSORMATION_SUCCESS;
        }
    } else if ((*expr)->right->data.type == BRACKET) {
        if (((*expr)->right->left->data.type == OPERATOR && (*expr)->right->left->arity == UNARY && (*expr)->right->left->data.data.operator_name == '-')) {
            Expression right = (*expr)->right->left->left;
            (*expr)->right->left = NULL;
            expression_destroy(&((*expr)->right));
            (*expr)->right = right;
            int err = expression_create_unary(&tmp, &bracket, (*expr));
            if (err) {
                expression_destroy(&tmp);
                return TRANSORMATION_ERROR;
            }
            err = expression_create_unary(&tmp, &minus, tmp);
            if (err) {
                expression_destroy(&tmp);
                return TRANSORMATION_ERROR;
            }
            err = expression_create_unary(&tmp, &bracket, tmp);
            if (err) {
                expression_destroy(&tmp);
                return TRANSORMATION_ERROR;
            }
            (*expr) = tmp;
            return TRANSORMATION_SUCCESS;
        }
    } else if ((*expr)->left->data.type == BRACKET) {
        if ((*expr)->left->left->data.type == OPERATOR && (*expr)->left->left->data.data.operator_name == '-' && (*expr)->left->left->arity == UNARY) {
            Expression left = (*expr)->left->left->left;
            (*expr)->left->left = NULL;
            expression_destroy(&((*expr)->left));
            (*expr)->left = left;
            int err = expression_create_unary(&tmp, &bracket, (*expr));
            if (err) {
                expression_destroy(&tmp);
                return TRANSORMATION_ERROR;
            }
            err = expression_create_unary(&tmp, &minus, tmp);
            if (err) {
                expression_destroy(&tmp);
                return TRANSORMATION_ERROR;
            }
            err = expression_create_unary(&tmp, &bracket, tmp);
            if (err) {
                expression_destroy(&tmp);
                return TRANSORMATION_ERROR;
            }
            (*expr) = tmp;
            return TRANSORMATION_SUCCESS;
        }
    }
    return TRANSORMATION_SUCCESS;
}
int match1(Expression *expr)
{
    return (*expr != NULL) && ((*expr)->data.type == OPERATOR)
           && ((*expr)->data.data.operator_name == '*')
           && ((*expr)->left->data.type == VARIABLE)
           && ((*expr)->right->data.type == INTEGER);
    //        && ((*expr)->right->data.data.value_int >= 0);
}

int match2(Expression *expr)
{
    return (*expr != NULL) && ((*expr)->data.type == OPERATOR)
           && ((*expr)->data.data.operator_name == '*')
           && ((*expr)->left->data.type == OPERATOR)
           && ((*expr)->left->data.data.operator_name == '*')
           && ((*expr)->left->right->data.type == VARIABLE)
           && ((*expr)->right->data.type == INTEGER);
    //        && ((*expr)->right->data.data.value_int >= 0);
}

int match3(Expression *expr)
{
    return (*expr != NULL) && ((*expr)->data.type == OPERATOR)
           && ((*expr)->left->data.type == OPERATOR)
           && ((*expr)->left->data.data.operator_name == '+');
}
int match4(Expression *expr)
{
    return (*expr != NULL) && ((*expr)->data.type == OPERATOR)
           && ((*expr)->data.data.operator_name == '*') && (((*expr)->right->data.type == BRACKET) || ((*expr)->left->data.type == BRACKET));
}
int expression_transform(Expression *expr)
{
    if ((*expr) != NULL) {
        int err = expression_transform(&((*expr)->left));
        if (err) {
            return TRANSORMATION_ERROR;
        }
        err = expression_transform(&((*expr)->right));
        if (err) {
            return TRANSORMATION_ERROR;
        }
//        if (match1(expr))
//            return transform1(expr);
//        if (match2(expr))
//            return transform2(expr);
        //        if(match3(expr))
        //            return transform3(expr);
            if (match4(expr))
                return transform4(expr);
    }
    return TRANSORMATION_SUCCESS;
}
