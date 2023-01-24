#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "errorlib.h"


int main () {


    int fd1[2], fd2[2], fd3[2];
    if (pipe(fd1) == -1)
    {
        oerror("can't create a pipe fd1:", -1);
    }
    if (pipe(fd2) == -1)
    {
        oerror("can't create a pipe fd2:", -2);
    }
    if (pipe(fd3) == -1)
    {
        oerror("can't create a pipe fd3:", -3);
    }
    int pid1, pid2;
    if((pid1 = fork()) == 0) {
        if (dup2(fd1[0], STDIN_FILENO) == -1)
        {
            oerror("can't duplicate descriptor pipe 1:", -1);
        }
        if (dup2(fd3[1], STDOUT_FILENO) == -1)
        {
            oerror("can't duplicate descriptor pipe 2:", -2);
        }
        if (close(fd1[1]) == -1)
        {
            oerror("can't close pipe 1 write", -3);
        }
        if (close(fd3[0]) == -1)
        {
            oerror("can't close pipe 3 read:", -4);
        }
        if (close(fd2[1]) == -1)
        {
            oerror("can't close pipe 3 read:", -5);
        }
        if (close(fd2[0]) == -1)
        {
            oerror("can't close pipe 3 read:", -6);
        }
        if(execlp("./child1", "child1", NULL) == -1) {
            oerror("can't open file child1:", -7);
        }
    }
    if(pid1 > 0 && (pid2 = fork()) == 0) {
        if (dup2(fd2[1], STDOUT_FILENO) == -1)
        {
            oerror("can't duplicate descriptor pipe 2:", -1);
        }
        if (dup2(fd3[0], STDIN_FILENO) == -1)
        {
            oerror("can't duplicate descriptor pipe 3:", -2);
        }
        if (close(fd2[0]) == -1)
        {
            oerror("can't close pipe 2 read", -3);
        }
        if (close(fd3[1]) == -1)
        {
            oerror("can't close pipe 3 write:", -4);
        }
        if (close(fd1[1]) == -1)
        {
            oerror("can't close pipe 3 read:", -5);
        }
        if (close(fd1[0])== -1)
        {
            oerror("can't close pipe 3 read:", -6);
        }
        if(execlp("./child2", "child2", NULL) == -1) {
            oerror("can't open file child2:", -7);
        }
    }
    if(pid1 == -1 || pid2 == -1) {
        fprintf(stderr, "Can't create a child process");
        exit(-1);
    }
    if(pid1 == -1) {
        oerror("can't create process child1:", -4);
    }
    if(pid2 == -1) {
        oerror("can't create process child2:", -5);
    }
    if(pid1 != 0 && pid2 != 0) {
        char c;
        if(close(fd1[0]) == -1) {
            oerror("can't close pipe 1 read:", -6);
        }
        if(close(fd2[1]) == -1) {
            oerror("can't close pipe 1 read:", -7);
        }
        int err;
        while(err = read(0, &c, 1) > 0) {
            if(write(fd1[1], &c, 1) == -1) {
                oerror("can't write in pipe 1:", -9);
            }
            if(read(fd2[0], &c, 1) == -1) {
                oerror("can't read from pipe 2:", -10);
            }
            if(write(1, &c, 1) == -1) {
                oerror("can't write in stdout:", -11);
            }
        }
        if(err == -1) {
            oerror("can't write in pipe 1:", -8);
        }
        close(fd1[1]);
        close(fd2[0]);
        close(fd3[1]);
        close(fd3[0]);
        waitpid(-1, NULL, 0);
    }
    return 0;
}