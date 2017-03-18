/*
 *                         图的遍历
 * 1.主要元素分为 点、弧或边，图的类型则可分为 有向图、无向图。在有向图中被成
 *   为弧，在无向图中则称为边。tail------->head
 *   图的无向指的是顶点间没有固定的相对的方向关系，即浏览时既可以由a到b也可以
 *   由b到a，而并不是说在遍历浏览的时候没有方向，一般在遍历时由a->b，之后还会
 *   有b->a的遍历，只是此时a是已经被标记访问过的点或者a-b这条边被标记过已访问
 *   过，所以不会再进行b->a的遍历。另外无向图中的头和尾是要相对着来理解，a此时
 *   作为b的头，可能在另外一次遍历中就变成b的尾。
 * 2.表示方法：邻接矩阵，邻接表，针对有向图的十字链表，针对无向图的邻接多重表。
 * 3.图的遍历：分为深度优先和广度优先两种形式。深度优先搜索访问一个点，沿着与
 *   该点有关的(两侧的)两条边或多条边顺序访问下去，看看是否有未被访问的点，如
 *   果有，则继续深入访问下去，如此递归迭代。像极了一棵二叉树(或者更多分支，原
 *   理一样)，只是分支搜索结束的条件不再是二叉树叶节点的lchild/rchild指向NULL，
 *   而是判断访问的节点是否之前被访问过。广度优先借助队列，将开始访问的节点压入
 *   队列后开始遍历。每弹出一个顶点，就将所有与该顶点相连接且未被访问过的节点压
 *   入队列。如此循环，直到队列为空。
 *   图的DFS与BFS的步骤基本一样，只是针对不同的存储结构在迭代条件上有细微的差别。
 *   DFS：
 *   ① 处理顶点A并标识
 *   ② 获取A顶点的边链表(单链表)的第一条边(节点)
 *   ③ 循环遍历所有依附与A的边(相当于处理单链表)，在每遍循环中，(通过边)获取边
 *      的另一个顶点B，检查如果B未被访问过，则递归调用DFS从①重新开始进行处理，
 *      否则继续边链表的循环(换下一条边)。
 *   BFS：
 *   ① 压入指定开始访问的顶点并标识
 *   ② 开始遍历，循环以下步骤，直到队列中再无元素：
 *      (1)从队列中弹出一个顶点A
 *      (2)遍历所有依附于A的边(相当于单链表处理)，(通过边)获取另一个顶点B，如果
 *         B未被访问过，则压入队列并标识。
 * 4.所使用的图如下，为连通图
 *       V0               有向图加上了方向为：V0->V1 V0->V2 V1->V3 V1->V4 V4->V7
 *     /    \             V3->V7 V2->V5 V5->V6 V6->V2
 *   V1      V2
 *  /  \    /  \
 * V3  V4  V5—V6  
 *  \  /
 *   V7
 *   主要的函数
 *   邻接矩阵
 *   CreateOneMatrixUndigraph
 *   Undigraph_Matrix_DFS
 *   Undigraph_Matrix_BFS
 *   MatrixFree
 *   邻接表
 *   CreateOneAdjacencyListUndigraph
 *   CreateOneAdjacencyListDigraph
 *   Undigraph_AdjacencyList_DFS
 *   Undigraph_AdjacencyList_BFS
 *   AdjacencyListFree
 *   邻接多重表
 *   CreateOneMultilistUndigraph
 *   Undigraph_Multilist_DFS
 *   Undigraph_Multilist_BFS
 *   MultilistFree
 *   十字链表
 *   CreateOneOrthogonalListDigraph
 *   Digraph_OrthogonalList_DFS
 *   Digraph_OrthogonalList_BFS
 *   OrthogonalListFree
 *   图显示
 *   Graphics_OrthMult_Show
 *   由上面的函数的实现可知，DFS和BFS的算法具有通用性，只是不同的存储结构在迭代条件
 *   上有细微的差别
 *
 *
 *
 *
 *                                                        2016年11月17日
 */

#define _DEBUG_CLOSE_
#include "../PublicForAlgorithms.h"

#define MAX_VERTEX_NUM 100
#define MAX_DATA_ADDR_LEN 140
#define MAX_DATA_NAME_LEN 60
#define MAX_EDGE_INFO_LEN 100

typedef enum{SHOP,MARKET,HOSPITAL,GOVERNMENT,PARK,GARDEN,MOVIES,SCHOOL,HOUSE,UNKNOWN}V_TYPE;
typedef enum{VISITED,UNVISITED}IF_VISITED;
typedef enum{DIGRAPH,UNDIGRAPH}G_TYPE;
typedef enum{DFS,BFS}SHOWMODE;
typedef enum{MATRIX,ADJACENCYLIST,ORTHOGONALLSIT,MULTILIST}STRUCTURE;

/*顶点数据类型*/
typedef struct
{
    int    id;         /*编号*/
    V_TYPE type;       /*类型*/
    double longtitude; /*经度*/
    double latitude;   /*纬度*/
    char   name[MAX_DATA_NAME_LEN];    /*名字*/
    char   address[MAX_DATA_ADDR_LEN]; /*地址*/
}V_DataType, *P_V_DataType;
/*顶点列表位置类型，边信息类型，权重类型*/
typedef int  V_Position;
typedef char Arc_Info[MAX_EDGE_INFO_LEN];
typedef int  Power;

/* 边，主要针对邻接多重表和十字链表设计，邻接表可以只使用其中arc_head,v_head，info三个字段
 * 具体的存储方式看相关Create函数
 */
typedef struct Edge
{
    IF_VISITED   if_visited;/*有向图中不使用此数据，无向图中代表该节点是否被访问过的标识*/
    V_Position   v_tail;    /*有向图中代表尾顶点的位置，无向图中代表边的一个顶点A*/
    V_Position   v_head;    /*有向图中代表头顶点的位置，无向图中代表边的一个顶点B*/
    struct Edge* arc_head;  /*有向图中代表头顶点相同的下一条边，无向图中代表边顶点A的下一条边*/
    struct Edge* arc_tail;  /*有向图中代表头尾点相同的下一条边，无向图中代表边顶点B的下一条边*/
    Power        power;     /*边的权重，值越大，权重越大*/
    Arc_Info     info;      /*边的信息*/
}ArcNode,*P_ArcNode,*ArcsList;

//顶点
typedef struct
{
    P_V_DataType data;         /*顶点数据*/
    P_ArcNode    arc_first_in; /*有向图中代表该顶点的第一条入边，无向图代表该顶点的第一条边*/
    P_ArcNode    arc_first_out;/*有向图中代表该顶点的第一条出边，无向图不使用此数据*/
}VertexNode,*P_VertexNode,*VertexesList;

//处理顶点函数
typedef void (*V_Handle_Fun_Type)(P_VertexNode);

void V_Handle1(P_VertexNode v)
{
    if(v == NULL || v->data == NULL){ LINE_DEBUG("Vertex or V->data is NULL"); return; }
    printf("######################## 顶点信息 ########################\n");
    printf("+  id : %d\n",v->data->id);
    printf("+  type : ");
    switch(v->data->type)
    {
	case SHOP: printf("商店\n");     break; case MARKET: printf("商场\n");         break;
	case HOSPITAL: printf("医院\n"); break; case GOVERNMENT: printf("政府机构\n"); break;
	case PARK: printf("停车场\n");   break; case GARDEN: printf("公园\n");         break;
	case MOVIES: printf("电影院\n"); break; case SCHOOL: printf("学校\n");         break;
	case HOUSE: printf("住宅区\n");  break; default: printf("未知\n");             break;
    }
    printf("+  longtitude : %.4f\n",v->data->longtitude);
    printf("+  latitude : %.4f\n",v->data->latitude);
    printf("+  name : %s\n",v->data->name);
    printf("+  address : %s\n",v->data->address);
    printf("\n");
}
//Vhandle2 ...

//图
typedef struct
{
    G_TYPE g_type;                      /*图类型：有向图，无向图*/
    VertexesList v_list[MAX_VERTEX_NUM];/*顶点列表*/
    P_ArcNode  arc_matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; /*边矩阵，只有邻接矩阵使用*/
    int v_num, arc_num;                 /*顶点数，边数*/
}Graphics, *P_Graphics;

//队列
typedef struct
{
    V_Position queue[MAX_VERTEX_NUM];
    int r_p;
    int w_p;
    int count;
}Queue,*P_Queue;

/*创建顶点数据*/
P_V_DataType CreateVertexDataNode(int id,V_TYPE type,double lo,double la,char* name,char* addr)
{
    if(id < 0 || lo < 0 || la < 0){ LINE_DEBUG("Arguments illegal"); return NULL; }
    P_V_DataType new_v_data = (P_V_DataType)malloc(sizeof(V_DataType));
    if(new_v_data == NULL){ LINE_DEBUG("New Vertex Data malloc failed"); return NULL; }
    new_v_data->id = id;
    new_v_data->type = type;
    new_v_data->longtitude = lo;
    new_v_data->latitude = la;
    strncpy(new_v_data->name,name,MAX_DATA_NAME_LEN);
    strncpy(new_v_data->address,addr,MAX_DATA_ADDR_LEN);
    return new_v_data;
}

/*创建顶点*/
P_VertexNode CreateVertexNode(void)
{
    P_VertexNode new_vertex = (P_VertexNode)malloc(sizeof(VertexNode));
    if(new_vertex == NULL){ LINE_DEBUG("New Vertex malloc failed"); return NULL; }
    new_vertex->data = NULL;
    new_vertex->arc_first_in  = NULL;
    new_vertex->arc_first_out = NULL;
    return new_vertex;
}

/*创建边*/
P_ArcNode CreateArcNode(char* info,Power p)
{
    P_ArcNode new_arc = (P_ArcNode)malloc(sizeof(ArcNode));
    if(new_arc == NULL){ LINE_DEBUG("New Arc malloc failed"); return NULL; }
    new_arc->if_visited = UNVISITED;
    new_arc->v_tail     = 0;
    new_arc->v_head     = 0;
    new_arc->arc_head   = NULL;
    new_arc->arc_tail   = NULL;
    new_arc->power      = p;
    strncpy(new_arc->info,info,MAX_EDGE_INFO_LEN);
    return new_arc;
}

