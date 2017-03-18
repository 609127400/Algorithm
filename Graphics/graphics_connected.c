/*
 *                                  ͼ����ͨ������
 * 1.��Ҫ��(��С)���������ؽڵ������ͨ�������⡣���������ͼ���ö��ر�洢��
 * 2.��С������
 *   �� ��Դ�Ȩֵ����ͨͼ������ͨͼ���Էֱ��������ͨ��ͼ����С����������С����
 *   ����Minimum Cost Splanning Tree������С��������ͨ����С��·�����ĵ���ͼ�е�
 *   ���ж��㡣һ��Ӧ��������ͼ�У�����ͼ��Ҳ����С�������������㷨�����ӡ�
 *   �� ͼ���������Ļ����������裺��DFS�У�ÿ�ε�������һ�����������ӵݹ鵽�����
 *   ���ؿ�ʼ������Ҷ�ڵ㿪ʼ������ÿ�����һ��һ�������ݣ����Ͻ��������ĸ��ڵ���
 *   Ϊ�µĸ��ڵ���ӽڵ����Ӳ��������ĸ��ڵ㼴�ɡ���BFS�У����Ǵ������¹�������
 *   ���̣�ѭ���У����������ĵ�һ��Ԫ����Ϊ���ڵ㣬֮��ÿ��Ҫ������Ԫ����ΪҪѹ
 *   ���Ԫ�صĸ��ڵ�������Ӽ��ɡ���Ҫע�⴦��ľ�������ͼ�ж������ķ�֧���Լ�
 *   ���Ĵ洢�ṹ��
 *   �� ��С������������ͼ��V�������n-1�����ұ�֤��Щ�ߵ�Ȩֵ����С�����õ���Prim
 *   �㷨��Kruskal�㷨���㷨��������Ȩ����ȵ�����ѡһ�����ɡ�
 *   Prim�㷨������һ��ͼ���µĿյĶ��㼯Vnew��Ȼ�������ʼ���㡣Ȼ��ʼ������С
 *   ��������ɨ��������Vnew�����ж�������бߣ��ҳ�Ȩֵ��С��һ���ߣ��������ߵ���
 *   һ���������Vnew�в���Ǽ�¼�����ߡ�Ȼ���ظ�ɨ��/Ѱ��Ȩֵ��С�ı�/���붥�㵽
 *   Vnew��ֱ��Vnew������ͼ�е����ж��㡣�������С������Ҳ��һ��һ���γɵģ���ÿ
 *   ��ѭ���������һ�������һ���ߵ���С�������ϣ�ͼ��n�����㣬���ѭ�����n-1�Ρ�
 *   �ɴ˿�֪Prim�㷨��n������أ�Ϊn��2�η�������ڳ���ͼ���㷨����Ч�ʽϸߡ�
 *   Kruskal�㷨������һ����ͼGnew����ʼֻ��ԭͼ�����ж����û�бߡ�ÿ�δ�ԭͼ����
 *   �ı���ѡȡһ��Ȩֵ��С�ģ����˱߲��ᵼ����ͼ���еı��γɻ����򽫴˱߼���Gnew��
 *   ֱ��Gnew���ж��㶼��ͨ����ʽ�ϣ�Kruskal�㷨���ڴ����ʼ״̬��Ϊ���ڵ������ɭ
 *   �֣�ÿ����һ���ߣ����ǽ���������Ϊһ������ֱ���������е����ں�Ϊһ���������
 *   �㷨��ͼ�ı���������أ�Ϊelog(e)��eΪͼ�ı���������ʺ�ϡ��ͼ��
 * 3.�ؽڵ������ͨ����
 *   �� �ؽڵ㣺��ɾ��ͼG�е�ĳһ����v��������v�����бߺ�G����ͨ��Ϊ����ͨ����v��
 *   Ϊ�ؽڵ㡣һ��û�йؽڵ��ͼ��������ͨͼ��˫��ͨͼbiconnected graph��������ɾ
 *   ��k���ڵ��G�Ż�ʧȥ��ͨ�ԣ����G����ͨ��Ϊk�����ߣ�ͨ���������㣬�ؼ�Ԫ����
 *   ·����һ������ͨ�ȡ���֮��GΪ������ͨͼ��Ҫ�ƻ�G����ͨ�ԣ�ֻҪ�ƻ��ؽڵ㼴�ɡ�
 *   �� �ؽڵ�����ԣ���ͼG���������������T�У�(1)T�ĸ��ڵ�R����>=2���ķ�֧����Rһ
 *   ���ǹؽڵ㣬��֮���ǡ�(2) ������Ҷ����v(Ҷ����һ�����ǹؽڵ�)ֻҪ�����ӷ�֧(��
 *   ��)�����ӷ�֧�в�����ĳ��������v�����ȵı���(���γɵĻ�)���������vһ���ǹؽ�
 *   �㡣��֮˵��v���ӷ�֧�е�һ������������v��һ���������γɵĻ�����ɾ��v��������v
 *   �ıߺ�v����ָ������ȶ�������ӷ�֧���㣬��Ϊv���ӷ�֧�еĶ��㻹������G��ͨ
 *   ��������v����������ͨ���磺A-B-C��ͬʱ����A-C��������DFS��������A-C����һ����
 *   �ߡ�A��B�����ȣ�B��C�����ȣ�B��ͨ��A��C����ɾ��B��C��Ϊ��һ������B������A��
 *   ���ߣ���Ȼ����ά����ͨ�ԣ����B�Ͳ��ǹؽڵ��ˡ�
 *   �� ʵ�ַ�������DFS�����У���ÿ�����ʵĶ�����С�����ţ�ּ����ȷ˭��(��������)
 *   �ȱ����������ȣ�˭�Ǻ�������ĺ�����ڱ�����ͬʱ�����ÿ���������С����ֵ����
 *   ��С����ֵ�ļ��㷽���漰����ֵ��1.v����Ĵ���ֵ 2.v����(����)v����С�������ȵ�
 *   ����ֵ 3.v�ĺ��������(����)v����С�������ȵĴ���ֵN��������ֵȡ��С��һ����Ϊ
 *   ����v����С����ֵ��Ȼ����v��ֱ�Ӻ��w����С����ֵ < v����Ĵ���ֵ��˵��w��w�ĺ�
 *   ���д�������v�����ȵı���ߣ�Ҳ��v���ǹؼ��ڵ㡣��֮����w����С����ֵ >= v����
 *   �Ĵ���ֵ����v�������ӷ�֧����˵��v�ǹؽڵ㡣
 *   �� �ؽڵ����ʵ�ֵķ�������������DFS��������ͼ���Ƿ��л����ڣ�ֻ������ָ������
 *   ��������ǰ���ʽڵ�v�����ȵĻ�������ɲο�graphics_dag 3 (3) ���֡�
 *
 *
 *
 *
 *                                                     2016��11��28��
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

typedef int V_Position;   /*����λ��*/
typedef int Power;        /*��Ȩֵ������Ȩֵ������ MAX_POWER*/
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
    bool mark;
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
    new_arc->mark = false; new_arc->info = info;
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
    char name[MAX_GRAPHICS_NAME_LEN];
    G_Type g_type;
    P_VertexNode v_list[MAX_VERTEX_NUM];
    int v_num; int arc_num;
}Graphics, *P_Graphics;

