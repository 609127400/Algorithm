/*
 *                                最大流问题
 * 1.流网络，适用于连通有向图中。将边看作输送的通道，每条边有一定的容量，
 *   允许多少个元素通过。流网络中不存在反向边，即若有1->2边，则不允许存
 *   在2->1的边。流量的发出点为源点，流量的汇入点为汇点。流网络允许有多
 *   个源点和汇点，在这种情况下一般都添加一个超级源点和超级汇点，用超级
 *   源点发送相应流量到各个源点，用超级汇点汇集各个汇点的流量，以此来转
 *   化为单源点和单汇点的情况进行处理。如果图中存在反向平行边，则需要通
 *   过增加一个新的顶点转化掉这条平行边。如1->2，同时存在2->1，则加入一
 *   个3顶点使得2->3，3->1来替代2->1。
 * 2.流网络的性质：容量限制和流量守恒。即边上的流量不能超过边容量的限制，
 *   且一个顶点处流入的流量与流出的流量在数量上，速率上必须一相等。
 * 3.最大流问题，就是求解出在满足流网络性质的前提下，源点最大能发送出多
 *   少数量的元素到汇点。有Ford-Fulkerson方法来求解。注意是方法而不是算
 *   法，因具体在部分代码的实现方法不同而有不同的算法。
 * 4.Ford-Fulkerson方法
 *   基本思想是利用流网络生成残存网络，不断在残存网络中寻找增广路径(增加
 *   流量的路径)，获取增广路径所有边中的最小容量值，通过对增广路径逐步增
 *   加这个最小容量值的流量，对这条增广路径的所有边的容/流量进行更新，进
 *   而更新残存网络。直到残存网络中再也寻找不到增广路径，此时从源点或汇点
 *   的流量和可计算出最大流值。
 *   残存网络：
 *   残存网络基于流网络，既包含流网络中的边，也包含流网络不存在的边，且在
 *   算法中是动态变化的。残存的意思就是对应流网络中的边在现有流量下还残余
 *   (剩)多少空间的容量可供额外的流通过，这部分是对应流网络的边，如流网络
 *   中有边1->2，流量为15，容量为20，则残存网络对应有边1->2，这条边的流量
 *   为0，容量为20-15=5。当流网络边1->2有流量为15时，残存网络就产生了流网
 *   络不存在的反向平行边2->1，该边的流量为0，容量为15。当流网络边1->2流量
 *   达到满负荷即20时，残存网络的1->2边变为20-20=0，也代表这条边在残存网络
 *   不再有运载能力，这条边不再存在，同时2->1这条反向平行边的容量变为20。
 *   残存网络在这里用一个顶点矩阵进行表示。
 *   增广路径：
 *   在残存网络中从源点连通到汇点的一条路径。
 *   FordFulkerson的执行时间随取决于寻找最短路径的算法时间。Edmonds-Karp算
 *   法将残存网络中的边视为单位等长，借助辅助数组，用搜寻从源点到汇点的最
 *   短路径的方法寻找增广路径，并将这条最短路径作为要处理的增广路径。
 * 5.Push-Relabel方法
 *   ① 推送-重贴标签方法，推送指推送流量，重贴标签指的是重新调整一个顶点
 *   的高度标签。真个算法围绕Push和Relabel这两个操作进行。较FordFulkerson
 *   更高效。方法引进了预流（就当作流量看待即可），超额流excess（蓄水池），
 *   推送（Push），高度标签（H）的概念。无论Push还是Relabel操作，依然是在
 *   残存网络上进行操作(即可以对反平行边进行操作)。
 *   ②基本思想：初始从源点S送出最大的流量，即将S的每条出边都送满，作为预
 *   流。每个顶点将接收到的预流存储在超额流字段（excess），就相当于一个蓄
 *   水池。当u的蓄水池中有水时(excess>0)，可从蓄水池中取水尝试推送，u只向
 *   其所有邻接头顶点高度最低的顶点min_v（可能有多个）推送流量，且u的高度
 *   必须比min_v高1（即水往低处流），同时要保证u->min_v存有残余流量，推送
 *   流量的大小由u->min_v的残余流量与u的蓄水池存水量excess两者中较小的一个
 *   决定。若推送时H(u)<=H(min_v)，则需要对u的高度重新调整，调整为H(min_v)+1，
 *   供以后再次遍历到u顶点时以便推送（也可当即回滚循环进行推送）。因此，在
 *   u蓄水池有水的大前提下(excess>0)，是进行推送操作还是重贴标签操作，取
 *   决于H(u)是否==H(min_v)+1。如1的excess=10，1->2 1->3 1->4，H(1)=1 H(2)
 *   =2 H(3)=2 H(4)=4，则顶点1所有邻接头顶点中高度最低的为2和3，则先将1高
 *   度调整为2+1，等再次遍历到1时就可以将1中的流量推送给2和3了。如此不断重
 *   复（任意次序的）遍历所有中间顶点，直到所有中间顶点的excess都为0后(这
 *   里可能包含了将多余的流量推送回源点)，算法终止。
 *   综上总结：
 *   根据重贴标签的操作，可以推导出在遍历过程中，u的高度始终<=H(min_v)+1，
 *   因而在每次遍历一个顶点时，要么执行Push，要么执行Relabel。
 *   u顶点推送的条件：u的蓄水池excess中有水，u的高度==H(min_v)+1，u->min_v
 *   这条边有残余流量(空间)可供推送。即有东西可送，高度够，有空间可供推送。
 *   u顶点重贴标签的条件：u的蓄水池excess中有水，u的高度<=H(min_v)。重贴标
 *   签操作不需要考虑u的出边是否有残余流量，而是做好自己的事情，让u的标签
 *   符合要求即可，至于有没有空间去推送，那是推送需要判断的事情。
 *   注：对于u的推送条件中，高度条件可放宽至只要u比v高即可，相应的无论是否
 *   执行推送，每次遍历u，只管重贴标签(高度+1)即可。这样可以节省掉计算最低
 *   高度的时间，但是由于高度每次最多只能增加1，因此遍历的次数也会增加。
 * 6.前置重贴标签算法
 *   初始化条件与推送-重贴标签方法一样。不同的是，重贴标签方法是一趟趟遍历
 *   所有中间顶点，每次可能将u中存储的流量全部推送，也可能只推送一部分。而
 *   前置重贴标签算法是每次遍历到一个中间顶点u，就会将其存储的流量完全推送
 *   完毕，也即释放掉其excess。算法维护了两条链表L和N：L存储所有中间顶点以
 *   供释放，N存储了所释放的顶点的所有邻接顶点，即u所有出边的头顶点和所有入
 *   边的尾顶点的集合。遍历扫描L，每次处理一个顶点u，则扫描u的所有N中的元素
 *   v，若uv在残存网络中符合推送的条件，则推送，若扫描完所有v点后u仍未释放
 *   完毕，则对u重贴标签后继续重新扫描u的所有v，直到u释放完毕（excess=0）。
 *   然后对u在释放过程中是否进行过重贴标签操作判断，若进行过，则需将u在L中
 *   进行前置（挪到L的开头）。u至此处理完毕，在L中向u的下一个中间顶点u'推进，
 *   继续处理u'。如此循环，直到处理掉L中所有的元素，算法结束。
 *
 *						           2017年1月9日
 */
