#include <stdio.h>

int factor(int);

void main(){
	int num;
	printf("��J�@�����: ");
	scanf("%d", &num);
	printf("%d ���]�Ƭ�", num);
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
