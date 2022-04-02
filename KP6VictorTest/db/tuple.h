#ifndef _NANOSQL_TUPLE_H_
#define _NANOSQL_TUPLE_H_

#include <stddef.h>
#include <stdbool.h>

#define NAME_LENGTH 64

typedef char byte;

#define TYPES_QTY 3

typedef enum {
    INTEGER = 0,
    LOGICAL = 1,
    VARCHAR = 2
} field_type;

extern size_t sizes[TYPES_QTY];

typedef struct {
    //  char tableName[NAME_LENGTH];
    char name[NAME_LENGTH];
    field_type type;
    size_t offset;
    size_t size;
} field;

typedef struct {
    field *fields;
    size_t numFields;
    size_t size;
} tuple_type;

byte *elem(byte *data, const field *field);
void copyTuple(tuple_type *type, byte *dest, byte *src);
void createScheme(tuple_type *scheme);
void destroyScheme(tuple_type *scheme);
void addField(tuple_type *scheme, const char *name, field_type type, size_t size);

#endif