/*
 * ����ͼ1 ��С������ʹ��
 *        0
 *       /|\            Ȩֵ��0-1 20  0-2 10  0-3 18
 *      / | \                 1-2 15  2-3 5   1-4 30
 *     /  |  \                2-4 1   2-5 10  3-5 5
 *    1---2---3               4-5 25
 *     \ / \ /
 *      4---5
 */
P_Graphics CreateUndigraphOne()
{
    //���������ݣ�����Ϣ���㣬�ߣ�ͼ
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
    //��������Ϣ
    info0_1 = CreateOneArcInfo(20,"V0-V1"); info0_2 = CreateOneArcInfo(10,"V0->V2");
    info0_3 = CreateOneArcInfo(18,"V0-V3"); info1_2 = CreateOneArcInfo(15,"V1-V2");
    info2_3 = CreateOneArcInfo(5,"V2-V3");  info1_4 = CreateOneArcInfo(30,"V1-V4");
    info2_4 = CreateOneArcInfo(1,"V2-V4");  info2_5 = CreateOneArcInfo(10,"V2-V5");
    info3_5 = CreateOneArcInfo(5,"V3-V5");  info4_5 = CreateOneArcInfo(25,"V4-V5");
    if(info0_1 == NULL || info0_2 == NULL || info0_3 == NULL || info1_2 == NULL
    || info2_3 == NULL || info1_4 == NULL || info2_4 == NULL || info2_5 == NULL
    || info3_5 == NULL || info4_5 == NULL)
    { LINE_DEBUG("ArcInfo Create failed"); goto Label_CreateUndigraphOne_Clean; }
    //������
    Arc0_1 = CreateOneArc(info0_1); Arc0_2 = CreateOneArc(info0_2);
    Arc0_3 = CreateOneArc(info0_3); Arc1_2 = CreateOneArc(info1_2);
    Arc2_3 = CreateOneArc(info2_3); Arc1_4 = CreateOneArc(info1_4);
    Arc2_4 = CreateOneArc(info2_4); Arc2_5 = CreateOneArc(info2_5);
    Arc3_5 = CreateOneArc(info3_5); Arc4_5 = CreateOneArc(info4_5);
    if(Arc0_1 == NULL || Arc0_2  == NULL || Arc0_3 == NULL || Arc1_2  == NULL
    || Arc2_3 == NULL || Arc1_4  == NULL || Arc2_4 == NULL || Arc2_5 == NULL
    || Arc3_5 == NULL || Arc4_5  == NULL)
    { LINE_DEBUG("ArcNode Create failed"); goto Label_CreateUndigraphOne_Clean; }
    //����������
    data0 = CreateOneVertexData(0,"V0","��ַ0"); data1 = CreateOneVertexData(1,"V1","��ַ1"); 
    data2 = CreateOneVertexData(2,"V2","��ַ2"); data3 = CreateOneVertexData(3,"V3","��ַ3");
    data4 = CreateOneVertexData(4,"V4","��ַ4"); data5 = CreateOneVertexData(5,"V5","��ַ5");
    if(data0 == NULL || data1 == NULL || data2 == NULL || data3 == NULL || data4 == NULL || data5 == NULL)
    { LINE_DEBUG("VertexData Create failed"); goto Label_CreateUndigraphOne_Clean; }
    //������
    V0 = CreateOneVertex(data0); V1 = CreateOneVertex(data1); V2 = CreateOneVertex(data2);
    V3 = CreateOneVertex(data3); V4 = CreateOneVertex(data4); V5 = CreateOneVertex(data5);
    if(V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL || V4 == NULL || V5 == NULL)
    { LINE_DEBUG("Vertex Create failed"); goto Label_CreateUndigraphOne_Clean; }
    //����ͼ
    new_undigraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_undigraph == NULL){ LINE_DEBUG("Graphics malloc failed"); goto Label_CreateUndigraphOne_Clean; }
    
    //��ϵ��֯
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
    strncpy(new_undigraph->name,"����μ�Ȩ��ͨ����ͼ����С������",MAX_GRAPHICS_NAME_LEN);
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

