/*
 *                         ͼ�ı���
 * 1.��ҪԪ�ط�Ϊ �㡢����ߣ�ͼ��������ɷ�Ϊ ����ͼ������ͼ��������ͼ�б���
 *   Ϊ����������ͼ�����Ϊ�ߡ�tail------->head
 *   ͼ������ָ���Ƕ����û�й̶�����Եķ����ϵ�������ʱ�ȿ�����a��bҲ����
 *   ��b��a����������˵�ڱ��������ʱ��û�з���һ���ڱ���ʱ��a->b��֮�󻹻�
 *   ��b->a�ı�����ֻ�Ǵ�ʱa���Ѿ�����Ƿ��ʹ��ĵ����a-b�����߱���ǹ��ѷ���
 *   �������Բ����ٽ���b->a�ı�������������ͼ�е�ͷ��β��Ҫ���������⣬a��ʱ
 *   ��Ϊb��ͷ������������һ�α����оͱ��b��β��
 * 2.��ʾ�������ڽӾ����ڽӱ��������ͼ��ʮ�������������ͼ���ڽӶ��ر�
 * 3.ͼ�ı�������Ϊ������Ⱥ͹������������ʽ�����������������һ���㣬������
 *   �õ��йص�(�����)�����߻������˳�������ȥ�������Ƿ���δ�����ʵĵ㣬��
 *   ���У���������������ȥ����˵ݹ����������һ�ö�����(���߸����֧��ԭ
 *   ��һ��)��ֻ�Ƿ�֧�������������������Ƕ�����Ҷ�ڵ��lchild/rchildָ��NULL��
 *   �����жϷ��ʵĽڵ��Ƿ�֮ǰ�����ʹ���������Ƚ������У�����ʼ���ʵĽڵ�ѹ��
 *   ���к�ʼ������ÿ����һ�����㣬�ͽ�������ö�����������δ�����ʹ��Ľڵ�ѹ
 *   ����С����ѭ����ֱ������Ϊ�ա�
 *   ͼ��DFS��BFS�Ĳ������һ����ֻ����Բ�ͬ�Ĵ洢�ṹ�ڵ�����������ϸ΢�Ĳ��
 *   DFS��
 *   �� ������A����ʶ
 *   �� ��ȡA����ı�����(������)�ĵ�һ����(�ڵ�)
 *   �� ѭ����������������A�ı�(�൱�ڴ�������)����ÿ��ѭ���У�(ͨ����)��ȡ��
 *      ����һ������B��������Bδ�����ʹ�����ݹ����DFS�Ӣ����¿�ʼ���д���
 *      ��������������ѭ��(����һ����)��
 *   BFS��
 *   �� ѹ��ָ����ʼ���ʵĶ��㲢��ʶ
 *   �� ��ʼ������ѭ�����²��裬ֱ������������Ԫ�أ�
 *      (1)�Ӷ����е���һ������A
 *      (2)��������������A�ı�(�൱�ڵ�������)��(ͨ����)��ȡ��һ������B�����
 *         Bδ�����ʹ�����ѹ����в���ʶ��
 * 4.��ʹ�õ�ͼ���£�Ϊ��ͨͼ
 *       V0               ����ͼ�����˷���Ϊ��V0->V1 V0->V2 V1->V3 V1->V4 V4->V7
 *     /    \             V3->V7 V2->V5 V5->V6 V6->V2
 *   V1      V2
 *  /  \    /  \
 * V3  V4  V5��V6  
 *  \  /
 *   V7
 *   ��Ҫ�ĺ���
 *   �ڽӾ���
 *   CreateOneMatrixUndigraph
 *   Undigraph_Matrix_DFS
 *   Undigraph_Matrix_BFS
 *   MatrixFree
 *   �ڽӱ�
 *   CreateOneAdjacencyListUndigraph
 *   CreateOneAdjacencyListDigraph
 *   Undigraph_AdjacencyList_DFS
 *   Undigraph_AdjacencyList_BFS
 *   AdjacencyListFree
 *   �ڽӶ��ر�
 *   CreateOneMultilistUndigraph
 *   Undigraph_Multilist_DFS
 *   Undigraph_Multilist_BFS
 *   MultilistFree
 *   ʮ������
 *   CreateOneOrthogonalListDigraph
 *   Digraph_OrthogonalList_DFS
 *   Digraph_OrthogonalList_BFS
 *   OrthogonalListFree
 *   ͼ��ʾ
 *   Graphics_OrthMult_Show
 *   ������ĺ�����ʵ�ֿ�֪��DFS��BFS���㷨����ͨ���ԣ�ֻ�ǲ�ͬ�Ĵ洢�ṹ�ڵ�������
 *   ����ϸ΢�Ĳ��
 *
 *
 *
 *
 *                                                        2016��11��17��
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

/*������������*/
typedef struct
{
    int    id;         /*���*/
    V_TYPE type;       /*����*/
    double longtitude; /*����*/
    double latitude;   /*γ��*/
    char   name[MAX_DATA_NAME_LEN];    /*����*/
    char   address[MAX_DATA_ADDR_LEN]; /*��ַ*/
}V_DataType, *P_V_DataType;
/*�����б�λ�����ͣ�����Ϣ���ͣ�Ȩ������*/
typedef int  V_Position;
typedef char Arc_Info[MAX_EDGE_INFO_LEN];
typedef int  Power;

