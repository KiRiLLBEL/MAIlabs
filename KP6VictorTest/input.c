#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db/api.h"
#include "structure.h"
#include "adders.h"

void promptData(FILE *in, FILE *out)
{
    int  id = 1;
    char oneMore[4] = { '\0' }; // User's answer to "One more computer?"

    do {
        int ram = 0, hddQty = 0, cpuQty = 0, videoQty = 0;
        int monitor = 0;

        char owner[32] = { '\0' };
        char    os[32] = { '\0' };

        fprintf(out, "Computer №%d: \n", id);

        fprintf(out, "  RAM capacity (MiB): ");
        fscanf(in, "%d", &ram);

        fprintf(out, "  Monitors: ");
        fscanf(in, "%d", &monitor);

        fprintf(out, "  Hard drives: ");
        fscanf(in, "%d", &hddQty);

        fprintf(out, "  CPUs: ");
        fscanf(in, "%d", &cpuQty);

        fprintf(out, "  Videocards: ");
        fscanf(in, "%d", &videoQty);

        fprintf(out, "  OS: ");
        fscanf(in, "\n%[^\n]", os);

        fprintf(out, "  Owner: ");
        fscanf(in, "\n%[^\n]", owner);

        addComputer(&computert, computer, id, ram, monitor > 0, hddQty,
                    cpuQty, videoQty, os, owner);

        for (int i = 0; i < hddQty; ++i) {
            int  hdd_capacity = 0;
            char hdd_type[5] = { '\0' };

            fprintf(out, "\n  Hard disk drive №%d: \n", i + 1);

            fprintf(out, "    Capacity (GiB): ");
            fscanf(in, "%d", &hdd_capacity);

            fprintf(out, "    Type (IDE, SATA, etc.): ");
            fscanf(in, "\n[^\n]", hdd_type);

            addHDD(&hddt, hdd, hdd_capacity, hdd_type, id);
        }

        for (int i = 0; i < cpuQty; ++i) {
            int  cpu_frequency = 0;
            char cpu_manufacturer[32] = { '\0' };
            fprintf(out, "\n  CPU №%d: \n", i + 1);

            fprintf(out, "    Frequency (MHz): ");
            fscanf(in, "%d", &cpu_frequency);

            fprintf(out, "    Manufacturer: ");
            fscanf(in, "\n%[^\n]", cpu_manufacturer);

            addCPU(&cput, cpu, cpu_frequency, cpu_manufacturer, id);
        }

        for (int i = 0; i < videoQty; ++i) {
            int  video_memory = 0;
            char video_type[4] = { '\0' };
            fprintf(out, "\n  Videocard №%d: \n", i + 1);

            fprintf(out, "    Video memory (MiB): ");
            fscanf(in, "%d", &video_memory);

            fprintf(out, "    Type (PCI, AGP, Int, etc.): ");
            fscanf(in, "\n%[^\n]", video_type);

            addVideo(&videot, video, video_memory, video_type, id);
        }

        ++id;

        fprintf(out, "\nOne more computer (y/n)? ");
        fscanf(in, "%s", oneMore);
    } while (strstr(oneMore, "y") || strstr(oneMore, "Y")); // Line 14 do's end

    FILE *db = fopen("db.bin", "wb");
    saveTable(&computert, db);
    saveTable(&hddt, db);
    saveTable(&cput, db);
    saveTable(&videot, db);
    fclose(db);

    fprintf(out, "Data recorded.\n");

    destroyTable(&computert);
    destroyTable(&hddt);
    destroyTable(&cput);
    destroyTable(&videot);
}

int main(int argc, char *argv[])
{
    createStructure();

    promptData(stdin, stdout);

    return 0;
}

