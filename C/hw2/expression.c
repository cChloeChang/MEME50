#include <stdio.h>

int expression(int);

void main(){
	int num;
	scanf("%d", &num);
	printf("1^2-2^2+3^2-...-50^2 = %d\n", expression(num));
}

int expression (int num){
	int sum = 0;
	
	for(int i = 1; i <= 50; i++){
		if(num % 2 == 1){
			sum += i*i;
		}else{
			sum -= i*i;
		}
	}
	
	return sum;
}
