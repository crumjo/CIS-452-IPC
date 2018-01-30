#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

static pid_t pid, ppid;

void sigHandler0 (int sigNum) {
		if(pid){
			printf (" received.\n");
			// this is where shutdown code would be inserted
			sleep (1);
			printf ("Program will now exit.\n");
		}
		exit(0);
}


void sig_handler1(int sig_num) {
		printf("received a SIGUSR1 signal.\n");
}


void sig_handler2(int sig_num) {
		printf("received a SIGUSR2 signal.\n");
}


int main(int argc, char **argv) {
		
		ppid = getpid();
		signal(SIGINT, sigHandler0);
		signal(SIGUSR1, sig_handler1);
		signal(SIGUSR2, sig_handler2);

		if ((pid = fork()) < 0) {
				printf("Fork error.\n");
				exit(1);
		}
		
		if (!pid) { //child
				while(1) {
						
						srand(time(NULL));
						int r = rand() % 5 + 1;
						
						int r_sig = rand() % 2 + 0;
						
						sleep(r);
						if (r_sig) {
								kill(ppid, SIGUSR1);
						} else {
								kill(ppid, SIGUSR2);
						}
				}
		} else { //parent
				printf("Spawned child PID# %d\n", pid); 
				while(1) {
						printf("Waiting...     ");
						fflush(stdout);
						pause();
						
				}
		}
		return 0;
}