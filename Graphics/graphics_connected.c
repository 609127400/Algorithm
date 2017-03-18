/*
 *                                  图的连通性问题
 * 1.主要有(最小)生成树，关节点和重联通分量问题。多针对无向图，用多重表存储。
 * 2.最小生成树
 *   ① 针对带权值的连通图。非连通图可以分别计算其连通子图的最小生成树。最小生成
 *   树：Minimum Cost Splanning Tree，即最小代价树。通过最小的路径消耗到达图中的
 *   所有顶点。一般应用在无向图中，有向图中也有最小生成树，但是算法更复杂。
 *   ② 图的生成树的基本操作步骤：在DFS中，每次迭代传进一个树参数，从递归到最深层
 *   返回开始，即从叶节点开始构建这棵空树。一层一层往上垒，不断将现有树的根节点作
 *   为新的根节点的子节点连接并更新树的根节点即可。在BFS中，则是从上向下构建树的
 *   过程，循环中，将弹出将的第一个元素作为根节点，之后将每次要弹出的元素作为要压
 *   入的元素的根节点进行连接即可。需要注意处理的就是留意图中顶点最多的分支量以及
 *   树的存储结构。
 *   ③ 最小生成树：连接图中V个顶点的n-1条边且保证这些边的权值和最小。常用的有Prim
 *   算法和Kruskal算法。算法中若遇到权重相等的则任选一个即可。
 *   Prim算法：建立一个图的新的空的顶点集Vnew，然后放入起始顶点。然后开始建立最小
 *   生成树。扫描依赖于Vnew中所有顶点的所有边，找出权值最小的一条边，将这条边的另
 *   一个顶点加入Vnew中并标记记录这条边。然后重复扫描/寻找权值最小的边/加入顶点到
 *   Vnew，直到Vnew包含了图中的所有顶点。这里的最小生成树也是一步一步形成的，即每
 *   次循环都会添加一个顶点和一条边到最小生成树上，图有n个顶点，则会循环添加n-1次。
 *   由此可知Prim算法与n密切相关，为n的2次方。因此在稠密图中算法利用效率较高。
 *   Kruskal算法：建立一个新图Gnew，初始只有原图的所有顶点而没有边。每次从原图所有
 *   的边中选取一条权值最小的，当此边不会导致新图现有的边形成环，则将此边加入Gnew。
 *   直到Gnew所有顶点都连通。形式上，Kruskal算法是在处理初始状态都为单节点的树的森
 *   林，每加入一条边，就是将两棵树融为一棵树，直至最终所有的树融合为一棵树。因此
 *   算法跟图的边数密切相关，为elog(e)，e为图的边数，因此适合稀疏图。
 * 3.关节点和重联通分量
 *   ① 关节点：在删除图G中的某一定点v和依附于v的所有边后，G由连通变为非连通，则v称
 *   为关节点。一个没有关节点的图称作重连通图或双连通图biconnected graph。若至少删
 *   除k个节点后G才会失去连通性，则称G的连通度为k。航线，通信网络服务点，关键元件线
 *   路都需一定的连通度。反之，G为非重连通图，要破坏G的连通性，只要破坏关节点即可。
 *   ② 关节点的属性：在图G的深度优先生成树T中，(1)T的根节点R存在>=2个的分支，则R一
 *   定是关节点，反之不是。(2) 其它非叶顶点v(叶顶点一定不是关节点)只要存在子分支(子
 *   树)，且子分支中不存在某顶点连向v的祖先的背边(而形成的环)的情况，则v一定是关节
 *   点。反之说明v的子分支中的一个顶点有连向v的一条背边所形成的环，当删除v及依附于v
 *   的边后，v不会分割其祖先顶点和其子分支顶点，因为v的子分支中的顶点还可以在G中通
 *   过背边与v的祖先相连通。如：A-B-C，同时还有A-C相连，在DFS生成树中A-C就是一条背
 *   边。A是B的祖先，B是C的祖先，B连通着A和C。当删除B后，C因为有一条连向B的祖先A的
 *   背边，仍然可以维持连通性，因此B就不是关节点了。
 *   ③ 实现方法：在DFS遍历中，给每个访问的顶点由小到大编号，旨在明确谁是(生成树中)
 *   先遍历到的祖先，谁是后遍历到的后代。在遍历的同时计算出每个顶点的最小次序值。而
 *   最小次序值的计算方法涉及三个值：1.v自身的次序值 2.v连向(若有)v的最小次序祖先的
 *   次序值 3.v的后代中连向(若有)v的最小次序祖先的次序值N。这三个值取最小的一个作为
 *   顶点v的最小次序值。然后若v的直接后代w的最小次序值 < v自身的次序值即说明w或w的后
 *   代中存在连向v的祖先的背向边，也即v不是关键节点。反之，若w的最小次序值 >= v自身
 *   的次序值，且v自身有子分支，则说明v是关节点。
 *   ④ 关节点查找实现的方法类似于利用DFS遍历测试图中是否有环存在，只是这里指定测试
 *   的是连向当前访问节点v的祖先的环。具体可参看graphics_dag 3 (3) 部分。
 *
 *
 *
 *
 *                                                     2016年11月28日
 */

