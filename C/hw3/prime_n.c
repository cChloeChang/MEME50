#include <stdio.h>

int prime(int);
int isPrime(int);

int main(){
	int n;
	printf("輸入一正整數: ");
	scanf("%d", &n);

    int result = prime(n);
    printf("第 %d 個質數是 %d", n, result);
    return 0;
}

int prime(int num){
	int count = 0;
	int current = 2; // 從 2 開始找質數
	
	while(count != num){
		if(isPrime(current)){  // 如果 current 是質數
            count++;  // 找到一個質數，count++
        }
        if(count == num){  // 找到第 num 個質數
            return current; 
        }
        current++;  // 繼續找下一個數
	}
}

int isPrime(int num){
	for(int i = 2; i * i <= num; i++){ //如果 num 有額外的因數，一定會在 sqrt(num) 之前被找到
		if(num % i == 0){ // 如果找到 num % i == 0，代表 num 不是質數
	        return 0; // 只要找到一個因數，就回傳 0（不是質數）
	    }
	} 
	return 1; // 如果跑完整個迴圈都沒找到因數，那是質數
}
