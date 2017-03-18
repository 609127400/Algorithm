/* 
 *                                   设计和分析技术
 * 1.类似于算法的算法，方法的方法，方法论，一些算法公有的基础的遵循的算法思想，分析技术。
 * 2.广泛使用的技术：分治策略，随机化方法，递归技术，
 * 3.高级的三种：动态规划，贪心算法(法则)，摊还分析。
 * 4.动态规划：
 *   常用于求解最优化问题，这类问题有很多可行解，每个解都有一个值，而从这些解中找出最优
 *   (最大/小)值的解。通常有四步：
 *   ①刻画一个最优解的结构特征 ②递归的定义一个最优解的值
 *   ③计算最优解的值，通常采用自底向上的方法 ④利用计算信息构造一个最优解。
 *   如一类问题中(钢条切割，最短路径)，规模为n的问题，可分化为若干个子问题，但求解形式一
 *   致，同时，划分的若干个子问题亦有相交的子子问题(公共部分)，这点则与分治策略不同。动
 *   态规划中，将仔细安排求解顺序，保证每个子问题求解之前，其依赖的子子问题或其他子问题
 *   都已经计算完毕并保存，从而在计算该子问题时只需查找保存的结果，不必重新计算。
 *
 *
 *
 *
 *
 *
 *
 *
 *                                                               2016年12月22日
 *
 */
//#define _DEBUG_CLOSE_
#include "PublicForAlgorithms.h"
#define PRICE_LEN (10 + 1)
#define MAX_PRICE_LEN (10 + 1)
#define SOLUTION_LEN (10 + 1)









/*钢条切割问题-典型的需动态规划的问题
 *PRICE中是不同长度的钢条的价格，如PRICE[3]=8，即长度为3的钢条价格是8
 *①现在有一根长度为n的钢条，求解如何切割，才能是切割后的钢条价格最大化。
 *②长度为n的钢条，分割可分为两部分，已经分割好的左半部分L和未分割的右半
 *  部份R，而R又可分为同样的两部分且求解方式一致，因此该问题的解存在与L
 *  部分从1到n遍历时，右半部份的求解过程中，此即递归定义一个最优解值*/


/*n 要分割的钢条总长度(规模为n的问题)*/
int MaxPrice_Cut(int n)
{
    int i,j;
    int PRICE[PRICE_LEN] = {0,1,5,8,9,10,17,17,20,24,30};
    /*保存（子问题的）最优解的值，MAX_PRICE[3]表示长度为3时的最优解的值*/
    int MAX_PRICE[MAX_PRICE_LEN];
    /*保存最优解，SOLUTION[3]代表n=3时，最优解值左半部分的长度*/
    int SOLUTION[SOLUTION_LEN];
    /*最最最小的子问题，即规模为0的时候，也即是钢条长度为0时，价格自然是0*/
    MAX_PRICE[0] = 0; SOLUTION[0] = 0;
    int max_price;
    for(i = 1; i <= n; ++i)
    {
	max_price = -1;/*价钱不可能是负数，所以-1代表绝对小*/
	/*规模为i的子问题*/
	for(j = 1; j <= i; ++j)
	{
	    /*左半部分为j时，其价格为PRICE[j]，右半部份则为已经计算过的
	     *子问题最优解的值MAX_PRICE[i-j]，其中j只能从1开始，若从0开
	     *始，则此时MAX_PRICE[i-j]=MAX_PRICE[i]，而此时规模为i的子问
	     *题并没有求出解来，当j=i时，代表规模为i的长度不分割的情况*/
	    if(max_price < PRICE[j] + MAX_PRICE[i-j])
	    {
		//更新最大值和最优解
		max_price = PRICE[j] + MAX_PRICE[i-j];
		SOLUTION[i] = j;
	    }
	}
	/*保存规模为i的最优解的值，此时i==j*/
	MAX_PRICE[i] = max_price;
    }

    /*显示*/
    printf("规模为%d的最优解的值MAX_PRICE:\n",n);
    for(i = 0; i < MAX_PRICE_LEN; ++i){ printf("%d ",MAX_PRICE[i]); }
    printf("\n");
    printf("规模为%d的最优解:\n",n);
    for(i = 0; i < MAX_PRICE_LEN; ++i){ printf("%d ",SOLUTION[i]); }
    printf("\n");
}

int main()
{
    MaxPrice_Cut(10);
    

    return 0;
}

