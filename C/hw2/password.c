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
		printf("�п�J�K�X:");
		scanf("%s", &enter_pwd);
		
		if(strcmp(enter_pwd, pwd) == 0){ //strcmp(string1, string2)�A�Ω�����Ӧr��C==0��ܦr�꧹���۵� 
			printf("�K�X��J���T�A�w��ϥΥ��t�ΡI\n");
			return;
		}else{
			count_err++;
			if (count_err < 3) {
                printf("�K�X���~�I�ЦA�դ@���C\n");
            }
		}
	}
	if(count_err == 3){
		printf("�K�X��J�W�L�T���I");
	}
}
