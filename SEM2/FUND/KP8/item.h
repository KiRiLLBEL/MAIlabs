#ifndef ITEM_H
#define ITEM_H
#define MAXSIZE 128
struct item {
    struct item * next;
    char data[128];
};
#endif