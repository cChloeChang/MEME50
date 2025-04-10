#include <stdio.h>
#include <math.h>

int isMersennePrime(int);
int isPrime(int);

int main(){
	int count = 0;
	int p = 2;
	
	while(count < 6){
		int number = pow(2, p) - 1;
		
		if(isMersennePrime(number)){ // if isMersennePrime(number) == 1
			printf("%d ", number);
			count++;
		}
		p++;
	}
	
	return 0;
}

int isMersennePrime(int n){
	if(!isPrime(n)){
		return 0;
	}
	
	int p = 1;
	
	while(pow(2, p) - 1 != n){
		p++;
	}
	
	return (pow(2, p) - 1 == n);
}

int isPrime(int n){
	for(int i = 2; i * i <= n; i++){ //�p�G num ���B�~���]�ơA�@�w�|�b sqrt(num) ���e�Q���
		if(n % i == 0){
	        return 0; // �p�G��� num % i == 0�A�Y�u�n���@�Ӧ]�ơA�N���O���
	    }
	} 
	return 1; // �p�G�]����Ӱj�鳣�S���]�ơA���O���
}
