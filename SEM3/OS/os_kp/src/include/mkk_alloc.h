#ifndef MKK_ALLOC_H
#define MKK_ALLOC_H

#include <stdlib.h>
#include <stdbool.h>
#define PAGE_SIZE 4096
#define MIN_BUFFER 4
#define MIN_ALLOC_SIZE (1 << MIN_BUFFER)
#define MAXKMEM (PAGE_SIZE * 1024)

enum States{
    FREE,
    CONT
};

struct kmem {
    size_t bufindex;
    size_t cnt_pages;
};

typedef struct kmem kmem;

static kmem kmemsizes[MAXKMEM / PAGE_SIZE];

struct kmembucket {
    void * next;
};
typedef struct kmembucket kmembucket;

static kmembucket bucket[MIN_BUFFER + 16];

struct kmem_Allocator {
    size_t size;
    size_t useful_kmem;
    size_t total_kmem;
    void * ptr;
};

typedef struct kmem_Allocator kmem_Allocator;
kmem_Allocator createMemorykmem_Allocator(size_t memory_size);
void * kmem_alloc(kmem_Allocator * allocator, size_t block_size);
void kmem_free(kmem_Allocator * allocator, void * block);
void kmem_Alloc_free(kmem_Allocator * allocator);
size_t get_useful_kmem(kmem_Allocator * allocator);
size_t get_total_kmem(kmem_Allocator * allocator);
#endif