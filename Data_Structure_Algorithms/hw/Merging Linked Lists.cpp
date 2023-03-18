#include<stdio.h>
#define max 100001

int node[max];
int next[max];
int getlen(int L);

main(){
	int L1,L2,n;
	scanf("%d %d %d",&L1,&L2,&n);
	int i,pos,data,nextp;
	for(i=0;i<n;i++){
		scanf("%d %d %d",&pos,&data,&nextp);
		node[pos]=data;
		next[pos]=nextp;
	}
	int lenl,lens;
	int L,Ls;
	L=(getlen(L1)>getlen(L2))?L1:L2;
	Ls=(getlen(L1)>getlen(L2))?L2:L1;
	lenl=getlen(L);
	lens=getlen(Ls);
	int Len;
	Len=lenl+lens;
	int reL[Len];
	for(i=0;i<Len;i++){
		reL[i]=-2;
	}
	int count =0,counts=0; 
	int insertp=0;
	
	while(L!=-1){
		count++;
		if(count == 3 && counts< lens) { insertp++; counts++;count = 0;}
		else{
			reL[insertp]=L;
			L=next[L];
			insertp++;
		}
	}
	for(i=Len-1;i>=0;i--){
		if(reL[i]==-2){
			reL[i]= Ls;
			Ls=next[Ls];
		}
	}
	int printp,nprintp;
	for(i=0;i<Len;i++){
		printp=reL[i];
		nprintp=reL[i+1];
		if(i==Len-1) printf("%05d %d %d\n",printp,node[printp],-1);
		else printf("%05d %d %05d\n",printp,node[printp],nprintp);
	}
	
	
}

int getlen(int L){
	int count;
	count = 0;
	while(L!=-1){
		L=next[L];
		count++;
	}
	return count;
}