#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#include "db/api.h"

tuple_type *hdd;
tuple_type *cpu;
tuple_type *video;
tuple_type *computer;

table hddt;
table cput;
table videot;
table computert;

void createStructure();

#endif // _STRUCTURE_H_