/*  ����ͼ2 ���ؽڵ����ʹ��
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
    
    //����������
    data0 = CreateOneVertexData(0,"V0","V0��ַ"); data1 = CreateOneVertexData(1,"V1","V1��ַ"); data2 = CreateOneVertexData(2,"V2","V2��ַ");
    data3 = CreateOneVertexData(3,"V3","V3��ַ"); data4 = CreateOneVertexData(4,"V4","V4��ַ"); data5 = CreateOneVertexData(5,"V5","V5��ַ");
    data6 = CreateOneVertexData(6,"V6","V6��ַ"); data7 = CreateOneVertexData(7,"V7","V7��ַ"); data8 = CreateOneVertexData(8,"V8","V8��ַ");
    data9 = CreateOneVertexData(9,"V9","V9��ַ");
    if(data0 == NULL || data1 == NULL || data2 == NULL || data3 == NULL || data4 == NULL
    || data5 == NULL || data6 == NULL || data7 == NULL || data8 == NULL || data9 == NULL)
    { LINE_DEBUG("Vertex Data Create failed"); goto Label_CreateUndigraphTwo_Clean; }
    //������
    V0 = CreateOneVertex(data0); V1 = CreateOneVertex(data1); V2 = CreateOneVertex(data2);
    V3 = CreateOneVertex(data3); V4 = CreateOneVertex(data4); V5 = CreateOneVertex(data5);
    V6 = CreateOneVertex(data6); V7 = CreateOneVertex(data7); V8 = CreateOneVertex(data8);
    V9 = CreateOneVertex(data9);
    if(V0 == NULL || V1 == NULL || V2 == NULL || V3 == NULL || V4 == NULL
    || V5 == NULL || V6 == NULL || V7 == NULL || V8 == NULL || V9 == NULL)
    { LINE_DEBUG("Vertex Create failed"); goto Label_CreateUndigraphTwo_Clean; }
    //��������Ϣ
    info0_1 = CreateOneArcInfo(6,"V0-V1"); info1_2 = CreateOneArcInfo(7,"V1-V2"); info1_3 = CreateOneArcInfo(12,"V1-V3");
    info2_4 = CreateOneArcInfo(3,"V2-V4"); info3_4 = CreateOneArcInfo(8,"V3-V4"); info3_5 = CreateOneArcInfo(17,"V3-V5");
    info5_6 = CreateOneArcInfo(7,"V5-V6"); info5_7 = CreateOneArcInfo(10,"V5-V7"); info6_7 = CreateOneArcInfo(9,"V6-V7");
    info7_8 = CreateOneArcInfo(5,"V7-V8"); info7_9 = CreateOneArcInfo(2,"V7-V9");
    if(info0_1 == NULL || info1_2 == NULL || info1_3 == NULL || info2_4 == NULL || info3_4 == NULL || info3_5 == NULL
    || info5_6 == NULL || info5_7 == NULL || info6_7 == NULL || info7_8 == NULL || info7_9 == NULL)
    { LINE_DEBUG("ArcInfo Create failed"); goto Label_CreateUndigraphTwo_Clean; }
    //������
    Arc0_1 = CreateOneArc(info0_1); Arc1_2 = CreateOneArc(info1_2); Arc1_3 = CreateOneArc(info1_3);
    Arc2_4 = CreateOneArc(info2_4); Arc3_4 = CreateOneArc(info3_4); Arc3_5 = CreateOneArc(info3_5);
    Arc5_6 = CreateOneArc(info5_6); Arc5_7 = CreateOneArc(info5_7); Arc6_7 = CreateOneArc(info6_7);
    Arc7_8 = CreateOneArc(info7_8); Arc7_9 = CreateOneArc(info7_9);
    if(Arc0_1 == NULL || Arc1_2 == NULL || Arc1_3 == NULL || Arc2_4 == NULL || Arc3_4 == NULL || Arc3_5 == NULL
    || Arc5_6 == NULL || Arc5_7 == NULL || Arc6_7 == NULL || Arc7_8 == NULL || Arc7_9 == NULL )
    { LINE_DEBUG("Arc Create failed"); goto Label_CreateUndigraphTwo_Clean; }
    //����ͼ
    new_undigraph = (P_Graphics)malloc(sizeof(Graphics));
    if(new_undigraph == NULL){ LINE_DEBUG("Graphics malloc failed"); goto Label_CreateUndigraphTwo_Clean; }

    //��ϵ��֯
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
    strncpy(new_undigraph->name,"����ͼ2����Ѱ�ؽڵ�",MAX_GRAPHICS_NAME_LEN);
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

/*��������*/
/*��ʶ�Ѿ�����Vnew�еĶ���*/
bool V_NEW[MAX_VERTEX_NUM];
/*��ŵ���С��������·������С������·����Զ�ȶ�������1*/
P_ArcNode MIN_ARCS[MAX_VERTEX_NUM];