/* �ߣ���Ҫ����ڽӶ��ر��ʮ��������ƣ��ڽӱ����ֻʹ������arc_head,v_head��info�����ֶ�
 * ����Ĵ洢��ʽ�����Create����
 */
typedef struct Edge
{
    IF_VISITED   if_visited;/*����ͼ�в�ʹ�ô����ݣ�����ͼ�д���ýڵ��Ƿ񱻷��ʹ��ı�ʶ*/
    V_Position   v_tail;    /*����ͼ�д���β�����λ�ã�����ͼ�д���ߵ�һ������A*/
    V_Position   v_head;    /*����ͼ�д���ͷ�����λ�ã�����ͼ�д���ߵ�һ������B*/
    struct Edge* arc_head;  /*����ͼ�д���ͷ������ͬ����һ���ߣ�����ͼ�д���߶���A����һ����*/
    struct Edge* arc_tail;  /*����ͼ�д���ͷβ����ͬ����һ���ߣ�����ͼ�д���߶���B����һ����*/
    Power        power;     /*�ߵ�Ȩ�أ�ֵԽ��Ȩ��Խ��*/
    Arc_Info     info;      /*�ߵ���Ϣ*/
}ArcNode,*P_ArcNode,*ArcsList;

//����
typedef struct
{
    P_V_DataType data;         /*��������*/
    P_ArcNode    arc_first_in; /*����ͼ�д���ö���ĵ�һ����ߣ�����ͼ����ö���ĵ�һ����*/
    P_ArcNode    arc_first_out;/*����ͼ�д���ö���ĵ�һ�����ߣ�����ͼ��ʹ�ô�����*/
}VertexNode,*P_VertexNode,*VertexesList;

//�����㺯��
typedef void (*V_Handle_Fun_Type)(P_VertexNode);

void V_Handle1(P_VertexNode v)
{
    if(v == NULL || v->data == NULL){ LINE_DEBUG("Vertex or V->data is NULL"); return; }
    printf("######################## ������Ϣ ########################\n");
    printf("+  id : %d\n",v->data->id);
    printf("+  type : ");
    switch(v->data->type)
    {
	case SHOP: printf("�̵�\n");     break; case MARKET: printf("�̳�\n");         break;
	case HOSPITAL: printf("ҽԺ\n"); break; case GOVERNMENT: printf("��������\n"); break;
	case PARK: printf("ͣ����\n");   break; case GARDEN: printf("��԰\n");         break;
	case MOVIES: printf("��ӰԺ\n"); break; case SCHOOL: printf("ѧУ\n");         break;
	case HOUSE: printf("סլ��\n");  break; default: printf("δ֪\n");             break;
    }
    printf("+  longtitude : %.4f\n",v->data->longtitude);
    printf("+  latitude : %.4f\n",v->data->latitude);
    printf("+  name : %s\n",v->data->name);
    printf("+  address : %s\n",v->data->address);
    printf("\n");
}
//Vhandle2 ...

//ͼ
typedef struct
{
    G_TYPE g_type;                      /*ͼ���ͣ�����ͼ������ͼ*/
    VertexesList v_list[MAX_VERTEX_NUM];/*�����б�*/
    P_ArcNode  arc_matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; /*�߾���ֻ���ڽӾ���ʹ��*/
    int v_num, arc_num;                 /*������������*/
}Graphics, *P_Graphics;

//����
typedef struct
{
    V_Position queue[MAX_VERTEX_NUM];
    int r_p;
    int w_p;
    int count;
}Queue,*P_Queue;

/*������������*/
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

/*��������*/
P_VertexNode CreateVertexNode(void)
{
    P_VertexNode new_vertex = (P_VertexNode)malloc(sizeof(VertexNode));
    if(new_vertex == NULL){ LINE_DEBUG("New Vertex malloc failed"); return NULL; }
    new_vertex->data = NULL;
    new_vertex->arc_first_in  = NULL;
    new_vertex->arc_first_out = NULL;
    return new_vertex;
}

