/*
 *                                ���������
 * 1.�����磬��������ͨ����ͼ�С����߿������͵�ͨ����ÿ������һ����������
 *   ������ٸ�Ԫ��ͨ�����������в����ڷ���ߣ�������1->2�ߣ��������
 *   ��2->1�ıߡ������ķ�����ΪԴ�㣬�����Ļ����Ϊ��㡣�����������ж�
 *   ��Դ��ͻ�㣬�����������һ�㶼���һ������Դ��ͳ�����㣬�ó���
 *   Դ�㷢����Ӧ����������Դ�㣬�ó������㼯���������������Դ���ת
 *   ��Ϊ��Դ��͵�����������д������ͼ�д��ڷ���ƽ�бߣ�����Ҫͨ
 *   ������һ���µĶ���ת��������ƽ�бߡ���1->2��ͬʱ����2->1�������һ
 *   ��3����ʹ��2->3��3->1�����2->1��
 * 2.����������ʣ��������ƺ������غ㡣�����ϵ��������ܳ��������������ƣ�
 *   ��һ�����㴦����������������������������ϣ������ϱ���һ��ȡ�
 * 3.��������⣬�����������������������ʵ�ǰ���£�Դ������ܷ��ͳ���
 *   ��������Ԫ�ص���㡣��Ford-Fulkerson��������⡣ע���Ƿ�����������
 *   ����������ڲ��ִ����ʵ�ַ�����ͬ���в�ͬ���㷨��
 * 4.Ford-Fulkerson����
 *   ����˼�����������������ɲд����磬�����ڲд�������Ѱ������·��(����
 *   ������·��)����ȡ����·�����б��е���С����ֵ��ͨ��������·������
 *   �������С����ֵ������������������·�������бߵ���/�������и��£���
 *   �����²д����硣ֱ���д���������ҲѰ�Ҳ�������·������ʱ��Դ�����
 *   �������Ϳɼ���������ֵ��
 *   �д����磺
 *   �д�������������磬�Ȱ����������еıߣ�Ҳ���������粻���ڵıߣ�����
 *   �㷨���Ƕ�̬�仯�ġ��д����˼���Ƕ�Ӧ�������еı������������»�����
 *   (ʣ)���ٿռ�������ɹ��������ͨ�����ⲿ���Ƕ�Ӧ������ıߣ���������
 *   ���б�1->2������Ϊ15������Ϊ20����д������Ӧ�б�1->2�������ߵ�����
 *   Ϊ0������Ϊ20-15=5�����������1->2������Ϊ15ʱ���д�����Ͳ���������
 *   �粻���ڵķ���ƽ�б�2->1���ñߵ�����Ϊ0������Ϊ15�����������1->2����
 *   �ﵽ�����ɼ�20ʱ���д������1->2�߱�Ϊ20-20=0��Ҳ�����������ڲд�����
 *   ���������������������߲��ٴ��ڣ�ͬʱ2->1��������ƽ�бߵ�������Ϊ20��
 *   �д�������������һ�����������б�ʾ��
 *   ����·����
 *   �ڲд������д�Դ����ͨ������һ��·����
 *   FordFulkerson��ִ��ʱ����ȡ����Ѱ�����·�����㷨ʱ�䡣Edmonds-Karp��
 *   �����д������еı���Ϊ��λ�ȳ��������������飬����Ѱ��Դ�㵽������
 *   ��·���ķ���Ѱ������·���������������·����ΪҪ���������·����
 * 5.Push-Relabel����
 *   �� ����-������ǩ����������ָ����������������ǩָ�������µ���һ������
 *   �ĸ߶ȱ�ǩ������㷨Χ��Push��Relabel�������������С���FordFulkerson
 *   ����Ч������������Ԥ�����͵��������������ɣ���������excess����ˮ�أ���
 *   ���ͣ�Push�����߶ȱ�ǩ��H���ĸ������Push����Relabel��������Ȼ����
 *   �д������Ͻ��в���(�����ԶԷ�ƽ�б߽��в���)��
 *   �ڻ���˼�룺��ʼ��Դ��S�ͳ���������������S��ÿ�����߶���������ΪԤ
 *   ����ÿ�����㽫���յ���Ԥ���洢�ڳ������ֶΣ�excess�������൱��һ����
 *   ˮ�ء���u����ˮ������ˮʱ(excess>0)���ɴ���ˮ����ȡˮ�������ͣ�uֻ��
 *   �������ڽ�ͷ����߶���͵Ķ���min_v�������ж����������������u�ĸ߶�
 *   �����min_v��1����ˮ���ʹ�������ͬʱҪ��֤u->min_v���в�������������
 *   �����Ĵ�С��u->min_v�Ĳ���������u����ˮ�ش�ˮ��excess�����н�С��һ��
 *   ������������ʱH(u)<=H(min_v)������Ҫ��u�ĸ߶����µ���������ΪH(min_v)+1��
 *   ���Ժ��ٴα�����u����ʱ�Ա����ͣ�Ҳ�ɵ����ع�ѭ���������ͣ�����ˣ���
 *   u��ˮ����ˮ�Ĵ�ǰ����(excess>0)���ǽ������Ͳ�������������ǩ������ȡ
 *   ����H(u)�Ƿ�==H(min_v)+1����1��excess=10��1->2 1->3 1->4��H(1)=1 H(2)
 *   =2 H(3)=2 H(4)=4���򶥵�1�����ڽ�ͷ�����и߶���͵�Ϊ2��3�����Ƚ�1��
 *   �ȵ���Ϊ2+1�����ٴα�����1ʱ�Ϳ��Խ�1�е��������͸�2��3�ˡ���˲�����
 *   �����������ģ����������м䶥�㣬ֱ�������м䶥���excess��Ϊ0��(��
 *   ����ܰ����˽�������������ͻ�Դ��)���㷨��ֹ��
 *   �����ܽ᣺
 *   ����������ǩ�Ĳ����������Ƶ����ڱ��������У�u�ĸ߶�ʼ��<=H(min_v)+1��
 *   �����ÿ�α���һ������ʱ��Ҫôִ��Push��Ҫôִ��Relabel��
 *   u�������͵�������u����ˮ��excess����ˮ��u�ĸ߶�==H(min_v)+1��u->min_v
 *   �������в�������(�ռ�)�ɹ����͡����ж������ͣ��߶ȹ����пռ�ɹ����͡�
 *   u����������ǩ��������u����ˮ��excess����ˮ��u�ĸ߶�<=H(min_v)��������
 *   ǩ��������Ҫ����u�ĳ����Ƿ��в������������������Լ������飬��u�ı�ǩ
 *   ����Ҫ�󼴿ɣ�������û�пռ�ȥ���ͣ�����������Ҫ�жϵ����顣
 *   ע������u�����������У��߶������ɷſ���ֻҪu��v�߼��ɣ���Ӧ�������Ƿ�
 *   ִ�����ͣ�ÿ�α���u��ֻ��������ǩ(�߶�+1)���ɡ��������Խ�ʡ���������
 *   �߶ȵ�ʱ�䣬�������ڸ߶�ÿ�����ֻ������1����˱����Ĵ���Ҳ�����ӡ�
 * 6.ǰ��������ǩ�㷨
 *   ��ʼ������������-������ǩ����һ������ͬ���ǣ�������ǩ������һ���˱���
 *   �����м䶥�㣬ÿ�ο��ܽ�u�д洢������ȫ�����ͣ�Ҳ����ֻ����һ���֡���
 *   ǰ��������ǩ�㷨��ÿ�α�����һ���м䶥��u���ͻὫ��洢��������ȫ����
 *   ��ϣ�Ҳ���ͷŵ���excess���㷨ά������������L��N��L�洢�����м䶥����
 *   ���ͷţ�N�洢�����ͷŵĶ���������ڽӶ��㣬��u���г��ߵ�ͷ�����������
 *   �ߵ�β����ļ��ϡ�����ɨ��L��ÿ�δ���һ������u����ɨ��u������N�е�Ԫ��
 *   v����uv�ڲд������з������͵������������ͣ���ɨ��������v���u��δ�ͷ�
 *   ��ϣ����u������ǩ���������ɨ��u������v��ֱ��u�ͷ���ϣ�excess=0����
 *   Ȼ���u���ͷŹ������Ƿ���й�������ǩ�����жϣ������й������轫u��L��
 *   ����ǰ�ã�Ų��L�Ŀ�ͷ����u���˴�����ϣ���L����u����һ���м䶥��u'�ƽ���
 *   ��������u'�����ѭ����ֱ�������L�����е�Ԫ�أ��㷨������
 *
 *						           2017��1��9��
 */
