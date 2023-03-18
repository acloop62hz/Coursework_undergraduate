#include "acllib.h"
#include <math.h>
#include <string.h>
#include <stdio.h>


typedef struct stack {                     //栈// 
	float data;
	char op;
	struct stack *next;
	struct stack *before;                 ////？ 
	int ds;
}Stack;

struct pstack{                            //栈的指针的指针// 
	struct stack *head;
	struct stack *tail;
	struct stack *tem;
};

int flagg=0;



void push(char *c,char rc,struct pstack *p1,int flag){   //入栈// 
	Stack *n=(Stack*)malloc(sizeof(Stack));
	if(flag){                                          //flag=1,栈入数字// 
		float x;
		x=atof(c);
		n->data=x;
		n->op='$';
	}else {n->op=rc;n->data=0;}                       //flag=0 栈中存入字符// 
		n->ds=0;
		n->next=NULL;
		n->before=NULL; 
		if(p1->head==NULL)p1->head=n;
		if(p1->tail==NULL){p1->tail=n;p1->tem=n;}
		else {p1->tail->next=n;p1->tail=p1->tail->next;
		p1->tail->before=p1->tem;p1->tem=p1->tem->next;} 
		
	
} 
void pushd(struct pstack *p1,float flag){
	Stack *n=(Stack*)malloc(sizeof(Stack));
		n->data=flag;
		n->op='$';
		n->next=NULL;
		n->ds=0;
		n->before=NULL; 
		if(p1->head==NULL)p1->head=n;
		if(p1->tail==NULL){p1->tail=n;p1->tem=n;}
		else {p1->tail->next=n;p1->tail=p1->tail->next;
		p1->tail->before=p1->tem;p1->tem=p1->tem->next;} 
		
	
} 



int order(char c){                                           //优先级///                
		switch (c){
		case '+':return 1;
		case '-':return 1;
		case '*':return 2;
		case '/':return 2;
		case 's':return 3;
		case 'c':return 3;
	}
}

float calculate(float a,float b,char c){
	float f;
	switch(c){
		case '+':f=a+b;break;
		case '-':f=a-b;break;
		case '*':f=a*b;break;
		case '/':{
			if(b==0){ flagg=1; f=2;break;}
			f=a/b;break;
		}
		case 's':f = sin(b);break;
		case 'c':f = cos(b);break;
		default :flagg=1;break;
	}
	return f;	
}

char* trans(char *all,char *yl){
	int i=0,j=0;
	for(i=0,j=0;all[i];i++,j++){
		if(all[i]=='s'||all[i]=='c'){
			yl[j]=all[i];
			i=i+2;
		}
		else yl[j]=all[i];
		
	}
	yl[j]='\0';
	return yl;
}

