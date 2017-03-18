/*
 *                          有向无环图
 * 1.有向图用十字链表存储。
 * 2.有向无环图(Directed Acyclic Graph,DAG)。有向无环图：图中任意两点A B，存
 *   在A通向B的路径，但不存在此路径经过其他点后再回到A的情况。有向无环图是描
 *   述工程的一个有效工具，任何工程都包含若干个活动(子工程)，而对于整个工程，
 *   我们主要关心两方面问题：工程能否顺利进行和在最短时间内完成。将图的顶点作
 *   为一个个活动，边作为活动间的关系的图称为AOV(activity on vertex)网；边表
 *   示活动，称为AOE网。对应的应用为拓扑排序和关键路径问题。
 * 3.环的检测。
 *   无向图较简单，通过不断删除(标记)度<=1的顶点及依附于这个顶点
 *   的边(注意这里删除的标准是无向图顶点的度，任何依附于一个顶点的边都是该顶点
 *   的一个度)，最后若顶点都删除(标记)完毕，则不存在环，否则存在环。
 *   有向图较复杂，方法多样。(1)利用拓扑排序，排序输出完毕，仍存在节点未打印出
 *   来，则说明有环。(2)在DFS中对顶点进行0 1 2 三种状态标记，0表示未访问，1表示
 *   该顶点的后续顶点正在访问中，2表示该顶点所有出边及其后续顶点已经DFS访问完毕。
 *   若DFS遍历中访问到一个1状态顶点，则说明存在环。(3)将所有顶点都标记一个值，初
 *   始都为0，表示未访问过，在DFS中每深入一次，值+1，如A->B，遍历A时A值为1，则
 *   递归至遍历B时，则B值在A的基础上+1，为2。如果以A为起点的路径上的所有顶点都D
 *   FS遍历完毕，则将A标记为正无穷大。如果在DFS遍历中，遇到一个非无穷大值的顶点，
 *   则说明环存在。其实这种方法与(2)方法本质是一样的，因为此方法也是三种状态，0
 *   未访问，0< && <正无穷大表示此路径正在访问，正无穷大表示此路径访问完毕。
 * 4.拓扑排序TopologicalSort
 *   ① 拓扑：不关心物体的大小/类型/等额外信息，只研究物体内部各个部分或物体
 *   与物体之间的结构，形状，位置变换后其本身的性质的改变以及这期间的联系。
 *   ② 图的拓扑排序：在有向图中的顶点，在实际应用中存在明显的先后顺序，A点
 *   若不完成，B就无法完成，如A点代表穿鞋子，B点代表穿袜子，则B-->A，即必须
 *   先让B点完成才能进行A点的任务。拓扑排序则是要输出这样一个前后关系正确的
 *   顶点序列。如果图中任意两点间都存在前后顺序，则称此图的拓扑是全序的，且
 *   输出的顶点序列结果唯一。
 *   ③ 实现的方法：常用的有两种，分别是从出度和入度两个方面考虑。
 *   (1)入度：借助链表结构，在每次循环迭代中，找出一个入度为0的顶点进行输出或
 *   放入链表尾部，然后(模拟)删除这个点及依附此点的边。因为在每次循环迭代中，
 *   入度为0，说明了该顶点已经没有前驱顶点(事件),所以放入链表尾部记录。这种方
 *   法在进行拓扑排序的同时，也可以进行检测图中是否存在环。
 *   (2)出度：借助栈结构后入先出的性质和图的深度优先遍历DFS的递归性质。在每次
 *   递归完成之前，将顶点放入栈中。DFS的递归性质导致一条路径会一直走到尽头，
 *   即递归到最后的那一轮所到达的顶点A的出度一定是0，也即A是所有顺序点中最后
 *   完成的那个，将其记录压人栈中，然后退出当次递归退回上次的递归，此时所处理
 *   的是A的前驱顶点B，也将其压入栈中。如此，直到将所有顶点遍历完毕。栈中的序
 *   列即为结果。注意：利用DFS进行拓扑排序的一个前提是图确定是DAG。即利用DFS无
 *   法实现拓扑排序的同时验证图中是否有环。
 * 5.关键路径
 *   ① 关键路径的目的是辨别哪些是关键活动，以争取提高关键活动工效，缩短工期。
 *   因为工程的多个活动路径一般都可以并行的执行，所以整个工程的最短完成时间就
 *   取决于耗费最长时间的活动路径，这条耗费时间最长的活动路径就被成为关键路径。
 *   因此设定工程的工期耗费时间就是关键路径所消耗的时间。
 *   整个工程的完成于一个时间点，耗时越长，代表需要开始的越早，定义最早(必须)
 *   开始时间为e；此外，那些耗时较短的活动可以延缓执行，但是会有一个最晚开始
 *   时间，定义为l；顶点称为事件，而边称为活动。如一条边A->B，尾顶点A开始，就
 *   代表A->B这个边活动的开始，到达B后，A->B活动结束同时B事件开始。最早开始时
 *   间指从开始顶点到V顶点的最大路径值，最晚开始时间则等于以V为尾的边的头顶点
 *   的最晚开始时间减去边(活动)自身的权值。当e=l，则说明此活动为关键活动。很明
 *   显，关键路径上所有的点都是关键事件，所有边都是关键活动。
 *   如一个工程中有活动A 1->2->3耗时5，活动B 1->4->3耗时3，则1是开始点，3是结
 *   束点，A活动即为关键路径。整个工程的的最短工期为5，则A必须最早或说最晚在5天
 *   前开始，即e=l。而B的e=5，l=3，中间有一个时间余量5-3=2，即B不是关键活动，他
 *   的提早开始并不能缩短整个工程的时间消耗，活动的时间余量越多，其重要性越低。
 *   ② 在图中表现为入度为0的表示工程开始点，出度为0的表示工程结束点，关键路径
 *   为权值(权值代表消耗时间)累计值最大的路径。查找关键路径就是查找e = l的路径。
 *   因此查找关键路径，关键是确定各个活动的最早开始时间e和最晚开始时间l，而活动
 *   的最早/晚时间又由事件的最早/晚时间计算得出。
 *   ③ 每个顶点事件最早开始时间，越早越好，即能开始的时候就开始，因此每个顶点
 *   要尽量靠近开始的时间线e；最晚，越晚越好，即能不开始就不开始，因此每个顶点
 *   要尽量靠近结束的时间线l，到非开始的时候再开始。所以计算节点最早时间时可以
 *   从起始点开始，累计计算到结束点结束；计算最晚开始时间时，可以从结束点开始，
 *   累计计算到开始点结束。
 *   如现在有三个活动A->B->C->D A->E->C->D A->F->G->D三个，时间消耗：A->B 2 B->C 3
 *   C->D 1 A->E 5 E->C 1 E->D 2 A->F 3 F->G 3 G->D 3，A为开始点，D为结束点，则
 *  e线                                                      l线
 *   A                                                        D
 *   |-->B--->C->D                                A-->B--->C->|
 *   |----->E->C->D                              A----->E->C->|
 *   |--->F--->G--->D                          A--->F--->G--->|
 *时间------------------------------------------------------------------>从小到大
 *
 *   计算顶点最早开始时间，B为2 C为6 D为9 E为5  F为3 G为6  终点D好理解，但是中途的
 *   点如C，有B->C,E->C，则C最早的时间确定的规则是两者间越大越好，因为A->B耗时2，
 *   A->E耗时5，因为C既要以B为前驱，也要以E为前驱，所以无论如何也要等A->E这个较A->B
 *   慢的活动完成了C才能开始。
 *   计算顶点最晚开始时间，C=8-1=7，B=8-(1+3)=4，...，同理，对于起点A，是B，E，F的前
 *   驱，在图中即可看出，A拖的再晚，也要在B->A E->A F->A中选择时间值最小的，为0，这样
 *   才能保证耗时最长的那个活动路径A-F-G-D能够顺利完成。
 *   ④ 具体实现。
 *   两个辅助数组V_EARLIEST V_LASTIEST，分别记录每个顶点的最早开始时间和最晚开始时间，
 *   分别初始化为0和终点最早(晚)开始时间。
 *   基本思路：开始时间0确定->得出各顶点最早完成时间和最终完成时间->因为终点的最早开
 *   始时间其实也是最晚完成时间，从终点倒推，得出各顶点的最晚开始时间->得出各活动余量
 *   和关键路径。
 *   (1)计算事件最早开始时间，得出终点的最早开始时间。其实就是图的正向遍历扫描，遍历
 *   中，开始顶点为0，若每个尾顶点的最早开始时间+边的持续时间(权值) > 头顶点现有最早
 *   开始时间，则更新头顶点的最早开始时间。这里的遍历是顺向的，所以可以用DFS/BFS/拓扑
 *   排序等等。
 *   (2)计算事件最晚开始时间。其实是图的逆向遍历扫描，即从每条边的头顶点向尾顶点方向，
 *   终点向开始顶点方向遍历，终点最晚开始时间即是最早开始时间。相当于以l线为基准，若边
 *   的头顶点最晚开始时间-边的持续时间(权值) < 尾顶点现有的最晚开始时间，则更新尾顶点
 *   的最晚开始时间即可。正向逆向遍历，也体现了十字链表存储结构的优势。
 *   (3)再次正向遍历图，根据事件的最早/晚时间，计算出活动的最早/晚时间，如活动A->B，若
 *   满足尾顶点A的最早开始时间=头顶点B的最晚开始时间-边的权值，A->B即为关键路径。这样
 *   可以扩展判断的条件，即若尾顶点A的最晚开始时间+边的权值=头顶点最早开始时间，也可判
 *   断A->B为关键路径。
 *
 *                                                             2016年11月28日
 */

