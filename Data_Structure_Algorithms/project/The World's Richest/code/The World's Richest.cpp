#include<stdio.h>
#include<string.h>
#define Cutoff 10
#define max 100000

//structure for storing information of each person
struct personInfo {
	char name[9];
	int age;
	int worth;
}list[max]; 

typedef struct personInfo *PI;
void Quicksort(int a[],int N);  //the shell of quicksort
int Median3(int a[],int Left,int Right); // get the pivot
void Qsort(int a[], int Left,int Right);
void swap(int *a,int *b); //exchange two values in the array
void InsertionSort(int a[], int n);
void printcase(int count,int lowbound,int highbound,int *table,int N); //print the result accroding to each query
int compare(int a, int b); //set up a new standard for comparing elements according to the requirements

main(){
	int N,K;
	scanf("%d %d",&N,&K);
	int i;
	//store the information into the array of structures
	for(i=0;i<N;i++)
		scanf("%s %d %d",list[i].name,&list[i].age,&list[i].worth);
	//table[N] is used to store the indices of elements after swapping, saving the time and space to swap structures
	int table[N];
	for(i=0;i<N;i++) table[i]=i;
	Quicksort(table,N);
	int count,lowbound,highbound;
	//for each query, print the results
	for(i=1;i<=K;i++) {
		scanf("%d %d %d",&count,&lowbound,&highbound);
		printf("Case #%d:\n",i);
		printcase(count,lowbound,highbound,table,N);	
	}
}

// the shell for quicksort
void Quicksort(int a[],int N){
	Qsort(a,0,N-1);
}

//exchange two values in the array
void swap(int *a,int *b){
	int temp;
	temp=*a;
	*a=(*b);
	*b=temp;
}
// since the results should be ranked not only according to the net worth, but also ages and names, this function define a new relation.
// this new relation makes sure that the results are ranked in non-increasing order of the net worths. In case there are equal worths, it must be in non-decreasing order of the ages. If both worths and ages are the same, then the output must be in non-decreasing alphabetical order of the names. 
//if it return 1, it means that a and b are in right order, otherwise not.
int compare(int a, int b){
	if(a==b) return 0;
	if (list[a].worth != list[b].worth) return list[a].worth > list[b].worth;
	else if(list[a].age != list[b].age) return list[a].age<list[b].age;
	else return strcmp(list[b].name,list[a].name); 
}
// get the pivot and sort a[Left],a[Right] and a[Center]
int Median3(int a[],int Left,int Right){
	int Center = (Left + Right)/2;
	//sort three elements accroding to the given order
	if(compare(a[Center],a[Left])>0) swap(&a[Left],&a[Center]);
	if(compare(a[Right],a[Left])>0) swap(&a[Left],&a[Right]);      
	if(compare(a[Right],a[Center])>0) swap(&a[Center],&a[Right]);      
	return Center;	//return the position of the pivot in the array
}

//the real quicksort algorithm
void Qsort(int a[], int Left,int Right){
	//if the number of elements to be sorted is less than 1, return directly
	if(Left >= Right) return;
	int i,j;
	int pivotp;
	//if the number of elements is large enough, use quicksort
	if(Left+Cutoff <= Right){
		pivotp=Median3(a,Left,Right);
		i=Left;j=Right-1;
		//the elements in the postion [Left] and [Right -1] are sorted. if i+1>=j-1, the array is already sorted.
		if(i+1>=j-1) return;
		//hide the pivot to the end of the array
		swap(&a[pivotp],&a[Right-1]);
		while(1){
			while(compare(a[++i],a[Right-1])>0) ;  //if a[i] and pivot are in right order,move i forward       
			while(compare(a[Right-1],a[--j])>0) ;  //if a[j] and pivot are in right order,move j backward         
			if(i<j) swap(&a[i],&a[j]); //as long as i and j do not meet, swap the elements that are in the wrong order
			else break;
		}
		//swap the pivot back to the right place
		swap(&a[i],&a[Right-1]);
		//quicksort the left and right parts that are partitioned based on the pivot
		Qsort(a,Left,i-1);
		Qsort(a,i+1,Right);
	}
	else
		//if the number of elements is relatively small, use insertionsort
		InsertionSort(a+Left,Right-Left+1);
}

void InsertionSort(int a[],int n){
	int i,j;
	int temp;
	for(i=1;i<n;i++){
		temp=a[i];
		//check the elements before a[i] until the right position for a[i] is found
		for(j=i;j>0 && compare(temp,a[j-1])>0 ;j--)      
			a[j]=a[j-1];
		a[j]=temp;
	}
}

//print the result accroding to each query
void printcase(int count,int lowbound,int highbound, int *table,int N){
	int rc;
	rc=0;
	int i;
	int preage;
	//visit each element in the array to see if it is in the given range of age.
	//use the integer rc to count the number of printed elements
	//if the ith element is in the the given range of age, and rc has not reach the given number , print it.
	for(i=0;i<N && rc<count;i++){
		preage= list[table[i]].age;
		if(lowbound<=preage && preage<=highbound) {
			printf("%s %d %d\n",list[table[i]].name,list[table[i]].age,list[table[i]].worth);
			rc++;
		}
	}
	//if no elements satisfy the requirements,print"None"
	if(rc ==0 ) printf("None\n");
}