/*������*/
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
 * �ڽӾ���
 * ֻ�ñ߽ṹ�е�info��power�ȴ洢����Ϣ���ֶΣ�������Ҫ����߹�ϵ���ӵ�ָ�롣
 * ����ṹֻ��data�ֶΡ��������֯��������0��1 2������������������0����һ��
 * ��1 2�����д�����Arc0_1�����ߵ���Ϣ����1��ʾ���������ÿ���0��ʾ�����£�
 *  �� 0 1 2 3 4 ...
 *  ��
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
    
    //��͵�����
    V0 = CreateVertexNode(); V1 = CreateVertexNode();
    V2 = CreateVertexNode(); V3 = CreateVertexNode();
    V4 = CreateVertexNode(); V5 = CreateVertexNode();
    V6 = CreateVertexNode(); V7 = CreateVertexNode();
    V0_data = CreateVertexDataNode(0,SHOP,123.52,175.21,"���ָ�����","֣�ݽ�ˮ·10��");
    V1_data = CreateVertexDataNode(1,MOVIES,103.54,123.14,"���ӰԺ","����������·67��");
    V2_data = CreateVertexDataNode(2,GARDEN,93.78,142.01,"�Ϻ���˹����԰","�Ϻ����ֶ���ϼ��·054��");
    V3_data = CreateVertexDataNode(3,PARK,41.32,75.47,"�������ŵ���ͣ����","�Ͼ��н���������·������");
    V4_data = CreateVertexDataNode(4,GOVERNMENT,124.37,154.00,"����������","�����о���·�Ϻ�������������");
    V5_data = CreateVertexDataNode(5,SCHOOL,142.01,86.32,"֣���е�����ѧ","֣����ȫ·7��");
    V6_data = CreateVertexDataNode(6,HOUSE,107.32,53.47,"�ʹ�����Ժ��","�����г�����127��");
    V7_data = CreateVertexDataNode(7,UNKNOWN,67.98,45,"���¹�����","����������");
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
    
    //��
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
    
    //ͼ
    new_undigraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_undigraph == NULL)
    { LINE_DEBUG("New Undigraph malloc failed"); goto Label_CreateOneMatrixUndigraph_Clean; }
    new_undigraph->g_type = UNDIGRAPH;
    //������0
    memset(new_undigraph->arc_matrix,0,MAX_VERTEX_NUM*MAX_VERTEX_NUM);
    new_undigraph->v_num   = 8;
    new_undigraph->arc_num = 9;

    //��ϵ��֯
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
 * �ڽӱ�洢����ͼ
 * ֻ��������߽ṹ��info v_head arc_head�����ֶΣ��ֱ�����ڽӱ�����ʾ�ı�
 * ����Ϣ����һ��������ͼ�е�λ�ã���һ���ߡ���ṹֻʹ��data arc_first_out��
 * ���ֶα�ʾ�����Ϣ����һ�����Ըö���Ϊβ�ģ��ߡ�
 * �ڽӱ������ͼͬһ����Ҫ�б�ʾΪ��������V0-V1��Ҫ��ʾΪArc0_1/Arc1_0��������
 * ����Ϊ����V0�ı������еĽڵ��V1�ı������еĽڵ㡣
 * �綥��V1����V1�йصı��� V1-V0 V1-V3 V1-V4
 * ���ڽӱ��ʾΪ��G->v_list[0]->arc_first_in = Arc1_0;1��Arc1_0����һ��������0��
 * ����Arc1_0->v_head = 0;1����һ������Arc1_3������Arc1_0->arc_head = Arc1_3;
 * �������ƣ�Arc1_3->v_head = 3;Arc1_3->arc_head = Arc1_4;Arc1_4->v_head=4;
 * Arc1_4->arc_head = NULL;�Ӷ��γ�һ������V1�ıߵ�����
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
    
    //��͵�����
    V0 = CreateVertexNode(); V1 = CreateVertexNode();
    V2 = CreateVertexNode(); V3 = CreateVertexNode();
    V4 = CreateVertexNode(); V5 = CreateVertexNode();
    V6 = CreateVertexNode(); V7 = CreateVertexNode();
    V0_data = CreateVertexDataNode(0,SHOP,123.52,175.21,"���ָ�����","֣�ݽ�ˮ·10��");
    V1_data = CreateVertexDataNode(1,MOVIES,103.54,123.14,"���ӰԺ","����������·67��");
    V2_data = CreateVertexDataNode(2,GARDEN,93.78,142.01,"�Ϻ���˹����԰","�Ϻ����ֶ���ϼ��·054��");
    V3_data = CreateVertexDataNode(3,PARK,41.32,75.47,"�������ŵ���ͣ����","�Ͼ��н���������·������");
    V4_data = CreateVertexDataNode(4,GOVERNMENT,124.37,154.00,"����������","�����о���·�Ϻ�������������");
    V5_data = CreateVertexDataNode(5,SCHOOL,142.01,86.32,"֣���е�����ѧ","֣����ȫ·7��");
    V6_data = CreateVertexDataNode(6,HOUSE,107.32,53.47,"�ʹ�����Ժ��","�����г�����127��");
    V7_data = CreateVertexDataNode(7,UNKNOWN,67.98,45,"���¹�����","����������");
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
    
    //��
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
    
    //ͼ
    new_undigraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_undigraph == NULL)
    { LINE_DEBUG("New Undigraph malloc failed"); goto Label_CreateOneAdjacencyListUndigraph_Clean; }
    new_undigraph->g_type = UNDIGRAPH;
    new_undigraph->v_num   = 8;
    new_undigraph->arc_num = 18;

    //��ϵ��֯
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
 * �ڽӱ��ʾ����ͼ
 * ����������ͼһ�£�ֻ�Ǳ�����ͬ����V1�㣬ֻ����V1Ϊβ����Ļ�������
 * ΪV1�ı�����Ľڵ㡣��V1�йصı���V0->V1,V1->V3,V1->V4,����ֻ��V1->V3,
 * V1->V4��ΪV1�ı�����ڵ㡣
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
    
    //��͵�����
    V0 = CreateVertexNode(); V1 = CreateVertexNode();
    V2 = CreateVertexNode(); V3 = CreateVertexNode();
    V4 = CreateVertexNode(); V5 = CreateVertexNode();
    V6 = CreateVertexNode(); V7 = CreateVertexNode();
    V0_data = CreateVertexDataNode(0,SHOP,123.52,175.21,"���ָ�����","֣�ݽ�ˮ·10��");
    V1_data = CreateVertexDataNode(1,MOVIES,103.54,123.14,"���ӰԺ","����������·67��");
    V2_data = CreateVertexDataNode(2,GARDEN,93.78,142.01,"�Ϻ���˹����԰","�Ϻ����ֶ���ϼ��·054��");
    V3_data = CreateVertexDataNode(3,PARK,41.32,75.47,"�������ŵ���ͣ����","�Ͼ��н���������·������");
    V4_data = CreateVertexDataNode(4,GOVERNMENT,124.37,154.00,"����������","�����о���·�Ϻ�������������");
    V5_data = CreateVertexDataNode(5,SCHOOL,142.01,86.32,"֣���е�����ѧ","֣����ȫ·7��");
    V6_data = CreateVertexDataNode(6,HOUSE,107.32,53.47,"�ʹ�����Ժ��","�����г�����127��");
    V7_data = CreateVertexDataNode(7,UNKNOWN,67.98,45,"���¹�����","����������");
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
    
    //��
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
    
    //ͼ
    new_digraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_digraph == NULL)
    { LINE_DEBUG("New Undigraph malloc failed"); goto Label_CreateOneAdjacencyListDigraph_Clean; }
    new_digraph->g_type = DIGRAPH;
    new_digraph->v_num   = 8;
    new_digraph->arc_num = 9;

    //��ϵ��֯
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

