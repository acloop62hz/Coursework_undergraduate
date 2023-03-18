#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node  {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read(); /* details omitted */
void Print( Polynomial p ); /* details omitted */
Polynomial Add( Polynomial a, Polynomial b );

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    return 0;
}

Polynomial Add( Polynomial a, Polynomial b ){
	
	Polynomial h;
	h =(Polynomial)malloc(sizeof(Polynomial));
	h->Next=NULL;
	
	Polynomial l=h;
	
	Polynomial pa,pb;
	pa=a->Next;pb=b->Next;
	int a1[1000]={0},b1[1000]={0};
	
	int amaxexp=0,bmaxexp=0;
	while(pa){
		a1[pa->Exponent]=pa->Coefficient;
		if(pa->Exponent > amaxexp) amaxexp=pa->Exponent;
		pa=pa->Next;
	}	
	while(pb){
		b1[pb->Exponent]=pb->Coefficient;
		if(pb->Exponent > bmaxexp) bmaxexp=pb->Exponent;
		pb=pb->Next;
	}
	int n;
	n=(amaxexp > bmaxexp)? amaxexp:bmaxexp;
	for(int i=n;i>=0;i--){
		if((a1[i]+b1[i])!= 0){
			Polynomial pc;
			pc = (Polynomial)malloc(sizeof(Polynomial));
			pc->Coefficient = a1[i]+b1[i];
			pc->Exponent=i;
			pc->Next= NULL;
			l->Next=pc;
			l=pc;
		}
	}
	return h;
	
}