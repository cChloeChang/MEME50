#include <stdio.h>

void prime(int);

int main(){
	int num;
	printf("块タ俱计: ");
	scanf("%d", &num);
	printf("单 %d 借计Τ: ", num);
    prime(num); 
    printf("\n"); 
    
    return 0;
}

void prime(int num){
	for(int i = 2; i <= num; i++){
		int count = 0;
		for(int j = 1; j <= i; j++){  // 浪琩 i 计
            if(i % j == 0){
                count++;
            }
        }
		if(count==2){
			printf("%d ", i);
		}
	}
}