/* �ֹ�����һ����ͨ����ͼ
 * ����Ĵ洢�ṹΪ�ڽӶ��ر�
 * 1.�߽ڵ�
 * if_visited��ʶ�Ƿ񱻷��ʹ���v_tail��ʾ(β)�ڵ㣬v_head��ʾ(ͷ)�ڵ㣬
 * info��ʾ�ߵ���Ϣ��
 * ͼ���б� V0-V1 V0-V2 V1-V3 V1-V4 V3-V7 V4-V7 V2-V5 V5-V6 V6-V2
 * ���� V0 V1����ı�����
 *    V0      V1      ������V0��صı���Arc0_1 Arc0_2����ڵ�����0��ص��ֶ�
 *  V0-V1   V0-V1     �ֱ�Ϊ�����ߵ�v_tail��arc_tail����Arc0_1ΪV0�ĵ�һ���ߣ�
 *   |        /       ����Arc0_1->arc_tail=Arc0_2; Arc0_2->arc_tail=NULL;�γ�
 *  V0-V2   V1-V3     һ������V0��һ������
 *   |      |         ������V1��صı���Arc0_1,Arc1_3,Arc1_4����ڵ�����1��ص�
 *  NULL    V1-V4     �ֶηֱ���Arc0_1->v_head/arc_head,Arc1_3->v_tail/arc_tail,
 *          |         Arc1_4->v_tail/arc_tial����Arc0_1ΪV1�ĵ�һ���ߣ�����Arc0_1
 *          NULL      ->arc_head=Arc1_3;Arc1_3->arc_tail=Arc1_4;Arc1_4->arc_tail
 *                    =NULL;�γ��˹���V1��һ������
 *  ���ඥ�������������ơ�����ÿ������ĵ�һ���ߺ�������رߵ�ǰ��˳�����Զ���ģ�
 *  ֻҪ��֤ÿ���������γ�һ��������С��ٴζ���Ϊ������Arcs_List��
 * 2.��ڵ�
 * data��ʾ�������ݣ�arc_first_inΪ�ԸĶ���Ϊ(β)���������ĵ�һ���ߣ��Ӵ�
 * �߿�ʼ������
 * 3.�����ڽӶ��ر����ʽ��֪��ÿ���ߺ�ÿ�����㶼�ᱻ�洢���顣��һ���㵽��һ���㣬
 * ����������ķ��򣬴�һ�����һ���ߵ���������һ���ߣ��Ǻ�������͸�ķ���ÿ
 * ������ı�������൱���������Ϊ���ڵ��һ�����ӷ�֧����
 *     V0                 V1
 *    /  \              / | \
 *   V1   V2           V0 V2 V4
 * 4.������ڽӱ��ڽӶ��ر��ʡ��һ��Ŀռ䣬��һ����ֻ��ʾΪһ���͹����ˡ�
 *   ��V0����V1�ʹ�V1����V0��ͬһ���ߣ����ر�ͨ������߽ڵ��е�arc_tail��arc_head
 *   �����ֶ����ﵽ��ʡһ��ռ��Ŀ�ġ�
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
    
    //��͵�����
    V0 = CreateVertexNode(); V1 = CreateVertexNode();
    V2 = CreateVertexNode(); V3 = CreateVertexNode();
    V4 = CreateVertexNode(); V5 = CreateVertexNode();
    V6 = CreateVertexNode(); V7 = CreateVertexNode();
    V0_data = CreateVertexDataNode(0,SHOP,123.52,175.21,"���ָ�����","֣�ݽ�ˮ·10��");
    V1_data = CreateVertexDataNode(1,MOVIES,103.54,123.14,"���ӰԺ","����������·67��");
    V2_data = CreateVertexDataNode(2,GARDEN,93.78,142.01,"�Ϻ���˹����԰","�Ϻ����ֶ���ϼ��·054��");
    V3_data = CreateVertexDataNode(3,PARK,41.32,75.47,"�������ŵ���ͣ����","�Ͼ��н���������·������");
    V4_data = CreateVertexDataNode(4,GOVERNMENT,124.37,154.00,"����������","�����о���·�Ϻ�������������");
    V5_data = CreateVertexDataNode(5,SCHOOL,142.01,86.32,"֣���е�����ѧ","֣����ȫ·7��");
    V6_data = CreateVertexDataNode(6,HOUSE,107.32,53.47,"�ʹ�����Ժ��","�����г�����127��");
    V7_data = CreateVertexDataNode(7,UNKNOWN,67.98,45,"���¹�����","����������");
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
    
    //��
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
    
    //ͼ
    new_undigraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_undigraph == NULL)
    { LINE_DEBUG("New Undigraph malloc failed"); goto Label_CreateOneMultilistUndigraph_Clean; }
    new_undigraph->g_type = UNDIGRAPH;
    new_undigraph->v_num   = 8;
    new_undigraph->arc_num = 9;

    //��ϵ��֯
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

/* �ֹ�����һ������ͼ������ʹ�õ���ʮ������Ĵ洢��ʽ��
 * ������ͼһ����ֻ�Ǵ�����ȷ�ķ���V0->V1 V0->V2 V1->V3 V1->V4 V4->V7
 * V3->V7 V2->V5 V5->V6 V6->V2
 * 1.�߽ڵ㣬����������V0 V1����
 *                        V0                V1
 * V->arc_first_out -> V0 -> V1          V1 -> V3
 *                     |                 |
 *                     V0 -> V2          V1 -> V4
 *                     |                 |
 *                    NULL              NULL
 * V->arc_first_in  -> NULL              V0 -> V1     V0û����ߣ�V1ֻ��һ��
 *                                             |      ��ߡ�Arc0_1->arc_head=NULL;
 *                                             NULL
 * ʮ��������V0 V1ֱ����ص����б����ϣ���Ϊout��in���ֱߣ��ֱ��Լ�ָ��
 * ��һ��out�ߺ͵�һ��in�ߣ�Ȼ��������out/in�߽�������γ�������������
 * ���ʾһ���������е���ȱߺͳ��ȱߡ�
 * ��v_list[0]->arc_first_out=Arc0_1;Arc0_1->arc_tail = Arc0_2;
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
    
    //��͵�����
    V0 = CreateVertexNode(); V1 = CreateVertexNode();
    V2 = CreateVertexNode(); V3 = CreateVertexNode();
    V4 = CreateVertexNode(); V5 = CreateVertexNode();
    V6 = CreateVertexNode(); V7 = CreateVertexNode();
    V0_data = CreateVertexDataNode(0,SHOP,123.52,175.21,"���ָ�����","֣�ݽ�ˮ·10��");
    V1_data = CreateVertexDataNode(1,MOVIES,103.54,123.14,"���ӰԺ","����������·67��");
    V2_data = CreateVertexDataNode(2,GARDEN,93.78,142.01,"�Ϻ���˹����԰","�Ϻ����ֶ���ϼ��·054��");
    V3_data = CreateVertexDataNode(3,PARK,41.32,75.47,"�������ŵ���ͣ����","�Ͼ��н���������·������");
    V4_data = CreateVertexDataNode(4,GOVERNMENT,124.37,154.00,"����������","�����о���·�Ϻ�������������");
    V5_data = CreateVertexDataNode(5,SCHOOL,142.01,86.32,"֣���е�����ѧ","֣����ȫ·7��");
    V6_data = CreateVertexDataNode(6,HOUSE,107.32,53.47,"�ʹ�����Ժ��","�����г�����127��");
    V7_data = CreateVertexDataNode(7,UNKNOWN,67.98,45,"���¹�����","����������");
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
    
    //��
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
    
    //ͼ
    new_digraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_digraph == NULL)
    { LINE_DEBUG("New Digraph malloc failed"); goto Label_CreateOneOrthogonalListDigraph_Clean; }
    new_digraph->g_type = DIGRAPH;
    new_digraph->v_num   = 8;
    new_digraph->arc_num = 9;

    //��ϵ��֯
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

//ÿ�ε���һ��Ԫ�أ��ɲ���p����
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

//ÿ��ѹ��һ��Ԫ��
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

/*������ʱ�ʶ��true��ʾ���ʹ���false��ʾδ���ʹ�*/
bool VISITED_FLAGS[MAX_VERTEX_NUM];