//#define _DEBUG_CLOSE_
#include "../PublicForAlgorithms.h"

#define MAX_MORE_POWER (100 + 1)
#define MAX_POWER 100
#define MIN_POWER 0
#define MAX_ARC_NAME_LEN 60
#define MAX_VERTEX_NUM 100
#define MAX_MORE_VERTEX_NUM (100 + 1)
#define MAX_VERTEX_NAME_LEN 60
#define MAX_VERTEX_ADDR_LEN 100
#define MAX_GRAPHICS_NAME_LEN 60

typedef int V_Position;   /*顶点位置*/
typedef int Power;        /*边权值，最大的权值不超过 MAX_POWER*/
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
    bool mark;
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
    new_arc->mark = false; new_arc->info = info;
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
    char name[MAX_GRAPHICS_NAME_LEN];
    G_Type g_type;
    P_VertexNode v_list[MAX_VERTEX_NUM];
    int v_num; int arc_num;
}Graphics, *P_Graphics;

/*
 * 无向图1 最小生成树使用
 *        0
 *       /|\            权值：0-1 20  0-2 10  0-3 18
 *      / | \                 1-2 15  2-3 5   1-4 30
 *     /  |  \                2-4 1   2-5 10  3-5 5
 *    1---2---3               4-5 25
 *     \ / \ /
 *      4---5
 */