/*
 * Prim������С������
 * ���ﲢ���������ɣ�������ԭͼ�ж��������С�������ı߽���mark��ǣ�
 * false��ʾδ��ǣ�true��ʾ�ѱ��
 */
bool Graphics_Prim_MinCostTree(P_Graphics G,V_Position s_p)
{
    if(G == NULL){ LINE_DEBUG("Graphics_Prim_MinCostTree G is NULL"); return false; }
    if(s_p < 0 || s_p >= G->v_num){ LINE_DEBUG("Graphics_Prim_MinCostTree s_p is illegal"); return false; }
    int i; P_ArcNode arc = NULL; V_Position next_v;
    for(i = 0; i < G->v_num; ++i){ V_NEW[i] = false; MIN_ARCS[i] = NULL; }
    int v_marked = 0;
    /*������ʼ����*/
    V_NEW[s_p] = true;
    /*����һ���Աȵĳ�ʼֵ����ֵӦȷ����ͼ�����е�Ȩֵ����MinArc����洢��СȨֵ�ı�*/
    ArcInfo mininfo; mininfo.power = MAX_MORE_POWER;
    ArcNode minarc; minarc.info = &mininfo;
    P_ArcNode MinArc = NULL;
    /*ѭ��v_num-1�λ�ȡv_num-1����*/
    for(i = 1; i < G->v_num; ++i)
    {
	/*���öԱ�ֵ*/
	MinArc = &minarc;
	/*������������Vnew���е����ж���ı���ȡ��Ȩֵ��С��һ��*/
	for(v_marked = 0; v_marked < G->v_num; ++v_marked)
	{
	    if(V_NEW[v_marked] == false){ continue; }
	    arc = G->v_list[v_marked]->arc_first_out;
	    while(arc)
	    {
		next_v = (v_marked == arc->v_tail) ? arc->v_head : arc->v_tail;
		/*�ڲ���Vnew�еĶ����У������ǰ���ʵı߱����е�MinArc��С�������MinArc*/
		if(V_NEW[next_v] == false)
		{ if(arc->info->power < MinArc->info->power){ MinArc = arc; } }
		arc = (v_marked == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	    }
	}
	/*�������С�ı���V_NEW���ĸ����㷢���ģ����Ըɴ඼��trueһ��*/
	V_NEW[MinArc->v_tail] = true;
	V_NEW[MinArc->v_head] = true;
	/*���ÿ����С�ߣ�Ҳ�ɾʹ˴洢ÿ�����γ�һ����ͼ*/
	MinArc->mark = true;
	MIN_ARCS[i-1] = MinArc;
    }
    return true;
}

/*
 * Kruskal������С������
 * ����Ĵ��������Ƚ��߰�Ȩֵ��arcs�д�С��������Ȼ�����
 * arcs����V_NEW���ݽ��и����������еı߽��н��ɻ������ı�ǡ�
 */
bool Graphics_Kruskal_MinCostTree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Graphics_Prim_MinCostTree G is NULL"); return false; }
    P_ArcNode arcs[G->arc_num];
    P_ArcNode arc = NULL; P_ArcNode temp_arc = NULL;
    int i = 0; int j = 0;
    for(i = 0; i < G->arc_num; ++i){ arcs[i] = NULL; }
    for(i = 0; i < G->v_num; ++i){ V_NEW[i] = false; MIN_ARCS[i] = NULL; }
    //�����г�������arcs�����У���ֹ���ظ�
    for(i = 0; i < G->v_num; ++i)
    {
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    if(i == arc->v_tail){ arcs[j] = arc; ++j; }
	    arc = (i == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	}
    }
    //��������
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
    //������
    for(i = 0; i < G->arc_num; ++i)
    { printf("%s power = %d\n",arcs[i]->info->name,arcs[i]->info->power); }
     */
    /*����arcs��ѡȡ��С�������ıߣ���ʶmark�ֶΣ�true������ܣ�false�������*/
    j = 0;
    for(i = 0; i < G->arc_num; ++i)
    {
	/*��������ߵ��������㲻ͬʱ���Ѿ�����ǣ�
	 *��˵�������߲��ᵼ��Gnew�����еı��γɻ�����¼������*/
	if(!(V_NEW[arcs[i]->v_tail] == true && V_NEW[arcs[i]->v_head] == true))
	{
	    arcs[i]->mark = true;
	    MIN_ARCS[j] = arcs[i]; j++;
	    //��Ǳߵ���������
	    V_NEW[arcs[i]->v_tail] = true; V_NEW[arcs[i]->v_head] = true;
	}
    }
}

