#ifndef __PARSER_H__
#define __PARSER_H__

#include "expression.h"

#define PARSER_SUCCESS 0
#define PARSER_ERROR  -1

int parse(Expression *expr);

#endif // __PARSER_H__
