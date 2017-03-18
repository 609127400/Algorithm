/*
 *                               ���·��
 * 1.���·��(MinimumShortPath,MSP)��ָͼG������һ������V����G��������һ��������
 *   ·����·��Ȩֵ����С������Ե��Ǵ�Ȩͼ��������Ȩֵ���൱��ÿ����Ȩֵ��ȣ�����
 *   �ı���Խ��·��Խ�̡�
 * 2.�������·�����⣬���������Դ�㣬Ŀ�ĵؽ����յ㡣��Ϊ��Դ���·������������
 *   ·�������ȵȣ���Դ���·��������Ϊ���������������Ļ�����
 * 3.��Դ���·��
 *   ��һ�������㵽ͼ��������������·����
 *   (1)BellmanFord�㷨�����һ��ͼ��ͼ�пɴ��ڸ�ֵ�ߺ�Ȧ���㷨���̾���ͼ����ɨ����
 *   �ж���ͱߵĹ��̣��������У������ж������·��ֵ��ʼ��ΪMAX_MORE_PATH_LEN������
 *   ʼ����ѹ����У�Ȼ��ʼ���㡣ÿ����һ�����㣬��ֱ����˶�������·��ֵ+ ��
 *   Ȩֵ�Ƿ�С�����Ӧ�������ڽӵ����е�ֵ����С�ڣ���������ڽӵ����С·��ֵ��ǰ
 *   �����㡣ֱ��������ϻ���е�������ͼ�������Ķ���ʱ���㷨���������Ժܼ򵥵ĵó���
 *   ���㷨��ʱ��Ч��ΪO(E)��E����ͼ���ܱ���
 *   ��Ҫע��������ͼ�Ƿ���ڸ�ֵȦ����Ȧ�����бߵ�Ȩֵ֮���Ǹ�����������ͼֻ��
 *   �ڸ�ֵ�߶����ᵼ�¸�ֵȦ����Ȼ������ȷ������·����
 *   ����ͼ�еĸ�ֵȦ����A->B->C->A����ȨֵA-B=-4��B-C=1��C-A=1�������������ͼ�д�
 *   �ڸ�ֵȦ���������A����С·��ֵΪ2�����·��ֵ��M��ʾ����Ȩֵ��W��ʾ�����ݲ���
 *   ���㷨��
 *   Pop(A) M(B)=2+-4=-2,Push(B);
 *   Pop(B) M(C)=-2+1=-1,Push(C);
 *   Pop(C) M(A)=-1+1=0(����),Push(A);(�µ�M(A) + W(A->B) < M(B)�����������B��M)...
 *   ��һֱѭ����ȥ�����е㶼����������С���޷�ȷ����С·��ֵ��
 *   �ڶ��������������ͼ����󶥵�����ֹͣ��
 *   ���ٱ�����ʱ����ֵȦ��ĳ������A������M(A)+W(A-B) < M(B)���������֤ͼ�д��ڸ�ֵ
 *   Ȧ���޷��������·����
 *   ����ͼ�еĸ�ֵ�߱������һ����������ĸ�ֵȦ����A-B��M(A-B)=-1������A->B->A��
 *   A+��Ȩֵ����B��B+��Ȩֵ����A��A�ٸ���B��ѭ����ȥ��A��B����С·��ֵҲ����������
 *   С����ʱ��Ҳ����ֹͣ����ʱ����ͬ����ͼ�������жϸ�ֵȦ��������
 *   (2)Dijkstra�㷨���������ͼ����Ҫ�󲻴��ڸ�ֵ�ߡ��㷨����ʱ�����Bellman Ford��
 *   ����S_SET������������ȶ�����Ϊ������S_SET���ڴ����ȷ�����·��ֵ�Ķ��㣬����
 *   ��������ȷ��Ҫɨ�����ĵ㣬��������·��ֵ��Ϊ���ȶ��еĹؼ�ֵ����ʼ��Դ��
 *   �������PQ��Ȼ��ʼ���㡣ÿ��PQ��DeleteMin��һ�����㣬���ö������S_SET������
 *   ���Ըö������������ɨ��ö�������г��ߣ�����ÿ���ߵ�ͷ�������·��ֵ��ǰ
 *   ������и��£����ڶ����н�����Ӧ�Ľ�key���� �ڷ���δ��������е�ͷ����(mark ==
 *   0)���������С����ѭ����ֱ�������в�����Ԫ�ء�
 *   ���㷨��BellmanFord�㷨Ч�ʸ����ڣ����㷨��������С·��һ·������ȥ�ģ������µ�
 *   �����������ԣ���Bellman�㷨����������������һ�����㣬����������һ�顣�ҽ�����
 *   �ȶ��в���Ч�ʸ��ߡ�
 *   Dijkstra�㷨���ܴ��ڸ�ֵ�ߵ�ԭ�򣬿���A->B,A->C,B->C�����ߣ�A->BȨֵ5,A->CȨֵ3,
 *   B->CȨֵ-4��������AΪ�����㣬���㷨���������·����ֱ�Ӵ�A->C��3������ʵ��
 *   ��A->B->C��ֵΪ1��Ϊ���·����
 *   (3)�������������·���㷨�����DAG��
 *   ��ͼ�������������ͼ�����ж��㰴ǰ��˳�����д洢�ڸ��������С���λ��Դ��󣬴�
 *   Դ�㿪ʼ��Դ��֮��Ķ������ν��д�������ÿ���������г��ߵ�ͷ��������·��ֵ��
 *   ǰ�����㡣���ַ�����Dijkstra�㷨ֻ�ǻ���һ�ֱ�������ķ���ͷ�����Ч��Ҳ����һ�㡣
 *   ����ʵ��Ӧ����ҲӦ�ÿ��������������ĵ�ʱ�䡣
 * 4.���е�����·��
 *   ��ͼ���������������ľ��롣�򵥵Ĵ��������ظ�ƽ����������ÿ��������ΪԴ�㣬��
 *   ����Դ���·���㷨���м��㡣����ʱ��ΪO(N^3)��
 *   Floyd�㷨��
 *   1----2
 *   |\  /|
 *   | \/ |
 *   | /\ |
 *   |/  \|
 *   0----3
 *   Floyd�㷨�Ǵ�ͼ��������������м䶥��Ƕ������ǵģ������·��������ͼ�е�0-3�Ķ���
 *   ���·����Ҫô0-3ֱ��������·����̣�ҪôҪ����ͼ������������γɵļ�ӵ�·����̣�
 *   ��0-1-3��0-2-3��0-1-2-3������·����ֱ��·���̣���һ�����·������һ�����·���̵�
 *   ������������·��ֵ����ʼʱ���������·������MSPV����MSPV[0][3]��ʾ0-3�����·��ֵ��
 *   �þ����ʼ��Ϊֱ�Ӿ��룬���㵽��������Ϊ0����ֱ�������Ķ���Ϊ����󡣼������е�ԣ�
 *   ��϶�Ҫ������ѭ�������⣬���������м䶥��k�Ĺ�ģ��С����ҲҪ��һ��ѭ�������ѭ��
 *   ʹ���˶�̬�滮�ļ��������������ǵģ�����ֻ��1��Ϊ�м䶥�㣬�������ж���ԣ�������С
 *   ·��ֵ����0-1-3���Ƚ�ԭMSPV[0][3]��MSPV[0][1]+MSPV[1][3]���и��£�Ȼ������2��Ϊ�м�
 *   ���㣬�������ж���ԣ�������С·��ֵ����0-2-3���Ƚ�ԭMSPV[0][3]��MSPV[0][2]+MSPV[2][3]
 *   ���и��¡����ѭ�������п������м䶥�㣬������ж���Եĸ��£�������ϡ�������һ����
 *   �⣬���0-3��˵������1��2����Ϊ���м䶥�㣬��0-1-2-3�������������漰��һ��ô������
 *   �Ƕ�̬�滮�����ã�����˳�򽫹�ģ�ϴ�������������Ŀ�����ͬ����ʽ���Ĺ�ģ��С������
 *   ������������¼��Ȼ����ݹ�ģ��С����Ľ���ټ����ģ�ϵĴ����⣬���ջ�����ۣ�����
 *   �յ�������������⡣k�Ĺ�ģ��С���󣬼��м䶥�㼯�Ϲ�ģ��С���󡣵�k=1ʱ���Ѿ������
 *   ���е����1Ϊ�м䶥�����С·��ֵ����ȻҲ����0-2�����ߣ���0-2�����·��ֵ�Ƿ���Ҫ��
 *   ��1�Ѿ���k=1ѭ���м�����������k=2ʱ����0-3�����ߵ����·��ֵ���Ƚ�MSPV[0][2]+MSPV[2][3]
 *   ��MSPV[0][3]ʱ���е�MSPV[0][2]�Ѿ���k=1ʱ��������Ľ����MSPV[0][2]��ֵ�Ѿ���������
 *   �����1��Ϊ�м䶥�㣬����Ҫk=2��һ���ٷ��ġ��Դ����ƣ�������չ��0-3���м䶥�㾭����
 *   ������ʱ�����е�ԣ�Ҳ��˵�����ÿһ���м䶥��������е�����·��ֵ���㣬���Եó�
 *   ��ȷ�����
 *   �ڼ�¼���е�Ե����·��ǰ������ʱ��i-k-j��ǰ������=k-j��ǰ�����㣬Ҳ�Ƕ�̬�滮������
 *   ���֡�����k-j����ֱ��·�������������м䶥�㣬���i-k-j�Ľ������֮ǰ��ѭ�����Ѿ�����
 *   ���k-j��ǰ�������
 *   �Ը�ֵ���ļ�⣺�ڼ�����Ϻ󣬿����±������е��ij����ǰ����Ϊforerunner�������ڸ�ֵ
 *   ����������MSPV[i][forerunner]+MSPV[forerunner][j] < MSPV[i][j];
 *
 *
 *                                                           2016��12��8��
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
/*�����������·��ֵ��ʼ��ֵ��Ҫ����ͼ�����·��ֵ�����������*/
#define MAX_MORE_PATH_LEN 1000000
/*��������·��ֵ�ڱ���ҪС��ͼ����С��·��ֵ(Դ��·��ֵ0)����������С*/
#define MIN_MORE_PATH_LEN  (-1000000)

