#include <stdio.h>
#include <stdlib.h>

int ispossible(int *a,int M,int N);

main(){
	int M,N,K;
	scanf("%d %d %d",&M,&N,&K);
	int a[K][N];
	for(int i=0;i<K;i++){
		for(int j=0;j<N;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=0;i<K;i++){
		if(ispossible(a[i],M,N)) printf("YES\n");
		else printf("NO\n");
	}
}

int ispossible(int *a,int M,int N){
	int t[M+1];int p = 0;
    t[0]=0;
	for(int i=0;i<N;i++){
		if(a[i]>t[p]){
			for(int o=t[p]+1;o<a[i];o++){
				int flag=0;
				for(int g=0;g<i;g++){
					if(o == a[g]) {flag = 1;break;}
				}	
				if(flag)continue;
				else {
					p++;
					if(p>=M)return 0;
					t[p] = o;
				}
			}
		}
		else{
			if(t[p] == a[i]) p--;
			else return 0;	
		}
	}
	return 1;

}