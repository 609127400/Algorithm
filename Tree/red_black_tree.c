
/*
 *
 *                           �����
 *
 *  1.Ҳ��������ƽ������������������/ɾ���Ȳ�����ʱ���ܹ���֤�������´ﵽO(logn)
 *    ��ƽ��ѹ��������ȣ�ʹ�� �·�� <= 2*���·����ʹ�ú����������ƽ�⡣��������
 *    �˽ṹ���棬AVL������ں������ƽ�⣬���Ǻ�����Ĳ���ɾ�����������˸ı䶼�ܱ�֤
 *    O(1)
 *  2.�������ʣ�
 *    �� ���нڵ㣬Ҫô�Ǻ�ɫ��Ҫô�Ǻ�ɫ
 *    �� ���ڵ�����Ǻ�ɫ
 *    �� Ҷ�ӽڵ�����Ǻ�ɫ����Ϊ�������㣬Ҷ�ڵ�һ�㲻�洢���ݣ���NIL��ʾ
 *    �� ����һ�ڵ���������ⲿ�ڵ��·���У���ɫ�ڵ�������ͬ��ע���ǴӸ����ⲿ�ڵ㡣
 *    �� �����ڵ�Ϊ��ɫ�����������ӽڵ�����Ǻ�ɫ��������·���в������������������ɫ
 *       �ڵ�������Ҳ����һ���ڵ�Ϊ��ɫ�����ӽڵ㣬������������ӽڵ���Ϊ��ɫ�����
 *       ���ʢܵó�����
 *
 *  3.���ݺ���������ʣ�����ÿ����ڵ㣬ʹ�������ɫ���ڵ�ƽ�룬�γ�һ�������ڵ㣬��ʱ
 *    ���൱��һ��4��B��������˵4��B���Ǻ������Ӱ�ӡ�ÿһ�ú�����ĺڸ߶ȣ�ֻ���ɫ��
 *    �㣩�������Ӧ��B���ĸ߶ȡ�
 *
 *  4.��ɾ����Ҫ��������ɾ�����жԺ�������ʵ�Ӱ�죬Ҫ���Ǹ��������ͨ���Ը��ڵ�P��
 *    �游�ڵ�G����ڵ�U���ֽڵ�ı�ɫ����ת��ά�����Ĳ����������������������б�����
 *
 *  5.NIL�ڱ�������ʵ�ʴ洢���ݵĽڵ㶼���������ӽڵ㡣���ĳһ�洢���ݵĽڵ�ֻ����
 *    һ���ӽڵ�򲻴����ӽڵ㣬����NIL�ڵ㲹�롣NIL�ڵ�ֻ��Ϊ�˱�ʶ��ǰ�����ѵ��ף�
 *    �����洢ʵ�����ݣ�Ϊ�˲��˷Ѵ洢�ռ䣬һ������һ��NIL�ڱ����滻���е�NIL������
 *    ��ָ��NIL�ڵ��ָ�붼ͳһָ��NIL�ڱ������⣬����ɾ�����������ϻ��ݵĹ��̣�Ϊ��
 *    ���㣬Ҳ�����ڵ�ĸ��ڵ�ָ���ڱ�������ڱ���Ϊ�����ⲿ�ڵ㣬Ҳ���뵽�Ժ��ɫ��
 *    �����Ͳ����С�
 *  6.�ⲿ�ڵ��Ҷ�ڵ㣺�ⲿ�ڵ���Ϊ�˼��㣬�������㣬��Ϊ����ȥ�������ڵ����ڵ�֮��
 *    �Ľڵ㣬���洢ʵ�ʵ����ݡ�Ҷ�ڵ㱾�������еĽڵ㣬�Ҵ�������ĩ�ˡ�һ���ں������
 *    B�����е����нڵ�Ŀ��ӽڵ㣨ָ�룩ָ���ⲿ�ڵ㣬�Ա���з����Ͳ���������һ��Ҷ��
 *    ��������ӽڵ�ָ�붼�ǿյģ�����Խ���ָ���ⲿ�ڵ㡣
 *
 *
 *
 *
 *
 *					    2016��10��21��
 *
 */


#define _DEBUG_CLOSE_
#include "../PublicForAlgorithms.h"

typedef enum{RED=0xff0000,BLACK=0xffffff,}Color;

#define NIL_FLAG 0xfffffff

typedef int ElementType;

//��С������ڵ����ݽṹ
typedef struct Node
{
    ElementType  element; //����
    Color        color;   //��ɫ
    struct Node* parent;  //���ڵ�ָ��
    struct Node* lchild;  //���ӽڵ�ָ��
    struct Node* rchild;  //���ӽ��ָ��

}RBTNode,*RBT,*P_RBTNode;

//RBTɭ�����ݽṹ
//����ֻ���õ�ɭ�ֵ�һ���ڵ㣬Ҳ�������RBT����root�ڵ�
typedef struct
{
    P_RBTNode rbt_root; //ָ��һ��RBT���ĸ��ڵ�
    int       id;       //����ʶ
    int       count;    //ͳ��RBT���Ľڵ���

}RBT_ForestNode,*P_RBT_Forest,*P_RBT_ForestNode;

