/*
 *                                 ���ȶ���
 * 1.һЩӦ�������ϵͳ���̹�����ӡ�������ȣ�����Ҫ�ڶ����ж�ռ��ʱ��϶�
 *   �Ļ򼶱�ϸߵ���ҵ���ȴ����������������Ҫһ�����ȶ���ģ�͡��������ͨ
 *   ���У��ɶԼ���ϸߵ���ҵ�������ȴ���
 * 2.����������Insert��Ӳ�����DeleteMin���Ӳ�����Insert��������ͨ����һ������
 *   ���Ӳ���ָ����ÿ�ν�������(�ؼ���)��С��Ԫ�س��ӡ������СԪ�ؿ���ָ����
 *   �����ȼ�������Linux�о������ȼ���Խ�ߣ�����ԽС��
 *   ��Insert��DeleteMin����Ϊ������������չ���ȶ��еĲ�����DecreaseKey(��key)��
 *   IncreaseKey(��key)��Delete��BuildHeap��
 * 3.һЩ�򵥵�ʵ�֣����������������Ϊ���д洢�ṹ��ÿ�α�������СԪ�ؽ��г��ӣ�
 *   �����ܻ���һ������������ʱ��ΪO(N)������������������Ϊ�洢�ṹ����ȻInsert
 *   ��DeleteMin�������ԴﵽLogN�������е�����С����ÿ��ɾ����Сֵ���������
 *   ����ʧ�⡣
 * 4.һ��ʵ�����ȶ��еĹ����Ƕ����(binary heap)����ƶѡ���Ϊʹ�õĺ��ձ飬��
 *   ��һ��˵�Ѿ���ָ����ʵ�ֵ����ȶ��С�����ʵ����һ����ȫ����������ײ������
 *   ���ݲ��������⣬��Ҳ�Ǵ�����������ġ�������ȫ�����������ڵ�ǳ��й��ɣ�
 *   ��˿�������������ʾ�����ȫ�������������У�һ��i���Ľڵ���������2i������
 *   ������2i+1�������ڵ�����i/2�����������ʾ��Ψһȱ����������ڵ���࣬����
 *   �����ܷ��䲻����ô����������ڴ棬����������ڵ���Խ��Խ���Ժ��ԣ���������
 *   Ϊһ�������Ķ��У�һ�㶼������ڼ�����ĳ���֮�ڡ����⣬��Ҫ����ж����ԡ�
 *   �����ԣ�������Ԫ�ص�������һ��Ҫ�󣺸��ڵ��Ԫ��һ��С�ڻ����������Ԫ�ء�
 *   ��Ҳ�����ȶ��еĶѲ���Insert��DeleteMin��Ӧ�ñ��ֵ����ʡ�
 * 5.Insert����
 *   ���õĲ��������ˡ�������Ԫ����X�����������ݵ�ĩβ�ҵ�һ����λ�����X����
 *   ֱ�ӷ����λ���������������򽫿�λ�ĸ��ڵ�����λ���ø��ڵ㴦�γ��µĿ�
 *   λ(�����п��������ϲ��ƽ�)���ٴ���֤X�Ƿ���Է��룬���ѭ��һֱ�����ס�����
 *   ����0������һ������С��ֵ��Ϊ�ڱ������������
 *   �������Ҫ��ʱ���ز���λ�ã����ӡ������������һ����ҵ�����ز����λ�ÿ���
 *   Ϊ֮����ҵ�Ĳ����ṩ���㣬��Ϊ�����Զ��ڶ����в���һ�������Ԫ�ذ�����С��
 *   ������ˣ�����Ҫר�Ŷ�Ԫ���ڶ����еĶ�λ���������ƣ�������ɢ�б������ֵ
 *   �ڶ��������н���ɢ�еȡ�
 *   DeleteMin����
 *   ���õĲ��������ˡ�������෴����СԪ�ؿ϶����ڸ��ڵ㣬��1����ɾ��1��1����
 *   ��һ����λ���ڲ���Insert�Ĳ��ԣ������Ԫ���Ƕ��е����һ��Ԫ��X����X����ֱ
 *   �Ӳ����λʱ����������������ѡ���λ��������н�С��һ��������λ����Ȼ�����
 *   ������γ��µĿ�λ(�����п��������²��ƽ�)���ٴ���֤X�ɷ���룬���ѭ����ֱ
 *   ��X���Բ���(һ������λ�ÿ��Բ���)���㷨������
 *   DecreaseKey/IncreaseKey����
 *   ����/��߶���ָ��λ��Ԫ�صĹؼ��ֵ�ֵ��Ȼ�������/���˲�������Ԫ�ص������
 *   ��λ�ã����ֶ����ԡ�
 *   Delete����
 *   ɾ��������ָ��λ�õ�Ԫ�أ��ȶԸ�λ��Ԫ�ؽ��н�key������ʹ��ﵽ���ף�Ȼ���
 *   ��DeleteMin������Ҳ�ɽ���αɾ����ֻ���Ҫɾ����Ԫ�أ���������Ҫ����������ϡ�
 *   BuildHeap����
 *   ���Ѳ�������Ԫ��˳���������У�Ȼ���N/2��(�����ڶ������һ��Ԫ��)��ʼ����
 *   ���п�ʼ���Զ���Ԫ�ؽ��������������Ӷ���֤�����ԡ�
 *
 *
 *                                                         2016��12��13��
 */

