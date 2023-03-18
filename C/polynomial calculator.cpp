#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	float parameter;
	int index;
	struct node *next;
}Node;

struct pnode{
	struct node *head;
	struct node *tail;
};

void enter(struct pnode *p1,int e,float p){ 

	Node*n=(Node*)malloc(sizeof(Node));
	n->parameter=p;
	n->index=e;
	n->next=NULL;
	if(p1->head==NULL) p1->head=n;
	if(p1->tail==NULL) p1->tail=n;
	else{p1->tail->next=n;p1->tail=p1->tail->next;} 
}

void add(struct pnode *p1,struct pnode *p2,struct pnode *p3){
	Node *a=p1->head;Node *b=p2->head;Node *c;
	int i=0;
	while(a||b){
		enter(p3,i,a->parameter+b->parameter);
		i++;a=a->next;b=b->next;
	}
	c=a?a:b;
	p3->tail->next=c;
	
}
void dele(struct pnode *p1,struct pnode *p2,struct pnode *p3){
	Node *a=p1->head;Node *b=p2->head;Node *c;
	int i=0;
	while(a||b){
		enter(p3,i,a->parameter-b->parameter);
		i++;a=a->next;b=b->next;
	}
	c=a?a:b;
	p3->tail->next=c;
	
}
void muti(struct pnode *p1,struct pnode *p2,struct pnode *p3){
	Node *a=p1->head;Node *b=p2->head;

	struct pnode *tem=(struct pnode*)malloc(sizeof(struct pnode));
	tem->head=NULL;
	tem->tail=NULL;
	
	int i=0;int max;
	max=p1->tail->index+p2->tail->index;
	for(a;a;a=a->next){
		for(b=p2->head;b;b=b->next){
			enter(tem,a->index+b->index,a->parameter*b->parameter);}	
	};
	Node *c=tem->head;
	for(i=0;i<=max;i++){
		float para=0;
		for(c=tem->head;c;c=c->next){
			if(c->index==i) para=para+c->parameter;	
		}enter(p3,i,para);
		
	}
} 
	
	

void printanswer(struct pnode *p3){
	Node* o;o=p3->head;int flag=0;
	if(o->parameter==0)flag=1;
	else printf("%f",o->parameter);
	for(o=o->next;o;o=o->next){
		if(o->parameter>0){if(flag){printf("%fx^%d",o->parameter,o->index);flag=0;}else printf(" +%fx^%d",o->parameter,o->index);}
		if(o->parameter==0) continue;
		if(o->parameter<0)	printf("%fx^%d",o->parameter,o->index);
		
	}
	 
}



main(){
	struct pnode *p1=(struct pnode*)malloc(sizeof(struct pnode));
	struct pnode *p2=(struct pnode*)malloc(sizeof(struct pnode));
	struct pnode *p3=(struct pnode*)malloc(sizeof(struct pnode));
	p1->head=NULL;
	p1->tail=NULL;
	p2->head=NULL;
	p2->tail=NULL;
	p3->head=NULL;
	p3->tail=NULL;
	printf("请输入多项式1最高项次数：") ;
	int e;
	float p;
	scanf("%d",&e);
	while(e<0){printf("超出范围，请重新输入：");scanf("%d",&e);}
	int i;
	for(i=0;i<=e;i++){
		printf("请输入%d次项系数：",i);
		scanf("%f",&p);
		enter(p1,i,p);
	} 
	printf("请输入多项式2最高项次数："); 
	scanf("%d",&e);
	while(e<0){printf("超出范围，请重新输入：");scanf("%d",&e);}
	for(i=0;i<=e;i++){
		printf("请输入%d次项系数：",i);
		scanf("%f",&p);
		enter(p2,i,p);
	} 
	printf("请输入数字选择对两个多项式的运算：多项式1 ？ 多项式2 \n1.+\n2.-\n3.*\n");
	int choice;
	scanf("%d",&choice);
	if(choice==1) {add(p1,p2,p3);printanswer(p3);}
	if(choice==2) {dele(p1,p2,p3);printanswer(p3);}
	if(choice==3) {muti(p1,p2,p3);printanswer(p3);}
			
}
	
