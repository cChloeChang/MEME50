#include <stdio.h>

void main(){
	int price_due, price_paid, change;
	int bills_1000 = 0, bills_500 = 0, bills_100 = 0;
    int coins_50 = 0, coins_10 = 0, coins_5 = 0, coins_1 = 0;
	
	printf("�п�J���I���B:");
	scanf("%d", &price_due);
	printf("�п�J��I���B:");
	scanf("%d", &price_paid);
	
	if(price_paid < price_due){
		printf("���B����");
	}else if(price_paid == price_due){
		printf("�������");
	}else{
		change = price_paid - price_due;
		
		if(change>=1000){
			bills_1000 = change / 1000;
			change %= 1000; //change/1000���l�ƴN�O�Ѿl���s�� 
		}
		if (change >= 500) {
            bills_500 = change / 500;
            change %= 500;
        }
        if (change >= 100) {
            bills_100 = change / 100;
            change %= 100;
        }
        if (change >= 50) {
            coins_50 = change / 50;
            change %= 50;
        }
        if (change >= 10) {
            coins_10 = change / 10;
            change %= 10;
        }
        if (change >= 5) {
            coins_5 = change / 5;
            change %= 5;
        }
        if (change >= 1) {
            coins_1 = change;
        }
		//printf("��^%d�i500���A%d�i100���A%d��50���w���A%d��10���w���A%d��5���w���M%d��1���w��", bills_500, bills_100, coins_50, coins_10, coins_5, coins_1);
		
		printf("\n��^");
		if (bills_1000 > 0) printf("%d�i1000��\n", bills_1000);
        if (bills_500 > 0) printf("%d�i500��\n", bills_500);
        if (bills_100 > 0) printf("%d�i100��\n", bills_100);
        if (coins_50 > 0) printf("%d��50���w��\n", coins_50);
        if (coins_10 > 0) printf("%d��10���w��\n", coins_10);
        if (coins_5 > 0) printf("%d��5���w��\n", coins_5);
        if (coins_1 > 0) printf("%d��1���w��\n", coins_1);
	}
	return 0;
} 
