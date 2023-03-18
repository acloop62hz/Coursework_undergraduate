#include<stdio.h>
#include <stdlib.h>
#define max 505
#define infty 1000000

typedef struct Edge *graph;
struct Edge {
    int V1;
    int V2;
    int weight;
    int accepted;
    int Yesbutdiscard;
};

void readgraph(graph G,int ne);
void kruskal(graph G,int nv,int ne,int *Disj_set);
int Find(int x, int *a);
void Union(int x1,int x2,int *a);


main(){
	int nv,ne;
	scanf("%d %d",&nv,&ne);
	graph G;
	G=(graph)malloc((ne+1)*sizeof(struct Edge));
	int Disj_set [nv+1];
	int i;
	for(i=1;i<=nv;i++){
		Disj_set[i]=-1;
	}
	readgraph(G,ne);
		int edges_accepted,j,min,count;

	edges_accepted=0;
	int minedges_temp[ne];
	
	int Tweight=0;
	
	while(edges_accepted<nv-1){
		int changesdone =0;
		//初始化 
		min=infty;
		for(i=0;i<ne;i++){
			minedges_temp[i]=0; 
		}
		int count = 0;
		//找最小 
		for(j=1;j<=ne;j++){
			if(G[j].accepted==0&&G[j].weight<min) 
				min=G[j].weight;
		}
		//初筛 
		for(j=1;j<=ne;j++){
			if(G[j].accepted==0&&G[j].weight == min) minedges_temp[count++]=j;		
		}
		// 复筛
		int count2=0;
		int only1=0;;
		for(j=0;j<count;j++){
			int k;
			k=minedges_temp[j];
			if(Find(G[k].V1, Disj_set) == Find(G[k].V2, Disj_set) ) {G[k].accepted=-1;changesdone=1;}
			else{
				count2++;
				if(count2 == 1) only1=k;
				else  G[k].Yesbutdiscard=1;
			}
		}
		if(only1) {G[only1].Yesbutdiscard=0;G[only1].accepted=1;edges_accepted++;Union(G[only1].V1,G[only1].V2,Disj_set) ;Tweight=Tweight+min;changesdone=1;}
		if(changesdone ==0 ) break;
	}
	
	if(edges_accepted<nv-1) {
		printf("No MST\n");
		int Ntrees = 0;
		for(i=1;i<=nv;i++){
			if (Disj_set[i] == -1) Ntrees++;
		}
		printf("%d\n",Ntrees);
	}
	else{
		printf("%d\n",Tweight);
		int flag=0;
		for(i=1;i<=ne;i++){
			if(G[i].accepted!=1 && G[i].Yesbutdiscard == 1) {flag=1;break;}
		}
		if(flag)printf("No\n");
		else printf("Yes\n");
	}
	
	
	
}
void readgraph(graph G,int ne){
	int v1,v2,w,i;
	for(i=1;i<=ne;i++){
		scanf("%d %d %d",&v1,&v2,&w);
		G[i].V1=v1;
		G[i].V2=v2;
		G[i].weight=w;	
		G[i].accepted=0;
		G[i].Yesbutdiscard=0;
	}
}



int Find(int x, int *a){
	if(a[x]<=0) return x;
	else
		return a[x]=Find(a[x],a);
} 
void Union(int x1,int x2,int *a){
	int r1,r2;
	r1=Find(x1,a);
	r2=Find(x2,a);
	if(r1==r2) return;
	else{
		if((-a[r1])>=(-a[r2])) a[r2]=r1;
		else a[r1]=r2;
	}
}


