#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include"errorlib.h"
int main() {
    char c;
    while(read(0, &c, 1) > 0) {
        if(c >= 'A' && c <= 'Z') {
            c = c + 32;
        }
        if(write(1, &c, 1) == -1) {
            
            oerror("can't write the pipe 3 by child1", -1);
        }
    }
    return 0;
}