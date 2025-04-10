#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isID(char id[]){
	char first_letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	int first_nums[] = {10, 11, 12, 13, 14, 15, 16, 17, 34, 18, 19, 20, 21, 22, 35, 23, 24, 25, 26, 27, 28, 29, 32, 30, 31, 33};
	
	// �ˬd���׬O�_��10
    if(strlen(id) != 10){
        return 1;  // ���פ����T
    }
    
    // �ˬd�Ĥ@�Ӧr���O�_���^��r��
    if(!isalpha(id[0])){
        return 1;  // �Ĥ@�Ӧr�����O�r��
    }
    
    // �ˬd�ĤG�Ӧr���O�_��1��2
    if(id[1] != '1' && id[1] != '2'){
        return 1;  // �ĤG�Ӧr�����O1��2
    }
    
    // �ˬd�ĤT�ܤE�Ӧr���O�_���Ʀr
    for(int i = 2; i < 9; i++){
        if(!isdigit(id[i])){
            return 1;  // ���O�Ʀr
        }
    }
    
    // �����ˬd�X
    // ��X�Ĥ@�Ӧr���������ƭ�
    int letter_value = 0;
    for(int i = 0; i < 26; i++){
        if(id[0] == first_letters[i]){
            letter_value = first_nums[i];
            break;
        }
    }
    
    // �p���ˬd�X
    int sum = letter_value / 10 + (letter_value % 10) * 9;
    for(int i = 0; i < 8; i++){
        sum += (id[i+1] - '0') * (8 - i);
    }
    int check_digit = (10 - (sum % 10)) % 10;
    
    // ����p��X���ˬd�X�P��J���̫�@��O�_�ۦP
    if(check_digit != (id[9] - '0')){
        return 1;  // �ˬd�X�����T
    }
	
	return 0;
}

int main(){
	char data[11]; // C ���r�굲���ݭn \0�A�ҥH���׭n�w�d�@���B�~���Ŷ�
	printf("�п�J�@�����Ҧr��: \n");
	scanf("%10s", data); // �o�� data ���ݭn�[ &�A�]���}�C�����N�O����
	
	if(isID(data)){
        printf("�L�Ī������Ҧr��\n");
    } else {
        printf("���Ī������Ҧr��\n");
    }
    
    return 0;
}
