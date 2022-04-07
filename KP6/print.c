#include "table.h"
int main() {
    FILE * f;
    Person p;
    f = fopen("BD.bin", "rb");
    fprintf(stdout, "+----------+--------+--------------+------+------------+-------------+---------+---------+\n");
    fprintf(stdout, "|Surname   |initials|NumberOfThings|Weight|Waypoint    |DepartureTime|Transfer |Children | \n");
    while (OutPerson(&p, f) == 0) {
        char * S;
        if (p.transfer == 1) {
            S = "Yes";
        }
        else {
            S = "No";
        }
        fprintf(stdout, "+----------+--------+--------------+------+------------+-------------+---------+---------+\n");
        fprintf(stdout, "|%-10s|   %c.%c  |      %2d      |%5.1f |%-12s|    %c%c:%c%c    |  %4s   |    %d    |\n", p.surname, p.initials[0], p.initials[1], p.numberOfThings, p.allWeight, p.waypoint, p.departureTime[0], p.departureTime[1], p.departureTime[2], p.departureTime[3], S, p.children);
    }
    fprintf(stdout, "+----------+--------+--------------+------+------------+-------------+---------+---------+\n");
    fclose(f);
}