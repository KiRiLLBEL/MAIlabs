#include <stdlib.h>
char* translation(long x) {
    char s[64];
    int length = 0;
    for(int i = 0; x > 0; ++i) {
        long a = x % 2;
        s[i] = a + '0';
        length++;;
        x /= 2;
    }
    char * r = (char *)malloc((length + 1)*sizeof(char));
    for(int i = length - 1; i >= 0; --i) {
        r[i] = s[length - 1 - i];
    }
    r[length] = '\0';
    return r;
}