float ator(char *tem,int al){
	struct pstack *p1=(struct pstack *)malloc(sizeof(struct pstack));
	struct pstack *p2=(struct pstack*)malloc(sizeof(struct pstack));
	struct pstack *p3=(struct pstack*)malloc(sizeof(struct pstack));
	p1->head=NULL;
	p1->tail=NULL;
	p2->head=NULL;
	p2->tail=NULL;
	p3->head=NULL;
	p3->tail=NULL;
	int i=0,j=0,flagfn=1;float x;
	char s[11];
	char yl[100];
	char *all = NULL;
	all=trans(tem,yl);
	int i2;
	
	for(i2=0;all[i2];i2++){                                                 //情况1：只有数字 
		if(!(all[i2]>='0'&&all[i2]<='9'||all[i2]=='.')) {flagfn=0;break;}
	}
	if(flagfn){printf("%f",atof(all));return 0;}
	
	flagfn=1;
	
	for(i2=0;all[i2];i2++){                                                 //情况1：只有数字 
		if(!(all[i2]=='x')) {flagfn=0;break;}
	}
	if(flagfn){printf("%f",atof(all));return 0;}
	
	while(all[i]){
		
		if(all[i]>=48&&all[i]<=57||all[i]=='.'){                               //判断是数字 
			while((all[i]>=48&&all[i]<=57)||all[i]=='.'){
				s[j]=all[i];
				i++;j++;
			}s[j]='\0';
			j=0;push(s,'r',p2,1);continue;
		}
		if(all[i]=='x'){
			push("hhh",'$',p2,0);p2->tail->data=al;i++;continue;
		}
		if(all[i]=='+'||all[i]=='-'||all[i]=='*'||all[i]=='/'||all[i]=='('||all[i]==')'||all[i]=='s'||all[i]=='c'){        //判断是符号 
			if(all[i]==')'){
				if(p1->tail){
					Stack *b,*tem2;tem2=b=p1->tail; 
					while(b->op!='('){push("hhh",b->op,p2,0);if(b->ds==1) p2->tail->ds=1; b=b->before;free(tem2);tem2=b;}
					p1->tail=b->before;p1->tem=p1->tail;
				}else {printf("ERROR");return -1;}
				i++;
				continue;
		    }
		    	
			
			if((!(p1->tail))||(all[i]=='(')||p1->tail->op=='('||(order(all[i])>=order(p1->tail->op))){
				if(((all[i]=='+'||all[i]=='-')&&all[i-1]=='(')||all[i]=='s'||all[i]=='c'){push("hhh",all[i],p1,0);p1->tail->ds=1;i++;continue;}
				else {push("hhh",all[i],p1,0);p1->tail->ds=0;i++;continue;}
					
				}
			if(order(all[i])<order(p1->tail->op)) {
				Stack *b;b=p1->tail; 
				while(b&&order(all[i])<order(b->op)&&b->op!='('){push("hhh",b->op,p2,0);if(b->ds==1) p2->tail->ds=1;b=b->before;}
				if(b){p1->tail=b;p1->tem=p1->tail;}
				else p1->tail=NULL;
				if(((all[i]=='+'||all[i]=='-')&&all[i-1]=='(')||all[i]=='s'||all[i]=='c'){push("hhh",all[i],p1,0);p1->tail->ds=1;i++;continue;}
				else {push("hhh",all[i],p1,0);p1->tail->ds=0;i++;continue;}
				}
			}
				
				
		}

			
		

	Stack *d;

	for(d=p1->tail;d;d=d->before){
		push("hhh",d->op,p2,0);
		if(d->ds==1) p2->tail->ds=1;
	}
	
	
	Stack *a,*ttee;
	a=p2->head;
	float ans;
	for(a;a;a=a->next){
		if(a->op=='$') pushd(p3,a->data);
		else {
			if(p3->tail==0) {printf("ERROR");return -1;}
			else if(p3->tail->before==0) {ans=calculate(0,p3->tail->data,a->op);p3->tail->data=ans;}
			else {
				if(a->ds==1) {ans=calculate(0,p3->tail->data,a->op);p3->tail->data=ans;}
				else {ans=calculate(p3->tail->before->data,p3->tail->data,a->op);ttee=p3->tail;p3->tail->before->data=ans;
				p3->tail=p3->tail->before;free(ttee);p3->tem=p3->tail;}
		}
	
	}
}
	if(flagg){printf("ERROR");return -1;}
return ans;
	
}




void init(){
	beginPaint();
	setPenWidth(2);
	line(0,300,800,300);
	line(790,290,800,300);
	line(790,310,800,300);
	line(400,0,400,600);
	line(390,10,400,0);
	line(410,10,400,0);

	int i;
	char c[4]; 

	for(i=3;i>=-3;i--){ 
	itoa(i*10,c,10);
	paintText(400,100*(3-i),c);
	} 
	

	for(i=-4;i<=4;i++){ 
	itoa(i*10,c,10);
	paintText(100*(i+4),300,c);
	} 
	endPaint();
}

void enterin(char *hh,float *y,int n){
	int i;
	for(i=-40;i<=40;i++){
		y[i+40]=300-ator(hh,i)*n;
	}
	return ;	
}

int Setup()
{
	initWindow("Test",DEFAULT,DEFAULT,800,600);
	initConsole(); 
	printf("输入一个公式，可以包含以下符号：\"+\"\",\",\"*\",\"/\",\"()\";可以包含以下函数：\"sin()\",\"cos()\"\n");
	char ss[100];
	float pre[81];
	scanf("%s",ss);
	enterin(ss,pre,10);
	int i;

	init();
	beginPaint();
	for(i=0;i<=80;i++){
		if(pre[i]>=600||pre[i]<=0) continue;
		line((i-1)*10,pre[i-1],i*10,pre[i]);

	}
	endPaint();

	return 0;
/*	int i;
	char y[810];
	for(i=-400;i<=400;i++){
		y[i+400]=ator("1+x",i);
	}
	
	init();
	beginPaint();
	for(i=0;i<=800;i++){
		putPixel(i,y[i],BLACK);
	}
	endPaint();
		*/
	
} 

