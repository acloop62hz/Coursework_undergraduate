#include <stdio.h>
#include <stdlib.h>

typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30   /* max size of expression */

ElementType EvalPostfix( char *expr );

int main()
{
    ElementType v;
    char expr[Max_Expr];
    gets(expr);
    v = EvalPostfix( expr );
    if ( v < Infinity )
        printf("%f\n", v);
    else
        printf("ERROR\n");
    return 0;
}

/* Your function will be put here */
ElementType EvalPostfix( char *expr ){
	char *p=expr;
	double x[Max_Expr]={0.0};
	int j=0;
	int z=0;
	double f=0;
	while(*p){
		if(*p>='0'&&*p<='9'||*p=='-'&&(*(p+1)>='0'&&*(p+1)<='9')){
			int n1=Max_Expr/2;int n2=Max_Expr/2-1;int a[Max_Expr]={0};int sign=0;
			if(*p == '-') {sign=1;p++;}
			while(*p>='0'&&*p<='9'){
				a[n1]=*p-'0';
				n1=n1+1;
				p++;
			}
			for(int i=Max_Expr/2;i<n1;i++){
				z=z*10+a[i];
			}
			if(*p == '.'){
				p++;
				while(*p>='0'&&*p<='9'){
					a[n2]=*p-'0';
					n2=n2-1;
					p++;
				}
				for(int i=n2+1;i<=Max_Expr/2-1;i++){
					f=f*0.1+a[i]*1.0;
				}

			}
			x[j]=z+f*0.1;
			z=0;f=0;
			

			if(sign) x[j]=-x[j];
			j++;

			
		}
		else {
			while(*p != ' ' && *p!='\0'){
				if(j<2) return Infinity;
				double t;
				switch(*p){
					case '+': t=x[j-2]+x[j-1];break;
					case '-': t=x[j-2]-x[j-1];break;
					case '*': t=x[j-2]*x[j-1];break;
					case '/': {
						if (x[j-1]==0) return Infinity;                              
						else t=x[j-2]*1.0/x[j-1];break;
					}
					default: return Infinity;
				}
				x[j-2]=t;x[j-1]=0;
				j=j-1;
				p++;
			}
		}
		if(*p!='\0')p++;
	}
	if (j!=1) return Infinity;
	else return x[0];

} 