#define _DEBUG_CLOSE_
#include "../PublicForAlgorithms.h"

#define MAX_ARC_NAME_LEN 60
#define MAX_VERTEX_NUM 100
#define MAX_VERTEX_NAME_LEN 60
#define MAX_VERTEX_ADDR_LEN 100
#define MAX_MAX_MAX_VALUE 100000 /*用于检测有向图是否有环，代表无穷大*/

typedef int V_Position;   /*顶点位置*/
typedef int Power;        /*边权值*/
typedef int G_Type;/*图类型*/

//边信息类型
typedef struct
{
    char name[MAX_ARC_NAME_LEN];
    Power power;
}ArcInfo, *P_Arc_Info;

P_Arc_Info CreateOneArcInfo(Power p,char *name)
{
    P_Arc_Info new_info = (P_Arc_Info)malloc(sizeof(ArcInfo));
    if(new_info == NULL){ LINE_DEBUG("ArcInfo malloc failed"); return NULL; }
    new_info->power = p;
    strncpy(new_info->name,name,MAX_ARC_NAME_LEN);
    return new_info;
}

//边
typedef struct Edge
{
    bool if_visited;
    V_Position v_tail;     /*有向图中表示尾顶点位置，无向图中表示边的一个顶点位置*/
    V_Position v_head;     /*有向图中表示头顶点位置，无向图中表示边的另一个顶点位置*/
    struct Edge* arc_tail; /*有向图中表示出边链表的下一条边，无向图中表示依附于顶点的下一条边*/
    struct Edge* arc_head; /*有向图中表示入边链表的下一条边，无向图中表示依附于另一个顶点的下一条边*/
    P_Arc_Info info;       /*边信息*/
}ArcNode, *P_ArcNode;

P_ArcNode CreateOneArc(P_Arc_Info info)
{
    P_ArcNode new_arc = (P_ArcNode)malloc(sizeof(ArcNode));
    if(new_arc == NULL){ LINE_DEBUG("ArcNode malloc failed"); return NULL; }
    new_arc->if_visited = false; new_arc->info = info;
    new_arc->v_tail = -1; new_arc->arc_tail = NULL;
    new_arc->v_head = -1; new_arc->arc_head = NULL;
    return new_arc;
}

//顶点数据类型
typedef struct
{
    int  id;
    char name[MAX_VERTEX_NAME_LEN];
    char address[MAX_VERTEX_ADDR_LEN];
}V_Data, *P_V_Data_Type;

P_V_Data_Type CreateOneVertexData(int id,char *n,char *addr)
{
    P_V_Data_Type new_data = (P_V_Data_Type)malloc(sizeof(V_Data));
    if(new_data == NULL){ LINE_DEBUG("V data malloc failed"); return NULL; }
    new_data->id = id;
    strncpy(new_data->name,n,MAX_VERTEX_NAME_LEN);
    strncpy(new_data->address,addr,MAX_VERTEX_ADDR_LEN);
    return new_data;
}

//点
typedef struct
{
    P_V_Data_Type data;      /*顶点数据*/
    P_ArcNode arc_first_in;  /*有向图中表示顶点的第一条入边，无向图不使用此字段*/
    P_ArcNode arc_first_out; /*有向图中表示顶点的第一条出边，无向图中表示顶点的第一条边*/
}VertexNode, *P_VertexNode;

//顶点访问辅助标识
bool V_VISITED_FLAGS[MAX_VERTEX_NUM];

//顶点处理函数
void Vertex_Handle()
{
    //do nothing
}