/* 
 * 1.Ϊ�������㣬����NIL�ڱ�Ϊȫ�ֱ�������main�г�ʼ��
 * 2.Ĭ��Ϊ��ɫ
 * 3.���нڵ���CreateRBTNode������parent/lchild/rchildĬ�϶�
 *   ָ����ڱ�����CreateRBTNode����ʧ�ܣ���Ĭ�Ϸ��ش��ڱ���
 *   �����ڱ�������������/�±����Ľ��������账��Ľڵ�
 * 3.RBT_ForestNode��rbt_rootĬ��ָ����ڱ�
 */
P_RBTNode NIL_Sentry;

//����һ��RBT�ڵ�
inline P_RBTNode CreateRBTNode(ElementType e,Color c)
{
    P_RBTNode node = (P_RBTNode)malloc(sizeof(RBTNode));
    if(node == NULL) return NIL_Sentry;
    node->element = e;
    node->color   = c;
    node->parent  = NIL_Sentry;
    node->lchild  = NIL_Sentry;
    node->rchild  = NIL_Sentry;
    return node;
}

/* 
 * ��ת
 * 1.���������C����˵����ת��C����������һ����ת���漰��G P
 *
 *   ��           ��           ��          ��
 *   G            G            G           G
 *    \            \          /           /
 *     P            P        P           P
 *      \          /          \         /
 *       C        C            C       C
 * ��-��-��    ��-��-��   ��-��-��    ��-��-��
 *   RRL         RLR        LRL         LLR
 *
 * 2.��������C child P parent g grandparent, A-B-C
 * A��B����ֱ����P��G��N��P�����ҹ�ϵ����������ӽڵ㣬�Ҵ������ӽڵ�
 * C�������N��P��ת�ķ�����CΪP�����ӽڵ㣬��Cͨ����ʱ�뷽�����ת��Pλ
 * �ã����ﶨ����ʱ�뷽��Ϊ����
 * 3.���Тںܶ͢Խڵ�Ĳ���һ�£�ֻ��G����C������������֮�ֻ����һ��������
 *   ����һ���ж�P��G�����ӽڵ㻹�����ӽڵ㼴�ɣ�������ת���򣬶���Ϊ����ת
 *   ��CΪP�����ӽڵ㣬˳ʱ�룬C��ת��P��λ�ã����ٺ͢�ͬ������Ϊ����ת
 * 4.��תֻ��Fix��ʹ�ã�Roll������C/P�Ǵ��ڵģ�G��������ڱ�����ΪFix������
 *   ��N/P/G��ȷ�����ڵģ����ݸ�Roll�����Ĳ���ΪN��P��
 *
 * ע�⣺ʹ��RollʱҪע�����Ҫ��ת�ĵ㣬���׳������ĸ��㣨ʵ��Ҫ������һ��ĵ㣩
 *       ��Ӧͼ�е�C�㣡��ע��RBTNode_Left_Roll��RBTNode_Right_Roll��G/P/C
 *       ��RBT_Insert_Fix()��G/P/N������
 * 
 *
 */
//�٢�
void RBTNode_Left_Roll(P_RBT_ForestNode forest_node,P_RBTNode C)
{
    P_RBTNode G = C->parent->parent;
    P_RBTNode P = C->parent;

    LINE_DEBUG("N parent element is %d",C->parent->element);
    if(G != NIL_Sentry)
    {
	if(G->lchild == P)
	    G->lchild = C;
	else
	    G->rchild = C;
    }
    else
    {
	//��֧���˴�˵��P�Ǻ�������ڵ�
	forest_node->rbt_root = C;
    }
    P->parent   = C;
    P->rchild   = C->lchild;
    if(C->lchild != NIL_Sentry){ C->lchild->parent = P->rchild; }
    C->parent   = G;
    C->lchild   = P;
}

//�ڢ�
void RBTNode_Right_Roll(P_RBT_ForestNode forest_node,P_RBTNode C)
{
    P_RBTNode G = C->parent->parent;
    P_RBTNode P = C->parent;

    LINE_DEBUG("N parent element is %d",C->parent->element);
    if(G != NIL_Sentry)
    {
	if(G->lchild == P)
	    G->lchild = C;
	else
	    G->rchild = C;
    }
    else
    {
	//��֧���˴�˵��P�Ǻ�������ڵ�
	forest_node->rbt_root = C;
    }
    P->parent   = C;
    P->lchild   = C->rchild;
    if(C->rchild != NIL_Sentry){ C->rchild->parent = P; }
    C->parent   = G;
    C->rchild   = P;
}

/*
 * �������Fix���򣺶��ڲ���ĺ�ɫ�󣬶Ժ��������Fix��
 *                  ʹ��ά���������5������
 * 1.N������Ľڵ�
 * 2.forest_node��ά����������ڵ��ɭ�ֽڵ�
 * 3.�ں������5�������У�����Insert_Fix��ֻ�����ƻ� ���ڵ��Ǻ�ɫ
 *   �� ��ɫ�ڵ���ӽڵ�����Ǻ�ɫ ���������ʣ���ֻ����ͬʱ�ƻ���
 *   �е�һ����
 * 4.��������ѭ���������ϲ㴦��Ч�ʽϵݹ�Ҫ��
 * ע�⣺����RBT_Insert�����ܹ�����Insert_Fix������
 *       N->parent��Ϊ�� �� N->parent->color==RED
 *       ��ΪN->parent->color==RED����G�ڵ�һ��������ΪBLACK
 * 5.������ʱ��ֻ��Ҫ����G P U N�ĸ��ڵ�Ĳ��ֺ���ɫ����������ۣ�
 * Ȼ���������ѭ�����ɣ�ֱ���������ڵ㡣
 *   ����Ļ���˼·���������Ǻ�ɫ�ڵ㣬���ֻ����Υ�������������
 * ������ʡ�����ڴ�������ʱ��P������תN��Pλ�ó�Ϊ����P�϶���Ҫ��
 * �ڣ�P����P��ڣ��򾭹��˵�·������һ���ڵ㣬Ҫ�跨����U�������
 * ��P��N��ת��Gλ�ã���Ӧ����U����������P����P·���Ͼͻ���һ���ڵ㡣
 * ��U�Ǻ�ɫ����ֻ�����ϲ�ѭ������
 */
