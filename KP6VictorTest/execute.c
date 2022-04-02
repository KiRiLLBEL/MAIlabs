#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db/api.h"
#include "structure.h"
#include "printers.h"

void processData()
{
    FILE *db = fopen("db.bin", "rb");

    loadTable(&computert, db);
    loadTable(&hddt, db);
    loadTable(&cput, db);
    loadTable(&videot, db);

    fclose(db);

    printf("Data loaded.\n");

    printf("Multimedia computers:\n\n");

    iterator i;
    createTableIterator(&i, &computert);

    clause *gpu = (clause *) malloc(sizeof(clause));
    createPosClause(gpu, "Computer", computer->fields + 5);

    clause *monitor = (clause *) malloc(sizeof(clause));
    createPosClause(monitor, "Computer", computer->fields + 2);

    clause *where = (clause *) malloc(sizeof(clause));
    createAndClause(where, gpu, monitor);

    iterator selecti;
    createSelectIterator(&selecti, &i, where);

    bool notEOI = first(&selecti);
    while (notEOI) {
        printComputer(&selecti, computer, hdd, video, cpu);
        notEOI = next(&selecti);
    }

    freeClause(where);


    printf("Diskless computers:\n\n");
    createTableIterator(&i, &computert);

    clause *nohdd = (clause *) malloc(sizeof(clause));
    createZeroClause(nohdd, "Computer", computer->fields + 3);

    createSelectIterator(&selecti, &i, nohdd);

    notEOI = first(&selecti);
    while (notEOI) {
        printComputer(&selecti, computer, hdd, video, cpu);
        notEOI = next(&selecti);
    }

    freeClause(nohdd);
}


int main(int argc, char *argv[])
{
    createStructure();

    processData();

    return 0;
}

