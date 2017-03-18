/*
 *                                �鲢����
 *1.���õݹ�
 *2.�ֶ���֮
 *3.��һ��������������A���õݹ�ֳ����룬ÿһ���ٷֳ����룬�ݹ飬ֱ��������С��λΪһ��Ԫ��
 *  ��ʱ��С��λ��һ��Ԫ�أ��ĵ�һ��Ԫ���±�ֵ�����һ��Ԫ���±�ֵ��ȡ��ֳ�����ÿһ�룬����
 *  һ��������ChildArr��Merge����ȥ����Merge�������⵱ǰҪ��������������м�ֳ����ݣ�Left��Right
 *  ����Left��Right���յ�4����������
 *4.Ȼ��ÿ���ݹ�Ļ��ݹ�����ÿ��������ChildArr���������Ѿ���С�������������Left��Right��С�����ϣ�
 *  ���αȽ������Ӽ��������ƣ�ȡ����С�ķ�����ʱ���飬��˵ݹ�
 *5.����������鼯��Ϊ[9,1,45,43,7,21,21,5,7,10]
 *  �鲢���̴��µ��ϣ�                              
 *
 *                1 5 7 7 9 10 21 21 43 45
 *                 /                   \
 *        1 5 7 9 21 21 43 45         7 10 
 *          /              \           \
 *     1 9 43 45       5 7 21 21      7 10
 *      /       \       /      \       \
 *    1  9    43 45   7  21   5  21   7 10     
 *    /  \    /  \    /  \    /  \   /  \
 *    9  1   45  43   7  21  21  5   7  10
 *
 *    2016��10��11��
 */

#define _DEBUG_CLOSE
#include "PublicForAlgorithms.h"

#define MAX_MAX 99999999

/*
 *���ܣ����ڹ鲢�����������е� �ϲ�
 * arr:����������
 * start: arr��һ��Ԫ���±�ֵ
 * mid:   left arrz���һ��Ԫ���±�ֵ
 * end:   arr���һ��Ԫ���±�ֵ,ͬʱҲ��arr�����һ��Ԫ�ص��±�
 * MAX_MAX: Ϊ�ڱ�������Left��Right��󣬷�ֹԽ����ʣ���ȷ��MAX_MAX������
 *          �������Ԫ�ض�Ҫ��
 */
void Merge(int arr[],int start,int mid,int end)
{
    int n1 = mid - start + 1;
    int n2 = end - mid;
    int Left[n1 + 1],Right[n2 + 1];
    int i = 0;
    while(i < n1 )
    {
	Left[i] = arr[start + i];
	++i;
    }
    Left[n1] = MAX_MAX;
    
    i = 0;
    while(i < n2)
    {
	Right[i] = arr[mid + 1 + i];
	++i;
    }
    Right[n2] = MAX_MAX;
    
    LINE_DEBUG("start = %d, mid = %d, end = %d",start,mid,end);
    LINE_DEBUG("sizeof LeftArr = %d,sizeof RightArr = %d",
	    sizeof(Left)/sizeof(int),sizeof(Right)/sizeof(int));
    
    int l=0,r = 0;
    while(start <= end)
    {
	if(Left[l] < Right[r])
	{
	    arr[start] = Left[l];
	    ++l;
	}
	else
	{
	    arr[start] = Right[r];
	    ++r;
	}
	++start;
    }
}

/*
 * arr:   ����������
 * start: arr��һ��Ԫ���±�ֵ
 * end:   arr���һ��Ԫ���±�ֵ
 */
void MergeSort(int arr[],int start,int end)
{
    if(start < end)
    {
	int mid = (start + end) >> 1;
	MergeSort(arr, start, mid);
	MergeSort(arr, mid+1, end);
	Merge(arr, start, mid, end);
    }
}

void ShowArr(int arr[],int len)
{
    int i = 0;
    while(i < len)
    {
	printf("%d  ",arr[i]);
	++i;
    }
    printf("\n");
}


int main()
{

    int arr[] = {9,1,45,43,7,21,21,5,7,10,17,120,164,2,35,38,19,21,75,64,68,100,96,74,54};
    int num = sizeof(arr)/sizeof(int);
    MergeSort(arr,0,num - 1);

    ShowArr(arr,num);

    PAUSE();


    return 0;
}