typedef int Power;
typedef int V_Position;
typedef int G_Type;

//����Ϣ
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

//��
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

//��������
typedef struct
{
    int id;
    char name[MAX_VERTEX_NAME_LEN];
    V_Position forerunner;/*���·����ǰ�����㣬���ֶνṹֻ�����ڵ�Դ���·��*/
    int min_len;/*�ӳ����㵽�ö�������·��ֵ�����ֶνṹֻ�����ڵ�Դ���·��*/
}VertexData,*P_VertexData;

P_VertexData CreateOneVertexData(int id,char *name)
{
    P_VertexData new_data = (P_VertexData)malloc(sizeof(VertexData));
    if(new_data == NULL){ LINE_DEBUG("malloc VertexData failed"); return NULL; }
    new_data->id = id;
    strncpy(new_data->name,name,MAX_VERTEX_NAME_LEN);
    new_data->forerunner = -1;
    new_data->min_len = MAX_MORE_PATH_LEN;/*��ʼ����С·��ֵΪ�����*/
    return new_data;
}

//����
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

//ͼ
typedef struct
{
    G_Type g_type;
    P_VertexNode v_list[MAX_VERTEX_NUM];
    int v_num; int arc_num;
}Graphics,*P_Graphics;

//����
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

//ջ
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

