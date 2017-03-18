/*
 *
 *             AVL��
 * 1.ֻ��һ�����ʣ��κ�һ���ڵ���������߶�Hl���������߶�Hr�Ĳ�ܴ���1
 * 2.�����ĸ߶�Ϊ-1�����ڵ㴦�ĸ߶�Ϊ0���ڵ�ƽ������ = �������߶� - �������߶�
 *   �ڵ�ĸ߶��������������һ��·���ĸ߶ȣ��ڵ��ƽ�����ӵ�ֵ���������ӽڵ��
 *   ������·���߶ȵĲ
 * 3.��Ҫ��ͨ����ת���ֲ������ɾ����ɵĸ߶�������
 * 4.����ɾ��Ҫ���ǵ����е�һ����Ȩ��·������ɾ�������Ľڵ��Ƿ���Ȩ��·���ϡ�
 *   Ȩ��·����һ���ڵ�����������·����
 * 4.ȱ�㣺ɾ�����������˽ṹ�仯�ﵽ��logn�Σ�Ҫ�洢ƽ�����ӻ�߶ȣ�ʵ������Ҳ
 *   �������в�ࡣ
 *
 *                                                2016��11��8��
 */

#define _DEBUG_CLOSE_
#include "../PublicForAlgorithms.h"

typedef int ElementType;
/* ����ƽ������Ҳ���Ի���Ϊ��¼�ýڵ�����������(��)·����ֵ
 * ����ڵ���¸߶ȵ�ʱ��Ҫ�Ƚ��ӽڵ�ĸ߶�ֵ+1�Ƿ��������
 * �߶ȣ������ڣ������+1��Ľϴ��ֵ���������ڣ��򲻸��¡�
 * ����Ǹ߶ȵĻ����ڸ��¸߶�ʱ�����ס�
 */
typedef struct Node
{
    ElementType element;
    struct Node* parent;
    struct Node* lchild;
    struct Node* rchild;
    //ƽ������
    int balance_factor;
}AVLNode, *P_AVLNode, *AVL_Tree;

typedef struct
{
    AVL_Tree root;
    int count;
}AVL_Forest_Node,*P_AVL_Forest_Node;

P_AVLNode CreateAVLNode(ElementType e)
{
    P_AVLNode new_node = (P_AVLNode)malloc(sizeof(AVLNode));
    if(new_node == NULL) return NULL;
    new_node->element = e;
    new_node->parent  = NULL;
    new_node->lchild  = NULL;
    new_node->rchild  = NULL;
    new_node->balance_factor  = 0;
    return new_node;
}

/*
 * ����ҵ����򷵻��ҵ��Ľڵ㣬���δ�ҵ����򷵻�
 * �����ʵ�һ���ڵ�
 */
P_AVLNode AVL_Search(AVL_Tree root,ElementType e)
{
    if(root == NULL)
    {
	LINE_DEBUG("AVL Tree is NULL");
	return NULL;
    }
    
    P_AVLNode temp_parent = NULL;
    while(root != NULL)
    {
	if(e == root->element)
	{
	    return root;
	}
	else
	{
	    temp_parent = root;
	    root = (e < root->element) ? root->lchild : root->rchild;
	}
    }
    return temp_parent;
}

typedef enum {LEFT,RIGHT}Roll_Direction;
/*
 * C(-child) Ҫ������ת�����Ľڵ�
 * d Ҫ��ת�ķ��� LEFT or RIGHT
 */
void AVL_Node_Roll(P_AVL_Forest_Node forest_node,P_AVLNode C,Roll_Direction d)
{
    if(C->parent == NULL) return;
    P_AVLNode G = C->parent->parent;
    P_AVLNode P = C->parent;
    P_AVLNode S = (C == P->lchild) ? P->rchild : P->lchild;
    if(G == NULL)
    {
	forest_node->root = C;
    }
    else
    {
	if(P == G->lchild){ G->lchild = C; }else{ G->rchild = C; }
    }
    C->parent = G;
    if(d == LEFT)
    {
	P->rchild = C->lchild;
	if(C->lchild != NULL) C->lchild->parent = P;
	C->lchild = P;
	P->parent = C;
    }
    else if(d == RIGHT)
    {
	P->lchild = C->rchild;
	if(C->rchild != NULL) C->rchild->parent = P;
	C->rchild = P;
	P->parent = C;
    }
    else
    {
	LINE_DEBUG("Roll Direction is wrong");
    }
}