//#define _DEBUG_CLOSE_
#include "../PublicForAlgorithms.h"

#define MAX_VERTEX_NUM 20
#define MAX_VERTEX_NAME_LEN 30
#define MAX_INFINITY 99999999
/*用于推送-重贴标签方法中求尾顶点邻接的头顶点中高度最低的顶点的高度*/
#define MAX_MORE_HEIGHT 100 

#define S_P 0 /*流网络中源点在图中的位置，放在v_list第一个，注意随着图的变化而更新*/
#define T_P 5 /*流网络中汇点在图中的位置，放在v_list最后一个，注意随着图的变化而更新*/

typedef int V_Position;
typedef int Power,Capacity,Flow,Height,Excess;
typedef int G_Type;

typedef struct
{
    Power power;      /*边权值*/
    Capacity capacity;/*边容量*/
    Flow flow;        /*边流量*/
}ArcInfo,*P_ArcInfo;

P_ArcInfo CreateOneArcInfo(Power p,Capacity c,Flow f)
{
    P_ArcInfo new_info = (P_ArcInfo)malloc(sizeof(ArcInfo));
    if(new_info == NULL){ LINE_DEBUG("ArcInfo malloc failed"); return NULL; }
    new_info->power = p;
    new_info->capacity = c;
    new_info->flow = f;
    return new_info;
}

