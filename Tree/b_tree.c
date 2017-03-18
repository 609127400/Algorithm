/*
 *
 *                                      B ��
 *  1.m��B��������m·��ƽ�����������൱��ÿlogm���������ϲ���һ���ڵ����γɵ�B������
 *    ������һ��B�������ڵ�����޺����ߡ�
 *    ���ޣ�������m·��֧��m-1���ؼ��롣
 *    ���ޣ������ڵ��⣬������m/2����֧��m/2-1���ؼ��룬����m/2ȡ���ޣ���5/2=3��
 *          ���ڵ�����������¿���������������֧��1���ؼ��롣
 *    ��˿�����B����֧�������޸�B����������m=5�����(3,5)�������У�(2,4)�����Ǻ��
 *    ����Ӱ�ӡ�
 *    �����ڵ㣺ÿ�������ڵ㶼�������ڵĹؼ���ͷ�֧��ɣ��ؼ��������ν�洢�����ݡ�
 *      5  10  15       ����   5  10  15 
 *    5l 5r  10r 15r         5l  10l 15l 15r
 *  2.����B����Ҷ�ڵ���ⲿ�ڵ㶼��ͳһ��ͬһ��ģ������ͳһ��B���ڶ༶�洢�ṹ��
 *    �бȽ��������Ӧ�á����ڴ�֮��Ӳ�̵�����I/O���ʡ��ּ��洢�Ļ���������ǽ�����
 *    Ҫ�Ĵ洢�ڸ���Ĵ洢���С���B���ĳ����ڵ�����Կ���ʹ�ڴ�һ�ζ�ȡ������ݣ���
 *    ������һ�㱻��������ڴ������������(I/O)���ϲ���֮�У�����������������
 *    �Ľӽ������B������������ͬһ�洢�����е��㷨����Ч�ʿ��ܲ�û������BBSTЧ�ʸߡ�
 *  3.B���ĸ߶��ǴӸ��ڵ㵽�ⲿ�ڵ��ĸ߶ȡ����ܹ���N���ؼ���ʱ�������ĸ߶Ƚ϶�����
 *    ���Խ���Ϊ1/7���ҡ�
 *  4.B����Insert����
 *    ������������m��B��Υ�������ֻ����m·��֧�Ĺ涨����Ϊ���磬��ʱ�����ڵ�ӵ��m
 *    ���ؼ��롣����������������ʹ֮�ָ�B�����ʣ���Ϊ���ѡ�
 *    ���ѹ���������ĳ����ڵ�Ϊ K1,K2...Km,ȡ�����ڵ�ؼ������λ������λ��m/2(ȡ
 *    ���ޣ���5/2=2)��λ��s�Ĺؼ���Ks���ɴ˳����ڵ㱻��Ϊ�����֣����K1,K2...Ks-1,��
 *    ���Ks���ұߵ�Ks+1,Ks+1...Km����Ks����һ�㣬�����丸�����ڵ���������󲿷���
 *    ΪKs�����ӽڵ㣬�Ҳ�����ΪKs�����ӽڵ㡣
 *    �磺
 *    һ��5��B����һ�������ڵ�ԭΪ 2 6 8 9���ֲ���һ��5��Ϊ 2 5 6 8 9���������λ��
 *    ��λ��6����һ�㣬�����丸�ڵ����2 5 ��Ϊ6�����ӽڵ㣬8 9 ��Ϊ6�����ӽڵ㡣
 *    
 *    ������ӽڵ㣬�ӽڵ㷢�����磬���ӽڵ���Ѳ���������Ҳ���������ڵ�����磬ֻҪ��
 *    ��ͬ�������ɣ�ֱ��������ڵ㡣���ڵ�����磬ͬ������λ��Ks��������ʱ��λ����Ϊ
 *    B���µĸ���ֻ��������֧��Ҳ���ڸ���������ʱ��B���ĸ߶ȲŻ�����һ�㡣
 *  5.B����Delete����
 *    ����ͬ����������һ����B����ɾ������ɾ���Ĺؼ�����Ҷ�ڵ��еģ���ֱ��ɾ���ؼ��뼰
 *    ��Ӧ���ӵ��ⲿ�ڵ㣬������ǣ���Ҫ��������Max��Min�ؼ�������滻��Ȼ��ɾ�����
 *    ��̵Ĺؼ��뼰�ⲿ���ӡ�
 *    ������ֱ��ɾ�����Ǽ��ɾ�������ᵼ�³����ڵ��ƻ�B����֧�����ޣ���Ϊ���磬��ʱ���
 *    �����ڵ����m/2-1����֧��m/2-2���ؼ��롣����������������ʹ֮�ָ�B�����ʣ������ַ�
 *    ��������ͺϲ��������Ƚ��н������(�������)����û�н���������ٽ��кϲ���
 *    (1) �����������������Ľڵ����ڵĵ����ֵܽڵ�����ֵܽڵ�ӵ������m/2���ؼ��룬
 *    ������Խ��һ������ʣ��m/2-1���ؼ������Υ��B�������ʣ������ͨ�����ֵܽ������
 *    �����硣����Ҫ��֤������ ��<��<�ң���������ڵ�����ֵܽڵ����������������Ĺ���
 *    �����ӽڵ��max�ؼ��������ڵ��滻��Ӧ���ؼ��룬���ӽڵ㽫���ڵ��ж�Ӧ�ĸ��ؼ�
 *    ������ֲ����硣��ʱע����뵽����ڵ�ĸ��ؼ�������ӽڵ�ҪΪNIL_Sentry��ʹ����
 *    �ڵ�Ĺؼ������ﵽ��С��m/2-1�������ȥ�Ĺؼ����Ӧ��childsҪ��������ڵ㴦��
 *    (2) �ϲ���������������Ľڵ�û���ֵܽڵ�����ֵܽڵ��Ѵﵽ���ޣ�ֻ��m/2-1����
 *    ���룬���ʱ��Ҫ���кϲ������������ӽڵ��0����m/2-1���ؼ��롢���ڵ�ĸ��ؼ��롢
 *    ���ӽڵ��m/2-2���ؼ���ϲ���һ������m/2-1 + 1 + m/2-2 = m-2��0 + 1 + m/2-2 = m/2-1
 *    ���ؼ���ĳ����ڵ㣬ʹ���µĳ����ڵ�Ĺؼ��벻�ᳬ�������ޡ�
 *    �ϲ������൱�ڴӸ��ڵ�ɾ����һ���ؼ��룬���ʹ���ڵ�ͬ����������Ŀ��ܣ����ˣ���
 *    ��ͬ�����ɣ�ֱ�����ڵ㣬ͨ���ϲ��γ��µĸ������ĸ߶Ƚ���һ�㡣
 *
 *
 *
 *
 *
 *
 *
 *
 *                                                            2016��10��31��
 *
 *
 *
 *
 *
 */