/*
 * �ڽӾ������/������ȱ�������ͼ������ͼһ������
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
	    /*���뵯����v���������Ķ���(G->arc_matrix[v][i]!=NULL)�У���û�б����ʹ���ѹ����в����*/
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

/* �ڽӱ�����ͼ���/������ȱ���
 * �����ڽӱ�Ĵ洢�ṹ������������Ͼ��ǶԵ�����Ĳ����������������Ƕ���ı�����
 * ���ڽӱ���ʽ�洢������ͼ������ͼ��DFS��BFS�㷨һ����������ͼʵ����
 */
void Undigraph_AdjacencyList_DFS(P_Graphics G,V_Position s_p,V_Handle_Fun_Type v_handle)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("DFS Start Vertex is illegal"); return; }
    if(v_handle == NULL){ LINE_DEBUG("v_handle is NULL"); return; }

    v_handle(G->v_list[s_p]);
    VISITED_FLAGS[s_p] = true;
    //ע���ڽӱ���ʹ�õ���arc_first_out����ֶ�
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
 * ���ر�����ͼ��DFS����
 * G ͼָ�� s_p���ĸ��㿪ʼ���� v_handle ���㴦����������ֻ�ǰѶ�����Ϣ��ӡ����
 * 1.����������ÿ����һ���µĶ��㣬�������Դ˶���Ϊ������������������ÿ������
 * ������̽�ԵĿ�������ֱ�������Ķ����Ƿ񱻷��ʹ�����û�У���������ȥ���������һ
 * �����㱻���ʹ�������������ѡһ���ߣ�����ǹ�ȷ������͸�����迴���¢�-�ݣ�����
 * �ھ��൱�����ı����е����֧lchild���ܾ��൱��Ѱ����һ����֧���ҷ�֧rchild����
 * ��Ϊ������ֻ��������֧���������Ĵ����еı�����ʽд�������ı���������������Ϊ 
 * int i = 0; while(i < 2){ DFS(root->lchild); root->lchild = root->rchild; ++i; }
 */