P_Graphics CreateUndigraphOne()
{
    //声明点数据，边信息，点，边，图
    P_Arc_Info info0_1 = NULL; P_Arc_Info info0_2 = NULL; P_Arc_Info info0_3 = NULL; P_Arc_Info info1_2 = NULL;
    P_Arc_Info info2_3 = NULL; P_Arc_Info info1_4 = NULL; P_Arc_Info info2_4 = NULL; P_Arc_Info info2_5 = NULL;
    P_Arc_Info info3_5 = NULL; P_Arc_Info info4_5 = NULL;
    P_ArcNode Arc0_1 = NULL; P_ArcNode Arc0_2 = NULL; P_ArcNode Arc0_3 = NULL; P_ArcNode Arc1_2 = NULL;
    P_ArcNode Arc2_3 = NULL; P_ArcNode Arc1_4 = NULL; P_ArcNode Arc2_4 = NULL; P_ArcNode Arc2_5 = NULL;
    P_ArcNode Arc3_5 = NULL; P_ArcNode Arc4_5 = NULL;
    P_V_Data_Type data0 = NULL; P_V_Data_Type data1 = NULL; P_V_Data_Type data2 = NULL; P_V_Data_Type data3 = NULL;
    P_V_Data_Type data4 = NULL; P_V_Data_Type data5 = NULL;
    P_VertexNode V0 = NULL; P_VertexNode V1 = NULL; P_VertexNode V2 = NULL; P_VertexNode V3 = NULL;
    P_VertexNode V4 = NULL; P_VertexNode V5 = NULL;
    P_Graphics new_undigraph = NULL;
    //创建边信息
    info0_1 = CreateOneArcInfo(20,"V0-V1"); info0_2 = CreateOneArcInfo(10,"V0->V2");
    info0_3 = CreateOneArcInfo(18,"V0-V3"); info1_2 = CreateOneArcInfo(15,"V1-V2");
    info2_3 = CreateOneArcInfo(5,"V2-V3");  info1_4 = CreateOneArcInfo(30,"V1-V4");
    info2_4 = CreateOneArcInfo(1,"V2-V4");  info2_5 = CreateOneArcInfo(10,"V2-V5");
    info3_5 = CreateOneArcInfo(5,"V3-V5");  info4_5 = CreateOneArcInfo(25,"V4-V5");
    if(info0_1 == NULL || info0_2 == NULL || info0_3 == NULL || info1_2 == NULL
    || info2_3 == NULL || info1_4 == NULL || info2_4 == NULL || info2_5 == NULL
    || info3_5 == NULL || info4_5 == NULL)
    { LINE_DEBUG("ArcInfo Create failed"); goto Label_CreateUndigraphOne_Clean; }
    //创建边
    Arc0_1 = CreateOneArc(info0_1); Arc0_2 = CreateOneArc(info0_2);
    Arc0_3 = CreateOneArc(info0_3); Arc1_2 = CreateOneArc(info1_2);
    Arc2_3 = CreateOneArc(info2_3); Arc1_4 = CreateOneArc(info1_4);
    Arc2_4 = CreateOneArc(info2_4); Arc2_5 = CreateOneArc(info2_5);
    Arc3_5 = CreateOneArc(info3_5); Arc4_5 = CreateOneArc(info4_5);
    if(Arc0_1 == NULL || Arc0_2  == NULL || Arc0_3 == NULL || Arc1_2  == NULL
    || Arc2_3 == NULL || Arc1_4  == NULL || Arc2_4 == NULL || Arc2_5 == NULL
    || Arc3_5 == NULL || Arc4_5  == NULL)
    { LINE_DEBUG("ArcNode Create failed"); goto Label_CreateUndigraphOne_Clean; }
    //创建点数据
    data0 = CreateOneVertexData(0,"V0","地址0"); data1 = CreateOneVertexData(1,"V1","地址1"); 
    data2 = CreateOneVertexData(2,"V2","地址2"); data3 = CreateOneVertexData(3,"V3","地址3");
    data4 = CreateOneVertexData(4,"V4","地址4"); data5 = CreateOneVertexData(5,"V5","地址5");
    if(data0 == NULL || data1 == NULL || data2 == NULL || data3 == NULL || data4 == NULL || data5 == NULL)
    { LINE_DEBUG("VertexData Create failed"); goto Label_CreateUndigraphOne_Clean; }
    //创建点
    V0 = CreateOneVertex(data0); V1 = CreateOneVertex(data1); V2 = CreateOneVertex(data2);
    V3 = CreateOneVertex(data3); V4 = CreateOneVertex(data4); V5 = CreateOneVertex(data5);
    if(V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL || V4 == NULL || V5 == NULL)
    { LINE_DEBUG("Vertex Create failed"); goto Label_CreateUndigraphOne_Clean; }
    //创建图
    new_undigraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_undigraph == NULL){ LINE_DEBUG("Graphics malloc failed"); goto Label_CreateUndigraphOne_Clean; }
    
    //关系组织
    Arc0_1->v_tail = 0; Arc0_1->v_head = 1; Arc0_1->arc_tail = Arc0_2; Arc0_1->arc_head = Arc1_2;
    Arc0_2->v_tail = 0; Arc0_2->v_head = 2; Arc0_2->arc_tail = Arc0_3; Arc0_2->arc_head = Arc1_2;
    Arc0_3->v_tail = 0; Arc0_3->v_head = 3; Arc0_3->arc_tail = NULL;   Arc0_3->arc_head = Arc2_3;
    Arc1_2->v_tail = 1; Arc1_2->v_head = 2; Arc1_2->arc_tail = Arc1_4; Arc1_2->arc_head = Arc2_3;
    Arc2_3->v_tail = 2; Arc2_3->v_head = 3; Arc2_3->arc_tail = Arc2_4; Arc2_3->arc_head = Arc3_5;
    Arc1_4->v_tail = 1; Arc1_4->v_head = 4; Arc1_4->arc_tail = NULL;   Arc1_4->arc_head = Arc2_4;
    Arc2_4->v_tail = 2; Arc2_4->v_head = 4; Arc2_4->arc_tail = Arc2_5; Arc2_4->arc_head = Arc4_5;
    Arc2_5->v_tail = 2; Arc2_5->v_head = 5; Arc2_5->arc_tail = NULL;   Arc2_5->arc_head = Arc3_5;
    Arc3_5->v_tail = 3; Arc3_5->v_head = 5; Arc3_5->arc_tail = NULL;   Arc3_5->arc_head = Arc4_5;
    Arc4_5->v_tail = 4; Arc4_5->v_head = 5; Arc4_5->arc_tail = NULL;   Arc4_5->arc_head = NULL;
    V0->arc_first_out = Arc0_1; V1->arc_first_out = Arc0_1; V2->arc_first_out = Arc0_2;
    V3->arc_first_out = Arc0_3; V4->arc_first_out = Arc1_4; V5->arc_first_out = Arc2_5;
    strncpy(new_undigraph->name,"五边形加权连通无向图：最小生成树",MAX_GRAPHICS_NAME_LEN);
    new_undigraph->v_num = 6; new_undigraph->arc_num = 10; new_undigraph->g_type = UNDIGRAPH;
    new_undigraph->v_list[0] = V0; new_undigraph->v_list[1] = V1;
    new_undigraph->v_list[2] = V2; new_undigraph->v_list[3] = V3;
    new_undigraph->v_list[4] = V4; new_undigraph->v_list[5] = V5;

    return new_undigraph;

