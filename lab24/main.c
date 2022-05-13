#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "tree.h"
#include "transform.h"

/*
 * Необходимые улучшения:
 *   сделать tokens вектором, а не массивом
 *   убрать вывод деревьев и вспомогательных сообщений
 *   перейти от однобуквенных имён переменных к многобуквенным
 *   обработать экзотические требования к обработке унарного минуса
*/

int main(void)
{
    Token tokens[256];
    size_t tokens_qty = 0;

    Token token;
    FILE * fin = fopen("input.txt", "r");
    token_next(&token, fin);

    while (token.type != FINAL) {
        tokens[tokens_qty++] = token;
        token_next(&token, fin);
    }
    fclose(fin);
    Tree tree = tree_create(tokens, 0, tokens_qty - 1);

    printf("\nExpression tree:\n");
    tree_print(tree, 0);

    tree_transform(&tree);

    printf("\nSemitransformed expression tree:\n");
    tree_print(tree, 0);

    printf("\nTree's infix linearization:\n");
    tree_infix(tree);
    printf("\n");

    return 0;
}

