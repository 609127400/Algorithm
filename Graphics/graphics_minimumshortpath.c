/*
 *                               最短路径
 * 1.最短路径(MinimumShortPath,MSP)，指图G中任意一个顶点V到达G中其他任一顶点的最短
 *   路径（路径权值和最小）。针对的是带权图，若不带权值，相当于每条边权值相等，经过
 *   的边数越少路径越短。
 * 2.对于最短路径问题，出发点叫做源点，目的地叫做终点。分为单源最短路径，单点对最短
 *   路径，，等等，单源最短路径可以作为理解其他衍生问题的基础。
 * 3.单源最短路径
 *   即一个出发点到图中其他顶点的最短路径。
 *   (1)BellmanFord算法：针对一般图，图中可存在负值边和圈。算法过程就是图遍历扫描所
 *   有顶点和边的过程，借助队列，将所有顶点最短路径值初始化为MAX_MORE_PATH_LEN，将起
 *   始顶点压入队列，然后开始计算。每弹出一个顶点，则分别计算此顶点的最短路径值+ 边
 *   权值是否小于其对应的所有邻接点现有的值，若小于，则更新其邻接点的最小路径值和前
 *   驱顶点。直到遍历完毕或队列弹出多于图顶点数的顶点时，算法结束。可以很简单的得出，
 *   此算法的时间效率为O(E)，E代表图的总边数
 *   需要注意的情况：图是否存在负值圈，即圈的所有边的权值之和是负数。若有向图只存
 *   在负值边而不会导致负值圈，依然可以正确算出最短路径。
 *   有向图中的负值圈，如A->B->C->A，设权值A-B=-4，B-C=1，C-A=1，这种情况就是图中存
 *   在负值圈的情况。设A的最小路径值为2，最短路径值用M表示，边权值用W表示。根据波尔
 *   曼算法，
 *   Pop(A) M(B)=2+-4=-2,Push(B);
 *   Pop(B) M(C)=-2+1=-1,Push(C);
 *   Pop(C) M(A)=-1+1=0(更新),Push(A);(新的M(A) + W(A->B) < M(B)，会继续更新B的M)...
 *   ，一直循环下去，所有点都会趋向无穷小而无法确定最小路径值。
 *   在队列中在输出多于图的最大顶点数后停止。
 *   则再遍历边时，负值圈中某个顶点A，呈现M(A)+W(A-B) < M(B)的情况，可证图中存在负值
 *   圈，无法计算最短路径。
 *   无向图中的负值边本身就是一个两个顶点的负值圈，如A-B，M(A-B)=-1，则是A->B->A，
 *   A+边权值更新B，B+边权值更新A，A再更新B，循环下去，A和B的最小路径值也趋向于无穷
 *   小。此时，也会在停止计算时出现同有向图那样的判断负值圈的条件。
 *   (2)Dijkstra算法：针对有向图，且要求不存在负值边。算法运行时间低于Bellman Ford。
 *   借助S_SET集合数组和优先队列作为辅助，S_SET用于存放已确定最短路径值的顶点，优先
 *   队列则负责确定要扫描计算的点，顶点的最短路径值作为优先队列的关键值。初始将源点
 *   插入队列PQ，然后开始计算。每从PQ中DeleteMin出一个顶点，将该顶点加入S_SET集合中
 *   并对该顶点有两项处理：①扫描该顶点的所有出边，并对每条边的头顶点最短路径值和前
 *   驱点进行更新，且在队列中进行相应的降key操作 ②发现未被加入队列的头顶点(mark ==
 *   0)，则插入队列。如此循环，直到队列中不存在元素。
 *   该算法较BellmanFord算法效率高在于，该算法是沿着最小路径一路更新下去的，即更新的
 *   对象更有针对性，而Bellman算法则是漫开来无论哪一个顶点，都遍历更新一遍。且借助优
 *   先队列操作效率更高。
 *   Dijkstra算法不能存在负值边的原因，考虑A->B,A->C,B->C三条边，A->B权值5,A->C权值3,
 *   B->C权值-4，则若以A为出发点，该算法给出的最短路径是直接从A->C的3，但是实际
 *   上A->B->C的值为1，为最短路径。
 *   (3)拓扑排序求算短路径算法：针对DAG。
 *   对图进行拓扑排序后，图中所有顶点按前后顺序排列存储在辅助数组中。定位到源点后，从
 *   源点开始对源点之后的顶点依次进行处理，更新每个顶点所有出边的头顶点的最短路径值和
 *   前驱顶点。这种方法较Dijkstra算法只是换了一种遍历顶点的方向和方法，效率也更高一点。
 *   但在实际应用中也应该考虑拓扑排序消耗的时间。
 * 4.所有点对最短路径
 *   即图中任意两个顶点间的距离。简单的处理方法是重复平方法，即将每个顶点作为源点，借
 *   助单源最短路径算法进行计算。运行时间为O(N^3)。
 *   Floyd算法：
 *   1----2
 *   |\  /|
 *   | \/ |
 *   | /\ |
 *   |/  \|
 *   0----3
 *   Floyd算法是从图中任意两顶点的中间顶点角度来考虑的，即间接路径。如左图中的0-3的顶点
 *   最短路径，要么0-3直接相连的路径最短，要么要经过图中其他顶点而形成的间接的路径最短，
 *   如0-1-3，0-2-3或0-1-2-3。如间接路径比直接路径短，或一条间接路径比另一条间接路径短的
 *   话，则更新最短路径值。初始时，建立最短路径矩阵MSPV，如MSPV[0][3]表示0-3的最短路径值，
 *   该矩阵初始化为直接距离，顶点到顶点自身为0，不直接相连的顶点为无穷大。计算所有点对，
 *   则肯定要有两层循环。另外，在两点间的中间顶点k的规模从小到大也要有一层循环，这层循环
 *   使用了动态规划的技术，是这样考虑的：首先只让1作为中间顶点，遍历所有顶点对，更新最小
 *   路径值，如0-1-3，比较原MSPV[0][3]与MSPV[0][1]+MSPV[1][3]进行更新；然后再让2作为中间
 *   顶点，遍历所有顶点对，更新最小路径值，如0-2-3，比较原MSPV[0][3]与MSPV[0][2]+MSPV[2][3]
 *   进行更新。如此循环完所有可以做中间顶点，完成所有顶点对的更新，计算完毕。这里有一个问
 *   题，如对0-3来说，若是1和2都作为的中间顶点，即0-1-2-3，上述方法有涉及这一点么？这点就
 *   是动态规划的作用，即按顺序将规模较大的问题所依赖的可以用同样方式求解的规模较小的问题
 *   解出并将结果记录，然后根据规模较小问题的结果再计算规模较的大问题，最终环环相扣，将最
 *   终的完整的问题求解。k的规模从小到大，即中间顶点集合规模从小到大。当k=1时，已经计算出
 *   所有点对以1为中间顶点的最小路径值，自然也包括0-2这条边，即0-2的最短路径值是否需要经
 *   过1已经在k=1循环中计算出结果，当k=2时计算0-3这条边的最短路径值，比较MSPV[0][2]+MSPV[2][3]
 *   和MSPV[0][3]时其中的MSPV[0][2]已经是k=1时计算出来的结果，MSPV[0][2]的值已经决定了是
 *   否包含1作为中间顶点，不需要k=2这一轮再费心。以此类推，可以扩展到0-3的中间顶点经过多
 *   个顶点时和所有点对，也因此单独对每一个中间顶点进行所有点对最短路径值计算，可以得出
 *   正确结果。
 *   在记录所有点对的最短路径前驱顶点时，i-k-j的前驱顶点=k-j的前驱顶点，也是动态规划技术的
 *   体现。可能k-j不是直接路径，存在其他中间顶点，因而i-k-j的结果依赖之前的循环中已经被计
 *   算出k-j的前驱结果。
 *   对负值环的检测：在计算完毕后，可重新遍历所有点对ij，其前驱点为forerunner，若存在负值
 *   环，则会出现MSPV[i][forerunner]+MSPV[forerunner][j] < MSPV[i][j];
 *
 *
 *                                                           2016年12月8日
 */