Label_CreateUndigraphOne_Clean:
    SAFE_FREE(info0_1); SAFE_FREE(info0_2); SAFE_FREE(info0_3); SAFE_FREE(info1_2); SAFE_FREE(info2_3);
    SAFE_FREE(info1_4); SAFE_FREE(info2_4); SAFE_FREE(info2_5); SAFE_FREE(info3_5); SAFE_FREE(info4_5);
    SAFE_FREE(Arc0_1); SAFE_FREE(Arc0_2); SAFE_FREE(Arc0_3); SAFE_FREE(Arc1_2); SAFE_FREE(Arc2_3);
    SAFE_FREE(Arc1_4); SAFE_FREE(Arc2_4); SAFE_FREE(Arc2_5); SAFE_FREE(Arc3_5); SAFE_FREE(Arc4_5);
    SAFE_FREE(data0); SAFE_FREE(data1); SAFE_FREE(data2); SAFE_FREE( data3); SAFE_FREE(data4); SAFE_FREE(data5);
    SAFE_FREE(V0); SAFE_FREE(V1); SAFE_FREE(V2); SAFE_FREE( V3); SAFE_FREE(V4); SAFE_FREE(V5);
    SAFE_FREE(new_undigraph);
    return NULL;
}

/*  无向图2 供关节点查找使用
 *       0      8 9
 *       |      |/
 *       1      7
 *      / \    /|
 *     2   3--5 |
 *      \ /    \|
 *       4      6
 */
