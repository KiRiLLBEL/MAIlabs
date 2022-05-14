#include <stdlib.h>
#include <string.h>

#include "mystring.h"

const size_t STRING_INIT_LENGTH = 4;

int string_initialize(String *string)
{
    string->cstring = (char *) malloc(STRING_INIT_LENGTH + 1);
    if (string->cstring != NULL) {
        string->allocated = STRING_INIT_LENGTH;
        memset(string->cstring, 0, string->allocated + 1);
        string->length = 0;
        return STRING_SUCCESS;
    } else {
        return STRING_NO_MEMORY;
    }
}

int string_copy(String *to, String *from)
{
    to->cstring = (char *) malloc(from->length + 1);
    if (to->cstring != NULL) {
        to->allocated = from->length;
        strncpy(to->cstring, from->cstring, from->length + 1);
        to->length = from->length;
        return STRING_SUCCESS;
    } else {
        return STRING_NO_MEMORY;
    }
}

int string_append(String *string, char c)
{
    if (string->length == string->allocated) {
        char *tmp = (char *) realloc(string->cstring, 2 * string->allocated + 1);
        if (tmp != NULL) {
            string->cstring = tmp;
            memset(string->cstring + string->allocated, 0, string->allocated + 1);
            string->allocated *= 2;
        } else {
            return STRING_NO_MEMORY;
        }
    }
    string->cstring[string->length++] = c;
    return STRING_SUCCESS;
}

int string_destroy(String *string)
{
    free(string->cstring);

    string->cstring = NULL;
    string->allocated = 0;
    string->length = 0;

    return STRING_SUCCESS;
}
