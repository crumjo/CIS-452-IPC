#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>



void sigHandler0 (int sigNum) {
		printf (" received an interrupt.\n");
		// this is where shutdown code would be inserted
		sleep (1);
		printf ("Program will now exit.\n");
		exit(0);
}


void sig_handler1(int sig_num) {
		printf("Handler 1.\n");
}


void sig_handler2(int sig_num) {
		printf("Handler 2.\n");
}


int main(int argc, char **argv) {
		int pid;
		signal(SIGINT, sigHandler0);
		signal(SIGUSR1, sig_handler1);
		signal(SIGUSR2, sig_handler2);

		if ((pid = fork()) < 0) {
				printf("Fork error.\n");
				exit(1);
		} else if (pid) { //child
				while(1) {
						srand(time(NULL));
						int r = rand() % 5 + 1;
						printf("Random: %d\n", r);
						int r_sig = rand() % 2 + 0;
						printf("Signal Random: %d\n", r_sig);
						sleep(r);
						if (r_sig) {
								kill(pid, SIGUSR1);
						} else {
								kill(pid, SIGUSR2);
						}
				}
		} else { //parent
				while(1) {
						pause();
				}
		}
		return 0;
}