/*
 * 邻接矩阵
 * 只用边结构中的info，power等存储边信息的字段，而不需要边与边关系链接的指针。
 * 顶点结构只用data字段。矩阵的组织方法，如0与1 2两个顶点相连，则在0的这一行
 * 的1 2这两列处放上Arc0_1这条边的信息，用1表示，其他列置空用0表示，如下：
 *  顶 0 1 2 3 4 ...
 *  点
 * 0   0 1 1 0 0
 * 1   1 0 0 1 1
 * 2   1 0 0 0 0
 * 3   0 1 0 0 0
 * 4   0 1 0 0 0
 * ...
 */
P_Graphics CreateOneMatrixUndigraph(void)
{
    P_VertexNode V0 = NULL; P_V_DataType V0_data = NULL;
    P_VertexNode V1 = NULL; P_V_DataType V1_data = NULL;
    P_VertexNode V2 = NULL; P_V_DataType V2_data = NULL;
    P_VertexNode V3 = NULL; P_V_DataType V3_data = NULL;
    P_VertexNode V4 = NULL; P_V_DataType V4_data = NULL;
    P_VertexNode V5 = NULL; P_V_DataType V5_data = NULL;
    P_VertexNode V6 = NULL; P_V_DataType V6_data = NULL;
    P_VertexNode V7 = NULL; P_V_DataType V7_data = NULL;
    P_ArcNode Arc0_1 = NULL; P_ArcNode Arc0_2 = NULL;
    P_ArcNode Arc1_3 = NULL; P_ArcNode Arc1_4 = NULL;
    P_ArcNode Arc2_5 = NULL; P_ArcNode Arc6_2 = NULL;
    P_ArcNode Arc3_7 = NULL; P_ArcNode Arc4_7 = NULL;
    P_ArcNode Arc5_6 = NULL;
    P_Graphics new_undigraph = NULL;
    
    //点和点数据
    V0 = CreateVertexNode(); V1 = CreateVertexNode();
    V2 = CreateVertexNode(); V3 = CreateVertexNode();
    V4 = CreateVertexNode(); V5 = CreateVertexNode();
    V6 = CreateVertexNode(); V7 = CreateVertexNode();
    V0_data = CreateVertexDataNode(0,SHOP,123.52,175.21,"家乐福超市","郑州金水路10号");
    V1_data = CreateVertexDataNode(1,MOVIES,103.54,123.14,"万达影院","杭州市西湖路67号");
    V2_data = CreateVertexDataNode(2,GARDEN,93.78,142.01,"上海迪斯尼乐园","上海市浦东区霞飞路054号");
    V3_data = CreateVertexDataNode(3,PARK,41.32,75.47,"苏宁集团地下停车场","南京市建邺区青年路地铁口");
    V4_data = CreateVertexDataNode(4,GOVERNMENT,124.37,154.00,"杭州市政府","杭州市九曲路南杭州市人民政府");
    V5_data = CreateVertexDataNode(5,SCHOOL,142.01,86.32,"郑州市第七中学","郑州三全路7号");
    V6_data = CreateVertexDataNode(6,HOUSE,107.32,53.47,"故宫博物院家","北京市长安街127号");
    V7_data = CreateVertexDataNode(7,UNKNOWN,67.98,45,"军事管理区","北京海淀区");
    if(V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL 
    || V4 == NULL || V5 == NULL || V6 == NULL || V7 == NULL)
    { 
	LINE_DEBUG("V malloc failed");
	goto Label_CreateOneMatrixUndigraph_Clean;
    }
    if(V0_data == NULL || V1_data == NULL || V2_data == NULL || V3_data == NULL
    || V4_data == NULL || V5_data == NULL || V6_data == NULL || V7_data == NULL)
    { 
	LINE_DEBUG("V_data malloc failed");
	goto Label_CreateOneMatrixUndigraph_Clean;
    }
    
    //边
    Arc0_1 = CreateArcNode("V0->V1",5); Arc0_2 = CreateArcNode("V0->V2",12);
    Arc1_3 = CreateArcNode("V1->V3",7); Arc1_4 = CreateArcNode("V1->V4",-4);
    Arc2_5 = CreateArcNode("V2->V5",0); Arc6_2 = CreateArcNode("V6->V2",5);
    Arc3_7 = CreateArcNode("V3->V7",8); Arc4_7 = CreateArcNode("V4->V7",10);
    Arc5_6 = CreateArcNode("V5->V6",17);
    if(Arc0_1 == NULL || Arc0_2 == NULL || Arc1_3 == NULL || Arc1_4 == NULL
    || Arc2_5 == NULL || Arc6_2 == NULL || Arc3_7 == NULL || Arc4_7 == NULL
    || Arc5_6 == NULL)
    { 
	LINE_DEBUG("Arc malloc failed");
	goto Label_CreateOneMatrixUndigraph_Clean;
    }
    
    //图
    new_undigraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_undigraph == NULL)
    { LINE_DEBUG("New Undigraph malloc failed"); goto Label_CreateOneMatrixUndigraph_Clean; }
    new_undigraph->g_type = UNDIGRAPH;
    //矩阵清0
    memset(new_undigraph->arc_matrix,0,MAX_VERTEX_NUM*MAX_VERTEX_NUM);
    new_undigraph->v_num   = 8;
    new_undigraph->arc_num = 9;

    //关系组织
    V0->data = V0_data; V1->data = V1_data; V2->data = V2_data; V3->data = V3_data;
    V4->data = V4_data; V5->data = V5_data; V6->data = V6_data; V7->data = V7_data;

    new_undigraph->v_list[0] = V0; new_undigraph->v_list[1] = V1;
    new_undigraph->v_list[2] = V2; new_undigraph->v_list[3] = V3;
    new_undigraph->v_list[4] = V4; new_undigraph->v_list[5] = V5;
    new_undigraph->v_list[6] = V6; new_undigraph->v_list[7] = V7;
    new_undigraph->arc_matrix[0][1] = Arc0_1; new_undigraph->arc_matrix[0][2] = Arc0_2;
    new_undigraph->arc_matrix[1][0] = Arc0_1; new_undigraph->arc_matrix[1][3] = Arc1_3;
    new_undigraph->arc_matrix[1][4] = Arc1_4;
    new_undigraph->arc_matrix[2][0] = Arc0_2; new_undigraph->arc_matrix[2][5] = Arc2_5;
    new_undigraph->arc_matrix[2][6] = Arc6_2;
    new_undigraph->arc_matrix[3][1] = Arc1_3; new_undigraph->arc_matrix[3][7] = Arc3_7;
    new_undigraph->arc_matrix[4][1] = Arc1_4; new_undigraph->arc_matrix[4][7] = Arc4_7;
    new_undigraph->arc_matrix[5][2] = Arc2_5; new_undigraph->arc_matrix[5][6] = Arc5_6;
    new_undigraph->arc_matrix[6][2] = Arc6_2; new_undigraph->arc_matrix[6][5] = Arc5_6;
    new_undigraph->arc_matrix[7][3] = Arc3_7; new_undigraph->arc_matrix[7][4] = Arc4_7;
    
    return new_undigraph;
    
Label_CreateOneMatrixUndigraph_Clean:
    SAFE_FREE(V0); SAFE_FREE(V0_data); SAFE_FREE(V1); SAFE_FREE(V1_data);
    SAFE_FREE(V2); SAFE_FREE(V2_data); SAFE_FREE(V3); SAFE_FREE(V3_data);
    SAFE_FREE(V4); SAFE_FREE(V4_data); SAFE_FREE(V5); SAFE_FREE(V5_data);
    SAFE_FREE(V6); SAFE_FREE(V6_data); SAFE_FREE(V7); SAFE_FREE(V7_data);
    SAFE_FREE(Arc0_1); SAFE_FREE(Arc0_2); SAFE_FREE(Arc1_3); SAFE_FREE(Arc1_4);
    SAFE_FREE(Arc2_5); SAFE_FREE(Arc6_2); SAFE_FREE(Arc3_7); SAFE_FREE(Arc4_7);
    SAFE_FREE(Arc5_6);
    SAFE_FREE(new_undigraph);
    return NULL;
}

/*
 * 邻接表存储无向图
 * 只是用这里边结构的info v_head arc_head三个字段，分别代表邻接表所表示的边
 * 的信息，另一个顶点在图中的位置，下一条边。点结构只使用data arc_first_out两
 * 个字段表示点的信息，第一条（以该顶点为尾的）边。
 * 邻接表的无向图同一条边要有表示为两条，如V0-V1，要表示为Arc0_1/Arc1_0两条，分
 * 别作为顶点V0的边链表中的节点和V1的边链表中的节点。
 * 如顶点V1，与V1有关的边有 V1-V0 V1-V3 V1-V4
 * 则邻接表表示为：G->v_list[0]->arc_first_in = Arc1_0;1在Arc1_0的另一个顶点是0，
 * 所以Arc1_0->v_head = 0;1的下一条边是Arc1_3，所以Arc1_0->arc_head = Arc1_3;
 * 依次类推，Arc1_3->v_head = 3;Arc1_3->arc_head = Arc1_4;Arc1_4->v_head=4;
 * Arc1_4->arc_head = NULL;从而形成一条关于V1的边的链表。
 */