void RBT_Insert_Loop_Fix(P_RBT_ForestNode forest_node,P_RBTNode N)
{
    /* �������ڵ�ĸ��ڵ�����Ǻ�ɫ�Ļ���Ҫѭ��������ȥ
     * 1.���ѭ����N->parent �Ǹ��ڵ㣬����ڵ��Ǻ�ɫ��ѭ���϶��ʹ�ֹͣ��
     *   ���ѭ����N->parent �Ǹ��ڵ���ӽڵ㣬����ʱ���ڵ���N��G�ڵ㣬
     *   ����ڵ㾭����������Ϊ��ɫ������N=G�ٴ�ѭ����N->parentΪ�ڱ���
     *   �㣬Ĭ��Ϊ��ɫ��Ҳ�����ѭ��.���ѭ������N->parent->color==RED
     *   ������ڷ��ʿ�ָ�������
     * 2.��Fix�����У�ֻ��������ת/��ɫ����������λ��ԭG�ڵ�λ�õĽڵ��
     *   ��ɫ�Ǻ�ɫ���Ǻ�ɫ������Ϊ��ɫ��������ѭ���ˣ��ɵ���break����
     *   Ϊ��ɫ����Ҫ���˽ڵ���Ϊ�µ�N�ڵ�������ϲ�ѭ���������µ�N�ڵ��
     *   parent�Ƿ�ΪRED
     */
    while(N->parent->color == RED)
    {
	//G-grandparent P-parent N-now���ڴ���Ľڵ�
	P_RBTNode G = N->parent->parent;
	P_RBTNode P = N->parent;

	//G left to P and P left to N
	if(G->lchild == P && P->lchild == N)
	{
	    LINE_DEBUG("G left to P and P left to N");
	    P_RBTNode U = G->rchild;
	    //��Ϊ�� || �����Ի�����֤���Ƿ�Ϊ�գ������Ϊ��������֤��ɫ
	    if(U == NIL_Sentry || U->color == BLACK)
	    {
		//P��Ϊ��ɫ��G��Ϊ��ɫ����P�õ�ԭ��G��λ�ã�G��P�����ӽڵ�
		P->color = BLACK;
		G->color = RED;
		//P������Ҫ������һ��ĵ㣬���Դ�P����N
		RBTNode_Right_Roll(forest_node,P);

		break;
	    }
	    else
	    {
		//��ʱ��UΪ��ɫ����G��Ϊ��ɫ��P/U��Ϊ��ɫ����
		G->color = RED;
		P->color = BLACK;
		U->color = BLACK;
		
		N = G;
	    }
	}
	//G left to P and P right to N
	else if(G->lchild == P && P->rchild == N)
	{
	    LINE_DEBUG("G left to P and P right to N");
	    //ȷ���常�ڵ�
	    P_RBTNode U = G->rchild;

	    //������ת������Ϊ��case2�����
	    RBTNode_Left_Roll(forest_node,N);

	    if(U == NIL_Sentry || U->color == BLACK)
	    {
		LINE_DEBUG("U == NIL_Sentry || U->color == BLACK");
		N->color = BLACK;
		G->color = RED;
		//������N��Ҫ������һ��ĵ㣬��˴���N
		RBTNode_Right_Roll(forest_node,N);

		break;
	    }
	    else
	    {
		//��G��Ϊ��ɫ��P/U��Ϊ��ɫ����
		G->color = RED;
		N->color = BLACK;
		U->color = BLACK;

		N = G;
	    }
	}
	//G right to P and P right to N
	//case4:����case2����case2�Գ�
	else if(G->rchild == P && P->rchild == N)
	{
	    LINE_DEBUG("G right to P and P right to N");
	    P_RBTNode U = G->lchild;
	    if(U == NIL_Sentry || U->color == BLACK)
	    {
		P->color = BLACK;
		G->color = RED;
		RBTNode_Left_Roll(forest_node,P);

		break;
	    }
	    else
	    {
		G->color = RED;
		P->color = BLACK;
		U->color = BLACK;

		N = G;
	    }
	}
	//G right to P and P left to N
	//case5:����case3����case3�Գ�
	else if(G->rchild == P && P->lchild == N)
	{
	    LINE_DEBUG("G right to P and P left to N");
	    P_RBTNode U = G->lchild;
	    RBTNode_Right_Roll(forest_node,N);
	    if(U == NIL_Sentry || U->color == BLACK)
	    {
		P->color = BLACK;
		G->color = RED;
		RBTNode_Left_Roll(forest_node,N);

		break;
	    }
	    else
	    {
		G->color = RED;
		P->color = BLACK;
		U->color = BLACK;

		N = G;
	    }
	}
    }//while end
    
    //����һֱ���ϲ�ѭ�����ս����ڵ��Ϊ��ɫ�����
    //�ڴ����۸��ڵ��Ƿ��Ϊ��ɫ���ú�һ�£�ȷ�����������
    forest_node->rbt_root->color = BLACK;
}

