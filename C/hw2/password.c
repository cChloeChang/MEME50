#include<stdio.h>
#include <string.h>

void password(const char*);

int main(){
	const char pwd[] = "abcdefgh";
	password(pwd);
    
	return 0;
}

void password(const char* pwd){
	int count_err = 0;
	char enter_pwd[50];
	
	while(count_err < 3){
		printf("請輸入密碼:");
		scanf("%s", &enter_pwd);
		
		if(strcmp(enter_pwd, pwd) == 0){ //strcmp(string1, string2)，用於比較兩個字串。==0表示字串完全相等 
			printf("密碼輸入正確，歡迎使用本系統！\n");
			return;
		}else{
			count_err++;
			if (count_err < 3) {
                printf("密碼錯誤！請再試一次。\n");
            }
		}
	}
	if(count_err == 3){
		printf("密碼輸入超過三次！");
	}
}
