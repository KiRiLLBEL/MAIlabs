#include <string.h>

#include "db/api.h"
#include "adders.h"

void addHDD(table *hddt, tuple_type *hdd, const int capacity, const char *type,
            const int computer)
{
    byte *new = insertTuple(hddt);
    *(int *) elem(new, hdd->fields + 0) = capacity;
    strncpy((char *) elem(new, hdd->fields + 1), type, 4);
    *(int *) elem(new, hdd->fields + 2) = computer;
}

void addCPU(table *cput, tuple_type *cpu, const int frequency,
            const char *manufacturer, const int computer)
{
    byte *new = insertTuple(cput);
    *(int *) elem(new, cpu->fields + 0) = frequency;
    strncpy((char *)elem(new, cpu->fields + 1), manufacturer, 32);
    *(int *) elem(new, cpu->fields + 2) = computer;
}

void addVideo(table *videot, tuple_type *video, const int memory,
              const char *type, const int computer)
{
    byte *new = insertTuple(videot);
    *(int *) elem(new, video->fields + 0) = memory;
    strncpy((char *) elem(new, video->fields + 1), type, 4);
    *(int *) elem(new, video->fields + 2) = computer;
}

void addComputer(table *compt, tuple_type *comp, const int id, const int ram,
                 const bool monitor, const int hdd, const int cpu,
                 const int video, const char *os, const char *owner)
{
    byte *new = insertTuple(compt);
    *(int *)  elem(new, comp->fields + 0) = id;
    *(int *)  elem(new, comp->fields + 1) = ram;
    *(bool *) elem(new, comp->fields + 2) = monitor;
    *(int *)  elem(new, comp->fields + 3) = hdd;
    *(int *)  elem(new, comp->fields + 4) = cpu;
    *(int *)  elem(new, comp->fields + 5) = video;
    strncpy((char *) elem(new, comp->fields + 6), os, 32);
    strncpy((char *) elem(new, comp->fields + 7), owner, 32);
}