/*
 * forest_node AVLɭ�ֽڵ㣬��һ��AVL��
 * e Ҫ����Ľڵ�Ԫ��
 * ����Ĳ�����Ҫ�������棺��ת�����ͽڵ�ƽ�����ӵĸ���
 * 1.����eǰ����ʵ�����е�AVL����ƽ��ġ�����e��ĩ�ڵ㡣������������ʵ���в��������
 * 2.����e������parentû����һ���ӽڵ㣬����parentƽ�����Ӽӻ��1��˳��һ·���ϲ�
 *   parent->parent->...->root �Ӽ�1��ֱ����һ���ڵ��ڼӼ�1���Ϊ����2���������Ҫ��
 *   �д���Ĳ�ƽ��㡣
 * 3.�����e��ƽ��ĵ���C�����һ����ӽڵ���B���ٵ�һ����ӽڵ���A��
 *   ��C�϶���|Ha-Hb| == 2��
 *   �����˼·����ͨ����ת���ٵ���һ������һ���ڵ㡣
 *   �����ת����C�����һ����ӽڵ�B����ת���C���뵽��ԭA��λ��(�ٵ�
 *   ��һ��)��B��ԭA��λ�á�
 * 4.��ѡת�����Σ�����ĵ���B�Ĺ�ϵ���� �� B��C�Ĺ�ϵ����һ�¡���e����
 *                 ��B����������B��C�����ӽڵ㡣
 *   ��ѡת�ķ�������B��ת��A�����ɡ�
 *   ˫��ת�����Σ�����ĵ���B�Ĺ�ϵ���� �� B��A�Ĺ�ϵ�����෴����e����
 *                 ��B����������B��A�����ӽڵ㡣
 *   ˫��ת�ķ������Ƚ�B��ͨ�����ڵ㷽����ӽڵ���ת��Bλ�ã��ٽ��µ�
 *   B��ת��Cλ�á�
 * 5.����ת��Ҫ���¸߶ȵĽڵ㣺C B ����Cλ�õ�B->parent->parent->..root
 *   ��תǰ��
 *                        C               ��ƽ��ڵ�
 *                    /        \
 *                   A         B          H_B - H_A = 1
 *   ��ת��e���뵽B�������������µ�����ת
 *                        B                 
 *                    /        \
 *                   C         Br
 *                 /   \
 *               A     Bl
 *  ԭ��B�ĸ߶ȿ϶���A�ĸ߶ȴ�1��������ת��B�ĸ߶Ȳ��䣬C+A�ĸ߶�
 *  ��1����ת��B�ĸ߶��ǲ���ģ��������B��ƽ������һ����0��
 *  F_C = H_A - H_Bl ��ʱ�����·��������B-Br����H_Bl�ĸ߶�ֻ�ܼ�ӱ�ʾ
 *  H_Bl = H_Br+F_B ��� F_C = H_A-H_Br-F_B=H_A-H_B+1-F_B = F_C-F_B+1;
 *  ������תҲ�ɰ��˷������㡣
 * 6.˫��ת��Ҫ���µĽڵ㣺B B_child C ����Cλ�õ�B_child->parent->...->root��e
 *   ����B�����ӽڵ�
 *
 *              C          -->        C            -->        Bl
 *          /       \              /      \                /      \
 *         A         B            A        Bl             C        B
 *                 /   \                  /  \          /   \     /  \
 *               Bl     Br              Bll   B        A    Bll  Blr  Br
 *             /    \                        / \
 *            Bll   Blr                     Blr Br
 *  H��ʾ�߶ȣ�F��ʾƽ�����ӣ�Bll����B�ڵ������ӵ�����ӣ�Blr�����B������Ҷ���
 *  e�Ĳ��뵼���˲�ƽ����Ҫ����˫��ת
 *  F_C = H_A - H_Bll      F_B = H_Blr - H_Br
 *  �ٵ�e���뵽Bl����������ʱ����϶���B-Bl-Bll�������һ�������·������ʱH_Bll��
 *    ֵ����ֱ����H_B-2��ʾ��H_Blr��ֵ��ֻ�ܼ�ӵ���H_Bll - F_Bl = H_B-2-F_Bl��ʾ��
 *    �ɴˣ�F_C = H_A-(H_B-2)=H_A-H_B+2=F_C+2  F_B=H_B-2-F_Bl-H_Br=1-2-F_Bl = -1-F_Bl;
 *  �ڵ�e���뵽Bl����������ʱ����϶���B-Bl-Blr�������һ�������·������ʱH_Blr��
 *    ֵ����ֱ����H_B-2��ʾ��H_Bll��ֵ��ֻ�ܼ�ӵ���H_Blr + F_Bl = H_B-2+F_Bl��ʾ��
 *    �ɴˣ�F_C = H_A-(H_B-2+F_Bl)=H_A-H_B+2-F_Bl=F_C+2-F_Bl  F_B=H_B-2 - H_Br=1-2=-1;
 *  �۵�һ���㶼δ�����²����e���Ӱ�졣�෴�ľ���˫��ת���մ˷������㡣
 * 7.C�ڵ�ĸ��ڵ������ڣ���C->parent->parent->..->root·���ϵ�ƽ����������ת����Ҫ
 *   ���¡�C����������CL CR���Ҵ���H_CR-H_CL=2���Լ����Ի����Ǵ���������������������
 *   ��ת������C����ԭ���ĸ߶ȡ�
 */
