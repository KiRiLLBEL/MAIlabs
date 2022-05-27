#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
void mysignal_handler(int signalmo) {
    exit(0);
}

int main(void) {
    pid_t pid;
	pid = fork();
	if (pid != 0) exit(EXIT_SUCCESS);
	chdir("/");
	setsid();
	signal(SIGURG , mysignal_handler);
	printf("%d\n", getpid());
	fclose(stdin);
	fclose(stdout);
	fclose(stderr);	
	while (1) {
		sleep(32);
	}
    return 0;
}