/*
 * �ݹ���ʽ��Insert_Fix
 * 1.����֧��ʽ�ı�
 * 2.ʹ�õݹ�
 */
void RBT_Insert_Recursion_Fix(P_RBT_ForestNode forest_node,P_RBTNode N)
{
    if(N->parent->color == BLACK)
	return;

    P_RBTNode G = N->parent->parent;
    P_RBTNode P = N->parent;
    P_RBTNode U = G->lchild==P ? G->rchild : G->lchild;

    if(U == NIL_Sentry || U->color == BLACK)
    {
	if(G->lchild == P && P->lchild == N)
	{
	    P->color = BLACK;
	    G->color = RED;
	    RBTNode_Right_Roll(forest_node,P);
	}
	else if(G->lchild == P && P->rchild == N)
	{
	    RBTNode_Left_Roll(forest_node,N);
	    N->color = BLACK;
	    G->color = RED;
	    RBTNode_Right_Roll(forest_node,N);
	}
	else if(G->rchild == P && P->rchild == N)
	{
	    P->color = BLACK;
	    G->color = RED;
	    RBTNode_Left_Roll(forest_node,P);
	}
	else if(G->rchild == P && P->lchild == N)
	{
	    RBTNode_Right_Roll(forest_node,N);
	    P->color = BLACK;
	    G->color = RED;
	    RBTNode_Left_Roll(forest_node,N);
	}
    }
    else
    {
	G->color = RED;
	P->color = BLACK;
	U->color = BLACK;
	//�ڱ�֤ͬInsert����Insert_Fix�������£����ϲ�ݹ����Fix
	if(G->parent != NIL_Sentry && G->parent->color == RED)
	    RBT_Insert_Recursion_Fix(forest_node,G);
    }
   
    forest_node->rbt_root->color = BLACK;
}

/*
 * Insert����
 * ������
 * forest_node:ָ��Ҫ�����ĺ������ɭ�ֽڵ�
 * node��      Ҫ����Ľڵ㣬��������CreateRBTNode��������
 *
 * ˵����
 * ���ݾ����5���������if���з�֧�����в�ͬ�Ĳ���
 * case1:RTB rootΪ�գ���ֱ�Ӳ��룬��Ҫ������ڵ����ɫ��ΪBLACK
 * case2-case5:P�ڵ�Ϊ��ɫ������Fix������case
 *
 */
bool RBT_Insert(P_RBT_ForestNode forest_node,P_RBTNode node)
{
    if(node == NIL_Sentry)
    {
	LINE_DEBUG("RBT_Insert Failed: Node Is NULL");
	return false;
    }
    //����������ɫ�ڵ�
    if(node->color == BLACK)
    {
	LINE_DEBUG("RBT_Insert Failed: Node Is BLACK");
	return false;
    }
    
    P_RBTNode temp_node = forest_node->rbt_root;
    P_RBTNode temp_parent = temp_node;
    //������ѭ����Ҫ����Ľڵ�
    while(temp_node != NIL_Sentry)
    {
	temp_parent = temp_node;
	if(node->element < temp_node->element)
	    temp_node = temp_node->lchild;
	else
	    temp_node = temp_node->rchild;
    }
    
    //�ڲ������
    //��ʱʵ���Ǻ����Ϊ�ջ�ֻ��һ�����ڵ�����
    /*****************************����case1*****************************/
    if(temp_parent == NIL_Sentry)
    {
	node->color = BLACK;
	node->parent = NIL_Sentry;
	forest_node->rbt_root = node;
    }
    else if(node->element < temp_parent->element)
    {
	temp_parent->lchild = node;
	node->parent = temp_parent;
    }
    else
    {
	temp_parent->rchild = node;
	node->parent = temp_parent;
    }
    
    /*
     * �� �����޲���Ҳ�ɽ�Fix���뵽�����if��֧�У���Fix�ķ�֧������Ӧ�ĸı����
     * �����Fix����������������Fix�������if��֧�ֿ�����Ϊȫ��������
     * 1.������ڵ�Ϊ��ɫ����Υ���κκ���������ʣ��򲻱䡣�����Ҫ����Fix����
     * 2.node->parent != NIL_Sentry���ж������ɲ�Ҫ����Ϊ�ڱ�Ĭ���Ǻ�ɫ
     * 3.������ʽ��Fix����������һ��
     */
    if(node->parent != NIL_Sentry && node->parent->color == RED)
    {
	LINE_DEBUG("Go Fix");
	//RBT_Insert_Loop_Fix(forest_node,node);
	RBT_Insert_Recursion_Fix(forest_node,node);
    }
    
    ++(forest_node->count);
    return true;
}

