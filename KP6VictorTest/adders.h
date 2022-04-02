#ifndef _ADDERS_H_
#define _ADDERS_H_

void addHDD(table *hddt, tuple_type *hdd, const int capacity, const char *type,
            const int computer);

void addCPU(table *cput, tuple_type *cpu, const int frequency,
            const char *manufacturer, const int computer);

void addVideo(table *videot, tuple_type *video, const int memory,
              const char *type, const int computer);

void addComputer(table *compt, tuple_type *comp, const int id, const int ram,
                 const bool monitor, const int hdd, const int cpu,
                 const int video, const char *os, const char *owner);

#endif // _ADDERS_H_

