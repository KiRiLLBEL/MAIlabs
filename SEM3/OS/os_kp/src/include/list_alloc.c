#include "list_alloc.h"
#include <errno.h>
#include <stdio.h>
#include <sys/mman.h>
list_Allocator createMemorylist_Allocator(size_t memory_size) {
    size_t pages = memory_size / PAGE_SIZE + ((memory_size % PAGE_SIZE != 0) ? 1 : 0);
    size_t size = pages * PAGE_SIZE;
    void * realMemory = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if(realMemory == MAP_FAILED) {
        perror("Error: list_Allocator not enough memory");
        exit(EXIT_FAILURE);
    }
    list_block * start_list = (list_block *)realMemory;
    start_list->next = NULL;
    start_list->prev = NULL;
    start_list->block_size = size - sizeof(list_block);
    start_list->is_free = true;
    return (list_Allocator){.size=size, .total_list=0, .useful_list=0, .ptr=realMemory};
}

void * list_alloc(list_Allocator * allocator, size_t block_size) {
    if(allocator == NULL)
        return NULL;
    if(block_size == 0)
        return NULL;
    size_t new_size = 0;
    if(block_size % 4 != 0) {
        new_size = block_size + block_size % 4;
    } else {
        new_size = block_size;
    }
    if(allocator->size < new_size)
        return NULL;
    list_block * list = (list_block *)allocator->ptr;
    void * ptr = NULL;
    while(list != NULL) {
        if(list->block_size >= new_size + sizeof(list_block) && list->is_free) {
            list->next = (list_block *)((void *)list + sizeof(list_block) + new_size);
            list->next->prev = list;
            list->next->block_size = list->block_size - new_size - sizeof(list_block);
            list->next->is_free = true;
            list->block_size = new_size;
            list->is_free = false;
            ptr = (void *)list + sizeof(list_block);
            break;
        } else {
            list = list->next;
        }
    }
    if(ptr != NULL) {
        allocator->useful_list += block_size;
        allocator->total_list += new_size + sizeof(list_block);
    }
    return ptr;
}

void list_free(void * block) {
    list_block * list = (list_block *)(block - sizeof(list_block));
    list->is_free = true;
    if(list->prev != NULL) {
        if(list->prev->is_free) {
            list->prev->block_size = list->prev->block_size + sizeof(list_block) + list->block_size;
            list->prev->next = list->next;
            list = list->prev;
        }
    }
    if(list->next != NULL) {
        if(list->next->is_free) {
            list->block_size = list->block_size + sizeof(list_block) + list->next->block_size;
            list->next = list->next->next;
        }
    }
}

void list_Alloc_free(list_Allocator * allocator) {
    if(munmap(allocator->ptr, allocator->size) == -1) {
        perror("Error: free list_Allocator is not success");
        exit(EXIT_FAILURE);
    }
}

size_t get_useful_list(list_Allocator * allocator) {
    return allocator->useful_list;
}
size_t get_total_list(list_Allocator * allocator) {
    return allocator->total_list;
}