/*
 * DeleteAssist����
 * 1.��ΪN�����һ���ӽڵ㡣�ӽڵ���ΪM�ڵ㡣N���ֵܽڵ���ΪS�����ڵ���ΪP��
 *   ���Nû���ӽڵ㣬�������ڱ�NIL_Sentry���ɶ��ӡ���Ҫ���Ĳ����ǽ�M��ֱ��
 *   �����������ɫ��N��Ϊ�µ�N�㣬Ȼ�������N����ɫ����������������漰��
 *   S���ӽڵ�Sl��Sr����S�������ӽڵ㣬��Ҳ��NIL_Sentry���ɶ��ӡ���ˣ�M Sl
 *   Sr����������ʵ�洢���ݵ��ڲ��ڵ㣬Ҳ�����ǲ��洢���ݵ�Ҷ�ڵ㣬��NIL_Se
 *   ntry��
 *        P                  P              P               P
 *       / \                / \            /                 \
 *      N   S      ��      S   N    ��    N          ��       N
 *       \                    /
 *        M                  M
 * 2.DeleteAssist�����
 *   ɾ���Ļ���˼·��ɾ��N����N������Ǻ�ɫ����ֱ��ɾ���������ǵ���N�Լ����ӽ�
 *   ��(��Ϊ��)�������ӽڵ����N���úڡ���NҲû���ӽڵ㣬��ֻ�ܿ�P��S��û�к�ɫ
 *   ���Խ���ת��Ϊ��ɫ���ֲ���ɾ����N������һ����ɫ�ڵ����ʧ�����P S�������
 *   ��û�к�ɫ���Խ裬��ֻ��ͨ������S����ĺ�ɫ��������⣬�������ʡ����������
 *   Ϊ��P��(����)�к�ɫ��S��(����)��ɫ��S�Ķ����к�ɫ��û�к�ɫ��������ķ���
 *   �Ļ���˼·ϸ���ǽ�P/S�����еĺ�ɫ��ں�һ���ڵ���Ų��P��λ�á�
 *   �� ��N�Ǻ�ɫ����N�϶��ǷǸ��ڵ������ӽڵ㡣�����ֱ��ɾ��N��
 *   �� ��N�Ǻ�ɫ���Ҵ���һ����ɫ�ӽڵ�M����M�滻N����M�úڣ�ɾ��M�㡣
 *   �� ��N�Ǻ�ɫ�����ǲ�����(��ɫ)�ӽڵ㣬������Ƚ��鷳��
 *      ��ʱS�ض����ڡ��������ϸ�����£�
 *      ע�⣺SΪĩ�ڵ���Ϊ��ʱ��Sl Sr�����ڣ����Ϊ�졣��Sl SrΪ����ָ�����䲢
 *      �����ڣ�ֻ�����ϵĸɶ��ӻ���˵Ҷ�ڵ�NIL_Sentry(��ɫ)������ġ�
 *      (1) NΪ���ڵ㣬��ֱ��ɾ��������Ϊ�ա�
 *      (2) SΪ�ڣ�����PΪ�죬��ʱN��P��ڣ���򵥵Ľ�P�úڣ���S�ú�(�������S��
 *          Sl Sr��������)��
 *      (3) SΪ�ڣ�Sl��Sr����һ���Ϊ�죬��ʱN��Sl��Sr��ڣ�ͨ��������תSl��Sr
 *          ��ԭP��λ��(˭������ת˭)����Sl�Ǻ�ɫ����ת�Ĺ���N��P�Ĺ�ϵ����Ӧ��
 *          S��Sl�Ĺ�ϵ�෴�����෴�����ֱ�ӽ�S����ת��Pλ�ã�S��ΪP����ɫ��P��
 *          �ڣ�Sl�úڣ������෴����������תSl��Sλ�ã�Sl��S������ɫ����ʱSl��Ϊԭ
 *          S��S��ΪSl�ĺ��ӽڵ㣬Ȼ���ٽ�Sl��ת��P��λ�ã�Sl��ΪP����ɫ��P�úڣ�
 *          S�úڡ�
 *      (4) SΪ��ɫ(��Sl Sr�ش��ڱ�Ϊ��ɫ��P��Ϊ��)����NΪP�����ӽڵ㣬��ʱN��S��
 *          �ڣ���S������ת����ԭ����P������ʱSl��ΪP�����ӽڵ㡣��S�úڣ�Sl�ú졣
 *      (5) SΪ�ڣ�Sl Sr(������)Ϊ�ڣ�PΪ�ڡ���Pû�к�ɫ��SҲû�к�ɫ������ͨ��
 *          ���ת�ڵ�;��������⣬ֻ����ͨ���ļ���S����ĺ�ɫ��������⡣��S��Ϊ
 *          �죬����P������·�����ﵽƽ������1����P��Ϊ�µ�N���(1)��ʼ���д���
 *      ����(1)-(5)����ĵĴ����ֱ��free��N�ڵ㼴�ɡ�
 *   �� ���۵����������Ϊdelete_case1...delete_case5�����г�����delete_case1�⣬
 *      ����N���ڵ������⣬��˽�N���ͷ�������ڵ���delete_case֮��ͳһ�����ͷ�
 *      Original_N��
 *
 */
void RBT_Delete_Case1(P_RBT_ForestNode forest_node,P_RBTNode N)
{
    SAFE_FREE(N);
    forest_node->rbt_root = NIL_Sentry;
}

void RBT_Delete_Case2(P_RBTNode N)
{
    //parent,sibling
    P_RBTNode P = N->parent;
    P_RBTNode S = (N == P->lchild) ? P->rchild : P->lchild;
    S->color = RED;
    P->color = BLACK;
    if(N == P->lchild)
	P->lchild = NIL_Sentry;
    else
	P->rchild = NIL_Sentry;
}

