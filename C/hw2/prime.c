#include <stdio.h>

void prime(int);

int main(){
	int num;
	printf("��J�@�����: ");
	scanf("%d", &num);
	printf("�p�󵥩� %d ����Ʀ�: ", num);
    prime(num); 
    printf("\n"); 
    
    return 0;
}

void prime(int num){
	for(int i = 2; i <= num; i++){
		int count = 0;
		for(int j = 1; j <= i; j++){  // �ˬd i ���]��
            if(i % j == 0){
                count++;
            }
        }
		if(count==2){
			printf("%d ", i);
		}
	}
}