#define _DEBUG_CLOSE_
#include "../PublicForAlgorithms.h"

//����B���Ľ�
#define M 5
#define KEYS_NUM (M-1)
//����B���ؼ���������ޣ��ؼ����ֱ��һ��
#define KEYS_UP_LIMIT (M-1)
#define KEYS_LOW_LIMIT (((M%2)?(M/2+1):(M/2)) - 1)

typedef int ElementType;

typedef struct Node
{
    struct Node* parent;
    /* 
     * elements��childs�Ķ�Ӧ��ϵ��
     * Ѱ��ĳһ�ؼ����lchildʱ���겻�䣬rchildʱ����+1
     * ��elements[1]��lchild��childs[1],rchild��childs[1+1];
     * ��elements���Ϊ���m������Ϊ������ʱ�������㣬����
     * capacity�����ֵֻ����KEYS_NUM
     * ��Ƴ����飬���ʷ��㣬�����ڲ���ɾ���ؼ���ʱ���鷳����
     * ����Ʋ���̫������Ƴ�����֮��Ŀ����ڲ���ɾ������ʱ
     * ������
     */
    ElementType  elements[M];
    struct Node* childs[M+1];
    /*��ǰelements������element������*/
    int          capacity;
}BTNode,*P_BTNode,*B_Tree;

//B��ɭ�֣�����򵥶���5�ã�ֻ�����е�BTrees[0]
typedef struct Forest
{
    P_BTNode B_Trees[5];
    int      capacity;
}BT_Forest,*P_BT_Forest;

//�ڱ�����Ϊ���е��ⲿ�ڵ㣬��main�г�ʼ��
//ͨ��CreateBTNode���������Ľڵ㣬parent��childsĬ�϶�ָ���ڱ�
//Ҫע�⣬������Ա��Ҫ�ڱ���ֻ����Ҫ�ڱ������ַ���ѣ��䱾��
//�洢���ݣ����洢���ݣ�������һЩ�����ı�ʶ�����䴵�š�
//�ڱ���parent\childsĬ��ΪNULL��elements��capacityĬ��Ϊ0��
P_BTNode NIL_Sentry;

bool InitSentry()
{
    NIL_Sentry = (P_BTNode)malloc(sizeof(BTNode));
    if(NIL_Sentry == NULL)
    {
	return false;
    }
    int i = 0;
    while(i < KEYS_NUM)
    {
	NIL_Sentry->elements[i] = 0;
	++i;
    }
    i = 0;
    while(i < M)
    {
	NIL_Sentry->childs[i] = NULL;
	++i;
    }
    NIL_Sentry->parent = NULL;
    NIL_Sentry->capacity = 0;
    return true;
}