void RBT_Delete_Case3(P_RBT_ForestNode forest_node,P_RBTNode N)
{
    P_RBTNode P = N->parent;
    P_RBTNode S = (N == P->lchild) ? P->rchild : P->lchild;
    P_RBTNode S_l = S->lchild;
    P_RBTNode S_r = S->rchild;
    if(N == P->lchild)
    {
	//S��lchildΪ�����lchild/rchild��Ϊ������˷�֧
	//S_l(Ϊ��)��S�Ĺ�ϵ������N��P�Ĺ�ϵ��ͬ������lchild
	if(S_l->color == RED)
	{
	    RBTNode_Right_Roll(forest_node,S_l);
	    RBTNode_Left_Roll(forest_node,S_l);
	    S_l->color = P->color;
	    P->color   = BLACK;
	}
	//S��rchildΪ��
	//S_l(Ϊ��)��S�Ĺ�ϵ������N��P�Ĺ�ϵ�෴
	else
	{
	    RBTNode_Left_Roll(forest_node,S);
	    S->color   = P->color;
	    P->color   = BLACK;
	    S_r->color = BLACK;
	}
    }
    //�������
    else
    {
	if(S_l->color == RED)
	{
	    RBTNode_Right_Roll(forest_node,S);
	    S->color   = P->color;
	    P->color   = BLACK;
	    S_l->color = BLACK;
	}
	else
	{
	    RBTNode_Left_Roll(forest_node,S_r);
	    RBTNode_Right_Roll(forest_node,S_r);
	    S_r->color = P->color;
	    P->color   = BLACK;
	}
    }
}

void RBT_Delete_Case4(P_RBT_ForestNode forest_node,P_RBTNode N)
{
    P_RBTNode P = N->parent;
    P_RBTNode S = (N == P->lchild) ? P->rchild : P->lchild;
    P_RBTNode S_l = S->lchild;
    P_RBTNode S_r = S->rchild;
    
    if(N == P->lchild)
    {
	RBTNode_Left_Roll(forest_node,S);
	S->color = BLACK;
	S_l->color = RED;;
    }
    else
    {
	RBTNode_Right_Roll(forest_node,S);
	S->color = BLACK;
	S_r->color = RED;
    }
}

void RBT_Delete_Case5(P_RBTNode N)
{
    P_RBTNode P = N->parent;
    P_RBTNode S = (N == P->lchild) ? P->rchild : P->lchild;
    S->color = RED;
}

bool RBT_Delete_Assist(P_RBT_ForestNode forest_node,P_RBTNode N)
{
    if(forest_node->rbt_root == NIL_Sentry || forest_node->rbt_root == NULL)
    {
	LINE_DEBUG("RBT is NULL");
	return false;
    }
    if(N == NIL_Sentry || N == NULL)
    {
	LINE_DEBUG("N is NULL");
	return false;
    }

    P_RBTNode P = N->parent;
    P_RBTNode S = NIL_Sentry;
    //�� ֱ��ɾ��N
    if(N->color == RED)
    {
	LINE_DEBUG("Ȧ1");
	if(P->lchild == N)
	    P->lchild = NIL_Sentry;
	else
	    P->rchild = NIL_Sentry;
	SAFE_FREE(N);
    }
    //�� ��M�滻N������ֱ����element�滻���Ͳ����漰P����ɫ�͸��ڵ���
    else if(N->lchild != NIL_Sentry)
    {
	LINE_DEBUG("Ȧ2");
	N->element = N->lchild->element;
	SAFE_FREE(N->lchild);
	N->lchild = NIL_Sentry;
    }
    else if(N->rchild != NIL_Sentry)
    {
	LINE_DEBUG("Ȧ2");
	N->element = N->rchild->element;
	SAFE_FREE(N->rchild);
	N->rchild = NIL_Sentry;
    }
    //�� NΪ�������ӽڵ�
    else
    {
	//(1)
	if(N->parent == NIL_Sentry)
	{
	    LINE_DEBUG("delete_case1");
	    RBT_Delete_Case1(forest_node,N);
	    return true;
	}

	//����ԭʼN
	P_RBTNode Original_N = N;
	while(N->parent != NIL_Sentry)
	{
	    P = N->parent;
	    S = (N == P->lchild) ? P->rchild : P->lchild;
	    //(2)
	    if(P->color == RED)
	    {
		LINE_DEBUG("delete_case2");
		RBT_Delete_Case2(N);
		break;
	    }
	    //(3)
	    else if(S->color == BLACK && (S->lchild->color == RED || S->rchild->color == RED))
	    {
		LINE_DEBUG("delete_case3");
		RBT_Delete_Case3(forest_node,N);
		break;
	    }
	    //(4)
	    else if(S->color == RED)
	    {
		LINE_DEBUG("delete_case4");
		RBT_Delete_Case4(forest_node,N);
		break;
	    }
	    //(5) Ψһ������������ϲ���������
	    else if(P->color == BLACK && S->color == BLACK && S->lchild->color == BLACK && S->rchild->color == BLACK)
	    {
		LINE_DEBUG("delete_case5");
		RBT_Delete_Case5(N);
		//����
		N = P;
	    }
	}//while end
	
	//�ͷ�ԭʼN
	if(Original_N == Original_N->parent->lchild)
	    Original_N->parent->lchild = NIL_Sentry;
	else
	    Original_N->parent->rchild = NIL_Sentry;

	SAFE_FREE(Original_N);
    }//if(N->color == RED) end
    
    return true;
} 

