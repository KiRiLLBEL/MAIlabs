#include <stdlib.h>

#include "io.h"

void printTable(table *table)
{
    char *types[3] = {"INTEGER", "LOGICAL", "VARCHAR"};

    printf("TABLE %s\n", table->name);
    printf("%d fields, ", table->type->numFields);
    printf("%d bytes in tuple\n", table->type->size);

    for (int i = 0; i < table->type->numFields; ++i) {
        printf("%d: %s: %s(%d) ", table->type->fields[i].offset,
               table->type->fields[i].name,
               types[table->type->fields[i].type],
               table->type->fields[i].size);
    }

    printf("\n");
    printf("%d tuples\n", table->numTuples);
}

void saveTable(table *table, FILE *f)
{
    fwrite(table->name, sizeof(char), NAME_LENGTH, f);
    fwrite(&(table->type->numFields), sizeof(size_t), 1, f);
    // fwrite(&(table->type->size), sizeof(size_t), 1, f);
    for (int i = 0; i < table->type->numFields; ++i) {
        // fwrite(&(table->type->fields[i].offset), sizeof(size_t), 1, f);
        fwrite(&(table->type->fields[i].type), sizeof(field_type), 1, f);
        fwrite(&(table->type->fields[i].size), sizeof(size_t), 1, f);
        fwrite(table->type->fields[i].name, sizeof(char), NAME_LENGTH, f);
    }

    fwrite(&(table->numTuples), sizeof(size_t), 1, f);
    fwrite(table->tuples, table->type->size, table->numTuples, f);
}

void loadTable(table *table, FILE *f)
{
    tuple_type *scheme;
    scheme = (tuple_type *)malloc(sizeof(tuple_type));
    createScheme(scheme);
    size_t fields;
    char name[NAME_LENGTH];
    fread(name, sizeof(char), NAME_LENGTH, f);
    fread(&fields, sizeof(size_t), 1, f);
    //  fields = 4;
    //  fread(&(table->type->size), sizeof(size_t), 1, f);
    char fname[NAME_LENGTH];
    field_type ftype;
    //  size_t foffset;
    size_t fsize;
    for (int i = 0; i < fields; ++i) {
        //    fread(&foffset, sizeof(size_t), 1, f);
        fread(&ftype, sizeof(field_type), 1, f);
        fread(&fsize, sizeof(size_t), 1, f);
        fread(fname, sizeof(char), NAME_LENGTH, f);
        addField(scheme, fname, ftype, fsize);
    }

    createTable(table, name, scheme);
    int tuples;
    fread(&tuples, sizeof(size_t), 1, f);
    if (tuples > INIT_TUPLES) {
        table->tuples = realloc(table->tuples, tuples * table->type->size);
    }
    table->numTuples = tuples;
    fread(table->tuples, table->type->size, tuples, f);
}

