#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
int main (int argc, char ** argv) {

    char programName[255];
    sprintf(programName, "%s %s", argv[1], argv[2]);
    FILE * fin = popen(programName, "r");
    char c;
    long long count = 0;
    while((c = fgetc(fin)) !=EOF) {
        if(c == '0') {
            ++count;
        }
    }
    fclose(fin);
    fprintf(stdout, "%lld\n", count);
    return 0;
}