typedef struct Edge
{
    Status mark;
    V_Position v_tail,v_head;
    struct Edge *arc_tail,*arc_head;
    P_ArcInfo info;
}ArcNode,*P_ArcNode;

P_ArcNode CreateOneArcNode(V_Position vt,V_Position vh,P_ArcInfo info)
{
    P_ArcNode new_arc = (P_ArcNode)malloc(sizeof(ArcNode));
    if(new_arc == NULL){ LINE_DEBUG("ArcNode malloc failed"); return NULL; }
    new_arc->mark = 0;
    new_arc->v_tail = vt; new_arc->v_head = vh;
    new_arc->info = info;
    return new_arc;
}

typedef struct
{
    char name[MAX_VERTEX_NAME_LEN];
    Height height;/*顶点的高度（标签）*/
    Excess excess;/*顶点的容纳的超额流量（蓄水池所容纳的预流）*/
}VertexData,*P_VertexData;

P_VertexData CreateOneVertexData(char* n)
{
    P_VertexData new_vd = (P_VertexData)malloc(sizeof(VertexData));
    if(new_vd == NULL){ LINE_DEBUG("VertexData malloc failed"); return NULL; }
    strncpy(new_vd->name,n,MAX_VERTEX_NAME_LEN);
    new_vd->height = 0;/*做了push-relabel的一部分初始化工作*/
    new_vd->excess = 0;/*做了push-relabel的一部分初始化工作*/
    return new_vd;
}

typedef struct
{
    Status mark;
    P_ArcNode arc_first_out,arc_first_in;
    P_VertexData data;
}VertexNode,*P_VertexNode;

P_VertexNode CreateOneVertexNode(P_ArcNode fo,P_ArcNode fi,P_VertexData data)
{
    P_VertexNode new_v = (P_VertexNode)malloc(sizeof(VertexNode));
    if(new_v == NULL){ LINE_DEBUG("VertexNode malloc failed"); return NULL; }
    new_v->mark = 0;
    new_v->arc_first_out = fo; new_v->arc_first_in = fi;
    new_v->data = data;
    return new_v;
}

typedef struct
{
    G_Type g_type;
    P_VertexNode v_list[MAX_VERTEX_NUM];
    int v_num,arc_num;
}Graphics,*P_Graphics;

/*     1---3
 *    /|  /|\          Capcity:
 *   S | / | T         S->1 16  S->2 13  2->1 4   1->3 12  3->2 9
 *    \|/  |/          2->4 14  4->3 7   3->T 20  4->T 4
 *     2---4
 */