void Undigraph_Multilist_DFS(P_Graphics G,V_Position s_p,V_Handle_Fun_Type v_handle)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("DFS Start Vertex is illegal"); return; }
    if(v_handle == NULL){ LINE_DEBUG("v_handle is NULL"); return; }
    //1.������
    v_handle(G->v_list[s_p]);
    VISITED_FLAGS[s_p] = true;
    //2.�ݹ����
    //��ȡ����v_list[s_p]�ı�����
    P_ArcNode arc = G->v_list[s_p]->arc_first_in;
    
    /*��ֱ���������ı����������ϣ����ö������еı߷�����ϣ���������͸��*/
    while(arc)
    {
	/*�ٻ�ȡ�����ߵ�����һ������*/
	V_Position another = (s_p == arc->v_tail) ? arc->v_head : arc->v_tail;
	/*�ڿ������ߵ���һ�������Ƿ񱻷��ʹ�*/
	if(VISITED_FLAGS[another] != true)
	{
	    /*����δ���ʹ���������������ʣ��������������*/
	    Undigraph_Multilist_DFS(G,another,v_handle);
	}
	else
	{
	    /*�������ʹ�����ͨ���������ö��������һ���ߣ�����������������һ������һ�������Ƿ񱻷��ʹ�*/
	    arc = (s_p == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	}
    }
}