P_VertexNode CreateOneVertex(P_V_Data_Type data)
{
    P_VertexNode new_v = (P_VertexNode)malloc(sizeof(VertexNode));
    if(new_v == NULL){ LINE_DEBUG("VertexNode malloc failed"); return NULL; }
    new_v->data = data;
    new_v->arc_first_in = NULL; new_v->arc_first_out = NULL;
    return new_v;
}

//图
typedef struct
{
    G_Type g_type;
    P_VertexNode v_list[MAX_VERTEX_NUM];
    int v_num; int arc_num;
}Graphics, *P_Graphics;

//链表/栈结点
typedef struct Node
{
    V_Position v_p;
    struct Node* next;
}Node,*P_Node;

//链表/栈
typedef struct
{
    P_Node head;
    P_Node tail;
    int node_num;
}Form,*P_Form;

P_Node CreateOneNode(V_Position v)
{
    P_Node new_node = (P_Node)malloc(sizeof(Node));
    if(new_node == NULL){ LINE_DEBUG("CreateOneFormNode malloc failed"); return NULL; }
    new_node->v_p = v;
    new_node->next = NULL;
    return new_node;
}

P_Form CreateOneForm()
{
    P_Form new_form = (P_Form)malloc(sizeof(Form));
    if(new_form == NULL){ LINE_DEBUG("CreateOneForm malloc failed"); return NULL; }
    new_form->head = NULL; new_form->tail = NULL; new_form->node_num = 0;
    return new_form;
}
//用于链表
void InsertListNode(P_Form list,P_Node node)
{
    if(list == NULL || node == NULL)
    { LINE_DEBUG("InsertFormNode arguments or illegal"); return; }
    if(list->head == NULL){ list->head = node; list->tail = node; }
    else{ list->tail->next = node; list->tail = node; }
    ++(list->node_num);
}
//用于栈
void InsertStackNode(P_Form stack,P_Node node)
{
    if(stack == NULL || node == NULL)
    { LINE_DEBUG("InsertFormNode arguments or illegal"); return; }
    if(stack->head == NULL){ stack->head = node; stack->tail = node; }
    else{ node->next = stack->head; stack->head = node; }
    ++(stack->node_num);
}

void FormFree(P_Form form)
{
    if(form == NULL || form->head == NULL){ return; }
    P_Node temp_node = NULL;
    while(form->head)
    {
	temp_node = form->head;
	form->head = form->head->next;
	SAFE_FREE(temp_node);
    }
    temp_node = NULL;
    SAFE_FREE(form);
}

/*  AOV网
 *  用于拓扑排序用
 *
 *     0       7
 *     |       |
 * 1---2---3---8---9
 *    /|\     /|\
 *   / | \   / | \
 *  /  |  \ /  |  \
 * 4   5   6   10  11
 *
 * 0->2 2->1 2->3 2->4 2->6 5->2
 * 8->7 8->10 3->8 9->8 6->8 11->8
 */
