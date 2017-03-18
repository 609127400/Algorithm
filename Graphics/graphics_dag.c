/*
 *                          �����޻�ͼ
 * 1.����ͼ��ʮ������洢��
 * 2.�����޻�ͼ(Directed Acyclic Graph,DAG)�������޻�ͼ��ͼ����������A B����
 *   ��Aͨ��B��·�����������ڴ�·��������������ٻص�A������������޻�ͼ����
 *   �����̵�һ����Ч���ߣ��κι��̶��������ɸ��(�ӹ���)���������������̣�
 *   ������Ҫ�������������⣺�����ܷ�˳�����к������ʱ������ɡ���ͼ�Ķ�����
 *   Ϊһ�����������Ϊ���Ĺ�ϵ��ͼ��ΪAOV(activity on vertex)�����߱�
 *   ʾ�����ΪAOE������Ӧ��Ӧ��Ϊ��������͹ؼ�·�����⡣
 * 3.���ļ�⡣
 *   ����ͼ�ϼ򵥣�ͨ������ɾ��(���)��<=1�Ķ��㼰�������������
 *   �ı�(ע������ɾ���ı�׼������ͼ����Ķȣ��κ�������һ������ı߶��Ǹö���
 *   ��һ����)����������㶼ɾ��(���)��ϣ��򲻴��ڻ���������ڻ���
 *   ����ͼ�ϸ��ӣ�����������(1)���������������������ϣ��Դ��ڽڵ�δ��ӡ��
 *   ������˵���л���(2)��DFS�жԶ������0 1 2 ����״̬��ǣ�0��ʾδ���ʣ�1��ʾ
 *   �ö���ĺ����������ڷ����У�2��ʾ�ö������г��߼�����������Ѿ�DFS������ϡ�
 *   ��DFS�����з��ʵ�һ��1״̬���㣬��˵�����ڻ���(3)�����ж��㶼���һ��ֵ����
 *   ʼ��Ϊ0����ʾδ���ʹ�����DFS��ÿ����һ�Σ�ֵ+1����A->B������AʱAֵΪ1����
 *   �ݹ�������Bʱ����Bֵ��A�Ļ�����+1��Ϊ2�������AΪ����·���ϵ����ж��㶼D
 *   FS������ϣ���A���Ϊ������������DFS�����У�����һ���������ֵ�Ķ��㣬
 *   ��˵�������ڡ���ʵ���ַ�����(2)����������һ���ģ���Ϊ�˷���Ҳ������״̬��0
 *   δ���ʣ�0< && <��������ʾ��·�����ڷ��ʣ���������ʾ��·��������ϡ�
 * 4.��������TopologicalSort
 *   �� ���ˣ�����������Ĵ�С/����/�ȶ�����Ϣ��ֻ�о������ڲ��������ֻ�����
 *   ������֮��Ľṹ����״��λ�ñ任���䱾������ʵĸı��Լ����ڼ����ϵ��
 *   �� ͼ����������������ͼ�еĶ��㣬��ʵ��Ӧ���д������Ե��Ⱥ�˳��A��
 *   ������ɣ�B���޷���ɣ���A�����Ь�ӣ�B��������ӣ���B-->A��������
 *   ����B����ɲ��ܽ���A�������������������Ҫ�������һ��ǰ���ϵ��ȷ��
 *   �������С����ͼ����������䶼����ǰ��˳����ƴ�ͼ��������ȫ��ģ���
 *   ����Ķ������н��Ψһ��
 *   �� ʵ�ֵķ��������õ������֣��ֱ��Ǵӳ��Ⱥ�����������濼�ǡ�
 *   (1)��ȣ���������ṹ����ÿ��ѭ�������У��ҳ�һ�����Ϊ0�Ķ�����������
 *   ��������β����Ȼ��(ģ��)ɾ������㼰�����˵�ıߡ���Ϊ��ÿ��ѭ�������У�
 *   ���Ϊ0��˵���˸ö����Ѿ�û��ǰ������(�¼�),���Է�������β����¼�����ַ�
 *   ���ڽ������������ͬʱ��Ҳ���Խ��м��ͼ���Ƿ���ڻ���
 *   (2)���ȣ�����ջ�ṹ�����ȳ������ʺ�ͼ��������ȱ���DFS�ĵݹ����ʡ���ÿ��
 *   �ݹ����֮ǰ�����������ջ�С�DFS�ĵݹ����ʵ���һ��·����һֱ�ߵ���ͷ��
 *   ���ݹ鵽������һ��������Ķ���A�ĳ���һ����0��Ҳ��A������˳��������
 *   ��ɵ��Ǹ��������¼ѹ��ջ�У�Ȼ���˳����εݹ��˻��ϴεĵݹ飬��ʱ������
 *   ����A��ǰ������B��Ҳ����ѹ��ջ�С���ˣ�ֱ�������ж��������ϡ�ջ�е���
 *   �м�Ϊ�����ע�⣺����DFS�������������һ��ǰ����ͼȷ����DAG��������DFS��
 *   ��ʵ�����������ͬʱ��֤ͼ���Ƿ��л���
 * 5.�ؼ�·��
 *   �� �ؼ�·����Ŀ���Ǳ����Щ�ǹؼ��������ȡ��߹ؼ����Ч�����̹��ڡ�
 *   ��Ϊ���̵Ķ���·��һ�㶼���Բ��е�ִ�У������������̵�������ʱ���
 *   ȡ���ںķ��ʱ��Ļ·���������ķ�ʱ����Ļ·���ͱ���Ϊ�ؼ�·����
 *   ����趨���̵Ĺ��ںķ�ʱ����ǹؼ�·�������ĵ�ʱ�䡣
 *   �������̵������һ��ʱ��㣬��ʱԽ����������Ҫ��ʼ��Խ�磬��������(����)
 *   ��ʼʱ��Ϊe�����⣬��Щ��ʱ�϶̵Ļ�����ӻ�ִ�У����ǻ���һ������ʼ
 *   ʱ�䣬����Ϊl�������Ϊ�¼������߳�Ϊ�����һ����A->B��β����A��ʼ����
 *   ����A->B����߻�Ŀ�ʼ������B��A->B�����ͬʱB�¼���ʼ�����翪ʼʱ
 *   ��ָ�ӿ�ʼ���㵽V��������·��ֵ������ʼʱ���������VΪβ�ıߵ�ͷ����
 *   ������ʼʱ���ȥ��(�)�����Ȩֵ����e=l����˵���˻Ϊ�ؼ��������
 *   �ԣ��ؼ�·�������еĵ㶼�ǹؼ��¼������б߶��ǹؼ����
 *   ��һ���������лA 1->2->3��ʱ5���B 1->4->3��ʱ3����1�ǿ�ʼ�㣬3�ǽ�
 *   ���㣬A���Ϊ�ؼ�·�����������̵ĵ���̹���Ϊ5����A���������˵������5��
 *   ǰ��ʼ����e=l����B��e=5��l=3���м���һ��ʱ������5-3=2����B���ǹؼ������
 *   �����翪ʼ�����������������̵�ʱ�����ģ����ʱ������Խ�࣬����Ҫ��Խ�͡�
 *   �� ��ͼ�б���Ϊ���Ϊ0�ı�ʾ���̿�ʼ�㣬����Ϊ0�ı�ʾ���̽����㣬�ؼ�·��
 *   ΪȨֵ(Ȩֵ��������ʱ��)�ۼ�ֵ����·�������ҹؼ�·�����ǲ���e = l��·����
 *   ��˲��ҹؼ�·�����ؼ���ȷ������������翪ʼʱ��e������ʼʱ��l�����
 *   ������/��ʱ�������¼�������/��ʱ�����ó���
 *   �� ÿ�������¼����翪ʼʱ�䣬Խ��Խ�ã����ܿ�ʼ��ʱ��Ϳ�ʼ�����ÿ������
 *   Ҫ����������ʼ��ʱ����e������Խ��Խ�ã����ܲ���ʼ�Ͳ���ʼ�����ÿ������
 *   Ҫ��������������ʱ����l�����ǿ�ʼ��ʱ���ٿ�ʼ�����Լ���ڵ�����ʱ��ʱ����
 *   ����ʼ�㿪ʼ���ۼƼ��㵽�������������������ʼʱ��ʱ�����Դӽ����㿪ʼ��
 *   �ۼƼ��㵽��ʼ�������
 *   �������������A->B->C->D A->E->C->D A->F->G->D������ʱ�����ģ�A->B 2 B->C 3
 *   C->D 1 A->E 5 E->C 1 E->D 2 A->F 3 F->G 3 G->D 3��AΪ��ʼ�㣬DΪ�����㣬��
 *  e��                                                      l��
 *   A                                                        D
 *   |-->B--->C->D                                A-->B--->C->|
 *   |----->E->C->D                              A----->E->C->|
 *   |--->F--->G--->D                          A--->F--->G--->|
 *ʱ��------------------------------------------------------------------>��С����
 *
 *   ���㶥�����翪ʼʱ�䣬BΪ2 CΪ6 DΪ9 EΪ5  FΪ3 GΪ6  �յ�D����⣬������;��
 *   ����C����B->C,E->C����C�����ʱ��ȷ���Ĺ��������߼�Խ��Խ�ã���ΪA->B��ʱ2��
 *   A->E��ʱ5����ΪC��Ҫ��BΪǰ����ҲҪ��EΪǰ���������������ҲҪ��A->E�����A->B
 *   ���Ļ�����C���ܿ�ʼ��
 *   ���㶥������ʼʱ�䣬C=8-1=7��B=8-(1+3)=4��...��ͬ���������A����B��E��F��ǰ
 *   ������ͼ�м��ɿ�����A�ϵ�����ҲҪ��B->A E->A F->A��ѡ��ʱ��ֵ��С�ģ�Ϊ0������
 *   ���ܱ�֤��ʱ����Ǹ��·��A-F-G-D�ܹ�˳����ɡ�
 *   �� ����ʵ�֡�
 *   ������������V_EARLIEST V_LASTIEST���ֱ��¼ÿ����������翪ʼʱ�������ʼʱ�䣬
 *   �ֱ��ʼ��Ϊ0���յ�����(��)��ʼʱ�䡣
 *   ����˼·����ʼʱ��0ȷ��->�ó��������������ʱ����������ʱ��->��Ϊ�յ�����翪
 *   ʼʱ����ʵҲ���������ʱ�䣬���յ㵹�ƣ��ó������������ʼʱ��->�ó��������
 *   �͹ؼ�·����
 *   (1)�����¼����翪ʼʱ�䣬�ó��յ�����翪ʼʱ�䡣��ʵ����ͼ���������ɨ�裬����
 *   �У���ʼ����Ϊ0����ÿ��β��������翪ʼʱ��+�ߵĳ���ʱ��(Ȩֵ) > ͷ������������
 *   ��ʼʱ�䣬�����ͷ��������翪ʼʱ�䡣����ı�����˳��ģ����Կ�����DFS/BFS/����
 *   ����ȵȡ�
 *   (2)�����¼�����ʼʱ�䡣��ʵ��ͼ���������ɨ�裬����ÿ���ߵ�ͷ������β���㷽��
 *   �յ���ʼ���㷽��������յ�����ʼʱ�伴�����翪ʼʱ�䡣�൱����l��Ϊ��׼������
 *   ��ͷ��������ʼʱ��-�ߵĳ���ʱ��(Ȩֵ) < β�������е�����ʼʱ�䣬�����β����
 *   ������ʼʱ�伴�ɡ��������������Ҳ������ʮ������洢�ṹ�����ơ�
 *   (3)�ٴ��������ͼ�������¼�������/��ʱ�䣬������������/��ʱ�䣬��A->B����
 *   ����β����A�����翪ʼʱ��=ͷ����B������ʼʱ��-�ߵ�Ȩֵ��A->B��Ϊ�ؼ�·��������
 *   ������չ�жϵ�����������β����A������ʼʱ��+�ߵ�Ȩֵ=ͷ�������翪ʼʱ�䣬Ҳ����
 *   ��A->BΪ�ؼ�·����
 *
 *                                                             2016��11��28��
 */