bool AVL_Insert(P_AVL_Forest_Node forest_node,ElementType e)
{

    if(forest_node == NULL)
    {
	LINE_DEBUG("Forest_Node is NULL");
	return false;
    }
    if(forest_node->root == NULL)
    {
	P_AVLNode new_root = CreateAVLNode(e);
	if(new_root == NULL) return false;
	forest_node->root = new_root;
    }
    //���Ԫ���Ƿ���������
    P_AVLNode temp_parent = AVL_Search(forest_node->root,e);

    if(temp_parent == NULL)
    {
	LINE_DEBUG("AVL Tree is NULL");
	return false;
    }
    if(temp_parent->element == e)
    {
	LINE_DEBUG("the element has been in the AVL Tree");
	return false;
    }
    //����Ԫ��
    P_AVLNode new_node = CreateAVLNode(e);
    if(new_node == NULL) return false;
    if(e < temp_parent->element)
	temp_parent->lchild = new_node;
    else
	temp_parent->rchild = new_node;
    new_node->parent = temp_parent;
    //��תƽ�Ⲣ���¸߶�
    //���¸߶�ʱ�����������ĸ��£�����ת���������ĸ�����Ҫ���µĸ߶�
    P_AVLNode N = temp_parent;
    if(N->balance_factor == 0)
    {
	if(e < N->element){ ++(N->balance_factor); }
	else{ --(N->balance_factor); }
	
	/*
	 * ���ϸ���ƽ������
	 * 1.һֱ���µ����ڵ㵫��δ���ֲ�ƽ��㣬N->parent == NULL
	 * 2.���µ���;������ƽ��㣬ֱ��break��N->parent != NULL
	 * 3.���µ���;����Ҫ�����ϲ���£���Ҳ����ʧȥƽ�⣬ֱ��
	 *   return����ʱ�����·��������root ->...-> N->parent ->
	 *   N -> e��·������N->parent������Ϊ0��N->parent->e��·�����
	 *   ����������·����ƽ������ϲ㲻��Ҫ�������¡�
	 */
	while(N->parent != NULL)
	{
	    if(N == N->parent->lchild)
	    {
		++(N->parent->balance_factor);
		if(N->parent->balance_factor == 2)
		{
		    break;
		}
		else if(N->parent->balance_factor == 0 && N->parent->parent != NULL 
			&& N->parent == N->parent->parent->rchild /*&& N == N->parent->lchild &&*/
			&& N->parent->parent->balance_factor == -1)
		{
		    LINE_DEBUG("++stop,����Ҫ��������");
		    return true;
		}
	    }
	    else
	    {
		--(N->parent->balance_factor);
		if(N->parent->balance_factor == -2)
		{
		    break;
		}
		else if(N->parent->balance_factor == 0 && N->parent->parent != NULL
			&& N->parent == N->parent->parent->lchild /*&& N == N->parent->rchild &&*/
			&& N->parent->parent->balance_factor == 1)
		{
		    LINE_DEBUG("--stop,����Ҫ��������");
		    return true;
		}
	    }

	    N = N->parent;
	}

	//���ڲ�ƽ��Ľڵ�N->parent
	//ע���ʱN�ĸ߶��Ѿ���Parent_Is_Unbalance�и��¹��ˣ�����ԭ����ֵ��
	if(N->parent != NULL)
	{
	    LINE_DEBUG("unbalance node element is %d",N->parent->element);
	    if(e < N->element && N->element < N->parent->element)
	    {
		LINE_DEBUG("������ת");
		/* 1.ע��߶ȸ��µ�˳����ת����ڵ�Ĺ�ϵ�ͱ���
		 * 2.��1����Ϊe��N���������У���ʱN��ƽ����������Parent_Is_Unbalance
		 *   ��(++balance_factor)���ֵ
		 * 3.��ƽ��ڵ��ƽ��������ԭֵ��Ϊ0������仯ֵ���ڸ���
		 *   N->parent->...->root�ڵ��ƽ������
		 */
		int F_C = (N->parent->balance_factor - 1);
		int F_A = (N->balance_factor - 1);
		N->parent->balance_factor = F_C - F_A - 1;
		AVL_Node_Roll(forest_node,N,RIGHT);
		N->balance_factor = 0;
	    }
	    else if(e > N->element && N->element > N->parent->element)
	    {
		LINE_DEBUG("������ת");
		int F_C = N->parent->balance_factor + 1;
		int F_B = N->balance_factor + 1;
		N->parent->balance_factor = F_C - F_B + 1;;
		AVL_Node_Roll(forest_node,N,LEFT);
		N->balance_factor = 0;
	    }
	    else if(e < N->element && N->element > N->parent->element)
	    {
		LINE_DEBUG("������ת�ٵ�����ת");
		P_AVLNode Bl = N->lchild;
		/* ԭC B Bl�ڵ��ƽ������
		 * ���¹�ʽ���Ƶ��μ�����˵��
		 * ���e��Bll�ϣ�Bll��ת����ΪC����������F_CҪ��Ӧ-1�����e��Blr�ϣ�Blr��ת���ΪB��
		 * ��������F_BҪ��Ӧ+1��
		 */
		int F_C = N->parent->balance_factor + 1;
		int F_B = N->balance_factor - 1;
		int F_Bl = (e < Bl->element) ? (Bl->balance_factor - 1) : (Bl->balance_factor + 1);
		//���¸߶�
		if(e < Bl->element)
		{
		    N->parent->balance_factor =  F_C + 2 - 1;
		    N->balance_factor = -1 - F_Bl;
		}
		else
		{
		    N->parent->balance_factor = F_C + 2 - F_Bl;
		    //-1 + 1 = 0
		    N->balance_factor = 0;
		}
		//��ת
		AVL_Node_Roll(forest_node,Bl,RIGHT);
		AVL_Node_Roll(forest_node,Bl,LEFT);
		Bl->balance_factor = 0;
	    }
	    else if(e > N->element && N->element < N->parent->element)
	    {
		LINE_DEBUG("������ת�ٵ�����ת");
		P_AVLNode Ar = N->rchild;
		int F_C = N->parent->balance_factor - 1;
		int F_A = N->balance_factor + 1;
		int F_Ar = (e < Ar->element) ? (Ar->balance_factor - 1) : (Ar->balance_factor + 1);
		if(e < Ar->element)
		{
		    N->parent->balance_factor = F_C - F_Ar - 2;
		    N->balance_factor = 0;
		}
		else
		{
		    N->parent->balance_factor = F_C - 1;
		    N->balance_factor = 1 - F_Ar;
		}
		
		AVL_Node_Roll(forest_node,Ar,LEFT);
		AVL_Node_Roll(forest_node,Ar,RIGHT);
		Ar->balance_factor = 0;
	    }
	}
    }
    /*�����ܳ��ֲ�ƽ��ĵ㣬ֻ����¸߶�
     *��temp_parentΪN��N��balance_factor!=0����N�϶���һ���ӽڵ�Nc����root->...->N->Nc��·��
     *һ����N�������·�����²���e������e->N->...->root�������Nc->N->...->root��ƽ����ˣ���
     *��N�⣬N֮�ϵĸ��ڵ��ƽ�����Ӳ���Ҫ����
     */
    else
    {
	N->balance_factor = N->balance_factor + ((e < N->element) ? (1) : (-1));
    }
    return true;
}