P_Graphics CreateUndigraphTwo(void)
{
    P_V_Data_Type data0 = NULL; P_V_Data_Type data1 = NULL; P_V_Data_Type data2 = NULL; P_V_Data_Type data3 = NULL;
    P_V_Data_Type data4 = NULL; P_V_Data_Type data5 = NULL; P_V_Data_Type data6 = NULL; P_V_Data_Type data7 = NULL;
    P_V_Data_Type data8 = NULL; P_V_Data_Type data9 = NULL;
    P_VertexNode V0 = NULL; P_VertexNode V1 = NULL; P_VertexNode V2 = NULL; P_VertexNode V3 = NULL;
    P_VertexNode V4 = NULL; P_VertexNode V5 = NULL; P_VertexNode V6 = NULL; P_VertexNode V7 = NULL;
    P_VertexNode V8 = NULL; P_VertexNode V9 = NULL;
    P_Arc_Info info0_1 = NULL; P_Arc_Info info1_2 = NULL; P_Arc_Info info1_3 = NULL; P_Arc_Info info2_4 = NULL;
    P_Arc_Info info3_4 = NULL; P_Arc_Info info3_5 = NULL; P_Arc_Info info5_6 = NULL; P_Arc_Info info5_7 = NULL;
    P_Arc_Info info6_7 = NULL; P_Arc_Info info7_8 = NULL; P_Arc_Info info7_9 = NULL;
    P_ArcNode Arc0_1 = NULL; P_ArcNode Arc1_2 = NULL; P_ArcNode Arc1_3 = NULL; P_ArcNode Arc2_4 = NULL;
    P_ArcNode Arc3_4 = NULL; P_ArcNode Arc3_5 = NULL; P_ArcNode Arc5_6 = NULL; P_ArcNode Arc5_7 = NULL;
    P_ArcNode Arc6_7 = NULL; P_ArcNode Arc7_8 = NULL; P_ArcNode Arc7_9 = NULL;
    P_Graphics new_undigraph = NULL;
    
    //创建点数据
    data0 = CreateOneVertexData(0,"V0","V0地址"); data1 = CreateOneVertexData(1,"V1","V1地址"); data2 = CreateOneVertexData(2,"V2","V2地址");
    data3 = CreateOneVertexData(3,"V3","V3地址"); data4 = CreateOneVertexData(4,"V4","V4地址"); data5 = CreateOneVertexData(5,"V5","V5地址");
    data6 = CreateOneVertexData(6,"V6","V6地址"); data7 = CreateOneVertexData(7,"V7","V7地址"); data8 = CreateOneVertexData(8,"V8","V8地址");
    data9 = CreateOneVertexData(9,"V9","V9地址");
    if(data0 == NULL || data1 == NULL || data2 == NULL || data3 == NULL || data4 == NULL
    || data5 == NULL || data6 == NULL || data7 == NULL || data8 == NULL || data9 == NULL)
    { LINE_DEBUG("Vertex Data Create failed"); goto Label_CreateUndigraphTwo_Clean; }
    //创建点
    V0 = CreateOneVertex(data0); V1 = CreateOneVertex(data1); V2 = CreateOneVertex(data2);
    V3 = CreateOneVertex(data3); V4 = CreateOneVertex(data4); V5 = CreateOneVertex(data5);
    V6 = CreateOneVertex(data6); V7 = CreateOneVertex(data7); V8 = CreateOneVertex(data8);
    V9 = CreateOneVertex(data9);
    if(V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL || V4 == NULL
    || V5 == NULL || V6 == NULL || V7 == NULL || V8 == NULL || V9 == NULL)
    { LINE_DEBUG("Vertex Create failed"); goto Label_CreateUndigraphTwo_Clean; }
    //创建边信息
    info0_1 = CreateOneArcInfo(6,"V0-V1"); info1_2 = CreateOneArcInfo(7,"V1-V2"); info1_3 = CreateOneArcInfo(12,"V1-V3");
    info2_4 = CreateOneArcInfo(3,"V2-V4"); info3_4 = CreateOneArcInfo(8,"V3-V4"); info3_5 = CreateOneArcInfo(17,"V3-V5");
    info5_6 = CreateOneArcInfo(7,"V5-V6"); info5_7 = CreateOneArcInfo(10,"V5-V7"); info6_7 = CreateOneArcInfo(9,"V6-V7");
    info7_8 = CreateOneArcInfo(5,"V7-V8"); info7_9 = CreateOneArcInfo(2,"V7-V9");
    if(info0_1 == NULL || info1_2 == NULL || info1_3 == NULL || info2_4 == NULL || info3_4 == NULL || info3_5 == NULL
    || info5_6 == NULL || info5_7 == NULL || info6_7 == NULL || info7_8 == NULL || info7_9 == NULL)
    { LINE_DEBUG("ArcInfo Create failed"); goto Label_CreateUndigraphTwo_Clean; }
    //创建边
    Arc0_1 = CreateOneArc(info0_1); Arc1_2 = CreateOneArc(info1_2); Arc1_3 = CreateOneArc(info1_3);
    Arc2_4 = CreateOneArc(info2_4); Arc3_4 = CreateOneArc(info3_4); Arc3_5 = CreateOneArc(info3_5);
    Arc5_6 = CreateOneArc(info5_6); Arc5_7 = CreateOneArc(info5_7); Arc6_7 = CreateOneArc(info6_7);
    Arc7_8 = CreateOneArc(info7_8); Arc7_9 = CreateOneArc(info7_9);
    if(Arc0_1 == NULL || Arc1_2 == NULL || Arc1_3 == NULL || Arc2_4 == NULL || Arc3_4 == NULL || Arc3_5 == NULL
    || Arc5_6 == NULL || Arc5_7 == NULL || Arc6_7 == NULL || Arc7_8 == NULL || Arc7_9 == NULL )
    { LINE_DEBUG("Arc Create failed"); goto Label_CreateUndigraphTwo_Clean; }
    //建立图
    new_undigraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_undigraph == NULL){ LINE_DEBUG("Graphics malloc failed"); goto Label_CreateUndigraphTwo_Clean; }

    //关系组织
    Arc0_1->v_tail = 0; Arc0_1->arc_tail = NULL; Arc0_1->v_head = 1; Arc0_1->arc_head = Arc1_2;
    Arc1_2->v_tail = 1; Arc1_2->arc_tail = Arc1_3; Arc1_2->v_head = 2; Arc1_2->arc_head = Arc2_4;
    Arc1_3->v_tail = 1; Arc1_3->arc_tail = NULL; Arc1_3->v_head = 3; Arc1_3->arc_head = Arc3_4;
    Arc2_4->v_tail = 2; Arc2_4->arc_tail = NULL; Arc2_4->v_head = 4; Arc2_4->arc_head = Arc3_4;
    Arc3_4->v_tail = 3; Arc3_4->arc_tail = Arc3_5; Arc3_4->v_head = 4; Arc3_4->arc_head = NULL;
    Arc3_5->v_tail = 3; Arc3_5->arc_tail = NULL; Arc3_5->v_head = 5; Arc3_5->arc_head = Arc5_6;
    Arc5_6->v_tail = 5; Arc5_6->arc_tail = Arc5_7; Arc5_6->v_head = 6; Arc5_6->arc_head = Arc6_7;
    Arc5_7->v_tail = 5; Arc5_7->arc_tail = NULL; Arc5_7->v_head = 7; Arc5_7->arc_head = Arc6_7;
    Arc6_7->v_tail = 6; Arc6_7->arc_tail = NULL; Arc6_7->v_head = 7; Arc6_7->arc_head = Arc7_8;
    Arc7_8->v_tail = 7; Arc7_8->arc_tail = Arc7_9; Arc7_8->v_head = 8; Arc7_8->arc_head = NULL;
    Arc7_9->v_tail = 7; Arc7_9->arc_tail = NULL; Arc7_9->v_head = 9; Arc7_9->arc_head = NULL;
    V0->arc_first_out = Arc0_1; V1->arc_first_out = Arc0_1; V2->arc_first_out = Arc1_2; V3->arc_first_out = Arc1_3;
    V4->arc_first_out = Arc2_4; V5->arc_first_out = Arc3_5; V6->arc_first_out = Arc5_6; V7->arc_first_out = Arc5_7;
    V8->arc_first_out = Arc7_8; V9->arc_first_out = Arc7_9;
    strncpy(new_undigraph->name,"无向图2：搜寻关节点",MAX_GRAPHICS_NAME_LEN);
    new_undigraph->v_num = 10; new_undigraph->arc_num = 11; new_undigraph->g_type = UNDIGRAPH;
    new_undigraph->v_list[0] = V0; new_undigraph->v_list[1] = V1;
    new_undigraph->v_list[2] = V2; new_undigraph->v_list[3] = V3;
    new_undigraph->v_list[4] = V4; new_undigraph->v_list[5] = V5;
    new_undigraph->v_list[6] = V6; new_undigraph->v_list[7] = V7;
    new_undigraph->v_list[8] = V8; new_undigraph->v_list[9] = V9;

    return new_undigraph;