//#define _DEBUG_CLOSE_
#include "../PublicForAlgorithms.h"

#define MAX_VERTEX_NUM 20
#define MAX_VERTEX_NAME_LEN 30
#define MAX_INFINITY 99999999
/*��������-������ǩ��������β�����ڽӵ�ͷ�����и߶���͵Ķ���ĸ߶�*/
#define MAX_MORE_HEIGHT 100 

#define S_P 0 /*��������Դ����ͼ�е�λ�ã�����v_list��һ����ע������ͼ�ı仯������*/
#define T_P 5 /*�������л����ͼ�е�λ�ã�����v_list���һ����ע������ͼ�ı仯������*/

typedef int V_Position;
typedef int Power,Capacity,Flow,Height,Excess;
typedef int G_Type;

typedef struct
{
    Power power;      /*��Ȩֵ*/
    Capacity capacity;/*������*/
    Flow flow;        /*������*/
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
    Height height;/*����ĸ߶ȣ���ǩ��*/
    Excess excess;/*��������ɵĳ�����������ˮ�������ɵ�Ԥ����*/
}VertexData,*P_VertexData;

P_VertexData CreateOneVertexData(char* n)
{
    P_VertexData new_vd = (P_VertexData)malloc(sizeof(VertexData));
    if(new_vd == NULL){ LINE_DEBUG("VertexData malloc failed"); return NULL; }
    strncpy(new_vd->name,n,MAX_VERTEX_NAME_LEN);
    new_vd->height = 0;/*����push-relabel��һ���ֳ�ʼ������*/
    new_vd->excess = 0;/*����push-relabel��һ���ֳ�ʼ������*/
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
    //����
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
    //����
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
    
    //��ϵ��֯
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

/*����ͼ�ͷ�*/
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

/*FordFulkerson�����е�Edmonds-Karp�㷨
 * �����������ֵ*/
int MF_FordFulkerson(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("FordFulkerson G is NULL"); return -1; }
    int P[G->v_num]; /*��Ӧ�������·��ֵ*/
    V_Position F[G->v_num]; /*��Ӧ�������·��ǰ������*/
    int i,j,cur_dist;
    int min_capacity;
    /*�����������ʹ�õĲд�����,R_NET[0][2]������0->2��ʣ���ͨ��������
     *==0���������ߴﵽ��������flow==capacity�����߲�����������*/
    Flow R_NET[G->v_num][G->v_num]; memset(R_NET,0,G->v_num * G->v_num * sizeof(int));
    P_ArcNode arc;
    /*��ʼ���д�����*/
    for(i = 0; i < G->v_num; ++i)
    {
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    R_NET[i][arc->v_head] = arc->info->capacity;
	    arc = arc->arc_tail;
	}
    }
    /*��ʼѭ����������·�������ӱߵ����������²д�����*/
    while(1)
    {
	//��ʼ�����������Դ��
	for(i = 0; i < G->v_num; ++i){ P[i] = MAX_INFINITY; F[i] = -1; }
	P[S_P] = 0;
	//�������·��(Ҳ������·��)
	for(cur_dist = 0;cur_dist < G->v_num; ++cur_dist)
	{
	    for(i = 0; i < G->v_num; ++i)
	    {
		//�������ľ�����ڵ�ǰҪ����ľ���
		if(P[i] == cur_dist)
		{
		    /*����������г��ߣ���ͷ����δ���ʹ������ڸ��������и���
		     *��ͷ��������·��ֵ(����һ��ʹ��)��ǰ������*/
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

	/*�����û��ǰ�����㣬��˵������������·�������������*/
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
	    /*����Դ����߲д�������������������ñ���i�洢*/
	    /*Ҳ�ɸ��ݻ������������������i += R_NET[G->v_num-1][arc->v_tail]*/
	    i = 0;
	    arc = G->v_list[S_P]->arc_first_out;
	    while(arc)
	    {

		i += (arc->info->capacity - R_NET[S_P][arc->v_head]);
		arc = arc->arc_tail;
	    }
	    return i;
	}

	//�ҳ������������·���е���С����
	min_capacity = MAX_INFINITY;
	for(i = G->v_num - 1; i > 0; i = F[i])
	{
	    if(R_NET[F[i]][i] < min_capacity)
	    { min_capacity = R_NET[F[i]][i]; }
	}
	//��������
	for(i = G->v_num - 1; i > 0; i = F[i])
	{
	    //��������·���ߵĲд�����
	    R_NET[F[i]][i] -= min_capacity;
	    //���ӵ��������ķ�ƽ�б�
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
    /*��ʼ���д�����*/
    for(i = 0; i < G->v_num; ++i)
    {
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    R_NET[i][arc->v_head] = arc->info->capacity;
	    arc = arc->arc_tail;
	}
    }
    /*��ʼ��Ԥ��/��ǩ���߶ȣ������ֹ����ڽ�ͼʱ�����*/
    /*flag����Ӧλ��1���б�ʶ��Ӧ�����excess�Ƿ�Ϊ0�������ж����excess��Ϊ0��
     *��������п����͵Ĺ������Ѿ���ɣ��㷨��ֹ*/
    int flag = 0;
    G->v_list[S_P]->data->height = 6;
    arc = G->v_list[S_P]->arc_first_out;
    while(arc)
    {
	R_NET[S_P][arc->v_head] -= arc->info->capacity;
	R_NET[arc->v_head][S_P] += arc->info->capacity;
	G->v_list[arc->v_head]->data->excess += arc->info->capacity;
	flag |= (1 << arc->v_head);//���ö���excess��Ϊ0����ӦλΪ1
	arc = arc->arc_tail;
    }
    //���͵���С����β����洢�������������ڽ�ͷ�������С�߶�
    Flow min_flow,excess_flow; Height min_height;
    /*���������*/
    while(flag)
    {
	/*�������г�Դ��ͻ��֮��Ķ���(��i��Ϊβ����)*/
	for(i = 1; i < T_P; ++i)
	{
	    //��֤excess����ˮ
	    if(G->v_list[i]->data->excess == 0){ continue; }
	    //����β����i����ͷ���ĵ���͸߶�
	    min_height = MAX_MORE_HEIGHT;
	    for(m = 0; m < G->v_num; ++m)
	    {
		if(R_NET[i][m] > 0 && G->v_list[m]->data->height < min_height)
		{ min_height = G->v_list[m]->data->height; }
	    }
	    //�������i�ڸ߶��Ϸ������͵�������������ͷ����j����
	    if(G->v_list[i]->data->height == min_height + 1)
	    {
		for(j = 0; j < G->v_num; ++j)
		{
		    //ȷ��i->j�в�������
		    if(R_NET[i][j] == 0){ continue; }
		    //ֻ�Ը߶���͵��ڽ�ͷ�����������
		    if(G->v_list[j]->data->height == min_height)
		    {
			/*��ѭ���п��ܴ��������������������������Ҫ��ʱ�ж�i��excess*/
			excess_flow = G->v_list[i]->data->excess;
			if(excess_flow > 0)
			{
			    //���Ͳ���
			    min_flow = excess_flow > R_NET[i][j] ? R_NET[i][j] : excess_flow;
			    R_NET[i][j] -= min_flow;
			    R_NET[j][i] += min_flow;
			    G->v_list[i]->data->excess -= min_flow;
			    G->v_list[j]->data->excess += min_flow;
			    //��β��������������excess==0����ӱ�ʶ��ɾ��
			    if(G->v_list[i]->data->excess == 0){ flag &= (~(1 << i)); }
			    //��ͷ���ڵ�����ʶ(ͷ����excess����+min_flow��һ��>0)
			    if(j != S_P && j != T_P){ flag |= (1 << j); }
			}
		    }
		}
	    }
	    //������������ǩ����i���������͸߶ȵ��ڽ�ͷ����ĸ߶ȴ�1
	    else
	    {
		G->v_list[i]->data->height = min_height + 1;
		/*��������ǩ�󵱼��ع�ѭ����������Ͳ�������Ч����ûʲô���
		 *�����Ǹ������һ�㡣����������ع���ֻ�ǽ������Ӻ�֮���
		 *�����в�������*/
		//--i;
	    }
	}
    }
    //��ʾ�д�����
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
    /*����L�����洢���п�������Ķ��㣬0���������ڴ���Ķ���λ��*/
    V_Position L[G->v_num];
    /*�����ڽӶ��������洢����������������ֱ�������Ķ��㣬0λ�÷�Ԫ�ظ���*/
    V_Position N[G->v_num];
    /*residual net*/;
    Flow R_NET[G->v_num][G->v_num];
    for(i = 0; i < G->v_num; ++i){ for(j = 0; j < G->v_num; ++j){ R_NET[i][j] = 0; } }
    /*��ʼ���д�����*/
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
    //��ʼ��Ԥ��
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
    /*���������*/
    for(i = 1; i < T_P; ++i)
    {
	//��ǰ����Ķ���u
	u = L[i];
	old_height = G->v_list[u]->data->height;
	//��ʼ��N����u�������ڽӶ���
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
	N[0] = j;/*N[0]Ϊ��N��Ԫ�ظ�����1���������൱�ڱ�ʶ��N�������ʱ���±�*/
	//�ͷ�u����
	j = 1;
	while(G->v_list[u]->data->excess > 0)
	{
	    v = N[j];
	    //��������������ڽӶ����u��δ�ͷŸɾ�
	    if(j == N[0])
	    {
		//��������ǩ��ÿ������1�������±���u���е��ڽӶ���
		G->v_list[u]->data->height += 1;
		j = 1;
	    }
	    //��������������������������������ͷ�u��excess
	    else if((R_NET[u][v] > 0) && (G->v_list[u]->data->height == (G->v_list[v]->data->height + 1)))
	    {
		//����
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
	//��u�������������ǩ��������u��L��ǰ��
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

    //��ʾ�д�����
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

    printf("FordFulkerson ������������������\n");
    int max_flow = MF_FordFulkerson(digraph_one);
    printf("MAXFLOW = %d\n",max_flow);
    printf("---------------------------------------\n");

    printf("����-������ǩ ������������������\n");
    max_flow = MF_Push_Relabel(digraph_two);
    printf("MAXFLOW = %d\n",max_flow);
    printf("---------------------------------------\n");
    
    printf("ǰ��������ǩ ������������������\n");
    max_flow = MF_Font_Relabel(digraph_three);
    printf("MAXFLOW = %d\n",max_flow);
    printf("---------------------------------------\n");
    
    Digraph_Free(digraph_one);
    Digraph_Free(digraph_two);
    Digraph_Free(digraph_three);

    return 0;
}
