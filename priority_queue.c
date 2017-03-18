/*
 *                                 优先队列
 * 1.一些应用如操作系统进程管理，打印任务管理等，都需要在队列中对占用时间较短
 *   的或级别较高的作业优先处理。因此这类任务需要一个优先队列模型。相较于普通
 *   队列，可对级别较高的作业进行优先处理。
 * 2.基本操作有Insert入队操作，DeleteMin出队操作，Insert操作和普通队列一样，而
 *   出队操作指的是每次将队列中(关键字)最小的元素出队。这个最小元素可以指任务
 *   的优先级别。如在Linux中就是优先级别越高，数字越小。
 *   以Insert和DeleteMin操作为基础，可以扩展优先队列的操作有DecreaseKey(降key)，
 *   IncreaseKey(升key)，Delete，BuildHeap。
 * 3.一些简单的实现，如用数组或链表作为队列存储结构，每次遍历出最小元素进行出队，
 *   这样总会有一个操作的运行时间为O(N)；若将二叉搜索树作为存储结构，虽然Insert
 *   和DeleteMin操作可以达到LogN，但是有点儿大材小用且每次删除最小值，会造成树
 *   左右失衡。
 * 4.一般实现优先队列的工具是二叉堆(binary heap)，简称堆。因为使用的很普遍，因
 *   此一般说堆就是指其所实现的优先队列。堆其实就是一颗完全二叉树，最底层可能因
 *   数据不够有例外，但也是从左到右依次填补的。由于完全二叉树各个节点非常有规律，
 *   因此可以用数组来表示这颗完全二叉树。数组中，一个i处的节点的左儿子在2i处，右
 *   儿子在2i+1处，父节点则在i/2处。用数组表示的唯一缺点是如果树节点过多，计算
 *   机可能分配不了这么大的连续的内存，但这种情况在当今越来越可以忽略，而且其作
 *   为一个流动的队列，一般都可设计在计算机的承受之内。此外，堆要求具有堆序性。
 *   堆序性，即堆中元素的排列有一定要求：根节点的元素一定小于或等于其后代的元素。
 *   这也是优先队列的堆操作Insert和DeleteMin所应该保持的性质。
 * 5.Insert操作
 *   采用的策略是上滤。设插入的元素是X，在数组数据的末尾找到一个空位，如果X可以
 *   直接放入空位，则插入结束，否则将空位的父节点放入空位，让父节点处形成新的空
 *   位(在树中看就是向上层推进)，再次验证X是否可以放入，如此循环一直到队首。可在
 *   队首0处设置一个绝对小的值作为哨兵，插入结束。
 *   插入操作要及时返回插入位置，如打印机操作，插入一个作业，返回插入的位置可以
 *   为之后作业的操作提供方便，因为堆序性对在队列中查找一个具体的元素帮助很小。
 *   若不如此，则需要专门对元素在队列中的定位问题进行设计，如利用散列表和特征值
 *   在队列数组中进行散列等。
 *   DeleteMin操作
 *   采用的策略是下滤。与插入相反。最小元素肯定是在根节点，即1处。删除1后，1处形
 *   成一个空位。在采用Insert的策略，插入的元素是队列的最后一个元素X。当X可以直
 *   接插入空位时，操作结束，否则选择空位两个后代中较小的一个补到空位处，然后这个
 *   后代处形成新的空位(在树中看就是向下层推进)，再次验证X可否插入，如此循环，直
 *   到X可以插入(一定会有位置可以插入)，算法结束。
 *   DecreaseKey/IncreaseKey操作
 *   降低/提高队列指定位置元素的关键字的值，然后进行上/下滤操作，让元素到达合适
 *   的位置，保持堆序性。
 *   Delete操作
 *   删除队列中指定位置的元素，先对该位置元素进行降key操作，使其达到队首，然后进
 *   行DeleteMin操作。也可进行伪删除，只标记要删除的元素，但这样需要其他操作配合。
 *   BuildHeap操作
 *   建堆操作，按元素顺序放入队列中，然后从N/2处(倒数第二层最后一个元素)开始，向
 *   队列开始处对队列元素进行下渗操作，从而保证堆序性。
 *
 *
 *                                                         2016年12月13日
 */

//#define _DEBUG_CLOSE_
#include "PublicForAlgorithms.h"

#define MAX_PQ_LEN (20 + 1)
#define MAX_PQ_ELEMENT_NUM 20
#define MAX_TASK_NAME_LEN 20
#define MIN_MORE_ELEMENT_LEVEL -1 /*即元素等级字段最小值为0*/

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

/*用分配的方法直接建堆*/
P_Priority_Queue CreateOnePriorityQueue(void)
{
    P_Priority_Queue new_pq = (P_Priority_Queue)malloc(sizeof(Priority_Queue));
    if(new_pq == NULL){ LINE_DEBUG("Priority_Queue malloc failed"); return NULL; }
    new_pq->e_num = 0;
    int i = 0;
    while(i < MAX_PQ_LEN){ new_pq->queue[i] = NULL; ++i; }
    return new_pq;
}

/*建堆操作
 *预留哨兵位置，从elements中顺序读元素入队列，然后进行整序*/
P_Priority_Queue PQ_BuildHeap(P_Element elements[],int size)
{
    if(size < 0 || size > MAX_PQ_ELEMENT_NUM)
    { LINE_DEBUG("BuildHeap elements size is not valid"); return NULL; }
    
    P_Priority_Queue H = (P_Priority_Queue)malloc(sizeof(Priority_Queue));
    if(H == NULL){ LINE_DEBUG("BuildHeap malloc failed"); return NULL; }
    int i = 0;
    for(i = 0; i < size; ++i){ H->queue[i + 1] = elements[i]; }
    H->e_num = i;
    /*整理堆序性*/
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
			root = lchild;/*向下走*/
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
			root = rchild;/*向下走*/
		    }
		    else
		    { break; }
		}
	    }
	    else/*只有一个左子节点*/
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

