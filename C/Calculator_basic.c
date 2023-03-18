#include <stdio.h>
#include <stdlib.h>
typedef struct stack {
	float data;
	char op;
	struct stack *next;
	struct stack *before;
	int ds;
}Stack;

struct pstack{
	struct stack *head;
	struct stack *tail;
	struct stack *tem;
};

int flagg=0;



void push(char *c,char rc,struct pstack *p1,int flag){
	Stack *n=(Stack*)malloc(sizeof(Stack));
	if(flag){
		float x;
		x=atof(c);
		n->data=x;
		n->op='$';
	}else {n->op=rc;n->data=0;}
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



int order(c){
		switch (c){
		case '+':return 1;
		case '-':return 1;
		case '*':return 2;
		case '/':return 2;
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
		default :flagg=1;break;
	}
	return f;	
}

main(){
	struct pstack *p1=(struct pstack *)malloc(sizeof(struct pstack));
	struct pstack *p2=(struct pstack*)malloc(sizeof(struct pstack));
	struct pstack *p3=(struct pstack*)malloc(sizeof(struct pstack));
	p1->head=NULL;
	p1->tail=NULL;
	p2->head=NULL;
	p2->tail=NULL;
	p3->head=NULL;
	p3->tail=NULL;
	int i=0,j=0;float x;
	char all[100],s[11];
	scanf("%s",all);
	while(all[i]){
		
		if(all[i]>=48&&all[i]<=57||all[i]=='.'){
			while((all[i]>=48&&all[i]<=57)||all[i]=='.'){
				s[j]=all[i];
				i++;j++;
			}s[j]='\0';
			j=0;push(s,'r',p2,1);continue;
		}
		
		if(all[i]=='+'||all[i]=='-'||all[i]=='*'||all[i]=='/'||all[i]=='('||all[i]==')'){
			if(all[i]==')'){
				if(p1->tail){
					Stack *b,*tem2;tem2=b=p1->tail; 
					while(b->op!='('){push("hhh",b->op,p2,0);if(b->ds==1) p2->tail->ds=1; b=b->before;free(tem2);tem2=b;}
					p1->tail=b->before;
				}else {printf("ERROR");return -1;}
				i++;
				continue;
		    }
			if((!(p1->tail))||(all[i]=='(')||p1->tail->op=='('||(order(all[i])>=order(p1->tail->op))){
				if((all[i]=='+'||all[i]=='-')&&all[i-1]=='('){push("hhh",all[i],p1,0);p1->tail->ds=1;i++;continue;}
				else {push("hhh",all[i],p1,0);p1->tail->ds=0;i++;continue;}
					
				}
			if(order(all[i])<order(p1->tail->op)) {
				Stack *b;b=p1->tail; 
				while(order(all[i])<order(b->op)&&b->op!='('){push("hhh",b->op,p2,0);if(b->ds==1) p2->tail->ds==1;b=b->before;}
				p1->tail=b->before;
				if((all[i]=='+'||all[i]=='-')&&all[i-1]=='('){push("hhh",all[i],p1,0);p1->tail->ds=1;i++;continue;}
				else {push("hhh",all[i],p1,0);p1->tail->ds=0;i++;continue;}
				}
				
				
		}

			
		}

	Stack *d;

	for(d=p1->tail;d;d=d->before){
		push("hhh",d->op,p2,0);
		if(d->ds==1) p2->tail->ds==1;
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
				else {ans=calculate(p3->tail->before->data,p3->tail->data,a->op);ttee=p3->tail;p3->tail->before->data=ans;p3->tail=p3->tail->before;free(ttee);}
		}
	
	}
}
	if(flagg){printf("ERROR");return -1;}
	printf("%f",ans);

}



/*	for(a=p2->tail;a;a=a->before){
		printf("%c\n",a->op);
	}
}*/
/*	Number *h;
	for(h=p1->tail;h;h=h->before){
		printf("%f\n",h->data);
	}*/
	
/*	float g=0;
	Number *h;Operator *f;
	h=p1->tail;f=p3->head;
	while(h->before){
		g=calculate(h->before->data,h->data,f->op);
		printf("%f\n",g);
		h->before->data=g;
		h=h->before;
		f=f->next;
	}
	printf("%f",p1->head->data);*/
	
	
	
	
	
/*addoperator('h',p3);
addoperator('a',p3);
addoperator('b',p3);*/

	 
/*ÎÊÌâ£¿	while((scanf("%d",&x))!=EOF){
		printf("%d\n",x);}
	while((c=getchar())!=EOF){
		printf("%c\n",c);	}*/ 
/*	char s[100];
	scanf("%s",s);
	while((scanf("%d",&x))!=EOF){
		
		Number *n=(*Number)malloc(sizeof(Number));
		n->data=c-48;
		
	}*/ 



