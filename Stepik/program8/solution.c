#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
int sig1 = 0;
int sig2 = 0;
void mysignal_handler1(int signalno) {
    ++sig1;
}
void mysignal_handler2(int signalno) {
    ++sig2;
}
void mysignal_handler3(int signalno) {
    fprintf(stdout, "%d %d\n", sig1, sig2);
        exit(0);
}

int main() {
    signal(SIGUSR1, mysignal_handler1);
    signal(SIGUSR2, mysignal_handler2);
    signal(SIGTERM, mysignal_handler3);
    while(1) {
        usleep(500000);
    }
}