//#define _DEBUG_CLOSE_
#include "../PublicForAlgorithms.h"

#define MAX_ARC_NAME_LEN 60
#define MAX_VERTEX_NAME_LEN 60
#define MAX_VERTEX_NUM 100
#define MAX_POWER_LIMIT 100
#define MAX_QUEUE_LEN 10
#define MAX_PQ_ELEMENT_NUM MAX_VERTEX_NUM
#define MAX_PQ_LEN (MAX_VERTEX_NUM + 1)
/*顶点数据最短路径值初始化值，要大于图的最大路径值，代表无穷大*/
#define MAX_MORE_PATH_LEN 1000000
/*顶点数据路径值哨兵，要小于图中最小的路径值(源点路径值0)，代表无穷小*/
#define MIN_MORE_PATH_LEN  (-1000000)

typedef int Power;
typedef int V_Position;
typedef int G_Type;

//边信息
typedef struct
{
    char name[MAX_ARC_NAME_LEN];
    Power power;
}ArcInfo,*P_ArcInfo;

P_ArcInfo CreateOneArcInfo(char *n,Power p)
{
    P_ArcInfo new_info = (P_ArcInfo)malloc(sizeof(ArcInfo));
    if(new_info == NULL){ LINE_DEBUG("malloc ArcInfo failed"); return NULL; }
    strncpy(new_info->name,n,MAX_ARC_NAME_LEN);
    new_info->power = p;
    return new_info;
}

//边
typedef struct Edge
{
    Status mark;
    V_Position v_tail;
    V_Position v_head;
    struct Edge *arc_tail;
    struct Edge *arc_head;
    P_ArcInfo info;
}ArcNode,*P_ArcNode;

P_ArcNode CreateOneArcNode(P_ArcInfo info)
{
    P_ArcNode new_arc = (P_ArcNode)malloc(sizeof(ArcNode));
    if(new_arc == NULL){ LINE_DEBUG("malloc ArcNode failed"); return NULL; }
    new_arc->mark = 0;
    new_arc->v_tail = -1; new_arc->v_head = -1;
    new_arc->arc_tail = NULL; new_arc->arc_head = NULL;
    new_arc->info = info;
    return new_arc;
}

//顶点数据
typedef struct
{
    int id;
    char name[MAX_VERTEX_NAME_LEN];
    V_Position forerunner;/*最短路径的前驱顶点，此字段结构只适用于单源最短路径*/
    int min_len;/*从出发点到该顶点的最短路径值，此字段结构只适用于单源最短路径*/
}VertexData,*P_VertexData;

P_VertexData CreateOneVertexData(int id,char *name)
{
    P_VertexData new_data = (P_VertexData)malloc(sizeof(VertexData));
    if(new_data == NULL){ LINE_DEBUG("malloc VertexData failed"); return NULL; }
    new_data->id = id;
    strncpy(new_data->name,name,MAX_VERTEX_NAME_LEN);
    new_data->forerunner = -1;
    new_data->min_len = MAX_MORE_PATH_LEN;/*初始化最小路径值为无穷大*/
    return new_data;
}

//顶点
typedef struct
{
    Status mark;
    P_ArcNode arc_first_out;
    P_ArcNode arc_first_in;
    P_VertexData data;
}VertexNode,*P_VertexNode;

P_VertexNode CreateOneVertexNode(P_VertexData data)
{
    P_VertexNode new_v = (P_VertexNode)malloc(sizeof(VertexNode));
    if(new_v == NULL){ LINE_DEBUG("malloc VertexNode failed"); return NULL; }
    new_v->mark = 0;
    new_v->arc_first_out = NULL; new_v->arc_first_in = NULL;
    new_v->data = data;
    return new_v;
}

//图
typedef struct
{
    G_Type g_type;
    P_VertexNode v_list[MAX_VERTEX_NUM];
    int v_num; int arc_num;
}Graphics,*P_Graphics;

//表结点
typedef struct Node
{
    P_ArcNode arc;
    V_Position vertex;
    struct Node *next;
}FormNode,*P_FormNode;

P_FormNode CreateOneFormNode(P_ArcNode arc,V_Position v)
{
    P_FormNode new_node = (P_FormNode)malloc(sizeof(FormNode));
    if(new_node == NULL){ LINE_DEBUG("malloc FormNode failed"); return NULL; }
    new_node->arc = arc;
    new_node->vertex = v;
    new_node->next = NULL;
    return new_node;
}

//栈
typedef struct
{
    P_FormNode head;
    int node_num;
}Stack,*P_Stack;

P_Stack CreateOneStack()
{
    P_Stack new_stack = (P_Stack)malloc(sizeof(Stack));
    if(new_stack == NULL){ LINE_DEBUG("malloc Stack failed"); return NULL; }
    new_stack->head = NULL;
    new_stack->node_num = 0;
    return new_stack;
}

void StackInsert(P_Stack stack,P_FormNode node)
{
    if(stack == NULL || node == NULL)
    { LINE_DEBUG("StackInsert arguments illegal"); return; }
    node->next = stack->head;
    stack->head = node;
    ++(stack->node_num);
}

void StackFree(P_Stack);

/*队列，用于bellman算法*/
typedef struct
{
    V_Position queue[MAX_QUEUE_LEN];
    int r_p; int w_p;
    int count;
}Queue,*P_Queue;

P_Queue CreateOneQueue()
{
    P_Queue new_queue = (P_Queue)malloc(sizeof(Queue));
    if(new_queue == NULL){ LINE_DEBUG("CreateOneQueue malloc is failed"); return NULL; }
    int i = 0; while(i < MAX_QUEUE_LEN){ new_queue->queue[i] = 0; ++i; }
    new_queue->r_p = 0; new_queue->w_p = 0;
    new_queue->count = 0;
    return new_queue;
}

bool Pop(P_Queue Q,V_Position *p)
{
    if(Q == NULL || Q->count == 0){ LINE_DEBUG("Pop Q is NULL"); return false; }
    *p = Q->queue[Q->r_p];
    ++(Q->r_p); if(Q->r_p == MAX_QUEUE_LEN){ Q->r_p = 0; }
    --(Q->count);
    return true;
}

bool Push(P_Queue Q,V_Position p)
{
    if(Q == NULL){ LINE_DEBUG("Push Q is NULL"); return false; }
    if(Q->count == MAX_QUEUE_LEN){ LINE_DEBUG("Push Q is FULL"); return false; }
    if(p < 0 || p >= MAX_VERTEX_NUM){ LINE_DEBUG("Push p is illegal"); return false; }
    Q->queue[Q->w_p] = p;
    ++(Q->w_p); if(Q->w_p == MAX_QUEUE_LEN){ Q->w_p = 0; }
    ++(Q->count);
    return true;
}

bool QueueClean(P_Queue Q)
{
    if(Q == NULL){ LINE_DEBUG("QueueClean Q is NULL"); return false; }
    int i = 0;
    while(i < MAX_QUEUE_LEN){ Q->queue[i] = 0; ++i; }
    Q->r_p = 0; Q->w_p = 0;
    Q->count = 0;
    return true;
}

/*优先队列，用于Dijkstra算法
 *关键字是图顶点的最短路径值min_len字段*/
typedef struct
{
    int e_num;
    P_VertexNode queue[MAX_PQ_LEN];

}PQ,*P_PQ;

