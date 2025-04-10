#include <stdio.h>

double my_fun(double x, int n);

int main(){
	double num1; 
	int num2;
	printf("enter two numbers: ");
	scanf("%lf %d", &num1, &num2);
	
	printf("answer = %lf\n", my_fun(num1, num2));
	return 0;
}

double my_fun(double x, int n){
	double sum = 0.0;
	
	for (int k = 1; k <= n; k++) { 
		double result1 = 1; // 重新初始化 x^k
		int result2 = 1; // 重新初始化 k!
		
		// 計算 x^k 
		for (int i = 1; i <= k; i++){ 
			result1 *= x; 
		} 
		
		// 計算 k! 
		for (int i = 2; i <= k; i++){ 
			result2 *= i; 
		} 
		sum += result1 / result2; 
	}
	return sum;
}
