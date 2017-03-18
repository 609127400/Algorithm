#include <stdio.h>





int functionA()
{
    printf("functionA\n");
}



int main()
{





    int a[5] = {2,5,6,8};
    int b[6] = {-2,-5,-6,-8,8};

    
    int i = 4;
    int key = 1;
    while(i >= 1)
    {
	if(a[i-1] > key)
	{
	    a[i] = a[i-1];
	    b[i+1] = b[i];
	}
	else
	    break;
	--i;
    }
    a[i] = key;
    b[i] = -key;
    b[i+1] = key; 


    i = 0;

    while(i < 5)
    {
	printf("%d  ",a[i]);
	++i;
    }
    printf("\n");
    i = 0;
    while(i < 6)
    {
	printf("%d  ",b[i]);
	++i;
    }
    printf("\n");


    int zheng = atoi("12a");
    printf("zheng = %d\n",zheng);

    printf("%-010s\n","abc");

    int yiwei = 16;
    yiwei>>1;
    printf("yiwei = %d\n",yiwei>>1);

    printf("fanhui = %d\n",functionA());


    int arr_name[5][2] = {{1,2},{3,4},{5,6},{7,8},{9,10}};

    int forgdb = 1;//…Ë÷√∂œµ„


}