P_PQ CreateOnePQ()
{
    P_PQ new_pq = NULL;
    P_VertexData data = NULL;
    P_VertexNode V = NULL;

    new_pq = (P_PQ)malloc(sizeof(PQ));
    if(new_pq == NULL)
    { LINE_DEBUG("CreateOnePQ malloc PQ failed"); goto Label_CreateOnePQ_Clean; }
    new_pq->e_num = 0;
    int i = 0;
    while(i < MAX_PQ_LEN){ new_pq->queue[i] = NULL; ++i; }
    /*设置哨兵，且要单独释放*/
    data = CreateOneVertexData(-1,"Sentry");
    if(data == NULL)
    { LINE_DEBUG("CreateOnePQ malloc VertexData failed"); goto Label_CreateOnePQ_Clean; }
    data->min_len = MIN_MORE_PATH_LEN;/*设置哨兵在堆中的关键值*/
    V = CreateOneVertexNode(data);
    if(V == NULL)
    { LINE_DEBUG("CreateOnePQ malloc Vertex failed"); goto Label_CreateOnePQ_Clean; }
    new_pq->queue[0] = V;

    return new_pq;

Label_CreateOnePQ_Clean:
    SAFE_FREE(new_pq); SAFE_FREE(data); SAFE_FREE(V);
    return NULL;
}

/*利用顶点的mark字段标记顶点在堆中的位置，方便降key操作*/
bool PQ_Insert(P_PQ PQ,P_VertexNode V)
{
    if(PQ == NULL){ LINE_DEBUG("PQ_Insert PQ is NULL"); return false; }
    if(V == NULL){ LINE_DEBUG("PQ_Insert V is NULL"); return false; }
    if(PQ->e_num == MAX_PQ_ELEMENT_NUM){ LINE_DEBUG("PQ_Insert PQ is FULL"); return false; }
    int blank = PQ->e_num + 1;
    int parent;
    /*上滤操作*/
    while(blank > 0)
    {
	parent = blank>>1;
	if(V->data->min_len >= PQ->queue[parent]->data->min_len)
	{
	    PQ->queue[blank] = V;
	    PQ->queue[blank]->mark = blank;
	    ++(PQ->e_num);
	    V->mark = blank;/*标记所处位置*/
	    break;
	}
	PQ->queue[blank] = PQ->queue[parent];
	PQ->queue[blank]->mark = blank;
	blank = parent;
    }
    return true;
}

P_VertexNode PQ_DeleteMin(P_PQ PQ)
{
    if(PQ == NULL || PQ->e_num == 0){ LINE_DEBUG("PQ_DeleteMin PQ is NULL"); return NULL; }
    P_VertexNode min_vertex = PQ->queue[1];
    int blank = 1;
    int lchild = blank*2; int rchild = lchild + 1;
    int last_key = PQ->queue[PQ->e_num]->data->min_len;
    /*下滤操作，当lchild=PQ->e_num时，说明最后一个元素是左子节点，这时可以直接停掉
     *循环此时blank停留在last_key元素的父节点*/
    while((blank*2) < PQ->e_num)
    {
	lchild = blank*2; rchild = lchild + 1;
	if(last_key <= PQ->queue[lchild]->data->min_len
	&& last_key <= PQ->queue[rchild]->data->min_len)
	{ break; }
	if(PQ->queue[lchild]->data->min_len < PQ->queue[rchild]->data->min_len)
	{
	    PQ->queue[blank] = PQ->queue[lchild];
	    blank = lchild;
	}
	else
	{
	    PQ->queue[blank] = PQ->queue[rchild];
	    blank = rchild;
	}
	/*位置改变，进行标记*/
	PQ->queue[blank]->mark = blank;
    }
    PQ->queue[blank] = PQ->queue[PQ->e_num];
    PQ->queue[blank]->mark = blank;
    PQ->queue[PQ->e_num] = NULL;
    --(PQ->e_num);

    return min_vertex;
}

/*把队列PQ的p位置的元素的最小路径值降为len*/
bool PQ_DecreaseKey(P_PQ PQ,int p,int len)
{
    if(PQ == NULL){ LINE_DEBUG("PQ_DecreaseKey PQ is NULL"); return false; }
    if(p <= 0 || p >= MAX_PQ_LEN){ LINE_DEBUG("PQ_DecreaseKey p is illegal"); return false; }
    if(len >= PQ->queue[p]->data->min_len)
    { LINE_DEBUG("PQ_DecreaseKey len is not valid"); return false; }
    
    P_VertexNode decrease_v = PQ->queue[p];
    decrease_v->data->min_len = len;
    int blank = p;
    int parent;
    /*上滤操作*/
    while(blank > 0)
    {
	parent = blank>>1;
	if(len >= PQ->queue[parent]->data->min_len)
	{
	    PQ->queue[blank] = decrease_v;
	    PQ->queue[blank]->mark = blank;
	    break;
	}
	PQ->queue[blank] = PQ->queue[parent];
	PQ->queue[blank]->mark = blank;
	blank = parent;
    }

    return true;
}

void PQ_Free(P_PQ PQ)
{
    /*除哨兵外，队列中的顶点由图的Free函数释放*/
    if(PQ == NULL){ LINE_DEBUG("PQ_Free PQ is NULL"); return; }
    SAFE_FREE(PQ->queue[0]->data);
    SAFE_FREE(PQ->queue[0]);
    SAFE_FREE(PQ);
}

/*
 *
 *     0-----5         权值
 *     |\   /|         0-5 100  0-2 10  0-4 30  1-2 5
 *     | \ / |         2-3 50   3-4 20  4-5 60  3-5 10
 *  1  |  4  |
 *   \ |   \ |
 *    \|    \|
 *     2-----3
 *
 */