//����B���ڵ�
P_BTNode CreateBTNode()
{
    P_BTNode new = (P_BTNode)malloc(sizeof(BTNode));
    if(new == NULL) return NULL;
    int i = 0;
    while(i < KEYS_NUM)
    {
	new->elements[i] = 0;
	++i;
    }
    i = 0;
    while(i < M)
    {
	new->childs[i] = NIL_Sentry;
	++i;
    }
    new->parent = NIL_Sentry;
    new->capacity = 0;
    
    return new;
}

/*
 * B����Search����
 * bt B��
 * key Ҫ��ѯ�Ĺؼ���
 * ע�⣺
 * �� ���ҳɹ����ذ���key��B�������ڵ㣬����ʧ���򷵻����������һ
 * �������ڵ㣬�Ը���Insert��Delete������
 * �� ��������ۺ��������ǻ���ģ���Ϊ�����ڵ��
 * �����������ڴ��еģ��ٶȺܿ죬����������������һ�鷢��key����B��
 * ����Ҫ���ٱ���һ��ȥѰ��Ҫ����ĵ㡣
 * �� �������ڱ���������ʶ���ҽ����������ʧ�ܷ��ص�last_super_node��
 * ���ڱ���capacity��Ϊ-1�����ɹ��򱣳��ڱ��ĳ�ʼ��ֵ0���䡣�����
 * �ڱ��ĳ�ʼ��ֵ�й������ж���Ϻ�ʱ���ڱ���š�
 * �� ������ƿ��ܴ��ڵ����⣺��Ϊ�ڱ���ȫ�ֱ���������ڶ��߳���Ӧ�û�
 * �������⡣
 *
 */

P_BTNode BT_Search(B_Tree bt,const ElementType key)
{
    if(bt == NULL)
    {
	LINE_DEBUG("Search Failed,B Tree is NULL");
	return NIL_Sentry;
    }
    
    int i;
    P_BTNode last_super_node = NIL_Sentry;
    while(bt != NIL_Sentry)
    {
	i = 0;
	//�����ڵ��ڲ�����
	while(i < bt->capacity)
	{
	    if(key == bt->elements[i])
	    {
		LINE_DEBUG("Find the Key");
		return bt;
	    }
	    /*һ�����ֵ�ǰ�����ڵ���һ����key����Ĺؼ��룬����
	     *ת���ùؼ���������ϣ�Ȼ��break�����������ӵ�
	     *����
	     */
	    else if(key < bt->elements[i])
	    {
		last_super_node = bt;
		bt = bt->childs[i];
		break;
	    }
	    ++i;
	    /*��ǰ�����ڵ��������˻�û�ҵ���key��Ĺؼ��룬��
	     *ת����ǰ�ڵ����ҵ��ӽڵ���ȥ��������
	     */
	    if(i == bt->capacity)
	    {
		last_super_node = bt;
		bt = bt->childs[i];
		break;
	    }
	}
    }

    LINE_DEBUG("Search Failed, The key is not in the B Tree");
    //�ڱ�����
    NIL_Sentry->capacity = -1;
    return last_super_node;
}

/*
 * Insert��������
 * ���ܣ��ڳ����ڵ��в���һ���ؼ��룬����childs��Ӧλ�ò���ؼ���������ӽڵ�
 * super_node Ҫ������ؼ���ĳ����ڵ�
 * key Ҫ����Ĺؼ���
 * lchild/rchild ����ؼ������ӵ����Ҷ���
 * ���ز���key������
 */

int InsertKey(P_BTNode super_node,ElementType key,P_BTNode lchild,P_BTNode rchild)
{
    if(super_node->capacity == M) return -1;
    int i = super_node->capacity;
    ElementType temp_element;
    while(i >= 1)
    {
	if(super_node->elements[i-1] > key)
	{
	    super_node->elements[i] = super_node->elements[i-1];
	    super_node->childs[i+1] = super_node->childs[i];
	}
	else
	{
	    break;
	}
	--i;
    }
    super_node->elements[i] = key;
    super_node->childs[i]   = lchild;
    super_node->childs[i+1] = rchild;
    lchild->parent = super_node;
    rchild->parent = super_node;
    ++(super_node->capacity);
    return i;
}

/*
 * B��Insert����
 * 
 * bf B��ɭ�֣�ֻ�Ե�һ��B��bf->B_Trees[0]���в���
 * key Ҫ����Ĺؼ���
 * �����޲���������Ĺ���û�е�������������Ƿ���
 * ��һ��while�С�
 *
 */

