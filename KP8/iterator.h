#ifndef ITERATOR_H
#define ITERATOR_H
#include "item.h"
#include "stdbool.h"
#include "list.h"
typedef struct _iterator {
    struct item * node;
} iterator;
#endif
