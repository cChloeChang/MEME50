#include<stdio.h>

int rope(int);

int main(){
	int length = 3000;
	int days = rope(length);
	printf("%d ���ت���÷�l�A�ݰ� %d �Ѥ~�|�u��5����\n", length, days);
    
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