P_Graphics CreateOneUndigraph()
{
    //声明
    P_ArcInfo info0_2 = NULL; P_ArcInfo info0_4 = NULL; P_ArcInfo info0_5 = NULL; P_ArcInfo info1_2 = NULL;
    P_ArcInfo info2_3 = NULL; P_ArcInfo info3_4 = NULL; P_ArcInfo info3_5 = NULL; P_ArcInfo info4_5 = NULL;
    P_ArcNode Arc0_2 = NULL; P_ArcNode Arc0_4 = NULL; P_ArcNode Arc0_5 = NULL; P_ArcNode Arc1_2 = NULL;
    P_ArcNode Arc2_3 = NULL; P_ArcNode Arc3_4 = NULL; P_ArcNode Arc3_5 = NULL; P_ArcNode Arc4_5 = NULL;
    P_VertexData data0 = NULL; P_VertexData data1 = NULL; P_VertexData data2 = NULL;
    P_VertexData data3 = NULL; P_VertexData data4 = NULL; P_VertexData data5 = NULL;
    P_VertexNode V0 = NULL; P_VertexNode V1 = NULL; P_VertexNode V2 = NULL;
    P_VertexNode V3 = NULL; P_VertexNode V4 = NULL; P_VertexNode V5 = NULL;
    P_Graphics undigraph = NULL;
    //边信息
    info0_2 = CreateOneArcInfo("V0-V2",10); info0_4 = CreateOneArcInfo("V0-V4",30); info0_5 = CreateOneArcInfo("V0-V5",100);
    info1_2 = CreateOneArcInfo("V1-V2",5);  info2_3 = CreateOneArcInfo("V2-V3",50); info3_4 = CreateOneArcInfo("V3-V4",20);
    info3_5 = CreateOneArcInfo("V3-V5",10); info4_5 = CreateOneArcInfo("V4-V5",60);
    if(info0_2 == NULL || info0_4 == NULL || info0_5 == NULL || info1_2 == NULL
    || info2_3 == NULL || info3_4 == NULL || info3_5 == NULL || info4_5 == NULL)
    { LINE_DEBUG("Create ArcInfo failed"); goto Label_CreateOneUndigraph_Clean; }
    //边
    Arc0_2 = CreateOneArcNode(info0_2); Arc0_4 = CreateOneArcNode(info0_4); Arc0_5 = CreateOneArcNode(info0_5);
    Arc1_2 = CreateOneArcNode(info1_2); Arc2_3 = CreateOneArcNode(info2_3); Arc3_4 = CreateOneArcNode(info3_4);
    Arc3_5 = CreateOneArcNode(info3_5); Arc4_5 = CreateOneArcNode(info4_5);
    if(Arc0_2 == NULL || Arc0_4 == NULL || Arc0_5 == NULL || Arc1_2 == NULL
    || Arc2_3 == NULL || Arc3_4 == NULL || Arc3_5 == NULL || Arc4_5 == NULL)
    { LINE_DEBUG("Create Arc failed"); goto Label_CreateOneUndigraph_Clean; }
    //点数据
    data0 = CreateOneVertexData(0,"V0"); data1 = CreateOneVertexData(1,"V1"); data2 = CreateOneVertexData(2,"V2");
    data3 = CreateOneVertexData(3,"V3"); data4 = CreateOneVertexData(4,"V4"); data5 = CreateOneVertexData(5,"V5");
    V0 = CreateOneVertexNode(data0); V1 = CreateOneVertexNode(data1); V2 = CreateOneVertexNode(data2);
    V3 = CreateOneVertexNode(data3); V4 = CreateOneVertexNode(data4); V5 = CreateOneVertexNode(data5);
    if(data0 == NULL || data1 == NULL || data2 == NULL || data3 == NULL || data4 == NULL || data5 == NULL
    || V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL || V4 == NULL || V5 == NULL)
    { LINE_DEBUG("Create Vertex(data) failed"); goto Label_CreateOneUndigraph_Clean; }
    //图
    undigraph = (P_Graphics)malloc(sizeof(Graphics));
    if(undigraph == NULL){ LINE_DEBUG("Create Graphics failed"); goto Label_CreateOneUndigraph_Clean; }

    //关系组织
    Arc0_2->v_tail = 0; Arc0_2->v_head = 2; Arc0_2->arc_tail = Arc0_4; Arc0_2->arc_head = Arc1_2;
    Arc0_4->v_tail = 0; Arc0_4->v_head = 4; Arc0_4->arc_tail = Arc0_5; Arc0_4->arc_head = Arc3_4;
    Arc0_5->v_tail = 0; Arc0_5->v_head = 5; Arc0_5->arc_tail = NULL;   Arc0_5->arc_head = Arc3_5;
    Arc1_2->v_tail = 1; Arc1_2->v_head = 2; Arc1_2->arc_tail = NULL;   Arc1_2->arc_head = Arc2_3;
    Arc2_3->v_tail = 2; Arc2_3->v_head = 3; Arc2_3->arc_tail = NULL;   Arc2_3->arc_head = Arc3_4;
    Arc3_4->v_tail = 3; Arc3_4->v_head = 4; Arc3_4->arc_tail = Arc3_5; Arc3_4->arc_head = Arc4_5;
    Arc3_5->v_tail = 3; Arc3_5->v_head = 5; Arc3_5->arc_tail = NULL;   Arc3_5->arc_head = Arc4_5;
    Arc4_5->v_tail = 4; Arc4_5->v_head = 5; Arc4_5->arc_tail = NULL;   Arc4_5->arc_head = NULL;
    V0->arc_first_out = Arc0_2; V1->arc_first_out = Arc1_2; V2->arc_first_out = Arc0_2;
    V3->arc_first_out = Arc2_3; V4->arc_first_out = Arc0_4; V5->arc_first_out = Arc0_5;
    undigraph->v_num = 6; undigraph->arc_num = 8; undigraph->g_type = (UNDIGRAPH | WEIGHTYES | CYCLIC | CONNECTED);
    undigraph->v_list[0] = V0; undigraph->v_list[1] = V1; undigraph->v_list[2] = V2;
    undigraph->v_list[3] = V3; undigraph->v_list[4] = V4; undigraph->v_list[5] = V5;
    
    return undigraph;

Label_CreateOneUndigraph_Clean:
    SAFE_FREE(info0_2); SAFE_FREE(info0_4); SAFE_FREE(info0_5); SAFE_FREE(info1_2);
    SAFE_FREE(info2_3); SAFE_FREE(info3_4); SAFE_FREE(info3_5); SAFE_FREE(info4_5);
    SAFE_FREE(Arc0_2); SAFE_FREE(Arc0_4); SAFE_FREE(Arc0_5); SAFE_FREE(Arc1_2);
    SAFE_FREE(Arc2_3); SAFE_FREE(Arc3_4); SAFE_FREE(Arc3_5); SAFE_FREE(Arc4_5);
    SAFE_FREE(data0); SAFE_FREE(data1); SAFE_FREE(data2); SAFE_FREE(data3); SAFE_FREE(data4); SAFE_FREE(data5);
    SAFE_FREE(V0); SAFE_FREE(V1); SAFE_FREE(V2); SAFE_FREE(V3); SAFE_FREE(V4); SAFE_FREE(V5);
    SAFE_FREE(undigraph);

    return NULL;
}

/*
 *
 *     0-----5         权值
 *     |\   /|         0->5 100  0->2 10  0->4 30  1->2 5
 *     | \ / |         2->3 50   4->3 20  4->5 60  3->5 10
 *  1  |  4  |
 *   \ |   \ |
 *    \|    \|
 *     2-----3
 *
 */
