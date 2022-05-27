#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
int main (int argc, char ** argv) {
    	int fd1 = open("in1", O_RDONLY, O_NONBLOCK);
	int fd2 = open("in2", O_RDONLY, O_NONBLOCK);
	
	int stop1 = 0, stop2 = 0;
	
	int sum = 0;
	
	for (;;) {
		fd_set fds;
		int maxfd;
		int res;
		char buf[1];

		FD_ZERO(&fds);
		FD_SET(fd1, &fds);
		FD_SET(fd2, &fds);

		maxfd = fd1 > fd2 ? fd1 : fd2;

		select(maxfd + 1, &fds, NULL, NULL, NULL);

		
		if (FD_ISSET(fd1, &fds)) {
			res = read(fd1, buf, sizeof(buf));
			if (res > 0 && buf[0] != '\n') {
				int t;
				sscanf(buf, "%d", &t); 
				sum += t;
			} else if (res == 0) {
				stop1 = 1;
			}
		}
		
		if (FD_ISSET(fd2, &fds)) {		
			res = read(fd2, buf, sizeof(buf));
			if (res > 0 && buf[0] != '\n') {
				int t;
				sscanf(buf, "%d", &t); 
				sum += t;
			} else if (res == 0) {
				stop2 = 1;
			}
		}
		
		if (stop1 == 1 && stop2 == 1) {
			break;
		}
	}
	
	printf("%d\n", sum);
}