P_Graphics CreateOneAdjacencyListUndigraph(void)
{
    P_VertexNode V0 = NULL; P_V_DataType V0_data = NULL;
    P_VertexNode V1 = NULL; P_V_DataType V1_data = NULL;
    P_VertexNode V2 = NULL; P_V_DataType V2_data = NULL;
    P_VertexNode V3 = NULL; P_V_DataType V3_data = NULL;
    P_VertexNode V4 = NULL; P_V_DataType V4_data = NULL;
    P_VertexNode V5 = NULL; P_V_DataType V5_data = NULL;
    P_VertexNode V6 = NULL; P_V_DataType V6_data = NULL;
    P_VertexNode V7 = NULL; P_V_DataType V7_data = NULL;
    P_ArcNode Arc0_1 = NULL; P_ArcNode Arc1_0 = NULL;
    P_ArcNode Arc0_2 = NULL; P_ArcNode Arc2_0 = NULL;
    P_ArcNode Arc1_3 = NULL; P_ArcNode Arc3_1 = NULL;
    P_ArcNode Arc1_4 = NULL; P_ArcNode Arc4_1 = NULL;
    P_ArcNode Arc2_5 = NULL; P_ArcNode Arc5_2 = NULL;
    P_ArcNode Arc6_2 = NULL; P_ArcNode Arc2_6 = NULL;
    P_ArcNode Arc3_7 = NULL; P_ArcNode Arc7_3 = NULL;
    P_ArcNode Arc4_7 = NULL; P_ArcNode Arc7_4 = NULL;
    P_ArcNode Arc5_6 = NULL; P_ArcNode Arc6_5 = NULL;
    P_Graphics new_undigraph = NULL;
    
    //点和点数据
    V0 = CreateVertexNode(); V1 = CreateVertexNode();
    V2 = CreateVertexNode(); V3 = CreateVertexNode();
    V4 = CreateVertexNode(); V5 = CreateVertexNode();
    V6 = CreateVertexNode(); V7 = CreateVertexNode();
    V0_data = CreateVertexDataNode(0,SHOP,123.52,175.21,"家乐福超市","郑州金水路10号");
    V1_data = CreateVertexDataNode(1,MOVIES,103.54,123.14,"万达影院","杭州市西湖路67号");
    V2_data = CreateVertexDataNode(2,GARDEN,93.78,142.01,"上海迪斯尼乐园","上海市浦东区霞飞路054号");
    V3_data = CreateVertexDataNode(3,PARK,41.32,75.47,"苏宁集团地下停车场","南京市建邺区青年路地铁口");
    V4_data = CreateVertexDataNode(4,GOVERNMENT,124.37,154.00,"杭州市政府","杭州市九曲路南杭州市人民政府");
    V5_data = CreateVertexDataNode(5,SCHOOL,142.01,86.32,"郑州市第七中学","郑州三全路7号");
    V6_data = CreateVertexDataNode(6,HOUSE,107.32,53.47,"故宫博物院家","北京市长安街127号");
    V7_data = CreateVertexDataNode(7,UNKNOWN,67.98,45,"军事管理区","北京海淀区");
    if(V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL 
    || V4 == NULL || V5 == NULL || V6 == NULL || V7 == NULL)
    { 
	LINE_DEBUG("V malloc failed");
	goto Label_CreateOneAdjacencyListUndigraph_Clean;
    }
    if(V0_data == NULL || V1_data == NULL || V2_data == NULL || V3_data == NULL
    || V4_data == NULL || V5_data == NULL || V6_data == NULL || V7_data == NULL)
    { 
	LINE_DEBUG("V_data malloc failed");
	goto Label_CreateOneAdjacencyListUndigraph_Clean;
    }
    
    //边
    Arc0_1 = CreateArcNode("V0-V1",5);  Arc1_0 = CreateArcNode("V1-V0",-5);;
    Arc0_2 = CreateArcNode("V0-V2",12); Arc2_0 = CreateArcNode("V2-V0",-12);
    Arc1_3 = CreateArcNode("V1-V3",7);  Arc3_1 = CreateArcNode("V3-V1",-7);
    Arc1_4 = CreateArcNode("V1-V4",-4); Arc4_1 = CreateArcNode("V4-V1",4);
    Arc2_5 = CreateArcNode("V2-V5",0);  Arc5_2 = CreateArcNode("V5-V2",0);
    Arc6_2 = CreateArcNode("V6-V2",5);  Arc2_6 = CreateArcNode("V2-V6",-5);
    Arc3_7 = CreateArcNode("V3-V7",8);  Arc7_3 = CreateArcNode("V7-V3",-8);
    Arc4_7 = CreateArcNode("V4-V7",10); Arc7_4 = CreateArcNode("V7-V4",-10);
    Arc5_6 = CreateArcNode("V5-V6",17); Arc6_5 = CreateArcNode("V6-V5",-17);
    if(Arc0_1 == NULL || Arc0_2 == NULL || Arc1_3 == NULL || Arc1_4 == NULL
    || Arc2_5 == NULL || Arc6_2 == NULL || Arc3_7 == NULL || Arc4_7 == NULL
    || Arc5_6 == NULL || Arc1_0 == NULL || Arc2_0 == NULL || Arc3_1 == NULL
    || Arc4_1 == NULL || Arc5_2 == NULL || Arc2_6 == NULL || Arc7_3 == NULL
    || Arc7_4 == NULL || Arc6_5 == NULL)
    { 
	LINE_DEBUG("Arc malloc failed");
	goto Label_CreateOneAdjacencyListUndigraph_Clean;
    }
    
    //图
    new_undigraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_undigraph == NULL)
    { LINE_DEBUG("New Undigraph malloc failed"); goto Label_CreateOneAdjacencyListUndigraph_Clean; }
    new_undigraph->g_type = UNDIGRAPH;
    new_undigraph->v_num   = 8;
    new_undigraph->arc_num = 18;

    //关系组织
    V0->data = V0_data; V0->arc_first_out = Arc0_1;
    V1->data = V1_data; V1->arc_first_out = Arc1_0;
    V2->data = V2_data; V2->arc_first_out = Arc2_0;
    V3->data = V3_data; V3->arc_first_out = Arc3_1;
    V4->data = V4_data; V4->arc_first_out = Arc4_1;
    V5->data = V5_data; V5->arc_first_out = Arc5_2;
    V6->data = V6_data; V6->arc_first_out = Arc6_2;
    V7->data = V7_data; V7->arc_first_out = Arc7_3;
    
    Arc0_1->v_head = 1; Arc0_1->arc_head = Arc0_2; Arc0_2->v_head = 2; Arc0_2->arc_head = NULL;
    Arc1_0->v_head = 0; Arc1_0->arc_head = Arc1_3; Arc1_3->v_head = 3; Arc1_3->arc_head = Arc1_4;
    Arc1_4->v_head = 4; Arc1_4->arc_head = NULL; 
    Arc2_0->v_head = 0; Arc2_0->arc_head = Arc2_5; Arc2_5->v_head = 5; Arc2_5->arc_head = Arc2_6;
    Arc2_6->v_head = 6; Arc2_6->arc_head = NULL;
    Arc3_1->v_head = 1; Arc3_1->arc_head = Arc3_7; Arc3_7->v_head = 7; Arc3_7->arc_head = NULL;
    Arc4_1->v_head = 1; Arc4_1->arc_head = Arc4_7; Arc4_7->v_head = 7; Arc4_7->arc_head = NULL;
    Arc5_2->v_head = 2; Arc5_2->arc_head = Arc5_6; Arc5_6->v_head = 6; Arc5_6->arc_head = NULL;
    Arc6_2->v_head = 2; Arc6_2->arc_head = Arc6_5; Arc6_5->v_head = 5; Arc6_5->arc_head = NULL;
    Arc7_3->v_head = 3; Arc7_3->arc_head = Arc7_4; Arc7_4->v_head = 4; Arc7_4->arc_head = NULL;

    new_undigraph->v_list[0] = V0; new_undigraph->v_list[1] = V1;
    new_undigraph->v_list[2] = V2; new_undigraph->v_list[3] = V3;
    new_undigraph->v_list[4] = V4; new_undigraph->v_list[5] = V5;
    new_undigraph->v_list[6] = V6; new_undigraph->v_list[7] = V7;
    
    return new_undigraph;

Label_CreateOneAdjacencyListUndigraph_Clean:
    SAFE_FREE(V0); SAFE_FREE(V0_data); SAFE_FREE(V1); SAFE_FREE(V1_data);
    SAFE_FREE(V2); SAFE_FREE(V2_data); SAFE_FREE(V3); SAFE_FREE(V3_data);
    SAFE_FREE(V4); SAFE_FREE(V4_data); SAFE_FREE(V5); SAFE_FREE(V5_data);
    SAFE_FREE(V6); SAFE_FREE(V6_data); SAFE_FREE(V7); SAFE_FREE(V7_data);
    SAFE_FREE(Arc0_1); SAFE_FREE(Arc0_2); SAFE_FREE(Arc1_3); SAFE_FREE(Arc1_4);
    SAFE_FREE(Arc2_5); SAFE_FREE(Arc6_2); SAFE_FREE(Arc3_7); SAFE_FREE(Arc4_7);
    SAFE_FREE(Arc5_6); SAFE_FREE(Arc1_0); SAFE_FREE(Arc3_1); SAFE_FREE(Arc4_1);
    SAFE_FREE(Arc5_2); SAFE_FREE(Arc2_6); SAFE_FREE(Arc7_3); SAFE_FREE(Arc7_4);
    SAFE_FREE(Arc6_5); SAFE_FREE(Arc2_0);
    SAFE_FREE(new_undigraph);
    return NULL;
}

/*
 * 邻接表表示有向图
 * 基本与无向图一致，只是边链表不同，如V1点，只有以V1为尾顶点的弧才能作
 * 为V1的边链表的节点。与V1有关的边有V0->V1,V1->V3,V1->V4,其中只有V1->V3,
 * V1->V4作为V1的边链表节点。
 */
