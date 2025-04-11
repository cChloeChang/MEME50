#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	pid_t pid;
	pid = fork();
	
	switch(pid){
		case -1:
			perror("fork failed");
			exit(1);
		case 0:
			int sum=1;
			for(int i=2; i<=10; i++){
				sum+=i;
			}
			exit(sum);
		default:
			break;
	}
	
	if(pid!=0){ // 表示為parent process
		int status;
		pid_t child_pid;
		child_pid = wait(&status);

		if (WIFEXITED(status)) { // 檢查child process 是否正常退出
			int exit_code = WEXITSTATUS(status);
			printf("計算結果: %d\n", exit_code); // print result
		}else{
			printf("child did not exit normally\n");
		}
	}
	return 0;
}
