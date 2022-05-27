#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/shm.h>
int main (int argc, char **argv) {

    long long key1, key2;
    key1 = strtol(argv[1], NULL, 10);
    key2 = strtol(argv[2], NULL, 10);
    int shmid1 = shmget(key1, 1000, 0600);
    int a[100];
    int * shared_mem1 = shmat(shmid1,(void *)0, SHM_RDONLY);
    int shmid2 = shmget(key2, 1000, 0600);
    int b[100];
    int * shared_mem2 = shmat(shmid2,(void *)0, SHM_RDONLY);
    int shmid3 = shmget(1939, 1000, 0644 | IPC_CREAT);
    int * shared_mem3 = shmat(shmid3,(void *) 0,0);  
    int i = 0;
    for (i = 0; i != 100; ++i) {
        shared_mem3[i] = shared_mem1[i] + shared_mem2[i];
    }
    printf("%d\n",1939);
    shmdt(shared_mem1);
    shmdt(shared_mem2);
    shmdt(shared_mem3);
    return 0;
}