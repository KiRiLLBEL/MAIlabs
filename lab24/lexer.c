#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "mystring.h"
#include "lexer.h"

int token_next(Token *t, FILE * fin)
{
    token_free(t);
    char c;

    do {
        c = fgetc(fin);
    } while (isspace(c));

    if (c == EOF) {
        t->type = FINAL;
        return LEXER_SUCCESS;
    }

    if (isalpha(c) || c == '_') {
        String s;
        int err = string_initialize(&s);

        if (err)
            return LEXER_ERROR;

        while (isalnum(c)) {
            err = string_append(&s, c);
            if (err) {
                string_destroy(&s);
                return LEXER_ERROR;
            }
            c = fgetc(fin);
        }
        ungetc(c, fin);

        t->type = VARIABLE;
        t->data.variable_name = s;

        return LEXER_SUCCESS;
    }
    if (isdigit(c) || c == '.') {
        int n = 0;
        bool left = false;

        while (isdigit(c)) {
            left = true;
            n = 10 * n + (c - '0');
            c = fgetc(fin);
        }

        if (c == '.') {
            double f = n;
            double m = 0.1L;
            c = fgetc(fin);

            if (!left && !isdigit(c)) {
                ungetc(c, fin);
                t->type = OPERATOR;
                t->data.operator_name = '.';
                return LEXER_SUCCESS;
            }

            while (isdigit(c)) {
                f = f + m * (c - '0');
                m /= 10;
                c = fgetc(fin);
            }
            ungetc(c, fin);

            t->type = FLOATING;
            t->data.value_float = f;

            return LEXER_SUCCESS;
        }
        ungetc(c, fin);

        t->type = INTEGER;
        t->data.value_int = n;

        return LEXER_SUCCESS;
    }

    if (c == '(' || c == ')') {
        t->type = BRACKET;
        t->data.is_left_bracket = (c == '(');

        return LEXER_SUCCESS;
    }

    t->type = OPERATOR;
    t->data.operator_name = c;

    return LEXER_SUCCESS;
}
