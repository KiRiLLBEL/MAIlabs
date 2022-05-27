#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(void) {
    pid_t mypid = getpid();
    char path[100];
    sprintf(path, "/proc/%d/stat", mypid);
    FILE * fin = fopen(path, "r");
    pid_t ppid;
    fscanf(fin, "%*d %*s %*c %d", &ppid);
    fprintf(stdout, "%d\n", ppid);
    return 0;
}