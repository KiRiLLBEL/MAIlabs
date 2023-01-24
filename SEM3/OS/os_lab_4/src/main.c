#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/mman.h>
#include <signal.h>
void sig_handler(int signum){
}
void sig_handler_1(int signum){
    kill(getppid(), SIGUSR1);
}
void sig_handler_2(int signum){
    kill(getppid(), SIGUSR1);
}
int main (void) {
    int pid1, pid2;
    char * ptr = mmap(NULL, 1, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);
    if(ptr == MAP_FAILED){
        perror("Not mmap");
    }
    if((pid1 = fork()) == 0) {
        int loop = 1;
        signal(SIGINT, SIG_DFL);
        signal(SIGUSR1, sig_handler_1);
        while (loop)
        {
            pause();
            if(ptr[0] >= 'A' && ptr[0] <= 'Z') {
                ptr[0] = ptr[0] + 32;
            }
        }
    }
    if(pid1 > 0 && (pid2 = fork()) == 0) {
        int loop = 1;
        signal(SIGINT, SIG_DFL);
        signal(SIGUSR1, sig_handler_2);
        while (loop)
        {
            pause();
            if(ptr[0] == ' ') {
                ptr[0] = '_';
            }
        }
    }
    if(pid1 == -1 || pid2 == -1) {
        perror("don't create child process");
        exit(EXIT_FAILURE);
    }
    if(pid1 == -1) {
        perror("don't create child1 process");
        exit(EXIT_FAILURE);
    }
    if(pid2 == -1) {
        perror("don't create child2 process");
        exit(EXIT_FAILURE);
    }
    if(pid1 != 0 && pid2 != 0) {
        signal(SIGUSR1, sig_handler);
        char c;
        int err;
        while(err = read(0, &c, 1) > 0) {
            ptr[0] = c;
            kill(pid1, SIGUSR1);
            kill(pid2, SIGUSR1);
            pause();
            printf("%c", ptr[0]);
        }
        kill(pid1, SIGINT);
        kill(pid1, SIGINT);
        waitpid(-1, NULL, 0);
        int errump = munmap(ptr, 1);
        if(errump != 0){
            perror("don't create child2 process");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}