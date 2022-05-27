#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#define MAXSIZE 5120
struct sockaddr_in local;

int main(int argc, char** argv)
{
    int s = socket (AF_INET, SOCK_DGRAM, 0);
    int port = strtol(argv[1], NULL, 10);
    //printf("socket = %d\n", s);
    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(port);
    local.sin_family = AF_INET;

    int result = bind(s, (struct  sockaddr*) &local, sizeof(local));
    //printf("%d\n", result);
    
    char buf[MAXSIZE];

    for(; ;) {
        int size = read(s, buf, MAXSIZE);
        buf[size] = '\0';
        if (strncmp(buf, "OFF\n", 4) == 0) {
            return 0;
        }
        fprintf(stdout, "%s\n", buf);
    }
    return 0;
}