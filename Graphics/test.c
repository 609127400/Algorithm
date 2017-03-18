#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef int ARRCHILD[50];


typedef struct
{
    int a;
    int arr[101];
}PQ,*P_PQ;

typedef int TWO[3][3];

int main()
{

    /*
    ARRCHILD* arr = (ARRCHILD*)malloc(20*sizeof(ARRCHILD));
    
    memset(arr,0,20*sizeof(ARRCHILD));

    int i,j;
    for(i = 0; i < 20; ++i)
    {
	for(j = 0; j < 20; ++j)
	{
	    printf("%d ",arr[i][j]);
	}
	printf("\n");
    }
    char arrr[10] = {0};

    sprintf(arr,"%d",i);

    printf("%s\n",arrr);

    P_PQ pq = (P_PQ)malloc(sizeof(PQ));
    free(pq);
    */


    int i = 0,j=0;

    while(i < 20)
    {
	while(j < 20)
	{
	    printf("i = %d,j = %d\n",i,j);
	    continue;
	    ++j;
	}

	i++;
    }










    return 0;
}