P_Graphics CreateOneAdjacencyListDigraph(void)
{
    P_VertexNode V0 = NULL; P_V_DataType V0_data = NULL;
    P_VertexNode V1 = NULL; P_V_DataType V1_data = NULL;
    P_VertexNode V2 = NULL; P_V_DataType V2_data = NULL;
    P_VertexNode V3 = NULL; P_V_DataType V3_data = NULL;
    P_VertexNode V4 = NULL; P_V_DataType V4_data = NULL;
    P_VertexNode V5 = NULL; P_V_DataType V5_data = NULL;
    P_VertexNode V6 = NULL; P_V_DataType V6_data = NULL;
    P_VertexNode V7 = NULL; P_V_DataType V7_data = NULL;
    P_ArcNode Arc0_1 = NULL; P_ArcNode Arc0_2 = NULL;
    P_ArcNode Arc1_3 = NULL; P_ArcNode Arc1_4 = NULL;
    P_ArcNode Arc2_5 = NULL; P_ArcNode Arc6_2 = NULL;
    P_ArcNode Arc3_7 = NULL; P_ArcNode Arc4_7 = NULL;
    P_ArcNode Arc5_6 = NULL;
    P_Graphics new_digraph = NULL;
    
    //点和点数据
    V0 = CreateVertexNode(); V1 = CreateVertexNode();
    V2 = CreateVertexNode(); V3 = CreateVertexNode();
    V4 = CreateVertexNode(); V5 = CreateVertexNode();
    V6 = CreateVertexNode(); V7 = CreateVertexNode();
    V0_data = CreateVertexDataNode(0,SHOP,123.52,175.21,"家乐福超市","郑州金水路10号");
    V1_data = CreateVertexDataNode(1,MOVIES,103.54,123.14,"万达影院","杭州市西湖路67号");
    V2_data = CreateVertexDataNode(2,GARDEN,93.78,142.01,"上海迪斯尼乐园","上海市浦东区霞飞路054号");
    V3_data = CreateVertexDataNode(3,PARK,41.32,75.47,"苏宁集团地下停车场","南京市建邺区青年路地铁口");
    V4_data = CreateVertexDataNode(4,GOVERNMENT,124.37,154.00,"杭州市政府","杭州市九曲路南杭州市人民政府");
    V5_data = CreateVertexDataNode(5,SCHOOL,142.01,86.32,"郑州市第七中学","郑州三全路7号");
    V6_data = CreateVertexDataNode(6,HOUSE,107.32,53.47,"故宫博物院家","北京市长安街127号");
    V7_data = CreateVertexDataNode(7,UNKNOWN,67.98,45,"军事管理区","北京海淀区");
    if(V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL 
    || V4 == NULL || V5 == NULL || V6 == NULL || V7 == NULL)
    { 
	LINE_DEBUG("V malloc failed");
	goto Label_CreateOneAdjacencyListDigraph_Clean;
    }
    if(V0_data == NULL || V1_data == NULL || V2_data == NULL || V3_data == NULL
    || V4_data == NULL || V5_data == NULL || V6_data == NULL || V7_data == NULL)
    { 
	LINE_DEBUG("V_data malloc failed");
	goto Label_CreateOneAdjacencyListDigraph_Clean;
    }
    
    //边
    Arc0_1 = CreateArcNode("V0->V1",5); Arc0_2 = CreateArcNode("V0->V2",12);
    Arc1_3 = CreateArcNode("V1->V3",7); Arc1_4 = CreateArcNode("V1->V4",-4);
    Arc2_5 = CreateArcNode("V2->V5",0); Arc6_2 = CreateArcNode("V6->V2",5);
    Arc3_7 = CreateArcNode("V3->V7",8); Arc4_7 = CreateArcNode("V4->V7",10);
    Arc5_6 = CreateArcNode("V5->V6",17);
    if(Arc0_1 == NULL || Arc0_2 == NULL || Arc1_3 == NULL || Arc1_4 == NULL
    || Arc2_5 == NULL || Arc6_2 == NULL || Arc3_7 == NULL || Arc4_7 == NULL
    || Arc5_6 == NULL)
    { 
	LINE_DEBUG("Arc malloc failed");
	goto Label_CreateOneAdjacencyListDigraph_Clean;
    }
    
    //图
    new_digraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_digraph == NULL)
    { LINE_DEBUG("New Undigraph malloc failed"); goto Label_CreateOneAdjacencyListDigraph_Clean; }
    new_digraph->g_type = DIGRAPH;
    new_digraph->v_num   = 8;
    new_digraph->arc_num = 9;

    //关系组织
    V0->data = V0_data; V0->arc_first_out = Arc0_1;
    V1->data = V1_data; V1->arc_first_out = Arc1_3;
    V2->data = V2_data; V2->arc_first_out = Arc2_5;
    V3->data = V3_data; V3->arc_first_out = Arc3_7;
    V4->data = V4_data; V4->arc_first_out = Arc4_7;
    V5->data = V5_data; V5->arc_first_out = Arc5_6;
    V6->data = V6_data; V6->arc_first_out = Arc6_2;
    V7->data = V7_data; V7->arc_first_out = NULL;
   
    Arc0_1->v_head = 1; Arc0_1->arc_head = Arc0_2; Arc0_2->v_head = 2; Arc0_2->arc_head = NULL;
    Arc1_3->v_head = 3; Arc1_3->arc_head = Arc1_4; Arc1_4->v_head = 4; Arc1_4->arc_head = NULL;
    Arc2_5->v_head = 5; Arc2_5->arc_head = NULL;    
    Arc3_7->v_head = 7; Arc3_7->arc_head = NULL;
    Arc4_7->v_head = 7; Arc4_7->arc_head = NULL;
    Arc5_6->v_head = 6; Arc5_6->arc_head = NULL;
    Arc6_2->v_head = 2; Arc6_2->arc_head = NULL;

    new_digraph->v_list[0] = V0; new_digraph->v_list[1] = V1;
    new_digraph->v_list[2] = V2; new_digraph->v_list[3] = V3;
    new_digraph->v_list[4] = V4; new_digraph->v_list[5] = V5;
    new_digraph->v_list[6] = V6; new_digraph->v_list[7] = V7;
    
    return new_digraph;

Label_CreateOneAdjacencyListDigraph_Clean:
    SAFE_FREE(V0); SAFE_FREE(V0_data); SAFE_FREE(V1); SAFE_FREE(V1_data);
    SAFE_FREE(V2); SAFE_FREE(V2_data); SAFE_FREE(V3); SAFE_FREE(V3_data);
    SAFE_FREE(V4); SAFE_FREE(V4_data); SAFE_FREE(V5); SAFE_FREE(V5_data);
    SAFE_FREE(V6); SAFE_FREE(V6_data); SAFE_FREE(V7); SAFE_FREE(V7_data);
    SAFE_FREE(Arc0_1); SAFE_FREE(Arc0_2); SAFE_FREE(Arc1_3); SAFE_FREE(Arc1_4);
    SAFE_FREE(Arc2_5); SAFE_FREE(Arc6_2); SAFE_FREE(Arc3_7); SAFE_FREE(Arc4_7);
    SAFE_FREE(Arc5_6);
    SAFE_FREE(new_digraph);
    return NULL;
}

/* 手工创建一个连通无向图
 * 这里的存储结构为邻接多重表
 * 1.边节点
 * if_visited标识是否被访问过。v_tail表示(尾)节点，v_head表示(头)节点，
 * info表示边的信息。
 * 图中有边 V0-V1 V0-V2 V1-V3 V1-V4 V3-V7 V4-V7 V2-V5 V5-V6 V6-V2
 * 则如 V0 V1顶点的边链表：
 *    V0      V1      所有与V0相关的边有Arc0_1 Arc0_2，则节点中与0相关的字段
 *  V0-V1   V0-V1     分别为两条边的v_tail和arc_tail，设Arc0_1为V0的第一条边，
 *   |        /       则有Arc0_1->arc_tail=Arc0_2; Arc0_2->arc_tail=NULL;形成
 *  V0-V2   V1-V3     一个关于V0的一条链表。
 *   |      |         所有与V1相关的边有Arc0_1,Arc1_3,Arc1_4，则节点中与1相关的
 *  NULL    V1-V4     字段分别是Arc0_1->v_head/arc_head,Arc1_3->v_tail/arc_tail,
 *          |         Arc1_4->v_tail/arc_tial，设Arc0_1为V1的第一条边，则有Arc0_1
 *          NULL      ->arc_head=Arc1_3;Arc1_3->arc_tail=Arc1_4;Arc1_4->arc_tail
 *                    =NULL;形成了关于V1的一条链表。
 *  其余顶点链表依次类推。其中每个顶点的第一条边和其他相关边的前后顺序是自定义的，
 *  只要保证每个顶点能形成一条链表就行。再次定名为边链表Arcs_List。
 * 2.点节点
 * data表示顶点数据，arc_first_in为以改顶点为(尾)的所依附的第一条边，从此
 * 边开始搜索。
 * 3.根据邻接多重表的形式可知，每条边和每个定点都会被存储两遍。从一个点到另一个点，
 * 是纵向深入的方向，从一个点的一条边到这个点的另一条边，是横向广度渗透的方向。每
 * 个顶点的边链表就相当于这个顶点为父节点的一个个子分支。如
 *     V0                 V1
 *    /  \              / | \
 *   V1   V2           V0 V2 V4
 * 4.相较于邻接表，邻接多重表节省了一半的空间，即一条边只表示为一条就够用了。
 *   从V0访问V1和从V1访问V0走同一条边，多重表通过共享边节点中的arc_tail和arc_head
 *   两个字段来达到节省一半空间的目的。
 */
