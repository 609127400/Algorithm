/*
 *
 *             AVL树
 * 1.只有一条性质：任何一个节点的左子树高度Hl与右子树高度Hr的差不能大于1
 * 2.空树的高度为-1。根节点处的高度为0。节点平衡因子 = 左子树高度 - 右子树高度
 *   节点的高度是其子树最深的一条路径的高度，节点的平衡因子的值是其左右子节点各
 *   自最深路径高度的差。
 * 3.主要是通过旋转来弥补插入或删除造成的高度增减。
 * 4.插入删除要考虑的其中的一点是权重路径：即删除或插入的节点是否在权重路径上。
 *   权重路径：一个节点子树的最深路径。
 * 4.缺点：删除操作的拓扑结构变化达到了logn次，要存储平衡因子或高度，实测性能也
 *   与理论有差距。
 *
 *                                                2016年11月8日
 */

#define _DEBUG_CLOSE_
#include "../PublicForAlgorithms.h"

typedef int ElementType;
/* 其中平衡因子也可以换做为记录该节点子树中最深(高)路径的值
 * 插入节点更新高度的时候要比较子节点的高度值+1是否大于现在
 * 高度，若大于，则更新+1后的较大的值，若不大于，则不更新。
 * 如果是高度的话，在更新高度时更容易。
 */
