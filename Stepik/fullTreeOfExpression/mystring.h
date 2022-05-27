#ifndef __MYSTRING_H__
#define __MYSTRING_H__

#include <stdlib.h>

#define STRING_NO_MEMORY -1
#define STRING_SUCCESS    0

typedef struct {
    char *cstring;
    size_t length;
    size_t allocated;
} String;

int string_initialize(String *string);
int string_copy(String *to, String *from);
int string_append(String *string, char c);
int string_destroy(String *string);

#endif // __MYSTRING_H__