/*���У�����bellman�㷨*/
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

/*���ȶ��У�����Dijkstra�㷨
 *�ؼ�����ͼ��������·��ֵmin_len�ֶ�*/
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
    /*�����ڱ�����Ҫ�����ͷ�*/
    data = CreateOneVertexData(-1,"Sentry");
    if(data == NULL)
    { LINE_DEBUG("CreateOnePQ malloc VertexData failed"); goto Label_CreateOnePQ_Clean; }
    data->min_len = MIN_MORE_PATH_LEN;/*�����ڱ��ڶ��еĹؼ�ֵ*/
    V = CreateOneVertexNode(data);
    if(V == NULL)
    { LINE_DEBUG("CreateOnePQ malloc Vertex failed"); goto Label_CreateOnePQ_Clean; }
    new_pq->queue[0] = V;

    return new_pq;

Label_CreateOnePQ_Clean:
    SAFE_FREE(new_pq); SAFE_FREE(data); SAFE_FREE(V);
    return NULL;
}

/*���ö����mark�ֶα�Ƕ����ڶ��е�λ�ã����㽵key����*/
bool PQ_Insert(P_PQ PQ,P_VertexNode V)
{
    if(PQ == NULL){ LINE_DEBUG("PQ_Insert PQ is NULL"); return false; }
    if(V == NULL){ LINE_DEBUG("PQ_Insert V is NULL"); return false; }
    if(PQ->e_num == MAX_PQ_ELEMENT_NUM){ LINE_DEBUG("PQ_Insert PQ is FULL"); return false; }
    int blank = PQ->e_num + 1;
    int parent;
    /*���˲���*/
    while(blank > 0)
    {
	parent = blank>>1;
	if(V->data->min_len >= PQ->queue[parent]->data->min_len)
	{
	    PQ->queue[blank] = V;
	    PQ->queue[blank]->mark = blank;
	    ++(PQ->e_num);
	    V->mark = blank;/*�������λ��*/
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
    /*���˲�������lchild=PQ->e_numʱ��˵�����һ��Ԫ�������ӽڵ㣬��ʱ����ֱ��ͣ��
     *ѭ����ʱblankͣ����last_keyԪ�صĸ��ڵ�*/
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
	/*λ�øı䣬���б��*/
	PQ->queue[blank]->mark = blank;
    }
    PQ->queue[blank] = PQ->queue[PQ->e_num];
    PQ->queue[blank]->mark = blank;
    PQ->queue[PQ->e_num] = NULL;
    --(PQ->e_num);

    return min_vertex;
}

/*�Ѷ���PQ��pλ�õ�Ԫ�ص���С·��ֵ��Ϊlen*/
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
    /*���˲���*/
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
    /*���ڱ��⣬�����еĶ�����ͼ��Free�����ͷ�*/
    if(PQ == NULL){ LINE_DEBUG("PQ_Free PQ is NULL"); return; }
    SAFE_FREE(PQ->queue[0]->data);
    SAFE_FREE(PQ->queue[0]);
    SAFE_FREE(PQ);
}

