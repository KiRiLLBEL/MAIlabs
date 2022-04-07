#include "table.h"

int main(int argc, char * argv[]) {
    FILE * f;
    Person p;
    f = fopen("BD.bin", "rb");
    if (argc < 4) {
        fprintf(stderr, "Error, input count of baggage and weight");
        exit(1);
    }
    int p1;
    double p2;
    p1 = atoi(argv[2]);
    p2 = atof(argv[3]);
    int buf;
    double bufd;
    char surnamebuf[MAXCHAR];
    char initialsbuf[MAXCHAR];
    while(fread(surnamebuf, sizeof(char), MAXCHAR, f) == MAXCHAR) {
        fread(initialsbuf, sizeof(char), MAXCHAR, f);
        fread(&buf, sizeof(int), 1, f);
        fread(&bufd, sizeof(double), 1, f);
        if (buf == p1 && bufd >= p2) {
            fprintf(stdout, "%s %c.%c.\n", surnamebuf, initialsbuf[0], initialsbuf[1]);
        }
        fseek(f, 264,SEEK_CUR);
    }
    fclose(f);
}