bool BT_Insert(P_BT_Forest bf,ElementType key)
{
    if(bf == NULL)
    {
	LINE_DEBUG("Insert Failed, bf is NULL");
	return false;
    }
    if(bf->B_Trees[0] == NIL_Sentry)
    {
	P_BTNode new_root = CreateBTNode();
	if(new_root == NULL)
	{
	    LINE_DEBUG("Insert Failed, malloc new root is NULL");
	    return false;
	}
	new_root->elements[0] = key;
	new_root->capacity = 1;
	bf->B_Trees[0] = new_root;
	return true;
    }

    P_BTNode re = BT_Search(bf->B_Trees[0],key);
    if(NIL_Sentry->capacity == 0)
    {
	printf("Search Success,The key has been in the B Tree\n");
	return false;
    }
    else
    {
	printf("Search Failed,BTree Last Super Node First key=%d\n",re->elements[0]);
	//�ڱ����
	NIL_Sentry->capacity = 0;
    }
    
    int i = 0;
    P_BTNode lchild = NIL_Sentry;
    P_BTNode rchild = NIL_Sentry;
    //����ڵ���м�λ�ú�ֵ
    int center_pos;
    ElementType center_element;
    /*
     * ���ߵ�����˵��key���Խ��в������
     * ѭ������������һֱ�������ڵ���ߵ�ǰ�����ڵ�����δ��������
     * ѭ�����̣���key����search���صĳ����ڵ㣬�жϸýڵ��Ƿ����磬��
     *           δ���磬��break�������磬����з��Ѳ���������Ҫ�����
     *           �����ڵ�re��Ҫ�����Ԫ��key/lchild/rchild��
     *           ��ԭ���ĸ��ڵ�re����ʱ��Ҫ�����µĸ��ڵ㲢����Ӧ������
     */

    while(re != NIL_Sentry)
    {
	InsertKey(re,key,lchild,rchild);
	if(re->capacity <= KEYS_UP_LIMIT)
	{
	    break;
	}
	//����󽫷�������,capacity == M;
	else
	{
	    LINE_DEBUG("�ڵ㷢������");
	    center_pos = M/2;
	    //���з��Ѵ���
	    //����lchild/rchild/center_element����ԭ�����ڵ��Ϊ������
	    //ԭ�ڵ���Ϊ����ӣ��Ҷ����½�
	    //������Ĵ�������ֱ�ӽض�capacity����
	    re->capacity = M/2;
	    lchild = re;
	    //��
	    center_element = re->elements[center_pos];
	    //�ұߣ������µĽڵ㣬��ԭ�ڵ��Ҳ��ֵ�elements��childs����
	    rchild = CreateBTNode();
	    i = 0; ++center_pos;
	    while(center_pos < M)
	    {
		rchild->elements[i] = re->elements[center_pos];
		rchild->childs[i]   = re->childs[center_pos];
		++(rchild->capacity);
		++i;
		++center_pos;
	    }
	    //�����������һ��childs
	    rchild->childs[i] = re->childs[center_pos];

	    //���� key �� re
	    key = center_element;
	    if(re->parent != NIL_Sentry)
	    {
		re  = re->parent;
	    }
	    //��re��rootʱ
	    else
	    {
		//���ѳ��¸�
		P_BTNode new_root = CreateBTNode();
		re = new_root;
		
		bf->B_Trees[0] = new_root;
	    }
	}
    }//while end
    
    return true;
}

/*
 * Delete��������
 * ֻ������DeleteAssist�����кϲ����ܵ�ɾ��key�㹤��
 * ɾ�������ڵ�node�Ĺؼ���key��node�ڵ���뺬�йؼ���key������
 * ���������ȷ����
 * �� ��DeleteAssist�����У���Ӧ��ĩ�ӽڵ��ĩ�ӽڵ�ֱ������ϲ����Һϲ���
 *    Ҫɾ���ĸ��ڵ��key�����һ���ͷ����һ������������¶Խڵ��elements
 *    ��childs����ʽ�ǲ�ͬ�ġ�
 * ԭ���ڵ���ӽڵ㣺
 *   10    20    30    40
 *  8/9  11/12 21/22  31/32  41/42  ɾ��node�Ĺؼ���21
 * 
 *   10    20      30       40        ���ڵ��е�30��ɾ��
 * 8/9  11/12  22/30/31/32  NIL 41/42 ����NIL����DeleteAssist����NIL�Ľڵ�
 * ���DeleteKeyɾ��30֮��
 *   10      20      40
 * 8/9    11/12  22/30/31/32  41/42
 * �����ڽڵ�ϲ���ʱ�򣬸��ؼ���ֱ�ӷ���40֮��childs���ô���֮��ֱ�Ӹ�
 * ���ұ߽ڵ��element��child
 * �� ��node�����һ���ڵ㣬��Ӧ��Ҫɾ�����ڵ��е����һ��key��
 * *   10    20    30    40
 *  8/9  11/12 21/22  31/32  41/42  ɾ��node�Ĺؼ���41
 * 
 *   10    20      30       40           ���ڵ��е�40��ɾ��
 * 8/9  11/12    21/22  31/32/40/42  NIL ����NIL����DeleteAssist����NIL�Ľڵ�
 * ���DeleteKeyɾ��40֮��
 *   10      20    30   
 * 8/9    11/12  21/22  31/32/40/42
 */

