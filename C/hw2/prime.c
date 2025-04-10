#include <stdio.h>

void prime(int);

int main(){
	int num;
	printf("輸入一正整數: ");
	scanf("%d", &num);
	printf("小於等於 %d 的質數有: ", num);
    prime(num); 
    printf("\n"); 
    
    return 0;
}

void prime(int num){
	for(int i = 2; i <= num; i++){
		int count = 0;
		for(int j = 1; j <= i; j++){  // 檢查 i 的因數
            if(i % j == 0){
                count++;
            }
        }
		if(count==2){
			printf("%d ", i);
		}
	}
}
