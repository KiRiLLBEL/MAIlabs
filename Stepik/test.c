#include <stdlib.h>
#include <stdio.h>

int cmp(const void *elem1, const void *elem2)
{
    char f = *((char*)elem1);
    char s = *((char*)elem2);
    if(f<s) return 1;
    if(f>s) return -1;

    return 0;
}

int main() {
    char a[3] = "ab\0";
    qsort(a, 3, 1, cmp);
    printf("%s", a);
}