/*
 *
 *     0-----5         Ȩֵ
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
    //����
    P_ArcInfo info0_2 = NULL; P_ArcInfo info0_4 = NULL; P_ArcInfo info0_5 = NULL; P_ArcInfo info1_2 = NULL;
    P_ArcInfo info2_3 = NULL; P_ArcInfo info3_4 = NULL; P_ArcInfo info3_5 = NULL; P_ArcInfo info4_5 = NULL;
    P_ArcNode Arc0_2 = NULL; P_ArcNode Arc0_4 = NULL; P_ArcNode Arc0_5 = NULL; P_ArcNode Arc1_2 = NULL;
    P_ArcNode Arc2_3 = NULL; P_ArcNode Arc3_4 = NULL; P_ArcNode Arc3_5 = NULL; P_ArcNode Arc4_5 = NULL;
    P_VertexData data0 = NULL; P_VertexData data1 = NULL; P_VertexData data2 = NULL;
    P_VertexData data3 = NULL; P_VertexData data4 = NULL; P_VertexData data5 = NULL;
    P_VertexNode V0 = NULL; P_VertexNode V1 = NULL; P_VertexNode V2 = NULL;
    P_VertexNode V3 = NULL; P_VertexNode V4 = NULL; P_VertexNode V5 = NULL;
    P_Graphics undigraph = NULL;
    //����Ϣ
    info0_2 = CreateOneArcInfo("V0-V2",10); info0_4 = CreateOneArcInfo("V0-V4",30); info0_5 = CreateOneArcInfo("V0-V5",100);
    info1_2 = CreateOneArcInfo("V1-V2",5);  info2_3 = CreateOneArcInfo("V2-V3",50); info3_4 = CreateOneArcInfo("V3-V4",20);
    info3_5 = CreateOneArcInfo("V3-V5",10); info4_5 = CreateOneArcInfo("V4-V5",60);
    if(info0_2 == NULL || info0_4 == NULL || info0_5 == NULL || info1_2 == NULL
    || info2_3 == NULL || info3_4 == NULL || info3_5 == NULL || info4_5 == NULL)
    { LINE_DEBUG("Create ArcInfo failed"); goto Label_CreateOneUndigraph_Clean; }
    //��
    Arc0_2 = CreateOneArcNode(info0_2); Arc0_4 = CreateOneArcNode(info0_4); Arc0_5 = CreateOneArcNode(info0_5);
    Arc1_2 = CreateOneArcNode(info1_2); Arc2_3 = CreateOneArcNode(info2_3); Arc3_4 = CreateOneArcNode(info3_4);
    Arc3_5 = CreateOneArcNode(info3_5); Arc4_5 = CreateOneArcNode(info4_5);
    if(Arc0_2 == NULL || Arc0_4 == NULL || Arc0_5 == NULL || Arc1_2 == NULL
    || Arc2_3 == NULL || Arc3_4 == NULL || Arc3_5 == NULL || Arc4_5 == NULL)
    { LINE_DEBUG("Create Arc failed"); goto Label_CreateOneUndigraph_Clean; }
    //������
    data0 = CreateOneVertexData(0,"V0"); data1 = CreateOneVertexData(1,"V1"); data2 = CreateOneVertexData(2,"V2");
    data3 = CreateOneVertexData(3,"V3"); data4 = CreateOneVertexData(4,"V4"); data5 = CreateOneVertexData(5,"V5");
    V0 = CreateOneVertexNode(data0); V1 = CreateOneVertexNode(data1); V2 = CreateOneVertexNode(data2);
    V3 = CreateOneVertexNode(data3); V4 = CreateOneVertexNode(data4); V5 = CreateOneVertexNode(data5);
    if(data0 == NULL || data1 == NULL || data2 == NULL || data3 == NULL || data4 == NULL || data5 == NULL
    || V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL || V4 == NULL || V5 == NULL)
    { LINE_DEBUG("Create Vertex(data) failed"); goto Label_CreateOneUndigraph_Clean; }
    //ͼ
    undigraph = (P_Graphics)malloc(sizeof(Graphics));
    if(undigraph == NULL){ LINE_DEBUG("Create Graphics failed"); goto Label_CreateOneUndigraph_Clean; }

    //��ϵ��֯
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
 *     0-----5         Ȩֵ
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
    //����
    P_ArcInfo info0_2 = NULL; P_ArcInfo info0_4 = NULL; P_ArcInfo info0_5 = NULL; P_ArcInfo info1_2 = NULL;
    P_ArcInfo info2_3 = NULL; P_ArcInfo info4_3 = NULL; P_ArcInfo info3_5 = NULL; P_ArcInfo info4_5 = NULL;
    P_ArcNode Arc0_2 = NULL; P_ArcNode Arc0_4 = NULL; P_ArcNode Arc0_5 = NULL; P_ArcNode Arc1_2 = NULL;
    P_ArcNode Arc2_3 = NULL; P_ArcNode Arc4_3 = NULL; P_ArcNode Arc3_5 = NULL; P_ArcNode Arc4_5 = NULL;
    P_VertexData data0 = NULL; P_VertexData data1 = NULL; P_VertexData data2 = NULL;
    P_VertexData data3 = NULL; P_VertexData data4 = NULL; P_VertexData data5 = NULL;
    P_VertexNode V0 = NULL; P_VertexNode V1 = NULL; P_VertexNode V2 = NULL;
    P_VertexNode V3 = NULL; P_VertexNode V4 = NULL; P_VertexNode V5 = NULL;
    P_Graphics digraph = NULL;
    //����Ϣ
    info0_2 = CreateOneArcInfo("V0->V2",10); info0_4 = CreateOneArcInfo("V0->V4",30); info0_5 = CreateOneArcInfo("V0->V5",100);
    info1_2 = CreateOneArcInfo("V1->V2",5);  info2_3 = CreateOneArcInfo("V2->V3",50); info4_3 = CreateOneArcInfo("V4->V3",20);
    info3_5 = CreateOneArcInfo("V3->V5",10); info4_5 = CreateOneArcInfo("V4->V5",60);
    if(info0_2 == NULL || info0_4 == NULL || info0_5 == NULL || info1_2 == NULL
    || info2_3 == NULL || info4_3 == NULL || info3_5 == NULL || info4_5 == NULL)
    { LINE_DEBUG("Create ArcInfo failed"); goto Label_CreateOneDigraph_Clean; }
    //��
    Arc0_2 = CreateOneArcNode(info0_2); Arc0_4 = CreateOneArcNode(info0_4); Arc0_5 = CreateOneArcNode(info0_5);
    Arc1_2 = CreateOneArcNode(info1_2); Arc2_3 = CreateOneArcNode(info2_3); Arc4_3 = CreateOneArcNode(info4_3);
    Arc3_5 = CreateOneArcNode(info3_5); Arc4_5 = CreateOneArcNode(info4_5);
    if(Arc0_2 == NULL || Arc0_4 == NULL || Arc0_5 == NULL || Arc1_2 == NULL
    || Arc2_3 == NULL || Arc4_3 == NULL || Arc3_5 == NULL || Arc4_5 == NULL)
    { LINE_DEBUG("Create Arc failed"); goto Label_CreateOneDigraph_Clean; }
    //������
    data0 = CreateOneVertexData(0,"V0"); data1 = CreateOneVertexData(1,"V1"); data2 = CreateOneVertexData(2,"V2");
    data3 = CreateOneVertexData(3,"V3"); data4 = CreateOneVertexData(4,"V4"); data5 = CreateOneVertexData(5,"V5");
    V0 = CreateOneVertexNode(data0); V1 = CreateOneVertexNode(data1); V2 = CreateOneVertexNode(data2);
    V3 = CreateOneVertexNode(data3); V4 = CreateOneVertexNode(data4); V5 = CreateOneVertexNode(data5);
    if(data0 == NULL || data1 == NULL || data2 == NULL || data3 == NULL || data4 == NULL || data5 == NULL
    || V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL || V4 == NULL || V5 == NULL)
    { LINE_DEBUG("Create Vertex(data) failed"); goto Label_CreateOneDigraph_Clean; }
    //ͼ
    digraph = (P_Graphics)malloc(sizeof(Graphics));
    if(digraph == NULL){ LINE_DEBUG("Create Graphics failed"); goto Label_CreateOneDigraph_Clean; }

    //��ϵ��֯
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

//����ֵ��������ͼ
P_Graphics CreateOneCyclicDigraph()
{
    //����
    P_ArcInfo info0_2 = NULL; P_ArcInfo info0_4 = NULL; P_ArcInfo info0_5 = NULL; P_ArcInfo info1_2 = NULL;
    P_ArcInfo info2_3 = NULL; P_ArcInfo info4_3 = NULL; P_ArcInfo info3_5 = NULL; P_ArcInfo info5_4 = NULL;
    P_ArcNode Arc0_2 = NULL; P_ArcNode Arc0_4 = NULL; P_ArcNode Arc0_5 = NULL; P_ArcNode Arc1_2 = NULL;
    P_ArcNode Arc2_3 = NULL; P_ArcNode Arc4_3 = NULL; P_ArcNode Arc3_5 = NULL; P_ArcNode Arc5_4 = NULL;
    P_VertexData data0 = NULL; P_VertexData data1 = NULL; P_VertexData data2 = NULL;
    P_VertexData data3 = NULL; P_VertexData data4 = NULL; P_VertexData data5 = NULL;
    P_VertexNode V0 = NULL; P_VertexNode V1 = NULL; P_VertexNode V2 = NULL;
    P_VertexNode V3 = NULL; P_VertexNode V4 = NULL; P_VertexNode V5 = NULL;
    P_Graphics digraph = NULL;
    //����Ϣ
    info0_2 = CreateOneArcInfo("V0->V2",10); info0_4 = CreateOneArcInfo("V0->V4",30); info0_5 = CreateOneArcInfo("V0->V5",100);
    info1_2 = CreateOneArcInfo("V1->V2",5);  info2_3 = CreateOneArcInfo("V2->V3",50); info4_3 = CreateOneArcInfo("V4->V3",20);
    info3_5 = CreateOneArcInfo("V3->V5",10); info5_4 = CreateOneArcInfo("V5->V4",-31);
    if(info0_2 == NULL || info0_4 == NULL || info0_5 == NULL || info1_2 == NULL
    || info2_3 == NULL || info4_3 == NULL || info3_5 == NULL || info5_4 == NULL)
    { LINE_DEBUG("Create ArcInfo failed"); goto Label_CreateOneDigraph_Clean; }
    //��
    Arc0_2 = CreateOneArcNode(info0_2); Arc0_4 = CreateOneArcNode(info0_4); Arc0_5 = CreateOneArcNode(info0_5);
    Arc1_2 = CreateOneArcNode(info1_2); Arc2_3 = CreateOneArcNode(info2_3); Arc4_3 = CreateOneArcNode(info4_3);
    Arc3_5 = CreateOneArcNode(info3_5); Arc5_4 = CreateOneArcNode(info5_4);
    if(Arc0_2 == NULL || Arc0_4 == NULL || Arc0_5 == NULL || Arc1_2 == NULL
    || Arc2_3 == NULL || Arc4_3 == NULL || Arc3_5 == NULL || Arc5_4 == NULL)
    { LINE_DEBUG("Create Arc failed"); goto Label_CreateOneDigraph_Clean; }
    //������
    data0 = CreateOneVertexData(0,"V0"); data1 = CreateOneVertexData(1,"V1"); data2 = CreateOneVertexData(2,"V2");
    data3 = CreateOneVertexData(3,"V3"); data4 = CreateOneVertexData(4,"V4"); data5 = CreateOneVertexData(5,"V5");
    V0 = CreateOneVertexNode(data0); V1 = CreateOneVertexNode(data1); V2 = CreateOneVertexNode(data2);
    V3 = CreateOneVertexNode(data3); V4 = CreateOneVertexNode(data4); V5 = CreateOneVertexNode(data5);
    if(data0 == NULL || data1 == NULL || data2 == NULL || data3 == NULL || data4 == NULL || data5 == NULL
    || V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL || V4 == NULL || V5 == NULL)
    { LINE_DEBUG("Create Vertex(data) failed"); goto Label_CreateOneDigraph_Clean; }
    //ͼ
    digraph = (P_Graphics)malloc(sizeof(Graphics));
    if(digraph == NULL){ LINE_DEBUG("Create Graphics failed"); goto Label_CreateOneDigraph_Clean; }

    //��ϵ��֯
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

/*BellmanFord���·���㷨
 *ȷ��ͼ�ж�������С��32������������flag����
 *s_p �������·��ֵ��Դ�㶥��λ��*/
