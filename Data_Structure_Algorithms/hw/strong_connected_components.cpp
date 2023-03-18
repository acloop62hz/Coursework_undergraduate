#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

/* Your function will be put here */
int a[MaxVertices][MaxVertices];
int visited[MaxVertices];
int num[MaxVertices];
int count;

void DFS1(Vertex V,Graph G){
	visited[V]=1;
	int j;
	for(j=0;j<G->NumOfVertices;j++){
		if(a[V][j]>0&&(!visited[j]))
		DFS1(j,G);
	}
	num[V]= ++count;
}

void DFS2(Vertex V,Graph G,void (*visit)(Vertex V)){
	visit(V);
	visited[V]=1;
	int j;
	for(j=0;j<G->NumOfVertices;j++){
		if(a[V][j]>0&&(!visited[j]))
		DFS2(j,G,visit);
	}
}
int findmax(Graph G){
	int max,i;
	int mp;
	max=num[0];mp=0;
	for(i=0;i<G->NumOfVertices;i++){
		if (num[i]>max) {
			max=num[i];
			mp=i;
		}
	}
	num[mp]=0; 
	return mp;
}
	

			
	
void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ){
	int i,p,j1,j2;
	for(j1=0;j1<G->NumOfVertices;j1++){
		for(j2=0;j2<G->NumOfVertices;j2++){
			a[j1][j2]=-1;
		}
	}
	for(i=0;i<G->NumOfVertices;i++){
		PtrToVNode p;
		p=G->Array[i];
		while(p){
			a[i][p->Vert]=1;
			p=p->Next;
		}
	}
		
	for(i=0;i<G->NumOfVertices;i++){
		visited[i]=0;
		num[i]=-1;
	}
	count=0;
	for(i=0;i<G->NumOfVertices;i++){
		if(!visited[i]) DFS1(i,G);
	}
	for(i=0;i<G->NumOfVertices;i++){
		for(p=i;p<G->NumOfVertices;p++){
			if(a[i][p]>0&&a[p][i]<0){a[i][p]=-a[i][p];a[p][i]=-a[p][i];}
			else if (a[i][p]<0&&a[p][i]>0){a[i][p]=-a[i][p];a[p][i]=-a[p][i];}
			else if (a[i][p]>0&&a[p][i]>0) ;
		}
	}
	for(i=0;i<G->NumOfVertices;i++){
		visited[i]=0;
	}
	for(i=0;i<G->NumOfVertices;i++){
		int maxp;
		maxp=findmax(G);
		if(!visited[maxp]) { DFS2(maxp,G,visit);printf("\n");}
	}	
	
}