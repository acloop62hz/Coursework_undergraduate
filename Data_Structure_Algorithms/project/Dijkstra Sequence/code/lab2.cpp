#include<stdio.h>
#include <stdlib.h>
#define max 1005
#define infty 200000
#define false 0
#define true 1
//use struct vertex to store each vertex,with label "known" and "dist". 
typedef struct vertex *PtrToV;
struct vertex{
    int known; //the status of a vertex, indicating whether or not it is visited
    int dist;  // the value of dist shows the length of path from the source vertex to it
};
int admatrix[max][max];
void readgraph(int a[][max],int ne,int nv);
void initial(int nv,PtrToV G);
int IsDseq(int s[],int nv,PtrToV G);

main(){
	int nv,ne,k;
	scanf("%d %d",&nv,&ne);//get the number of vertices and edges
	PtrToV G=(PtrToV)malloc((nv+1)*sizeof(struct vertex));	//apply for enough space to store vertices and their labels
	readgraph(admatrix,ne,nv);//construct a two-dimensional array to represent a graph
	// get k sequences and judge if they are Dijkstra sequences
	scanf("%d",&k);
	int seq[nv];
	for(int i=0;i<k;i++){
		for(int j=0;j<nv;j++){
			scanf("%d",&seq[j]);
		}
		if(IsDseq(seq,nv,G))printf("Yes\n");
		else printf("No\n");
	}
	return 0;
} 


void readgraph(int a[][max],int ne,int nv){
	int i,j;
	int v1,v2,w;
	// initialize the adjacency matrix, using the value infty to represent that two vertices are not connected
	for(i=1;i<=nv;i++){
		for(j=1;j<=nv;j++){
			a[i][j]=infty;
		}
	}
	// get information for each edge and store their weight.The adjacency matrix for a undirected graph is symmetrical
	for(i=0;i<ne;i++){
		scanf("%d %d %d",&v1,&v2,&w);
		a[v1][v2]=w;
		a[v2][v1]=w;
	}
}

//Since each given sequence has different source vertices, the labels of each vertex will be different.
//the function initial is used to clear labels of all vertices before examing each sequence.
void initial(int nv,PtrToV G){
	for(int i=1;i<=nv;i++){
		G[i].known=0;
		G[i].dist=infty;
	}
}
//the function IsDseq judges each given sequence through Dijkstra's algorithm
int IsDseq(int s[],int nv,PtrToV G){
	initial(nv,G);
	int i,tem,j,next,min;
	G[s[0]].dist=0; //set the label of dist to be 0 for the source vertex
	//for each vertex in the given sequence,judges if its following vertex is legal
	for(i=0;i<nv-1;i++){
		tem=s[i];
		G[tem].known=1; //visit one vertex in each turn
		for(j=1;j<=nv;j++){
			//find all the vertices w that has not been visited and has a shorter length of path through the present vertex s[i]
			if(G[j].known==0&&(G[tem].dist+admatrix[tem][j]<G[j].dist))
			G[j].dist=G[tem].dist+admatrix[tem][j];//update the label of distance for w
		}
		//in all the vertices whose label of dist has been updated, find the minimum  
		min=infty;next=i+1;
		for(j=1;j<=nv;j++){
			if(G[j].known==0&&G[j].dist<min) 
				min=G[j].dist;
		}
		//for the next vertex a to be legal, a.dist should be minimum among vertices that has been labeled 
		if(G[s[next]].dist!=min) return false;
	}
	//if all the vertex in the given sequence is legal , return true
	return true;	
}