Label_CreateUndigraphTwo_Clean:
    SAFE_FREE(data0); SAFE_FREE(data1); SAFE_FREE(data2); SAFE_FREE(data3); SAFE_FREE(data4); 
    SAFE_FREE(data5); SAFE_FREE(data6); SAFE_FREE(data7); SAFE_FREE(data8); SAFE_FREE(data9);
    SAFE_FREE(V0); SAFE_FREE(V1); SAFE_FREE(V2); SAFE_FREE(V3); SAFE_FREE(V4);
    SAFE_FREE(V5); SAFE_FREE(V6); SAFE_FREE(V7); SAFE_FREE(V8); SAFE_FREE(V9);
    SAFE_FREE(info0_1); SAFE_FREE(info1_2); SAFE_FREE(info1_3); SAFE_FREE(info2_4); SAFE_FREE(info3_4); SAFE_FREE(info3_5);
    SAFE_FREE(info5_6); SAFE_FREE(info5_7); SAFE_FREE(info6_7); SAFE_FREE(info7_8); SAFE_FREE(info7_9);
    SAFE_FREE(Arc0_1); SAFE_FREE(Arc1_2); SAFE_FREE(Arc1_3); SAFE_FREE(Arc2_4); SAFE_FREE(Arc3_4); SAFE_FREE(Arc3_5);
    SAFE_FREE(Arc5_6); SAFE_FREE(Arc5_7); SAFE_FREE(Arc6_7); SAFE_FREE(Arc7_8); SAFE_FREE(Arc7_9);
    SAFE_FREE(new_undigraph);

    return NULL;
}

/*辅助数组*/
/*标识已经放入Vnew中的顶点*/
bool V_NEW[MAX_VERTEX_NUM];
/*存放的最小生成树的路径，最小生成树路径永远比顶点数少1*/
P_ArcNode MIN_ARCS[MAX_VERTEX_NUM];

/*
 * Prim生成最小代价树
 * 这里并不真正生成，而是在原图中对于组成最小代价树的边进行mark标记，
 * false表示未标记，true表示已标记
 */
