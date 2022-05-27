#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#define MAXSIZE 5000
struct sockaddr_in local;
int cmp(const void *elem1, const void *elem2)
{
    char f = *((char*)elem1);
    char s = *((char*)elem2);
    if(f<s) return 1;
    if(f>s) return -1;

    return 0;
}
int main(int argc, char** argv)
{
    int s = socket (AF_INET, SOCK_STREAM, 0);
    int cs;
    int port = strtol(argv[1], NULL, 10);
    //printf("socket = %d\n", s);
    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(port);
    local.sin_family = AF_INET;

    int result = bind(s, (struct  sockaddr*) &local, sizeof(local));
    //printf("%d\n", result);
    listen(s, 1);
    cs = accept(s, NULL, NULL);
    char buf[MAXSIZE];
    for(; ;) {
        int size = read(cs, buf, MAXSIZE);
        if (strncmp(buf, "OFF", 3) == 0) {
            return 0;
        }
        qsort(buf, size, 1, cmp);
        write(cs, buf, size);
    }
    return 0;
}