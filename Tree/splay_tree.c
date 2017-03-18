/*
 *                     伸展树
 * 1.利用了数据的局部性，即当次访问的数据，极有可能在下次或近期再次需要被访问。
 *   因此在访问一个数据之后，就将此数据通过旋转操作移送到根节点。这样在使用中，
 *   经常被访问的数据逐渐被放置到树的浅层地带。
 * 2.搜索的话将搜索的点移送到根节点，插入的话将插入的点移送到根节点，删除的话
 *   将删除点的父节点移送到根节点。
 * 2.伸展树的旋转，通过简单的单旋转和双旋转可以达到目的，与avl树中的旋转一致，
 *   将一个节点一步一步向上层移送，最终达到根节点。但是单旋转的使用存在最坏的
 *   情况。因此伸展树的单旋转采用，先旋转N的父亲，然后再旋转N节点的方式，而不
 *   是直接就旋转N节点，这种旋转方式成为 双层伸展，如：
 *       G              P              N
 *      / \            / \              \
 *     P   Gr  -->    N   G     -->      P
 *    / \                / \              \
 *   N   S               S  Gr             G
 *   这样操作的单旋转的话，除了N层外，需要偶数曾才能完整的进行如此旋转。但当除
 *   N外只有奇数层的话，则最后一层用简单的单循环即可。另外，双旋转(zig-zag/zag-
 *   zig)不变。
 * 3.伸展树依旧保持logn的性能。但是打破了avl树必须存储高度或平衡因子等限制。
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
 * 创建一个节点
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
 * 旋转操作
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
 * splay操作
 * forest_node 伸展树森林节点，因为涉及到旋转和根节点更新操作
 * N：要移送到根节点的点 
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
    //根节点不做处理，直接返回
    if(N->parent == NULL){ return true; }
    P_STNode G = NULL;
    P_STNode P = NULL;

    while(N->parent != NULL)
    {
	//旋转之后相当于循环条件更新
	G = N->parent->parent;
	P = N->parent;
	if(G == NULL)
	{
	    //简单的单旋转
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
	    //双层伸展-R
	    STNode_Roll(forest_node,P,RIGHT);
	    STNode_Roll(forest_node,N,RIGHT);
	}
	else if(N == P->rchild && P == G->rchild)
	{
	    //双层伸展-L
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
 * 搜索
 * 1.如果搜索成功，则返回搜素到的节点，如果搜索失败，则返回最后访问的节点。
 *   有可能返回NULL值
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
 * 伸展树插入操作
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

    //伸展操作
    ST_Splay(forest_node,new_node);
    return true;
}

/*
 * 伸展树删除操作
 * 1.不使用ST_Search
 * 2.使用右子树最少值策略
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
    
    //当delete_node为根节点时，splay_node为空
    P_STNode splay_node  = delete_node->parent;
    //经过搜素，此时树中存在e
    //左子树不为空且右子树为空
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
    //右子树不为空
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
    //左右子树都为NULL
    else
    {
	//只有一个根节点的时候
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
    //伸展操作
    ST_Splay(forest_node,splay_node);
}

//显示
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

//释放
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


    //清理工作
    ST_Free(ST_Forest[0].root);

    return 0;
}
