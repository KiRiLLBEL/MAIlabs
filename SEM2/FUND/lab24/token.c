#include "mystring.h"
#include "token.h"

int token_free(Token *t)
{
    if (t->type == VARIABLE) {
        string_destroy(&(t->data.variable_name));
    }
    return TOKEN_SUCCESS;
}

int token_copy(Token *to, Token *from)
{
    to->type = from->type;
    switch (to->type) {
        case FINAL:
            break;
        case INTEGER:
            to->data.value_int = from->data.value_int;
            break;
        case FLOATING:
            to->data.value_float = from->data.value_float;
            break;
        case VARIABLE:
            return string_copy(&(to->data.variable_name), &(from->data.variable_name));
            break;
        case OPERATOR:
            to->data.operator_name = from->data.operator_name;
            break;
        case BRACKET:
            to->data.is_left_bracket = from->data.is_left_bracket;
            break;
    }
    return TOKEN_SUCCESS;
}
