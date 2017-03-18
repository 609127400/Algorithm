/*
 *                     ��չ��
 * 1.���������ݵľֲ��ԣ������η��ʵ����ݣ����п������´λ�����ٴ���Ҫ�����ʡ�
 *   ����ڷ���һ������֮�󣬾ͽ�������ͨ����ת�������͵����ڵ㡣������ʹ���У�
 *   ���������ʵ������𽥱����õ�����ǳ��ش���
 * 2.�����Ļ��������ĵ����͵����ڵ㣬����Ļ�������ĵ����͵����ڵ㣬ɾ���Ļ�
 *   ��ɾ����ĸ��ڵ����͵����ڵ㡣
 * 2.��չ������ת��ͨ���򵥵ĵ���ת��˫��ת���ԴﵽĿ�ģ���avl���е���תһ�£�
 *   ��һ���ڵ�һ��һ�����ϲ����ͣ����մﵽ���ڵ㡣���ǵ���ת��ʹ�ô������
 *   ����������չ���ĵ���ת���ã�����תN�ĸ��ף�Ȼ������תN�ڵ�ķ�ʽ������
 *   ��ֱ�Ӿ���תN�ڵ㣬������ת��ʽ��Ϊ ˫����չ���磺
 *       G              P              N
 *      / \            / \              \
 *     P   Gr  -->    N   G     -->      P
 *    / \                / \              \
 *   N   S               S  Gr             G
 *   ���������ĵ���ת�Ļ�������N���⣬��Ҫż�������������Ľ��������ת��������
 *   N��ֻ��������Ļ��������һ���ü򵥵ĵ�ѭ�����ɡ����⣬˫��ת(zig-zag/zag-
 *   zig)���䡣
 * 3.��չ�����ɱ���logn�����ܡ����Ǵ�����avl������洢�߶Ȼ�ƽ�����ӵ����ơ�
 *
 *
 */

#define _DEBUG_CLOSE_
#include "../PublicForAlgorithms.h"

typedef int ElementType;

typedef enum{LEFT,RIGHT}Roll_Direction;

typedef struct Node
{
    ElementType element;
    struct Node* parent;
    struct Node* lchild;
    struct Node* rchild;
}STNode,*P_STNode,*STree;

typedef struct
{
    P_STNode root;
    int count;
}STForest_Node,*P_ST_Forest_Node;

/*
 * ����һ���ڵ�
 */
P_STNode CreateSTNode(ElementType e)
{
    P_STNode new_node = (P_STNode)malloc(sizeof(STNode));
    if(new_node == NULL){ return NULL; }
    new_node->element = e;   new_node->parent = NULL;
    new_node->lchild = NULL; new_node->rchild = NULL;
    return new_node;
}

/*
 * ��ת����
 */
