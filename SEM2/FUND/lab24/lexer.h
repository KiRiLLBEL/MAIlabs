#ifndef __LEXER_H__
#define __LEXER_H__

#include "token.h"
#include "stdio.h"
#define LEXER_SUCCESS 0
#define LEXER_ERROR  -1

int token_next(Token *t, FILE * fin);

#endif // __LEXER_H__
