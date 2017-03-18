/*
 *                                   队列
 *             ------------------------------------------------
 *
 *  out <----- <----- <----- <----- <----- <----- <----- <----- <----- in   
 *
 *             ------------------------------------------------
 *                                   data
 *  
 *  1.实现功能：将一棵二叉树进行广度优先遍历输出。基本思路就是在队列中每输出
 *    一个(根)节点，同时就把它的两个(非空)子节点压入队列中，如此反复，直至所
 *    队列中的数据为空。
 *
 *
 *                                                     2016年11月17日
 */

//#define _DEBUG_CLOSE_
#include "PublicForAlgorithms.h"

/* 队列大小的设计跟实际需求和数据量和处理的方式有关
 * 这里实现的树的广度优先遍历，基本是弹一个压两个的
 * 处理形式。因此设计太小会出现写满的情况，最小也是
 * 可以容纳所有叶节点 + 哨兵 的大小。这是一个问题。
 * 队列的大小呈指数级的增长。
 */
#define QUEUE_MAX_LEN (16+1)

typedef int ElementType;

typedef struct Node
{
    ElementType element;
    struct Node* lchild;
    struct Node* rchild;
}Node, *P_Node, *Tree;

typedef struct
{
    P_Node queue[QUEUE_MAX_LEN];
    int r_p;//读位置
    int w_p;//写位置
    int count;//剩余可读数据量
}Queue, *P_Queue;

P_Queue CreateQueue()
{
    P_Queue new_queue = (P_Queue)malloc(sizeof(Queue));
    if(new_queue == NULL){ LINE_DEBUG("malloc queue failed"); return NULL; }
    int i = 0;while(i < QUEUE_MAX_LEN){new_queue->queue[i] = NULL; ++i; }
    new_queue->r_p = 0;
    new_queue->w_p = 0;
    new_queue->count = 0;
    return new_queue;
}

//压栈：向Q中压入num个node，num个node用线性表表示
bool Push(P_Queue Q,P_Node nodes[],int num)
{
    if(Q == NULL || nodes == NULL){ LINE_DEBUG("queue is NULL"); return false; }
    if(num <= 0){ LINE_DEBUG("num is illegal"); return false; }
    
    int i = 0;
    while(i < num)
    {
	/* 在上次Push后且可读数据满时，w_p==QUEUE_MAX_LEN，则此次先折回队列头
	 * 然后再返回。当写满时且r_p=0时，说明0处的数据还未读取过，不能将w_p置
	 * 为0，防止下次写时直接将未读的数据覆盖
	 */
	if((Q->w_p == QUEUE_MAX_LEN) && (Q->r_p != 0)){ Q->w_p = 0; }
	if(Q->count == QUEUE_MAX_LEN)
	{ 
	    LINE_DEBUG("queue is FULL，%d data have not been pushed in queue",(num - i));
	    return false; 
	}
	
	//压入数据，空节点不压入
	if(nodes[i] != NULL){ Q->queue[Q->w_p] = nodes[i]; ++(Q->w_p); ++(Q->count); }
	++i;
    }
    return true;
}

//弹栈，从Q中弹出num个node到nodes中
bool Pop(P_Queue Q,P_Node nodes[],int num)
{
    if(Q == NULL || nodes == NULL){ LINE_DEBUG("queue is NULL"); return false; }
    if(num <= 0){ LINE_DEBUG("num is illegal"); return false; }
    
    int i = 0;
    while(i < num)
    {
	//当w_p在0的位置的时候，r_p可以置0，此时count=0；不会读取重复的数据
	if(Q->r_p == QUEUE_MAX_LEN){ Q->r_p = 0; }
	if(Q->count == 0)
	{
	    LINE_DEBUG("queue is NULL，%d data have not been popped in queue",(num - i));
	    return false;
	}
	
	nodes[i] = Q->queue[Q->r_p];
	++(Q->r_p);
	--(Q->count);
	++i;
    }
    return true;
}

bool Clear(P_Queue Q)
{
    if(Q == NULL){ LINE_DEBUG("queue is NULL"); return false; }
    int i = 0;
    while(i < QUEUE_MAX_LEN)
    {
	Q->queue[i] = NULL;
	++i;
    }
    Q->r_p = 0;
    Q->w_p = 0;
    Q->count = 0;
}

