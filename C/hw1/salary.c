#include <stdio.h>

void main(){
	int hours;
	double salary = 0.0;
	
	printf("�п�J�u�@�ɼ� : ");
    scanf("%d", &hours);
    
    if(hours <= 60){
    	salary = hours * 150;
	}else if(hours <= 80){
		salary = 60 * 150 + (hours-60) * 150 * 1.25;
	}else{
		salary = 60 * 150 + 20 * 150 * 1.25 + (hours-80) * 150 * 1.5;
	}
	
	printf("�~�ꬰ %.2f ��\n", salary);
}