P_Graphics CreateDigraphOne()
{
    //声明点数据，边信息，点，边，图
    P_Arc_Info info0_2 = NULL;  P_Arc_Info info2_1 = NULL; P_Arc_Info info2_3 = NULL; P_Arc_Info info2_4 = NULL;
    P_Arc_Info info2_6 = NULL;  P_Arc_Info info5_2 = NULL; P_Arc_Info info8_7 = NULL; P_Arc_Info info8_10 = NULL;
    P_Arc_Info info3_8 = NULL; P_Arc_Info info9_8  = NULL; P_Arc_Info info6_8 = NULL; P_Arc_Info info11_8 = NULL;
    P_ArcNode Arc0_2  = NULL; P_ArcNode Arc2_1 = NULL; P_ArcNode Arc2_3  = NULL; P_ArcNode Arc2_4 = NULL;
    P_ArcNode Arc2_6  = NULL; P_ArcNode Arc5_2 = NULL; P_ArcNode Arc8_7  = NULL; P_ArcNode Arc8_10 = NULL;
    P_ArcNode Arc3_8  = NULL; P_ArcNode Arc9_8 = NULL; P_ArcNode Arc6_8  = NULL; P_ArcNode Arc11_8 = NULL;
    P_V_Data_Type data0 = NULL; P_V_Data_Type data1 = NULL; P_V_Data_Type data2 = NULL; P_V_Data_Type data3 = NULL;
    P_V_Data_Type data4 = NULL; P_V_Data_Type data5 = NULL; P_V_Data_Type data6 = NULL; P_V_Data_Type data7 = NULL;
    P_V_Data_Type data8 = NULL; P_V_Data_Type data9 = NULL; P_V_Data_Type data10 = NULL; P_V_Data_Type data11 = NULL;
    P_VertexNode V0 = NULL; P_VertexNode V1 = NULL; P_VertexNode V2 = NULL; P_VertexNode V3 = NULL;
    P_VertexNode V4 = NULL; P_VertexNode V5 = NULL; P_VertexNode V6 = NULL; P_VertexNode V7 = NULL;
    P_VertexNode V8 = NULL; P_VertexNode V9 = NULL; P_VertexNode V10 = NULL; P_VertexNode V11 = NULL;
    P_Graphics new_digraph = NULL;
    //创建边信息
    info0_2 = CreateOneArcInfo(8,"V0->V2");  info2_1  = CreateOneArcInfo(17,"V2->V1");
    info2_3 = CreateOneArcInfo(15,"V2->V3"); info2_4  = CreateOneArcInfo(-18,"V2->V4");
    info2_6 = CreateOneArcInfo(3,"V2->V6");  info5_2  = CreateOneArcInfo(30,"V5->V2");
    info8_7 = CreateOneArcInfo(-1,"V8->V7"); info8_10 = CreateOneArcInfo(10,"V8->V10");
    info3_8 = CreateOneArcInfo(-8,"V3->V8"); info9_8  = CreateOneArcInfo(25,"V9->V8");
    info6_8 = CreateOneArcInfo(10,"V6->V8"); info11_8 = CreateOneArcInfo(3,"V11->V8");
    if(info0_2 == NULL || info2_1 == NULL || info2_3 == NULL || info2_4 == NULL
    || info2_6 == NULL || info5_2 == NULL || info8_7 == NULL || info8_10 == NULL
    || info3_8 == NULL || info9_8 == NULL || info6_8 == NULL || info11_8 == NULL)
    { LINE_DEBUG("ArcInfo Create failed"); goto Label_CreateDigraphOne_Clean;}
    //创建边
    Arc0_2 = CreateOneArc(info0_2); Arc2_1  = CreateOneArc(info2_1);
    Arc2_3 = CreateOneArc(info2_3); Arc2_4  = CreateOneArc(info2_4);
    Arc2_6 = CreateOneArc(info2_6); Arc5_2  = CreateOneArc(info5_2);
    Arc8_7 = CreateOneArc(info8_7); Arc8_10 = CreateOneArc(info8_10);
    Arc3_8 = CreateOneArc(info3_8); Arc9_8  = CreateOneArc(info9_8);
    Arc6_8 = CreateOneArc(info6_8); Arc11_8 = CreateOneArc(info11_8);
    if(Arc0_2 == NULL || Arc2_1  == NULL || Arc2_3 == NULL || Arc2_4  == NULL
    || Arc2_6 == NULL || Arc5_2  == NULL || Arc8_7 == NULL || Arc8_10 == NULL
    || Arc3_8 == NULL || Arc9_8  == NULL || Arc6_8 == NULL || Arc11_8 == NULL)
    { LINE_DEBUG("ArcNode Create failed"); goto Label_CreateDigraphOne_Clean; }
    //创建点数据
    data0 = CreateOneVertexData(0,"V0","地址0"); data1 = CreateOneVertexData(1,"V1","地址1"); 
    data2 = CreateOneVertexData(2,"V2","地址2"); data3 = CreateOneVertexData(3,"V3","地址3");
    data4 = CreateOneVertexData(4,"V4","地址4"); data5 = CreateOneVertexData(5,"V5","地址5");
    data6 = CreateOneVertexData(6,"V6","地址6"); data7 = CreateOneVertexData(7,"V7","地址7");
    data8 = CreateOneVertexData(8,"V8","地址8"); data9 = CreateOneVertexData(9,"V9","地址9");
    data10 = CreateOneVertexData(10,"V10","地址10"); data11 = CreateOneVertexData(11,"V11","地址11");
    if(data0 == NULL || data1 == NULL || data2 == NULL || data3 == NULL
    || data4 == NULL || data5 == NULL || data6 == NULL || data7 == NULL
    || data8 == NULL || data9 == NULL || data10 == NULL|| data11 == NULL)
    { LINE_DEBUG("VertexData Create failed"); goto Label_CreateDigraphOne_Clean; }
    //创建点
    V0 = CreateOneVertex(data0); V1 = CreateOneVertex(data1); V2 = CreateOneVertex(data2);
    V3 = CreateOneVertex(data3); V4 = CreateOneVertex(data4); V5 = CreateOneVertex(data5);
    V6 = CreateOneVertex(data6); V7 = CreateOneVertex(data7); V8 = CreateOneVertex(data8);
    V9 = CreateOneVertex(data9); V10 = CreateOneVertex(data10); V11 = CreateOneVertex(data11);
    if(V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL || V4 == NULL || V5 == NULL
    || V6 == NULL || V7 == NULL || V8 == NULL || V9 == NULL || V10 == NULL|| V11 == NULL)
    { LINE_DEBUG("Vertex Create failed"); goto Label_CreateDigraphOne_Clean; }
    //创建图
    new_digraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_digraph == NULL){ LINE_DEBUG("Graphics malloc failed"); goto Label_CreateDigraphOne_Clean; }
    
    //关系组织
    Arc0_2->v_tail = 0; Arc0_2->v_head = 2; Arc0_2->arc_tail = NULL;   Arc0_2->arc_head = Arc5_2;
    Arc2_1->v_tail = 2; Arc2_1->v_head = 1; Arc2_1->arc_tail = Arc2_3; Arc2_1->arc_head = NULL;
    Arc2_3->v_tail = 2; Arc2_3->v_head = 3; Arc2_3->arc_tail = Arc2_4; Arc2_3->arc_head = NULL;
    Arc2_4->v_tail = 2; Arc2_4->v_head = 4; Arc2_4->arc_tail = Arc2_6; Arc2_4->arc_head = NULL;
    Arc2_6->v_tail = 2; Arc2_6->v_head = 6; Arc2_6->arc_tail = NULL;   Arc2_6->arc_head = NULL;
    Arc5_2->v_tail = 5; Arc5_2->v_head = 2; Arc5_2->arc_tail = NULL;   Arc5_2->arc_head = NULL;
    Arc8_7->v_tail = 8; Arc8_7->v_head = 7; Arc8_7->arc_tail = Arc8_10;Arc8_7->arc_head = NULL; 
    Arc3_8->v_tail = 3; Arc3_8->v_head = 8; Arc3_8->arc_tail = NULL; Arc3_8->arc_head = Arc9_8;
    Arc9_8->v_tail = 9; Arc9_8->v_head = 8; Arc9_8->arc_tail = NULL; Arc9_8->arc_head = Arc6_8;
    Arc6_8->v_tail = 6; Arc6_8->v_head = 8; Arc6_8->arc_tail = NULL; Arc6_8->arc_head = Arc11_8;  
    Arc8_10->v_tail = 8; Arc8_10->v_head = 10; Arc8_10->arc_tail = NULL; Arc8_10->arc_head = NULL;
    Arc11_8->v_tail = 11; Arc11_8->v_head = 8; Arc11_8->arc_tail = NULL; Arc11_8->arc_head = NULL;
    V0->arc_first_out = Arc0_2; V1->arc_first_out = NULL; V2->arc_first_out = Arc2_1;
    V3->arc_first_out = Arc3_8; V4->arc_first_out = NULL; V5->arc_first_out = Arc5_2;
    V6->arc_first_out = Arc6_8; V7->arc_first_out = NULL; V8->arc_first_out = Arc8_7;
    V9->arc_first_out = Arc9_8; V10->arc_first_out = NULL; V11->arc_first_out = Arc11_8;
    V0->arc_first_in = NULL;   V1->arc_first_in = Arc2_1; V2->arc_first_in = Arc0_2;
    V3->arc_first_in = Arc2_3; V4->arc_first_in = Arc2_4; V5->arc_first_in = NULL;
    V6->arc_first_in = Arc2_6; V7->arc_first_in = Arc8_7; V8->arc_first_in = Arc3_8;
    V9->arc_first_in = NULL;   V10->arc_first_in = Arc8_10; V11->arc_first_in = NULL;
    new_digraph->v_num = 12; new_digraph->arc_num = 12; new_digraph->g_type = (DIGRAPH | ACYCLIC);
    new_digraph->v_list[0] = V0; new_digraph->v_list[1] = V1;
    new_digraph->v_list[2] = V2; new_digraph->v_list[3] = V3;
    new_digraph->v_list[4] = V4; new_digraph->v_list[5] = V5;
    new_digraph->v_list[6] = V6; new_digraph->v_list[7] = V7;
    new_digraph->v_list[8] = V8; new_digraph->v_list[9] = V9;
    new_digraph->v_list[10] = V10; new_digraph->v_list[11] = V11;

    return new_digraph;