P_Graphics CreateOneMultilistUndigraph(void)
{
    P_VertexNode V0 = NULL; P_V_DataType V0_data = NULL;
    P_VertexNode V1 = NULL; P_V_DataType V1_data = NULL;
    P_VertexNode V2 = NULL; P_V_DataType V2_data = NULL;
    P_VertexNode V3 = NULL; P_V_DataType V3_data = NULL;
    P_VertexNode V4 = NULL; P_V_DataType V4_data = NULL;
    P_VertexNode V5 = NULL; P_V_DataType V5_data = NULL;
    P_VertexNode V6 = NULL; P_V_DataType V6_data = NULL;
    P_VertexNode V7 = NULL; P_V_DataType V7_data = NULL;
    P_ArcNode Arc0_1 = NULL; P_ArcNode Arc0_2 = NULL;
    P_ArcNode Arc1_3 = NULL; P_ArcNode Arc1_4 = NULL;
    P_ArcNode Arc2_5 = NULL; P_ArcNode Arc6_2 = NULL;
    P_ArcNode Arc3_7 = NULL; P_ArcNode Arc4_7 = NULL;
    P_ArcNode Arc5_6 = NULL;
    P_Graphics new_undigraph = NULL;
    
    //点和点数据
    V0 = CreateVertexNode(); V1 = CreateVertexNode();
    V2 = CreateVertexNode(); V3 = CreateVertexNode();
    V4 = CreateVertexNode(); V5 = CreateVertexNode();
    V6 = CreateVertexNode(); V7 = CreateVertexNode();
    V0_data = CreateVertexDataNode(0,SHOP,123.52,175.21,"家乐福超市","郑州金水路10号");
    V1_data = CreateVertexDataNode(1,MOVIES,103.54,123.14,"万达影院","杭州市西湖路67号");
    V2_data = CreateVertexDataNode(2,GARDEN,93.78,142.01,"上海迪斯尼乐园","上海市浦东区霞飞路054号");
    V3_data = CreateVertexDataNode(3,PARK,41.32,75.47,"苏宁集团地下停车场","南京市建邺区青年路地铁口");
    V4_data = CreateVertexDataNode(4,GOVERNMENT,124.37,154.00,"杭州市政府","杭州市九曲路南杭州市人民政府");
    V5_data = CreateVertexDataNode(5,SCHOOL,142.01,86.32,"郑州市第七中学","郑州三全路7号");
    V6_data = CreateVertexDataNode(6,HOUSE,107.32,53.47,"故宫博物院家","北京市长安街127号");
    V7_data = CreateVertexDataNode(7,UNKNOWN,67.98,45,"军事管理区","北京海淀区");
    if(V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL 
    || V4 == NULL || V5 == NULL || V6 == NULL || V7 == NULL)
    { 
	LINE_DEBUG("V malloc failed");
	goto Label_CreateOneMultilistUndigraph_Clean;
    }
    if(V0_data == NULL || V1_data == NULL || V2_data == NULL || V3_data == NULL
    || V4_data == NULL || V5_data == NULL || V6_data == NULL || V7_data == NULL)
    { 
	LINE_DEBUG("V_data malloc failed");
	goto Label_CreateOneMultilistUndigraph_Clean;
    }
    
    //边
    Arc0_1 = CreateArcNode("V0-V1",5); Arc0_2 = CreateArcNode("V0-V2",12);
    Arc1_3 = CreateArcNode("V1-V3",7); Arc1_4 = CreateArcNode("V1-V4",-4);
    Arc2_5 = CreateArcNode("V2-V5",0); Arc6_2 = CreateArcNode("V6-V2",5);
    Arc3_7 = CreateArcNode("V3-V7",8); Arc4_7 = CreateArcNode("V4-V7",10);
    Arc5_6 = CreateArcNode("V5-V6",17);
    if(Arc0_1 == NULL || Arc0_2 == NULL || Arc1_3 == NULL || Arc1_4 == NULL
    || Arc2_5 == NULL || Arc6_2 == NULL || Arc3_7 == NULL || Arc4_7 == NULL
    || Arc5_6 == NULL)
    { 
	LINE_DEBUG("Arc malloc failed");
	goto Label_CreateOneMultilistUndigraph_Clean;
    }
    
    //图
    new_undigraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_undigraph == NULL)
    { LINE_DEBUG("New Undigraph malloc failed"); goto Label_CreateOneMultilistUndigraph_Clean; }
    new_undigraph->g_type = UNDIGRAPH;
    new_undigraph->v_num   = 8;
    new_undigraph->arc_num = 9;

    //关系组织
    V0->data = V0_data; V0->arc_first_in = Arc0_1;
    V1->data = V1_data; V1->arc_first_in = Arc0_1;
    V2->data = V2_data; V2->arc_first_in = Arc0_2;
    V3->data = V3_data; V3->arc_first_in = Arc1_3;
    V4->data = V4_data; V4->arc_first_in = Arc1_4;
    V5->data = V5_data; V5->arc_first_in = Arc2_5;
    V6->data = V6_data; V6->arc_first_in = Arc5_6;
    V7->data = V7_data; V7->arc_first_in = Arc3_7;
   
    Arc0_1->v_tail = 0; Arc0_1->arc_tail = Arc0_2; Arc0_1->v_head = 1; Arc0_1->arc_head = Arc1_3;
    Arc0_2->v_tail = 0; Arc0_2->arc_tail = NULL;   Arc0_2->v_head = 2; Arc0_2->arc_head = Arc2_5;
    Arc1_3->v_tail = 1; Arc1_3->arc_tail = Arc1_4; Arc1_3->v_head = 3; Arc1_3->arc_head = Arc3_7;
    Arc1_4->v_tail = 1; Arc1_4->arc_tail = NULL;   Arc1_4->v_head = 4; Arc1_4->arc_head = Arc4_7;
    Arc3_7->v_tail = 3; Arc3_7->arc_tail = NULL;   Arc3_7->v_head = 7; Arc3_7->arc_head = Arc4_7;
    Arc4_7->v_tail = 4; Arc4_7->arc_tail = NULL;   Arc4_7->v_head = 7; Arc4_7->arc_head = NULL;
    Arc2_5->v_tail = 2; Arc2_5->arc_tail = Arc6_2; Arc2_5->v_head = 5; Arc2_5->arc_head = Arc5_6;
    Arc5_6->v_tail = 5; Arc5_6->arc_tail = NULL;   Arc5_6->v_head = 6; Arc5_6->arc_head = Arc6_2;
    Arc6_2->v_tail = 6; Arc6_2->arc_tail = NULL;   Arc6_2->v_head = 2; Arc6_2->arc_head = NULL;

    new_undigraph->v_list[0] = V0; new_undigraph->v_list[1] = V1;
    new_undigraph->v_list[2] = V2; new_undigraph->v_list[3] = V3;
    new_undigraph->v_list[4] = V4; new_undigraph->v_list[5] = V5;
    new_undigraph->v_list[6] = V6; new_undigraph->v_list[7] = V7;
    
    return new_undigraph;

Label_CreateOneMultilistUndigraph_Clean:
    SAFE_FREE(V0); SAFE_FREE(V0_data); SAFE_FREE(V1); SAFE_FREE(V1_data);
    SAFE_FREE(V2); SAFE_FREE(V2_data); SAFE_FREE(V3); SAFE_FREE(V3_data);
    SAFE_FREE(V4); SAFE_FREE(V4_data); SAFE_FREE(V5); SAFE_FREE(V5_data);
    SAFE_FREE(V6); SAFE_FREE(V6_data); SAFE_FREE(V7); SAFE_FREE(V7_data);
    SAFE_FREE(Arc0_1); SAFE_FREE(Arc0_2); SAFE_FREE(Arc1_3); SAFE_FREE(Arc1_4);
    SAFE_FREE(Arc2_5); SAFE_FREE(Arc6_2); SAFE_FREE(Arc3_7); SAFE_FREE(Arc4_7);
    SAFE_FREE(Arc5_6);
    SAFE_FREE(new_undigraph);
    return NULL;
}

/* 手工创建一个有向图，这里使用的是十字链表的存储方式。
 * 和无向图一样，只是带有明确的方向，V0->V1 V0->V2 V1->V3 V1->V4 V4->V7
 * V3->V7 V2->V5 V5->V6 V6->V2
 * 1.边节点，链表其中以V0 V1举例
 *                        V0                V1
 * V->arc_first_out -> V0 -> V1          V1 -> V3
 *                     |                 |
 *                     V0 -> V2          V1 -> V4
 *                     |                 |
 *                    NULL              NULL
 * V->arc_first_in  -> NULL              V0 -> V1     V0没有入边，V1只有一条
 *                                             |      入边。Arc0_1->arc_head=NULL;
 *                                             NULL
 * 十字链表：与V0 V1直接相关的所有边如上，分为out和in两种边，分别自己指定
 * 第一条out边和第一条in边，然后其他的out/in边紧跟其后形成两条边链表，分
 * 别表示一个顶点所有的入度边和出度边。
 * 如v_list[0]->arc_first_out=Arc0_1;Arc0_1->arc_tail = Arc0_2;
 *   Arc0_2->arc_tail = NULL; v_list[0]->arc_first_in = NULL;
 */