bool Graphics_Prim_MinCostTree(P_Graphics G,V_Position s_p)
{
    if(G == NULL){ LINE_DEBUG("Graphics_Prim_MinCostTree G is NULL"); return false; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("Graphics_Prim_MinCostTree s_p is illegal"); return false; }
    int i; P_ArcNode arc = NULL; V_Position next_v;
    for(i = 0; i < G->v_num; ++i){ V_NEW[i] = false; MIN_ARCS[i] = NULL; }
    int v_marked = 0;
    /*加入起始顶点*/
    V_NEW[s_p] = true;
    /*设立一个对比的初始值，此值应确保比图中所有的权值都大，MinArc负责存储最小权值的边*/
    ArcInfo mininfo; mininfo.power = MAX_MORE_POWER;
    ArcNode minarc; minarc.info = &mininfo;
    P_ArcNode MinArc = NULL;
    /*循环v_num-1次获取v_num-1条边*/
    for(i = 1; i < G->v_num; ++i)
    {
	/*重置对比值*/
	MinArc = &minarc;
	/*从所有依附于Vnew现有的所有顶点的边中取出权值最小的一条*/
	for(v_marked = 0; v_marked < G->v_num; ++v_marked)
	{
	    if(V_NEW[v_marked] == false){ continue; }
	    arc = G->v_list[v_marked]->arc_first_out;
	    while(arc)
	    {
		next_v = (v_marked == arc->v_tail) ? arc->v_head : arc->v_tail;
		/*在不在Vnew中的顶点中，如果当前访问的边比现有的MinArc还小，则更新MinArc*/
		if(V_NEW[next_v] == false)
		{ if(arc->info->power < MinArc->info->power){ MinArc = arc; } }
		arc = (v_marked == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	    }
	}
	/*不清楚最小的边是V_NEW中哪个顶点发出的，所以干脆都置true一下*/
	V_NEW[MinArc->v_tail] = true;
	V_NEW[MinArc->v_head] = true;
	/*标记每条最小边，也可就此存储每条边形成一个新图*/
	MinArc->mark = true;
	MIN_ARCS[i-1] = MinArc;
    }
    return true;
}

/*
 * Kruskal生成最小代价树
 * 这里的处理方法是先将边按权值在arcs中从小到大排序，然后遍历
 * arcs，由V_NEW数据进行辅助，对所有的边进行接纳或舍弃的标记。
 */
bool Graphics_Kruskal_MinCostTree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Graphics_Prim_MinCostTree G is NULL"); return false; }
    P_ArcNode arcs[G->arc_num];
    P_ArcNode arc = NULL; P_ArcNode temp_arc = NULL;
    int i = 0; int j = 0;
    for(i = 0; i < G->arc_num; ++i){ arcs[i] = NULL; }
    for(i = 0; i < G->v_num; ++i){ V_NEW[i] = false; MIN_ARCS[i] = NULL; }
    //将所有出边纳入arcs数组中，防止边重复
    for(i = 0; i < G->v_num; ++i)
    {
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    if(i == arc->v_tail){ arcs[j] = arc; ++j; }
	    arc = (i == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	}
    }
    //插入排序
    for(i = 1; i < G->arc_num; ++i)
    {
	arc = arcs[i];
	for(j = 0; j < i; ++j)
	{
	    if(arc->info->power < arcs[j]->info->power)
	    {
		temp_arc = arcs[j];
		arcs[j] = arc;
		arc = temp_arc;
	    }
	}
	arcs[i] = arc;
    }
    /*
    //排序结果
    for(i = 0; i < G->arc_num; ++i)
    { printf("%s power = %d\n",arcs[i]->info->name,arcs[i]->info->power); }
     */
    /*遍历arcs，选取最小生成树的边，标识mark字段，true代表接受，false代表放弃*/
    j = 0;
    for(i = 0; i < G->arc_num; ++i)
    {
	/*如果这条边的两个顶点不同时都已经被标记，
	 *则说明这条边不会导致Gnew中现有的边形成环，记录这条边*/
	if(!(V_NEW[arcs[i]->v_tail] == true && V_NEW[arcs[i]->v_head] == true))
	{
	    arcs[i]->mark = true;
	    MIN_ARCS[j] = arcs[i]; j++;
	    //标记边的两个顶点
	    V_NEW[arcs[i]->v_tail] = true; V_NEW[arcs[i]->v_head] = true;
	}
    }
}

void Graphics_ShowMinCostTree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Graphics_ShowMinCostTree G is NULL"); return; }
    int i = 0; int all_cost = 0;
    printf("%s---最小生成树\n",G->name);
    for(i = 0; i < G->v_num - 1; ++i)
    {
	printf("%s power = %d\n",MIN_ARCS[i]->info->name,MIN_ARCS[i]->info->power);
	all_cost += MIN_ARCS[i]->info->power;
    }
    printf("权值共计：%d\n",all_cost);
}

/*关节点搜寻辅助数组和变量
 * 全局的数组和变量，在多线程下容易出错。
 * V_SEQUENCE_NUM 存储顶点自身的次序值，初始为0，表示未访问，次序值从1开始，
 * 最大值为顶点数值
 * V_MIN_SEQUENCE_NUM 存储顶点最小次序值*/
int V_SEQUENCE_NUM[MAX_VERTEX_NUM];
int V_MIN_SEQUENCE_NUM[MAX_VERTEX_NUM];
/*次序号*/
static int sequence_num = 1;

/*利用DFS在辅助数组中标记所有顶点的次序值和最小次序值
 * 参数  G：图    s_p：顶点位置
 * 返回值 返回当前顶点s_p最小的次序值*/
int Graphics_DFS_ArticulationPoints(P_Graphics G,V_Position s_p)
{
    /*第一个相关值，s_p本身的次序号*/
    V_SEQUENCE_NUM[s_p] = sequence_num;
    ++sequence_num;
    
    /*存储s_p最小的次序值*/
    int min_sequence = V_SEQUENCE_NUM[s_p];
    /*存储返回的s_p后代的最小次序值*/
    int re_min_sequence = MAX_MORE_VERTEX_NUM;

    P_ArcNode arc = G->v_list[s_p]->arc_first_out;
    V_Position another_v;
    while(arc)
    {
	another_v = (s_p == arc->v_tail) ? arc->v_head : arc->v_tail;
	
	/*第二个相关值：s_p相邻点的最小次序号值*/
	if(V_SEQUENCE_NUM[another_v] != 0 && V_SEQUENCE_NUM[another_v] < min_sequence)
	{ min_sequence = V_SEQUENCE_NUM[another_v]; }
	if(V_SEQUENCE_NUM[another_v] == 0)
	{
	    /*标记生成树的边，可以为根节点有多少个分支做准备*/
	    arc->mark = true;
	    re_min_sequence = Graphics_DFS_ArticulationPoints(G,another_v);
	    /*第三个相关值：s_p后代的最小次序号值*/
	    if(re_min_sequence < min_sequence)
	    { min_sequence = re_min_sequence; }
	    /*
	    //如果不用返回值，可直接用V_MIN_SEQUENCE_NUM[another_v]获取后代最小次序号值
	    //这样效率更高
	    if(V_MIN_SEQUENCE_NUM[another_v] < min_sequence)
	    { min_sequence = V_MIN_SEQUENCE_NUM[another_v]; }
	    */
	}

	arc = (s_p == arc->v_tail) ? arc->arc_tail : arc->arc_head;
    }
    /*置最小次序值给s_p*/
    V_MIN_SEQUENCE_NUM[s_p] = min_sequence;
    return min_sequence;
}

