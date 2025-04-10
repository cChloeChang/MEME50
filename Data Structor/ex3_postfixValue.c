#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // for isdigit()

char result[100]; // 儲存轉換後的後序運算式 
char stack[100]; // 儲存運算子 

int prec(char); // 設定運算子的優先順序 
void infixToPostfix(char s[]);
int evaluatePostfix();

void main() {
	char expr[] = "99-7*(3+5)/4";
	printf("原算式: %s\n", expr);
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
        
        // 若為數字（包括多位數）
        if (isdigit(c)) { // isdigit(c)功能：判斷 c 是否為數字 0~9。 如果 c 是數字（例如 '9'） 
            result[result_idx++] = c; // 先存入第一個數字
            while (isdigit(expr[i + 1])) { // 檢查下一個字元是否仍是數字
                result[result_idx++] = expr[++i]; // 連續讀取數字（例如 "99"）
            }
            result[result_idx++] = ' '; // 分隔數字
        }else if (c == '(') {
            stack[++stack_idx] = c;
        }else if (c == ')') {
            while (stack_idx >= 0 && stack[stack_idx] != '(') {
                result[result_idx++] = stack[stack_idx--];
            }
            stack_idx--; // Pop '('
        }else { // 若為運算子（+ - * /）
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
 	
 	//只要stack還有東西，就依序丟出來 
    while (stack_idx >= 0)
        result[result_idx++] = stack[stack_idx--];
 
    result[result_idx] = '\0'; // 字串結束
    
}
 
int evaluatePostfix(char expr[]) {
    int stack[100]; // 儲存數值
    int stack_idx = -1;
    int num = 0;
    int isReadingNumber = 0;

    for (int i = 0; i < strlen(expr); i++) {
        char c = expr[i];

        if (isdigit(c)) { // 讀取數字
            num = num * 10 + (c - '0');
            isReadingNumber = 1;
        } 
        else if (c == ' ' && isReadingNumber) { // 遇到空格，數字結束
            stack[++stack_idx] = num;
            num = 0;
            isReadingNumber = 0;
        } 
        else if (c == '+' || c == '-' || c == '*' || c == '/') { // 讀取運算子
            int b = stack[stack_idx--]; // 取出第二個操作數
            int a = stack[stack_idx--]; // 取出第一個操作數
            int result = 0;

            switch (c) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
            }

            stack[++stack_idx] = result; // result放回 stack
        }
    }

    return stack[stack_idx]; // return最終結果
}
