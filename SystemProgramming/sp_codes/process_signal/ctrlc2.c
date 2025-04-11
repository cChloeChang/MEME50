#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig){
	printf("\nOUCH! - I got signal %d\n", sig);
}

int main(){
	struct sigaction act;
	act.sa_handler = ouch;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, 0);
	// 上面五行把原本(void)signal(SIGINT, ouch);拆成五行做

	while(1){
		printf("hello world\n");
		sleep(1);
	}
}
