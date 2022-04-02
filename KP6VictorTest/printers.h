#ifndef _PRINTERS_H_
#define _PRINTERS_H_

#define printOS(iter, comp)      \
    printf("OS: %s\n\n",     \
           (char *) get(iter, "Computer", comp->fields + 6))

#define printID(iter, comp)      \
    printf("ID: %d\n",       \
           *(int *) get(iter, "Computer", comp->fields + 0))

#define printOwner(iter, comp)   \
    printf("Owner: %s\n",    \
           (char *) get(iter, "Computer", comp->fields + 7))

#define printQtyCPU(iter, comp)  \
    printf("CPUs: %d\n",     \
           *(int *) get(iter, "Computer", comp->fields + 4))

#define printCPU(iter, cpu)      \
    printf("  %s %d MHz\n",  \
           (char *) get(iter, "CPU", cpu->fields + 1), \
           *(int *) get(iter, "CPU", cpu->fields + 0))

#define printRAM(iter, comp)     \
    printf("RAM: %d MiB\n",  \
           *(int *) get(iter, "Computer", comp->fields + 1))

#define printQtyGPU(iter, comp)  \
    printf("GPUs: %d\n",     \
           *(int *) get(iter, "Computer", comp->fields + 5))

#define printGPU(iter, video)    \
    printf("  %s %d MiB\n",  \
           (char *) get(iter, "Video", video->fields + 1), \
           *(int *) get(iter, "Video", video->fields + 0))

#define printQtyHDD(iter, comp)  \
    printf("HDDs: %d\n",     \
           *(int *) get(iter, "Computer", comp->fields + 3))

#define printHDD(iter, hdd)      \
    printf("  %s %d GiB\n",  \
           (char *) get(iter, "HDD", hdd->fields + 1), \
           *(int *) get(iter, "HDD", hdd->fields + 0))


#define printComputer(selector, computer, hdd, video, cpu) \
    do { \
        printID(selector, computer);  \
        printOwner(selector, computer); \
        printQtyCPU(selector, computer); \
        \
        iterator fixcomp[2]; \
        createFixedIterator(fixcomp + 1, selector); \
        createTableIterator(fixcomp + 0, &cput); \
        \
        iterator join; \
        createJoinIteratorI(&join, 2, fixcomp); \
        \
        clause *id = (clause *) malloc(sizeof(clause)); \
        createEqClause(id, "Computer", computer->fields + 0, "CPU", cpu->fields + 2); \
        \
        iterator select; \
        createSelectIterator(&select, &join, id); \
        \
        bool notEOICPU = first(&select); \
        while(notEOICPU) \
        { \
            printCPU(&join, cpu); \
            notEOICPU = next(&select); \
        } \
        \
        freeClause(id); \
        \
        printRAM(selector, computer); \
        printQtyGPU(selector, computer); \
        \
        createTableIterator(fixcomp + 0, &videot); \
        createJoinIteratorI(&join, 2, fixcomp); \
        \
        id = (clause *) malloc(sizeof(clause)); \
        createEqClause(id, "Computer", computer->fields + 0, "Video", video->fields + 2); \
        \
        createSelectIterator(&select, &join, id); \
        \
        bool notEOIGPU = first(&select); \
        while(notEOIGPU) \
        { \
            printGPU(&join, video); \
            notEOIGPU = next(&select); \
        } \
        \
        freeClause(id); \
        \
        printQtyHDD(selector, computer); \
        \
        createTableIterator(fixcomp + 0, &hddt); \
        createJoinIteratorI(&join, 2, fixcomp); \
        \
        id = (clause *) malloc(sizeof(clause)); \
        createEqClause(id, "Computer", computer->fields + 0, "HDD", hdd->fields + 2); \
        createSelectIterator(&select, &join, id); \
        \
        bool notEOIHDD = first(&select); \
        while(notEOIHDD) \
        { \
            printHDD(&join, hdd); \
            notEOIHDD = next(&select); \
        } \
        \
        freeClause(id); \
        \
        printOS(selector, computer); \
    } while (0)

#endif // _PRINTERS_H_

