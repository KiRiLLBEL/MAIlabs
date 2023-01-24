#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stdlib.h>
#include <stdbool.h>
#define PAGE_SIZE 4096

struct list_block{
    size_t block_size;
    bool is_free;
    struct list_block * next;
    struct list_block * prev;
};

typedef struct list_block list_block;

struct list_Allocator {
    size_t size;
    size_t useful_list;
    size_t total_list;
    void * ptr;
};

typedef struct list_Allocator list_Allocator;

list_Allocator createMemorylist_Allocator(size_t memory_size);
void * list_alloc(list_Allocator * allocator, size_t block_size);
void list_free(void * block); 
void list_Alloc_free(list_Allocator * allocator);
size_t get_useful_list(list_Allocator * allocator);
size_t get_total_list(list_Allocator * allocator);
#endif