#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db/api.h"
#include "structure.h"
#include "printers.h"

void printData()
{
    FILE *db = fopen("db.bin", "rb");

    loadTable(&computert, db);
    loadTable(&hddt, db);
    loadTable(&cput, db);
    loadTable(&videot, db);

    fclose(db);

    printf("Data loaded.\n");

    iterator selecti;

    printf("All computers: \n\n");
    createTableIterator(&selecti, &computert);

    bool notEOI = first(&selecti);
    while (notEOI) {
        printComputer(&selecti, computer, hdd, video, cpu);
        notEOI = next(&selecti);
    }
}

int main(int argc, char *argv[])
{
    createStructure();

    printData();

    return 0;
}

