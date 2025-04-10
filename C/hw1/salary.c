#include <stdio.h>

void main(){
	int hours;
	double salary = 0.0;
	
	printf("請輸入工作時數 : ");
    scanf("%d", &hours);
    
    if(hours <= 60){
    	salary = hours * 150;
	}else if(hours <= 80){
		salary = 60 * 150 + (hours-60) * 150 * 1.25;
	}else{
		salary = 60 * 150 + 20 * 150 * 1.25 + (hours-80) * 150 * 1.5;
	}
	
	printf("薪資為 %.2f 元\n", salary);
}
