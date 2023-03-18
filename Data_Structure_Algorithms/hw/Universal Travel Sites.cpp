#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 1505
#define infty 1000000


int admatrix[max][max];
int size_ID=0;


typedef struct node *Name;
struct node{
	char name[4];
};


int NameToID(char* s,Name array);
int FindMax(char* source, char* destination);
int SearchPath(char* source, char* destination,int *path,Name names);


main(){
	char source[4],destination[4],tem1[4],tem2[4];
	int e,w,v1,v2,i,j;
	Name names;
	names=(Name)malloc(max*sizeof(struct node));
	
	for(i=0;i<max;i++){
		for(j=0;j<max;j++){
			admatrix[i][j]=0;
		}
	}

	scanf("%s %s %d",source,destination,&e);
	NameToID(source,names);
	NameToID(destination,names);
	
	for(i = 0; i < e; i++){
		scanf("%s %s %d",tem1,tem2,&w);
		v1 = NameToID(tem1,names);
		v2 = NameToID(tem2,names);
		admatrix[v1][v2] = w; 
	}
	
	int path[max];
	
	int Sumflow=0,flow;
	while(1){
		flow = SearchPath(source, destination,path,names);
		if(flow == 0) break;
		Sumflow = Sumflow + flow;
		v1 = NameToID(destination,names);
		while(v1 != NameToID(source,names) && v1 != -1){
			v2 = path[v1];
			admatrix[v2][v1] -= flow;
			admatrix[v1][v2] += flow;
			v1 = v2;
		}
	}
	printf("%d", Sumflow);
} 

int NameToID(char* s,Name array){
	int i;
	for(i = 1; i <= size_ID; i++){
		if(strcmp(s,array[i].name) == 0)
		return i;
	}
	strcpy(array[++size_ID].name, s);
	return size_ID;
}


int SearchPath(char* source, char* destination,int *path,Name names){
	int queue[max];
	int fflo[max];
	int front = 0, rear = 0;
	int i,tem,flag=0,j;
	fflo[NameToID(source,names)]=infty;
	
	for(i=0;i<max;i++){
		path[i]=-1;
	} 
	path[1]=0;
	queue[rear++] = NameToID(source,names);
	while(front != rear){
		tem = queue[front++];
		if(tem == NameToID(destination,names)) {flag=1;break;}
		for(i = 1; i <=size_ID; i++){
			if(admatrix[tem][i] > 0 && path[i] == -1){
				path[i] = tem;
				fflo[i]=(fflo[tem]<=admatrix[tem][i]?fflo[tem]:admatrix[tem][i]);
				queue[rear++] = i;
			}
		}
	} 
	if(path[2]==-1)return 0;
	else return fflo[2];
}