#include <stdio.h>

void pattern1();
void pattern2();
void pattern3();

void main(){
	pattern1(); 
	printf("\n"); 
	pattern2(); 
	printf("\n"); 
	pattern3(); 
	
	return 0;
}

void pattern1(){
	for(int i = 1; i <= 5; i++){
		for (int j = 1; j <= i; j++){
			printf("* "); 
		} 
		printf("\n");
	}
}

void pattern2(){
	/*
	for(int i = 5; i >= 1; i--){
		for (int j = 1; j <= i; j++){
			printf("* "); 
		} 
		printf("\n");
	}*/
	
	for (int i = 1; i <= 5; i++) { 
		// 印出空格，使星星圖案右對齊 
		for (int j = 1; j <= i; j++) { 
			printf("  "); 
		} 
		
		// 印出星星 
		for (int k = i; k <= 5; k++) { 
			printf("* "); 
		} 
		printf("\n"); 
	}
}

/* 外層的 for 迴圈用來控制列數，內層的兩個 for 迴圈分別控制空格數量和星星數量。
1.列數迴圈：從1開始到5（假設三角形有5行），每次迴圈代表圖形的一行。

2.空格數量：對於每一行，我們需要先印出適當數量的空格，空格的數量為（總行數 - 當前行數），這樣可以使星星圖案居中對齊
第一行：4個空格 + 1顆星星
第二行：3個空格 + 3顆星星
第三行：2個空格 + 5顆星星
第四行：1個空格 + 7顆星星
第五行：0個空格 + 9顆星星
所以空格數量 = 總行數 - 當前行數

3.星星數量：在印完空格之後，緊接著印出相應數量的星星，星星的數量為（2 * 當前行數 - 1） */

void pattern3(){
	for (int i = 1; i <= 5; i++) { 
		for (int j = 1; j <= 5 - i; j++) { 
			printf(" "); 
		} 
		
		for (int k = 1; k <= 2 * i - 1; k++) { 
			printf("*"); 
		} 
		
		printf("\n"); 
	}
}