void DeleteKey(P_BTNode node,ElementType key)
{
    int i = 0;//ȷ��key��λ��
    int j = 0;
    while(i < node->capacity)
    {
	if(node->elements[i] == key) break;
	++i;
    }

    //���ɾ����key�������һ������elements��childs������Ų
    //����ɾ����key�����һ�����򲻴���ֱ��--(capacity)���൱��ɾ�����һ��key
    if(i < node->capacity-1)
    {
	j = i;
	while(j < node->capacity-1)
	{
	    node->elements[j] = node->elements[j+1];
	    if(j+2 <= node->capacity)
		node->childs[j+1] = node->childs[j+2];
	    ++j;
	}
    }
    
    --(node->capacity);
}

/*
 * DeleteAssist���ܣ�����ʵ�ʵ�ɾ���������޸����ܴ��ڵ�����
 * bf��B��ɭ�֣�ֻ�Ե�һ��B��bf->B_Trees[0]���в���
 * node����Fix�ĳ����ڵ�
 *
 */
bool DeleteAssist(P_BT_Forest bf,P_BTNode node,ElementType key)
{
    if(bf == NULL)
    {
	LINE_DEBUG("bf is NULL");
	return false;
    }
    if(bf->B_Trees[0] == NIL_Sentry)
    {
	LINE_DEBUG("b tree is NULL");
	return false;
    }
    if(node  == NIL_Sentry || node == NULL)
    {
	LINE_DEBUG("node is NULL");
	return false;
    }
    
    //����������������Զ����ﵽ����Ϊ�������ڵ��
    //����ֻ��Ҫ����ѭ����Ч����Ҳ�ɽ�����д��1
    while(node != NIL_Sentry)
    {
	DeleteKey(node,key);

	/*��ǰ����ڵ�ɾ��key֮��*/

	//���������ɾ���ϲ���ֻʣһ�����ڵ�ʱ�Żᷢ��
	//����Ľڵ��Ǹ��ڵ㣬��Ϊ���ڵ��LOW_LIMIT�����������˲�������
	if(node->parent == NIL_Sentry)
	{
	    break;
	}
	//������Ľڵ㲻�Ǹ��ڵ���elementsδ�������޵�
	else if(node->capacity >= KEYS_LOW_LIMIT)
	{
	    break;
	}
	else
	{
	    LINE_DEBUG("�ڵ㷢������");
	    //��������
	    int i = 0;
	    int j = 0;
	    P_BTNode P = node->parent;
	    P_BTNode S_l = NIL_Sentry;
	    P_BTNode S_r = NIL_Sentry;
	    //ȷ�����ؼ����λ�ã���i��ʾ��ע��������childs[i]
	    while(i <= P->capacity)
	    {
		if(P->childs[i] == node) break;
		++i;
	    }

	    /*
	     * �������
	     * �ٽ�����ᷢ������������յĹؼ���ķ�֧û�ط��Ż��߱����ǵ����⡣
	     * �ھ���Ҷ�ڵ�ĺϲ���������Ҷ�ڵ��(ֻ�����Ǿ��ϲ��ŵ�������Ҷ�ڵ��)
	     *   �������ķ�Ҷ�ڵ���A���ֵܽڵ���B����B��B��min��max�ؼ��룬B�����
	     *   �ؼ�������һ���������һ�����ߵ�һ�����ؼ���ķ�֧ҲӦ��Ӧ��һ����Ӧ
	     *   ɾȥ�����֧���ò���A�ĵ�һ���������һ��key�ķ�֧�ϡ�Ȼ���B��elements
	     *   ��childs����Ӧ����
	     * �۽������˵��ת������ͬ��ڵ㷢���ģ��������²�����ģ��Ҳ��ᷢ��ʵ��
	     *   �Ե�ɾ��
	     * �����Ҫ���ֵܽڵ�max�ؼ��븳ֵ�����ؼ��룬�Ѹ��ؼ��븳ֵ������ڵ�
	     *   elements[0],�����ҵ�childs��ֵ������ڵ�childs[0]�������ֵܽڵ�
	     *   ��max�ؼ���ɾ����
	     *   ����Ҫ���ֵܽڵ�min�ؼ��븳ֵ�����ؼ��룬�Ѹ��ؼ��븳ֵ������ڵ�
	     *   elements[capacity],�����ҵ�childs��ֵ������ڵ�childs[capacity+1]��
	     *   �����ֵܽڵ��max�ؼ���ɾ����
	     *  
	     */
	    //���
	    if(((i-1) >= 0) && (P->childs[i-1]->capacity > KEYS_LOW_LIMIT))
	    {
		S_l = P->childs[i-1];
		//�Ƴ�һ��λ�ã��������Ż��Ŀռ䣬��ΪDeleteKey�����꣬��������
		j = node->capacity;
		while(j >= 1)
		{ 
		    node->elements[j] = node->elements[j-1];
		    node->childs[j+1] = node->childs[j];
		    --j;
		}
		node->childs[j+1] = node->childs[j];
		//����node�ڵ�
		node->elements[0] = P->elements[i-1];
		node->childs[0]   = S_l->childs[S_l->capacity];
		++(node->capacity);
		//����P�����ֵܽڵ�
		P->elements[i-1]  = S_l->elements[S_l->capacity - 1];
		--(S_l->capacity);
		
		break;
	    }
	    //����
	    if(((i+1) <= P->capacity) && (P->childs[i+1]->capacity > KEYS_LOW_LIMIT))
	    {
		S_r = P->childs[i+1];
		//����node�ڵ�
		node->elements[node->capacity] = P->elements[i];
		node->childs[node->capacity + 1] = S_r->childs[0];
		++(node->capacity);
		//����P�����ֵܽڵ�
		P->elements[i] = S_r->elements[0];
		j = 0;
		while(j < S_r->capacity-1)
		{
		    S_r->elements[j] = S_r->elements[j+1];
		    S_r->childs[j]   = S_r->childs[j+1];
		    ++j;
		}
		S_r->childs[j] = S_r->childs[j+1];
		--(S_r->capacity);
		
		break;
	    }
	    /* �ϲ����������е���
	     * �ٴ���ʽ����node��Ϊ�ϲ���Ľڵ㣬parent�ڽӴ������ڵ�ʱҪ���£���
	     *   �ڵ�Ҫ�ͷŲ�����Ӧ�ĸ��ڵ��е�childs��NIL
	     * �ڸ���B���ص㣬�ϲ������ܳ������Խ��
	     * ��һ��ڵ㱻ɾ�����϶����²�ϲ�����ģ��������������ɾ��
	     * ���������Һϲ���Ҳ����������ϲ�
	     * �ݲ������Ч������node����P��ĩ�ڵ㣬�򸸹ؼ�����ҽڵ�ϲ���node����
	     *   node��P��ĩ�ڵ㣬��ϲ���S_l��P�ڵ��ڵ�ǰ������ֻ�ж�Ӧchilds������
	     *   Ҫɾ���Ĺؼ���Ҫ���´ε����н��д���
	     */
	    if(i < P->capacity)
	    {
		S_r = P->childs[i+1];
		j = 0;
		node->elements[node->capacity] = P->elements[i];
		//���븸�ؼ���,��Ӧ��childs���ô���
		++(node->capacity);
		//����S_r�ؼ����childs
		while(j < S_r->capacity)
		{
		    node->elements[node->capacity] = S_r->elements[j];
		    node->childs[node->capacity]   = S_r->childs[j];
		    ++(node->capacity);
		    ++j;
		}
		node->childs[node->capacity] = S_r->childs[j];

		SAFE_FREE(S_r);
		P->childs[i+1] = NIL_Sentry;
	    }
	    else
	    {
		S_l = P->childs[i-1];
		j = 0;
		S_l->elements[S_l->capacity] = P->elements[i-1];
		++(S_l->capacity);
		while(j < node->capacity)
		{
		    S_l->elements[S_l->capacity] = node->elements[j];
		    S_l->childs[S_l->capacity]   = node->childs[j];
		    ++(S_l->capacity);
		    ++j;
		}
		S_l->childs[S_l->capacity] = node->childs[j];

		SAFE_FREE(node);
		//ԭnode�ڵ��Ѿ���ʧ������Ҫ�����µĺϲ����node
		node = S_l;
		P->childs[i] = NIL_Sentry;
	    }

	    //�ϲ���Ľڵ�ĸ��ڵ��Ƿ��Ǹ��ڵ㣬���ǣ�����¸��ڵ㲢�ͷ�ԭ���ڵ�
	    //��ʱB���߶Ƚ���
	    //ֻ������ͨ���ϲ������ڵ�Ż���ʧ
	    if((P->parent == NIL_Sentry) && (P->capacity == 1))
	    {
		LINE_DEBUG("New Root");
		SAFE_FREE(P);
		node->parent = NIL_Sentry;
		bf->B_Trees[0] = node;
		break;
	    }

	    //����������DeleteKey
	    node = P;
	    if(i < node->capacity)
		key  = P->elements[i];
	    else
		key  = P->elements[i-1];
	}
    }//while end

    return true;
}
/*
 * B��Delete����
 * bf��B��ɭ�֣�ֻ�Ե�һ��B��bf->B_Trees[0]���в���
 * key��Ҫɾ���Ĺؼ���
 * ��Ȼ������������Сֵ�滻�ķ���
 *
 */
