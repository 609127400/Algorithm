/*
 *
 *                  �������㷨
 *1.Ҳ�ƻ������������㷨�������Ŀ�ľ��ǹ���һ�û���������
 *2.����������������
 *  �� ���ڵ����Ȩ��
 *  �� �ڵ�Ĵ�Ȩ·������ָ���ýڵ㵽���ڵ��·������ýڵ�Ȩ�صĳ˻�
 *  �� ���Ĵ�Ȩ·�����ȣ�WPL��ָ  ������Ҷ�ڵ�Ĵ�Ȩ·������֮��
 *  �� �ڹ�����n����ȨҶ�ӽڵ�����У���Ȩ·��������С��Ϊ��������
 *3.�㷨������
 *  �ٸ��ݸ�����n��Ȩ��{W1,W2,...,Wn}����n����{T1,T2,...,Tn}������ÿ����ֻ��һ�����ڵ㣬
 *    ����һ��T(i)��WPL(i) = W(i);
 *  ����{T1,T2,...,Tn}��ѡȡ������С����T(min1)��T(min2)��Ϊ��������������һ���µ���T(new),
 *    T(new)�ĸ��ڵ��Ȩ��Ϊ��������Ȩ��֮��
 *  �۽�T(min1)��T(min2)��{T1,T2,...,Tn}��ɾ������T(new)���뵽����
 *   ���˲����������������棬�粻ɾ����ֻҪ��¼T(min1)��T(min2)��ʹ�ù���֮����ʹ�ü��ɣ�
 *  ���ظ�����ںۣ͢�ֱ��{T1,T2,...,Tn}ֻʣ��һ�������������γ�һ������
 *4.����
 *  ����ʵ����ʵ�����������õĴ洢�ṹ�й�
 *
 *
 *
 */
#define _DEBUG_CLOSE_
#include "PublicForAlgorithms.h"

/*
 * ����
 * ����������
 * ���ַ����ֵĴ�����ΪȨ�أ���ÿ���ַ�����Ҷ�ڵ�����һ���û���������·���������ʾ0�����ұ�ʾ1
 * ���ɴ����ɱ�������ڷ������ַ������������ٵġ�
 *
 */
typedef unsigned int WEIGHT; //Ȩ��
typedef unsigned int LINK;   //�������б�ʾ���ڵ����ӣ�Ҳ���±�ֵ

typedef struct
{
    WEIGHT w;
    LINK   parent;
    LINK   lchild;
    LINK   rchild;
}HTNode,*P_HT;   //P����ָ�����˼

typedef char* *P_HC;

/*
 * ����  :ѡ��û�б�ѡ����Ҷ�ڵ�����С��������ͨ��Min1��Min2����  
 * HT_ARR:�����ɻ�������������
 * NUM_WIDTH:ɨ��ѡ��������±귶Χ����
 */
void SelectMin(P_HT HT_ARR,int NUM_WIDTH,LINK *Min1,LINK *Min2)
{
    WEIGHT min_weight = INT_MAX;
    int i = 0;
    while(i < NUM_WIDTH)
    {
	//û�и��ڵ� && ��С
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
	//û�и��ڵ� && ������Min1 && �ڶ�С
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
 * HT_ARR:HuffmanTree Array���������ʾһ�Ż�������
 * HC_ARR:HuffmanCode Array�������������ַ�����
 * W_ARR :Ȩ������
 * NUM_OF_W:Ȩ�������е�Ȩ��������Ҳ���������ַ�����
 * ע�����е�ַ���ݣ��Բ�������ֵ�޸�
 */
void Show_HT_ARR(P_HT ht,int len);
void Show_HC_ARR(P_HC hc,int len);

void HuffmanCoding(P_HT *HT_ARR,P_HC *HC_ARR,WEIGHT W_ARR[],int NUM_OF_W)
{
    if(NUM_OF_W < 2) return;
    //������������n��Ҷ�ӽڵ㣬���ܹ�Ҫ��2n-1���ڵ�
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

    //�������н�����������
    //�ɲο�����������������
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

    //��Ҷ�ڵ㿪ʼ��¼����������
    //���ݻ����������Ĺ��̣����Ƶ��������n-1��������ţ���'\0'����Ϊn��
    (*HC_ARR) = (P_HC)malloc(NUM_OF_W * sizeof(char*));
    char* temp_box = (char*)malloc(NUM_OF_W * sizeof(char));
    if((*HC_ARR) == NULL || temp_box == NULL) return;
    LINK temp_l;/*��child->parent·��ѭ��������Ŀ���Ǵ�Ҷ�ڵ��������ѭ��ֱ�����ڵ㣨û�и��ڵ�ĵ㣩*/
    LINK temp_c;/*����temp_box��0ѭ����+1������Ŀ���ǽ�0��1������д��temp_box��*/

    for( i=0; i<NUM_OF_W; ++i )
    {
	//�ӵ�ǰҶ�ڵ㿪ʼѭ������child->parent·������ڵ㿿����ֱ�����ڵ����
	for(temp_l=i,temp_c=0; (*HT_ARR)[temp_l].parent != 0; temp_l=(*HT_ARR)[temp_l].parent,++temp_c)
	{
	    //�жϵ�ǰ�ӽڵ����ڸ��ڵ����߻����ұ�
	    if((*HT_ARR)[(*HT_ARR)[temp_l].parent].lchild == temp_l)
		temp_box[temp_c] = '0';
	    else
		temp_box[temp_c] = '1';
	}
	/*��ʱtemp_c���±�Ļ�����ָ��Ҫ�������ַ������'\0'��λ��*/
	temp_box[temp_c] = '\0';
	/*Ϊ�����ַ��������еĵ�ǰҶ�ڵ����ռ䣬��ʱ��Ϊ�ռ��С���ַ���������,temp_cҪ+1*/
	++temp_c;
	(*HC_ARR)[i] = (char*)malloc((temp_c) * sizeof(char));
	strncpy((*HC_ARR)[i],temp_box,temp_c);
	//int testtest = 1;//gdb��ϵ�ʹ��
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
    //һ���ڱ�д����ʱΪ�����׵��Ժ͸Ĵ��������Ը��ľ����ٵ��
    //WEIGHT arr_weight[] = {12, 10, 5};

    int NUM_OF_WEIGHT = sizeof(arr_weight)/sizeof(WEIGHT);                       
    
    P_HT huffman_tree = 0;
    P_HC huffman_code = 0;

    //����
    HuffmanCoding(&huffman_tree,&huffman_code,arr_weight,NUM_OF_WEIGHT);
       
    Show_HT_ARR(huffman_tree,2*NUM_OF_WEIGHT-1);
    Show_HC_ARR(huffman_code,NUM_OF_WEIGHT);
    
    //������
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
