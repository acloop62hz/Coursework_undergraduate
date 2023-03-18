#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define ERROR 1e5
typedef enum { push, pop, inject, eject, end } Operation;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Element;
    PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
    PtrToNode Front, Rear;
};
Deque CreateDeque();
int Push( ElementType X, Deque D );
ElementType Pop( Deque D );
int Inject( ElementType X, Deque D );
ElementType Eject( Deque D );

Operation GetOp();          /* details omitted */
void PrintDeque( Deque D ); /* details omitted */

int main()
{
    ElementType X;
    Deque D;
    int done = 0;

    D = CreateDeque();
    while (!done) {
        switch(GetOp()) {
        case push: 
            scanf("%d", &X);
            if (!Push(X, D)) printf("Memory is Full!\n");
            break;
        case pop:
            X = Pop(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case inject: 
            scanf("%d", &X);
            if (!Inject(X, D)) printf("Memory is Full!\n");
            break;
        case eject:
            X = Eject(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case end:
            PrintDeque(D);
            done = 1;
            break;
        }
    }
    return 0;
}

/* Your function will be put here */
Deque CreateDeque(){
	PtrToNode head;
	head=(PtrToNode)malloc(sizeof(struct Node));
	head->Last=NULL;
	head->Next=NULL;
	Deque k;
	k=(Deque)malloc(sizeof(struct DequeRecord));
	k->Front=head;
	k->Rear=head;
	return k;
} 
int Push( ElementType X, Deque D ){
	PtrToNode hnew;
	hnew=(PtrToNode)malloc(sizeof(struct Node));
	hnew->Element=X;
	PtrToNode next;
	next = D->Front->Next;
	if (next == NULL) {
		hnew->Next=NULL;
		D->Rear=hnew;
	}
	else {
		hnew->Next=next;
		next->Last=hnew;
	}
	hnew->Last=D->Front;
	D->Front->Next=hnew;
	return 1;
	
}
ElementType Pop( Deque D ){
	if(D->Front == D->Rear) return ERROR;
	else{
		PtrToNode n1;
		ElementType x; 
		x=D->Front->Next->Element;
		n1=D->Front->Next->Next;
		if(n1 == NULL) 	{
			if(D->Rear==D->Front->Next) D->Rear=D->Front;
			free(D->Front->Next);
			D->Front->Next=NULL;
		}
		else{
			n1->Last=D->Front;
			if(D->Rear==D->Front->Next) D->Rear=D->Front;
			free(D->Front->Next);
			D->Front->Next=n1;
		}
		return x;
	}
}
int Inject( ElementType X, Deque D ){
	PtrToNode rnew;
	rnew=(PtrToNode)malloc(sizeof(struct Node));
	rnew->Element=X;
	rnew->Last=D->Rear;
	rnew->Next=NULL;
	D->Rear->Next=rnew;	
	D->Rear=rnew;
	return 1;
}
ElementType Eject( Deque D ){
	if(D->Front == D->Rear) return ERROR;
	else{
		ElementType y;
		y=D->Rear->Element;
		PtrToNode p;
		p=D->Rear->Last;
		p->Next=NULL;
		free(D->Rear);
		D->Rear=p;
		return y;
	}
	
}