void Graphics_ShowMinCostTree(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Graphics_ShowMinCostTree G is NULL"); return; }
    int i = 0; int all_cost = 0;
    printf("%s---��С������\n",G->name);
    for(i = 0; i < G->v_num - 1; ++i)
    {
	printf("%s power = %d\n",MIN_ARCS[i]->info->name,MIN_ARCS[i]->info->power);
	all_cost += MIN_ARCS[i]->info->power;
    }
    printf("Ȩֵ���ƣ�%d\n",all_cost);
}

/*�ؽڵ���Ѱ��������ͱ���
 * ȫ�ֵ�����ͱ������ڶ��߳������׳���
 * V_SEQUENCE_NUM �洢��������Ĵ���ֵ����ʼΪ0����ʾδ���ʣ�����ֵ��1��ʼ��
 * ���ֵΪ������ֵ
 * V_MIN_SEQUENCE_NUM �洢������С����ֵ*/
int V_SEQUENCE_NUM[MAX_VERTEX_NUM];
int V_MIN_SEQUENCE_NUM[MAX_VERTEX_NUM];
/*�����*/
static int sequence_num = 1;

/*����DFS�ڸ��������б�����ж���Ĵ���ֵ����С����ֵ
 * ����  G��ͼ    s_p������λ��
 * ����ֵ ���ص�ǰ����s_p��С�Ĵ���ֵ*/