/*
 * ���ر�����ͼBFS����
 * �����������������У����Ȱѿ�ʼ����ѹ����У�Ȼ��ÿ����һ������󣬾ͽ��ö�������
 * ��ֱ����ص���δ�����ʹ��Ķ���ѹ�����(ͨ��������Arc_List�ң���ΪArc_List����һ��
 * ����������رߵ�����)����û�з��������Ķ��㣬��ѹ�롣���ѭ����ֱ���������ٴ�û
 * �����ݡ�
 */
void Undigraph_Multilist_BFS(P_Graphics G,V_Position s_p,V_Handle_Fun_Type v_handle)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("BFS Start Vertex is illegal"); return; }
    if(v_handle == NULL){ LINE_DEBUG("v_handle is NULL"); return; }
    V_Position one,another;
    bool re;
    //��������
    P_Queue Q = CreateQueue();
    if(Q == NULL){ LINE_DEBUG("BFS Queue Create Failed"); return; }
    //ѹ�뿪ʼ����
    re = Push(Q,s_p); VISITED_FLAGS[s_p] = true;
    if(re == false){ LINE_DEBUG("queue push is wrong"); return; }
    //��ʼ����
    while(Q->count != 0)
    {
	//����һ������
	re = Pop(Q,&one);
	if(re == false){ LINE_DEBUG("queue pop is wrong"); return; }
	//����ö���
	v_handle(G->v_list[one]);
	//ͨ������������ѹ��ö�������ֱ�������δ�����ʹ��Ķ���
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
    //����
    SAFE_FREE(Q);
}

