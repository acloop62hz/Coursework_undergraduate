#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

List Read(); /* details omitted */
void Print( List L ); /* details omitted */
List Reverse( List L );

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

List Reverse( List L ){
	List a=L->Next,b=L->Next,c=L->Next;
	while (c&&c->Next){
			c=c->Next;
			if(b==L->Next) b->Next = NULL;
			else b->Next =a;
			a=b;
			b=c;
	}
	if(!c) return L;
	else if(c->Next == NULL){
		if(b==L->Next) b->Next = NULL;
		else b->Next =a;		
	} 
	L->Next=c;
	return L;
	
	
}