P_Graphics CreateOneOrthogonalListDigraph(void)
{
    P_VertexNode V0 = NULL; P_V_DataType V0_data = NULL;
    P_VertexNode V1 = NULL; P_V_DataType V1_data = NULL;
    P_VertexNode V2 = NULL; P_V_DataType V2_data = NULL;
    P_VertexNode V3 = NULL; P_V_DataType V3_data = NULL;
    P_VertexNode V4 = NULL; P_V_DataType V4_data = NULL;
    P_VertexNode V5 = NULL; P_V_DataType V5_data = NULL;
    P_VertexNode V6 = NULL; P_V_DataType V6_data = NULL;
    P_VertexNode V7 = NULL; P_V_DataType V7_data = NULL;
    P_ArcNode Arc0_1 = NULL; P_ArcNode Arc0_2 = NULL;
    P_ArcNode Arc1_3 = NULL; P_ArcNode Arc1_4 = NULL;
    P_ArcNode Arc2_5 = NULL; P_ArcNode Arc6_2 = NULL;
    P_ArcNode Arc3_7 = NULL; P_ArcNode Arc4_7 = NULL;
    P_ArcNode Arc5_6 = NULL;
    P_Graphics new_digraph = NULL;
    
    //点和点数据
    V0 = CreateVertexNode(); V1 = CreateVertexNode();
    V2 = CreateVertexNode(); V3 = CreateVertexNode();
    V4 = CreateVertexNode(); V5 = CreateVertexNode();
    V6 = CreateVertexNode(); V7 = CreateVertexNode();
    V0_data = CreateVertexDataNode(0,SHOP,123.52,175.21,"家乐福超市","郑州金水路10号");
    V1_data = CreateVertexDataNode(1,MOVIES,103.54,123.14,"万达影院","杭州市西湖路67号");
    V2_data = CreateVertexDataNode(2,GARDEN,93.78,142.01,"上海迪斯尼乐园","上海市浦东区霞飞路054号");
    V3_data = CreateVertexDataNode(3,PARK,41.32,75.47,"苏宁集团地下停车场","南京市建邺区青年路地铁口");
    V4_data = CreateVertexDataNode(4,GOVERNMENT,124.37,154.00,"杭州市政府","杭州市九曲路南杭州市人民政府");
    V5_data = CreateVertexDataNode(5,SCHOOL,142.01,86.32,"郑州市第七中学","郑州三全路7号");
    V6_data = CreateVertexDataNode(6,HOUSE,107.32,53.47,"故宫博物院家","北京市长安街127号");
    V7_data = CreateVertexDataNode(7,UNKNOWN,67.98,45,"军事管理区","北京海淀区");
    if(V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL 
    || V4 == NULL || V5 == NULL || V6 == NULL || V7 == NULL)
    { 
	LINE_DEBUG("V malloc failed");
	goto Label_CreateOneOrthogonalListDigraph_Clean;
    }
    if(V0_data == NULL || V1_data == NULL || V2_data == NULL || V3_data == NULL
    || V4_data == NULL || V5_data == NULL || V6_data == NULL || V7_data == NULL)
    { 
	LINE_DEBUG("V_data malloc failed");
	goto Label_CreateOneOrthogonalListDigraph_Clean;
    }
    
    //边
    Arc0_1 = CreateArcNode("V0->V1",5); Arc0_2 = CreateArcNode("V0->V2",12);
    Arc1_3 = CreateArcNode("V1->V3",7); Arc1_4 = CreateArcNode("V1->V4",-4);
    Arc2_5 = CreateArcNode("V2->V5",0); Arc6_2 = CreateArcNode("V6->V2",5);
    Arc3_7 = CreateArcNode("V3->V7",8); Arc4_7 = CreateArcNode("V4->V7",10);
    Arc5_6 = CreateArcNode("V5->V6",17);
    if(Arc0_1 == NULL || Arc0_2 == NULL || Arc1_3 == NULL || Arc1_4 == NULL
    || Arc2_5 == NULL || Arc6_2 == NULL || Arc3_7 == NULL || Arc4_7 == NULL
    || Arc5_6 == NULL)
    { 
	LINE_DEBUG("Arc malloc failed");
	goto Label_CreateOneOrthogonalListDigraph_Clean;
    }
    
    //图
    new_digraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_digraph == NULL)
    { LINE_DEBUG("New Digraph malloc failed"); goto Label_CreateOneOrthogonalListDigraph_Clean; }
    new_digraph->g_type = DIGRAPH;
    new_digraph->v_num   = 8;
    new_digraph->arc_num = 9;

    //关系组织
    V0->data = V0_data; V0->arc_first_in = NULL;   V0->arc_first_out = Arc0_1;
    V1->data = V1_data; V1->arc_first_in = Arc0_1; V1->arc_first_out = Arc1_3;
    V2->data = V2_data; V2->arc_first_in = Arc0_2; V2->arc_first_out = Arc2_5;
    V3->data = V3_data; V3->arc_first_in = Arc1_3; V3->arc_first_out = Arc3_7;
    V4->data = V4_data; V4->arc_first_in = Arc1_4; V4->arc_first_out = Arc4_7;
    V5->data = V5_data; V5->arc_first_in = Arc2_5; V5->arc_first_out = Arc5_6;
    V6->data = V6_data; V6->arc_first_in = Arc5_6; V6->arc_first_out = Arc6_2;
    V7->data = V7_data; V7->arc_first_in = Arc3_7; V7->arc_first_out = NULL;

    Arc0_1->v_tail = 0; Arc0_1->arc_tail = Arc0_2; Arc0_1->v_head = 1; Arc0_1->arc_head = NULL;
    Arc0_2->v_tail = 0; Arc0_2->arc_tail = NULL;   Arc0_2->v_head = 2; Arc0_2->arc_head = Arc6_2;
    Arc1_3->v_tail = 1; Arc1_3->arc_tail = Arc1_4; Arc1_3->v_head = 3; Arc1_3->arc_head = NULL;
    Arc1_4->v_tail = 1; Arc1_4->arc_tail = NULL;   Arc1_4->v_head = 4; Arc1_4->arc_head = NULL;
    Arc2_5->v_tail = 2; Arc2_5->arc_tail = NULL;   Arc2_5->v_head = 5; Arc2_5->arc_head = NULL;
    Arc6_2->v_tail = 6; Arc6_2->arc_tail = NULL;   Arc6_2->v_head = 2; Arc6_2->arc_head = NULL;
    Arc3_7->v_tail = 3; Arc3_7->arc_tail = NULL;   Arc3_7->v_head = 7; Arc3_7->arc_head = Arc4_7;
    Arc4_7->v_tail = 4; Arc4_7->arc_tail = NULL;   Arc4_7->v_head = 7; Arc4_7->arc_head = NULL;
    Arc5_6->v_tail = 5; Arc5_6->arc_tail = NULL;   Arc5_6->v_head = 6; Arc5_6->arc_head = NULL;

    new_digraph->v_list[0] = V0; new_digraph->v_list[1] = V1;
    new_digraph->v_list[2] = V2; new_digraph->v_list[3] = V3;
    new_digraph->v_list[4] = V4; new_digraph->v_list[5] = V5;
    new_digraph->v_list[6] = V6; new_digraph->v_list[7] = V7;
    
    return new_digraph;

Label_CreateOneOrthogonalListDigraph_Clean:
    SAFE_FREE(V0); SAFE_FREE(V0_data); SAFE_FREE(V1); SAFE_FREE(V1_data);
    SAFE_FREE(V2); SAFE_FREE(V2_data); SAFE_FREE(V3); SAFE_FREE(V3_data);
    SAFE_FREE(V4); SAFE_FREE(V4_data); SAFE_FREE(V5); SAFE_FREE(V5_data);
    SAFE_FREE(V6); SAFE_FREE(V6_data); SAFE_FREE(V7); SAFE_FREE(V7_data);
    SAFE_FREE(Arc0_1); SAFE_FREE(Arc0_2); SAFE_FREE(Arc1_3); SAFE_FREE(Arc1_4);
    SAFE_FREE(Arc2_5); SAFE_FREE(Arc6_2); SAFE_FREE(Arc3_7); SAFE_FREE(Arc4_7);
    SAFE_FREE(Arc5_6);
    SAFE_FREE(new_digraph);
    return NULL;
}

inline P_Queue CreateQueue()
{
    P_Queue Q = (P_Queue)malloc(sizeof(Queue));
    if(Q == NULL){ LINE_DEBUG("CreateQueue malloc failed"); return NULL; }
    Q->r_p = 0;
    Q->w_p = 0;
    Q->count = 0;
}

//每次弹出一个元素，由参数p带出
bool Pop(P_Queue Q,V_Position* p)
{
    if(p == NULL){ LINE_DEBUG("Pop argument p is illegal"); return false; }
    if(Q == NULL || Q->count == 0){ LINE_DEBUG("Pop Q is NULL"); return false; }
    
    if((Q->r_p + 1) < MAX_VERTEX_NUM)
    {
	*p = Q->queue[Q->r_p];
	--(Q->count);
	++(Q->r_p);
    }
    else
    {
	*p = Q->queue[Q->r_p];
	--(Q->count);
	Q->r_p = 0;
    }
    return true;
}

//每次压入一个元素
bool Push(P_Queue Q,V_Position p)
{
    if(p < 0 || p >= MAX_VERTEX_NUM){ LINE_DEBUG("Pop argument p is illegal"); return false; }
    if(Q == NULL || Q->count == MAX_VERTEX_NUM){ LINE_DEBUG("Pop Q is NULL or FULL"); return false; }
    if((Q->w_p + 1) < MAX_VERTEX_NUM)
    {
	Q->queue[Q->w_p] = p;
	++(Q->count);
	++(Q->w_p);
    }
    else
    {
	Q->queue[Q->w_p] = p;
	++(Q->count);
	Q->w_p = 0;
    }
}

/*顶点访问标识，true表示访问过，false表示未访问过*/
bool VISITED_FLAGS[MAX_VERTEX_NUM];

/*
 * 邻接矩阵深度/广度优先遍历无向图，有向图一样，略
 */
void Undigraph_Matrix_DFS(P_Graphics G,V_Position s_p,V_Handle_Fun_Type v_handle)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("DFS Start Vertex is illegal"); return; }
    if(v_handle == NULL){ LINE_DEBUG("v_handle is NULL"); return; }
    
    v_handle(G->v_list[s_p]); VISITED_FLAGS[s_p] = true;
    int i,j;
    for(i = s_p; i < G->v_num; ++i)
    {
	for(j = 0; j < G->v_num; ++j)
	{
	    if(G->arc_matrix[i][j] != NULL && VISITED_FLAGS[j] == false)
	    {
		Undigraph_Matrix_DFS(G,j,v_handle);
	    }
	}
    }
}

void Undigraph_Matrix_BFS(P_Graphics G,V_Position s_p,V_Handle_Fun_Type v_handle)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("BFS Start Vertex is illegal"); return; }
    if(v_handle == NULL){ LINE_DEBUG("v_handle is NULL"); return; }

    bool re; V_Position v; int i;
    P_Queue Q = CreateQueue();
    if(Q == NULL){ LINE_DEBUG("Undigraph_Matrix_BFS Queue Create failed"); return; }
    
    re = Push(Q,s_p); VISITED_FLAGS[s_p] = true;
    if(re == false){ LINE_DEBUG("Undigraph_Matrix_BFS Push failed"); return; }

    while(Q->count != 0)
    {
	re = Pop(Q,&v);
	if(v < 0 || re == false){ LINE_DEBUG("Undigraph_Matrix_BFS Pop failed"); return; }

	v_handle(G->v_list[v]); VISITED_FLAGS[v] = true;
	for(i = 0; i < G->v_num; ++i)
	{
	    /*在与弹出的v顶点相连的顶点(G->arc_matrix[v][i]!=NULL)中，将没有被访问过的压入队列并标记*/
	    if(G->arc_matrix[v][i] != NULL && VISITED_FLAGS[i] == false)
	    {
		re = Push(Q,i);
		if(re == false){ LINE_DEBUG("Undigraph_Matrix_BFS Push failed"); return; }
		VISITED_FLAGS[i] = true;
	    }
	}
    }
    SAFE_FREE(Q);
}

