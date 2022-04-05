/*
* Author:  Elad Shoham
* I.D: 205439649
* Date: 05/04/2022
*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void sig_handler(int signum)
{
	int i=5;
	int j=0;
	int k;
	switch (signum) {

        case SIGSEGV:
			printf("handle SIGSEGV\n");
            if (!(fork())) {
		        exit(1);
	        }
            break;
		case SIGCHLD:
			printf("handle SIGCHLD\n");
			fflush(stdout);
			raise(SIGUSR1);
			break;
		case SIGUSR1: 
			printf("handle SIGUSR1\n");
			fflush(stdout);
			k=i/j;
			break;
		case SIGFPE:
			printf("handle SIGFPE\n");
			alarm(1);
            sleep(2);
            break; 
        case SIGALRM:
            printf("handle SIGALRM\n");
            fflush(stdout);
            exit(1);
        }

}

void makeSegmentationFault() {
    int *a;
    *a = 0;
}

int main()
{
    signal(SIGSEGV, sig_handler); //for segmationFault
	signal(SIGCHLD, sig_handler); //for exit with a child
	signal(SIGUSR1, sig_handler); //my signal
	signal(SIGFPE, sig_handler); //for  division by zero
    signal(SIGALRM, sig_handler); //for the alarm
	makeSegmentationFault();
}
