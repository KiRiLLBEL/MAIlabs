#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <stdbool.h>
#include "mystring.h"

#define TOKEN_SUCCESS 0

// Типы лексем (символ конца, целые, дробные, операторы, переменные, скобки)
typedef enum {
    FINAL,    // Символ конца потока, возникает при EOF
    INTEGER,
    FLOATING,
    OPERATOR,
    VARIABLE,
    BRACKET
} TokenType;

typedef struct {
    TokenType type;
    union {
        int value_int;
        double value_float;
        char operator_name;
        bool is_left_bracket; // 1, если левая скобка, 0 -- если правая
        String variable_name;
    } data;
} Token;

int token_free(Token *token);
int token_copy(Token *to, Token *from);

#endif // __TOKEN_H__