bool BT_Delete(P_BT_Forest bf,ElementType key)
{
    if(bf == NULL)
    {
	LINE_DEBUG("bf is NULL");
	return false;
    }
    if(bf->B_Trees[0] == NIL_Sentry)
    {
	LINE_DEBUG("b tree is NULL");
	return false;
    }

    P_BTNode re = BT_Search(bf->B_Trees[0],key);
    if(NIL_Sentry->capacity == 0)
    {
	printf("Search Success,The key has been in the B Tree\n");
    }
    else
    {
	printf("Search Failed,BTree Last Super Node First key=%d\n",re->elements[0]);
	//�ڱ����
	NIL_Sentry->capacity = 0;
	return false;
    }
    
    //�����Ҷ�ڵ㣬��ȷ������Ҫ����Ľڵ��key
    if(re->childs[0] != NIL_Sentry)
    {
	LINE_DEBUG("Find R_Child min element");
	P_BTNode temp_node = NIL_Sentry;
	int i = 0;
	while(i < re->capacity)
	{
	    if(re->elements[i] == key)
	    {
		temp_node = re->childs[i+1];
		break;
	    }
	    ++i;
	}
	while(temp_node->childs[0] != NIL_Sentry)
	{
	    temp_node = temp_node->childs[0];
	}

	//ֵ�滻����Ӧ��childs����
	re->elements[i] = temp_node->elements[0];
	key = temp_node->elements[0];
	re = temp_node;
    }

    LINE_DEBUG("key=%d",key);
    //����DeleteAssistɾ���ڵ㲢������ܷ���������
    bool result = DeleteAssist(bf,re,key);

    if(result == true)
	printf("Delete Success\n");
    else
	printf("Delete Failed\n");
}

