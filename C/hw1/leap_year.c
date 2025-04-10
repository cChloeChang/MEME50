#include <stdio.h>

void main(){
	int year;
	
	printf("enter year: ");
	scanf("%d", &year);
	
	if((year%4==0 && year%100!=0) || (year%400==0)){
		printf("%d 年是閏年\n", year);
	}else{
		printf("%d 年不是閏年\n", year);
	}
	return 0;
}