//#define _DEBUG_CLOSE_
#include "PublicForAlgorithms.h"

#define MAX_PQ_LEN (20 + 1)
#define MAX_PQ_ELEMENT_NUM 20
#define MAX_TASK_NAME_LEN 20
#define MIN_MORE_ELEMENT_LEVEL -1 /*��Ԫ�صȼ��ֶ���СֵΪ0*/

typedef struct
{
    int level;
    char task[MAX_TASK_NAME_LEN];
}Element,*P_Element;

P_Element CreateOneElement(int level,char *name)
{
    P_Element new_e = (P_Element)malloc(sizeof(Element));
    if(new_e == NULL){ LINE_DEBUG("Element malloc failed"); return NULL; }
    new_e->level = level;
    strncpy(new_e->task,name,MAX_TASK_NAME_LEN);
    return new_e;
}

typedef struct
{
    int e_num;
    P_Element queue[MAX_PQ_LEN];
}Priority_Queue,*P_Priority_Queue;

/*�÷���ķ���ֱ�ӽ���*/
P_Priority_Queue CreateOnePriorityQueue(void)
{
    P_Priority_Queue new_pq = (P_Priority_Queue)malloc(sizeof(Priority_Queue));
    if(new_pq == NULL){ LINE_DEBUG("Priority_Queue malloc failed"); return NULL; }
    new_pq->e_num = 0;
    int i = 0;
    while(i < MAX_PQ_LEN){ new_pq->queue[i] = NULL; ++i; }
    return new_pq;
}

/*���Ѳ���
 *Ԥ���ڱ�λ�ã���elements��˳���Ԫ������У�Ȼ���������*/
P_Priority_Queue PQ_BuildHeap(P_Element elements[],int size)
{
    if(size < 0 || size > MAX_PQ_ELEMENT_NUM)
    { LINE_DEBUG("BuildHeap elements size is not valid"); return NULL; }
    
    P_Priority_Queue H = (P_Priority_Queue)malloc(sizeof(Priority_Queue));
    if(H == NULL){ LINE_DEBUG("BuildHeap malloc failed"); return NULL; }
    int i = 0;
    for(i = 0; i < size; ++i){ H->queue[i + 1] = elements[i]; }
    H->e_num = i;
    /*���������*/
    int root,lchild,rchild;
    P_Element temp;
    for(i = i/2; i > 0; --i)
    {
	root = i;
	while(root*2 <= H->e_num)
	{
	    lchild = root*2; rchild = lchild + 1;
	    temp = H->queue[root];
	    if(rchild <= H->e_num)
	    {
		if(H->queue[lchild]->level < H->queue[rchild]->level)
		{
		    if(H->queue[lchild]->level < H->queue[root]->level)
		    {
			H->queue[root] = H->queue[lchild];
			H->queue[lchild] = temp;
			root = lchild;/*������*/
		    }
		    else
		    { break; }
		}
		else
		{
		    if(H->queue[rchild]->level < H->queue[root]->level)
		    {
			H->queue[root] = H->queue[rchild];
			H->queue[rchild] = temp;
			root = rchild;/*������*/
		    }
		    else
		    { break; }
		}
	    }
	    else/*ֻ��һ�����ӽڵ�*/
	    {
		if(H->queue[lchild]->level < H->queue[root]->level)
		{
		    H->queue[root] = H->queue[lchild];
		    H->queue[lchild] = temp;
		    root = lchild;
		}
		else
		{ break; }
	    }
	}/*while end*/
    }/*for end*/
    
    return H;
}