P_Graphics CreateOneDigraph()
{
    //声明
    P_VertexData dataS = NULL;P_VertexData data1 = NULL;P_VertexData data2 = NULL;
    P_VertexData data3 = NULL;P_VertexData data4 = NULL;P_VertexData dataT = NULL;
    P_VertexNode VS = NULL;P_VertexNode V1 = NULL;P_VertexNode V2 = NULL;
    P_VertexNode V3 = NULL;P_VertexNode V4 = NULL;P_VertexNode VT = NULL;
    P_ArcInfo infos_1 = NULL;P_ArcInfo infos_2 = NULL;P_ArcInfo info2_1 = NULL;
    P_ArcInfo info1_3 = NULL;P_ArcInfo info3_2 = NULL;P_ArcInfo info2_4 = NULL;
    P_ArcInfo info4_3 = NULL;P_ArcInfo info3_t = NULL;P_ArcInfo info4_t = NULL;
    P_ArcNode Arcs_1 = NULL;P_ArcNode Arcs_2 = NULL;P_ArcNode Arc2_1 = NULL;
    P_ArcNode Arc1_3 = NULL;P_ArcNode Arc3_2 = NULL;P_ArcNode Arc2_4 = NULL;
    P_ArcNode Arc4_3 = NULL;P_ArcNode Arc3_t = NULL;P_ArcNode Arc4_t = NULL;
    P_Graphics digraph = NULL;
    //创建
    infos_1 = CreateOneArcInfo(1,16,0);infos_2 = CreateOneArcInfo(1,13,0);info2_1 = CreateOneArcInfo(1,4,0);
    info1_3 = CreateOneArcInfo(1,12,0);info3_2 = CreateOneArcInfo(1,9,0); info2_4 = CreateOneArcInfo(1,14,0);
    info4_3 = CreateOneArcInfo(1,7,0); info3_t = CreateOneArcInfo(1,20,0);info4_t = CreateOneArcInfo(1,4,0);
    if(infos_1 == NULL || infos_2 == NULL || info2_1 == NULL || info1_3 == NULL|| info3_2 == NULL
    || info2_4 == NULL || info4_3 == NULL || info3_t == NULL || info4_t == NULL)
    { LINE_DEBUG("ArcInfo create failed"); goto Label_CreateOneDigraph_Clean; }
    
    Arcs_1 = CreateOneArcNode(0,1,infos_1);Arcs_2 = CreateOneArcNode(0,2,infos_2);
    Arc2_1 = CreateOneArcNode(2,1,info2_1);Arc1_3 = CreateOneArcNode(1,3,info1_3);
    Arc3_2 = CreateOneArcNode(3,2,info3_2);Arc2_4 = CreateOneArcNode(2,4,info2_4);
    Arc4_3 = CreateOneArcNode(4,3,info4_3);Arc3_t = CreateOneArcNode(3,5,info3_t);
    Arc4_t = CreateOneArcNode(4,5,info4_t);
    if(Arcs_1 == NULL || Arcs_2 == NULL || Arc2_1 == NULL || Arc1_3 == NULL || Arc3_2 == NULL
    || Arc2_4 == NULL || Arc4_3 == NULL || Arc3_t == NULL || Arc4_t == NULL)
    { LINE_DEBUG("ArcNode create failed"); goto Label_CreateOneDigraph_Clean; }

    dataS = CreateOneVertexData("VS");data1 = CreateOneVertexData("V1");data2 = CreateOneVertexData("V2");
    data3 = CreateOneVertexData("V3");data4 = CreateOneVertexData("V4");dataT = CreateOneVertexData("VT");
    if(dataS == NULL || data1 == NULL || data2 == NULL
    || data3 == NULL || data4 == NULL || dataT == NULL)
    { LINE_DEBUG("VertexData create failed"); goto Label_CreateOneDigraph_Clean; }

    VS = CreateOneVertexNode(Arcs_1,NULL,  dataS);V1 = CreateOneVertexNode(Arc1_3,Arcs_1,data1);
    V2 = CreateOneVertexNode(Arc2_1,Arcs_2,data2);V3 = CreateOneVertexNode(Arc3_2,Arc1_3,data3);
    V4 = CreateOneVertexNode(Arc4_3,Arc2_4,data4);VT = CreateOneVertexNode(NULL,  Arc3_t,dataT);
    if(VS == NULL || V1 == NULL || V2 == NULL
    || V3 == NULL || V4 == NULL || VT == NULL)
    { LINE_DEBUG("Vertex create failed"); goto Label_CreateOneDigraph_Clean; }
    
    //关系组织
    Arcs_1->arc_tail = Arcs_2;Arcs_1->arc_head = Arc2_1;Arcs_2->arc_tail = NULL;Arcs_2->arc_head = Arc3_2;
    Arc2_1->arc_tail = Arc2_4;Arc2_1->arc_head = NULL;  Arc1_3->arc_tail = NULL;Arc1_3->arc_head = Arc4_3;
    Arc3_2->arc_tail = Arc3_t;Arc3_2->arc_head = NULL;  Arc2_4->arc_tail = NULL;Arc2_4->arc_head = NULL;
    Arc4_3->arc_tail = Arc4_t;Arc4_3->arc_head = NULL;  Arc3_t->arc_tail = NULL;Arc3_t->arc_head = Arc4_t;
    Arc4_t->arc_tail = NULL;  Arc4_t->arc_head = NULL;
    
    digraph = (P_Graphics)malloc(sizeof(Graphics));
    if(digraph == NULL){ LINE_DEBUG("Graphics create failed"); goto Label_CreateOneDigraph_Clean; }
    digraph->g_type = (DIGRAPH | CYCLIC | WEIGHTYES | CONNECTED);
    digraph->v_num = 6;digraph->arc_num = 9;
    digraph->v_list[0] = VS;digraph->v_list[1] = V1;digraph->v_list[2] = V2;
    digraph->v_list[3] = V3;digraph->v_list[4] = V4;digraph->v_list[5] = VT;

    return digraph;

Label_CreateOneDigraph_Clean:
    SAFE_FREE(dataS);SAFE_FREE(data1);SAFE_FREE(data2);SAFE_FREE(data3);SAFE_FREE(data4);SAFE_FREE(dataT);
    SAFE_FREE(VS);SAFE_FREE(V1);SAFE_FREE(V2);SAFE_FREE(V3);SAFE_FREE(V4);SAFE_FREE(VT);
    SAFE_FREE(infos_1);SAFE_FREE(infos_2);SAFE_FREE(info2_1);SAFE_FREE(info1_3);
    SAFE_FREE(info3_2);SAFE_FREE(info2_4);SAFE_FREE(info4_3);SAFE_FREE(info3_t);SAFE_FREE(info4_t);
    SAFE_FREE(Arcs_1);SAFE_FREE(Arcs_2);SAFE_FREE(Arc2_1);SAFE_FREE(Arc1_3);
    SAFE_FREE(Arc3_2);SAFE_FREE(Arc2_4);SAFE_FREE(Arc4_3);SAFE_FREE(Arc3_t);SAFE_FREE(Arc4_t);
    SAFE_FREE(digraph);
    return NULL;
}