/*
 * B��Free����
 */
void BT_Free(B_Tree bt)
{
    if(bt == NIL_Sentry)
    {
	//LINE_DEBUG("bt is NULL");
	return;
    }
    
    int i = 0;
    while(i <= bt->capacity)
    {
	BT_Free(bt->childs[i]);
	++i;
    }
    SAFE_FREE(bt);
}

/*
 * ��ʾB�����еĳ����ڵ�
 *
 */
void BT_Show(B_Tree bt)
{
    if(bt == NIL_Sentry)
    {
	//LINE_DEBUG("bt is NULL");
	return;
    }
    
    int i = 0;
    printf("| ");
    while(i < bt->capacity)
    {
	printf("%d ",bt->elements[i]);
	++i;
    }
    printf("|");
    printf("\n");
    
    i = 0;
    while(i < bt->capacity+1)
    {
	BT_Show(bt->childs[i]);
	++i;
    }
}






int main()
{

    if(!InitSentry())
    {
	LINE_DEBUG("NIL_Sentry malloc failed");
	return -1;
    }

    P_BT_Forest bt_forest = (P_BT_Forest)malloc(sizeof(BT_Forest));
    if(bt_forest == NULL)
    {
	LINE_DEBUG("BT Forest malloc failed");
	return -1;
    }
    bt_forest->capacity = 0;
    bt_forest->B_Trees[0] = NIL_Sentry;
    bt_forest->B_Trees[1] = NIL_Sentry;
    bt_forest->B_Trees[2] = NIL_Sentry;
    bt_forest->B_Trees[3] = NIL_Sentry;
    bt_forest->B_Trees[4] = NIL_Sentry;
    /*
    //�ֹ�����һ��4��B��
    P_BTNode node1 = CreateBTNode();
    P_BTNode node2 = CreateBTNode();
    P_BTNode node3 = CreateBTNode();
    P_BTNode node4 = CreateBTNode();
    P_BTNode node5 = CreateBTNode();
    node1->capacity = 3;
    node1->elements[0] = 40;
    node1->elements[1] = 50;
    node1->elements[2] = 60;
    node2->capacity = 3;
    node2->parent   = node1;
    node2->elements[0] = 10;
    node2->elements[1] = 20;
    node2->elements[2] = 30;
    node3->capacity = 2;
    node3->parent   = node1;
    node3->elements[0] = 43;
    node3->elements[1] = 47;
    node4->capacity = 2;
    node4->parent   = node1;
    node4->elements[0] = 55;
    node4->elements[1] = 58;
    node5->capacity = 3;
    node5->parent   = node1;
    node5->elements[0] = 70;
    node5->elements[1] = 80;
    node5->elements[2] = 90;

    node1->parent = NIL_Sentry;
    node1->childs[0] = node2;
    node1->childs[1] = node3;
    node1->childs[2] = node4;
    node1->childs[3] = node5;

    bt_forest->B_Trees[0] = node1;
    bt_forest->capacity  = 1;
    
    //����Search����
    P_BTNode re = BT_Search(bt_forest->B_Trees[0],100);
    if(NIL_Sentry->capacity == 0)
    {
	printf("Search Success,BTree Node First key=%d\n",re->elements[0]);
    }
    else
    {
	printf("Search Failed,BTree Last Super Node First key=%d\n",re->elements[0]);
	//�ڱ����
	NIL_Sentry->capacity = 0;
    }

    //����Insert����
    if(BT_Insert(bt_forest,31))
	printf("Insert Success\n");
    else
	printf("Insert Failed\n");
    if(BT_Insert(bt_forest,32))
	printf("Insert Success\n");
    else
	printf("Insert Failed\n");
    if(BT_Insert(bt_forest,33))
	printf("Insert Success\n");
    else
	printf("Insert Failed\n");
    if(BT_Insert(bt_forest,34))
	printf("Insert Success\n");
    else
	printf("Insert Failed\n");
    if(BT_Insert(bt_forest,35))
	printf("Insert Success\n");
    else
	printf("Insert Failed\n");
    
    printf("node1->elements[0]=%d\n",node1->elements[0]);//30
    printf("node1->childs[0]->elements[0]=%d\n",node1->childs[0]->elements[0]);//10
    printf("node1->childs[1]->elements[0]=%d\n",node1->childs[1]->elements[0]);//31
    printf("node1->childs[2]->elements[0]=%d\n",node1->childs[2]->elements[0]);//43
    printf("node1->childs[0]->capacity=%d\n",node1->childs[0]->capacity);//2
    printf("node2->parent->elements[0]=%d\n",node2->parent->elements[0]);//30
    
    BT_Show(bt_forest->B_Trees[0]);
    
    BT_Delete(bt_forest,32);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,90);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,80);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,50);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,30);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,47);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,35);
    BT_Show(bt_forest->B_Trees[0]);
    */
    
    P_BTNode node1 = CreateBTNode();
    P_BTNode node2 = CreateBTNode();
    P_BTNode node3 = CreateBTNode();
    P_BTNode node4 = CreateBTNode();
    P_BTNode node5 = CreateBTNode();
    P_BTNode node6 = CreateBTNode();
    P_BTNode node7 = CreateBTNode();
    P_BTNode node8 = CreateBTNode();
    P_BTNode node9 = CreateBTNode();
    P_BTNode node10 = CreateBTNode();

    node1->capacity = 3;
    node1->elements[0] = 40;
    node1->elements[1] = 50;
    node1->elements[2] = 60;
    node2->capacity = 2;
    node2->elements[0] = 35;
    node2->elements[1] = 36;
    node2->parent = node1;

    node3->capacity = 2;
    node3->elements[0] = 45;
    node3->elements[1] = 46;
    node3->parent = node1;
    node4->capacity = 2;
    node4->elements[0] = 55;
    node4->elements[1] = 56;
    node4->parent = node1;
    node5->capacity = 2;
    node5->elements[0] = 65;
    node5->elements[1] = 66;
    node5->parent = node1;

    node1->childs[0] = node2;
    node1->childs[1] = node3;
    node1->childs[2] = node4;
    node1->childs[3] = node5;

    
    bt_forest->B_Trees[0] = node1;
    bt_forest->capacity  = 1;

    BT_Show(bt_forest->B_Trees[0]);
    
    
    BT_Delete(bt_forest,56);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,60);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,40);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,35);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,36);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,45);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,46);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,50);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,55);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,65);
    BT_Show(bt_forest->B_Trees[0]);
    BT_Delete(bt_forest,66);
    BT_Show(bt_forest->B_Trees[0]);
    



    BT_Free(bt_forest->B_Trees[0]);
    SAFE_FREE(bt_forest);
    SAFE_FREE(NIL_Sentry);


    return 0;
}