//ʮ����������ͼ�����/������ȱ���
void Digraph_OrthogonalList_DFS(P_Graphics G,V_Position s_p,V_Handle_Fun_Type v_handle)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("DFS Start Vertex is illegal"); return; }
    if(v_handle == NULL){ LINE_DEBUG("v_handle is NULL"); return; }
    
    v_handle(G->v_list[s_p]);
    VISITED_FLAGS[s_p] = true;

    /* ����ͼ�У��������B��һ���ߵ�ͷ�����ڱ����в�����ȥ������β����A
     * ��������ͼ�б�����ȥ����A������A�����B��˵��ʱ��Ϊβ����*/
    P_ArcNode arc = G->v_list[s_p]->arc_first_out;
    while(arc)
    {
	/*�Ա�������ͼ��������ͼһֱ���ݱߵķ�������ͷ����ķ���ǰ��*/
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

/*�ڽӾ���/�ڽӱ�/ʮ������/�ڽӶ��ر����/������ȱ�������ͼ������ͼ*/
void Graphics_Show(P_Graphics G,V_Position v_begin,SHOWMODE show_mode,STRUCTURE structure)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    if(v_begin < 0 || v_begin >= G->v_num){ LINE_DEBUG("Show Start Vertex is illegal"); return; }
    int i = 0;
    while(i < MAX_VERTEX_NUM){ VISITED_FLAGS[i] = false; ++i; }
    
    if(show_mode == DFS && structure == MULTILIST)
    {
	i = v_begin;
	/* ����ͨͼ����Ҫ������������һ����������ܵ���ĵ㶼��������Ϻ󻹴���δ�����ʵĵ㣬
	 * ��˵��ͼ�Ƿ���ͨ�ģ�������һ����δ�����ʵ���ͼ����ʱ��Ҫ����(���)ѡ��һ���㣬��
	 * ��DFS
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

/* �ͷ�ͼ
 * Ҫע���ͷŸɾ�������ͼ���ֹ�������ڴ涼Ҫ��С�����ͷŵ�
 * ��������ͷţ����Ǹ��洢�ṹ��ϵ���ܣ����̴�����ͬ����ϸ΢
 * �ĵ����������в��졣
 */
/*���ر��ͷ�*/
/* ע����ر�ߵ��ͷ�Ҫ��ɸѡ�����еĳ��ߣ�Ȼ�����ͷţ�������ܳ���
 * �ͷ���A�ĳ���Arc������Arc��ΪB��һ����ߣ���֮��ı���B�����б���
 * ������ʱ���������Ѿ��ͷŵı�ָ�룬�����δ���
 */
void MultilistFree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    int i = 0; int j = 0;
    P_ArcNode arc = NULL;
    P_ArcNode arcs[G->arc_num];
    while(i < G->v_num)
    {
	//�ͷŶ���i������
	SAFE_FREE(G->v_list[i]->data);
	//��¼�����Զ���iΪβ�ı�(����ֻ�ͷ������Զ���iΪͷ�ı�Ҳ����)
	arc = G->v_list[i]->arc_first_in;
	while(arc)
	{
	    if(i == arc->v_tail){ arcs[j] = arc; ++j; }
	    arc = (i == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	}
	//�ͷŶ���i����
	SAFE_FREE(G->v_list[i]);
	++i;
    }
    //�ͷű�
    for(i = 0; i < G->arc_num; ++i){ SAFE_FREE(arcs[i]); }
    arc = NULL; temp_arc = NULL;
    //�ͷ�ͼ
    SAFE_FREE(G);
}

//ʮ�������ͷ�
void OrthogonalListFree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    int i = 0;
    P_ArcNode arc = NULL;
    P_ArcNode temp_arc = NULL;
    while(i < G->v_num)
    {
	SAFE_FREE(G->v_list[i]->data);
	//�ͷŶ���i�����г���
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

//�ڽӱ��ͷ�
void AdjacencyListFree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    int i = 0;
    P_ArcNode arc = NULL;
    P_ArcNode temp_arc = NULL;
    while(i < G->v_num)
    {
	SAFE_FREE(G->v_list[i]->data);
	//�ͷŶ���i�����б�
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

//�ڽӾ����ͷ�
void MatrixFree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Graphics is NULL"); return; }
    int i = 0;
    int j;
    while(i < G->v_num)
    {
	SAFE_FREE(G->v_list[i]->data);
	j = 0;
	//�ͷ����еı�
	while(j < G->v_num)
	{
	    if(G->arc_matrix[i][j] != NULL)
	    {
		SAFE_FREE(G->arc_matrix[i][j]);
		/* ��j������iλ������¼��ͬһ���ߵĵط��ÿգ���ֹ���ʵ�
		 * j�����iλ��ʱ�ظ��ͷ�
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
    //ͼ�ı�����ʾ����ѡ����ʼ�ڵ��DFS or BFS
    printf("---------------------�ڽӶ��ر�-----------------------\n");
    P_Graphics Multilist_Undigraph = CreateOneMultilistUndigraph();
    if(Multilist_Undigraph == NULL){ LINE_DEBUG("Multilist_Undigraph Create failed"); return -1; }
    Graphics_Show(Multilist_Undigraph,0,DFS,MULTILIST);
    printf("---------------------ʮ������-----------------------\n");
    P_Graphics OrthogonalList_Digraph = CreateOneOrthogonalListDigraph();
    if(OrthogonalList_Digraph == NULL){ LINE_DEBUG("OrthogonalList_Digraph Create failed"); return -1; }
    Graphics_Show(OrthogonalList_Digraph,0,DFS,ORTHOGONALLSIT);
    printf("--------------------�ڽӱ�����ͼ-----------------------\n");
    P_Graphics AdjacencyList_Undigraph = CreateOneAdjacencyListUndigraph();
    if(AdjacencyList_Undigraph == NULL){ LINE_DEBUG("AdjacencyList_Undigraph Create failed"); return -1; }
    Graphics_Show(AdjacencyList_Undigraph,0,BFS,ADJACENCYLIST);
    printf("--------------------�ڽӾ��������ͼ-----------------------\n");
    P_Graphics Matrix_Undigraph = CreateOneMatrixUndigraph();
    if(Matrix_Undigraph == NULL){ LINE_DEBUG("Matrix_Undigraph Create failed"); return -1; }
    Graphics_Show(Matrix_Undigraph,0,BFS,MATRIX);
    
    //������
    GraphicsFree(Multilist_Undigraph,MULTILIST);
    GraphicsFree(OrthogonalList_Digraph,ORTHOGONALLSIT);
    GraphicsFree(AdjacencyList_Undigraph,ADJACENCYLIST);
    GraphicsFree(Matrix_Undigraph,MATRIX);

    return 0;
}
