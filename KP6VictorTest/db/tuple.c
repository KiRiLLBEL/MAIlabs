#include <stdlib.h>
#include <string.h>

#include "tuple.h"

size_t sizes[TYPES_QTY] = { sizeof(int), sizeof(bool), sizeof(char) };

byte *elem(byte *data, const field *field)
{
    return (data + field->offset);
}

void copyTuple(tuple_type *type, byte *dest, byte *src)
{
    memmove(dest, src, type->size);
}

void createScheme(tuple_type *scheme)
{
    scheme->fields = (field *)malloc(0);
    scheme->numFields = 0;
    scheme->size = 0;
}

void destroyScheme(tuple_type *scheme)
{
    free(scheme->fields);
}

void addField(tuple_type *scheme, const char *name, field_type type, size_t size)
{
    scheme->fields = (field *) realloc(scheme->fields, (scheme->numFields + 1) * sizeof(field));
    strncpy(scheme->fields[scheme->numFields].name, name, NAME_LENGTH);
    scheme->fields[scheme->numFields].type = type;
    scheme->fields[scheme->numFields].offset = scheme->size;
    scheme->fields[scheme->numFields].size = size;
    scheme->numFields++;
    scheme->size += sizes[type] * size;
}