/*
 * Delete����
 * forest_node��RBTɭ�ֽڵ㣬��ʾһ������һ�ú�����Ľڵ�
 * element��Ҫɾ���ĺ���Ԫ��element�ĺ�����ڵ㣬������������еĽڵ����Ψһ��
 * 1.��ͨ��������ɾ������һ�����Ѱ��һ��Ҫɾ���ڵ�D�������������ڵ�Lmax������������
 *   С�ڵ�Rmin�����滻��Ȼ��ɾ��Lmax��Rmin��ֱ���滻��D�ڵ�Ҳ����ı����������ʣ����
 *   Delete�Ĳ�����Ϊɾ��Lmax��Rmin�ڵ�����⣬�������ɾ��Rmin�ķ�������Delete_AssistҪ��
 *   �������⡣
 * 2.��D��������һ���ӽڵ�ʱ��ֱ�ӽ�D����Ҫ����ĵ�N���ݸ�Delete_Assist����D�������ӽڵ�ʱ
 *   ����Rmin����ΪҪ�����N�㴫�ݸ�Delete_Assist��
 *   
 */
bool RBT_Delete(P_RBT_ForestNode forest_node,ElementType element)
{
    if(forest_node->rbt_root == NIL_Sentry)
    {
	LINE_DEBUG("The RBT is NULL");
	return false;    
    }
    //Ѱ��element���ڽڵ�
    P_RBTNode temp_node = forest_node->rbt_root;
    while((temp_node != NIL_Sentry) && (temp_node->element != element))
    {
	if(element < temp_node->element)
	    temp_node = temp_node->lchild;
	else
	    temp_node = temp_node->rchild;
    }
    if(temp_node == NIL_Sentry)
    {
	LINE_DEBUG("The Element is not in The RBT");
	return false;
    }
    
    /* Ҫɾ���Ľڵ�������������ѡ������������Сֵ�滻�ڵ㲢������ΪN��
     * ���ݸ�Delete_Assist
     */
    if(temp_node->lchild != NIL_Sentry && temp_node->rchild != NIL_Sentry)
    {
	//Ѱ��Ҫ����ĵ�N���������element���ڵĽڵ�
	P_RBTNode temp_right_min_node = temp_node->rchild;
	while(temp_right_min_node->lchild != NIL_Sentry)
	{
	    temp_right_min_node = temp_right_min_node->lchild;
	}
	//�滻
	temp_node->element = temp_right_min_node->element;
	temp_node = temp_right_min_node;
    }
    
    bool result = RBT_Delete_Assist(forest_node,temp_node);
    if(result)
    {
	--(forest_node->count);
    }
    return result;
}

void RBT_Show(RBT root)
{
    if(root == NIL_Sentry)
	return;

    printf("%2d - ",root->element);
    if(root->color == RED)
	printf("��ɫ");
    else
	printf("��ɫ");
    printf("\n");

    if(root->lchild != NIL_Sentry)
	RBT_Show(root->lchild);
    if(root->rchild != NIL_Sentry)
	RBT_Show(root->rchild);
}

void RBT_Free(RBT root)
{
    if(root == NIL_Sentry)
	return;
    P_RBTNode temp_left  = root->lchild;
    P_RBTNode temp_right = root->rchild;
    SAFE_FREE(root);
    RBT_Free(temp_left);
    RBT_Free(temp_right);
    temp_left  = NULL;
    temp_right = NULL;
}

void Init_RBT_Forest(RBT_ForestNode f[],int f_len)
{
    int i = 0;
    while( i < f_len )
    {
	f[i].rbt_root = NIL_Sentry;
	f[i].id = i;
	f[i].count = 0;
	++i;
    }
}

void Free_RBT_Forest(RBT_ForestNode f[], int f_len)
{
    int i = 0;
    while( i < f_len )
    {
	RBT_Free(f[i].rbt_root);
	++i;
    }
}



