#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */
void merge_pass( ElementType list[], ElementType sorted[], int N, int length ){
	int i,leftpos,leftend,rightpos,rightend,temp;
	if(length>=N) {
		for(i=0;i<N;i++)
			sorted[i]=list[i];
	}
	for(i=0;i<N;i=i+2*length){
		leftpos=i;
		leftend=i+length-1;
		if(leftend>N)leftend=N-1;
		rightpos=i+length;
		rightend=rightpos+length-1;
		if(rightend>N)rightend=N-1;
		temp=leftpos;
		while(leftpos<=leftend && rightpos<=rightend){
			if(list[leftpos]<=list[rightpos]) 
				sorted[temp++]=list[leftpos++];
			else
				sorted[temp++]=list[rightpos++];
		}
		while(leftpos<=leftend)
			sorted[temp++]=list[leftpos++];
		while(rightpos<=rightend)
			sorted[temp++]=list[rightpos++];
	}
} 