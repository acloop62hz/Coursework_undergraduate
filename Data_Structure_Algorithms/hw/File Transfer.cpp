#include<stdio.h>

int Find(int x, int *a);
void Union(int x1,int x2,int *a);
int Check(int x1,int x2,int *a);

int main(){
	int n;
	scanf("%d",&n);
	int a[n+1];
	for(int i=1;i<=n;i++){
		a[i]=-1;
	}
	char c;
	while((c=getchar())!='S'){
		int x1,x2;
		scanf("%d %d",&x1,&x2);
		switch(c){
			case 'C':{
				if(Check(x1,x2,a))printf("yes\n");
				else printf("no\n");
				break;
			}
			case 'I':{
				Union(x1,x2,a);
				break;
			}
		}
	}
	int count=0;
	for(int i=1;i<=n;i++){
		if(a[i]<=0) count++;
		else;
	}
	if(count == 1||count == 0) printf("The network is connected.\n");
	else printf("There are %d components.\n",count);
	return 0;
}