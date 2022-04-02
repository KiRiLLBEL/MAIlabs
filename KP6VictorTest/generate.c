#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db/api.h"
#include "structure.h"
#include "adders.h"

void createData()
{
    addComputer(&computert, computer, 1, 2048, true,  2, 1, 1,
                "MS Windows 7", "V.Pupkin");
    addComputer(&computert, computer, 2, 1024, true,  0, 1, 1,
                "Debian GNU/Linux", "R.J.Hacker");
    addComputer(&computert, computer, 3, 4096, false, 2, 1, 0,
                "Debian GNU/Linux", "R.J.Hacker");
    addComputer(&computert, computer, 4, 1024, true,  1, 1, 1,
                "Linux", "Alice");
    addComputer(&computert, computer, 5, 1024, true,  1, 1, 1,
                "Windows", "Bob");
    addComputer(&computert, computer, 6, 1024, true,  1, 1, 1,
                "Linux", "Mallory");
    addComputer(&computert, computer, 7, 8192, false, 1, 2, 2,
                "Black Hat Linux", "Mallory");

    addHDD(&hddt, hdd,  500, "SATA", 1);
    addHDD(&hddt, hdd, 1000,  "USB", 1);
    addHDD(&hddt, hdd, 1000, "SATA", 3);
    addHDD(&hddt, hdd, 1000, "SATA", 3);
    addHDD(&hddt, hdd,  100,  "IDE", 4);
    addHDD(&hddt, hdd,  100,  "IDE", 5);
    addHDD(&hddt, hdd,  200,  "IDE", 6);
    addHDD(&hddt, hdd, 2000, "SCSI", 7);

    addCPU(&cput, cpu, 2000, "Intel", 1);
    addCPU(&cput, cpu, 2400,   "AMD", 2);
    addCPU(&cput, cpu, 3000, "Intel", 3);
    addCPU(&cput, cpu, 1600, "Intel", 4);
    addCPU(&cput, cpu, 1600, "Intel", 5);
    addCPU(&cput, cpu, 1800,   "AMD", 6);
    addCPU(&cput, cpu, 3200, "Intel", 7);
    addCPU(&cput, cpu, 3200, "Intel", 7);

    addVideo(&videot, video, 1024, "PCI", 1);
    addVideo(&videot, video, 2048, "PCI", 2);
    addVideo(&videot, video,  512, "Int", 4);
    addVideo(&videot, video,  512, "Int", 5);
    addVideo(&videot, video,  512, "AGP", 6);
    addVideo(&videot, video, 1536, "PCI", 7);
    addVideo(&videot, video, 1536, "PCI", 7);

    FILE *db = fopen("db.bin", "wb");
    saveTable(&computert, db);
    saveTable(&hddt, db);
    saveTable(&cput, db);
    saveTable(&videot, db);
    fclose(db);

    printf("Sample data generated.\n");

    destroyTable(&computert);
    destroyTable(&hddt);
    destroyTable(&cput);
    destroyTable(&videot);
}

int main(int argc, char *argv[])
{
    createStructure();

    createData();

    return 0;
}

