#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

void SignalHandle(int signal){
	switch(signal){
		case SIGHUP:
			printf("\nCatch signal: SIGHUP(%d)\n", signal);
			break;
		case SIGINT:
			printf("\nCatch signal: SIGINT(%d)\n", signal);
			break;
		case SIGQUIT:
			printf("\nCatch signal: SIGQUIT(%d)\n", signal);
			break;
		case SIGALRM:
			printf("\nCatch signal: SIGALRM(%d)\n", signal);
			break;
		default:
			printf("\nUnknown signal: %d\n", signal);
			break;
	}
}

int main(void){
	int sec_delay = 5;
	printf("Current process ID: %d\n", (int)getpid());
	
	signal(SIGINT, SignalHandle);
	signal(SIGQUIT, SignalHandle);
	signal(SIGALRM, SignalHandle);

	alarm(sec_delay);
	while(1){
		pause();
	}
	return 0;
}
