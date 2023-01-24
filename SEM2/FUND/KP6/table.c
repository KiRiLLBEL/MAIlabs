#include "table.h"
int StrWrite(char * str, FILE *f) {
    if(fwrite(str, sizeof(str[0]), MAXCHAR, f) != MAXCHAR) {
        return 1;
    }
    return 0;
}
int IntWrite(int * i, FILE *f) {
    if(fwrite(i, sizeof(*i), 1, f) != 1) {
        return 1;
    }
    return 0;
}
int DblWrite(double * d, FILE *f) {
    if(fwrite(d, sizeof(*d), 1, f) != 1) {
        return 1;
    }
    return 0;
}
int StrRead(char * str, FILE *f) {
    if(fread(str, sizeof(str[0]), MAXCHAR, f) != MAXCHAR) {
        return 1;
    }
    return 0;
}
int IntRead(int * i, FILE *f) {
    if(fread(i, sizeof(*i), 1, f) != 1) {
        return 1;
    }
    return 0;
}
int DblRead(double * d, FILE *f) {
    if(fread(d, sizeof(*d), 1, f) != 1) {
        return 1;
    }
    return 0;
}
int addPerson (Person * p, FILE * f) {
    if (StrWrite(p->surname, f) == 1) {
        return 1;
    }
    if (StrWrite(p->initials, f) == 1) {
        return 1;
    }
    if (IntWrite(&p->numberOfThings, f) == 1) {
        return 1;
    }
    if (DblWrite(&p->allWeight, f) == 1) {
        return 1;
    }
    if (StrWrite(p->waypoint, f) == 1) {
        return 1;
    }
    if (StrWrite(p->departureTime, f) == 1) {
        return 1;
    }
    if (IntWrite(&p->transfer, f) == 1) {
        return 1;
    }
    if (IntWrite(&p->children,f) == 1) {
        return 1;
    }
    return 0;
}
int OutPerson (Person * p, FILE * f) {
    if (StrRead(p->surname, f) == 1) {
        return 1;
    }
    if (StrRead(p->initials, f) == 1) {
        return 1;
    }
    if (IntRead(&p->numberOfThings, f) == 1) {
        return 1;
    }
    if (DblRead(&p->allWeight, f) == 1) {
        return 1;
    }
    if (StrRead(p->waypoint, f) == 1) {
        return 1;
    }
    if (StrRead(p->departureTime, f) == 1) {
        return 1;
    }
    if (IntRead(&p->transfer, f) == 1) {
        return 1;
    }
    if (IntRead(&p->children,f) == 1) {
        return 1;
    }
    return 0;
}