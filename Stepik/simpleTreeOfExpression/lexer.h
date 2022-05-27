#ifndef __LEXER_H__
#define __LEXER_H__

#include <stdbool.h>

typedef enum {
    FINAL, // Идентификатор конца входной строки
    INTEGER,
    FLOATING,
    OPERATOR,
    VARIABLE,
    BRACKET
} TokenType;

typedef struct {
    TokenType type;
    union {
        int   value_int;
        float value_float;
        char  operator_name;
        bool  is_left_bracket; // Левая скобка - истина, правая - ложь
        char  variable_name;
    } data;
} Token; // Именно они будут в узлах дерева выражений

void token_print(Token *t);
void token_next(Token *t); // Считать в *t следующий "кусок" входной строки

#endif