/* 邻接表无向图深度/广度优先遍历
 * 根据邻接表的存储结构，其遍历基本上就是对单链表的操作，这个单链表就是顶点的边链表
 * 且邻接表形式存储的无向图和有向图的DFS和BFS算法一样，故有向图实现略
 */
void Undigraph_AdjacencyList_DFS(P_Graphics G,V_Position s_p,V_Handle_Fun_Type v_handle)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("DFS Start Vertex is illegal"); return; }
    if(v_handle == NULL){ LINE_DEBUG("v_handle is NULL"); return; }

    v_handle(G->v_list[s_p]);
    VISITED_FLAGS[s_p] = true;
    //注意邻接表中使用的是arc_first_out这个字段
    P_ArcNode arc = G->v_list[s_p]->arc_first_out;
    while(arc)
    {
	//V_Position another = arc->v_head;
	if(VISITED_FLAGS[arc->v_head] != true)
	{
	    Undigraph_AdjacencyList_DFS(G,arc->v_head,v_handle);
	}
	else
	{
	    arc = arc->arc_head;
	}
    }
}

void Undigraph_AdjacencyList_BFS(P_Graphics G,V_Position s_p,V_Handle_Fun_Type v_handle)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("BFS Start Vertex is illegal"); return; }
    if(v_handle == NULL){ LINE_DEBUG("v_handle is NULL"); return; }

    V_Position v = -1; bool re = false; P_ArcNode arc = NULL;
    
    P_Queue Q = CreateQueue();
    if(Q == NULL){ LINE_DEBUG("DFS Queue malloc failed"); return; }
    re = Push(Q,s_p); VISITED_FLAGS[s_p] = true;
    if(re == false){ LINE_DEBUG("Queue Push failed"); return; }

    while(Q->count != 0)
    {
	re = Pop(Q,&v);
	if(re == false){ LINE_DEBUG("Queue Pop failed"); return; }
	v_handle(G->v_list[v]);
	
	arc = G->v_list[v]->arc_first_out;
	while(arc)
	{
	    if(VISITED_FLAGS[arc->v_head] != true)
	    {
		re = Push(Q,arc->v_head); VISITED_FLAGS[arc->v_head] = true;
		if(re == false){ LINE_DEBUG("Queue Push failed"); return; }
	    }
	    arc = arc->arc_head;
	}
    }
    SAFE_FREE(Q);
}

/* 
 * 多重表无向图的DFS遍历
 * G 图指针 s_p从哪个点开始遍历 v_handle 顶点处理函数，这里只是把顶点信息打印出来
 * 1.遍历方法：每发现一个新的顶点，就首先以此顶点为起点向其深处继续遍历。每个顶点
 * 都会试探性的看看与其直接相连的顶点是否被访问过，若没有，则深入下去。如果碰到一
 * 个顶点被访问过，则跳过，另选一条边，这个是广度方向的渗透。步骤看如下①-⑤，其中
 * ②就相当于树的遍历中的左分支lchild，④就相当于寻找下一个分支（右分支rchild），
 * 因为二叉树只有两个分支，所以下文代码中的遍历方式写二叉树的遍历，迭代部分则为 
 * int i = 0; while(i < 2){ DFS(root->lchild); root->lchild = root->rchild; ++i; }
 */
void Undigraph_Multilist_DFS(P_Graphics G,V_Position s_p,V_Handle_Fun_Type v_handle)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("DFS Start Vertex is illegal"); return; }
    if(v_handle == NULL){ LINE_DEBUG("v_handle is NULL"); return; }
    //1.处理顶点
    v_handle(G->v_list[s_p]);
    VISITED_FLAGS[s_p] = true;
    //2.递归迭代
    //获取顶点v_list[s_p]的边链表
    P_ArcNode arc = G->v_list[s_p]->arc_first_in;
    
    /*⑤直到这个顶点的边链表访问完毕，即该顶点所有的边访问完毕（横向广度渗透）*/
    while(arc)
    {
	/*①获取这条边的另外一个顶点*/
	V_Position another = (s_p == arc->v_tail) ? arc->v_head : arc->v_tail;
	/*②看这条边的另一个顶点是否被访问过*/
	if(VISITED_FLAGS[another] != true)
	{
	    /*③若未访问过，则纵向深入访问（纵向深入遍历）*/
	    Undigraph_Multilist_DFS(G,another,v_handle);
	}
	else
	{
	    /*④若访问过，则通过边链表换该定点的另外一条边，看看这个顶点的另外一条的另一个顶点是否被访问过*/
	    arc = (s_p == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	}
    }
}

/*
 * 多重表无向图BFS遍历
 * 遍历方法：借助队列，首先把开始顶点压入队列，然后每弹出一个顶点后，就将该顶点所有
 * 的直接相关的且未被访问过的顶点压入队列(通过边链表Arc_List找，因为Arc_List就是一个
 * 顶点所有相关边的链表)，若没有符合条件的顶点，则不压入。如此循环，直到队列中再次没
 * 有数据。
 */
void Undigraph_Multilist_BFS(P_Graphics G,V_Position s_p,V_Handle_Fun_Type v_handle)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("BFS Start Vertex is illegal"); return; }
    if(v_handle == NULL){ LINE_DEBUG("v_handle is NULL"); return; }
    V_Position one,another;
    bool re;
    //创建队列
    P_Queue Q = CreateQueue();
    if(Q == NULL){ LINE_DEBUG("BFS Queue Create Failed"); return; }
    //压入开始顶点
    re = Push(Q,s_p); VISITED_FLAGS[s_p] = true;
    if(re == false){ LINE_DEBUG("queue push is wrong"); return; }
    //开始遍历
    while(Q->count != 0)
    {
	//弹出一个顶点
	re = Pop(Q,&one);
	if(re == false){ LINE_DEBUG("queue pop is wrong"); return; }
	//处理该顶点
	v_handle(G->v_list[one]);
	//通过遍历边链表压入该顶点所有直接相关且未被访问过的顶点
	P_ArcNode arc = G->v_list[one]->arc_first_in;
	while(arc)
	{
	    another = (one == arc->v_tail) ? arc->v_head : arc->v_tail;
	    if(VISITED_FLAGS[another] != true)
	    {
		re = Push(Q,another);
		if(re == false){ LINE_DEBUG("queue push is wrong"); return; }
		VISITED_FLAGS[another] = true;
	    }
	    arc = (one == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	}
    }
    //清理
    SAFE_FREE(Q);
}

//十字链表有向图的深度/广度优先遍历
void Digraph_OrthogonalList_DFS(P_Graphics G,V_Position s_p,V_Handle_Fun_Type v_handle)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("DFS Start Vertex is illegal"); return; }
    if(v_handle == NULL){ LINE_DEBUG("v_handle is NULL"); return; }
    
    v_handle(G->v_list[s_p]);
    VISITED_FLAGS[s_p] = true;

    /* 有向图中，如果顶点B是一条边的头，则在遍历中不会再去访问其尾顶点A
     * 但在无向图中必须再去看看A，即便A相对于B来说此时是为尾顶点*/
    P_ArcNode arc = G->v_list[s_p]->arc_first_out;
    while(arc)
    {
	/*对比着无向图看，有向图一直根据边的方向向着头顶点的方向前进*/
	V_Position head = arc->v_head;
	if(VISITED_FLAGS[head] != true)
	{
	    Digraph_OrthogonalList_DFS(G,head,v_handle);
	}
	else
	{
	    arc = arc->arc_tail;
	}
    }
}

void Digraph_OrthogonalList_BFS(P_Graphics G,V_Position s_p,V_Handle_Fun_Type v_handle)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("BFS Start Vertex is illegal"); return; }
    if(v_handle == NULL){ LINE_DEBUG("v_handle is NULL"); return; }
    
    bool re = false; V_Position v = -1; P_ArcNode arc = NULL;

    P_Queue Q = CreateQueue();
    if(Q == NULL){ LINE_DEBUG("Digraph_OrthogonalList_BFS Queue malloc failed"); return; }
    re = Push(Q,s_p); VISITED_FLAGS[s_p] = true;
    if(re == false){ LINE_DEBUG("Push failed"); return; }

    while(Q->count != 0)
    {
	re = Pop(Q,&v);
	if(re == false){ LINE_DEBUG("Queue Pop failed"); return; }
	v_handle(G->v_list[v]);

	arc = G->v_list[v]->arc_first_out;
	while(arc)
	{
	    if(VISITED_FLAGS[arc->v_head] != true)
	    {
		re = Push(Q,arc->v_head); VISITED_FLAGS[arc->v_head] = true;
		if(re == false){ LINE_DEBUG("Queue Push failed"); return; }
	    }
	    arc = arc->arc_tail;
	}
    }
    SAFE_FREE(Q);
}

