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
		printf("這不是一元二次方程式\n");
		return 1;
	}
	
	equation = b*b-4*a*c;
	if(equation>0){
		root1 = ((-b)+sqrt(b*b-4*a*c))/(2*a);
		root2 = ((-b)-sqrt(b*b-4*a*c))/(2*a);
		printf("有兩個不相等的實根%.2lf, %.2lf", root1, root2);
	}else if(equation==0){
		root1 = -b / (2 * a);
		printf("有兩個相等的實根%.2lf", root1);
	}else{
		printf("沒有實根");
	}
	return 0;
}
