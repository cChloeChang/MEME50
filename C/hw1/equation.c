#include <stdio.h>
#include<math.h>

double equation(double equation, double root1, double root2);

void main(){
	double a, b, c;
	
	printf("please enter a, b, c :");
	scanf("%lf %lf %lf", &a, &b, &c);

} 

double equation(double a, double b, double c){
	double equation, root1, root2;
	
	if(a==0){
		printf("�o���O�@���G����{��\n");
		return 1;
	}
	
	equation = b*b-4*a*c;
	if(equation>0){
		root1 = ((-b)+sqrt(b*b-4*a*c))/(2*a);
		root2 = ((-b)-sqrt(b*b-4*a*c))/(2*a);
		printf("����Ӥ��۵������%.2lf, %.2lf", root1, root2);
	}else if(equation==0){
		root1 = -b / (2 * a);
		printf("����Ӭ۵������%.2lf", root1);
	}else{
		printf("�S�����");
	}
	return 0;
}