Label_CreateDigraphOne_Clean:
    SAFE_FREE(info0_2); SAFE_FREE(info2_1); SAFE_FREE(info2_3); SAFE_FREE(info2_4);
    SAFE_FREE(info2_6); SAFE_FREE(info5_2); SAFE_FREE(info8_7); SAFE_FREE(info8_10);
    SAFE_FREE(info3_8); SAFE_FREE(info9_8); SAFE_FREE(info6_8); SAFE_FREE(info11_8);
    SAFE_FREE(Arc0_2); SAFE_FREE(Arc2_1); SAFE_FREE(Arc2_3); SAFE_FREE(Arc2_4);
    SAFE_FREE(Arc2_6); SAFE_FREE(Arc5_2); SAFE_FREE(Arc8_7); SAFE_FREE(Arc8_10);
    SAFE_FREE(Arc3_8); SAFE_FREE(Arc9_8); SAFE_FREE(Arc6_8); SAFE_FREE(Arc11_8);
    SAFE_FREE(data0); SAFE_FREE(data1); SAFE_FREE(data2); SAFE_FREE( data3);
    SAFE_FREE(data4); SAFE_FREE(data5); SAFE_FREE(data6); SAFE_FREE( data7);
    SAFE_FREE(data8); SAFE_FREE(data9); SAFE_FREE(data10);SAFE_FREE(data11);
    SAFE_FREE(V0); SAFE_FREE(V1); SAFE_FREE(V2); SAFE_FREE( V3); SAFE_FREE(V4); SAFE_FREE(V5);
    SAFE_FREE(V6); SAFE_FREE( V7); SAFE_FREE(V8); SAFE_FREE(V9); SAFE_FREE(V10);SAFE_FREE(V11);
    SAFE_FREE(new_digraph);
    return NULL;
}

/* AOE图
 * 供关键路径算法使用
 * 
 *   0--1--4      权值，表示活动耗时
 *   |  |  |      0->1 3   0->2 2   1->3 2   1->4 3
 *   |  3  |      2->3 4   2->5 3   3->5 2   4->5 1
 *   | / \ |      
 *   2-----5
 */
P_Graphics CreateDigraphTwo(void)
{
    //声明点数据，边信息，点，边，图
    P_Arc_Info info0_1 = NULL; P_Arc_Info info0_2 = NULL; P_Arc_Info info1_3 = NULL; P_Arc_Info info1_4 = NULL;
    P_Arc_Info info2_3 = NULL; P_Arc_Info info2_5 = NULL; P_Arc_Info info3_5 = NULL; P_Arc_Info info4_5 = NULL;
    P_ArcNode Arc0_2  = NULL; P_ArcNode Arc0_1 = NULL; P_ArcNode Arc2_3  = NULL; P_ArcNode Arc1_4 = NULL;
    P_ArcNode Arc1_3  = NULL; P_ArcNode Arc2_5 = NULL; P_ArcNode Arc3_5  = NULL; P_ArcNode Arc4_5 = NULL;
    P_V_Data_Type data0 = NULL; P_V_Data_Type data1 = NULL; P_V_Data_Type data2 = NULL; P_V_Data_Type data3 = NULL;
    P_V_Data_Type data4 = NULL; P_V_Data_Type data5 = NULL;
    P_VertexNode V0 = NULL; P_VertexNode V1 = NULL; P_VertexNode V2 = NULL; P_VertexNode V3 = NULL;
    P_VertexNode V4 = NULL; P_VertexNode V5 = NULL;
    P_Graphics new_digraph = NULL;
    //创建边信息
    info0_2 = CreateOneArcInfo(2,"V0->V2"); info0_1 = CreateOneArcInfo(3,"V0->V1");
    info2_3 = CreateOneArcInfo(4,"V2->V3"); info1_4 = CreateOneArcInfo(3,"V1->V4");
    info1_3 = CreateOneArcInfo(2,"V1->V3"); info2_5 = CreateOneArcInfo(3,"V2->V5");
    info3_5 = CreateOneArcInfo(2,"V3->V5"); info4_5 = CreateOneArcInfo(1,"V4->V5");
    if(info0_2 == NULL || info0_1 == NULL || info2_3 == NULL || info1_4 == NULL
    || info1_3 == NULL || info2_5 == NULL || info3_5 == NULL || info4_5 == NULL)
    { LINE_DEBUG("ArcInfo Create failed"); goto Label_CreateDigraphTwo_Clean;}
    //创建边
    Arc0_2 = CreateOneArc(info0_2); Arc0_1  = CreateOneArc(info0_1);
    Arc2_3 = CreateOneArc(info2_3); Arc1_4  = CreateOneArc(info1_4);
    Arc1_3 = CreateOneArc(info1_3); Arc2_5  = CreateOneArc(info2_5);
    Arc3_5 = CreateOneArc(info3_5); Arc4_5 = CreateOneArc(info4_5);
    if(Arc0_2 == NULL || Arc0_1  == NULL || Arc2_3 == NULL || Arc1_4  == NULL
    || Arc1_3 == NULL || Arc2_5  == NULL || Arc3_5 == NULL || Arc4_5 == NULL)
    { LINE_DEBUG("ArcNode Create failed"); goto Label_CreateDigraphTwo_Clean; }
    //创建点数据
    data0 = CreateOneVertexData(0,"V0","地址0"); data1 = CreateOneVertexData(1,"V1","地址1"); 
    data2 = CreateOneVertexData(2,"V2","地址2"); data3 = CreateOneVertexData(3,"V3","地址3");
    data4 = CreateOneVertexData(4,"V4","地址4"); data5 = CreateOneVertexData(5,"V5","地址5");
    if(data0 == NULL || data1 == NULL || data2 == NULL || data3 == NULL
    || data4 == NULL || data5 == NULL)
    { LINE_DEBUG("VertexData Create failed"); goto Label_CreateDigraphTwo_Clean; }
    //创建点
    V0 = CreateOneVertex(data0); V1 = CreateOneVertex(data1); V2 = CreateOneVertex(data2);
    V3 = CreateOneVertex(data3); V4 = CreateOneVertex(data4); V5 = CreateOneVertex(data5);
    if(V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL || V4 == NULL || V5 == NULL)
    { LINE_DEBUG("Vertex Create failed"); goto Label_CreateDigraphTwo_Clean; }
    //创建图
    new_digraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_digraph == NULL){ LINE_DEBUG("Graphics malloc failed"); goto Label_CreateDigraphTwo_Clean; }
    
    //关系组织
    Arc0_1->v_tail = 0; Arc0_1->v_head = 1; Arc0_1->arc_tail = Arc0_2; Arc0_1->arc_head = NULL;
    Arc0_2->v_tail = 0; Arc0_2->v_head = 2; Arc0_2->arc_tail = NULL;   Arc0_2->arc_head = NULL;
    Arc1_3->v_tail = 1; Arc1_3->v_head = 3; Arc1_3->arc_tail = Arc1_4; Arc1_3->arc_head = Arc2_3;
    Arc1_4->v_tail = 1; Arc1_4->v_head = 4; Arc1_4->arc_tail = NULL;   Arc1_4->arc_head = NULL;
    Arc2_3->v_tail = 2; Arc2_3->v_head = 3; Arc2_3->arc_tail = Arc2_5; Arc2_3->arc_head = NULL;
    Arc2_5->v_tail = 2; Arc2_5->v_head = 5; Arc2_5->arc_tail = NULL;   Arc2_5->arc_head = Arc3_5;
    Arc3_5->v_tail = 3; Arc3_5->v_head = 5; Arc3_5->arc_tail = NULL;   Arc3_5->arc_head = Arc4_5;  
    Arc4_5->v_tail = 4; Arc4_5->v_head = 5; Arc4_5->arc_tail = NULL;   Arc4_5->arc_head = NULL;
    V0->arc_first_out = Arc0_1; V1->arc_first_out = Arc1_3; V2->arc_first_out = Arc2_3;
    V3->arc_first_out = Arc3_5; V4->arc_first_out = Arc4_5; V5->arc_first_out = NULL;
    V0->arc_first_in = NULL;   V1->arc_first_in = Arc0_1; V2->arc_first_in = Arc0_2;
    V3->arc_first_in = Arc1_3; V4->arc_first_in = Arc1_4; V5->arc_first_in = Arc2_5;
    new_digraph->v_num = 6; new_digraph->arc_num = 8; new_digraph->g_type = (DIGRAPH | ACYCLIC);
    new_digraph->v_list[0] = V0; new_digraph->v_list[1] = V1;
    new_digraph->v_list[2] = V2; new_digraph->v_list[3] = V3;
    new_digraph->v_list[4] = V4; new_digraph->v_list[5] = V5;

    return new_digraph;

