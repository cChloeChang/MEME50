#include <stdio.h>

void main(){
	int price_due, price_paid, change;
	int bills_1000 = 0, bills_500 = 0, bills_100 = 0;
    int coins_50 = 0, coins_10 = 0, coins_5 = 0, coins_1 = 0;
	
	printf("請輸入應付金額:");
	scanf("%d", &price_due);
	printf("請輸入實付金額:");
	scanf("%d", &price_paid);
	
	if(price_paid < price_due){
		printf("金額不足");
	}else if(price_paid == price_due){
		printf("不必找錢");
	}else{
		change = price_paid - price_due;
		
		if(change>=1000){
			bills_1000 = change / 1000;
			change %= 1000; //change/1000的餘數就是剩餘的零錢 
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
		//printf("找回%d張500元，%d張100元，%d個50元硬幣，%d個10元硬幣，%d個5元硬幣和%d個1元硬幣", bills_500, bills_100, coins_50, coins_10, coins_5, coins_1);
		
		printf("\n找回");
		if (bills_1000 > 0) printf("%d張1000元\n", bills_1000);
        if (bills_500 > 0) printf("%d張500元\n", bills_500);
        if (bills_100 > 0) printf("%d張100元\n", bills_100);
        if (coins_50 > 0) printf("%d個50元硬幣\n", coins_50);
        if (coins_10 > 0) printf("%d個10元硬幣\n", coins_10);
        if (coins_5 > 0) printf("%d個5元硬幣\n", coins_5);
        if (coins_1 > 0) printf("%d個1元硬幣\n", coins_1);
	}
	return 0;
} 
