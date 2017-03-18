/*
 *                                归并排序
 *1.利用递归
 *2.分而治之
 *3.将一个待排序数集合A利用递归分成两半，每一半再分成两半，递归，直到分至最小单位为一个元素
 *  此时最小单位（一个元素）的第一个元素下标值与最后一个元素下标值相等。分出来的每一半，当作
 *  一个子数组ChildArr让Merge函数去排序。Merge函数将这当前要处理的子数组重中间分成两份，Left和Right
 *  根据Left和Right按照第4步进行排序
 *4.然后将每个递归的回溯过程中每个子数组ChildArr看成两堆已经从小到大排序过的牌Left和Right，小牌在上，
 *  依次比较两堆子集顶部的牌，取出最小的放入临时数组，如此递归
 *5.如待排序数组集合为[9,1,45,43,7,21,21,5,7,10]
 *  归并过程从下到上：                              
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
 *    2016年10月11日
 */

#define _DEBUG_CLOSE
#include "PublicForAlgorithms.h"

#define MAX_MAX 99999999

/*
 *功能：用于归并排序三步骤中的 合并
 * arr:待排序数组
 * start: arr第一个元素下标值
 * mid:   left arrz最后一个元素下标值
 * end:   arr最后一个元素下标值,同时也是arr的最后一个元素的下标
 * MAX_MAX: 为哨兵，放在Left和Right最后，防止越界访问，需确保MAX_MAX比所有
 *          待排序的元素都要大。
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
 * arr:   待排序数组
 * start: arr第一个元素下标值
 * end:   arr最后一个元素下标值
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
