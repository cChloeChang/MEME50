#include <stdio.h>

int isPrime(int);

int main(){
	int n;
	printf("块タ俱计: ");
	scanf("%d", &n);
//    isPrime(n); 

    int result = isPrime(n);
	if (result == 1) {
	    printf("%d 琌借计\n", n);
	} else {
	    printf("%d ぃ琌借计\n", n);
	}
    return 0;
}

int isPrime(int num){
//	int count = 1;
//	
//	for(int i = 2; i * i <= num; i++){ //狦 num Τ肂计﹚穦 sqrt(num) ぇ玡砆т
//		if(num % i == 0){
//	        count++;
//	    }
//	}
//	if(count == 2){
//		printf("%d 琌借计", num);
//		return 1;
//	}else{
//		printf("%d ぃ琌借计", num);
//		return 0;
//	}

	
	for(int i = 2; i * i <= num; i++){ //狦 num Τ肂计﹚穦 sqrt(num) ぇ玡砆т
		if(num % i == 0){ // 狦т num % i == 0 num ぃ琌借计
	        return 0; // 璶т计碞肚 0ぃ琌借计
	    }
	} 
	return 1; // 狦禲Ч俱癹伴常⊿т计ê琌借计
}
