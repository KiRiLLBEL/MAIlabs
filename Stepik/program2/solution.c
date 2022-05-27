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
int main(){
    struct dirent **namelist;
    int n;
    int count = 0;
    char name[9] = "(genenv)";
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
                    char buf[255];
                    while(fscanf(fin, "%*d %s", buf)) {
                        if(strstr(buf, name)) {
                            ++count;
                            break;
                        } 
                    }
                }
                fclose(fin);
            }
            free(namelist[n]);
        }
        free(namelist);
    }
    fprintf(stdout, "%d\n", count);
}