/*有向图释放*/
void Digraph_Free(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Digraph_Free G is NULL"); return; }
    int i; P_ArcNode arc,temp_arc;
    for(i = 0; i < G->v_num; ++i)
    {
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    temp_arc = arc;
	    arc = arc->arc_tail;
	    SAFE_FREE(temp_arc->info);
	    SAFE_FREE(temp_arc);
	}
	SAFE_FREE(G->v_list[i]->data);
	SAFE_FREE(G->v_list[i]);
    }
    SAFE_FREE(G);
}

/*FordFulkerson方法中的Edmonds-Karp算法
 * 返回最大流的值*/
int MF_FordFulkerson(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("FordFulkerson G is NULL"); return -1; }
    int P[G->v_num]; /*对应顶点最短路径值*/
    V_Position F[G->v_num]; /*对应顶点最短路径前驱顶点*/
    int i,j,cur_dist;
    int min_capacity;
    /*供计算最大流使用的残存网络,R_NET[0][2]即代表0->2的剩余可通行流量，
     *==0代表这条边达到了满负荷flow==capacity，或者不存在这条边*/
    Flow R_NET[G->v_num][G->v_num]; memset(R_NET,0,G->v_num * G->v_num * sizeof(int));
    P_ArcNode arc;
    /*初始化残存网络*/
    for(i = 0; i < G->v_num; ++i)
    {
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    R_NET[i][arc->v_head] = arc->info->capacity;
	    arc = arc->arc_tail;
	}
    }
    /*开始循环搜索增广路径并增加边的流量，更新残存网络*/
    while(1)
    {
	//初始化辅助数组和源点
	for(i = 0; i < G->v_num; ++i){ P[i] = MAX_INFINITY; F[i] = -1; }
	P[S_P] = 0;
	//计算最短路径(也是增广路径)
	for(cur_dist = 0;cur_dist < G->v_num; ++cur_dist)
	{
	    for(i = 0; i < G->v_num; ++i)
	    {
		//如果顶点的距离等于当前要处理的距离
		if(P[i] == cur_dist)
		{
		    /*则遍历其所有出边，若头顶的未访问过，则在辅助数组中更新
		     *该头顶点的最短路径值(供下一轮使用)和前驱顶点*/
		    arc = G->v_list[i]->arc_first_out;
		    while(arc)
		    {
			if(R_NET[i][arc->v_head] && P[arc->v_head] == MAX_INFINITY)
			{
			    P[arc->v_head] = cur_dist + 1;
			    F[arc->v_head] = i;
			}
			arc = arc->arc_tail;
		    }
		}/*if end*/
	    }/*for end*/
	}/*for end*/

	/*若汇点没有前驱顶点，则说明不存在增广路径，返回最大流*/
	if(F[T_P] == -1)
	{
	    for(i = 0; i < G->v_num; ++i)
	    {
		for(j = 0; j < G->v_num; ++j)
		{
		    printf("%-3d ",R_NET[i][j]);
		}
		printf("\n");
	    }
	    /*根据源点出边残存流量计算最大流量，用变量i存储*/
	    /*也可根据汇点入边流量最大流量：i += R_NET[G->v_num-1][arc->v_tail]*/
	    i = 0;
	    arc = G->v_list[S_P]->arc_first_out;
	    while(arc)
	    {

		i += (arc->info->capacity - R_NET[S_P][arc->v_head]);
		arc = arc->arc_tail;
	    }
	    return i;
	}

	//找出计算出的增广路径中的最小容量
	min_capacity = MAX_INFINITY;
	for(i = G->v_num - 1; i > 0; i = F[i])
	{
	    if(R_NET[F[i]][i] < min_capacity)
	    { min_capacity = R_NET[F[i]][i]; }
	}
	//增加流量
	for(i = G->v_num - 1; i > 0; i = F[i])
	{
	    //削减增广路径边的残存流量
	    R_NET[F[i]][i] -= min_capacity;
	    //增加抵消流量的反平行边
	    R_NET[i][F[i]] += min_capacity;
	}
    }
}