/*���ȶ��в������
 *���ز����λ�ã�-1����ʧ��*/
int PQ_Insert(P_Priority_Queue PQ,P_Element element)
{
    if(PQ == NULL){ LINE_DEBUG("Insert PQ is NULL"); return -1; }
    if(element == NULL){ LINE_DEBUG("Insert element is NULL"); return -1; }
    if(element->level <= MIN_MORE_ELEMENT_LEVEL)
    { LINE_DEBUG("Insert element level is not valid"); return -1; }
    if(PQ->e_num == MAX_PQ_ELEMENT_NUM){ LINE_DEBUG("Insert Queue is FULL"); return -1; }
    int blank = PQ->e_num + 1; int parent;
    while(blank > 0)
    {
	parent = blank/2;
	/*�ҵ����ʵĿ�λ��ע�������Ϊ ���ڵ�<=�ӽڵ㣬����Ϊ���ڱ�����
	 *�ڴ�if��һ���Ϳ����ҵ����ʵĿ�λ*/
	if(element->level >= PQ->queue[parent]->level)
	{
	    PQ->queue[blank] = element;
	    ++(PQ->e_num);
	    break;
	}
	/*����*/
	PQ->queue[blank] = PQ->queue[parent];
	blank = parent;
    }
    return blank;
}

/*���ȶ���ɾ������
 * ע�����˹���û���ڱ��������ѭ���������������в�ͬ��
 * ��Ԫ�صȼ�ֵ�����ֵ����*/
P_Element PQ_DeleteMin(P_Priority_Queue PQ)
{
    if(PQ == NULL){ LINE_DEBUG("DeleteMin PQ is NULL"); return NULL; }
    if(PQ->e_num == 0){ LINE_DEBUG("DeleteMin PQ there is no element"); return NULL; }
    P_Element min_element = PQ->queue[1];
    int last_level = PQ->queue[PQ->e_num]->level;/*���е����һ��Ԫ����Ϊ����Ԫ��*/
    int lchild,rchild;
    int blank = 1;
    /*blank�����ӽڵ�λ��С�����һ��Ԫ�أ���λ�����Ϊ�����ڶ���Ԫ�أ�
     *Ҳ�����ӽڵ�λ�����Ϊ���һ��Ԫ��*/
    while((blank*2) < PQ->e_num)
    {
	lchild = blank*2; rchild = lchild + 1;
	/*�ҵ����ʵĿ�λ*/
	if(last_level <= PQ->queue[lchild]->level && last_level <= PQ->queue[rchild]->level)
	{ break; }
	/*����*/
	if(PQ->queue[lchild]->level <= PQ->queue[rchild]->level)
	{
	    PQ->queue[blank] = PQ->queue[lchild];
	    blank = lchild; 
	}
	else
	{
	    PQ->queue[blank] = PQ->queue[rchild];
	    blank = rchild;
	}
    }
    /*ѭ���������ҵ����ʵĿ�λ���������һ��Ԫ��*/
    PQ->queue[blank] = PQ->queue[PQ->e_num];
    PQ->queue[PQ->e_num] = NULL;
    --(PQ->e_num);
    /*������СԪ��*/
    return min_element;
}

/*����PQ������pλ�õ�Ԫ�صĹؼ���levelΪlevel
 *���ؽ�keyԪ���µ�λ�ã�ʧ�ܷ���-1*/
int PQ_DecreaseKey(P_Priority_Queue PQ,int p,int level)
{
    if(PQ == NULL){ LINE_DEBUG("DecreaseKey PQ is NULL"); return -1; }
    if(p < 1 || p > PQ->e_num){ LINE_DEBUG("DecreaseKey p is illegal"); return -1; }
    if(level <= MIN_MORE_ELEMENT_LEVEL || level >= PQ->queue[p]->level)
    { LINE_DEBUG("DecreaseKey level is not valid"); return -1; }
    /*����*/
    PQ->queue[p]->level = level;
    P_Element up_e = PQ->queue[p];
    int blank = p;
    int parent;
    while(blank > 0)
    {
	parent = blank/2;
	if(level >= PQ->queue[parent]->level)
	{ 
	    PQ->queue[blank] = up_e;
	    break;
	}
	PQ->queue[blank] = PQ->queue[parent];
	blank = parent;
    }
    return blank;
}

