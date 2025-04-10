#include <stdio.h>

int perfect_number(int);
void findPerfectNumbers(int);

void main(){
	int limit = 100;
	printf("100以內的完美數有: "); 
	findPerfectNumbers(limit);
}

int perfect_number(int num){
	int sum = 0;
	
	for(int i = 1; i <= num/2; i++){
		if(num % i == 0){
			sum += i;
		}
	}
	return sum == num;
}

void findPerfectNumbers(int limit){
	for (int i = 1; i <= limit; i++) { 
		if (perfect_number(i)) { 
			printf("%d ", i); 
		} 
	} 
	printf("\n");
}