/*
 *参数：G 图   s_p 开始遍历的起始顶点 sequence_num次序值开始值，这里定为1*/
void Graphics_ArticulationPoints(P_Graphics G,V_Position s_p)
{
    if(G == NULL){ LINE_DEBUG("Graphics_ArticulationPoints G is NULL"); return; }
    int i = 0;
    for(i = 0; i < G->v_num; ++i){ V_SEQUENCE_NUM[i] = 0; V_MIN_SEQUENCE_NUM[i] = 0; }
    /*利用DFS在辅助数组中标记所有顶点的次序值和最小次序值*/
    Graphics_DFS_ArticulationPoints(G,s_p);
    /*
    //显示DFS标识结果
    for(i = 0; i < G->v_num; ++i)
    {
	printf("%s SequenceNum = %d, Min_SequenceNum =%d \n",
		G->v_list[i]->data->name,V_SEQUENCE_NUM[i],V_MIN_SEQUENCE_NUM[i]);
    }
    */
    /*遍历两个辅助数组，输出关节点
     *判断是否有v顶点的后代w，且V_MIN_SEQUENCE_NUM[w] >= V_SEQUENCE_NUM[v]*/
    P_ArcNode arc = NULL;
    for(i = 0; i < G->v_num; ++i)
    {
	arc = G->v_list[i]->arc_first_out;
	//如果是根节点
	if(i == s_p)
	{
	    /*计算根节点有多少个分支，若>=2 则为关节点*/
	    int root_child_num = 0;
	    while(arc)
	    {
		if(arc->mark == true){ ++root_child_num; }
		arc = (i == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	    }
	    if(root_child_num >= 2){ printf("%s ",G->v_list[i]->data->name); }
	}
	else
	{
	    /*寻找i的第一个后代j(j就足够了，因为如果j的后代的某个节点可以达到的最小次序值也会传给j)*/
	    V_Position child = -1;
	    while(arc)
	    {
		child = (i == arc->v_tail) ? arc->v_head : arc->v_tail;
		if(V_SEQUENCE_NUM[child] == (V_SEQUENCE_NUM[i] + 1)){ break; }
		arc = (i == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	    }
	    /*判断i是否为关节点*/
	    if(child >= 0)
	    {
		if(V_MIN_SEQUENCE_NUM[child] >= V_SEQUENCE_NUM[i])
		{ printf("%s ",G->v_list[i]->data->name); }
	    }
	}
    }
}

/*无向图的释放*/
void Graphics_Free(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Graphics_Free G is NULL"); return; }
    int i = 0; int j = 0; P_ArcNode arc = NULL;
    P_ArcNode arcs[G->arc_num];
    //释放顶点
    for(i = 0; i < G->v_num; ++i)
    {
	SAFE_FREE(G->v_list[i]->data);
	//顺道记录所有出边
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    if(i == arc->v_tail)
	    { arcs[j] = arc; ++j; }
	    arc = (i == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	}
	SAFE_FREE(G->v_list[i]);
    }
    //释放边
    for(i = 0; i < G->arc_num; ++i)
    {
	SAFE_FREE(arcs[i]->info);
	SAFE_FREE(arcs[i]);
    }
    SAFE_FREE(G);
}

int main()
{
    //建图
    P_Graphics undigraph_one = CreateUndigraphOne();
    if(undigraph_one == NULL){ LINE_DEBUG("undigraph_one create failed"); return -1; }
    /*无向图1生成最小生成树*/
    //Prim算法
    Graphics_Prim_MinCostTree(undigraph_one,5);
    Graphics_ShowMinCostTree(undigraph_one);
    //Kruskal算法
    Graphics_Kruskal_MinCostTree(undigraph_one);
    Graphics_ShowMinCostTree(undigraph_one);
    printf("--------------------------------------------------\n");
    /*无向图2关节点的搜寻*/
    P_Graphics undigraph_two = CreateUndigraphTwo();
    if(undigraph_two == NULL){ LINE_DEBUG("undigraph_two create failed"); return -1; }
    Graphics_ArticulationPoints(undigraph_two,7);


    //清理工作
    Graphics_Free(undigraph_one);
    Graphics_Free(undigraph_two);

    return 0;
}
