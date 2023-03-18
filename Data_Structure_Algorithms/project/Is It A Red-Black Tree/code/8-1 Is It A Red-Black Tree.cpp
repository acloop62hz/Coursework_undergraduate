#include<stdio.h>
#include <stdlib.h>
#define Black 0
#define Red 1 

typedef struct TreeNode *Tree;
struct TreeNode {
	int color;
    int Element;
    int n;     // n stores the number of black nodes in all simple paths from the node to its descendant leaves
    Tree  Left;
    Tree  Right;
};

Tree addkey(Tree T,int a);
int islegal(Tree T);
int islegalr(Tree T);

main(){
	// get the number of inputs and creat an array of all the roots
	int k;
	scanf("%d",&k);
	int result[k];
	//for each root(the root will be set null first),build a tree using binary search tree inserting
	for (int i=0;i<k;i++){
		int n;
		scanf("%d",&n);
		Tree Treehead;
		Treehead= NULL;
		for(int j=0;j<n;j++){
			int a;
			scanf("%d",&a);
			Treehead= addkey(Treehead,a);
			if(islegal(Treehead)) result[i]=1;
			else result[i]=0;
		}
	}

	//print the results
	for(int i=0;i<k;i++){
		if(result[i]) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
	 
}
/*
 * binary search tree inserting
 * ------------------------------------------------
 *	 for a binary search tree, if a< the key of p, the position of a must be in the left subtree of p;if a> the key of p, the position of a must be in the right subtree of p 
 *   T: the root of the tree
 *	 a: the integer to be inserted
 *   h: a new node for a
 *   p: set a pointer of the root
 *   pb: Store p in pb, before setting p=p->Left or p=p->Right and do the next round
 
 *   while p is not null, do the search for the proper postition of a in the child of p. 
 *	 end: p=null,then put h in the position of p                                                        
 *   return: T
 */ 

Tree addkey(Tree T,int a){
	//create a new node for a
	Tree h;
	h=(Tree)malloc(sizeof(struct TreeNode));
	if(a<0){
		h->color = Red;
		h->Element= (-1)*a;	
	}
	else{
		h->color = Black;
		h->Element= a;			
	}
	h->Left= NULL;
	h->Right=NULL;
	h->n=0; 
	//if T is null, let h be the root of the tree
	if(T == NULL) return h; 
	else{
		Tree p;Tree pb;
		pb=T;p=T;
		while(p!= NULL){
			if(h->Element<p->Element){
				pb=p;  
				p=p->Left;
				if(p == NULL){pb->Left=h;break;}  //pb is the father of p when p is null
			}
			else{
				pb=p;
				p=p->Right;
				if(p == NULL){pb->Right=h;break;}
			}
			
		}	
		return T;
	}
	
	
}



 // judging if T is an empty tree or if the root of T is black

int islegal(Tree T){

	if(T == NULL) return 1;
	else if(T->color == Red) return 0;
	else
		return islegalr(T);
}

/*
 *  Recursive judging 
 * ------------------------------------------------
 *   T: the root of the tree
 *   While one or two children of T is presnt, iterate to judge if both of the subtrees of the root of T is a legal red-black tree and if the number of black nodes in all simple path from the root of both subtrees are the same.
 *   T->n = (the present child of T)->n+1 if T is a black node
 *   return 1 when T is a legal red-black tree ; return 0 when T is not a legal red-black tree
 */ 
int islegalr(Tree T){
	// case1 when both children is not present
	if (T->Left == NULL && T->Right == NULL) {
		T->n = ((T->color == Black)?1:0);  //T->n add 1 if T is a black node
		return 1;
	}
	//case2 when one child is present and the other is not
	else if(T->Left == NULL||T->Right == NULL){
		Tree tem;
		tem= (T->Left == NULL? T->Right : T->Left);
		//case 2.1 when the child that is present is black
		if(tem->color == Black) return 0;
		//case 2.2 when the child that is present is red
		else {
			if (islegalr(tem)){
				if(T->color == Black) T->n=tem->n+1;
				else T->n=tem->n; 
				return 1;
			}
			else return 0;
		}
	} 
	//case 3 when both children is present
	//judge if both children of a red node is black
	if(T->color == Red){
		if(T->Left->color == Red || T->Right->color == Red)
			return 0;
	}
	if(islegalr(T->Left) && islegalr(T->Right)){      //judge if both subtrees is a red-black tree
		if (T->Left->n == T->Right->n){               //judge if the number of black nodes in all simple paths from both children to thier descendant leaves is the same
			if(T->color == Black) T->n=T->Left->n+1;
			else T->n=T->Left->n; 
			return 1;
		} 
		else return 0;
	}
	else return 0;	
}