#define _DEBUG_CLOSE_
#include "../PublicForAlgorithms.h"

#define MAX_ARC_NAME_LEN 60
#define MAX_VERTEX_NUM 100
#define MAX_VERTEX_NAME_LEN 60
#define MAX_VERTEX_ADDR_LEN 100
#define MAX_MAX_MAX_VALUE 100000 /*���ڼ������ͼ�Ƿ��л������������*/

typedef int V_Position;   /*����λ��*/
typedef int Power;        /*��Ȩֵ*/
typedef int G_Type;/*ͼ����*/

//����Ϣ����
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

//��
typedef struct Edge
{
    bool if_visited;
    V_Position v_tail;     /*����ͼ�б�ʾβ����λ�ã�����ͼ�б�ʾ�ߵ�һ������λ��*/
    V_Position v_head;     /*����ͼ�б�ʾͷ����λ�ã�����ͼ�б�ʾ�ߵ���һ������λ��*/
    struct Edge* arc_tail; /*����ͼ�б�ʾ�����������һ���ߣ�����ͼ�б�ʾ�����ڶ������һ����*/
    struct Edge* arc_head; /*����ͼ�б�ʾ����������һ���ߣ�����ͼ�б�ʾ��������һ���������һ����*/
    P_Arc_Info info;       /*����Ϣ*/
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

//������������
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

//��
typedef struct
{
    P_V_Data_Type data;      /*��������*/
    P_ArcNode arc_first_in;  /*����ͼ�б�ʾ����ĵ�һ����ߣ�����ͼ��ʹ�ô��ֶ�*/
    P_ArcNode arc_first_out; /*����ͼ�б�ʾ����ĵ�һ�����ߣ�����ͼ�б�ʾ����ĵ�һ����*/
}VertexNode, *P_VertexNode;

//������ʸ�����ʶ
bool V_VISITED_FLAGS[MAX_VERTEX_NUM];

//���㴦����
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

//ͼ
typedef struct
{
    G_Type g_type;
    P_VertexNode v_list[MAX_VERTEX_NUM];
    int v_num; int arc_num;
}Graphics, *P_Graphics;

//����/ջ���
typedef struct Node
{
    V_Position v_p;
    struct Node* next;
}Node,*P_Node;

//����/ջ
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
//��������
void InsertListNode(P_Form list,P_Node node)
{
    if(list == NULL || node == NULL)
    { LINE_DEBUG("InsertFormNode arguments or illegal"); return; }
    if(list->head == NULL){ list->head = node; list->tail = node; }
    else{ list->tail->next = node; list->tail = node; }
    ++(list->node_num);
}
//����ջ
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

/*  AOV��
 *  ��������������
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
    //���������ݣ�����Ϣ���㣬�ߣ�ͼ
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
    //��������Ϣ
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
    //������
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
    //����������
    data0 = CreateOneVertexData(0,"V0","��ַ0"); data1 = CreateOneVertexData(1,"V1","��ַ1"); 
    data2 = CreateOneVertexData(2,"V2","��ַ2"); data3 = CreateOneVertexData(3,"V3","��ַ3");
    data4 = CreateOneVertexData(4,"V4","��ַ4"); data5 = CreateOneVertexData(5,"V5","��ַ5");
    data6 = CreateOneVertexData(6,"V6","��ַ6"); data7 = CreateOneVertexData(7,"V7","��ַ7");
    data8 = CreateOneVertexData(8,"V8","��ַ8"); data9 = CreateOneVertexData(9,"V9","��ַ9");
    data10 = CreateOneVertexData(10,"V10","��ַ10"); data11 = CreateOneVertexData(11,"V11","��ַ11");
    if(data0 == NULL || data1 == NULL || data2 == NULL || data3 == NULL
    || data4 == NULL || data5 == NULL || data6 == NULL || data7 == NULL
    || data8 == NULL || data9 == NULL || data10 == NULL|| data11 == NULL)
    { LINE_DEBUG("VertexData Create failed"); goto Label_CreateDigraphOne_Clean; }
    //������
    V0 = CreateOneVertex(data0); V1 = CreateOneVertex(data1); V2 = CreateOneVertex(data2);
    V3 = CreateOneVertex(data3); V4 = CreateOneVertex(data4); V5 = CreateOneVertex(data5);
    V6 = CreateOneVertex(data6); V7 = CreateOneVertex(data7); V8 = CreateOneVertex(data8);
    V9 = CreateOneVertex(data9); V10 = CreateOneVertex(data10); V11 = CreateOneVertex(data11);
    if(V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL || V4 == NULL || V5 == NULL
    || V6 == NULL || V7 == NULL || V8 == NULL || V9 == NULL || V10 == NULL|| V11 == NULL)
    { LINE_DEBUG("Vertex Create failed"); goto Label_CreateDigraphOne_Clean; }
    //����ͼ
    new_digraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_digraph == NULL){ LINE_DEBUG("Graphics malloc failed"); goto Label_CreateDigraphOne_Clean; }
    
    //��ϵ��֯
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

/* AOEͼ
 * ���ؼ�·���㷨ʹ��
 * 
 *   0--1--4      Ȩֵ����ʾ���ʱ
 *   |  |  |      0->1 3   0->2 2   1->3 2   1->4 3
 *   |  3  |      2->3 4   2->5 3   3->5 2   4->5 1
 *   | / \ |      
 *   2-----5
 */
P_Graphics CreateDigraphTwo(void)
{
    //���������ݣ�����Ϣ���㣬�ߣ�ͼ
    P_Arc_Info info0_1 = NULL; P_Arc_Info info0_2 = NULL; P_Arc_Info info1_3 = NULL; P_Arc_Info info1_4 = NULL;
    P_Arc_Info info2_3 = NULL; P_Arc_Info info2_5 = NULL; P_Arc_Info info3_5 = NULL; P_Arc_Info info4_5 = NULL;
    P_ArcNode Arc0_2  = NULL; P_ArcNode Arc0_1 = NULL; P_ArcNode Arc2_3  = NULL; P_ArcNode Arc1_4 = NULL;
    P_ArcNode Arc1_3  = NULL; P_ArcNode Arc2_5 = NULL; P_ArcNode Arc3_5  = NULL; P_ArcNode Arc4_5 = NULL;
    P_V_Data_Type data0 = NULL; P_V_Data_Type data1 = NULL; P_V_Data_Type data2 = NULL; P_V_Data_Type data3 = NULL;
    P_V_Data_Type data4 = NULL; P_V_Data_Type data5 = NULL;
    P_VertexNode V0 = NULL; P_VertexNode V1 = NULL; P_VertexNode V2 = NULL; P_VertexNode V3 = NULL;
    P_VertexNode V4 = NULL; P_VertexNode V5 = NULL;
    P_Graphics new_digraph = NULL;
    //��������Ϣ
    info0_2 = CreateOneArcInfo(2,"V0->V2"); info0_1 = CreateOneArcInfo(3,"V0->V1");
    info2_3 = CreateOneArcInfo(4,"V2->V3"); info1_4 = CreateOneArcInfo(3,"V1->V4");
    info1_3 = CreateOneArcInfo(2,"V1->V3"); info2_5 = CreateOneArcInfo(3,"V2->V5");
    info3_5 = CreateOneArcInfo(2,"V3->V5"); info4_5 = CreateOneArcInfo(1,"V4->V5");
    if(info0_2 == NULL || info0_1 == NULL || info2_3 == NULL || info1_4 == NULL
    || info1_3 == NULL || info2_5 == NULL || info3_5 == NULL || info4_5 == NULL)
    { LINE_DEBUG("ArcInfo Create failed"); goto Label_CreateDigraphTwo_Clean;}
    //������
    Arc0_2 = CreateOneArc(info0_2); Arc0_1  = CreateOneArc(info0_1);
    Arc2_3 = CreateOneArc(info2_3); Arc1_4  = CreateOneArc(info1_4);
    Arc1_3 = CreateOneArc(info1_3); Arc2_5  = CreateOneArc(info2_5);
    Arc3_5 = CreateOneArc(info3_5); Arc4_5 = CreateOneArc(info4_5);
    if(Arc0_2 == NULL || Arc0_1  == NULL || Arc2_3 == NULL || Arc1_4  == NULL
    || Arc1_3 == NULL || Arc2_5  == NULL || Arc3_5 == NULL || Arc4_5 == NULL)
    { LINE_DEBUG("ArcNode Create failed"); goto Label_CreateDigraphTwo_Clean; }
    //����������
    data0 = CreateOneVertexData(0,"V0","��ַ0"); data1 = CreateOneVertexData(1,"V1","��ַ1"); 
    data2 = CreateOneVertexData(2,"V2","��ַ2"); data3 = CreateOneVertexData(3,"V3","��ַ3");
    data4 = CreateOneVertexData(4,"V4","��ַ4"); data5 = CreateOneVertexData(5,"V5","��ַ5");
    if(data0 == NULL || data1 == NULL || data2 == NULL || data3 == NULL
    || data4 == NULL || data5 == NULL)
    { LINE_DEBUG("VertexData Create failed"); goto Label_CreateDigraphTwo_Clean; }
    //������
    V0 = CreateOneVertex(data0); V1 = CreateOneVertex(data1); V2 = CreateOneVertex(data2);
    V3 = CreateOneVertex(data3); V4 = CreateOneVertex(data4); V5 = CreateOneVertex(data5);
    if(V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL || V4 == NULL || V5 == NULL)
    { LINE_DEBUG("Vertex Create failed"); goto Label_CreateDigraphTwo_Clean; }
    //����ͼ
    new_digraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_digraph == NULL){ LINE_DEBUG("Graphics malloc failed"); goto Label_CreateDigraphTwo_Clean; }
    
    //��ϵ��֯
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

/*������ֵ����ͼ�Ƿ��л����м��
 *������״̬�ķ���*/
void Graphics_Is_DAG(P_Graphics G,V_Position s_p)
{
    V_VISITED_FLAGS[s_p] = 1;
    P_ArcNode arc = G->v_list[s_p]->arc_first_out;
    while(arc)
    {
	/*�������״̬Ϊ1�Ķ��㣬˵��������ָ���˻��ڱ����е�·����֮ǰ�Ķ��㣬�ض����ڻ�*/
	if(V_VISITED_FLAGS[arc->v_head] == 1)
	{
	    G->g_type = (DIGRAPH | CYCLIC);
	    printf("����ͼ���ڻ�������DFS���е�����������ʾ�����Ч\n"); 
	    return;
	}
	if(V_VISITED_FLAGS[arc->v_head] == 0)
	{ Graphics_Is_DAG(G,arc->v_head); }
	arc = arc->arc_tail;
    }
    /*s_p�������г��ߵ�������ȱ�����ϣ���Ϊ״̬2*/
    V_VISITED_FLAGS[s_p] = 2;
}

/* ���ȣ���������������������������� 
 * ע��ʹ�õ�ǰ���Ǵ����GΪDAG���Ҳ���ͬʱ���л�����*/
void DFS(P_Graphics G,V_Position s_p,P_Form stack)
{
    /*��ʹ��ջ��ʹ�������ڴ�(δ������һ�ֵݹ�ǰ)��û�б����ʹ��ĵ���������У�Ҳ����*/
    /*if(V_VISITED_FLAGS[s_p] == false){ node = CreateOneNode(s_p); InsertListNode(node); }*/
    V_VISITED_FLAGS[s_p] = true;
    
    P_ArcNode arc = G->v_list[s_p]->arc_first_out;
    while(arc)
    {
	if(V_VISITED_FLAGS[arc->v_head] == false)
	{
	    DFS(G,arc->v_head,stack);
	    /*����·��������ݹ���ɣ���v_headѹ��ջ�� */
	    P_Node node = CreateOneNode(arc->v_head);
	    InsertStackNode(stack,node);
	}
	/*��һ����(·��)����*/
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
    /*����Ƿ��л�*/
    Graphics_Is_DAG(G,0);
    if(G->g_type == (DIGRAPH | CYCLIC)){ printf("G is not a DAG\n"); return; }
    i = 0;
    while(i < G->v_num){ V_VISITED_FLAGS[i] = false; ++i; }
    
    /*��ʼ���㲻��Ҫ��������ѭ����������˳�����е��м��ĳ������V��ʼ���
     *��������ǰ����������Ҳ����Stack���ŵ�Vǰ�棬����˳���֧��ǰ������Ҳ
     *���ŵ���ǰ��*/
    i = s_p;
    while(i < G->v_num)
    {
	if(V_VISITED_FLAGS[i] == false)
	{ 
	    DFS(G,i,stack);
	    /*����ʼ�Ľڵ����ջ�У���DFS��(��ջ�Ĳ������������λ��)�޷���������ջ��*/
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

/* ��ȣ�Ѱ�����Ϊ0�Ķ���
 * �����Ϊ0�ĵ㲻����������ɾ�������ǽ��б�ǡ��������V_VISITED_FLAGS
 * ���б�ʶ��ֻ�����洢�Ĳ��ٴ����Ӧ�����Ƿ���ʹ������Ƕ�Ӧ�����ʵʱ
 * ��ȱ�����
 * �����ͼ�����Ƿ�DAG��ͬʱ���л����ԡ�
 */
V_Position GetZeroIndegreeVertex(P_Graphics G,V_Position s_p)
{
    int i = s_p;
    while(i < G->v_num)
    {
	if(V_VISITED_FLAGS[i] == 0)
	{
	    /*��i�������г��ߵ�ͷ�������-1���൱��ɾ����i�����г���*/
	    P_ArcNode arc = G->v_list[i]->arc_first_out;
	    while(arc)
	    {
		--(V_VISITED_FLAGS[arc->v_head]);
		arc = arc->arc_tail;
	    }
	    /*��i���������1��Ϊ-1���Ա�ʶ���Ѿ��������*/
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
    /*�����������Ϊ0�ĵ㣬�򷵻�-1*/
    return -1;
}

/*��ȡ����Ϊ0�Ķ���*/
V_Position GetZeroOutdegreeVertex(P_Graphics G,V_Position s_p)
{
    int i = s_p;
    while(i < G->v_num)
    {
	if(V_VISITED_FLAGS[i] == 0)
	{
	    P_ArcNode arc = G->v_list[i]->arc_first_in;
	    /*ɾ��(���)i�������е����*/
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
	    /*ɾ��(���)i�������е����*/
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
    /*����Ƿ��л�*/
    Graphics_Is_DAG(G,0);
    if(G->g_type == (DIGRAPH | CYCLIC)){ LINE_DEBUG("GraphicsZeroIndgreeTopologicalSort G is not a DAG"); return; }
    
    /*��ʼ��V_VISITED_FLAGS��Ӧ������������*/
    i = 0;
    while(i < G->v_num)
    {
	/*������*/
	count = 0;
	P_ArcNode arc = G->v_list[i]->arc_first_in;
	while(arc){ ++count; arc = arc->arc_head; }
	V_VISITED_FLAGS[i] = count;
	++i;
    }
    /*��ʼ��������ֻ��ѭ��G->v_num�鼴��*/
    i = 0;
    count = 0;
    while(i < G->v_num)
    {
	/*��ȡһ��0��ȶ���λ��*/
	zero_v = GetZeroIndegreeVertex(G,s_p);
	/*������ص�Ϊ-1����˵��δȡ�����Ϊ0�Ķ��㣬˵�����ڻ�*/
	if(zero_v > -1)
	{
	    ++count;/*ÿ����һ�����Ϊ0�Ķ��㣬����һ��*/
	    P_Node node = CreateOneNode(zero_v);
	    InsertListNode(list,node);
	}
	++i;
    }
    /*������е�0��ȶ���������G�Ķ�������˵��G�д�����Ȳ�����Ϊ0�ĵ㣬��ͼ�д��ڻ�
     *�������������������л��ļ��ķ���*/
    if(count < G->v_num)
    { LINE_DEBUG("GraphicsZeroIndgreeTopologicalSort G is not a DAG"); }
}

/*������ȷ������е�����������������ͼΪDAG����������������ȷ*/
void GraphicsTopologicalSortShow(P_Graphics G,P_Form form)
{
    if(G == NULL){ LINE_DEBUG("GraphicsTopologicalSortShow is NULL"); return; }
    if(form == NULL || form->head == NULL){ LINE_DEBUG("GraphicsTopologicalSortShow form is NULL"); return; }
    printf("�����޻�ͼ�������������£�\n");
    P_Node temp_head = form->head;
    while(temp_head != NULL)
    {
	printf("%s",G->v_list[temp_head->v_p]->data->name);
	temp_head = temp_head->next;
	if(temp_head != NULL){ printf(" ---> "); }
    }
    printf("\n");
    if(form->node_num == G->v_num){ printf("ͼ�в����ڻ�\n"); }
    else { printf("ͼ�д��ڻ�\n"); }
}

/*�������飬�洢���������/�����ʱ��*/
int V_EARLIEST[MAX_VERTEX_NUM];
int V_LASTIEST[MAX_VERTEX_NUM];

/*��Ѱͼ�Ĺؼ�·��
 * s_p ͼ����ʼ����λ��*/
void Graphics_CriticalPath(P_Graphics G,V_Position s_p)
{
    /*�������*/
    if(G == NULL){ LINE_DEBUG("Graphics_CriticalPath G is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("Graphics_CriticalPath s_p is illegal"); return; }
    if(G->v_list[s_p]->arc_first_in != NULL)
    { LINE_DEBUG("Graphics_CriticalPath s_p is G's start vertex"); return; }
    /*����Ƿ��л�*/
    Graphics_Is_DAG(G,0);
    if(G->g_type == (DIGRAPH | CYCLIC)){ printf("G is not a DAG\n"); return; }
    
    int i = 0;
    /*��V_EARLIEST��ֵ��ʼ��Ϊ0���൱��e�ߵ�ֵ*/
    for(i = 0; i < G->v_num; ++i){ V_VISITED_FLAGS[i] = 0; V_EARLIEST[i] = 0; }
    /*�����¼����翪ʼʱ��*/
    /*��ʼ��V_VISITED_FLAGS��Ӧ������������*/
    int count = 0;
    P_ArcNode arc = NULL;
    for(i = 0; i < G->v_num; ++i)
    {
	/*������*/
	count = 0;
	arc = G->v_list[i]->arc_first_in;
	while(arc){ ++count; arc = arc->arc_head; }
	V_VISITED_FLAGS[i] = count;
    }

    V_Position zero_v;
    /*�������ͼ�������õķ���������������ı���������ÿ��ȡ�����Ϊ0��һ���㣬��֪��ͼ�Ŀ�ʼ��
     *����ͨ�ı���Ҳ��*/
    for(i = 0; i < G->v_num; ++i)
    {
	/*��ȡһ��0��ȶ���λ��*/
	zero_v = GetZeroIndegreeVertex(G,s_p);
	/*������ص�Ϊ-1����˵��δȡ�����Ϊ0�Ķ��㣬˵�����ڻ�*/
	if(zero_v > -1)
	{
	    /*�����zero_v��Ϊβ������б���*/
	    arc = G->v_list[zero_v]->arc_first_out;
	    while(arc)
	    {
		/*���β��������翪ʼʱ��+�߻�ĳ���ʱ��(Ȩֵ) > ͷ��������翪ʼʱ�䣬��ֵ*/
		if((V_EARLIEST[zero_v] + arc->info->power) > V_EARLIEST[arc->v_head])
		{ V_EARLIEST[arc->v_head] = V_EARLIEST[zero_v] + arc->info->power; }
		arc = arc->arc_tail;
	    }
	    
	    /*
	    //��һ�ַ�������Ϊβ������б�����ȥ������ͷ��������翪ʼʱ��
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
    
    /*��������ʼʱ��*/
    /*��V_LASTIEST��ֵ����ʼ��Ϊ�����������Ļ���ֵ���൱��l�ߵ�ֵ*/
    for(i = 0; i < G->v_num; ++i){ V_VISITED_FLAGS[i] = 0; V_LASTIEST[i] = V_EARLIEST[G->v_num - 1]; }
    /*��ʼ��V_VISITED_FLAGS��Ӧ������ĳ�����*/
    for(i = 0; i < G->v_num; ++i)
    {
	/*������*/
	count = 0;
	arc = G->v_list[i]->arc_first_out;
	while(arc){ ++count; arc = arc->arc_tail; }
	V_VISITED_FLAGS[i] = count;
    }
    /*�������ͼ�������õķ�����������������ı���������ÿ��ȡ������Ϊ0��һ���㣬��֪��ͼ���յ�
     *����ͨ�ı���Ҳ��*/
    for(i = 0; i < G->v_num; ++i)
    {
	/*��ȡһ��0���ȶ���λ��*/
	zero_v = GetZeroOutdegreeVertex(G,G->v_num - 1);
	/*������ص�Ϊ-1����˵��δȡ������Ϊ0�Ķ���*/
	if(zero_v > -1)
	{
	    /*�����zero_v��Ϊͷ������б���*/
	    arc = G->v_list[zero_v]->arc_first_in;
	    while(arc)
	    {
		/*���ͷ���������ʼʱ��-�߻�ĳ���ʱ��(Ȩֵ) < β���������ʼʱ�䣬��ֵ*/
		if((V_LASTIEST[zero_v] - arc->info->power) < V_LASTIEST[arc->v_tail])
		{ V_LASTIEST[arc->v_tail] = V_LASTIEST[zero_v] - arc->info->power; }
		arc = arc->arc_head;
	    }
	}
    }

    /*���������������飬����e==l�Ļ*/
    /*�����Ŀ�ʼʱ�� = β����(�¼�)���翪ʼ��ʱ�䣬��ʱ�൱�ڴ�e�߳�����β���㻹��β����
     *�����ʼ��ʱ�� = ͷ��������ʼʱ��-�ߵ�Ȩֵ����ʱ�൱�ڴ�l�߳�����ͷ��������β
     *ȷ����β��ͷ�����Ǵ�e�߳������Ǵ�l�߳��������Ǻϣ�����ȷ��һ�����ǹؼ��*/
    for(i = 0; i < G->v_num; ++i)
    {
	/*i��Ϊβ������б���*/
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    /*�ڴ�Ҳ�����ÿ���ߵ�ʱ������*/
	    if(V_EARLIEST[i] == (V_LASTIEST[arc->v_head] - arc->info->power))
	    { printf("%s ",arc->info->name); }
	    arc = arc->arc_tail;
	}
    }
    printf("\n");
}

/*ͼ���ͷ�*/
void GraphicsFree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("GraphicsFree G is NULL"); return; }
    int i = 0;
    while(i < G->v_num){ V_VISITED_FLAGS[i] = false; ++i; }
    P_ArcNode arc = NULL;
    P_ArcNode temp_arc = NULL;
    while(i < G->v_num)
    {
	//�ͷŵ�����
	SAFE_FREE(G->v_list[i]->data);
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    temp_arc = arc;
	    arc = arc->arc_head;
	    //�ͷ����г�����Ϣ�ͳ���
	    SAFE_FREE(temp_arc->info);
	    SAFE_FREE(temp_arc);
	}
	//�ͷŵ�
	SAFE_FREE(G->v_list[i]);
    }
    arc = NULL; temp_arc = NULL;
    //�ͷ�ͼ
    SAFE_FREE(G);
}

int main()
{
    //��ͼ
    P_Graphics digraph_one = CreateDigraphOne();
    if(digraph_one == NULL){ LINE_DEBUG("digraph_one create failed"); return -1; }
    P_Graphics digraph_two = CreateDigraphTwo();
    if(digraph_two == NULL){ LINE_DEBUG("digraph_two create failed"); return -1; }
    //������/ջ
    P_Form stack = CreateOneForm();
    if(stack == NULL){ LINE_DEBUG("stack create failed"); return -1; }
    P_Form list = CreateOneForm();
    if(list == NULL){ LINE_DEBUG("list create failed"); return -1; }
    //DFS������������
    GraphicsDFS_TopologicalSort(digraph_one,0,stack);
    GraphicsTopologicalSortShow(digraph_one,stack);
    printf("------------------------------------\n");
    //0��ȷ���������
    GraphicsZeroIndgreeTopologicalSort(digraph_one,0,list);
    GraphicsTopologicalSortShow(digraph_one,list);
    printf("------------------------------------\n");
    //��ؼ�·��
    Graphics_CriticalPath(digraph_two,0);

    //������
    FormFree(stack);
    FormFree(list);
    GraphicsFree(digraph_one);
    GraphicsFree(digraph_two);

    return 0;
}
