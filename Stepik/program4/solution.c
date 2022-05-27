#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
bool isInt(const char*str) {
    while(*str)  {
        if((*str< '0' || *str > '9') && *str != '-')
            return false;
        *str++;
    }
    return true;
}
void check(pid_t pid, int * count) {
    struct dirent **namelist;
    int n;
    n = scandir("/proc", &namelist, 0, alphasort);
    if (n < 0)
        perror("scandir");
    else {
        while(n--) {
            char path[255];
            sprintf(path, "/proc/%s/stat", namelist[n]->d_name);
            if (isInt(namelist[n]->d_name)) {
                FILE * fin = fopen(path, "r");
                if (fin != NULL) {
                    pid_t check_pid;
                    fscanf(fin, "%*d %*s %*c %d", &check_pid);
                    if (check_pid == pid) {
                        ++(*count);
                        //printf("---%s\n", namelist[n]->d_name);
                        check(strtol(namelist[n]->d_name, NULL, 10), count);
                    }
                }
                fclose(fin);
            }
            free(namelist[n]);
        }
        free(namelist);
    }
}
int main(int argc, char ** argv){
    pid_t mypid = strtol(argv[1], NULL, 10);
    int count = 0;
    check(mypid, &count);
    ++count;
    // struct dirent **namelist;
    // int n;
    // int count = 0;
    // n = scandir("/proc", &namelist, 0, alphasort);
    // if (n < 0)
    //     perror("scandir");
    // else {
    //     while(n--) {
    //         char path[255];
    //         sprintf(path, "/proc/%s/stat", namelist[n]->d_name);
    //         if (isInt(namelist[n]->d_name)) {
    //             FILE * fin = fopen(path, "r");
    //             if (fin != NULL) {
    //                 pid_t check_pid;
    //                 fscanf(fin, "%*d %*s %*c %d", &check_pid);
    //                 if (check_pid == mypid) {
    //                     ++count;
    //                 }
    //             }
    //             fclose(fin);
    //         }
    //         free(namelist[n]);
    //     }
    //     free(namelist);
    // }
    fprintf(stdout, "%d\n", count);
}