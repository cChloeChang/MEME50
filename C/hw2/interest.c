#include <stdio.h>
#include <math.h>


int main(){
	double P = 100000; // ���� 100000 ��
    double r1 = 0.10;
    double r2 = 0.05;
    int n = 0; // �O���~��
    
    double money1 = P; // ���르���� 
    double money2 = P; // �q�Ӻ⪺�� 
    
    while (money2 <= money1){
		n++;
		money1 = P * (1 + r1 * n); // ������Q�p�� 
		money2 = P * pow((1 + r2), n);     // �q�Ӻ⪺�ƧQ�p�� 
	} 
	
	printf("�� %d �~��A�q�Ӻ⪺���N�W�L���르�C\n", n);
    printf("���ɡA���르�����B��: %.2f ��\n", money1);
    printf("�q�Ӻ⪺���B��: %.2f ��\n", money2);

    return 0;
}