/*���PQ������pλ�õ�Ԫ�صĹؼ���levelΪlevel*/
int PQ_IncreaseKey(P_Priority_Queue PQ,int p,int level)
{
    if(PQ == NULL){ LINE_DEBUG("IncreaseKey PQ is NULL"); return -1; }
    if(p < 1 || p > PQ->e_num){ LINE_DEBUG("IncreaseKey p is illegal"); return -1; }
    if(level <= PQ->queue[p]->level){ LINE_DEBUG("IncreaseKey level is not valid"); return -1; }
    /*����*/
    PQ->queue[p]->level = level;
    P_Element down_e = PQ->queue[p];
    int blank = p;
    int lchild,rchild;
    while((blank*2) <= PQ->e_num)/*����ȱ�����ӽڵ����*/
    {
	lchild = blank*2; rchild = lchild + 1;
	if(rchild <= PQ->e_num)
	{
	    if(level <= PQ->queue[lchild]->level && level <= PQ->queue[rchild]->level)
	    { break; }
	    if(PQ->queue[lchild]->level <= PQ->queue[rchild]->level)
	    {
		PQ->queue[blank] = PQ->queue[lchild];
		blank = lchild;
	    }
	    else
	    {
		PQ->queue[blank] = PQ->queue[rchild];
		blank = rchild;
	    }
	}
	else/*ֻ��һ�����ӽڵ�*/
	{
	    if(level <= PQ->queue[lchild]->level){ break; }
	    PQ->queue[blank] = PQ->queue[lchild];
	    blank = lchild;
	}
    }
    PQ->queue[blank] = down_e;
    return blank;
}

/*ɾ��PQ������ָ��λ�õ�Ԫ��*/
P_Element PQ_Delete(P_Priority_Queue PQ,int p)
{
    if(PQ == NULL){ LINE_DEBUG("Delete PQ is NULL"); return NULL; }
    if(p < 1 || p > PQ->e_num){ LINE_DEBUG("Delete p is illegal"); return NULL; }
    /*���ˣ����ﲻ��ʵ���Եĸı�p��Ԫ�ص�level��ֱ�ӽ��˴�������λ����*/
    P_Element del_e = PQ->queue[p];
    int blank = p;
    int parent;
    while(blank > 0)
    {
	parent = blank/2;
	/*
	//do nothing
	if(MIN_MORE_ELEMENT_LEVEL >= PQ->queue[parent]->level)
	{ break; }*/
	PQ->queue[blank] = PQ->queue[parent];
	blank = parent;
    }
    /*���ˣ�ֱ�ӵ���DeleteMin����*/
    PQ_DeleteMin(PQ);

    return del_e;
}

void PQ_Show(P_Priority_Queue PQ)
{
    if(PQ == NULL){ LINE_DEBUG("DeleteMin PQ is NULL"); return; }
    int i = 1;
    while(i <= PQ->e_num)
    {
	printf("%s-%d ",PQ->queue[i]->task,PQ->queue[i]->level);
	++i;
    }
    printf("\n");
}

void PQ_Free(P_Priority_Queue PQ)
{
    if(PQ == NULL){ LINE_DEBUG("DeleteMin PQ is NULL"); return; }
    int i = 0;
    while(i < MAX_PQ_LEN)
    {
	SAFE_FREE(PQ->queue[i]);
	++i;
    }
    SAFE_FREE(PQ);
}