bool BellmanFord_MSP(P_Graphics G,V_Position s_p)
{
    if(G == NULL){ LINE_DEBUG("G is NULL"); return false; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("s_p is illegal"); return false; }
    
    /*��ʼ��*/
    /*��һ��������bitλ����ʶ�����Ƿ���������(�����)��������<=32����ÿ������ֻ��ɨ�����
     *���ڱ߶���һ��*/
    int flag = 0;
    bool re = false;
    P_Queue Q = CreateOneQueue(); if(Q == NULL){ LINE_DEBUG("Queue create failed"); return false; }
    G->v_list[s_p]->data->min_len = 0;/*��ʼ����ʼ��������·��ֵ������֮����޷�����*/
    re = Push(Q,s_p); if(re == false){ SAFE_FREE(Q); return false; } 
    flag |= (1 << s_p);
    int count = 0;/*����������¼Q����Ԫ�ص���Ŀ*/
    V_Position V;/*��ȡ������Ԫ��*/
    V_Position another_v;
    P_ArcNode arc = NULL;

    /*��ʼ���㵥Դ���·��*/
    while(Q->count != 0 && count < (G->v_num + 1))
    {
	re = Pop(Q,&V); if(re == false){ SAFE_FREE(Q); return false; }
	++count;/*�������ۼ�*/
	arc = G->v_list[V]->arc_first_out;
	/*���������ڽӶ�������·��ֵ*/
	while(arc)
	{
	    another_v = (V == arc->v_tail) ? arc->v_head : arc->v_tail;
	    /*������С·��ֵ�����õ���A-B��B�ֻط�A���㣬���A-BΪ������A���ǻ��BС*/
	    if((G->v_list[V]->data->min_len + arc->info->power) < G->v_list[another_v]->data->min_len)
	    {
		//�������·��ֵ
		G->v_list[another_v]->data->min_len = G->v_list[V]->data->min_len + arc->info->power;
		//����ǰ������
		G->v_list[another_v]->data->forerunner = V;
	    }
	    //���anotherû�м��������
	    if(!(flag & (1 << another_v)))
	    {
		re = Push(Q,another_v);
		if(re == false){ SAFE_FREE(Q); return false; }
		flag |= (1 << another_v);/*��ʶ�Ѽ��������*/
	    }

	    arc = (V == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	}
    }
    /*�ٴα������бߣ���ͼ���Ƿ���ڸ�ֵȦ*/
    for(count = 0; count < G->v_num; ++count)
    {
	arc = G->v_list[count]->arc_first_out;
	while(arc)
	{
	    /*ֻҪ���д��ڸ�ֵ�ߣ��϶������ĳһ�ߵ� A����С·��ֵ + ��Ȩֵ < B��С·��ֵ*/
	    another_v = (count == arc->v_tail) ? arc->v_head : arc->v_tail;
	    if(G->v_list[count]->data->min_len + arc->info->power < G->v_list[another_v]->data->min_len)
	    { printf("ͼ�д���ȨֵΪ���ıߵ�Ȧ��Bellman�㷨�޷��������·��\n"); SAFE_FREE(Q); return false; }

	    arc = (count == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	}
    }
    /*�ͷŶ���*/
    SAFE_FREE(Q);
    return true;
}

/* Dijkstra���·���㷨���������ͼ���޸�ֵ�ߡ�
 * �������飺S_SET S���ϣ����ڴ�����ҵ����·���Ķ���
 * �����㷨��Դ�㲻ͬ��S_SET��һ����������ͼ�Ķ���*/
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
    /*��ʼ��Դ�㣬����Դ��ѹ�����ȶ���S_SET�У�iΪ��ǰ����Ķ���*/
    G->v_list[s_p]->data->forerunner = -1; G->v_list[s_p]->data->min_len = 0;
    re = PQ_Insert(PQ,G->v_list[s_p]);
    if(re == false){ LINE_DEBUG("Dijkstra_MSP PQ_Insert failed"); PQ_Free(PQ); return false; }
    
    /*�������ȶ��п�ʼ����*/
    int r_p = 0;/*S_SETдλ��*/
    while(PQ->e_num != 0)
    {
	deal_v = PQ_DeleteMin(PQ);
	if(deal_v == NULL){ LINE_DEBUG("Dijkstra_MSP PQ_Insert failed"); PQ_Free(PQ); return false; }
	S_SET[r_p] = deal_v; ++(r_p);/*ȷ�����·��ֵ�Ķ���*/
	arc = deal_v->arc_first_out;
	while(arc)
	{
	    /*���ͷ���㲻���ڶ����У���϶�δ���������ֱ�Ӹ�����С·��ֵ��ǰ�����㲢�������*/
	    if(G->v_list[arc->v_head]->mark == 0)
	    {
		G->v_list[arc->v_head]->data->min_len = deal_v->data->min_len + arc->info->power;
		G->v_list[arc->v_head]->data->forerunner = arc->v_tail;
		re = PQ_Insert(PQ,G->v_list[arc->v_head]);/*Insert��������mark��ֵ*/
		if(re == false){ LINE_DEBUG("Dijkstra_MSP PQ_Insert failed"); PQ_Free(PQ); return false; }
	    }
	    /*���ͷ�����ڶ����У���鿴�Ƿ���Խ����ɳڲ����������ԣ��ڶ����н��н�key����*/
	    else
	    {
		if(deal_v->data->min_len + arc->info->power < G->v_list[arc->v_head]->data->min_len)
		{
		    re = PQ_DecreaseKey(PQ,G->v_list[arc->v_head]->mark,deal_v->data->min_len+arc->info->power);
		    if(re == false){ LINE_DEBUG("Dijkstra_MSP PQ_DecreaseKey failed"); PQ_Free(PQ); return false; }
		    G->v_list[arc->v_head]->data->forerunner = arc->v_tail;/*DecreaseKey����������ǰ����*/
		}
	    }
	    arc = arc->arc_tail;
	}
    }
    
    /*�ͷŶ���*/
    PQ_Free(PQ);
    
    return true;
}

/*�������飬V_FLAG��¼�����Ƿ���ʹ�*/
bool V_FLAG[MAX_VERTEX_NUM];

/*����������ȱ���������������*/
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

/*�������������·��*/
bool TopologicalSort_MSP(P_Graphics G,V_Position s_p)
{
    if(G == NULL){ LINE_DEBUG("TopologicalSort_MSP G is NULL"); return false; }
    if(s_p < 0 || s_p >= G->v_num)
    { LINE_DEBUG("TopologicalSort_MSP s_p is not valid"); return false; }
    int i = 0;
    while(i < G->v_num){ V_FLAG[i] = false; ++i; }
    /*��������*/
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

    /*�������·��*/
    /*��ʼ��Դ��*/
    G->v_list[s_p]->data->forerunner = -1;
    G->v_list[s_p]->data->min_len = 0;
    P_FormNode temp = stack->head;
    P_ArcNode arc = NULL;
    /*ջ�ж�λ��Դ��*/
    while(temp)
    {
	if(temp->vertex == s_p){ break; }
	temp = temp->next;
    }
    /*˳���������������м���*/
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
    /*����ͼ�����·���㷨�У����ֶ�����ܲ������뵽S_SET�����У������ᱻ��������
     *����Ҳ����Щ�㷨��ĳһԴ�������������·��������Щ����S_SET�еĶ���*/
    if(G->v_list[e_p]->data->forerunner == -1)
    { LINE_DEBUG("There is not a way from Vertex %d to the Vertex %d",s_p,e_p); return; }
    printf("���·���ܳ���%d\n",G->v_list[e_p]->data->min_len);
    P_Stack stack = CreateOneStack();
    P_ArcNode arc = NULL;
    V_Position another_v;
    //���յ�����������ν���ѹ��ջ��
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

    //��ʾ
    P_FormNode temp_head = stack->head;
    while(temp_head != NULL)
    {
	printf("%s ",temp_head->arc->info->name);
	temp_head = temp_head->next;
    }
    printf("\n");
    //�ͷ�ջ
    StackFree(stack);
}

/*Floyd�㷨*/
bool Floyd_MSP(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Floyd_MSP G is NULL"); return false; }
    V_Position i,j,k; P_ArcNode arc;
    /*MSPV[i][j]��¼�����i��j�����·��ֵ*/
    int MSPV[G->v_num][G->v_num];
    /*FRS[i][j]��¼�����i��j�����·����j��ǰ�����㡣
     *Ҳ��FRS[i]���Ƕ���i�����·���е����о�����*/
    V_Position FRS[G->v_num][G->v_num];
    /*��һ����ʼ��*/
    for(i = 0; i < G->v_num; ++i)
    {
	for(j = 0; j < G->v_num; ++j)
	{
	    if(j == i)
	    { MSPV[i][j] = 0; }
	    else/*���ν��бȽ����·��ֵ�������µĻ���*/
	    { MSPV[i][j] = MAX_MORE_PATH_LEN; }
	    FRS[i][j] = -1;
	}
    }
    /*�ڶ�����ʼ��
     *k��Ϊ�м䶥�㣬��ֵ����Ϊ���������±꣬����������Ӧ����
     *��k=-1ʱ����i��j֮�����м䶥�㣬Ҳ������ֱ�������ĵ��
     *�����·����ǰ���������ȷ�����Ǽ���ij֮�����м䶥���
     *��Ļ���*/
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
    
    /*�㷨���ģ���k>=0ʱ����[i][j]֮������м䶥��ʱ
     *k�Ĺ�ģ��С���󣬼���̬�滮����*/
    for(k = 0; k < G->v_num; ++k)
    {
	/*���еĵ����k����Ϊ���м�ڵ�ʱ���������·��ֵ��ǰ��*/
	for(i = 0; i < G->v_num; ++i)
	{
	    for(j = 0; j < G->v_num; ++j)
	    {
		if(i == j){ continue; }
		/*�������������*/
		if(MSPV[i][k] + MSPV[k][j] < MSPV[i][j])
		{
		    MSPV[i][j] = MSPV[i][k] + MSPV[k][j];
		    /*����FRS[i][j] = k;��Ϊ����k��Ϊ�м䶥�����i-j�����·��ֵʱ��
		     *����k-j��·�����ܲ���ֱ��·�����Ǽ��·������k-j֮�仹������
		     *�����㣬�����ʱFRS[i][j]����FRS[k][j]��ֵ����k*/
		    FRS[i][j]  = FRS[k][j];
		}
	    }
	}
    }
    /*�ٴα������еıߣ�����Ƿ��и�ֵ��*/
    V_Position forerunner;
    if(G->g_type & UNDIGRAPH)
    {
	P_ArcNode arc;
	/*����ͼ��ֻҪ�и�ֵ�߾����и�ֵ��*/
	for(i = 0; i < G->v_num; ++i)
	{
	    arc = G->v_list[i]->arc_first_out;
	    while(arc)
	    {
		if(arc->info->power < 0)
		{ printf("ͼ�д��ڸ�ֵ����Floyd�㷨�޷��������е�����·��ֵ\n"); return false; }
		arc = (i == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	    }
	}
    }
    else if(G->g_type & DIGRAPH)
    {
	/*������������ij����ǰ��Ϊforerunner������и�ֵ����������
	 *MSPV[i][forerunner] + MSPV[forerunner][j] < MSPV[i][j]*/
	for(i = 0; i < G->v_num; ++i)
	{
	    for(j = 0; j < G->v_num; ++j)
	    {
		if(i == j){ continue; }
		if(FRS[i][j] == -1){ continue; }
		forerunner = FRS[i][j];
		if(MSPV[i][forerunner] + MSPV[forerunner][j] < MSPV[i][j])
		{ printf("ͼ�д��ڸ�ֵ����Floyd�㷨�޷��������е�����·��ֵ\n"); return false; }
	    }
	}
    }


    /*��ʾ*/
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

//�����ͷ�
//����ͼ�ͷ�
void Graphics_UndigraphFree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("GraphicsFree G is NULL"); return; }
    P_ArcNode arcs[G->arc_num];
    int i = 0; int a_p = 0;
    P_ArcNode arc = NULL;
    while(i < G->v_num)
    {
	//�ͷŵ�����
	SAFE_FREE(G->v_list[i]->data);
	//��¼����
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    if(i == arc->v_tail)
	    { arcs[a_p] = arc; ++a_p; }
	    arc = (i == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	}
	//�ͷŵ�
	SAFE_FREE(G->v_list[i]);
	++i;
    }
    i = 0;
    //�ͷű���Ϣ����
    while(i < G->arc_num)
    {
	SAFE_FREE(arcs[i]->info);
	SAFE_FREE(arcs[i]);
	++i;
    }
    //�ͷ�ͼ
    SAFE_FREE(G);
}

//����ͼ�ͷ�
void Graphics_DigraphFree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("GraphicsFree G is NULL"); return; }
    int i = 0;
    P_ArcNode arc = NULL;
    P_ArcNode temp_arc = NULL;
    while(i < G->v_num)
    {
	//�ͷŵ�����
	SAFE_FREE(G->v_list[i]->data);
	//�ͷű�
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    temp_arc = arc;
	    arc = arc->arc_tail;
	    SAFE_FREE(temp_arc->info);
	    SAFE_FREE(temp_arc);
	}
	//�ͷŵ�
	SAFE_FREE(G->v_list[i]);
	++i;
    }
    //�ͷ�ͼ
    SAFE_FREE(G);
}

