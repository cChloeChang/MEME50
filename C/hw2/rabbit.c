#include<stdio.h>

int rabbit();

int main(){
	int rabbits = rabbit();
	printf("�ߤl�̤֦� %d ��\n", rabbits);
    
	return 0;
}

int rabbit(){
	//�Ĥ@�ؼg�k 
	int x = 1;
	while(1){
		if(x % 3 == 1 && x % 5 == 3 && x % 7 == 2){
			return x;
		}
		x++;
	}
	
	//�ĤG�ؼg�k 
//	int x = 2;  // �q���� x % 7 = 2 ���̤p�ȶ}�l
//    while (!(x % 3 == 1 && x % 5 == 3)) {
//        x += 7;  // �u���ղŦX x % 7 = 2 ����
//    }
//	return x;
}