/*优先队列插入操作
 *返回插入的位置，-1代表失败*/
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
	/*找到合适的空位，注意堆序性为 根节点<=子节点，且因为有哨兵，则
	 *在此if中一定就可以找到合适的空位*/
	if(element->level >= PQ->queue[parent]->level)
	{
	    PQ->queue[blank] = element;
	    ++(PQ->e_num);
	    break;
	}
	/*上滤*/
	PQ->queue[blank] = PQ->queue[parent];
	blank = parent;
    }
    return blank;
}

/*优先队列删除操作
 * 注意下滤过程没有哨兵，其结束循环条件与上滤略有不同，
 * 且元素等级值无最大值限制*/
P_Element PQ_DeleteMin(P_Priority_Queue PQ)
{
    if(PQ == NULL){ LINE_DEBUG("DeleteMin PQ is NULL"); return NULL; }
    if(PQ->e_num == 0){ LINE_DEBUG("DeleteMin PQ there is no element"); return NULL; }
    P_Element min_element = PQ->queue[1];
    int last_level = PQ->queue[PQ->e_num]->level;/*队列的最后一个元素作为插入元素*/
    int lchild,rchild;
    int blank = 1;
    /*blank的左子节点位置小于最后一个元素，即位置最大为倒数第二个元素，
     *也即右子节点位置最大为最后一个元素*/
    while((blank*2) < PQ->e_num)
    {
	lchild = blank*2; rchild = lchild + 1;
	/*找到合适的空位*/
	if(last_level <= PQ->queue[lchild]->level && last_level <= PQ->queue[rchild]->level)
	{ break; }
	/*下滤*/
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
    /*循环结束后找到合适的空位，填入最后一个元素*/
    PQ->queue[blank] = PQ->queue[PQ->e_num];
    PQ->queue[PQ->e_num] = NULL;
    --(PQ->e_num);
    /*返回最小元素*/
    return min_element;
}

/*降低PQ队列中p位置的元素的关键字level为level
 *返回降key元素新的位置，失败返回-1*/
int PQ_DecreaseKey(P_Priority_Queue PQ,int p,int level)
{
    if(PQ == NULL){ LINE_DEBUG("DecreaseKey PQ is NULL"); return -1; }
    if(p < 1 || p > PQ->e_num){ LINE_DEBUG("DecreaseKey p is illegal"); return -1; }
    if(level <= MIN_MORE_ELEMENT_LEVEL || level >= PQ->queue[p]->level)
    { LINE_DEBUG("DecreaseKey level is not valid"); return -1; }
    /*上滤*/
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

/*提高PQ队列中p位置的元素的关键字level为level*/
int PQ_IncreaseKey(P_Priority_Queue PQ,int p,int level)
{
    if(PQ == NULL){ LINE_DEBUG("IncreaseKey PQ is NULL"); return -1; }
    if(p < 1 || p > PQ->e_num){ LINE_DEBUG("IncreaseKey p is illegal"); return -1; }
    if(level <= PQ->queue[p]->level){ LINE_DEBUG("IncreaseKey level is not valid"); return -1; }
    /*下滤*/
    PQ->queue[p]->level = level;
    P_Element down_e = PQ->queue[p];
    int blank = p;
    int lchild,rchild;
    while((blank*2) <= PQ->e_num)/*考虑缺少右子节点情况*/
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
	else/*只有一个左子节点*/
	{
	    if(level <= PQ->queue[lchild]->level){ break; }
	    PQ->queue[blank] = PQ->queue[lchild];
	    blank = lchild;
	}
    }
    PQ->queue[blank] = down_e;
    return blank;
}

/*删除PQ队列中指定位置的元素*/
P_Element PQ_Delete(P_Priority_Queue PQ,int p)
{
    if(PQ == NULL){ LINE_DEBUG("Delete PQ is NULL"); return NULL; }
    if(p < 1 || p > PQ->e_num){ LINE_DEBUG("Delete p is illegal"); return NULL; }
    /*上滤，这里不用实质性的改变p处元素的level，直接将此处当作空位即可*/
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
    /*下滤，直接调用DeleteMin即可*/
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
    P_Element element0 = CreateOneElement(MIN_MORE_ELEMENT_LEVEL,"哨兵");
    P_Element element2 = CreateOneElement(2,"系统防火墙");
    P_Element element8 = CreateOneElement(8,"窗口管理器");
    P_Element element6 = CreateOneElement(6,"系统中断");
    P_Element element12 = CreateOneElement(12,"服务网络");
    P_Element element20 = CreateOneElement(20,"系统索引器");
    P_Element element25 = CreateOneElement(25,"系统设置");
    P_Element element30 = CreateOneElement(30,"模块管理");
    P_Element element40 = CreateOneElement(40,"蓝牙");

    P_Priority_Queue PQ = CreateOnePriorityQueue();
    PQ->queue[0] = element0;/*设置哨兵*/
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
    printf("降key\n");
    PQ_DecreaseKey(PQ,4,2);
    PQ_Show(PQ);
    printf("升key\n");
    PQ_IncreaseKey(PQ,3,50);
    PQ_Show(PQ);
    */
    /*没有释放的哨兵和6个元素作为数组的元素*/
    P_Element elements[6] = { element40,element20,element6,element30,element25,element8, };
    P_Priority_Queue Heap = PQ_BuildHeap(elements,6);
    Heap->queue[0] = element0;/*手动设置哨兵*/
    PQ_Show(Heap);
    
    //清理工作
    PQ_Free(PQ);
    SAFE_FREE(Heap);

    return 0;
}
