#include <stdlib.h>
#include <stdbool.h>

#include "lexer.h"
#include "parser.h"

typedef enum {
    ERROR = -1,
    ADD   =  0,
    MULT  =  1,
    POW   =  2
} Priority;

Priority priority(char c)
{
    if (c == '+' || c == '-') {
        return ADD;
    } else if (c == '*' || c == '/' || c == '%') {
        return MULT;
    } else if (c == '^') {
        return POW;
    }
    return ERROR;
}

// Forward declaration необходим из-за взаимной рекурсии в парсере
int parse_addition(Expression *expr, Token *buf, FILE * fin);

int parse_primary(Expression *expr, Token *buf, bool sign, FILE * fin)
{
    Expression tmp = NULL;
    int err = PARSER_SUCCESS;
    
    if (buf->type == FINAL) {
        return PARSER_ERROR;
    }
    
    if ((!sign) && buf->type == OPERATOR && (buf->data.operator_name == '+' || buf->data.operator_name == '-')) {
        Token s;
        int mult = (buf->data.operator_name == '+') ? +1 : -1;
        token_copy(&s, buf);
        token_next(buf, fin);
        err = parse_primary(&tmp, buf, true, fin);
        if (err) {
            expression_destroy(&tmp);
            return PARSER_ERROR;
        }
        if (tmp->data.type == INTEGER) {
            tmp->data.data.value_int = mult * tmp->data.data.value_int;
            *expr = tmp;
            return PARSER_SUCCESS;
        }
        err = expression_create_unary(expr, &s, tmp);
        if (err) {
            expression_destroy(&tmp);
            return PARSER_ERROR;
        }
        token_free(&s);
        return PARSER_SUCCESS;
    }
    
    if (buf->type == BRACKET) {
        if (buf->data.is_left_bracket) {
            token_next(buf, fin);
            err = parse_addition(&tmp, buf, fin);
            if (err) {
                expression_destroy(&tmp);
                return PARSER_ERROR;
            }
            if (buf->type != BRACKET || buf->data.is_left_bracket) {
                return PARSER_ERROR;
            }
            err = expression_create_unary(expr, buf, tmp);
            if (err) {
                expression_destroy(&tmp);
                return PARSER_ERROR;
            }
            token_next(buf, fin);
            return PARSER_SUCCESS;
        } else {
            return PARSER_ERROR;
        }
    } else {
        err = expression_create_terminal(expr, buf);
        if (err) {
            return PARSER_ERROR;
        }
        token_next(buf, fin);
        return PARSER_SUCCESS;
    }
}

int parse_power(Expression *expr, Token *buf, FILE * fin)
{
    Expression tmp = NULL;
    int err = PARSER_SUCCESS;
    if (buf->type == FINAL) {
        return PARSER_ERROR;
    }
    
    err = parse_primary(&tmp, buf, false, fin);
    if (err) {
        expression_destroy(&tmp);
        return PARSER_ERROR;
    }
    if (buf->type == OPERATOR && priority(buf->data.operator_name) == POW) {
        Token t;
        err = token_copy(&t, buf);
        if (err) {
            token_free(&t);
            expression_destroy(&tmp);
            return PARSER_ERROR;
        }
        token_next(buf, fin);
        err = parse_power(expr, buf, fin);
        if (err) {
            token_free(&t);
            expression_destroy(&tmp);
            return PARSER_ERROR;
        }
        err = expression_create_binary(expr, &t, tmp, *expr);
        token_free(&t);
        if (err) {
            expression_destroy(&tmp);
            return PARSER_ERROR;
        }
    } else {
        *expr = tmp;
    }
    return PARSER_SUCCESS;
}

int parse_multiplication(Expression *expr, Token *buf, FILE * fin)
{
    Expression tmp = NULL;
    int err = PARSER_SUCCESS;
    
    if (buf->type == OPERATOR || buf->type == FINAL) {
        return PARSER_ERROR;
    }
    
    err = parse_power(expr, buf, fin);
    if (err) {
        return PARSER_ERROR;
    }
    while (buf->type == OPERATOR) {
        if (priority(buf->data.operator_name) == MULT) {
            Token t;
            err = token_copy(&t, buf);
            if (err) {
                token_free(&t);
                return PARSER_ERROR;
            }
            token_next(buf, fin);
            err = parse_power(&tmp, buf, fin);
            if (err) {
                token_free(&t);
                expression_destroy(&tmp);
                return PARSER_ERROR;
            }
            err = expression_create_binary(expr, &t, *expr, tmp);
            token_free(&t);
            if (err) {
                expression_destroy(&tmp);
                return PARSER_ERROR;
            }
        } else {
            return PARSER_SUCCESS;
        }
    }
    return PARSER_SUCCESS;
}

int parse_addition(Expression *expr, Token *buf, FILE * fin)
{
    Expression tmp = NULL;
    int err = PARSER_SUCCESS;
    
    if (buf->type == OPERATOR) {
        if (priority(buf->data.operator_name) == ADD) {
            Token t;
            err = token_copy(&t, buf);
            if (err) {
                token_free(&t);
                return PARSER_ERROR;
            }
            
            token_next(buf, fin);
            err = parse_multiplication(&tmp, buf, fin);
            if (err) {
                token_free(&t);
                expression_destroy(&tmp);
                return PARSER_ERROR;
            }
            
            err = expression_create_unary(expr, &t, tmp);
            token_free(&t);
            if (err) {
                expression_destroy(&tmp);
                return PARSER_ERROR;
            }
        } else {
            return PARSER_ERROR;
        }
    } else if (buf->type == FINAL) {
        return PARSER_ERROR;
    } else {
        err = parse_multiplication(expr, buf, fin);
        if (err) {
            return PARSER_ERROR;
        }
    }
    while (buf->type == OPERATOR) {
        if (priority(buf->data.operator_name) == ADD) {
            Token t;
            err = token_copy(&t, buf);
            
            if (err) {
                token_free(&t);
                expression_destroy(&tmp);
                return PARSER_ERROR;
            }
            token_next(buf, fin);
            
            err = parse_multiplication(&tmp, buf, fin);
            if (err) {
                token_free(&t);
                expression_destroy(&tmp);
                return PARSER_ERROR;
            }
            
            err = expression_create_binary(expr, &t, *expr, tmp);
            token_free(&t);
            if (err) {
                expression_destroy(&tmp);
                return PARSER_ERROR;
            }
        } else {
            return PARSER_ERROR;
        }
    }
    return PARSER_SUCCESS;
}

int parse(Expression *expr, FILE * fin)
{
    Token buf = { .type = FINAL };
    token_next(&buf, fin);
    
    int err = parse_addition(expr, &buf, fin);
    
    if (err) {
        expression_destroy(expr);
        return PARSER_ERROR;
    }
    
    if (buf.type == FINAL) {
        return PARSER_SUCCESS;
    } else {
        expression_destroy(expr);
        return PARSER_ERROR;
    }
}