/*邻接矩阵/邻接表/十字链表/邻接多重表深度/广度优先遍历有向图和无向图*/
void Graphics_Show(P_Graphics G,V_Position v_begin,SHOWMODE show_mode,STRUCTURE structure)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    if(v_begin < 0 || v_begin >= G->v_num){ LINE_DEBUG("Show Start Vertex is illegal"); return; }
    int i = 0;
    while(i < MAX_VERTEX_NUM){ VISITED_FLAGS[i] = false; ++i; }
    
    if(show_mode == DFS && structure == MULTILIST)
    {
	i = v_begin;
	/* 非连通图中需要这样遍历，当一个点的所有能到达的点都被遍历完毕后还存在未被访问的点，
	 * 则说明图是非连通的，存在另一个还未被访问的子图，此时需要重新(随机)选择一个点，进
	 * 行DFS
	 */
	while(i < G->v_num)
	{
	    if(VISITED_FLAGS[i] != true){ Undigraph_Multilist_DFS(G,i,V_Handle1); }
	    ++i;
	}
	i = 0;
	while(i < v_begin)
	{
	    if(VISITED_FLAGS[i] != true){ Undigraph_Multilist_DFS(G,i,V_Handle1); }
	    ++i;
	}
    }
    else if(show_mode == BFS && structure == MULTILIST)
    { 
	i = v_begin;
	while(i < G->v_num)
	{
	    if(VISITED_FLAGS[i] != true){ Undigraph_Multilist_BFS(G,i,V_Handle1); }
	    ++i;
	}
	i = 0;
	while(i < v_begin)
	{
	    if(VISITED_FLAGS[i] != true){ Undigraph_Multilist_BFS(G,i,V_Handle1); }
	    ++i;
	}
    }
    else if(show_mode == DFS && structure == ORTHOGONALLSIT)
    {
	i = v_begin;
	while(i < G->v_num)
	{
	    if(VISITED_FLAGS[i] != true){ Digraph_OrthogonalList_DFS(G,i,V_Handle1); }
	    ++i;
	}
	i = 0;
	while(i < v_begin)
	{
	    if(VISITED_FLAGS[i] != true){ Digraph_OrthogonalList_DFS(G,i,V_Handle1); }
	    ++i;
	}
    }
    else if(show_mode == BFS && structure == ORTHOGONALLSIT)
    {
	i = v_begin;
	while(i < G->v_num)
	{
	    if(VISITED_FLAGS[i] != true){ Digraph_OrthogonalList_BFS(G,i,V_Handle1); }
	    ++i;
	}
	i = 0;
	while(i < v_begin)
	{
	    if(VISITED_FLAGS[i] != true){ Digraph_OrthogonalList_BFS(G,i,V_Handle1); }
	    ++i;
	}
    }
    else if(show_mode == DFS && structure == ADJACENCYLIST && G->g_type == UNDIGRAPH)
    {
	i = v_begin;
	while(i < G->v_num)
	{
	    if(VISITED_FLAGS[i] != true){ Undigraph_AdjacencyList_DFS(G,i,V_Handle1); }
	    ++i;
	}
	i = 0;
	while(i < v_begin)
	{
	    if(VISITED_FLAGS[i] != true){ Undigraph_AdjacencyList_DFS(G,i,V_Handle1); }
	    ++i;
	}
    }
    else if(show_mode == BFS && structure == ADJACENCYLIST && G->g_type == UNDIGRAPH)
    {
	i = v_begin;
	while(i < G->v_num)
	{
	    if(VISITED_FLAGS[i] != true){ Undigraph_AdjacencyList_BFS(G,i,V_Handle1); }
	    ++i;
	}
	i = 0;
	while(i < v_begin)
	{
	    if(VISITED_FLAGS[i] != true){ Undigraph_AdjacencyList_BFS(G,i,V_Handle1); }
	    ++i;
	}
    }
    else if(show_mode == DFS && structure == MATRIX && G->g_type == UNDIGRAPH)
    {
	i = v_begin;
	while(i < G->v_num)
	{
	    if(VISITED_FLAGS[i] != true){ Undigraph_Matrix_DFS(G,i,V_Handle1); }
	    ++i;
	}
	i = 0;
	while(i < v_begin)
	{
	    if(VISITED_FLAGS[i] != true){ Undigraph_Matrix_DFS(G,i,V_Handle1); }
	    ++i;
	}
    }
    else if(show_mode == BFS && structure == MATRIX && G->g_type == UNDIGRAPH)
    {
	i = v_begin;
	while(i < G->v_num)
	{
	    if(VISITED_FLAGS[i] != true){ Undigraph_Matrix_BFS(G,i,V_Handle1); }
	    ++i;
	}
	i = 0;
	while(i < v_begin)
	{
	    if(VISITED_FLAGS[i] != true){ Undigraph_Matrix_BFS(G,i,V_Handle1); }
	    ++i;
	}
    }
    else
    { 
	LINE_DEBUG("Unknown Show Mode"); 
    }
}

/* 释放图
 * 要注意释放干净，所有图中手工分配的内存都要从小到大释放掉
 * 具体如何释放，还是跟存储结构关系紧密，过程大致相同，在细微
 * 的迭代条件上有差异。
 */
/*多重表释放*/
/* 注意多重表边的释放要先筛选出所有的出边，然后再释放，否则可能出现
 * 释放了A的出边Arc，但是Arc作为B的一条入边，在之后的遍历B的所有边条
 * 件迭代时会访问这个已经释放的边指针，产生段错误。
 */
void MultilistFree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    int i = 0; int j = 0;
    P_ArcNode arc = NULL;
    P_ArcNode arcs[G->arc_num];
    while(i < G->v_num)
    {
	//释放顶点i的数据
	SAFE_FREE(G->v_list[i]->data);
	//记录所有以顶点i为尾的边(或者只释放所有以顶点i为头的边也可以)
	arc = G->v_list[i]->arc_first_in;
	while(arc)
	{
	    if(i == arc->v_tail){ arcs[j] = arc; ++j; }
	    arc = (i == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	}
	//释放顶点i自身
	SAFE_FREE(G->v_list[i]);
	++i;
    }
    //释放边
    for(i = 0; i < G->arc_num; ++i){ SAFE_FREE(arcs[i]); }
    arc = NULL; temp_arc = NULL;
    //释放图
    SAFE_FREE(G);
}

//十字链表释放
void OrthogonalListFree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    int i = 0;
    P_ArcNode arc = NULL;
    P_ArcNode temp_arc = NULL;
    while(i < G->v_num)
    {
	SAFE_FREE(G->v_list[i]->data);
	//释放顶点i的所有出边
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    temp_arc = arc;
	    arc = arc->arc_tail;
	    SAFE_FREE(temp_arc);
	}
	SAFE_FREE(G->v_list[i]);
	++i;
    }
    arc = NULL; temp_arc = NULL;
    SAFE_FREE(G);
}

//邻接表释放
void AdjacencyListFree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    int i = 0;
    P_ArcNode arc = NULL;
    P_ArcNode temp_arc = NULL;
    while(i < G->v_num)
    {
	SAFE_FREE(G->v_list[i]->data);
	//释放顶点i的所有边
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    temp_arc = arc;
	    arc = arc->arc_head;
	    SAFE_FREE(temp_arc);
	}
	SAFE_FREE(G->v_list[i]);
	++i;
    }
    arc = NULL; temp_arc = NULL;
    SAFE_FREE(G);
}

//邻接矩阵释放
void MatrixFree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    int i = 0;
    int j;
    while(i < G->v_num)
    {
	SAFE_FREE(G->v_list[i]->data);
	j = 0;
	//释放所有的边
	while(j < G->v_num)
	{
	    if(G->arc_matrix[i][j] != NULL)
	    {
		SAFE_FREE(G->arc_matrix[i][j]);
		/* 把j顶点在i位置所记录的同一条边的地方置空，防止访问到
		 * j顶点的i位置时重复释放
		 */
		G->arc_matrix[j][i] = NULL;
	    }
	    ++j;
	}
	SAFE_FREE(G->v_list[i]);
	++i;
    }
    SAFE_FREE(G);
}

void GraphicsFree(P_Graphics G,STRUCTURE structure)
{
    if(G == NULL){ LINE_DEBUG("GraphicsFree G is NULL"); return; }
    switch(structure)
    {
	case MULTILIST:
	    MultilistFree(G);      break;
	case ORTHOGONALLSIT:
	    OrthogonalListFree(G); break;
	case ADJACENCYLIST:
	    AdjacencyListFree(G);  break;
	case MATRIX:
	    MatrixFree(G);         break;
	default:
	    printf("GraphicsFree Unknown structure\n"); break;
    }
}


int main()
{
    //图的遍历显示，可选定开始节点和DFS or BFS
    printf("---------------------邻接多重表-----------------------\n");
    P_Graphics Multilist_Undigraph = CreateOneMultilistUndigraph();
    if(Multilist_Undigraph == NULL){ LINE_DEBUG("Multilist_Undigraph Create failed"); return -1; }
    Graphics_Show(Multilist_Undigraph,0,DFS,MULTILIST);
    printf("---------------------十字链表-----------------------\n");
    P_Graphics OrthogonalList_Digraph = CreateOneOrthogonalListDigraph();
    if(OrthogonalList_Digraph == NULL){ LINE_DEBUG("OrthogonalList_Digraph Create failed"); return -1; }
    Graphics_Show(OrthogonalList_Digraph,0,DFS,ORTHOGONALLSIT);
    printf("--------------------邻接表无向图-----------------------\n");
    P_Graphics AdjacencyList_Undigraph = CreateOneAdjacencyListUndigraph();
    if(AdjacencyList_Undigraph == NULL){ LINE_DEBUG("AdjacencyList_Undigraph Create failed"); return -1; }
    Graphics_Show(AdjacencyList_Undigraph,0,BFS,ADJACENCYLIST);
    printf("--------------------邻接矩阵表无向图-----------------------\n");
    P_Graphics Matrix_Undigraph = CreateOneMatrixUndigraph();
    if(Matrix_Undigraph == NULL){ LINE_DEBUG("Matrix_Undigraph Create failed"); return -1; }
    Graphics_Show(Matrix_Undigraph,0,BFS,MATRIX);
    
    //清理工作
    GraphicsFree(Multilist_Undigraph,MULTILIST);
    GraphicsFree(OrthogonalList_Digraph,ORTHOGONALLSIT);
    GraphicsFree(AdjacencyList_Undigraph,ADJACENCYLIST);
    GraphicsFree(Matrix_Undigraph,MATRIX);

    return 0;
}
