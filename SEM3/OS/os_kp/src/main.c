#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "include/list_alloc.h"
#include "include/mkk_alloc.h"

typedef struct 
{
    void * addr;
    size_t size;
} data_alloc;


const size_t malloc_request = 100000;
const size_t first_malloc_lower_limit = 4;
const size_t first_malloc_upper_limit = 2048;
const size_t second_malloc_lower_limit = 4;
const size_t second_malloc_upper_limit = 81920;
const size_t third_malloc_lower_limit = 4;
const size_t third_malloc_upper_limit = 4096000;

int main(int argc, char * argv[]) {
    clock_t start_time = 0;
    clock_t end_time = 0;
    size_t useful = 0;
    size_t total = 0;
    if(argc < 2) {
        fprintf(stderr, "Error: input test grade and size of heap\n");
        exit(EXIT_FAILURE);
    }
    srand((unsigned int)time(0));

    size_t heap_size = strtoul(argv[1], NULL, 0);
    list_Allocator list_allocator = createMemorylist_Allocator(heap_size);
    kmem_Allocator kmem_allocator = createMemorykmem_Allocator(heap_size);

    data_alloc first_m_requests[malloc_request];
    data_alloc second_m_requests[malloc_request];
    data_alloc third_m_requests[malloc_request];

    for(int i = 0; i < malloc_request; ++i) {
        first_m_requests[i].size = first_malloc_lower_limit + rand() % first_malloc_upper_limit;
    }
    printf("LIST ALLOCATOR LOWER TEST: \n");

    start_time = clock();

    for(int i = 0; i < malloc_request; ++i) {
        first_m_requests[i].addr = list_alloc(&list_allocator, first_m_requests[i].size);
    }

    end_time = clock();

    printf("Requests: %ld\n", malloc_request);
    printf("Heap size: %ld bytes\n", heap_size);
    printf("Limits: %ld to %ld bytes\n", first_malloc_lower_limit, first_malloc_upper_limit);
    printf("Allocation time: %lfs\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);

    for(int i = 0; i < malloc_request / 2; ++i) {
        int j = rand() % (malloc_request - 1);
        data_alloc t = first_m_requests[i];
        first_m_requests[i] = first_m_requests[j];
        first_m_requests[j] = t;
    }

    start_time = clock();

    for(int i = 0; i < malloc_request; ++i) {
        if(first_m_requests[i].addr != NULL) {
            list_free(first_m_requests[i].addr);
        }
    }

    end_time = clock();

    useful = list_allocator.useful_list;
    total = list_allocator.total_list;
    printf("free time: %lfs\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
    printf("Usage: %lf%%\n\n", (double)useful / total);

    for(int i = 0; i < malloc_request; ++i) {
        first_m_requests[i].size = first_malloc_lower_limit + rand() % first_malloc_upper_limit;
    }

    printf("KMEM ALLOCATOR LOWER TEST: \n");

    start_time = clock();

    for(int i = 0; i < malloc_request; ++i) {
        first_m_requests[i].addr = kmem_alloc(&kmem_allocator, first_m_requests[i].size);
    }

    end_time = clock();

    printf("Requests: %ld\n", malloc_request);
    printf("Heap size: %ld bytes\n", heap_size);
    printf("Limits: %ld to %ld bytes\n", first_malloc_lower_limit, first_malloc_upper_limit);
    printf("Allocation time: %lfs\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);

    for(int i = 0; i < malloc_request / 2; ++i) {
        int j = rand() % (malloc_request - 1);
        data_alloc t = first_m_requests[i];
        first_m_requests[i] = first_m_requests[j];
        first_m_requests[j] = t;
    }

    start_time = clock();

    for(int i = 0; i < malloc_request; ++i) {
        if(first_m_requests[i].addr != NULL) {
            kmem_free(&kmem_allocator, first_m_requests[i].addr);
        }
    }

    end_time = clock();

    useful = kmem_allocator.useful_kmem;
    total = kmem_allocator.total_kmem;
    printf("free time: %lfs\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
    printf("Usage: %lf%%\n\n", (double)useful / total);

    list_Alloc_free(&list_allocator);
    kmem_Alloc_free(&kmem_allocator);

    list_allocator = createMemorylist_Allocator(heap_size);
    kmem_allocator = createMemorykmem_Allocator(heap_size);

    for(int i = 0; i < malloc_request; ++i) {
        second_m_requests[i].size = second_malloc_lower_limit + rand() % second_malloc_upper_limit;
    }

    printf("LIST ALLOCATOR MIDDLE TEST: \n");

    start_time = clock();

    for(int i = 0; i < malloc_request; ++i) {
        second_m_requests[i].addr = list_alloc(&list_allocator, second_m_requests[i].size);
    }

    end_time = clock();

    printf("Requests: %ld\n", malloc_request);
    printf("Heap size: %ld bytes\n", heap_size);
    printf("Limits: %ld to %ld bytes\n", second_malloc_lower_limit, second_malloc_upper_limit);
    printf("Allocation time: %lfs\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);

    for(int i = 0; i < malloc_request / 2; ++i) {
        int j = rand() % (malloc_request - 1);
        data_alloc t = second_m_requests[i];
        second_m_requests[i] = second_m_requests[j];
        second_m_requests[j] = t;
    }
    
    start_time = clock();

    for(int i = 0; i < malloc_request; ++i) {
        if(second_m_requests[i].addr != NULL) {
            list_free(second_m_requests[i].addr);
        }
    }

    end_time = clock();

    useful = list_allocator.useful_list;
    total = list_allocator.total_list;
    printf("free time: %lfs\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
    printf("Usage: %lf%%\n\n", (double)useful / total);

    for(int i = 0; i < malloc_request; ++i) {
        second_m_requests[i].size = second_malloc_lower_limit + rand() % second_malloc_upper_limit;
    }

    printf("KMEM ALLOCATOR MIDDLE TEST: \n");

    start_time = clock();

    for(int i = 0; i < malloc_request; ++i) {
        second_m_requests[i].addr = kmem_alloc(&kmem_allocator, second_m_requests[i].size);
    }

    end_time = clock();

    printf("Requests: %ld\n", malloc_request);
    printf("Heap size: %ld bytes\n", heap_size);
    printf("Limits: %ld to %ld bytes\n", second_malloc_lower_limit, second_malloc_upper_limit);
    printf("Allocation time: %lfs\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);

    for(int i = 0; i < malloc_request / 2; ++i) {
        int j = rand() % (malloc_request - 1);
        data_alloc t = second_m_requests[i];
        second_m_requests[i] = second_m_requests[j];
        second_m_requests[j] = t;
    }
    
    start_time = clock();

    for(int i = 0; i < malloc_request; ++i) {
        if(second_m_requests[i].addr != NULL) {
            kmem_free(&kmem_allocator, second_m_requests[i].addr);
        }
    }

    end_time = clock();

    useful = kmem_allocator.useful_kmem;
    total = kmem_allocator.total_kmem;
    printf("free time: %lfs\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
    printf("Usage: %lf%%\n\n", (double)useful / total);

    list_Alloc_free(&list_allocator);
    kmem_Alloc_free(&kmem_allocator);

    list_allocator = createMemorylist_Allocator(heap_size);
    kmem_allocator = createMemorykmem_Allocator(heap_size);

    for(int i = 0; i < malloc_request; ++i) {
        third_m_requests[i].size = third_malloc_lower_limit + rand() % third_malloc_upper_limit;
    }

    printf("LIST ALLOCATOR UPPER TEST: \n");

    start_time = clock();

    for(int i = 0; i < malloc_request; ++i) {
        third_m_requests[i].addr = list_alloc(&list_allocator, third_m_requests[i].size);
    }

    end_time = clock();

    printf("Requests: %ld\n", malloc_request);
    printf("Heap size: %ld bytes\n", heap_size);
    printf("Limits: %ld to %ld bytes\n", third_malloc_lower_limit, third_malloc_upper_limit);
    printf("Allocation time: %lfs\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);

    for(int i = 0; i < malloc_request / 2; ++i) {
        int j = rand() % (malloc_request - 1);
        data_alloc t = third_m_requests[i];
        third_m_requests[i] = third_m_requests[j];
        third_m_requests[j] = t;
    }

    start_time = clock();

    for(int i = 0; i < malloc_request; ++i) {
        if(third_m_requests[i].addr != NULL) {
            list_free(third_m_requests[i].addr);
        }
    }

    end_time = clock();

    useful = list_allocator.useful_list;
    total = list_allocator.total_list;
    printf("free time: %lfs\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
    printf("Usage: %lf%%\n\n", (double)useful / total);

    for(int i = 0; i < malloc_request; ++i) {
        third_m_requests[i].size = third_malloc_lower_limit + rand() % third_malloc_upper_limit;
    }

    printf("KMEM ALLOCATOR UPPER TEST: \n");

    start_time = clock();

    for(int i = 0; i < malloc_request; ++i) {
        third_m_requests[i].addr = kmem_alloc(&kmem_allocator, third_m_requests[i].size);
    }

    end_time = clock();

    printf("Requests: %ld\n", malloc_request);
    printf("Heap size: %ld bytes\n", heap_size);
    printf("Limits: %ld to %ld bytes\n", third_malloc_lower_limit, third_malloc_upper_limit);
    printf("Allocation time: %lfs\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);

    for(int i = 0; i < malloc_request / 2; ++i) {
        int j = rand() % (malloc_request - 1);
        data_alloc t = third_m_requests[i];
        third_m_requests[i] = third_m_requests[j];
        third_m_requests[j] = t;
    }

    start_time = clock();

    for(int i = 0; i < malloc_request; ++i) {
        if(third_m_requests[i].addr != NULL) {
            kmem_free(&kmem_allocator, third_m_requests[i].addr);
        }
    }

    end_time = clock();

    useful = kmem_allocator.useful_kmem;
    total = kmem_allocator.total_kmem;
    printf("free time: %lfs\n",(double)(end_time - start_time)/CLOCKS_PER_SEC);
    printf("Usage: %lf%%\n\n", (double)useful / total);

    list_Alloc_free(&list_allocator);
    kmem_Alloc_free(&kmem_allocator);
    return 0;
} 