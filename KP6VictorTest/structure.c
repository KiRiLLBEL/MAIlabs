#include <stdlib.h>

#include "db/api.h"
#include "structure.h"

void createStructure()
{
    hdd = (tuple_type *) malloc(sizeof(tuple_type));
    cpu = (tuple_type *) malloc(sizeof(tuple_type));
    video = (tuple_type *) malloc(sizeof(tuple_type));
    computer = (tuple_type *) malloc(sizeof(tuple_type));

    createScheme(hdd);
    createScheme(cpu);
    createScheme(video);
    createScheme(computer);

    addField(hdd, "Capacity",   INTEGER, 1);
    addField(hdd, "Type",       VARCHAR, 5);
    addField(hdd, "ComputerID", INTEGER, 1);

    addField(cpu, "Frequency",    INTEGER, 1);
    addField(cpu, "Manufacturer", VARCHAR, 32);
    addField(cpu, "ComputerID",   INTEGER, 1);

    addField(video, "Memory",     INTEGER, 1);
    addField(video, "Type",       VARCHAR, 4);
    addField(video, "ComputerID", INTEGER, 1);

    addField(computer, "ID",       INTEGER, 1);
    addField(computer, "RAM",      INTEGER, 1);
    addField(computer, "Monitor",  LOGICAL, 1);
    addField(computer, "NumHDD",   INTEGER, 1);
    addField(computer, "NumCPU",   INTEGER, 1);
    addField(computer, "NumVideo", INTEGER, 1);
    addField(computer, "OS",       VARCHAR, 32);
    addField(computer, "Owner",    VARCHAR, 32);

    createTable(&hddt, "HDD", hdd);
    createTable(&cput, "CPU", cpu);
    createTable(&videot, "Video", video);
    createTable(&computert, "Computer", computer);
}