int MF_Push_Relabel(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("P_R G is NULL"); return -1; }
    int i,j,m;
    P_ArcNode arc = NULL;
    /*residual net*/;
    Flow R_NET[G->v_num][G->v_num];
    for(i = 0; i < G->v_num; ++i){ for(j = 0; j < G->v_num; ++j){ R_NET[i][j] = 0; } }
    /*初始化残存网络*/
    for(i = 0; i < G->v_num; ++i)
    {
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    R_NET[i][arc->v_head] = arc->info->capacity;
	    arc = arc->arc_tail;
	}
    }
    /*初始化预流/标签（高度），部分工作在建图时已完成*/
    /*flag用相应位置1进行标识对应顶点的excess是否为0，若所有顶点的excess都为0，
     *则表明所有可推送的工作都已经完成，算法终止*/
    int flag = 0;
    G->v_list[S_P]->data->height = 6;
    arc = G->v_list[S_P]->arc_first_out;
    while(arc)
    {
	R_NET[S_P][arc->v_head] -= arc->info->capacity;
	R_NET[arc->v_head][S_P] += arc->info->capacity;
	G->v_list[arc->v_head]->data->excess += arc->info->capacity;
	flag |= (1 << arc->v_head);//设置顶点excess不为0的相应位为1
	arc = arc->arc_tail;
    }
    //推送的最小流，尾顶点存储的流量，所有邻接头顶点的最小高度
    Flow min_flow,excess_flow; Height min_height;
    /*计算最大流*/
    while(flag)
    {
	/*遍历所有除源点和汇点之外的顶点(将i作为尾顶点)*/
	for(i = 1; i < T_P; ++i)
	{
	    //保证excess中有水
	    if(G->v_list[i]->data->excess == 0){ continue; }
	    //计算尾顶点i所有头顶的的最低高度
	    min_height = MAX_MORE_HEIGHT;
	    for(m = 0; m < G->v_num; ++m)
	    {
		if(R_NET[i][m] > 0 && G->v_list[m]->data->height < min_height)
		{ min_height = G->v_list[m]->data->height; }
	    }
	    //如果顶点i在高度上符合推送的条件，则尝试向头顶点j推送
	    if(G->v_list[i]->data->height == min_height + 1)
	    {
		for(j = 0; j < G->v_num; ++j)
		{
		    //确保i->j有残余流量
		    if(R_NET[i][j] == 0){ continue; }
		    //只对高度最低的邻接头顶点进行推送
		    if(G->v_list[j]->data->height == min_height)
		    {
			/*在循环中可能存在向多个顶点可推送流量，所有要及时判断i的excess*/
			excess_flow = G->v_list[i]->data->excess;
			if(excess_flow > 0)
			{
			    //推送操作
			    min_flow = excess_flow > R_NET[i][j] ? R_NET[i][j] : excess_flow;
			    R_NET[i][j] -= min_flow;
			    R_NET[j][i] += min_flow;
			    G->v_list[i]->data->excess -= min_flow;
			    G->v_list[j]->data->excess += min_flow;
			    //若尾顶点推送流量后excess==0，则从标识中删除
			    if(G->v_list[i]->data->excess == 0){ flag &= (~(1 << i)); }
			    //把头顶节点加入标识(头顶点excess经过+min_flow，一定>0)
			    if(j != S_P && j != T_P){ flag |= (1 << j); }
			}
		    }
		}
	    }
	    //否则，则重贴标签，让i顶点比其最低高度的邻接头顶点的高度大1
	    else
	    {
		G->v_list[i]->data->height = min_height + 1;
		/*当重贴标签后当即回滚循环后进行推送操作，在效率上没什么提高
		 *，但是更好理解一点。如果不立即回滚，只是将推送延后到之后的
		 *遍历中操作而已*/
		//--i;
	    }
	}
    }
    //显示残存网络
    for(i = 0; i < G->v_num; ++i)
    {
	for(j = 0; j < G->v_num; ++j)
	{ printf("%-3d ",R_NET[i][j]); }
	printf("\n");
    }
    //printf("T->excess = %d\n",G->v_list[T_P]->data->excess);
    //printf("S->excess = %d\n",G->v_list[S_P]->data->excess);
    return G->v_list[T_P]->data->excess;
}