int Graphics_DFS_ArticulationPoints(P_Graphics G,V_Position s_p)
{
    /*��һ�����ֵ��s_p����Ĵ����*/
    V_SEQUENCE_NUM[s_p] = sequence_num;
    ++sequence_num;
    
    /*�洢s_p��С�Ĵ���ֵ*/
    int min_sequence = V_SEQUENCE_NUM[s_p];
    /*�洢���ص�s_p�������С����ֵ*/
    int re_min_sequence = MAX_MORE_VERTEX_NUM;

    P_ArcNode arc = G->v_list[s_p]->arc_first_out;
    V_Position another_v;
    while(arc)
    {
	another_v = (s_p == arc->v_tail) ? arc->v_head : arc->v_tail;
	
	/*�ڶ������ֵ��s_p���ڵ����С�����ֵ*/
	if(V_SEQUENCE_NUM[another_v] != 0 && V_SEQUENCE_NUM[another_v] < min_sequence)
	{ min_sequence = V_SEQUENCE_NUM[another_v]; }
	if(V_SEQUENCE_NUM[another_v] == 0)
	{
	    /*����������ıߣ�����Ϊ���ڵ��ж��ٸ���֧��׼��*/
	    arc->mark = true;
	    re_min_sequence = Graphics_DFS_ArticulationPoints(G,another_v);
	    /*���������ֵ��s_p�������С�����ֵ*/
	    if(re_min_sequence < min_sequence)
	    { min_sequence = re_min_sequence; }
	    /*
	    //������÷���ֵ����ֱ����V_MIN_SEQUENCE_NUM[another_v]��ȡ�����С�����ֵ
	    //����Ч�ʸ���
	    if(V_MIN_SEQUENCE_NUM[another_v] < min_sequence)
	    { min_sequence = V_MIN_SEQUENCE_NUM[another_v]; }
	    */
	}

	arc = (s_p == arc->v_tail) ? arc->arc_tail : arc->arc_head;
    }
    /*����С����ֵ��s_p*/
    V_MIN_SEQUENCE_NUM[s_p] = min_sequence;
    return min_sequence;
}

/*
 *������G ͼ   s_p ��ʼ��������ʼ���� sequence_num����ֵ��ʼֵ�����ﶨΪ1*/