/*
 * ɾ��
 * forest_node AVLɭ�ֽڵ� e Ҫɾ���Ľڵ�element
 * 1.ɾ���ĵ���Ȩ��·����ʱ��ƽ�����ӿ϶�Ҫһ·���µ�root������Ȩ��·���ϣ���Ȩ��·��Ҫô����
 *   ��ȣ�Ҫô�����1�����ʱ����ɾ��һ����ֻ����¸��ڵ�ƽ�����ӣ���1ʱ��ɾ��һ�������Ȼ��
 *   ��ʧ�⣬��ת���¸��ڵ�ĸ߶�Ҳ��Ȼ��ԭ����1������Ҫ�������ϸ���ƽ�����ӡ�
 *
 *
 */
bool AVL_Delete(P_AVL_Forest_Node forest_node,ElementType e)
{
    if(forest_node == NULL)
    {
	LINE_DEBUG("AVL Forest is NULL");
	return false;
    }
    if(forest_node->root == NULL)
    {
	LINE_DEBUG("AVL Tree is NULL");
	return false;
    }

    P_AVLNode N = AVL_Search(forest_node->root,e);
    if(N->element != e)
    {
	LINE_DEBUG("The element is not in the AVL Tree");
	return false;
    }
    //Ѱ������Ҫɾ���ĵ�
    if(N->lchild != NULL && N->rchild == NULL)
    {
	N->element = N->lchild->element;
	N = N->lchild;
    }
    else if(N->lchild == NULL && N->rchild != NULL)
    {
	N->element = N->rchild->element;
	N = N->rchild;
    }
    else if(N->lchild != NULL && N->rchild != NULL)
    {
	P_AVLNode real = N->rchild;
	while(real->lchild != NULL){ real = real->lchild; }
	N->element = real->element;
	//��Ҫɾ���Ľڵ�ֻ(����)��һ�����ӽڵ�
	if(real->rchild != NULL)
	{
	    real->element = real->rchild->element;
	    real = real->rchild;
      	}
	N = real;
    }
    LINE_DEBUG("Real Delete Node is %d",N->element);
    
    //ֻ��һ�����ڵ�
    if(N->parent == NULL)
    {
	SAFE_FREE(N);
	forest_node->root = NULL;
    }
    else
    {
	/*���ڵ������Ҫô��ȣ�Ҫô���1��
	 * ��ȵĻ������¸��ڵ㼴�ɣ�Ȩ��·����Ϊ���ڵ����һ֧·��
	 * ���1ɾ����Ҫô��2��תƽ�⣬Ҫôһ·���µ����ڵ�
	 */
	if(N->parent->balance_factor == 0)
	{
	    LINE_DEBUG("N->parent->balance_factor == 0��ֻ����¸��ڵ�");
	    if(N == N->parent->lchild)
	    { 
		N->parent->lchild = NULL;
		--(N->parent->balance_factor);
	    }
	    else
	    { 
		N->parent->rchild = NULL;
		++(N->parent->balance_factor);
	    }
	    SAFE_FREE(N);
	}
	else
	{
	    P_AVLNode free_node = N;
	    P_AVLNode S = NULL;
	    P_AVLNode roll_node = NULL;
	    while(N->parent != NULL)
	    {
		//����ƽ������
		(N == N->parent->lchild) ? (--(N->parent->balance_factor)) 
		                         : (++(N->parent->balance_factor));
		/* ���ڲ�ƽ�����1
		 * ==2 ˵�� N == N->parent->rchild
		 */
		if(N->parent->balance_factor == 2 )
		{
		    S = N->parent->lchild;
		    //˫��ת
		    if(S->balance_factor == -1)
		    {
			LINE_DEBUG("����ѡ���ٵ�����ת");
			roll_node = S->rchild;
			//����ƽ������
			if(roll_node->balance_factor >= 0)
			{
			    S->balance_factor = 0;
			    N->parent->balance_factor = roll_node->balance_factor;
			}
			else
			{
			    S->balance_factor = 1;
			    N->parent->balance_factor = 0;
			}
			roll_node->balance_factor = 0;

			AVL_Node_Roll(forest_node,roll_node,LEFT);
			AVL_Node_Roll(forest_node,roll_node,RIGHT);
			//��������
			N = roll_node;
		    }
		    else
		    {
			LINE_DEBUG("������ת");
			AVL_Node_Roll(forest_node,S,RIGHT);
			/*����ƽ�����ӣ�
			 * S������һ���������
			 * ����ת��S��һ��������������ȣ�������һ��û�У���˿���ֹͣ���ϸ���
			 */
			if(S->balance_factor == 0)
			{
			    //F_C = ����F_C - 1 = 2 - 1;
			    N->parent->balance_factor = 1;
			    S->balance_factor = -1;
			    //ֹͣ����
			    break;
			}
			else if(S->balance_factor == 1)
			{
			    //F_C = ����F_C - ԭF_S - 1 = 2 - 1 - 1;
			    N->parent->balance_factor = 0;
			    S->balance_factor = 0;
			    //��������
			    N = S;
			}
		    }
		}
		/*���ڲ�ƽ�����2*/
		else if(N->parent->balance_factor == -2)
		{
		    S = N->parent->rchild;
		    if(S->balance_factor == 1)
		    {
			LINE_DEBUG("������ת�ٵ�����ת");
			roll_node = S->lchild;
			//����ƽ������
			if(roll_node->balance_factor >= 0)
			{
			    S->balance_factor = -(roll_node->balance_factor);
			    N->parent->balance_factor = 0;
			}
			else
			{
			    S->balance_factor = 0;
			    N->parent->balance_factor = 1;
			}
			roll_node->balance_factor = 0;

			AVL_Node_Roll(forest_node,roll_node,RIGHT);
			AVL_Node_Roll(forest_node,roll_node,LEFT);
			//��������
			N = roll_node;
		    }
		    else
		    {
			LINE_DEBUG("������ת");
			AVL_Node_Roll(forest_node,S,LEFT);
			//����ƽ������
			if(S->balance_factor == 0)
			{
			    //F_C = ��F_C + 1 = -2 + 1;
			    N->parent->balance_factor = -1;
			    S->balance_factor = 1;
			    //ֹͣ����
			    break;
			}
			else if(S->balance_factor == -1)
			{
			    //F_C = ��F_C - ԭF_S + 1 = -2 - (-1) + 1;
			    N->parent->balance_factor = 0;
			    S->balance_factor = 1;
			    //��������
			    N = S;
			}
		    }
		}
		else if(N == N->parent->lchild && N->parent->balance_factor == -1)
		{
		    /*��lchild��ɾ��һ�����Ȩ��·�������rchild�ϣ�ֹͣ����*/
		    break;
		}
		else if(N == N->parent->rchild && N->parent->balance_factor == 1)
		{
		    /*��rchild��ɾ��һ�����Ȩ��·�������lchild�ϣ�ֹͣ����*/
		    break;
		}
		//��ʧ����N�Դ���Ȩ��·���ϣ��������ϸ���ƽ������
		else
		{
		    N = N->parent;
		}
	    }/*while(N->parent != NULL) end*/
	    
	    if(free_node == free_node->parent->lchild){ free_node->parent->lchild = NULL; } 
	    else { free_node->parent->rchild = NULL; }
	    SAFE_FREE(free_node);
	}/*if(N->parent->balance_factor == 0) end*/
    }/*if(N->parent == NULL) end*/
}

