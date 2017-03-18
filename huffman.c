/*
 *
 *                  霍夫曼算法
 *1.也称霍夫曼树，其算法的任务和目的就是构造一棵霍夫曼树。
 *2.霍夫曼树的特征：
 *  ① 树节点带有权重
 *  ② 节点的带权路径长度指：该节点到根节点的路径长与该节点权重的乘积
 *  ③ 树的带权路径长度（WPL）指  ：所有叶节点的带权路径长度之和
 *  ④ 在构造有n个带权叶子节点的树中，带权路径长度最小的为霍夫曼树
 *3.算法描述：
 *  ①根据给定的n个权重{W1,W2,...,Wn}构造n棵树{T1,T2,...,Tn}，其中每棵树只有一个根节点，
 *    即任一树T(i)的WPL(i) = W(i);
 *  ②在{T1,T2,...,Tn}中选取两个最小的树T(min1)和T(min2)作为左右子树，构成一个新的树T(new),
 *    T(new)的根节点的权重为左右子树权重之和
 *  ③将T(min1)和T(min2)从{T1,T2,...,Tn}中删除，将T(new)加入到其中
 *   （此步可用其他方法代替，如不删除，只要记录T(min1)和T(min2)被使用过，之后不再使用即可）
 *  ④重复步骤②和③，直到{T1,T2,...,Tn}只剩下一棵树（即最终形成一棵树）
 *4.其他
 *  具体实现与实际问题所采用的存储结构有关
 *
 *
 *
 */
#define _DEBUG_CLOSE_
#include "PublicForAlgorithms.h"

/*
 * 例子
 * 霍夫曼编码
 * 将字符出现的次数作为权重，将每个字符当作叶节点生成一个棵霍夫曼树，路径中向左表示0，向右表示1
 * ，由此生成编码编码在发送中字符总数会是最少的。
 *
 */
typedef unsigned int WEIGHT; //权重
typedef unsigned int LINK;   //在数组中表示树节点连接，也即下标值

typedef struct
{
    WEIGHT w;
    LINK   parent;
    LINK   lchild;
    LINK   rchild;
}HTNode,*P_HT;   //P代表指针的意思

typedef char* *P_HC;

/*
 * 功能  :选出没有被选过的叶节点中最小的两个，通过Min1，Min2带出  
 * HT_ARR:待生成霍夫曼树的数组
 * NUM_WIDTH:扫描选择的数组下标范围长度
 */
void SelectMin(P_HT HT_ARR,int NUM_WIDTH,LINK *Min1,LINK *Min2)
{
    WEIGHT min_weight = INT_MAX;
    int i = 0;
    while(i < NUM_WIDTH)
    {
	//没有父节点 && 最小
        if(HT_ARR[i].parent==0 && HT_ARR[i].w < min_weight)
	{ 
	    min_weight = HT_ARR[i].w; 
	    *Min1 = i; 
	}
	++i;
    }

    min_weight = INT_MAX;
    i = 0;
    while(i < NUM_WIDTH)
    {
	//没有父节点 && 不等于Min1 && 第二小
	if(HT_ARR[i].parent==0 && i!=(*Min1) && HT_ARR[i].w<min_weight)
	{
	    min_weight = HT_ARR[i].w;
	    *Min2 = i;
	}
	++i;
    }
    
    LINE_DEBUG("min1_pos = %d, min2_pos = %d",*Min1,*Min2);
}

/*
 * HT_ARR:HuffmanTree Array，用数组表示一颗霍夫曼树
 * HC_ARR:HuffmanCode Array，霍夫曼编码字符数组
 * W_ARR :权重数组
 * NUM_OF_W:权重数组中的权重数量，也即待编码字符数量
 * 注：进行地址传递，对参数进行值修改
 */
void Show_HT_ARR(P_HT ht,int len);
void Show_HC_ARR(P_HC hc,int len);