void Graphics_ArticulationPoints(P_Graphics G,V_Position s_p)
{
    if(G == NULL){ LINE_DEBUG("Graphics_ArticulationPoints G is NULL"); return; }
    int i = 0;
    for(i = 0; i < G->v_num; ++i){ V_SEQUENCE_NUM[i] = 0; V_MIN_SEQUENCE_NUM[i] = 0; }
    /*����DFS�ڸ��������б�����ж���Ĵ���ֵ����С����ֵ*/
    Graphics_DFS_ArticulationPoints(G,s_p);
    /*
    //��ʾDFS��ʶ���
    for(i = 0; i < G->v_num; ++i)
    {
	printf("%s SequenceNum = %d, Min_SequenceNum =%d \n",
		G->v_list[i]->data->name,V_SEQUENCE_NUM[i],V_MIN_SEQUENCE_NUM[i]);
    }
    */
    /*���������������飬����ؽڵ�
     *�ж��Ƿ���v����ĺ��w����V_MIN_SEQUENCE_NUM[w] >= V_SEQUENCE_NUM[v]*/
    P_ArcNode arc = NULL;
    for(i = 0; i < G->v_num; ++i)
    {
	arc = G->v_list[i]->arc_first_out;
	//����Ǹ��ڵ�
	if(i == s_p)
	{
	    /*������ڵ��ж��ٸ���֧����>=2 ��Ϊ�ؽڵ�*/
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
	    /*Ѱ��i�ĵ�һ�����j(j���㹻�ˣ���Ϊ���j�ĺ����ĳ���ڵ���Դﵽ����С����ֵҲ�ᴫ��j)*/
	    V_Position child = -1;
	    while(arc)
	    {
		child = (i == arc->v_tail) ? arc->v_head : arc->v_tail;
		if(V_SEQUENCE_NUM[child] == (V_SEQUENCE_NUM[i] + 1)){ break; }
		arc = (i == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	    }
	    /*�ж�i�Ƿ�Ϊ�ؽڵ�*/
	    if(child >= 0)
	    {
		if(V_MIN_SEQUENCE_NUM[child] >= V_SEQUENCE_NUM[i])
		{ printf("%s ",G->v_list[i]->data->name); }
	    }
	}
    }
}

/*����ͼ���ͷ�*/
void Graphics_Free(P_Graphics G)
{
    if(G == NULL){ LINE_DEBUG("Graphics_Free G is NULL"); return; }
    int i = 0; int j = 0; P_ArcNode arc = NULL;
    P_ArcNode arcs[G->arc_num];
    //�ͷŶ���
    for(i = 0; i < G->v_num; ++i)
    {
	SAFE_FREE(G->v_list[i]->data);
	//˳����¼���г���
	arc = G->v_list[i]->arc_first_out;
	while(arc)
	{
	    if(i == arc->v_tail)
	    { arcs[j] = arc; ++j; }
	    arc = (i == arc->v_tail) ? arc->arc_tail : arc->arc_head;
	}
	SAFE_FREE(G->v_list[i]);
    }
    //�ͷű�
    for(i = 0; i < G->arc_num; ++i)
    {
	SAFE_FREE(arcs[i]->info);
	SAFE_FREE(arcs[i]);
    }
    SAFE_FREE(G);
}

int main()
{
    //��ͼ
    P_Graphics undigraph_one = CreateUndigraphOne();
    if(undigraph_one == NULL){ LINE_DEBUG("undigraph_one create failed"); return -1; }
    /*����ͼ1������С������*/
    //Prim�㷨
    Graphics_Prim_MinCostTree(undigraph_one,5);
    Graphics_ShowMinCostTree(undigraph_one);
    //Kruskal�㷨
    Graphics_Kruskal_MinCostTree(undigraph_one);
    Graphics_ShowMinCostTree(undigraph_one);
    printf("--------------------------------------------------\n");
    /*����ͼ2�ؽڵ����Ѱ*/
    P_Graphics undigraph_two = CreateUndigraphTwo();
    if(undigraph_two == NULL){ LINE_DEBUG("undigraph_two create failed"); return -1; }
    Graphics_ArticulationPoints(undigraph_two,7);


    //������
    Graphics_Free(undigraph_one);
    Graphics_Free(undigraph_two);

    return 0;
}