Label_CreateDigraphTwo_Clean:
    SAFE_FREE(info0_2); SAFE_FREE(info0_1); SAFE_FREE(info2_3); SAFE_FREE(info1_4);
    SAFE_FREE(info1_3); SAFE_FREE(info2_5); SAFE_FREE(info3_5); SAFE_FREE(info4_5);
    SAFE_FREE(Arc0_2); SAFE_FREE(Arc0_1); SAFE_FREE(Arc2_3); SAFE_FREE(Arc1_4);
    SAFE_FREE(Arc1_3); SAFE_FREE(Arc2_5); SAFE_FREE(Arc3_5); SAFE_FREE(Arc4_5);
    SAFE_FREE(data0); SAFE_FREE(data1); SAFE_FREE(data2); SAFE_FREE( data3);
    SAFE_FREE(data4); SAFE_FREE(data5);
    SAFE_FREE(V0); SAFE_FREE(V1); SAFE_FREE(V2); SAFE_FREE( V3); SAFE_FREE(V4); SAFE_FREE(V5);
    SAFE_FREE(new_digraph);
    return NULL;
}

/*利用数值法对图是否有环进行检测
 *用三种状态的方法*/
void Graphics_Is_DAG(P_Graphics G,V_Position s_p)
{
    V_VISITED_FLAGS[s_p] = 1;
    P_ArcNode arc = G->v_list[s_p]->arc_first_out;
    while(arc)
    {
	/*如果遇到状态为1的顶点，说明这条边指回了还在遍历中的路径的之前的顶点，必定存在环*/
	if(V_VISITED_FLAGS[arc->v_head] == 1)
	{
	    G->g_type = (DIGRAPH | CYCLIC);
	    printf("有向图存在环，利用DFS进行的拓扑排序显示结果无效\n"); 
	    return;
	}
	if(V_VISITED_FLAGS[arc->v_head] == 0)
	{ Graphics_Is_DAG(G,arc->v_head); }
	arc = arc->arc_tail;
    }
    /*s_p顶点所有出边的深度优先遍历完毕，置为状态2*/
    V_VISITED_FLAGS[s_p] = 2;
}

/* 出度：利用深度优先搜索进行拓扑排序 
 * 注意使用的前提是传入的G为DAG，且不能同时进行环测试*/
void DFS(P_Graphics G,V_Position s_p,P_Form stack)
{
    /*不使用栈而使用链表，在此(未进入下一轮递归前)将没有被访问过的点插入链表中，也可以*/
    /*if(V_VISITED_FLAGS[s_p] == false){ node = CreateOneNode(s_p); InsertListNode(node); }*/
    V_VISITED_FLAGS[s_p] = true;
    
    P_ArcNode arc = G->v_list[s_p]->arc_first_out;
    while(arc)
    {
	if(V_VISITED_FLAGS[arc->v_head] == false)
	{
	    DFS(G,arc->v_head,stack);
	    /*到达路径的最深处递归完成，将v_head压入栈中 */
	    P_Node node = CreateOneNode(arc->v_head);
	    InsertStackNode(stack,node);
	}
	/*换一条边(路径)继续*/
	arc = arc->arc_tail;
    }
}

