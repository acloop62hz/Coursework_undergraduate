#include<stdio.h>
#define max 1001

int hobbies[max]={0};
void Sort(int *s,int n);
int Find(int x, int *a);
void Union(int a,int b,int *s);

main(){
	int n,i,j;
	scanf("%d",&n);
	int a[n+1];
	for(i=1;i<=n;i++) a[i]=-1;
	int nh,t;
	for(i=1;i<=n;i++){
		scanf("%d:",&nh);
		for(j=0;j<nh;j++){
			scanf("%d",&t);
			if(hobbies[t] == 0) hobbies[t]=i;
			else Union(hobbies[t],i,a);
		}
	}
	int r;
	for(i=1;i<=n;i++){
		r=Find(i,a);
		if(r == i);
		else a[r]--;
	}
	int sort[n];
	for(i=0;i<n;i++)sort[i]=-1;
	int rear=0;
	for(i=1;i<=n;i++){
		if(a[i]<0){
			sort[rear++]=-a[i];
		}
	}
	Sort(sort,rear);
	printf("%d\n",rear);
	for(i=0;i<rear-1;i++){
		printf("%d ",sort[i]);
	}
	printf("%d",sort[i]);
}

void Sort(int *s,int n){
	int i,j,temp;
	for(i=1;i<n;i++){
		temp=s[i];
		for(j=i;j>0&&s[j-1]<temp;j--){
			s[j]=s[j-1];
		}
		s[j]=temp;
	}
}

int Find(int x, int *a){
	if(a[x]<=0) return x;
	else
		return a[x]=Find(a[x],a);
}

void Union(int a,int b,int *s){
	int r1,r2;
	r1=Find(a,s);
	r2=Find(b,s);
	if(r1==r2) return ;
	else s[r1]=r2;
} 