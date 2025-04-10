#include <stdio.h>

int prime(int);
int isPrime(int);

int main(){
	int n;
	printf("��J�@�����: ");
	scanf("%d", &n);

    int result = prime(n);
    printf("�� %d �ӽ�ƬO %d", n, result);
    return 0;
}

int prime(int num){
	int count = 0;
	int current = 2; // �q 2 �}�l����
	
	while(count != num){
		if(isPrime(current)){  // �p�G current �O���
            count++;  // ���@�ӽ�ơAcount++
        }
        if(count == num){  // ���� num �ӽ��
            return current; 
        }
        current++;  // �~���U�@�Ӽ�
	}
}

int isPrime(int num){
	for(int i = 2; i * i <= num; i++){ //�p�G num ���B�~���]�ơA�@�w�|�b sqrt(num) ���e�Q���
		if(num % i == 0){ // �p�G��� num % i == 0�A�N�� num ���O���
	        return 0; // �u�n���@�Ӧ]�ơA�N�^�� 0�]���O��ơ^
	    }
	} 
	return 1; // �p�G�]����Ӱj�鳣�S���]�ơA���O���
}