void GraphicsDFS_TopologicalSort(P_Graphics G,V_Position s_p,P_Form stack)
{
    if(G == NULL){ LINE_DEBUG("DFS_TopologicalSort G is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("DFS_TopologicalSort s_p is illegal"); return; }
    if(stack == NULL){ LINE_DEBUG("DFS_TopologicalSort stack is NULL"); return; }
    int i = 0;
    while(i < G->v_num){ V_VISITED_FLAGS[i] = false; ++i; }
    /*检测是否有环*/
    Graphics_Is_DAG(G,0);
    if(G->g_type == (DIGRAPH | CYCLIC)){ printf("G is not a DAG\n"); return; }
    i = 0;
    while(i < G->v_num){ V_VISITED_FLAGS[i] = false; ++i; }
    
    /*起始顶点不重要，借助此循环，即便重顺序链中的中间的某个顶点V开始深度
     *遍历，其前驱顶点最终也会在Stack中排到V前面，其他顺序分支的前驱顶点也
     *会排到其前面*/
    i = s_p;
    while(i < G->v_num)
    {
	if(V_VISITED_FLAGS[i] == false)
	{ 
	    DFS(G,i,stack);
	    /*将开始的节点插入栈中，在DFS中(因栈的插入代码须所处位置)无法将起点插入栈中*/
	    P_Node node = CreateOneNode(i);
	    InsertStackNode(stack,node);
	}
	++i;
    }
    i = 0;
    while(i < s_p)
    {
	if(V_VISITED_FLAGS[i] == false)
	{
	    DFS(G,i,stack);
	    P_Node node = CreateOneNode(i);
	    InsertStackNode(stack,node);
	}
	++i;
    }
}

/* 入度：寻找入度为0的顶点
 * 对入度为0的点不进行真正的删除，而是进行标记。这里借助V_VISITED_FLAGS
 * 进行标识，只是所存储的不再代表对应顶点是否访问过，而是对应顶点的实时
 * 入度边数。
 * 输入的图可以是非DAG，同时进行环测试。
 */
V_Position GetZeroIndegreeVertex(P_Graphics G,V_Position s_p)
{
    int i = s_p;
    while(i < G->v_num)
    {
	if(V_VISITED_FLAGS[i] == 0)
	{
	    /*将i顶点所有出边的头顶点入度-1，相当于删除了i的所有出边*/
	    P_ArcNode arc = G->v_list[i]->arc_first_out;
	    while(arc)
	    {
		--(V_VISITED_FLAGS[arc->v_head]);
		arc = arc->arc_tail;
	    }
	    /*将i顶点自身减1变为-1，以标识其已经被排序过*/
	    --(V_VISITED_FLAGS[i]);
	    return i;
	}
	++i;
    }
    i = 0;
    while(i < s_p)
    {
	if(V_VISITED_FLAGS[i] == 0)
	{
	    P_ArcNode arc = G->v_list[i]->arc_first_out;
	    while(arc)
	    {
		--(V_VISITED_FLAGS[arc->v_head]);
		arc = arc->arc_tail;
	    }
	    --(V_VISITED_FLAGS[i]);
	    return i;
	}
	++i;
    }
    /*若不存在入度为0的点，则返回-1*/
    return -1;
}

/*获取出度为0的顶点*/
V_Position GetZeroOutdegreeVertex(P_Graphics G,V_Position s_p)
{
    int i = s_p;
    while(i < G->v_num)
    {
	if(V_VISITED_FLAGS[i] == 0)
	{
	    P_ArcNode arc = G->v_list[i]->arc_first_in;
	    /*删除(标记)i顶点所有的入边*/
	    while(arc)
	    {
		--(V_VISITED_FLAGS[arc->v_tail]);
		arc = arc->arc_head;
	    }
	    --(V_VISITED_FLAGS[i]);
	    return i;
	}
	++i;
    }
    i = 0;
    while(i < s_p)
    {
	if(V_VISITED_FLAGS[i] == 0)
	{
	    P_ArcNode arc = G->v_list[i]->arc_first_in;
	    /*删除(标记)i顶点所有的入边*/
	    while(arc)
	    {
		--(V_VISITED_FLAGS[arc->v_tail]);
		arc = arc->arc_head;
	    }
	    --(V_VISITED_FLAGS[i]);
	    return i;
	}
	++i;
    }
    return -1;
}

void GraphicsZeroIndgreeTopologicalSort(P_Graphics G,V_Position s_p,P_Form list)
{
    if(G == NULL){ LINE_DEBUG("GraphicsZeroIndgreeTopologicalSort G is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num)
    { LINE_DEBUG("GraphicsZeroIndgreeTopologicalSort s_p is illegal"); return; }
    if(list == NULL){ LINE_DEBUG("GraphicsZeroIndgreeTopologicalSort list is NULL"); return; }
    int i = 0; int count; V_Position zero_v;
    while(i < G->v_num){ V_VISITED_FLAGS[i] = false; ++i; }
    /*检测是否有环*/
    Graphics_Is_DAG(G,0);
    if(G->g_type == (DIGRAPH | CYCLIC)){ LINE_DEBUG("GraphicsZeroIndgreeTopologicalSort G is not a DAG"); return; }
    
    /*初始化V_VISITED_FLAGS对应的最初的入度数*/
    i = 0;
    while(i < G->v_num)
    {
	/*计数器*/
	count = 0;
	P_ArcNode arc = G->v_list[i]->arc_first_in;
	while(arc){ ++count; arc = arc->arc_head; }
	V_VISITED_FLAGS[i] = count;
	++i;
    }
    /*开始拓扑排序，只需循环G->v_num遍即可*/
    i = 0;
    count = 0;
    while(i < G->v_num)
    {
	/*获取一个0入度顶点位置*/
	zero_v = GetZeroIndegreeVertex(G,s_p);
	/*如果返回的为-1，则说明未取到入度为0的顶点，说明存在环*/
	if(zero_v > -1)
	{
	    ++count;/*每插入一个入度为0的顶点，计数一次*/
	    P_Node node = CreateOneNode(zero_v);
	    InsertListNode(list,node);
	}
	++i;
    }
    /*如果所有的0入度顶点数少于G的顶点数，说明G中存在入度不可能为0的点，即图中存在环
     *这就是利用拓扑排序进行环的检测的方法*/
    if(count < G->v_num)
    { LINE_DEBUG("GraphicsZeroIndgreeTopologicalSort G is not a DAG"); }
}

/*深度优先方法进行的拓扑排序除非输入的图为DAG，否则输出结果不正确*/
void GraphicsTopologicalSortShow(P_Graphics G,P_Form form)
{
    if(G == NULL){ LINE_DEBUG("GraphicsTopologicalSortShow is NULL"); return; }
    if(form == NULL || form->head == NULL){ LINE_DEBUG("GraphicsTopologicalSortShow form is NULL"); return; }
    printf("有向无环图拓扑排序结果如下：\n");
    P_Node temp_head = form->head;
    while(temp_head != NULL)
    {
	printf("%s",G->v_list[temp_head->v_p]->data->name);
	temp_head = temp_head->next;
	if(temp_head != NULL){ printf(" ---> "); }
    }
    printf("\n");
    if(form->node_num == G->v_num){ printf("图中不存在环\n"); }
    else { printf("图中存在环\n"); }
}

/*辅助数组，存储顶点的最早/晚完成时间*/
int V_EARLIEST[MAX_VERTEX_NUM];
int V_LASTIEST[MAX_VERTEX_NUM];

/*搜寻图的关键路径
 * s_p 图的起始顶点位置*/
void Graphics_CriticalPath(P_Graphics G,V_Position s_p)
{
    /*参数检测*/
    if(G == NULL){ LINE_DEBUG("Graphics_CriticalPath G is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("Graphics_CriticalPath s_p is illegal"); return; }
    if(G->v_list[s_p]->arc_first_in != NULL)
    { LINE_DEBUG("Graphics_CriticalPath s_p is G's start vertex"); return; }
    /*检测是否有环*/
    Graphics_Is_DAG(G,0);
    if(G->g_type == (DIGRAPH | CYCLIC)){ printf("G is not a DAG\n"); return; }
    
    int i = 0;
    /*将V_EARLIEST的值初始化为0，相当于e线的值*/
    for(i = 0; i < G->v_num; ++i){ V_VISITED_FLAGS[i] = 0; V_EARLIEST[i] = 0; }
    /*计算事件最早开始时间*/
    /*初始化V_VISITED_FLAGS对应的最初的入度数*/
    int count = 0;
    P_ArcNode arc = NULL;
    for(i = 0; i < G->v_num; ++i)
    {
	/*计数器*/
	count = 0;
	arc = G->v_list[i]->arc_first_in;
	while(arc){ ++count; arc = arc->arc_head; }
	V_VISITED_FLAGS[i] = count;
    }

    V_Position zero_v;
    /*正向遍历图，这里用的方法类似拓扑排序的遍历方法，每次取出入度为0的一个点，若知道图的开始点
     *则普通的遍历也可*/
    for(i = 0; i < G->v_num; ++i)
    {
	/*获取一个0入度顶点位置*/
	zero_v = GetZeroIndegreeVertex(G,s_p);
	/*如果返回的为-1，则说明未取到入度为0的顶点，说明存在环*/
	if(zero_v > -1)
	{
	    /*这里的zero_v作为尾顶点进行遍历*/
	    arc = G->v_list[zero_v]->arc_first_out;
	    while(arc)
	    {
		/*如果尾顶点的最早开始时间+边活动的持续时间(权值) > 头顶点的最早开始时间，则赋值*/
		if((V_EARLIEST[zero_v] + arc->info->power) > V_EARLIEST[arc->v_head])
		{ V_EARLIEST[arc->v_head] = V_EARLIEST[zero_v] + arc->info->power; }
		arc = arc->arc_tail;
	    }
	    
	    /*
	    //另一种方法是作为尾顶点进行遍历，去计算其头顶点的最早开始时间
	    arc = G->v_list[zero_v]->arc_first_in;
	    while(arc)
	    {
		if((V_EARLIEST[arc->v_tail] + arc->info->power) > V_EARLIEST[zero_v])
		{ V_EARLIEST[zero_v] = V_EARLIEST[arc->v_tail] + arc->info->power; }
		arc = arc->arc_head;
	    }
	    */
	}
    }
    
    /*计算最晚开始时间*/
    /*将V_LASTIEST的值都初始化为整个工程最大的花费值，相当于l线的值*/
    for(i = 0; i < G->v_num; ++i){ V_VISITED_FLAGS[i] = 0; V_LASTIEST[i] = V_EARLIEST[G->v_num - 1]; }
    /*初始化V_VISITED_FLAGS对应的最初的出度数*/
    for(i = 0; i < G->v_num; ++i)
    {
	/*计数器*/
	count = 0;
	arc = G->v_list[i]->arc_first_out;
	while(arc){ ++count; arc = arc->arc_tail; }
	V_VISITED_FLAGS[i] = count;
    }
    /*逆向遍历图，这里用的方法类似拓扑逆排序的遍历方法，每次取出出度为0的一个点，若知道图的终点
     *则普通的遍历也可*/
    for(i = 0; i < G->v_num; ++i)
    {
	/*获取一个0出度顶点位置*/
	zero_v = GetZeroOutdegreeVertex(G,G->v_num - 1);
	/*如果返回的为-1，则说明未取到出度为0的顶点*/
	if(zero_v > -1)
	{
	    /*这里的zero_v作为头顶点进行遍历*/
	    arc = G->v_list[zero_v]->arc_first_in;
	    while(arc)
	    {
		/*如果头顶点的最晚开始时间-边活动的持续时间(权值) < 尾顶点的最晚始时间，则赋值*/
		if((V_LASTIEST[zero_v] - arc->info->power) < V_LASTIEST[arc->v_tail])
		{ V_LASTIEST[arc->v_tail] = V_LASTIEST[zero_v] - arc->info->power; }
		arc = arc->arc_head;
	    }
	}
    }

    /*根据两个辅助数组，计算e==l的活动*/
    /*活动最早的开始时间 = 尾顶点(事件)最早开始的时间，这时相当于从e线出发，尾顶点还是尾顶点
     *活动最晚开始的时间 = 头顶点最晚开始时间-边的权值，这时相当于从l线出发，头顶点变成了尾
     *确定了尾和头无论是从e线出发还是从l线出发都能吻合，才能确定一条边是关键活动*/
    for(i = 0; i < G->v_num; ++i)
    {
	/*i作为尾顶点进行遍历*/
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    /*在此也可输出每条边的时间余量*/
	    if(V_EARLIEST[i] == (V_LASTIEST[arc->v_head] - arc->info->power))
	    { printf("%s ",arc->info->name); }
	    arc = arc->arc_tail;
	}
    }
    printf("\n");
}

/*图的释放*/
void GraphicsFree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("GraphicsFree G is NULL"); return; }
    int i = 0;
    while(i < G->v_num){ V_VISITED_FLAGS[i] = false; ++i; }
    P_ArcNode arc = NULL;
    P_ArcNode temp_arc = NULL;
    while(i < G->v_num)
    {
	//释放点数据
	SAFE_FREE(G->v_list[i]->data);
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    temp_arc = arc;
	    arc = arc->arc_head;
	    //释放所有出边信息和出边
	    SAFE_FREE(temp_arc->info);
	    SAFE_FREE(temp_arc);
	}
	//释放点
	SAFE_FREE(G->v_list[i]);
    }
    arc = NULL; temp_arc = NULL;
    //释放图
    SAFE_FREE(G);
}

int main()
{
    //建图
    P_Graphics digraph_one = CreateDigraphOne();
    if(digraph_one == NULL){ LINE_DEBUG("digraph_one create failed"); return -1; }
    P_Graphics digraph_two = CreateDigraphTwo();
    if(digraph_two == NULL){ LINE_DEBUG("digraph_two create failed"); return -1; }
    //建链表/栈
    P_Form stack = CreateOneForm();
    if(stack == NULL){ LINE_DEBUG("stack create failed"); return -1; }
    P_Form list = CreateOneForm();
    if(list == NULL){ LINE_DEBUG("list create failed"); return -1; }
    //DFS方法拓扑排序
    GraphicsDFS_TopologicalSort(digraph_one,0,stack);
    GraphicsTopologicalSortShow(digraph_one,stack);
    printf("------------------------------------\n");
    //0入度法拓扑排序
    GraphicsZeroIndgreeTopologicalSort(digraph_one,0,list);
    GraphicsTopologicalSortShow(digraph_one,list);
    printf("------------------------------------\n");
    //求关键路径
    Graphics_CriticalPath(digraph_two,0);

    //清理工作
    FormFree(stack);
    FormFree(list);
    GraphicsFree(digraph_one);
    GraphicsFree(digraph_two);

    return 0;
}
