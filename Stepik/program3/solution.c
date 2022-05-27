#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char ** argv) {
    pid_t mypid = strtol(argv[1], NULL, 10);
    while (mypid != 1)
    {
        fprintf(stdout, "%d\n", mypid);
        char path[100];
        sprintf(path, "/proc/%d/stat", mypid);
        FILE * fin = fopen(path, "r");
        pid_t ppid;
        fscanf(fin, "%*d %*s %*c %d", &ppid);
        mypid = ppid;
    }
    fprintf(stdout, "%d\n", mypid);
    return 0;
}