P_Graphics CreateOneDigraph()
{
    //声明
    P_ArcInfo info0_2 = NULL; P_ArcInfo info0_4 = NULL; P_ArcInfo info0_5 = NULL; P_ArcInfo info1_2 = NULL;
    P_ArcInfo info2_3 = NULL; P_ArcInfo info4_3 = NULL; P_ArcInfo info3_5 = NULL; P_ArcInfo info4_5 = NULL;
    P_ArcNode Arc0_2 = NULL; P_ArcNode Arc0_4 = NULL; P_ArcNode Arc0_5 = NULL; P_ArcNode Arc1_2 = NULL;
    P_ArcNode Arc2_3 = NULL; P_ArcNode Arc4_3 = NULL; P_ArcNode Arc3_5 = NULL; P_ArcNode Arc4_5 = NULL;
    P_VertexData data0 = NULL; P_VertexData data1 = NULL; P_VertexData data2 = NULL;
    P_VertexData data3 = NULL; P_VertexData data4 = NULL; P_VertexData data5 = NULL;
    P_VertexNode V0 = NULL; P_VertexNode V1 = NULL; P_VertexNode V2 = NULL;
    P_VertexNode V3 = NULL; P_VertexNode V4 = NULL; P_VertexNode V5 = NULL;
    P_Graphics digraph = NULL;
    //边信息
    info0_2 = CreateOneArcInfo("V0->V2",10); info0_4 = CreateOneArcInfo("V0->V4",30); info0_5 = CreateOneArcInfo("V0->V5",100);
    info1_2 = CreateOneArcInfo("V1->V2",5);  info2_3 = CreateOneArcInfo("V2->V3",50); info4_3 = CreateOneArcInfo("V4->V3",20);
    info3_5 = CreateOneArcInfo("V3->V5",10); info4_5 = CreateOneArcInfo("V4->V5",60);
    if(info0_2 == NULL || info0_4 == NULL || info0_5 == NULL || info1_2 == NULL
    || info2_3 == NULL || info4_3 == NULL || info3_5 == NULL || info4_5 == NULL)
    { LINE_DEBUG("Create ArcInfo failed"); goto Label_CreateOneDigraph_Clean; }
    //边
    Arc0_2 = CreateOneArcNode(info0_2); Arc0_4 = CreateOneArcNode(info0_4); Arc0_5 = CreateOneArcNode(info0_5);
    Arc1_2 = CreateOneArcNode(info1_2); Arc2_3 = CreateOneArcNode(info2_3); Arc4_3 = CreateOneArcNode(info4_3);
    Arc3_5 = CreateOneArcNode(info3_5); Arc4_5 = CreateOneArcNode(info4_5);
    if(Arc0_2 == NULL || Arc0_4 == NULL || Arc0_5 == NULL || Arc1_2 == NULL
    || Arc2_3 == NULL || Arc4_3 == NULL || Arc3_5 == NULL || Arc4_5 == NULL)
    { LINE_DEBUG("Create Arc failed"); goto Label_CreateOneDigraph_Clean; }
    //点数据
    data0 = CreateOneVertexData(0,"V0"); data1 = CreateOneVertexData(1,"V1"); data2 = CreateOneVertexData(2,"V2");
    data3 = CreateOneVertexData(3,"V3"); data4 = CreateOneVertexData(4,"V4"); data5 = CreateOneVertexData(5,"V5");
    V0 = CreateOneVertexNode(data0); V1 = CreateOneVertexNode(data1); V2 = CreateOneVertexNode(data2);
    V3 = CreateOneVertexNode(data3); V4 = CreateOneVertexNode(data4); V5 = CreateOneVertexNode(data5);
    if(data0 == NULL || data1 == NULL || data2 == NULL || data3 == NULL || data4 == NULL || data5 == NULL
    || V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL || V4 == NULL || V5 == NULL)
    { LINE_DEBUG("Create Vertex(data) failed"); goto Label_CreateOneDigraph_Clean; }
    //图
    digraph = (P_Graphics)malloc(sizeof(Graphics));
    if(digraph == NULL){ LINE_DEBUG("Create Graphics failed"); goto Label_CreateOneDigraph_Clean; }

    //关系组织
    Arc0_2->v_tail = 0; Arc0_2->v_head = 2; Arc0_2->arc_tail = Arc0_4; Arc0_2->arc_head = Arc1_2;
    Arc0_4->v_tail = 0; Arc0_4->v_head = 4; Arc0_4->arc_tail = Arc0_5; Arc0_4->arc_head = NULL;
    Arc0_5->v_tail = 0; Arc0_5->v_head = 5; Arc0_5->arc_tail = NULL;   Arc0_5->arc_head = Arc3_5;
    Arc1_2->v_tail = 1; Arc1_2->v_head = 2; Arc1_2->arc_tail = NULL;   Arc1_2->arc_head = NULL;
    Arc2_3->v_tail = 2; Arc2_3->v_head = 3; Arc2_3->arc_tail = NULL;   Arc2_3->arc_head = Arc4_3;
    Arc4_3->v_tail = 4; Arc4_3->v_head = 3; Arc4_3->arc_tail = Arc4_5; Arc4_3->arc_head = NULL;
    Arc3_5->v_tail = 3; Arc3_5->v_head = 5; Arc3_5->arc_tail = NULL;   Arc3_5->arc_head = Arc4_5;
    Arc4_5->v_tail = 4; Arc4_5->v_head = 5; Arc4_5->arc_tail = NULL;   Arc4_5->arc_head = NULL;
    V0->arc_first_out = Arc0_2; V1->arc_first_out = Arc1_2; V2->arc_first_out = Arc2_3;
    V3->arc_first_out = Arc3_5; V4->arc_first_out = Arc4_3; V5->arc_first_out = NULL;
    V0->arc_first_in = NULL;   V1->arc_first_in = NULL;   V2->arc_first_in = Arc0_2;
    V3->arc_first_in = Arc2_3; V4->arc_first_in = Arc0_4; V5->arc_first_in = Arc0_5;
    digraph->v_num = 6; digraph->arc_num = 8; digraph->g_type = (DIGRAPH | WEIGHTYES | ACYCLIC | CONNECTED);
    digraph->v_list[0] = V0; digraph->v_list[1] = V1; digraph->v_list[2] = V2;
    digraph->v_list[3] = V3; digraph->v_list[4] = V4; digraph->v_list[5] = V5;
    
    return digraph;

Label_CreateOneDigraph_Clean:
    SAFE_FREE(info0_2); SAFE_FREE(info0_4); SAFE_FREE(info0_5); SAFE_FREE(info1_2);
    SAFE_FREE(info2_3); SAFE_FREE(info4_3); SAFE_FREE(info3_5); SAFE_FREE(info4_5);
    SAFE_FREE(Arc0_2); SAFE_FREE(Arc0_4); SAFE_FREE(Arc0_5); SAFE_FREE(Arc1_2);
    SAFE_FREE(Arc2_3); SAFE_FREE(Arc4_3); SAFE_FREE(Arc3_5); SAFE_FREE(Arc4_5);
    SAFE_FREE(data0); SAFE_FREE(data1); SAFE_FREE(data2); SAFE_FREE(data3); SAFE_FREE(data4); SAFE_FREE(data5);
    SAFE_FREE(V0); SAFE_FREE(V1); SAFE_FREE(V2); SAFE_FREE(V3); SAFE_FREE(V4); SAFE_FREE(V5);
    SAFE_FREE(digraph);

    return NULL;
}

//带负值环的有向图
P_Graphics CreateOneCyclicDigraph()
{
    //声明
    P_ArcInfo info0_2 = NULL; P_ArcInfo info0_4 = NULL; P_ArcInfo info0_5 = NULL; P_ArcInfo info1_2 = NULL;
    P_ArcInfo info2_3 = NULL; P_ArcInfo info4_3 = NULL; P_ArcInfo info3_5 = NULL; P_ArcInfo info5_4 = NULL;
    P_ArcNode Arc0_2 = NULL; P_ArcNode Arc0_4 = NULL; P_ArcNode Arc0_5 = NULL; P_ArcNode Arc1_2 = NULL;
    P_ArcNode Arc2_3 = NULL; P_ArcNode Arc4_3 = NULL; P_ArcNode Arc3_5 = NULL; P_ArcNode Arc5_4 = NULL;
    P_VertexData data0 = NULL; P_VertexData data1 = NULL; P_VertexData data2 = NULL;
    P_VertexData data3 = NULL; P_VertexData data4 = NULL; P_VertexData data5 = NULL;
    P_VertexNode V0 = NULL; P_VertexNode V1 = NULL; P_VertexNode V2 = NULL;
    P_VertexNode V3 = NULL; P_VertexNode V4 = NULL; P_VertexNode V5 = NULL;
    P_Graphics digraph = NULL;
    //边信息
    info0_2 = CreateOneArcInfo("V0->V2",10); info0_4 = CreateOneArcInfo("V0->V4",30); info0_5 = CreateOneArcInfo("V0->V5",100);
    info1_2 = CreateOneArcInfo("V1->V2",5);  info2_3 = CreateOneArcInfo("V2->V3",50); info4_3 = CreateOneArcInfo("V4->V3",20);
    info3_5 = CreateOneArcInfo("V3->V5",10); info5_4 = CreateOneArcInfo("V5->V4",-31);
    if(info0_2 == NULL || info0_4 == NULL || info0_5 == NULL || info1_2 == NULL
    || info2_3 == NULL || info4_3 == NULL || info3_5 == NULL || info5_4 == NULL)
    { LINE_DEBUG("Create ArcInfo failed"); goto Label_CreateOneDigraph_Clean; }
    //边
    Arc0_2 = CreateOneArcNode(info0_2); Arc0_4 = CreateOneArcNode(info0_4); Arc0_5 = CreateOneArcNode(info0_5);
    Arc1_2 = CreateOneArcNode(info1_2); Arc2_3 = CreateOneArcNode(info2_3); Arc4_3 = CreateOneArcNode(info4_3);
    Arc3_5 = CreateOneArcNode(info3_5); Arc5_4 = CreateOneArcNode(info5_4);
    if(Arc0_2 == NULL || Arc0_4 == NULL || Arc0_5 == NULL || Arc1_2 == NULL
    || Arc2_3 == NULL || Arc4_3 == NULL || Arc3_5 == NULL || Arc5_4 == NULL)
    { LINE_DEBUG("Create Arc failed"); goto Label_CreateOneDigraph_Clean; }
    //点数据
    data0 = CreateOneVertexData(0,"V0"); data1 = CreateOneVertexData(1,"V1"); data2 = CreateOneVertexData(2,"V2");
    data3 = CreateOneVertexData(3,"V3"); data4 = CreateOneVertexData(4,"V4"); data5 = CreateOneVertexData(5,"V5");
    V0 = CreateOneVertexNode(data0); V1 = CreateOneVertexNode(data1); V2 = CreateOneVertexNode(data2);
    V3 = CreateOneVertexNode(data3); V4 = CreateOneVertexNode(data4); V5 = CreateOneVertexNode(data5);
    if(data0 == NULL || data1 == NULL || data2 == NULL || data3 == NULL || data4 == NULL || data5 == NULL
    || V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL || V4 == NULL || V5 == NULL)
    { LINE_DEBUG("Create Vertex(data) failed"); goto Label_CreateOneDigraph_Clean; }
    //图
    digraph = (P_Graphics)malloc(sizeof(Graphics));
    if(digraph == NULL){ LINE_DEBUG("Create Graphics failed"); goto Label_CreateOneDigraph_Clean; }

    //关系组织
    Arc0_2->v_tail = 0; Arc0_2->v_head = 2; Arc0_2->arc_tail = Arc0_4; Arc0_2->arc_head = Arc1_2;
    Arc0_4->v_tail = 0; Arc0_4->v_head = 4; Arc0_4->arc_tail = Arc0_5; Arc0_4->arc_head = Arc5_4;
    Arc0_5->v_tail = 0; Arc0_5->v_head = 5; Arc0_5->arc_tail = NULL;   Arc0_5->arc_head = Arc3_5;
    Arc1_2->v_tail = 1; Arc1_2->v_head = 2; Arc1_2->arc_tail = NULL;   Arc1_2->arc_head = NULL;
    Arc2_3->v_tail = 2; Arc2_3->v_head = 3; Arc2_3->arc_tail = NULL;   Arc2_3->arc_head = Arc4_3;
    Arc4_3->v_tail = 4; Arc4_3->v_head = 3; Arc4_3->arc_tail = NULL;   Arc4_3->arc_head = NULL;
    Arc3_5->v_tail = 3; Arc3_5->v_head = 5; Arc3_5->arc_tail = NULL;   Arc3_5->arc_head = NULL;
    Arc5_4->v_tail = 5; Arc5_4->v_head = 4; Arc5_4->arc_tail = NULL;   Arc5_4->arc_head = NULL;
    V0->arc_first_out = Arc0_2; V1->arc_first_out = Arc1_2; V2->arc_first_out = Arc2_3;
    V3->arc_first_out = Arc3_5; V4->arc_first_out = Arc4_3; V5->arc_first_out = Arc5_4;
    V0->arc_first_in = NULL;   V1->arc_first_in = NULL;   V2->arc_first_in = Arc0_2;
    V3->arc_first_in = Arc2_3; V4->arc_first_in = Arc0_4; V5->arc_first_in = Arc0_5;
    digraph->v_num = 6; digraph->arc_num = 8; digraph->g_type = (DIGRAPH | WEIGHTYES | CYCLIC | CONNECTED);
    digraph->v_list[0] = V0; digraph->v_list[1] = V1; digraph->v_list[2] = V2;
    digraph->v_list[3] = V3; digraph->v_list[4] = V4; digraph->v_list[5] = V5;
    
    return digraph;

Label_CreateOneDigraph_Clean:
    SAFE_FREE(info0_2); SAFE_FREE(info0_4); SAFE_FREE(info0_5); SAFE_FREE(info1_2);
    SAFE_FREE(info2_3); SAFE_FREE(info4_3); SAFE_FREE(info3_5); SAFE_FREE(info5_4);
    SAFE_FREE(Arc0_2); SAFE_FREE(Arc0_4); SAFE_FREE(Arc0_5); SAFE_FREE(Arc1_2);
    SAFE_FREE(Arc2_3); SAFE_FREE(Arc4_3); SAFE_FREE(Arc3_5); SAFE_FREE(Arc5_4);
    SAFE_FREE(data0); SAFE_FREE(data1); SAFE_FREE(data2); SAFE_FREE(data3); SAFE_FREE(data4); SAFE_FREE(data5);
    SAFE_FREE(V0); SAFE_FREE(V1); SAFE_FREE(V2); SAFE_FREE(V3); SAFE_FREE(V4); SAFE_FREE(V5);
    SAFE_FREE(digraph);

    return NULL;
}

