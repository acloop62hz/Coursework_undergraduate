int round(int des,int n);
int getmin(int *buffer,int n,int *srh);
main(){
	int n,i,sv;
	scanf("%d",&n);
	int objs = n;
	int hash_tbl[n];
	int search[n];
	for(i=0;i<n;i++) {
		scanf("%d",&hash_tbl[i]);
		if(hash_tbl[i]<0) {search[i]=-1;objs--;continue;}
		sv=hash_tbl[i]%n;
		if(i<sv)search[i]=i+n-sv+1;
		else search[i]=i-sv+1;
	}
	int buffer[n];
	int j,tj;
	int count = 0;
	int min;
	while(count < objs){
		for(i=0;i<n;i++) buffer[i]=-1;
		for(i=0;i<n;i++){
			if(search[i]==-1)continue;
			int legal=1;
			for(j=hash_tbl[i]%n;j<hash_tbl[i]%n+search[i]-1;j++){
				tj=round(j,n);
				if(search[tj]>0) {legal=0;break;}
			}
			if(legal == 1) buffer[i]=hash_tbl[i];
		}
		min=getmin(buffer,n,search);
		if(min>0) {
			count++;
			if(count < objs)printf("%d ",min);
			else printf("%d\n",min);
			
		}
		else break;
	}
	return 0;
	
}


int round(int des,int n){
	if(des>=n) return des-n;
	else return des;
}

int getmin(int *buffer,int n,int *srh){
	int i;
	int min=1000000;
	int pos = -1;
	for(i=0;i<n;i++){
		if(buffer[i]<0) continue;
		if(buffer[i]<=min) {min=buffer[i];pos=i;}
	} 
	if(pos<0) return -1;
	else {
		srh[pos]=-1;
		return min;
	}
}