void STNode_Roll(P_ST_Forest_Node forest_node,P_STNode C,Roll_Direction d)
{
    if(C->parent == NULL) return;
    P_STNode G = C->parent->parent;
    P_STNode P = C->parent;
    P_STNode S = (C == P->lchild) ? P->rchild : P->lchild;
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
 * splay����
 * forest_node ��չ��ɭ�ֽڵ㣬��Ϊ�漰����ת�͸��ڵ���²���
 * N��Ҫ���͵����ڵ�ĵ� 
 */
bool ST_Splay(P_ST_Forest_Node forest_node,P_STNode N)
{
    if(forest_node == NULL || forest_node->root == NULL)
    {
	LINE_DEBUG("Splay Tree is NULL");
	return false;
    }
    if(N == NULL)
    {
	LINE_DEBUG("N is NULL");
	return false;
    }
    //���ڵ㲻������ֱ�ӷ���
    if(N->parent == NULL){ return true; }
    P_STNode G = NULL;
    P_STNode P = NULL;

    while(N->parent != NULL)
    {
	//��ת֮���൱��ѭ����������
	G = N->parent->parent;
	P = N->parent;
	if(G == NULL)
	{
	    //�򵥵ĵ���ת
	    if(N == P->lchild)
	    {
	       //zig
	       STNode_Roll(forest_node,N,RIGHT);
	    }
	    else
	    {
		//zag
		STNode_Roll(forest_node,N,LEFT);
	    }
	}
	else if(N == P->lchild && P == G->lchild)
	{
	    //˫����չ-R
	    STNode_Roll(forest_node,P,RIGHT);
	    STNode_Roll(forest_node,N,RIGHT);
	}
	else if(N == P->rchild && P == G->rchild)
	{
	    //˫����չ-L
	    STNode_Roll(forest_node,P,LEFT);
	    STNode_Roll(forest_node,N,LEFT);
	}
	else if(N == P->lchild && P == G->rchild)
	{
	    //zig-zag
	    STNode_Roll(forest_node,N,RIGHT);
	    STNode_Roll(forest_node,N,LEFT);
	}
	else if(N == P->rchild && P == G->lchild)
	{
	    //zag-zig
	    STNode_Roll(forest_node,N,LEFT);
	    STNode_Roll(forest_node,N,RIGHT);
	}
    }
    return true;
}

/*
 * ����
 * 1.��������ɹ����򷵻����ص��Ľڵ㣬�������ʧ�ܣ��򷵻������ʵĽڵ㡣
 *   �п��ܷ���NULLֵ
 */
P_STNode ST_Search(P_ST_Forest_Node forest_node,ElementType e)
{
    if(forest_node == NULL || forest_node->root == NULL)
    { LINE_DEBUG("Splay Tree is NULL"); return NULL; }

    P_STNode root = forest_node->root;
    P_STNode temp_parent = NULL;
    while(root != NULL)
    {
	temp_parent = root;
	if(e < root->element)
	{ root = root->lchild; }
	else if(e > root->element)
	{ root = root->rchild; }
	else if(e == root->element)
	{
	    ST_Splay(forest_node,root);
	    return root;
	}
    }
    return temp_parent;
}

/*
 * ��չ���������
 */
bool ST_Insert(P_ST_Forest_Node forest_node,ElementType e)
{
    if(forest_node == NULL || forest_node->root == NULL)
    {
	LINE_DEBUG("Splay Tree is NULL");
	return false;
    }
    
    P_STNode temp_parent = ST_Search(forest_node,e);
    if(temp_parent == NULL || temp_parent->element == e)
    {
	LINE_DEBUG("Search Failed or The Element has been in the Splay Tree");
	return false;
    }

    P_STNode new_node = CreateSTNode(e);
    if(new_node == NULL){ LINE_DEBUG("Insert malloc failed"); return false; }
    if(e < temp_parent->element){ temp_parent->lchild = new_node; }
    else{ temp_parent->rchild = new_node; }
    new_node->parent = temp_parent;

    //��չ����
    ST_Splay(forest_node,new_node);
    return true;
}

/*
 * ��չ��ɾ������
 * 1.��ʹ��ST_Search
 * 2.ʹ������������ֵ����
 */
bool ST_Delete(P_ST_Forest_Node forest_node,ElementType e)
{
    if(forest_node == NULL || forest_node->root == NULL)
    {
	LINE_DEBUG("Splay Tree is NULL");
	return false;
    }
    
    P_STNode delete_node = forest_node->root;
    while(delete_node != NULL)
    {
	if(e < delete_node->element){ delete_node = delete_node->lchild; }
	else if(e > delete_node->element){ delete_node = delete_node->rchild; }
	else if(e == delete_node->element){ break; }
    }
    if(delete_node == NULL)
    {
	LINE_DEBUG("The Element is not in Splay Tree");
	return false;
    }
    
    //��delete_nodeΪ���ڵ�ʱ��splay_nodeΪ��
    P_STNode splay_node  = delete_node->parent;
    //�������أ���ʱ���д���e
    //��������Ϊ����������Ϊ��
    if(delete_node->lchild != NULL && delete_node->rchild == NULL)
    {
	if(delete_node->parent == NULL)
	{
	    forest_node->root = delete_node->lchild;
	    delete_node->lchild->parent = NULL;
	}
	else
	{
	    if(delete_node == delete_node->parent->lchild)
	    { delete_node->parent->lchild = delete_node->lchild; }
	    else
	    { delete_node->parent->rchild = delete_node->lchild; } 
	    delete_node->lchild->parent = delete_node->parent;
	}
	LINE_DEBUG("Real Delete is %d",delete_node->element);
	SAFE_FREE(delete_node);
    }
    //��������Ϊ��
    else if(delete_node->rchild != NULL)
    {
	P_STNode real_node = delete_node->rchild;
	while(real_node->lchild != NULL){ real_node = real_node->lchild; }
	delete_node->element = real_node->element;
	if(real_node == real_node->parent->lchild)
	{ real_node->parent->lchild = real_node->rchild; }
	else
	{ real_node->parent->rchild = real_node->rchild; }
	if(real_node->rchild != NULL){ real_node->rchild->parent = real_node->parent; }
	LINE_DEBUG("Real Delete is %d",real_node->element);
	SAFE_FREE(real_node);
    }
    //����������ΪNULL
    else
    {
	//ֻ��һ�����ڵ��ʱ��
	if(delete_node->parent == NULL)
	{ forest_node->root = NULL; }
	else
	{ 
	    if(delete_node == delete_node->parent->lchild)
	    { delete_node->parent->lchild = NULL; } 
	    else
	    { delete_node->parent->rchild = NULL; }
	}	
	SAFE_FREE(delete_node);
    }
    //��չ����
    ST_Splay(forest_node,splay_node);
}

//��ʾ
void ST_Show(STree root)
{
    if(root == NULL){ /*LINE_DEBUG("Splay Tree is NULL");*/ return;}
    
    printf("%d ",root->element);
    if(root->lchild == NULL){ printf("lchild - NULL "); }else { printf("lchild - %d ",root->lchild->element); }
    if(root->rchild == NULL){ printf("rchild - NULL"); }else { printf("rchild - %d",root->rchild->element); }
    printf("\n");

    ST_Show(root->lchild);
    ST_Show(root->rchild);
}

//�ͷ�
void ST_Free(STree root)
{
    if(root == NULL){ /*LINE_DEBUG("Splay Tree is NULL");*/ return; }
    ST_Free(root->lchild);
    ST_Free(root->rchild);
    SAFE_FREE(root);
}

int main()
{
/*
 *                              100
 *                        /             \
 *                      50               150
 *                       \                /
 *                        75             125
 *                      /    \             \
 *                     60    90            135
 *                    / \   /  \           /  \
 *                   55 65 85  95        130 140 
 */
    P_STNode node100 = CreateSTNode(100); P_STNode node50  = CreateSTNode(50);
    P_STNode node150 = CreateSTNode(150); P_STNode node125 = CreateSTNode(125);
    P_STNode node75  = CreateSTNode(75);  P_STNode node60  = CreateSTNode(60);
    P_STNode node90  = CreateSTNode(90);  P_STNode node135 = CreateSTNode(135); 
    P_STNode node55  = CreateSTNode(55);  P_STNode node85  = CreateSTNode(85);
    P_STNode node65  = CreateSTNode(65);  P_STNode node95  = CreateSTNode(95);  
    P_STNode node130 = CreateSTNode(130); P_STNode node140 = CreateSTNode(140);

    node100->lchild = node50;  node50->parent  = node100;
    node100->rchild = node150; node150->parent = node100;
    node50->rchild  = node75;  node75->parent  = node50;
    node150->lchild = node125; node125->parent = node150;
    node75->lchild  = node60;  node60->parent  = node75;
    node75->rchild  = node90;  node90->parent  = node75;
    node125->rchild = node135; node135->parent = node125;
    node60->lchild  = node55;  node55->parent  = node60;
    node60->rchild  = node65;  node65->parent  = node60;
    node90->lchild  = node85;  node85->parent  = node90;
    node90->rchild  = node95;  node95->parent  = node90;
    node135->lchild = node130; node130->parent = node135;
    node135->rchild = node140; node140->parent = node135;
    
    STForest_Node ST_Forest[5];
    ST_Forest[0].root = node100;

    printf("Search 105---------------\n");
    ST_Search(&(ST_Forest[0]),105);
    ST_Show(ST_Forest[0].root);
    printf("Insert 180---------------\n");
    ST_Insert(&(ST_Forest[0]),180);
    ST_Show(ST_Forest[0].root);

    printf("Delete 150--------------\n");
    ST_Delete(&(ST_Forest[0]),150);
    ST_Show(ST_Forest[0].root);
    printf("Delete 50--------------\n");
    ST_Delete(&(ST_Forest[0]),50);
    ST_Show(ST_Forest[0].root);
    printf("Delete 65--------------\n");
    ST_Delete(&(ST_Forest[0]),65);
    ST_Show(ST_Forest[0].root);
    printf("Delete 90--------------\n");
    ST_Delete(&(ST_Forest[0]),90);
    ST_Show(ST_Forest[0].root);
    printf("Delete 75--------------\n");
    ST_Delete(&(ST_Forest[0]),75);
    ST_Show(ST_Forest[0].root);
    printf("Delete 100--------------\n");
    ST_Delete(&(ST_Forest[0]),100);
    ST_Show(ST_Forest[0].root);
    printf("Delete 130--------------\n");
    ST_Delete(&(ST_Forest[0]),130);
    ST_Show(ST_Forest[0].root);
    printf("Delete 85--------------\n");
    ST_Delete(&(ST_Forest[0]),85);
    ST_Show(ST_Forest[0].root);
    printf("Delete 140--------------\n");
    ST_Delete(&(ST_Forest[0]),140);
    ST_Show(ST_Forest[0].root);
    printf("Delete 55--------------\n");
    ST_Delete(&(ST_Forest[0]),55);
    ST_Show(ST_Forest[0].root);
    printf("Delete 60--------------\n");
    ST_Delete(&(ST_Forest[0]),60);
    ST_Show(ST_Forest[0].root);
    printf("Delete 75--------------\n");
    ST_Delete(&(ST_Forest[0]),75);
    ST_Show(ST_Forest[0].root);
    printf("Delete 125--------------\n");
    ST_Delete(&(ST_Forest[0]),125);
    ST_Show(ST_Forest[0].root);
    printf("Delete 135--------------\n");
    ST_Delete(&(ST_Forest[0]),135);
    ST_Show(ST_Forest[0].root); 
    printf("Delete 95--------------\n");
    ST_Delete(&(ST_Forest[0]),95);
    ST_Show(ST_Forest[0].root);


    //������
    ST_Free(ST_Forest[0].root);

    return 0;
}