/*BellmanFord最短路径算法
 *确保图中顶点总数小于32，否则还需更多的flag变量
 *s_p 计算最短路径值的源点顶点位置*/
bool BellmanFord_MSP(P_Graphics G,V_Position s_p)
{
    if(G == NULL){ LINE_DEBUG("G is NULL"); return false; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("s_p is illegal"); return false; }
    
    /*初始化*/
    /*用一个整数的bit位来标识顶点是否加入过队列(处理过)，顶点数<=32个，每个顶点只需扫描计算
     *其邻边顶点一次*/
    int flag = 0;
    bool re = false;
    P_Queue Q = CreateOneQueue(); if(Q == NULL){ LINE_DEBUG("Queue create failed"); return false; }
    G->v_list[s_p]->data->min_len = 0;/*初始化开始顶点的最短路径值，否则之后的无法计算*/
    re = Push(Q,s_p); if(re == false){ SAFE_FREE(Q); return false; } 
    flag |= (1 << s_p);
    int count = 0;/*计数器，记录Q弹出元素的数目*/
    V_Position V;/*获取弹出的元素*/
    V_Position another_v;
    P_ArcNode arc = NULL;

    /*开始计算单源最短路径*/
    while(Q->count != 0 && count < (G->v_num + 1))
    {
	re = Pop(Q,&V); if(re == false){ SAFE_FREE(Q); return false; }
	++count;/*计数器累加*/
	arc = G->v_list[V]->arc_first_out;
	/*计算所有邻接顶点的最短路径值*/
	while(arc)
	{
	    another_v = (V == arc->v_tail) ? arc->v_head : arc->v_tail;
	    /*更新最小路径值，不用担心A-B边B又回访A顶点，如果A-B为负，则A还是会比B小*/
	    if((G->v_list[V]->data->min_len + arc->info->power) < G->v_list[another_v]->data->min_len)
	    {
		//更新最短路径值
		G->v_list[another_v]->data->min_len = G->v_list[V]->data->min_len + arc->info->power;
		//更新前驱顶点
		G->v_list[another_v]->data->forerunner = V;
	    }
	    //如果another没有加入过队列
	    if(!(flag & (1 << another_v)))
	    {
		re = Push(Q,another_v);
		if(re == false){ SAFE_FREE(Q); return false; }
		flag |= (1 << another_v);/*标识已加入过队列*/
	    }

	    arc = (V == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	}
    }
    /*再次遍历所有边，看图中是否存在负值圈*/
    for(count = 0; count < G->v_num; ++count)
    {
	arc = G->v_list[count]->arc_first_out;
	while(arc)
	{
	    /*只要环中存在负值边，肯定会造成某一边的 A点最小路径值 + 边权值 < B最小路径值*/
	    another_v = (count == arc->v_tail) ? arc->v_head : arc->v_tail;
	    if(G->v_list[count]->data->min_len + arc->info->power < G->v_list[another_v]->data->min_len)
	    { printf("图中存在权值为负的边的圈，Bellman算法无法计算最短路径\n"); SAFE_FREE(Q); return false; }

	    arc = (count == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	}
    }
    /*释放队列*/
    SAFE_FREE(Q);
    return true;
}

/* Dijkstra最短路径算法，针对有向图且无负值边。
 * 辅助数组：S_SET S集合，用于存放已找到最短路径的顶点
 * 根据算法，源点不同，S_SET不一定放入所有图的顶点*/
P_VertexNode S_SET[MAX_VERTEX_NUM];

bool Dijkstra_MSP(P_Graphics G,V_Position s_p)
{
    if(G == NULL){ LINE_DEBUG("Dijkstra_MSP G is NULL"); return false; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("Dijkstra_MSP s_p is illegal"); return false; }
    int i = 0; P_VertexNode deal_v;
    for(i = 0; i < G->v_num; ++i){ S_SET[i] = NULL; }
    P_ArcNode arc = NULL;
    bool re = false;
    P_PQ PQ = CreateOnePQ();
    if(PQ == NULL){ LINE_DEBUG("Dijkstra_MSP PQ create failed"); return false; }
    /*初始化源点，并将源点压入优先队列S_SET中，i为当前处理的顶点*/
    G->v_list[s_p]->data->forerunner = -1; G->v_list[s_p]->data->min_len = 0;
    re = PQ_Insert(PQ,G->v_list[s_p]);
    if(re == false){ LINE_DEBUG("Dijkstra_MSP PQ_Insert failed"); PQ_Free(PQ); return false; }
    
    /*利用优先队列开始处理*/
    int r_p = 0;/*S_SET写位置*/
    while(PQ->e_num != 0)
    {
	deal_v = PQ_DeleteMin(PQ);
	if(deal_v == NULL){ LINE_DEBUG("Dijkstra_MSP PQ_Insert failed"); PQ_Free(PQ); return false; }
	S_SET[r_p] = deal_v; ++(r_p);/*确定最短路径值的顶点*/
	arc = deal_v->arc_first_out;
	while(arc)
	{
	    /*如果头顶点不存在队列中，则肯定未计算过，则直接更新最小路径值和前驱顶点并加入队列*/
	    if(G->v_list[arc->v_head]->mark == 0)
	    {
		G->v_list[arc->v_head]->data->min_len = deal_v->data->min_len + arc->info->power;
		G->v_list[arc->v_head]->data->forerunner = arc->v_tail;
		re = PQ_Insert(PQ,G->v_list[arc->v_head]);/*Insert操作会置mark的值*/
		if(re == false){ LINE_DEBUG("Dijkstra_MSP PQ_Insert failed"); PQ_Free(PQ); return false; }
	    }
	    /*如果头顶点在队列中，则查看是否可以进行松弛操作，若可以，在队列中进行降key操作*/
	    else
	    {
		if(deal_v->data->min_len + arc->info->power < G->v_list[arc->v_head]->data->min_len)
		{
		    re = PQ_DecreaseKey(PQ,G->v_list[arc->v_head]->mark,deal_v->data->min_len+arc->info->power);
		    if(re == false){ LINE_DEBUG("Dijkstra_MSP PQ_DecreaseKey failed"); PQ_Free(PQ); return false; }
		    G->v_list[arc->v_head]->data->forerunner = arc->v_tail;/*DecreaseKey操作不更新前驱点*/
		}
	    }
	    arc = arc->arc_tail;
	}
    }
    
    /*释放队列*/
    PQ_Free(PQ);
    
    return true;
}

/*辅助数组，V_FLAG记录顶点是否访问过*/
bool V_FLAG[MAX_VERTEX_NUM];

/*利用深度优先遍历进行拓扑排序*/
void DFS(P_Graphics G,V_Position s_p,P_Stack stack)
{
    V_FLAG[s_p] = true;
    P_ArcNode arc = G->v_list[s_p]->arc_first_out;
    while(arc)
    {
	if(V_FLAG[arc->v_head] != true)
	{
	    DFS(G,arc->v_head,stack);
	    P_FormNode node = CreateOneFormNode(NULL,arc->v_head);
	    StackInsert(stack,node);
	}
	arc = arc->arc_tail;
    }
}

/*拓扑排序求最短路径*/
bool TopologicalSort_MSP(P_Graphics G,V_Position s_p)
{
    if(G == NULL){ LINE_DEBUG("TopologicalSort_MSP G is NULL"); return false; }
    if(s_p < 0 || s_p >= G->v_num)
    { LINE_DEBUG("TopologicalSort_MSP s_p is not valid"); return false; }
    int i = 0;
    while(i < G->v_num){ V_FLAG[i] = false; ++i; }
    /*拓扑排序*/
    P_Stack stack = CreateOneStack();
    if(stack == NULL){ LINE_DEBUG("TopologicalSort_MSP stack create failed"); return false; }
    i = s_p;
    while(i < G->v_num)
    {
	if(V_FLAG[i] != true)
	{
	    DFS(G,i,stack);
	    P_FormNode node = CreateOneFormNode(NULL,i);
	    StackInsert(stack,node);
	}
	++i;
    }
    i = 0;
    while(i < s_p)
    {
	if(V_FLAG[i] != true)
	{
	    DFS(G,i,stack);
	    P_FormNode node = CreateOneFormNode(NULL,i);
	    StackInsert(stack,node);
	}
	++i;
    }

    /*计算最短路径*/
    /*初始化源点*/
    G->v_list[s_p]->data->forerunner = -1;
    G->v_list[s_p]->data->min_len = 0;
    P_FormNode temp = stack->head;
    P_ArcNode arc = NULL;
    /*栈中定位到源点*/
    while(temp)
    {
	if(temp->vertex == s_p){ break; }
	temp = temp->next;
    }
    /*顺序遍历各个顶点进行计算*/
    while(temp)
    {
	arc = G->v_list[temp->vertex]->arc_first_out;
	while(arc)
	{
	    if((G->v_list[arc->v_tail]->data->min_len + arc->info->power)
	    <   G->v_list[arc->v_head]->data->min_len)
	    {
		G->v_list[arc->v_head]->data->min_len 
		    = G->v_list[arc->v_tail]->data->min_len + arc->info->power;
		G->v_list[arc->v_head]->data->forerunner = arc->v_tail;
	    }
	    arc = arc->arc_tail;
	}
	temp = temp->next;
    }

    StackFree(stack);
}

void OneSource_ShowMSP(P_Graphics G,V_Position s_p,V_Position e_p)
{
    if(G == NULL){ LINE_DEBUG("ShowMinShortPath G is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num || e_p < 0 || e_p >= G->v_num)
    { LINE_DEBUG("ShowMinShortPath s_p or e_p is illegal"); return; }
    /*有向图的最短路径算法中，部分顶点可能不会纳入到S_SET集合中，即不会被遍历计算
     *到，也即这些算法从某一源点出发，不存在路径到达这些不在S_SET中的顶点*/
    if(G->v_list[e_p]->data->forerunner == -1)
    { LINE_DEBUG("There is not a way from Vertex %d to the Vertex %d",s_p,e_p); return; }
    printf("最短路径总长：%d\n",G->v_list[e_p]->data->min_len);
    P_Stack stack = CreateOneStack();
    P_ArcNode arc = NULL;
    V_Position another_v;
    //由终点向出发点依次将边压入栈中
    if(G->g_type & UNDIGRAPH)
    {
	while(e_p != s_p)
	{
	    arc = G->v_list[e_p]->arc_first_out;
	    while(arc)
	    {
		another_v = (e_p == arc->v_tail) ? arc->v_head : arc->v_tail;
		if(another_v == G->v_list[e_p]->data->forerunner){ break; }
		arc = (e_p == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	    }
	    P_FormNode node = CreateOneFormNode(arc,-1);
	    StackInsert(stack,node);
	    e_p = G->v_list[e_p]->data->forerunner;
	}
    }
    else
    {
	while(e_p != s_p)
	{
	    arc = G->v_list[e_p]->arc_first_in;
	    while(arc)
	    {
		if(arc->v_tail == G->v_list[e_p]->data->forerunner){ break; }
		arc = arc->arc_head;
	    }
	    P_FormNode node = CreateOneFormNode(arc,-1);
	    StackInsert(stack,node);
	    e_p = arc->v_tail;
	}
    }

    //显示
    P_FormNode temp_head = stack->head;
    while(temp_head != NULL)
    {
	printf("%s ",temp_head->arc->info->name);
	temp_head = temp_head->next;
    }
    printf("\n");
    //释放栈
    StackFree(stack);
}

/*Floyd算法*/
bool Floyd_MSP(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Floyd_MSP G is NULL"); return false; }
    V_Position i,j,k; P_ArcNode arc;
    /*MSPV[i][j]记录顶点对i到j的最短路径值*/
    int MSPV[G->v_num][G->v_num];
    /*FRS[i][j]记录顶点对i到j的最短路径中j的前驱顶点。
     *也即FRS[i]就是顶点i的最短路径中的所有经过顶*/
    V_Position FRS[G->v_num][G->v_num];
    /*第一步初始化*/
    for(i = 0; i < G->v_num; ++i)
    {
	for(j = 0; j < G->v_num; ++j)
	{
	    if(j == i)
	    { MSPV[i][j] = 0; }
	    else/*初次进行比较最短路径值进而更新的基础*/
	    { MSPV[i][j] = MAX_MORE_PATH_LEN; }
	    FRS[i][j] = -1;
	}
    }
    /*第二步初始化
     *k作为中间顶点，其值表现为顶点数组下标，进而代表相应顶点
     *当k=-1时，即i与j之间无中间顶点，也即所有直接相连的点对
     *的最短路径和前驱顶点可以确定，是继续ij之间有中间顶点计
     *算的基础*/
    if(G->g_type & UNDIGRAPH)
    {
	for(i = 0; i < G->v_num; ++i)
	{
	    arc = G->v_list[i]->arc_first_out;
	    while(arc)
	    {
		if(i == arc->v_tail)
		{
		    MSPV[arc->v_tail][arc->v_head] = arc->info->power;
		    MSPV[arc->v_head][arc->v_tail] = arc->info->power;
		    FRS[arc->v_tail][arc->v_head] = arc->v_tail;
		    FRS[arc->v_head][arc->v_tail] = arc->v_head;
		}
		arc = (i == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	    }
	}
    }
    else if(G->g_type & DIGRAPH)
    {
	for(i = 0; i < G->v_num; ++i)
	{
	    arc = G->v_list[i]->arc_first_out;
	    while(arc)
	    {
		MSPV[arc->v_tail][arc->v_head] = arc->info->power;
		FRS[arc->v_tail][arc->v_head] = arc->v_tail;
		arc = arc->arc_tail;
	    }
	}
    }
    
    /*算法核心：当k>=0时，即[i][j]之间存在中间顶点时
     *k的规模从小到大，即动态规划技术*/
    for(k = 0; k < G->v_num; ++k)
    {
	/*所有的点对在k点作为其中间节点时计算其最短路径值和前驱*/
	for(i = 0; i < G->v_num; ++i)
	{
	    for(j = 0; j < G->v_num; ++j)
	    {
		if(i == j){ continue; }
		/*符合条件则更新*/
		if(MSPV[i][k] + MSPV[k][j] < MSPV[i][j])
		{
		    MSPV[i][j] = MSPV[i][k] + MSPV[k][j];
		    /*不能FRS[i][j] = k;因为当将k作为中间顶点更新i-j的最短路径值时，
		     *顶点k-j的路径可能不是直接路径而是间接路径，即k-j之间还存在其
		     *他顶点，因而此时FRS[i][j]等于FRS[k][j]的值而非k*/
		    FRS[i][j]  = FRS[k][j];
		}
	    }
	}
    }
    /*再次遍历所有的边，检测是否有负值环*/
    V_Position forerunner;
    if(G->g_type & UNDIGRAPH)
    {
	P_ArcNode arc;
	/*无向图，只要有负值边就算有负值环*/
	for(i = 0; i < G->v_num; ++i)
	{
	    arc = G->v_list[i]->arc_first_out;
	    while(arc)
	    {
		if(arc->info->power < 0)
		{ printf("图中存在负值环，Floyd算法无法计算所有点对最短路径值\n"); return false; }
		arc = (i == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	    }
	}
    }
    else if(G->g_type & DIGRAPH)
    {
	/*遍历任意两点ij，其前驱为forerunner，如果有负值环，则会产生
	 *MSPV[i][forerunner] + MSPV[forerunner][j] < MSPV[i][j]*/
	for(i = 0; i < G->v_num; ++i)
	{
	    for(j = 0; j < G->v_num; ++j)
	    {
		if(i == j){ continue; }
		if(FRS[i][j] == -1){ continue; }
		forerunner = FRS[i][j];
		if(MSPV[i][forerunner] + MSPV[forerunner][j] < MSPV[i][j])
		{ printf("图中存在负值环，Floyd算法无法计算所有点对最短路径值\n"); return false; }
	    }
	}
    }


    /*显示*/
    printf("MSPV:\n");
    for(i = 0; i < G->v_num; ++i)
    {
	for(j = 0; j < G->v_num; ++j)
	{
	    printf("%-3d ",MSPV[i][j]);
	}
	printf("\n");
    }
    printf("FRS:\n");
    for(i = 0; i < G->v_num; ++i)
    {
	for(j = 0; j < G->v_num; ++j)
	{
	    printf("%-3d ",FRS[i][j]);
	}
	printf("\n");
    }
}

//数据释放
//无向图释放
void Graphics_UndigraphFree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("GraphicsFree G is NULL"); return; }
    P_ArcNode arcs[G->arc_num];
    int i = 0; int a_p = 0;
    P_ArcNode arc = NULL;
    while(i < G->v_num)
    {
	//释放点数据
	SAFE_FREE(G->v_list[i]->data);
	//记录出边
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    if(i == arc->v_tail)
	    { arcs[a_p] = arc; ++a_p; }
	    arc = (i == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	}
	//释放点
	SAFE_FREE(G->v_list[i]);
	++i;
    }
    i = 0;
    //释放边信息、边
    while(i < G->arc_num)
    {
	SAFE_FREE(arcs[i]->info);
	SAFE_FREE(arcs[i]);
	++i;
    }
    //释放图
    SAFE_FREE(G);
}

//有向图释放
void Graphics_DigraphFree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("GraphicsFree G is NULL"); return; }
    int i = 0;
    P_ArcNode arc = NULL;
    P_ArcNode temp_arc = NULL;
    while(i < G->v_num)
    {
	//释放点数据
	SAFE_FREE(G->v_list[i]->data);
	//释放边
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    temp_arc = arc;
	    arc = arc->arc_tail;
	    SAFE_FREE(temp_arc->info);
	    SAFE_FREE(temp_arc);
	}
	//释放点
	SAFE_FREE(G->v_list[i]);
	++i;
    }
    //释放图
    SAFE_FREE(G);
}

//栈表的释放
void StackFree(P_Stack stack)
{
    if(stack == NULL)
    { LINE_DEBUG("StackFree arguments is illegal"); return; }
    P_FormNode temp_node = NULL;
    while(stack->head)
    {
	temp_node = stack->head;
	stack->head = stack->head->next;
	SAFE_FREE(temp_node);
    }

    SAFE_FREE(stack);
}

int main()
{
    /*建图*/
    P_Graphics undigraph_one = CreateOneUndigraph();
    if(undigraph_one == NULL){ LINE_DEBUG("undigraph_one create failed"); return -1; }

    P_Graphics undigraph_two = CreateOneUndigraph();
    if(undigraph_two == NULL){ LINE_DEBUG("undigraph_two create failed"); return -1; }

    P_Graphics digraph_one = CreateOneDigraph();
    if(digraph_one == NULL){ LINE_DEBUG("digraph_one create failed"); return -1; }

    P_Graphics digraph_two = CreateOneDigraph();
    if(digraph_two == NULL){ LINE_DEBUG("digraph_two create failed"); return -1; }
    
    P_Graphics cyclic_digraph = CreateOneCyclicDigraph();
    if(cyclic_digraph == NULL){ LINE_DEBUG("cyclic_digraph create failed"); return -1; }

    /*单源最短路径三种算法*/
    printf("----------------BellmanFord算法-----------------\n");
    bool re = BellmanFord_MSP(undigraph_one,0);
    if(re == true)
    { OneSource_ShowMSP(undigraph_one,0,5); }
    
    printf("----------------Dijkstra算法-----------------\n");
    re = Dijkstra_MSP(digraph_one,0);
    if(re == true)
    { OneSource_ShowMSP(digraph_one,0,5); }
    
    printf("----------------拓扑排序算法-----------------\n");
    re = TopologicalSort_MSP(digraph_two,4);
    if(re == true)
    { OneSource_ShowMSP(digraph_two,4,5); }
    
    /*所有点对最短路径算法*/
    printf("----------------Floyd算法 无向图-----------------\n");
    Floyd_MSP(undigraph_two);
    printf("----------------Floyd算法 有向图-----------------\n");
    Floyd_MSP(digraph_two);/*可使用cyclic_digraph检测带负值环的有向图*/
    
    //清理工作
    Graphics_UndigraphFree(undigraph_one);
    Graphics_UndigraphFree(undigraph_two);
    Graphics_DigraphFree(digraph_one);
    Graphics_DigraphFree(digraph_two);
    Graphics_DigraphFree(cyclic_digraph);

    return 0;
}
