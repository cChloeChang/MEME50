#include <stdio.h>

void pattern1();
void pattern2();
void pattern3();

void main(){
	pattern1(); 
	printf("\n"); 
	pattern2(); 
	printf("\n"); 
	pattern3(); 
	
	return 0;
}

void pattern1(){
	for(int i = 1; i <= 5; i++){
		for (int j = 1; j <= i; j++){
			printf("* "); 
		} 
		printf("\n");
	}
}

void pattern2(){
	/*
	for(int i = 5; i >= 1; i--){
		for (int j = 1; j <= i; j++){
			printf("* "); 
		} 
		printf("\n");
	}*/
	
	for (int i = 1; i <= 5; i++) { 
		// �L�X�Ů�A�ϬP�P�Ϯץk��� 
		for (int j = 1; j <= i; j++) { 
			printf("  "); 
		} 
		
		// �L�X�P�P 
		for (int k = i; k <= 5; k++) { 
			printf("* "); 
		} 
		printf("\n"); 
	}
}

/* �~�h�� for �j��Ψӱ���C�ơA���h����� for �j����O����Ů�ƶq�M�P�P�ƶq�C
1.�C�ưj��G�q1�}�l��5�]���]�T���Φ�5��^�A�C���j��N��ϧΪ��@��C

2.�Ů�ƶq�G���C�@��A�ڭ̻ݭn���L�X�A��ƶq���Ů�A�Ů檺�ƶq���]�`��� - ��e��ơ^�A�o�˥i�H�ϬP�P�Ϯש~�����
�Ĥ@��G4�ӪŮ� + 1���P�P
�ĤG��G3�ӪŮ� + 3���P�P
�ĤT��G2�ӪŮ� + 5���P�P
�ĥ|��G1�ӪŮ� + 7���P�P
�Ĥ���G0�ӪŮ� + 9���P�P
�ҥH�Ů�ƶq = �`��� - ��e���

3.�P�P�ƶq�G�b�L���Ů椧��A�򱵵ۦL�X�����ƶq���P�P�A�P�P���ƶq���]2 * ��e��� - 1�^ */

void pattern3(){
	for (int i = 1; i <= 5; i++) { 
		for (int j = 1; j <= 5 - i; j++) { 
			printf(" "); 
		} 
		
		for (int k = 1; k <= 2 * i - 1; k++) { 
			printf("*"); 
		} 
		
		printf("\n"); 
	}
}
