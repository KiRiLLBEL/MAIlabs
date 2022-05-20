#ifndef MAP_H
#define MAP_H
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#define MAXLEN 128
typedef struct mapitem {
    int key;
    char value[MAXLEN];
    struct mapitem * prev;
    struct mapitem * next;
} mapitem;
typedef struct map {
    int size;
    mapitem * maps[MAXLEN];
} map;
int size(map * m);
map * create_map();
void delete_map(map * m);
void push_back(map * m, int key, char * value);
void erase(map * m, int key);
void read_table(map * m, FILE * fin);
void print_table(map * m);
void bin_search(map * m, int key);
void reverse_table(map * m);
void diffuse(map * m);
void sort(map * m);
#endif