#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
void mysignal_handler(int signalno) {
    exit(0);
}
int main(void) {
    pid_t mypid = getpid();
    signal(SIGURG, mysignal_handler);
    fprintf(stdout, "%d\n", mypid);
    daemon(0, 0);
    sleep(1000);
    return 0;
}