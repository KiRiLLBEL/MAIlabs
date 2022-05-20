#include <stdio.h>
#include "map.h"
int main() {
    map * m = create_map();
    FILE * fin = fopen("input.txt", "r");
    read_table(m, fin);
    fclose(fin);
    //print_table(m);
    reverse_table(m);
    diffuse(m);
    sort(m);
    delete_map(m);
    return 0;
}
