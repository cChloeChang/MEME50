#include<stdio.h>

int rope(int);

int main(){
	int length = 3000;
	int days = rope(length);
	printf("%d 公尺長的繩子，需剪 %d 天才會短於5公尺\n", length, days);
    
	return 0;
}

int rope(int length){
	int day = 0;
	while(length>=5){
		length /= 2 ;
		day++;
	} 
	return day;
}
