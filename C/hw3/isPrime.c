#include <stdio.h>

int isPrime(int);

int main(){
	int n;
	printf("��J�@�����: ");
	scanf("%d", &n);
//    isPrime(n); 

    int result = isPrime(n);
	if (result == 1) {
	    printf("%d �O���\n", n);
	} else {
	    printf("%d ���O���\n", n);
	}
    return 0;
}

int isPrime(int num){
//	int count = 1;
//	
//	for(int i = 2; i * i <= num; i++){ //�p�G num ���B�~���]�ơA�@�w�|�b sqrt(num) ���e�Q���
//		if(num % i == 0){
//	        count++;
//	    }
//	}
//	if(count == 2){
//		printf("%d �O���", num);
//		return 1;
//	}else{
//		printf("%d ���O���", num);
//		return 0;
//	}

	
	for(int i = 2; i * i <= num; i++){ //�p�G num ���B�~���]�ơA�@�w�|�b sqrt(num) ���e�Q���
		if(num % i == 0){ // �p�G��� num % i == 0�A�N�� num ���O���
	        return 0; // �u�n���@�Ӧ]�ơA�N�^�� 0�]���O��ơ^
	    }
	} 
	return 1; // �p�G�]����Ӱj�鳣�S���]�ơA���O���
}
