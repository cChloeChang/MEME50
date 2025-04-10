#include <stdio.h>

int factor(int);

void main(){
	int num;
	printf("輸入一正整數: ");
	scanf("%d", &num);
	printf("%d 的因數為", num);
	factor(num);
}

int factor(int num){
	//int factor[];
	
	for(int i = 1; i <= num; i++){
		if(num % i == 0){
			printf("%d ", i);
		}
	}
}
