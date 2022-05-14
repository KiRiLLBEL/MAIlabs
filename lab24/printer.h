#ifndef __PRINTER_H__
#define __PRINTER_H__

#include "token.h"
#include "expression.h"

void token_print(Token *t);
void tree_print(Expression e);
void expression_print(Expression e);

#endif // __PRINTER_H__
