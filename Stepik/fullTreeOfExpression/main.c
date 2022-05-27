#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "transform.h"
#include "printer.h"

int main(void)
{
    Expression expr = NULL;

    int err = parse(&expr);
    if (err || expr == NULL) {
        fprintf(stderr, "Error: syntax error or no memory.\n");
        return EXIT_FAILURE;
    }

    err = expression_transform(&expr);
    if (err) {
        fprintf(stderr, "Error: an error during transformation occured.\n");
        return EXIT_FAILURE;
    }

    if (expr->arity == UNARY && expr->data.type == BRACKET) {
        expr = expr->left;
    }

    expression_print(expr);
    expression_destroy(&expr);

    return EXIT_SUCCESS;
}
