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
	for(int i = 2; i * i <= n; i++){ //狦 num Τ肂计﹚穦 sqrt(num) ぇ玡砆т
		if(n % i == 0){
	        return 0; // 狦т num % i == 0璶т计碞ぃ琌借计
	    }
	} 
	return 1; // 狦禲Ч俱癹伴常⊿т计ê琌借计
}