typedef struct Node
{
    ElementType element;
    struct Node* parent;
    struct Node* lchild;
    struct Node* rchild;
    //平衡因子
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
 * 如果找到，则返回找到的节点，如果未找到，则返回
 * 最后访问的一个节点
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
 * C(-child) 要进行旋转上升的节点
 * d 要旋转的方向 LEFT or RIGHT
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
 * forest_node AVL森林节点，即一棵AVL树
 * e 要插入的节点元素
 * 插入的操作主要有两方面：旋转操作和节点平衡因子的更新
 * 1.插入e前的事实：现有的AVL树是平衡的、插入e到末节点。根据这两个事实进行插入分析。
 * 2.插入e后，若其parent没有另一个子节点，则导致parent平衡因子加或减1，顺带一路向上层
 *   parent->parent->...->root 加减1。直到第一个节点在加减1后变为正负2，这就是需要进
 *   行处理的不平衡点。
 * 3.设插入e后不平衡的点是C，多的一侧的子节点是B，少的一侧的子节点是A，
 *   则C肯定是|Ha-Hb| == 2。
 *   则基本思路就是通过旋转向少的那一侧多加入一个节点。
 *   因此旋转的是C多的那一侧的子节点B，旋转后把C加入到了原A的位置(少的
 *   那一侧)，B到原A的位置。
 * 4.单选转的情形：插入的点与B的关系方向 与 B与C的关系方向一致。如e插入
 *                 到B的左子树，B是C的左子节点。
 *   单选转的方法：将B旋转至A处即可。
 *   双旋转的情形：插入的点与B的关系方向 与 B与A的关系方向相反。如e插入
 *                 到B的左子树，B是A的右子节点。
 *   双旋转的方法：先将B的通向插入节点方向的子节点旋转至B位置，再将新的
 *   B旋转至C位置。
 * 5.单旋转需要更新高度的节点：C B 代替C位置的B->parent->parent->..root
 *   旋转前：
 *                        C               不平衡节点
 *                    /        \
 *                   A         B          H_B - H_A = 1
 *   旋转后：e插入到B的右子树，导致单左旋转
 *                        B                 
 *                    /        \
 *                   C         Br
 *                 /   \
 *               A     Bl
 *  原本B的高度肯定比A的高度大1，经过旋转，B的高度不变，C+A的高度
 *  增1，旋转后B的高度是不变的，因此现在B的平衡因子一定是0。
 *  F_C = H_A - H_Bl 此时最深的路径存在于B-Br方向，H_Bl的高度只能间接表示
 *  H_Bl = H_Br+F_B 因此 F_C = H_A-H_Br-F_B=H_A-H_B+1-F_B = F_C-F_B+1;
 *  单右旋转也可按此方法推算。
 * 6.双旋转需要更新的节点：B B_child C 代替C位置的B_child->parent->...->root，e
 *   插入B的左子节点
 *
 *              C          -->        C            -->        Bl
 *          /       \              /      \                /      \
 *         A         B            A        Bl             C        B
 *                 /   \                  /  \          /   \     /  \
 *               Bl     Br              Bll   B        A    Bll  Blr  Br
 *             /    \                        / \
 *            Bll   Blr                     Blr Br
 *  H表示高度，F表示平衡因子，Bll代表B节点的左儿子的左儿子，Blr则代表B左儿的右儿。
 *  e的插入导致了不平衡且要经过双旋转
 *  F_C = H_A - H_Bll      F_B = H_Blr - H_Br
 *  ①当e插入到Bl的左子树中时，则肯定是B-Bl-Bll方向存在一条最深的路径，此时H_Bll的
 *    值可以直接用H_B-2表示。H_Blr的值，只能间接的用H_Bll - F_Bl = H_B-2-F_Bl表示。
 *    由此，F_C = H_A-(H_B-2)=H_A-H_B+2=F_C+2  F_B=H_B-2-F_Bl-H_Br=1-2-F_Bl = -1-F_Bl;
 *  ②当e插入到Bl的右子树中时，则肯定是B-Bl-Blr方向存在一条最深的路径，此时H_Blr的
 *    值可以直接用H_B-2表示。H_Bll的值，只能间接的用H_Blr + F_Bl = H_B-2+F_Bl表示。
 *    由此，F_C = H_A-(H_B-2+F_Bl)=H_A-H_B+2-F_Bl=F_C+2-F_Bl  F_B=H_B-2 - H_Br=1-2=-1;
 *  ③第一二点都未考虑新插入的e点的影响。相反的镜像双旋转参照此方法推算。
 * 7.C节点的父节点若存在，则C->parent->parent->..->root路径上的平衡因子在旋转后不需要
 *   更新。C的左右子树CL CR，且存在H_CR-H_CL=2，自己可以画三角代表左右子树分析，经过
 *   旋转，整个C还是原来的高度。
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
    //检测元素是否已在树中
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
    //插入元素
    P_AVLNode new_node = CreateAVLNode(e);
    if(new_node == NULL) return false;
    if(e < temp_parent->element)
	temp_parent->lchild = new_node;
    else
	temp_parent->rchild = new_node;
    new_node->parent = temp_parent;
    //旋转平衡并更新高度
    //更新高度时，最初并不真的更新，在旋转后再真正的更新需要更新的高度
    P_AVLNode N = temp_parent;
    if(N->balance_factor == 0)
    {
	if(e < N->element){ ++(N->balance_factor); }
	else{ --(N->balance_factor); }
	
	/*
	 * 向上更新平衡因子
	 * 1.一直更新到根节点但是未出现不平衡点，N->parent == NULL
	 * 2.更新到中途遇到不平衡点，直接break，N->parent != NULL
	 * 3.更新到中途不需要再向上层更新，树也不会失去平衡，直接
	 *   return，此时最深的路径不经过root ->...-> N->parent ->
	 *   N -> e的路径，在N->parent被调整为0后N->parent->e的路径深度
	 *   顶多与最深路径持平，因此上层不需要继续更新。
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
		    LINE_DEBUG("++stop,不需要继续更新");
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
		    LINE_DEBUG("--stop,不需要继续更新");
		    return true;
		}
	    }

	    N = N->parent;
	}

	//存在不平衡的节点N->parent
	//注意此时N的高度已经在Parent_Is_Unbalance中更新过了，不是原来的值了
	if(N->parent != NULL)
	{
	    LINE_DEBUG("unbalance node element is %d",N->parent->element);
	    if(e < N->element && N->element < N->parent->element)
	    {
		LINE_DEBUG("单右旋转");
		/* 1.注意高度更新的顺序，旋转过后节点的关系就变了
		 * 2.减1是因为e在N的左子树中，此时N的平衡因子是在Parent_Is_Unbalance
		 *   中(++balance_factor)后的值
		 * 3.不平衡节点的平衡因子由原值变为0，这个变化值用于更新
		 *   N->parent->...->root节点的平衡因子
		 */
		int F_C = (N->parent->balance_factor - 1);
		int F_A = (N->balance_factor - 1);
		N->parent->balance_factor = F_C - F_A - 1;
		AVL_Node_Roll(forest_node,N,RIGHT);
		N->balance_factor = 0;
	    }
	    else if(e > N->element && N->element > N->parent->element)
	    {
		LINE_DEBUG("单左旋转");
		int F_C = N->parent->balance_factor + 1;
		int F_B = N->balance_factor + 1;
		N->parent->balance_factor = F_C - F_B + 1;;
		AVL_Node_Roll(forest_node,N,LEFT);
		N->balance_factor = 0;
	    }
	    else if(e < N->element && N->element > N->parent->element)
	    {
		LINE_DEBUG("单右旋转再单左旋转");
		P_AVLNode Bl = N->lchild;
		/* 原C B Bl节点的平衡因子
		 * 更新公式的推到参见上文说明
		 * 如果e在Bll上，Bll旋转后将作为C的右子树，F_C要相应-1，如果e在Blr上，Blr旋转后成为B的
		 * 左子树，F_B要相应+1。
		 */
		int F_C = N->parent->balance_factor + 1;
		int F_B = N->balance_factor - 1;
		int F_Bl = (e < Bl->element) ? (Bl->balance_factor - 1) : (Bl->balance_factor + 1);
		//更新高度
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
		//旋转
		AVL_Node_Roll(forest_node,Bl,RIGHT);
		AVL_Node_Roll(forest_node,Bl,LEFT);
		Bl->balance_factor = 0;
	    }
	    else if(e > N->element && N->element < N->parent->element)
	    {
		LINE_DEBUG("单左旋转再单右旋转");
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
    /*不可能出现不平衡的点，只需更新高度
     *设temp_parent为N，N的balance_factor!=0，则N肯定有一个子节点Nc，且root->...->N->Nc的路径
     *一定是N树最深的路径。新插入e，顶多e->N->...->root的深度与Nc->N->...->root持平，因此，除
     *了N外，N之上的父节点的平衡因子不需要更新
     */
    else
    {
	N->balance_factor = N->balance_factor + ((e < N->element) ? (1) : (-1));
    }
    return true;
}

/*
 * 删除
 * forest_node AVL森林节点 e 要删除的节点element
 * 1.删除的点在权重路径上时，平衡因子肯定要一路更新到root，不在权重路径上，则权重路径要么和其
 *   相等，要么比其多1。相等时，则删除一个，只需更新父节点平衡因子，多1时，删除一个，则必然导
 *   致失衡，旋转后新父节点的高度也必然比原来少1，则需要继续向上更新平衡因子。
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
    //寻找真正要删除的点
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
	//当要删除的节点只(可能)有一个右子节点
	if(real->rchild != NULL)
	{
	    real->element = real->rchild->element;
	    real = real->rchild;
      	}
	N = real;
    }
    LINE_DEBUG("Real Delete Node is %d",N->element);
    
    //只有一个根节点
    if(N->parent == NULL)
    {
	SAFE_FREE(N);
	forest_node->root = NULL;
    }
    else
    {
	/*父节点的子树要么相等，要么相差1，
	 * 相等的话，更新父节点即可，权重路径变为父节点的另一支路径
	 * 相差1删除后要么成2旋转平衡，要么一路更新到根节点
	 */
	if(N->parent->balance_factor == 0)
	{
	    LINE_DEBUG("N->parent->balance_factor == 0，只需更新父节点");
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
		//更新平衡因子
		(N == N->parent->lchild) ? (--(N->parent->balance_factor)) 
		                         : (++(N->parent->balance_factor));
		/* 存在不平衡情况1
		 * ==2 说明 N == N->parent->rchild
		 */
		if(N->parent->balance_factor == 2 )
		{
		    S = N->parent->lchild;
		    //双旋转
		    if(S->balance_factor == -1)
		    {
			LINE_DEBUG("单左选择再单右旋转");
			roll_node = S->rchild;
			//更新平衡因子
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
			//继续更新
			N = roll_node;
		    }
		    else
		    {
			LINE_DEBUG("单右旋转");
			AVL_Node_Roll(forest_node,S,RIGHT);
			/*更新平衡因子，
			 * S有两个一样深的子树
			 * 在旋转后，S有一个子树降低了深度，但是另一棵没有，因此可以停止向上更新
			 */
			if(S->balance_factor == 0)
			{
			    //F_C = 现在F_C - 1 = 2 - 1;
			    N->parent->balance_factor = 1;
			    S->balance_factor = -1;
			    //停止更新
			    break;
			}
			else if(S->balance_factor == 1)
			{
			    //F_C = 现在F_C - 原F_S - 1 = 2 - 1 - 1;
			    N->parent->balance_factor = 0;
			    S->balance_factor = 0;
			    //继续更新
			    N = S;
			}
		    }
		}
		/*存在不平衡情况2*/
		else if(N->parent->balance_factor == -2)
		{
		    S = N->parent->rchild;
		    if(S->balance_factor == 1)
		    {
			LINE_DEBUG("单右旋转再单左旋转");
			roll_node = S->lchild;
			//更新平衡因子
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
			//继续更新
			N = roll_node;
		    }
		    else
		    {
			LINE_DEBUG("单左旋转");
			AVL_Node_Roll(forest_node,S,LEFT);
			//更新平衡因子
			if(S->balance_factor == 0)
			{
			    //F_C = 现F_C + 1 = -2 + 1;
			    N->parent->balance_factor = -1;
			    S->balance_factor = 1;
			    //停止更新
			    break;
			}
			else if(S->balance_factor == -1)
			{
			    //F_C = 现F_C - 原F_S + 1 = -2 - (-1) + 1;
			    N->parent->balance_factor = 0;
			    S->balance_factor = 1;
			    //继续更新
			    N = S;
			}
		    }
		}
		else if(N == N->parent->lchild && N->parent->balance_factor == -1)
		{
		    /*在lchild上删除一个点后，权重路径变成在rchild上，停止更新*/
		    break;
		}
		else if(N == N->parent->rchild && N->parent->balance_factor == 1)
		{
		    /*在rchild上删除一个点后，权重路径变成在lchild上，停止更新*/
		    break;
		}
		//不失衡且N仍处在权重路径上，继续向上更新平衡因子
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
    
    //插入
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
    
    //清理工作
    AVL_Free(AVL_Forest[0].root);
    AVL_Free(AVL_Forest[1].root);

    return 0;
}