void AVL_Show(AVL_Tree root)
{
    if(root == NULL)
    {
	//LINE_DEBUG("AVL Tree is NULL");
	return;
    }
    printf("element=%d--balance_factor=%d\n",root->element,root->balance_factor);
    AVL_Show(root->lchild);
    AVL_Show(root->rchild);
}

void Special_Show(AVL_Tree root)
{
    if(root == NULL)
    {
	//LINE_DEBUG("AVL Tree is NULL");
	return;
    }
    printf("element=%d--balance_factor=%d\n",root->element,root->balance_factor);
    P_AVLNode child = NULL;
    
    int i = 0;
    while(i < 2)
    {
	Special_Show(root->lchild);
	root->lchild = root->rchild;
	++i;
    }
}

void AVL_Free(AVL_Tree root)
{
    if(root == NULL)
    {
	//LINE_DEBUG("AVL Tree is NULL");
	return;
    }
    AVL_Free(root->lchild);
    AVL_Free(root->rchild);
    SAFE_FREE(root);
}





int main()
{
    AVL_Forest_Node AVL_Forest[5];
    AVL_Forest[0].root = NULL;
    AVL_Forest[0].count = 0;
    
    //����
    printf("Insert 100-------------------\n");
    AVL_Insert(&(AVL_Forest[0]),100);
    AVL_Show(AVL_Forest[0].root);
    printf("Insert 10--------------------\n");
    AVL_Insert(&(AVL_Forest[0]),10);
    AVL_Show(AVL_Forest[0].root);
    printf("Insert 50-------------------\n");
    AVL_Insert(&(AVL_Forest[0]),50);
    AVL_Show(AVL_Forest[0].root);
    printf("Insert 40-------------------\n");
    AVL_Insert(&(AVL_Forest[0]),40);
    AVL_Show(AVL_Forest[0].root);
    printf("Insert 150-------------------\n");
    AVL_Insert(&(AVL_Forest[0]),150);
    AVL_Show(AVL_Forest[0].root);
    printf("Insert 175-------------------\n");
    AVL_Insert(&(AVL_Forest[0]),175);
    AVL_Show(AVL_Forest[0].root);
    printf("Insert 25-------------------\n");
    AVL_Insert(&(AVL_Forest[0]),25);
    AVL_Show(AVL_Forest[0].root);
    printf("Insert 60-------------------\n");
    AVL_Insert(&(AVL_Forest[0]),60);
    AVL_Show(AVL_Forest[0].root);
    printf("Insert 90-------------------\n");
    AVL_Insert(&(AVL_Forest[0]),90);
    AVL_Show(AVL_Forest[0].root);
    printf("Insert 70-------------------\n");
    AVL_Insert(&(AVL_Forest[0]),70);
    AVL_Show(AVL_Forest[0].root);
    printf("Insert 75-------------------\n");
    AVL_Insert(&(AVL_Forest[0]),75);
    AVL_Show(AVL_Forest[0].root);

/*
 *                              100
 *                        /              \
 *                   50                     150
 *              /        \              /           \
 *             25         75           125            175
 *          /     \     /    \       /     \         /     \
 *        10      40   60    90     110    135      160    190
 *       /  \    / \   / \   /  \   /  \    /  \    /  \   /  \
 *      5   15  30 45 55 65 85  95 105 115 130 140 155 165 180 200
 */
    P_AVLNode node100 = CreateAVLNode(100); P_AVLNode node50  = CreateAVLNode(50);
    P_AVLNode node150 = CreateAVLNode(150); P_AVLNode node25  = CreateAVLNode(25);
    P_AVLNode node75  = CreateAVLNode(75);  P_AVLNode node125 = CreateAVLNode(125);
    P_AVLNode node175 = CreateAVLNode(175); P_AVLNode node10  = CreateAVLNode(10);
    P_AVLNode node40  = CreateAVLNode(40);  P_AVLNode node60  = CreateAVLNode(60);
    P_AVLNode node90  = CreateAVLNode(90);  P_AVLNode node110 = CreateAVLNode(110);
    P_AVLNode node135 = CreateAVLNode(135); P_AVLNode node160 = CreateAVLNode(160);
    P_AVLNode node190 = CreateAVLNode(190); P_AVLNode node5   = CreateAVLNode(5);
    P_AVLNode node15  = CreateAVLNode(15);  P_AVLNode node30  = CreateAVLNode(30);
    P_AVLNode node45  = CreateAVLNode(45);  P_AVLNode node55  = CreateAVLNode(55);
    P_AVLNode node65  = CreateAVLNode(65);  P_AVLNode node85  = CreateAVLNode(85);
    P_AVLNode node95  = CreateAVLNode(95);  P_AVLNode node105 = CreateAVLNode(105);
    P_AVLNode node115 = CreateAVLNode(115); P_AVLNode node130 = CreateAVLNode(130);
    P_AVLNode node140 = CreateAVLNode(140); P_AVLNode node155 = CreateAVLNode(155);
    P_AVLNode node165 = CreateAVLNode(165); P_AVLNode node180 = CreateAVLNode(180);
    P_AVLNode node200 = CreateAVLNode(200);
    node100->lchild = node50;  node50->parent  = node100;
    node100->rchild = node150; node150->parent = node100;
    node50->lchild  = node25;  node25->parent  = node50;
    node50->rchild  = node75;  node75->parent  = node50;
    node150->lchild = node125; node125->parent = node150;
    node150->rchild = node175; node175->parent = node150;
    node25->lchild  = node10;  node10->parent  = node25;
    node25->rchild  = node40;  node40->parent  = node25;
    node75->lchild  = node60;  node60->parent  = node75;
    node75->rchild  = node90;  node90->parent  = node75;
    node125->lchild = node110; node110->parent = node125;
    node125->rchild = node135; node135->parent = node125;
    node175->lchild = node160; node160->parent = node175;
    node175->rchild = node190; node190->parent = node175;
    node10->lchild  = node5;   node5->parent   = node10;
    node10->rchild  = node15;  node15->parent  = node10;
    node40->lchild  = node30;  node30->parent  = node40;
    node40->rchild  = node45;  node45->parent  = node40;
    node60->lchild  = node55;  node55->parent  = node60;
    node60->rchild  = node65;  node65->parent  = node60;
    node90->lchild  = node85;  node85->parent  = node90;
    node90->rchild  = node95;  node95->parent  = node90;
    node110->lchild = node105; node105->parent = node110;
    node110->rchild = node115; node115->parent = node110;
    node135->lchild = node130; node130->parent = node135;
    node135->rchild = node140; node140->parent = node135;
    node160->lchild = node155; node155->parent = node160;
    node160->rchild = node165; node165->parent = node160;
    node190->lchild = node180; node180->parent = node190;
    node190->rchild = node200; node200->parent = node190;

    AVL_Forest[1].root = node100;
    
    printf("delete 125----------\n");
    AVL_Delete(&(AVL_Forest[1]),125);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 160----------\n");
    AVL_Delete(&(AVL_Forest[1]),160);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 175----------\n");
    AVL_Delete(&(AVL_Forest[1]),175);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 60----------\n");
    AVL_Delete(&(AVL_Forest[1]),60);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 90----------\n");
    AVL_Delete(&(AVL_Forest[1]),90);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 75----------\n");
    AVL_Delete(&(AVL_Forest[1]),75);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 55----------\n");
    AVL_Delete(&(AVL_Forest[1]),55);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 65----------\n");
    AVL_Delete(&(AVL_Forest[1]),65);
    printf("delete 200----------\n");
    AVL_Delete(&(AVL_Forest[1]),200);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 110----------\n");
    AVL_Delete(&(AVL_Forest[1]),110);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 165----------\n");
    AVL_Delete(&(AVL_Forest[1]),165);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 150----------\n");
    AVL_Delete(&(AVL_Forest[1]),150);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 45----------\n");
    AVL_Delete(&(AVL_Forest[1]),45);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 15----------\n");
    AVL_Delete(&(AVL_Forest[1]),15);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 10----------\n");
    AVL_Delete(&(AVL_Forest[1]),10);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 190----------\n");
    AVL_Delete(&(AVL_Forest[1]),190);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 180----------\n");
    AVL_Delete(&(AVL_Forest[1]),180);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 140----------\n");
    AVL_Delete(&(AVL_Forest[1]),140);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 135----------\n");
    AVL_Delete(&(AVL_Forest[1]),135);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 155----------\n");
    AVL_Delete(&(AVL_Forest[1]),155);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 100----------\n");
    AVL_Delete(&(AVL_Forest[1]),100);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 130----------\n");
    AVL_Delete(&(AVL_Forest[1]),130);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 105----------\n");
    AVL_Delete(&(AVL_Forest[1]),105);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 115----------\n");
    AVL_Delete(&(AVL_Forest[1]),115);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 25----------\n");
    AVL_Delete(&(AVL_Forest[1]),25);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 40----------\n");
    AVL_Delete(&(AVL_Forest[1]),40);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 5----------\n");
    AVL_Delete(&(AVL_Forest[1]),5);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 30----------\n");
    AVL_Delete(&(AVL_Forest[1]),30);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 50----------\n");
    AVL_Delete(&(AVL_Forest[1]),50);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 85----------\n");
    AVL_Delete(&(AVL_Forest[1]),85);
    AVL_Show(AVL_Forest[1].root);
    printf("delete 95----------\n");
    AVL_Delete(&(AVL_Forest[1]),95);
    AVL_Show(AVL_Forest[1].root);
    
    //������
    AVL_Free(AVL_Forest[0].root);
    AVL_Free(AVL_Forest[1].root);

    return 0;
}
