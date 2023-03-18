#include <stdio.h>

void IsInsertSort(int *a,int *origin, int n);
void IsHeapSort(int *a,int *origin, int n);
int judge(int *a, int *b,int n);
void PercolateUp( int p, int *a, int n );
void PercolateDown(int p, int *a, int n);
int DeleteMax( int *a, int n ) ;


main(){
	int n;
	scanf("%d",&n);
	int origin[n];
	int a[n];
	int i;
	for(i=0;i<n;i++)
		scanf("%d",&origin[i]);
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	
	IsInsertSort(a,origin,n);
	IsHeapSort(a,origin,n);
}

void IsInsertSort(int *a,int *origin, int n){
	int i,j,flag;
	flag=0;
	int copyorigin[n];
	for(i=0;i<n;i++){
		copyorigin[i]=origin[i];
	}
	for(i=1;i<n;i++){
		if(flag == 1)flag=2;
		int temp;
		temp=copyorigin[i];
		for(j=i;j>0&&copyorigin[j-1]>temp;j--)
			copyorigin[j]=copyorigin[j-1];
		copyorigin[j]=temp;
		if(judge(a,copyorigin,n)) {flag = 1;}
		if(flag == 2)break;
	}
	if(flag == 2){
		printf("Insertion Sort\n");
		for(i=0;i<n-1;i++) printf("%d ",copyorigin[i]);
		printf("%d\n",copyorigin[i]);
	}
}

void IsHeapSort(int *a,int *origin, int n){
	int na[n+1];
	int i,flag;
	flag=0;
	for(i=1;i<=n;i++){
		na[i]=origin[i-1];
	}
	for(i=n;i>=1;i--){
		PercolateDown(i,na,n);
	}
	
	for(i=0;i<n;i++){
		if(flag == 1) flag=2;
		na[n-i]=DeleteMax(na,n-i);
		if(judge(na+1,a,n)) flag=1;
		if(flag==2)break;
	}
	if(flag == 2){
		printf("Heap Sort\n");
		for(i=1;i<n;i++) printf("%d ",na[i]);
		printf("%d\n",na[i]);
	}
	
	
	
}

void PercolateUp( int p, int *a, int n ){
	int x;
	x=a[p]; 
	int i;
	for(i=p;a[i/2]<x&&i>0;i/=2)
		a[i]=a[i/2];
	a[i]=x;
}
void PercolateDown(int p, int *a, int n){
	int child,i;
	int x;
	x=a[p];
	for(i=p;i*2<=n;i=child){
        child=2*i;
		if ((i*2+1)<=n&&a[i*2+1]>a[2*i]) child=2*i+1;
		if(x<a[child]) a[i]=a[child];
		else break;
	}
	a[i]=x;
}

int judge(int *a, int *b,int n){
	int i,flag;
	flag=0;
	for(i=0;i<n;i++){
		if(a[i]!=b[i]){flag=1;break;}
	}
	if(flag == 1) return 0;
	else return 1;
}

int DeleteMax( int *a, int n ) 
{ 
    int MaxElement; 
    MaxElement = a[1];
    a[1] = a[n--];
    PercolateDown( 1, a,n );
    return 	MaxElement; 
}