#include "unistd.h"
#include "pthread.h"
#include "stdlib.h"
#include "stdio.h"
#include <time.h>
#include <errno.h>
typedef struct {
    int * vec;
    int l;
    int r;
} QSin;
int THREAD_COUNT = 0;
int MAXTHREAD = 4;
pthread_mutex_t mutex;
int partition(int * vec, int l, int r) {
    int v = vec[(l + r) / 2];
    int i = l;
    int j = r;
    while(i <= j) {
        while(vec[i] < v)
            i++;
        while(vec[j] > v)
            j--;
        if(i >= j)
            break;
        int w = vec[i];
        vec[i++] = vec[j];
        vec[j--] = w;
    }
    return j;
}
void * quicksort(void * arg) {
    int err;
    QSin * data = (QSin*) arg;
    pthread_t id = pthread_self();
    if(data->l < data->r) {
        int q = partition(data->vec, data->l, data->r);
        QSin * data1 = (QSin *)malloc(sizeof(QSin));
        data1->vec = data->vec;
        data1->l = data->l;
        data1->r = q;
        pthread_t id1 = 0;
        if(THREAD_COUNT < MAXTHREAD) {
            if(pthread_create(&id1, NULL, &quicksort, data1) == 0) {
                pthread_mutex_lock(&mutex);
                ++THREAD_COUNT;
                pthread_mutex_unlock(&mutex);
            } else {
                quicksort(data1);
            }
        } else {
            quicksort(data1);
        }
        QSin * data2 = (QSin *)malloc(sizeof(QSin));
        data2->vec = data->vec;
        data2->l = q + 1;
        data2->r = data->r;
        pthread_t id2 = 0;
        if(THREAD_COUNT < MAXTHREAD) {
            if(pthread_create(&id2, NULL, &quicksort, data2) == 0) {
                pthread_mutex_lock(&mutex);
                ++THREAD_COUNT;
                pthread_mutex_unlock(&mutex);
            } else {
                quicksort(data2);
            }
        } else {
            quicksort(data2);
        }
        if(id1 != 0) {
            if(pthread_join(id1, NULL) == 0) {
                pthread_mutex_lock(&mutex);
                --THREAD_COUNT;
                pthread_mutex_unlock(&mutex);
            }
        }
        if(id2 != 0) {
            if(pthread_join(id2, NULL) == 0) {
                pthread_mutex_lock(&mutex);
                --THREAD_COUNT;
                pthread_mutex_unlock(&mutex);
            }
        }
    }
}

int main (int argc, char * argv[]) {
    clock_t start;
    clock_t end;
    if(argc < 2) {
        fprintf(stderr, "input count of threads\n");
        exit(-1);
    } else {
        char * c = argv[1];
        MAXTHREAD = atoi(c);
    }
    int n;
    int err;
    scanf("%d", &n);
    int * vec = calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &vec[i]);
    }
    QSin * in = (QSin *)malloc(sizeof(QSin));
    in->vec = vec;
    in->l = 0;
    in->r = n - 1;
    pthread_mutex_init(&mutex, NULL);
    pthread_t id;
    start = clock();
    err = pthread_create(&id, NULL, &quicksort, in);
    if(err != 0) {
        perror("thread not create");
    }
    err = pthread_join(id, NULL);
    end = clock();
    if(err != 0) {
        perror("error join to thread");
    }
    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", vec[i]);
    }
    printf("\n");
    printf("Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);
    return 0;
}