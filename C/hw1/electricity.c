#include <stdio.h>
#define NON_RATE1 1.63
#define NON_RATE2 2.10
#define NON_RATE3 2.89
#define NON_RATE4 3.94
#define NON_RATE5 4.60
#define NON_RATE6 5.03

#define BUSINESS_RATE1 2.12
#define BUSINESS_RATE2 2.91
#define BUSINESS_RATE3 3.44
#define BUSINESS_RATE4 5.05

double electricity(int type, double degrees);

void main(){
	int type;
    double degrees;     // 每月用電度數
    
    printf("請輸入用電類型 (1: 非營業用, 2: 營業用): ");
    scanf("%d", &type);
    
    printf("請輸入每月用電度數: ");
    scanf("%lf", &degrees);
    
    electricity(type, degrees);
    
    if(cost == -1){
    	printf("輸入錯誤的用電類型！\n");
	}else{
		printf("總電費為 %.0f 元", cost);
	}
}

double electricity(int type, double degrees){
	double cost = 0; 
	
	if (type == 1) { // 非營業用
        if (degrees <= 120) {
            cost = degrees * 1.63;
        }else if (degrees <= 330) {
            cost = 120 * NON_RATE1 + (degrees - 120) * NON_RATE2;
        }else if (degrees <= 500) {
            cost = 120 * NON_RATE1 + 210 * NON_RATE2 + (degrees - 330) * NON_RATE3;
        }else if (degrees <= 700) {
            cost = 120 * NON_RATE1 + 210 * NON_RATE2 + 170 * NON_RATE3 + (degrees - 500) * NON_RATE4;
        }else if (degrees <= 1000) {
            cost = 120 * NON_RATE1 + 210 * NON_RATE2 + 170 * NON_RATE3 + 200 * NON_RATE4 + (degrees - 700) * NON_RATE5;
        }else {
            cost = 120 * NON_RATE1 + 210 * NON_RATE2 + 170 * NON_RATE3 + 200 * NON_RATE4 + 300 * NON_RATE5 + (degrees - 1000) * NON_RATE6;
        }
	}else if (type == 2) { // 營業用
        if (degrees <= 330) {
            cost = degrees * BUSINESS_RATE1;
        } else if (degrees <= 700) {
            cost = 330 * BUSINESS_RATE1 + (degrees - 330) * BUSINESS_RATE2;
        } else if (degrees <= 1500) {
            cost = 330 * BUSINESS_RATE1 + 370 * BUSINESS_RATE2 + (degrees - 700) * BUSINESS_RATE3;
        } else {
            cost = 330 * BUSINESS_RATE1 + 370 * BUSINESS_RATE2 + 800 * BUSINESS_RATE3 + (degrees - 1500) * BUSINESS_RATE4;
        }
	}else{
        return -1;
    }
	
	return cost;
}
