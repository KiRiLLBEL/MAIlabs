#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "lexer.h"

void token_next(Token *t, FILE * fin)
{
    static bool can_be_unary = true; // http://en.wikipedia.org/wiki/Static_variable
    char c;
    do { // Избавление от пробельных литер
        c = fgetc(fin);
    } while (isspace(c));
    
    if (c == EOF) { // The end
        t->type = FINAL;
    }
    
    else if (isalpha(c) || c == '_') { // Переменные
        t->type = VARIABLE;
        t->data.variable_name = c;
        can_be_unary = false;
    }
    
    else if (isdigit(c)) { // Числа
        float result;
        ungetc(c, fin);
        fscanf(fin,"%f", &result);
        
        if (result == (int) result) {
            t->type = INTEGER;
            t->data.value_int = (int) result;
        } else {
            t->type = FLOATING;
            t->data.value_float = result;
        }
        can_be_unary = false;
    }
    
    else if (c == '(' || c == ')') {
        t->type = BRACKET;
        t->data.is_left_bracket = (c == '(');
        can_be_unary = t->data.is_left_bracket;
    }
    
    else if (can_be_unary && (c == '-' || c == '+')) { // Учёт минуса перед числом
        int m = (c == '+') ? +1 : -1; // Знак
        
        do {
            c = fgetc(fin);
        } while (isspace(c));
        
        if (isdigit(c)) {
            ungetc(c, fin);
            token_next(t, fin); // После минуса и т.д. надо число считать
            if (t->type == INTEGER) {
                t->data.value_int = m * (t->data.value_int);
            } else {
                t->data.value_float = m * (t->data.value_float);
            }
        }
        else {
            ungetc(c, fin);
            t->type = OPERATOR;
            t->data.operator_name = '-';
            can_be_unary = true;
        }
    }
    
    else {
        t->type = OPERATOR;
        t->data.operator_name = c;
        can_be_unary = true;
    }
}

void token_print(Token *t)
{
    switch (t->type) {
        case FINAL:
            break;
        case INTEGER:
            printf("%d", t->data.value_int);
            break;
        case FLOATING:
            printf("%lg", t->data.value_float);
            break;
        case VARIABLE:
            printf("%c", t->data.variable_name);
            break;
        case OPERATOR:
            printf("%c", t->data.operator_name);
            break;
        case BRACKET:
            printf("%c", (t->data.is_left_bracket) ? '(' : ')');
            break;
    }
}

