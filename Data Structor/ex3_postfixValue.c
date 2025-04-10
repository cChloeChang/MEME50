#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // for isdigit()

char result[100]; // �x�s�ഫ�᪺��ǹB�⦡ 
char stack[100]; // �x�s�B��l 

int prec(char); // �]�w�B��l���u������ 
void infixToPostfix(char s[]);
int evaluatePostfix();

void main() {
	char expr[] = "99-7*(3+5)/4";
	printf("��⦡: %s\n", expr);
	infixToPostfix(expr);
	printf("Postfix: %s\n", result);
	printf("Evaluation Result: %d\n", evaluatePostfix(result));
}

int prec(char c) {
    if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}
  
void infixToPostfix(char expr[]) {
    int result_idx = 0;
    int stack_idx = -1;
    
    for (int i = 0; i < strlen(expr); i++) {
        char c = expr[i];
        
        // �Y���Ʀr�]�]�A�h��ơ^
        if (isdigit(c)) { // isdigit(c)�\��G�P�_ c �O�_���Ʀr 0~9�C �p�G c �O�Ʀr�]�Ҧp '9'�^ 
            result[result_idx++] = c; // ���s�J�Ĥ@�ӼƦr
            while (isdigit(expr[i + 1])) { // �ˬd�U�@�Ӧr���O�_���O�Ʀr
                result[result_idx++] = expr[++i]; // �s��Ū���Ʀr�]�Ҧp "99"�^
            }
            result[result_idx++] = ' '; // ���j�Ʀr
        }else if (c == '(') {
            stack[++stack_idx] = c;
        }else if (c == ')') {
            while (stack_idx >= 0 && stack[stack_idx] != '(') {
                result[result_idx++] = stack[stack_idx--];
            }
            stack_idx--; // Pop '('
        }else { // �Y���B��l�]+ - * /�^
            while (stack_idx >= 0 && prec(c) <= prec(stack[stack_idx])) {
                result[result_idx++] = stack[stack_idx--];
            }
            stack[++stack_idx] = c;
        }
        
        
//        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
//            result[result_idx++] = c;
//        else if (c == '(')
//            stack[++stack_idx] = c;
//        else if (c == ')') {
//            while (stack_idx >= 0 && stack[stack_idx] != '(') {
//                result[result_idx++] = stack[stack_idx--];
//            }
//            stack_idx--; // Pop '('
//        }
//        else { //+-*/
//            while (stack_idx >= 0 && prec(c) <= prec(stack[stack_idx])) {
//                result[result_idx++] = stack[stack_idx--];
//            }
//            stack[++stack_idx] = c;
//        }
    }
 	
 	//�u�nstack�٦��F��A�N�̧ǥ�X�� 
    while (stack_idx >= 0)
        result[result_idx++] = stack[stack_idx--];
 
    result[result_idx] = '\0'; // �r�굲��
    
}
 
int evaluatePostfix(char expr[]) {
    int stack[100]; // �x�s�ƭ�
    int stack_idx = -1;
    int num = 0;
    int isReadingNumber = 0;

    for (int i = 0; i < strlen(expr); i++) {
        char c = expr[i];

        if (isdigit(c)) { // Ū���Ʀr
            num = num * 10 + (c - '0');
            isReadingNumber = 1;
        } 
        else if (c == ' ' && isReadingNumber) { // �J��Ů�A�Ʀr����
            stack[++stack_idx] = num;
            num = 0;
            isReadingNumber = 0;
        } 
        else if (c == '+' || c == '-' || c == '*' || c == '/') { // Ū���B��l
            int b = stack[stack_idx--]; // ���X�ĤG�Ӿާ@��
            int a = stack[stack_idx--]; // ���X�Ĥ@�Ӿާ@��
            int result = 0;

            switch (c) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
            }

            stack[++stack_idx] = result; // result��^ stack
        }
    }

    return stack[stack_idx]; // return�̲׵��G
}
