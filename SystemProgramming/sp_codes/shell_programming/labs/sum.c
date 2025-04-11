#include <stdio.h>

int main(void){
	int sum=1;
	for(int i=2; i<=100; i++){
		sum+=i;
	}
	printf("%d\n", sum);
}
