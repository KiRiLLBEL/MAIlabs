#include <stdio.h>

#include "printer.h"

void token_print(Token *t)
{
    switch (t->type) {
        case FINAL:
            printf("EOF\n");
            break;
        case INTEGER:
            printf("int %d\n", t->data.value_int);
            break;
        case FLOATING:
            printf("double  %lf\n", t->data.value_float);
            break;
        case VARIABLE:
            printf("var %s\n", t->data.variable_name.cstring);
            break;
        case OPERATOR:
            printf("op  %c\n", t->data.operator_name);
            break;
        case BRACKET:
            printf("bracket %s\n", t->data.is_left_bracket ? "(" : ")");
            break;
    }
}

void tree_print_subtree(Expression expr, int depth)
{
    if (expr) {
        for (int i = 0; i < depth; i++) {
            printf("| ");
        }
        printf("# ");
        token_print(&(expr->data));
        tree_print_subtree(expr->left, depth + 1);
        tree_print_subtree(expr->right, depth + 1);
    }
}

void tree_print(Expression expr)
{
    tree_print_subtree(expr, 0);
}

void expression_print_subexpression(Expression expr)
{
    if (expr) {
        switch (expr->arity) {
            case BINARY:
                expression_print_subexpression(expr->left);
                printf(" ");
                token_print(&(expr->data));
                printf(" ");
                expression_print_subexpression(expr->right);
                break;
            case UNARY:
                if (expr->data.type == OPERATOR) {
                    token_print(&(expr->data));
                    printf(" ");
                    expression_print_subexpression(expr->left);
                } else {
                    printf("( ");
                    expression_print_subexpression(expr->left);
                    printf(" )");
                }
                break;
            case TERMINAL:
                token_print(&(expr->data));
                break;
        }
    } else {
        printf("Void expression");
    }
}

void expression_print(Expression expr)
{
    expression_print_subexpression(expr);
    printf("\n");
}