P_Node CreateNode(ElementType e)
{
    P_Node new_node = (P_Node)malloc(sizeof(Node));
    if(new_node == NULL) return NULL;
    new_node->element = e;
    new_node->lchild  = NULL;
    new_node->rchild  = NULL;
    return new_node;
}

void Tree_Free(Tree root)
{
    if(root == NULL){ return; }
    Tree_Free(root->lchild);
    Tree_Free(root->rchild);
    SAFE_FREE(root);
}

void Show_Tree(P_Queue Q,Tree root)
{
    if(Q == NULL || root == NULL)
    {
	LINE_DEBUG("Queue or Tree is NULL");
	return;
    }
    P_Node Sentry[1];
    P_Node nodes_root[1];
    P_Node nodes_lchild[1];
    P_Node nodes_rchild[1];
    Sentry[0] = CreateNode(1);
    if(Sentry[0] == NULL){ LINE_DEBUG("Sentry malloc failed"); return; }

    /*初始状态Q->count==0，压入根节点和哨兵*/
    nodes_root[0] = root;
    Push(Q,nodes_root,1);
    Push(Q,Sentry,1);
    
    /*每弹出一个节点，就将其两个子节点压入队列
     *一旦再出现Q->count==0，只能是读完了队列中的数据
     *根据对根节点的操作方式，一旦再次出现Q->count==0，
     *则肯定是树中的节点全部输出完毕
     */
    while(Q->count != 0) /*while(1)*/
    {
	Pop(Q,nodes_root,1);
	if(nodes_root[0] == Sentry[0])
	{
	    /*当层弹出完毕，且下一层一定都已经压入队列，
	     *此时再在队尾插入一个哨兵。最后一层的最后一个哨兵弹出后直接退出
	     */
	    printf("\n");
	    if(Q->count == 0){ break; }
	    Push(Q,Sentry,1);
	}
	else
	{
	    printf("%d ",nodes_root[0]->element);
	    nodes_lchild[0] = nodes_root[0]->lchild;
	    Push(Q,nodes_lchild,1);
	    nodes_rchild[0] = nodes_root[0]->rchild;
	    Push(Q,nodes_rchild,1);
	}
    }
    SAFE_FREE(Sentry[0]);
}

int main()
{
/*
 *                              100
 *                        /              \
 *                   50                     150
 *              /        \              /           \
 *             25         75           125            175
 *          /     \          \             \         /     \
 *        10      40         90            135      160    190
 *       /  \    / \         /  \           /  \    /  \   /  \
 *      5   15  30 45       85  95        130 140 155 165 180 200
 */
    P_Node node100 = CreateNode(100); P_Node node50  = CreateNode(50);
    P_Node node150 = CreateNode(150); P_Node node25  = CreateNode(25);
    P_Node node75  = CreateNode(75);  P_Node node125 = CreateNode(125);
    P_Node node175 = CreateNode(175); P_Node node10  = CreateNode(10);
    P_Node node40  = CreateNode(40);  P_Node node90  = CreateNode(90);  
    P_Node node135 = CreateNode(135); P_Node node160 = CreateNode(160);
    P_Node node190 = CreateNode(190); P_Node node5   = CreateNode(5);
    P_Node node15  = CreateNode(15);  P_Node node30  = CreateNode(30);
    P_Node node45  = CreateNode(45);  P_Node node85  = CreateNode(85);
    P_Node node95  = CreateNode(95);  P_Node node130 = CreateNode(130);
    P_Node node140 = CreateNode(140); P_Node node155 = CreateNode(155);
    P_Node node165 = CreateNode(165); P_Node node180 = CreateNode(180);
    P_Node node200 = CreateNode(200);
    node100->lchild = node50;  node100->rchild = node150;
    node50->lchild  = node25;  node50->rchild  = node75;
    node150->lchild = node125; node150->rchild = node175;
    node25->lchild  = node10;  node25->rchild  = node40;
    node75->rchild  = node90;  node125->rchild = node135;
    node175->lchild = node160; node175->rchild = node190;
    node10->lchild  = node5;   node10->rchild  = node15;
    node40->lchild  = node30;  node40->rchild  = node45;
    node90->lchild  = node85;  node90->rchild  = node95;
    node135->lchild = node130; node135->rchild = node140;
    node160->lchild = node155; node160->rchild = node165;
    node190->lchild = node180; node190->rchild = node200;

    P_Queue Q = CreateQueue();
    Show_Tree(Q,node100);
    
    //清理工作
    SAFE_FREE(Q);
    Tree_Free(node100);

    return 0;
}
