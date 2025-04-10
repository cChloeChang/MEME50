#include <stdio.h>

int power(int x, int n);

void main(){
	int num1, num2, ans;
	printf("enter two numbers: ");
	scanf("%d %d", &num1, &num2);
	
	ans = power(num1, num2);
	printf("%d 的 %d 次方為 %d\n", num1, num2, ans);
}

int power(int x, int n){
	int result = 1;
	for (int i = 1; i <= n; i++){
		result *= x;
	}
	return result;
}
