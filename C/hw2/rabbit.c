#include<stdio.h>

int rabbit();

int main(){
	int rabbits = rabbit();
	printf("兔子最少有 %d 隻\n", rabbits);
    
	return 0;
}

int rabbit(){
	//第一種寫法 
	int x = 1;
	while(1){
		if(x % 3 == 1 && x % 5 == 3 && x % 7 == 2){
			return x;
		}
		x++;
	}
	
	//第二種寫法 
//	int x = 2;  // 從滿足 x % 7 = 2 的最小值開始
//    while (!(x % 3 == 1 && x % 5 == 3)) {
//        x += 7;  // 只測試符合 x % 7 = 2 的數
//    }
//	return x;
}