int main()
{
    P_Element element0 = CreateOneElement(MIN_MORE_ELEMENT_LEVEL,"�ڱ�");
    P_Element element2 = CreateOneElement(2,"ϵͳ����ǽ");
    P_Element element8 = CreateOneElement(8,"���ڹ�����");
    P_Element element6 = CreateOneElement(6,"ϵͳ�ж�");
    P_Element element12 = CreateOneElement(12,"��������");
    P_Element element20 = CreateOneElement(20,"ϵͳ������");
    P_Element element25 = CreateOneElement(25,"ϵͳ����");
    P_Element element30 = CreateOneElement(30,"ģ�����");
    P_Element element40 = CreateOneElement(40,"����");

    P_Priority_Queue PQ = CreateOnePriorityQueue();
    PQ->queue[0] = element0;/*�����ڱ�*/
    PQ_Show(PQ);

    printf("Insert25---------------------------\n");
    PQ_Insert(PQ,element25);
    PQ_Show(PQ);
    printf("Insert12---------------------------\n");
    PQ_Insert(PQ,element12);
    PQ_Show(PQ);
    printf("Insert40---------------------------\n");
    PQ_Insert(PQ,element40);
    PQ_Show(PQ);
    printf("Insert8---------------------------\n");
    PQ_Insert(PQ,element8);
    PQ_Show(PQ);
    printf("Insert6---------------------------\n");
    PQ_Insert(PQ,element6);
    PQ_Show(PQ);
    printf("Insert2---------------------------\n");
    PQ_Insert(PQ,element2);
    PQ_Show(PQ);
    printf("Insert30---------------------------\n");
    PQ_Insert(PQ,element30);
    PQ_Show(PQ);
    printf("Insert20---------------------------\n");
    PQ_Insert(PQ,element20);
    PQ_Show(PQ);
    
    P_Element min_element = PQ_DeleteMin(PQ);
    if(min_element){ printf("Delete %s------------\n",min_element->task); }
    SAFE_FREE(min_element);
    PQ_Show(PQ);
    min_element = PQ_DeleteMin(PQ);
    if(min_element){ printf("Delete %s------------\n",min_element->task); }
    SAFE_FREE(min_element);
    PQ_Show(PQ);
    min_element = PQ_DeleteMin(PQ);
    if(min_element){ printf("Delete %s------------\n",min_element->task); }
    SAFE_FREE(min_element);
    PQ_Show(PQ);
    min_element = PQ_DeleteMin(PQ);
    if(min_element){ printf("Delete %s------------\n",min_element->task); }
    SAFE_FREE(min_element);
    PQ_Show(PQ);
    min_element = PQ_DeleteMin(PQ);
    if(min_element){ printf("Delete %s------------\n",min_element->task); }
    SAFE_FREE(min_element);
    PQ_Show(PQ);
    min_element = PQ_DeleteMin(PQ);
    if(min_element){ printf("Delete %s------------\n",min_element->task); }
    SAFE_FREE(min_element);
    PQ_Show(PQ);
    min_element = PQ_DeleteMin(PQ);
    if(min_element){ printf("Delete %s------------\n",min_element->task); }
    SAFE_FREE(min_element);
    PQ_Show(PQ);
    min_element = PQ_DeleteMin(PQ);
    if(min_element){ printf("Delete %s------------\n",min_element->task); }
    SAFE_FREE(min_element);
    PQ_Show(PQ);
    min_element = PQ_DeleteMin(PQ);
    if(min_element){ printf("Delete %s------------\n",min_element->task); }
    SAFE_FREE(min_element);
    PQ_Show(PQ);
    
    /*
    P_Element del_element = PQ_Delete(PQ,5);
    if(del_element){ printf("Delete %s------------\n",del_element->task); }
    SAFE_FREE(del_element);
    PQ_Show(PQ);
    del_element = PQ_Delete(PQ,1);
    if(del_element){ printf("Delete %s------------\n",del_element->task); }
    SAFE_FREE(del_element);
    PQ_Show(PQ);
    del_element = PQ_Delete(PQ,3);
    if(del_element){ printf("Delete %s------------\n",del_element->task); }
    SAFE_FREE(del_element);
    PQ_Show(PQ);
    del_element = PQ_Delete(PQ,1);
    if(del_element){ printf("Delete %s------------\n",del_element->task); }
    SAFE_FREE(del_element);
    PQ_Show(PQ);
    del_element = PQ_Delete(PQ,1);
    if(del_element){ printf("Delete %s------------\n",del_element->task); }
    SAFE_FREE(del_element);
    PQ_Show(PQ);
    */
    
    /*
    printf("��key\n");
    PQ_DecreaseKey(PQ,4,2);
    PQ_Show(PQ);
    printf("��key\n");
    PQ_IncreaseKey(PQ,3,50);
    PQ_Show(PQ);
    */
    /*û���ͷŵ��ڱ���6��Ԫ����Ϊ�����Ԫ��*/
    P_Element elements[6] = { element40,element20,element6,element30,element25,element8, };
    P_Priority_Queue Heap = PQ_BuildHeap(elements,6);
    Heap->queue[0] = element0;/*�ֶ������ڱ�*/
    PQ_Show(Heap);
    
    //������
    PQ_Free(PQ);
    SAFE_FREE(Heap);

    return 0;
}