void HuffmanCoding(P_HT *HT_ARR,P_HC *HC_ARR,WEIGHT W_ARR[],int NUM_OF_W)
{
    if(NUM_OF_W < 2) return;
    //霍夫曼树：有n个叶子节点，则总共要有2n-1个节点
    int NodeNum = 2*NUM_OF_W - 1;
    *(HT_ARR) = (P_HT)malloc(NodeNum * sizeof(HTNode));
    if((*HT_ARR) == NULL) return;
    LINK i = 0;
    for(i = 0; i < NUM_OF_W; ++i)
    { 
	(*HT_ARR)[i].w = W_ARR[i]; 
	(*HT_ARR)[i].parent = 0;
	(*HT_ARR)[i].lchild = 0;
	(*HT_ARR)[i].rchild = 0;
    }
    for(;i < NodeNum; ++i)
    {
	(*HT_ARR)[i].w      = 0; 
	(*HT_ARR)[i].parent = 0;
	(*HT_ARR)[i].lchild = 0;
	(*HT_ARR)[i].rchild = 0;
    }

    //在数组中建立霍夫曼树
    //可参看霍夫曼树建立步骤
    LINK min1 = -1, min2 = -1;
    for( i=NUM_OF_W; i<NodeNum; ++i )
    {
	SelectMin((*HT_ARR),i,&min1,&min2);
	(*HT_ARR)[min1].parent = i;
	(*HT_ARR)[min2].parent = i;
	(*HT_ARR)[i].lchild = min1;
	(*HT_ARR)[i].rchild = min2;
	(*HT_ARR)[i].w      = (*HT_ARR)[min1].w + (*HT_ARR)[min2].w;
    }

    //从叶节点开始记录霍夫曼编码
    //根据霍夫曼建立的过程，可推导出最多有n-1个编码符号，带'\0'，则为n个
    (*HC_ARR) = (P_HC)malloc(NUM_OF_W * sizeof(char*));
    char* temp_box = (char*)malloc(NUM_OF_W * sizeof(char));
    if((*HC_ARR) == NULL || temp_box == NULL) return;
    LINK temp_l;/*沿child->parent路径循环递增，目的是从叶节点逐层向上循环直到根节点（没有父节点的点）*/
    LINK temp_c;/*沿着temp_box的0循环，+1递增，目的是将0或1按次序写入temp_box中*/

    for( i=0; i<NUM_OF_W; ++i )
    {
	//从当前叶节点开始循环，沿child->parent路径向根节点靠近，直到根节点结束
	for(temp_l=i,temp_c=0; (*HT_ARR)[temp_l].parent != 0; temp_l=(*HT_ARR)[temp_l].parent,++temp_c)
	{
	    //判断当前子节点是在父节点的左边还是右边
	    if((*HT_ARR)[(*HT_ARR)[temp_l].parent].lchild == temp_l)
		temp_box[temp_c] = '0';
	    else
		temp_box[temp_c] = '1';
	}
	/*此时temp_c做下标的话正好指向要给编码字符串添加'\0'的位置*/
	temp_box[temp_c] = '\0';
	/*为编码字符串数组中的当前叶节点分配空间，此时作为空间大小（字符的数量）,temp_c要+1*/
	++temp_c;
	(*HC_ARR)[i] = (char*)malloc((temp_c) * sizeof(char));
	strncpy((*HC_ARR)[i],temp_box,temp_c);
	//int testtest = 1;//gdb打断点使用
    }

    SAFE_FREE(temp_box);
}

void Show_HT_ARR(P_HT ht,int len)
{
    int i = 0;
    while(i < len)
    {
	printf("\n");
	printf("HT[%d]:\n",i);
	printf("w=%d\n",ht[i].w);
	printf("parent=%d\n",ht[i].parent);
	printf("lchild=%d\n",ht[i].lchild);
	printf("rchild=%d\n",ht[i].rchild);
	printf("------------------\n");
	++i;
    }
}

void Show_HC_ARR(P_HC hc,int len)
{
    int i = 0;
    while(i < len)
    {
	printf("\n");
	printf("HC[%d]:\n",i);
	printf("code=%s\n",hc[i]);
	printf("\n");
	++i;
    }
}



int main()
{
    char   arr_char[]   = {'a','b','c','d','e','f','g'};
    WEIGHT arr_weight[] = {5, 29, 7,  8, 14, 23, 3, 11 };
    //一般在编写代码时为了容易调试和改错，样本可以给的尽量少点儿
    //WEIGHT arr_weight[] = {12, 10, 5};

    int NUM_OF_WEIGHT = sizeof(arr_weight)/sizeof(WEIGHT);                       
    
    P_HT huffman_tree = 0;
    P_HC huffman_code = 0;

    //编码
    HuffmanCoding(&huffman_tree,&huffman_code,arr_weight,NUM_OF_WEIGHT);
       
    Show_HT_ARR(huffman_tree,2*NUM_OF_WEIGHT-1);
    Show_HC_ARR(huffman_code,NUM_OF_WEIGHT);
    
    //清理工作
    SAFE_FREE(huffman_tree);
    int i = 0;
    while( i < NUM_OF_WEIGHT )
    {
	SAFE_FREE(huffman_code[i]);
	++i;
    }

    PAUSE();

    return 0;
}
