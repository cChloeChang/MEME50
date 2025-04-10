#include <stdio.h>
#define ROW 3
#define COL 5

void sales(){
	int sales_quantity[ROW][COL] = {{33, 32, 56, 45, 33}, {77, 33, 68, 45, 23}, {43, 55, 43, 67, 65}};
	int price[COL] = {12, 16, 10, 14, 15};
	char salespeople[ROW][8] = {"Jean", "Tom", "Tina"};
	char products[COL] = {'A', 'B', 'C', 'D', 'E'};
	
	
	// question a
	int tot_sales[ROW] = {0};
	printf("\n�C�@�ӾP������P���`���B: \n");
	for(int i=0; i<ROW; i++){
		for(int j=0; j<COL; j++){
			tot_sales[i] += sales_quantity[i][j] * price[j];
		}
		printf("%s ���`�P����B: %d\n", salespeople[i], tot_sales[i]);
	}
	
	// question b
	int max_sales = tot_sales[0];
	int bestSeller_index = 0;
	
	for(int i=0; i<ROW; i++){
		if(tot_sales[i] > max_sales){
			max_sales = tot_sales[i];
			bestSeller_index = i;
		}
	}
	printf("--------------------\n");
	printf("\n�P���`���B�̦h���P���: %s \n", salespeople[bestSeller_index]);

	// question c
	int tot_prodSales[COL] = {0}; 
	printf("\n--------------------\n");
	printf("\n�C�@�����~���P���`���B: \n");
	
	for(int j=0; j<COL; j++){
		for(int i=0; i<ROW; i++){
			tot_prodSales[j] += sales_quantity[i][j] * price[j];
		}
		printf("���~ %c ���`�P����B: %d\n", products[j], tot_prodSales[j]);
	}
	
	// question d
	int max_prodSales = tot_prodSales[0];
	int bestSellProd_index = 0;
	
	for(int j=0; j<COL; j++){
		if(tot_prodSales[j] > max_prodSales){
			max_prodSales = tot_prodSales[j];
			bestSellProd_index = j;
		}
	}
	printf("--------------------\n");
	printf("\n�P���`���B�̦h�����~: %c \n", products[bestSellProd_index]);

}

void main(){
	sales();
}
