#include "table.h"
#include "stdbool.h"
int main() {
    FILE * f;
    Person p;
    f = fopen("BD.bin", "ab");
    bool ContinueInput = true;
    while (ContinueInput) {
        fprintf(stdout, "Input Surname:\n");
        fscanf(stdin, "%s", p.surname);
        fprintf(stdout, "Input initials:\n");
        fscanf(stdin, "%s", p.initials);
        fprintf(stdout, "Input count of baggage:\n");
        fscanf(stdin, "%d", &p.numberOfThings);
        fprintf(stdout, "Input weight:\n");
        fscanf(stdin, "%lf", &p.allWeight);
        fprintf(stdout, "Input waypoint:\n");
        fscanf(stdin, "%s", p.waypoint);
        fprintf(stdout, "Input departure time:\n");
        fscanf(stdin, "%s", p.departureTime);
        fprintf(stdout, "Input transfer:\n");
        char s[MAXCHAR];
        fscanf(stdin, "%s", s);
        if (strcmp(s, "yes") == 0) {
            p.transfer = 1;
        }
        else {
            p.transfer = 0;
        }
        fprintf(stdout, "Input count of children:\n");
        fscanf(stdin, "%d", &p.children);
        addPerson(&p, f);
        fprintf(stdout,"Add new passenger?\n");
        fscanf(stdin, "%s", s);
        if (strcmp(s, "yes") == 0) {
            ContinueInput = true;
        }
        else {
            ContinueInput = false;
        }
    }
    fclose(f);
}