//ջ����ͷ�
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
    /*��ͼ*/
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

    /*��Դ���·�������㷨*/
    printf("----------------BellmanFord�㷨-----------------\n");
    bool re = BellmanFord_MSP(undigraph_one,0);
    if(re == true)
    { OneSource_ShowMSP(undigraph_one,0,5); }
    
    printf("----------------Dijkstra�㷨-----------------\n");
    re = Dijkstra_MSP(digraph_one,0);
    if(re == true)
    { OneSource_ShowMSP(digraph_one,0,5); }
    
    printf("----------------���������㷨-----------------\n");
    re = TopologicalSort_MSP(digraph_two,4);
    if(re == true)
    { OneSource_ShowMSP(digraph_two,4,5); }
    
    /*���е�����·���㷨*/
    printf("----------------Floyd�㷨 ����ͼ-----------------\n");
    Floyd_MSP(undigraph_two);
    printf("----------------Floyd�㷨 ����ͼ-----------------\n");
    Floyd_MSP(digraph_two);/*��ʹ��cyclic_digraph������ֵ��������ͼ*/
    
    //������
    Graphics_UndigraphFree(undigraph_one);
    Graphics_UndigraphFree(undigraph_two);
    Graphics_DigraphFree(digraph_one);
    Graphics_DigraphFree(digraph_two);
    Graphics_DigraphFree(cyclic_digraph);

    return 0;
}
