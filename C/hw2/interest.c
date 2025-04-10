#include <stdio.h>
#include <math.h>


int main(){
	double P = 100000; // 本金 100000 元
    double r1 = 0.10;
    double r2 = 0.05;
    int n = 0; // 記錄年數
    
    double money1 = P; // 錢精打的錢 
    double money2 = P; // 郝細算的錢 
    
    while (money2 <= money1){
		n++;
		money1 = P * (1 + r1 * n); // 錢的單利計算 
		money2 = P * pow((1 + r2), n);     // 郝細算的複利計算 
	} 
	
	printf("第 %d 年後，郝細算的投資將超過錢精打。\n", n);
    printf("此時，錢精打的金額為: %.2f 元\n", money1);
    printf("郝細算的金額為: %.2f 元\n", money2);

    return 0;
}

