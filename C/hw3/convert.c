#include <stdio.h>

void toBinary(int n);
void toHexadecimal(int n);

int main(){
	int n;
	printf("please enter a number: ");
	scanf("%d", &n);
	printf("The result of %d converting to binary is ", n);
	toBinary(n);
	printf("\n");
	printf("The result of %d converting to hexidecimal is ", n);
	toHexadecimal(n);
	printf("\n");
}

void toBinary(int n){
	if (n == 0) { // 疭矪瞶 0
        printf("0");
        return;
    }
    
	int remainder_arr[32]; // ㄓ緇计 
	int index = 0;
	
	while(n > 0){
		remainder_arr[index++] = n % 2; // 緇计
    	n /= 2;
    	
	}
	 // 緇计块 
	for (int i = index - 1; i >= 0; i--) {
	    printf("%d", remainder_arr[i]);
	}

}

void toHexadecimal(int n){
	if (n == 0) { // 疭矪瞶 0
        printf("0");
        return;
    }
    
    /*  int 篈计计╰参琌 32 じτせ秈琌 4 じbits舱 ㄓボ计┮
	32 bits / 4 bits per digit = 8 digits */ 
	int remainder_arr[8]; // ㄓ緇计 
	int index = 0;
	
	while(n > 0){
		remainder_arr[index++] = n % 16; // 緇计
    	n /= 16;
    	
	}
//	// 緇计块 
//	for (int i = index - 1; i >= 0; i--) {
//		if(remainder_arr[i] == 10){
//			printf("A");
//		}else if(remainder_arr[i] == 11){
//			printf("B");
//		}else if(remainder_arr[i] == 12){
//			printf("C");
//		}else if(remainder_arr[i] == 13){
//			printf("D");
//		}else if(remainder_arr[i] == 14){
//			printf("E");
//		}else if(remainder_arr[i] == 15){
//			printf("F");
//		}else{
//			printf("%d", remainder_arr[i]);
//		}
//	}
	
	// 虏祏糶猭
	char hexChars[] = "0123456789ABCDEF";
	for (int i = index - 1; i >= 0; i--) {
	    printf("%c", hexChars[remainder_arr[i]]);
	}
 
}
