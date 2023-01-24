#include "mkk_alloc.h"
#include <errno.h>
#include <stdio.h>
#include <sys/mman.h>
#define NDX(size) \
    (size) <= (MIN_ALLOC_SIZE * 16) \
        ? (size) <= (MIN_ALLOC_SIZE * 4) \
            ? (size) <= (MIN_ALLOC_SIZE * 2) \
                ? (size) <= (MIN_ALLOC_SIZE * 1) \
                    ? (MIN_BUFFER + 0) \
                    : (MIN_BUFFER + 1) \
                : (MIN_BUFFER + 2) \
            : (size) <= (MIN_ALLOC_SIZE * 8) \
                ? (MIN_BUFFER + 3) \
                : (MIN_BUFFER + 4) \
        : (size) <= (MIN_ALLOC_SIZE * 64) \
            ? (size) <= (MIN_ALLOC_SIZE * 32) \
                ? (MIN_BUFFER + 5) \
                : (MIN_BUFFER + 6) \
            : (size) <= (MIN_ALLOC_SIZE * 128) \
                ? (MIN_BUFFER + 7) \
                : (MIN_BUFFER + 8) \

kmem_Allocator createMemorykmem_Allocator(size_t memory_size) {
    size_t pages = memory_size / PAGE_SIZE + ((memory_size % PAGE_SIZE != 0) ? 1 : 0);
    size_t size = pages * PAGE_SIZE;
    void * ptr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if(ptr == MAP_FAILED) {
        perror("Error: kmem_Allocator not enough memory");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < pages; ++i) {
        kmemsizes[i].bufindex = FREE;
    }
    return (kmem_Allocator){.ptr=ptr, .total_kmem=0, .useful_kmem=0, .size=size};
}

void * alloc_page(kmem_Allocator * allocator, size_t block_size) {
    size_t count_of_blocks = PAGE_SIZE / block_size;
    size_t i = 0;
    while(kmemsizes[i].bufindex != FREE) {
        ++i;
    }
    if(i > allocator->size / PAGE_SIZE - 1)
        return NULL;
    kmemsizes[i].bufindex = block_size;
    void * start = (allocator->ptr + i * PAGE_SIZE);
    kmembucket * kbp = &bucket[NDX(block_size)];
    kbp->next = start;
    for (int j = 0; j < count_of_blocks - 1; ++j) {
        kmembucket * cur = (kmembucket *)start;
        cur->next = start + block_size;
        start = cur->next;
    }
    kmembucket * end = (kmembucket *)(start);
    end->next = NULL;
    void * res = kbp->next;
    kbp->next = ((kmembucket *)res)->next;
    return res;
}

void * alloc_pages(kmem_Allocator * allocator, size_t pages) {
    size_t count_pages = 0;
    size_t i = 0;
    while(i < (allocator->size / PAGE_SIZE) && count_pages != pages) {
        if(kmemsizes[i].bufindex == FREE) {
            ++count_pages;
        }
        else{
            count_pages = 0;
        }
        ++i;
    }
    if(count_pages != pages || i > (allocator->size / PAGE_SIZE)) {
        return NULL;
    }
    void * ptr = allocator->ptr + (i - pages) * PAGE_SIZE;
    kmemsizes[i - pages].bufindex = pages * PAGE_SIZE;
    for(int j = i - pages + 1; j != i; ++j) {
        kmemsizes[j].bufindex = CONT;
    }
    return ptr;
}

void * kmem_alloc(kmem_Allocator * allocator, size_t block_size) {
    if(allocator == NULL)
        return NULL;
    if(block_size == 0)
        return NULL;
    void * ptr = NULL;
    size_t total_size = 0;
    if(block_size <= PAGE_SIZE / 2) {
        kmembucket * kbp = &bucket[NDX(block_size)];
        if(kbp->next == NULL) {
            ptr = alloc_page(allocator, 1 << (NDX(block_size) - MIN_BUFFER));
        } else {
            ptr = kbp->next;
            kbp->next = ((kmembucket *)ptr)->next;
        }
        total_size = 1 << (NDX(block_size) - MIN_BUFFER);
    }
    else {
        size_t pages = block_size / PAGE_SIZE + ((block_size % PAGE_SIZE != 0) ? 1 : 0);
        ptr = alloc_pages(allocator, pages);
        total_size = pages * PAGE_SIZE;
    }
    if(ptr != NULL) {
        allocator->useful_kmem += block_size;
        allocator->total_kmem += total_size;
    }
    return ptr;
}

void kmem_free(kmem_Allocator * allocator, void * block) {
    kmem * ksp = &kmemsizes[(block - allocator->ptr) / PAGE_SIZE];
    kmembucket * kbp;
    if(ksp->bufindex <= PAGE_SIZE / 2) {
        kbp = &bucket[NDX(ksp->bufindex)];
        ((kmembucket *)block)->next = kbp->next;
        kbp->next = block;
    }
    else {
        size_t pages = ksp->bufindex / PAGE_SIZE;
        ksp->bufindex = FREE;
        for(int i = 1; i < pages - 1; ++i) {
            kmemsizes[(block - allocator->ptr) / PAGE_SIZE].bufindex = FREE;
        }
    }
}
void kmem_Alloc_free(kmem_Allocator * allocator) {
    if(munmap(allocator->ptr, allocator->size) == -1) {
        perror("Error: free kmem_Allocator is not success");
        exit(EXIT_FAILURE);
    }
}

size_t get_useful_kmem(kmem_Allocator * allocator) {
    return allocator->useful_kmem;
}
size_t get_total_kmem(kmem_Allocator * allocator) {
    return allocator->total_kmem;
}