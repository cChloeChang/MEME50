#include <stdio.h>
#include <math.h>

void armstrong();

int main(){
	printf("1000�H����armstrong�Ʀ�: \n"); 
	armstrong();
	return 0;
}

void armstrong(){
	for (int num = 100; num < 1000; num++) {  // �T��ƽd�� 100 ~ 999
		int sum = 0;
		
		int hundred = num / 100;
		int dec = num % 100 / 10;
		int unit = num % 10;
		
		sum = (int)pow(hundred,3) + (int)pow(dec, 3) + (int)pow(unit, 3);
		if(sum == num){
			printf("%d\n", sum);
		}
	}
} 