int MF_Font_Relabel(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("F_R G is NULL"); return -1; }
    int i,j;
    V_Position u,v;
    P_ArcNode arc = NULL;
    /*创建L链表，存储所有可能溢出的顶点，0处放置正在处理的顶点位置*/
    V_Position L[G->v_num];
    /*创建邻接顶点链表，存储处理溢出顶点的所有直接相连的顶点，0位置放元素个数*/
    V_Position N[G->v_num];
    /*residual net*/;
    Flow R_NET[G->v_num][G->v_num];
    for(i = 0; i < G->v_num; ++i){ for(j = 0; j < G->v_num; ++j){ R_NET[i][j] = 0; } }
    /*初始化残存网络*/
    for(i = 0; i < G->v_num; ++i)
    {
	L[i] = i;
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    R_NET[i][arc->v_head] = arc->info->capacity;
	    arc = arc->arc_tail;
	}
    }
    //初始化预流
    G->v_list[S_P]->data->height = 6;
    arc = G->v_list[S_P]->arc_first_out;
    while(arc)
    {
	R_NET[S_P][arc->v_head] -= arc->info->capacity;
	R_NET[arc->v_head][S_P] += arc->info->capacity;
	G->v_list[arc->v_head]->data->excess += arc->info->capacity;
	arc = arc->arc_tail;
    }
    
    Flow min_flow; Height old_height;
    /*计算最大流*/
    for(i = 1; i < T_P; ++i)
    {
	//当前处理的顶点u
	u = L[i];
	old_height = G->v_list[u]->data->height;
	//初始化N，即u的所有邻接顶点
	j = 1;
	arc = G->v_list[u]->arc_first_out;
	while(arc)
	{
	    N[j] = arc->v_head;
	    ++j;
	    arc = arc->arc_tail;
	}
	arc = G->v_list[u]->arc_first_in;
	while(arc)
	{
	    N[j] = arc->v_tail;
	    ++j;
	    arc = arc->arc_head;
	}
	N[0] = j;/*N[0]为比N中元素个数大1的数，即相当于标识着N遍历完毕时的下标*/
	//释放u顶点
	j = 1;
	while(G->v_list[u]->data->excess > 0)
	{
	    v = N[j];
	    //如果遍历完所有邻接顶点后u仍未释放干净
	    if(j == N[0])
	    {
		//则重贴标签，每次升高1，并重新遍历u所有的邻接顶点
		G->v_list[u]->data->height += 1;
		j = 1;
	    }
	    //如果符合推送条件，则推送流量进行释放u的excess
	    else if((R_NET[u][v] > 0) && (G->v_list[u]->data->height == (G->v_list[v]->data->height + 1)))
	    {
		//推送
		min_flow = G->v_list[u]->data->excess;
		min_flow = min_flow > R_NET[u][v] ? R_NET[u][v] : min_flow;
		R_NET[u][v] -= min_flow;
		R_NET[v][u] += min_flow;
		G->v_list[u]->data->excess -= min_flow;
		G->v_list[v]->data->excess += min_flow;
	    }
	    else
	    {
		++j;
	    }
	}
	//若u点进行了重贴标签操作，则将u在L中前置
	if(G->v_list[u]->data->height > old_height)
	{
	    L[0] = L[i];
	    while(i > 1)
	    {
		L[i] = L[i - 1];
		--i;
	    }
	    L[1] = L[0];
	}
    }

    //显示残存网络
    for(i = 0; i < G->v_num; ++i)
    {
	for(j = 0; j < G->v_num; ++j)
	{ printf("%-3d ",R_NET[i][j]); }
	printf("\n");
    }
    return G->v_list[T_P]->data->excess;
}













int main()
{
    P_Graphics digraph_one = CreateOneDigraph();
    if(digraph_one == NULL){ printf("digraph_one create failed\n"); return -1; }
    P_Graphics digraph_two = CreateOneDigraph();
    if(digraph_two == NULL){ printf("digraph_two create failed\n"); return -1; }
    P_Graphics digraph_three = CreateOneDigraph();
    if(digraph_three == NULL){ printf("digraph_three create failed\n"); return -1; }

    printf("FordFulkerson 方法计算最大流结果：\n");
    int max_flow = MF_FordFulkerson(digraph_one);
    printf("MAXFLOW = %d\n",max_flow);
    printf("---------------------------------------\n");

    printf("推送-重贴标签 方法计算最大流结果：\n");
    max_flow = MF_Push_Relabel(digraph_two);
    printf("MAXFLOW = %d\n",max_flow);
    printf("---------------------------------------\n");
    
    printf("前置重贴标签 方法计算最大流结果：\n");
    max_flow = MF_Font_Relabel(digraph_three);
    printf("MAXFLOW = %d\n",max_flow);
    printf("---------------------------------------\n");
    
    Digraph_Free(digraph_one);
    Digraph_Free(digraph_two);
    Digraph_Free(digraph_three);

    return 0;
}
