#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isID(char id[]){
	char first_letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	int first_nums[] = {10, 11, 12, 13, 14, 15, 16, 17, 34, 18, 19, 20, 21, 22, 35, 23, 24, 25, 26, 27, 28, 29, 32, 30, 31, 33};
	
	// 檢查長度是否為10
    if(strlen(id) != 10){
        return 1;  // 長度不正確
    }
    
    // 檢查第一個字元是否為英文字母
    if(!isalpha(id[0])){
        return 1;  // 第一個字元不是字母
    }
    
    // 檢查第二個字元是否為1或2
    if(id[1] != '1' && id[1] != '2'){
        return 1;  // 第二個字元不是1或2
    }
    
    // 檢查第三至九個字元是否為數字
    for(int i = 2; i < 9; i++){
        if(!isdigit(id[i])){
            return 1;  // 不是數字
        }
    }
    
    // 驗證檢查碼
    // 找出第一個字母的對應數值
    int letter_value = 0;
    for(int i = 0; i < 26; i++){
        if(id[0] == first_letters[i]){
            letter_value = first_nums[i];
            break;
        }
    }
    
    // 計算檢查碼
    int sum = letter_value / 10 + (letter_value % 10) * 9;
    for(int i = 0; i < 8; i++){
        sum += (id[i+1] - '0') * (8 - i);
    }
    int check_digit = (10 - (sum % 10)) % 10;
    
    // 比較計算出的檢查碼與輸入的最後一位是否相同
    if(check_digit != (id[9] - '0')){
        return 1;  // 檢查碼不正確
    }
	
	return 0;
}

int main(){
	char data[11]; // C 的字串結尾需要 \0，所以長度要預留一個額外的空間
	printf("請輸入一身分證字號: \n");
	scanf("%10s", data); // 這裡 data 不需要加 &，因為陣列本身就是指標
	
	if(isID(data)){
        printf("無效的身分證字號\n");
    } else {
        printf("有效的身分證字號\n");
    }
    
    return 0;
}