int main()
{


    //Ҫ���óɺ�ɫ�ڱ�������Ϻ��������ɾ����
    //�����Ͽɲο�Insert��Insert_Fix����
    NIL_Sentry = (RBT)malloc(sizeof(RBTNode));
    if(NIL_Sentry == NULL)
    {
	printf("NIL Sentry malloc failed\n");
	return -1;
    }
    NIL_Sentry->color = BLACK;

    //��ʼ�����ɭ��
    RBT_ForestNode RBT_FOREST[5];
    Init_RBT_Forest(RBT_FOREST,5);
    
    //����CreateRBTNode
    P_RBTNode node5 = CreateRBTNode(5,RED);
    if(node5) DEBUG("create success!\n");
    P_RBTNode node12 = CreateRBTNode(12,RED);
    if(node12) DEBUG("create success!\n");
    P_RBTNode node10 = CreateRBTNode(10,BLACK);
    if(node10) DEBUG("create success!\n");
    P_RBTNode node15 = CreateRBTNode(15,RED);
    if(node15) DEBUG("create success!\n");
    P_RBTNode node20 = CreateRBTNode(20,BLACK);
    if(node20) DEBUG("create success!\n");
    P_RBTNode node25 = CreateRBTNode(25,RED);
    if(node25) DEBUG("create success!\n");
    P_RBTNode node22 = CreateRBTNode(22,BLACK);
    if(node22) DEBUG("create success!\n");
    P_RBTNode node30 = CreateRBTNode(30,BLACK);
    if(node30) DEBUG("create success!\n");
    
    //�ֹ�д��֯һ�ú����
    /* 
     * RBT_Tree->rbt_root
     *              |
     *             20
     *            /  \
     *          15    25
     *         /      / \
     *        10    22   30
     *       /  \
     *      5   12
     *      
     *          NIL_Sentry
     */
    node20->parent = NIL_Sentry;
    node20->lchild = node15;
    node20->rchild = node25;
    node15->parent = node20;
    node15->lchild = node10;
    node10->parent = node15;
    node10->lchild = node5;
    node10->rchild = node12;
    node5->parent  = node10;
    node12->parent = node10;
    node25->parent = node20;
    node25->lchild = node22;
    node25->rchild = node30;
    
    
    RBT_FOREST[0].rbt_root = node20;
    
    RBT_Show(RBT_FOREST[0].rbt_root);
    
    //insert����
    P_RBTNode node6 = CreateRBTNode(6,RED);
    if(node6) DEBUG("create success!\n");
    
    //����һ��6�ڵ�
    RBT_Insert(&(RBT_FOREST[0]),node6);
    
    RBT_Show(RBT_FOREST[0].rbt_root);

    P_RBTNode node8 = CreateRBTNode(8,RED);
    if(node8) DEBUG("create success!\n");

    //����һ��8�ڵ�
    RBT_Insert(&(RBT_FOREST[0]),node8);
    RBT_Show(RBT_FOREST[0].rbt_root);

    P_RBTNode node9 = CreateRBTNode(9,RED);
    if(node8) DEBUG("create success!\n");
    P_RBTNode node4 = CreateRBTNode(4,RED);
    if(node4) DEBUG("create success!\n");
    P_RBTNode node13 = CreateRBTNode(13,RED);
    if(node13) DEBUG("create success!\n");
    P_RBTNode node1 = CreateRBTNode(1,RED);
    if(node1) DEBUG("create success!\n");

    RBT_Insert(&(RBT_FOREST[1]),node9);
    RBT_Show(RBT_FOREST[1].rbt_root);

    RBT_Insert(&(RBT_FOREST[1]),node4);
    RBT_Show(RBT_FOREST[1].rbt_root);

    RBT_Insert(&(RBT_FOREST[1]),node13);
    RBT_Show(RBT_FOREST[1].rbt_root);

    RBT_Insert(&(RBT_FOREST[1]),node1);
    RBT_Show(RBT_FOREST[1].rbt_root);
    
    //delete����
    P_RBTNode node100 = CreateRBTNode(100,BLACK);
    if(node100) DEBUG("create success!\n");
    P_RBTNode node90 = CreateRBTNode(90,BLACK);
    if(node90) DEBUG("create success!\n");
    P_RBTNode node85 = CreateRBTNode(85,BLACK);
    if(node85) DEBUG("create success!\n");
    P_RBTNode node95 = CreateRBTNode(95,BLACK);
    if(node95) DEBUG("create success!\n");
    P_RBTNode node110 = CreateRBTNode(110,BLACK);
    if(node110) DEBUG("create success!\n");
    P_RBTNode node105 = CreateRBTNode(105,BLACK);
    if(node105) DEBUG("create success!\n");
    P_RBTNode node115 = CreateRBTNode(115,BLACK);
    if(node115) DEBUG("create success!\n");
    
    node100->lchild = node90;
    node100->rchild = node110;
    node90->parent  = node100;
    node110->parent = node100;
    node90->lchild  = node85;
    node90->rchild  = node95;
    node85->parent  = node90;
    node95->parent  = node90;
    node110->lchild = node105;
    node110->rchild = node115;
    node105->parent = node110;
    node115->parent = node110;
    
    RBT_FOREST[2].rbt_root = node100;

    if(RBT_Delete(&(RBT_FOREST[2]),100))
	printf("Delete Success\n");
    else
	printf("Delete Failed\n");
    RBT_Show(RBT_FOREST[2].rbt_root);
    if(RBT_Delete(&(RBT_FOREST[2]),105))
	printf("Delete Success\n");
    else
	printf("Delete Failed\n");
    RBT_Show(RBT_FOREST[2].rbt_root);
    if(RBT_Delete(&(RBT_FOREST[2]),95))
	printf("Delete Success\n");
    else
	printf("Delete Failed\n");
    RBT_Show(RBT_FOREST[2].rbt_root);
    int iiiiiiiii=0;
    if(RBT_Delete(&(RBT_FOREST[2]),110))
	printf("Delete Success\n");
    else
	printf("Delete Failed\n");
    RBT_Show(RBT_FOREST[2].rbt_root);
    if(RBT_Delete(&(RBT_FOREST[2]),85))
	printf("Delete Success\n");
    else
	printf("Delete Failed\n");
    RBT_Show(RBT_FOREST[2].rbt_root);
    if(RBT_Delete(&(RBT_FOREST[2]),115))
	printf("Delete Success\n");
    else
	printf("Delete Failed\n");
    RBT_Show(RBT_FOREST[2].rbt_root);
    if(RBT_Delete(&(RBT_FOREST[2]),90))
	printf("Delete Success\n");
    else
	printf("Delete Failed\n");
    RBT_Show(RBT_FOREST[2].rbt_root);






    
    //clean
    Free_RBT_Forest(RBT_FOREST,5);
    SAFE_FREE(NIL_Sentry);

    return 0;
}

