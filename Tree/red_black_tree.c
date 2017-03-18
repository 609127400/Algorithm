
/*
 *
 *                           红黑树
 *
 *  1.也是属于自平衡搜索二叉树，插入/删除等操作的时间能够保证在最坏情况下达到O(logn)
 *    自平衡压缩树的深度，使得 最长路径 <= 2*最短路径，使得红黑树趋向于平衡。在树的拓
 *    扑结构方面，AVL树相较于红黑树更平衡，但是红黑树的插入删除操作的拓扑改变都能保证
 *    O(1)
 *  2.五条性质：
 *    ① 所有节点，要么是红色，要么是黑色
 *    ② 根节点必须是黑色
 *    ③ 叶子节点必须是黑色，且为操作方便，叶节点一般不存储数据，用NIL表示
 *    ④ 从任一节点出发，到外部节点的路径中，黑色节点数量相同，注意是从根到外部节点。
 *    ⑤ 若父节点为红色，则其两个子节点必须是黑色，即所有路径中不允许存在连续两个红色
 *       节点的情况，也即若一个节点为红色且有子节点，则必须有两个子节点且为黑色（结合
 *       性质④得出）。
 *
 *  3.根据红黑树的性质，提升每个红节点，使其与其黑色父节点平齐，形成一个超级节点，此时
 *    就相当于一个4阶B树。所以说4阶B树是红黑树的影子。每一棵红黑树的黑高度（只算黑色节
 *    点）就是其对应的B树的高度。
 *
 *  4.增删所需要考虑在增删过程中对红黑树性质的影响，要考虑各种情况，通过对父节点P，
 *    祖父节点G，叔节点U三种节点的变色，旋转来维护。改查则按正常的搜索二叉树进行遍历。
 *
 *  5.NIL哨兵：所有实际存储数据的节点都存在两个子节点。如果某一存储数据的节点只存在
 *    一个子节点或不存在子节点，则用NIL节点补齐。NIL节点只是为了标识当前搜索已到底，
 *    并不存储实际数据，为了不浪费存储空间，一般设置一个NIL哨兵来替换所有的NIL，即所
 *    有指向NIL节点的指针都统一指向NIL哨兵。另外，在增删过程中有向上回溯的过程，为了
 *    方便，也将根节点的父节点指向哨兵。这个哨兵称为树的外部节点，也参与到对红黑色的
 *    分析和操作中。
 *  6.外部节点和叶节点：外部节点是为了计算，分析方便，人为加上去或假想存在的树节点之外
 *    的节点，不存储实际的数据。叶节点本身还是树中的节点，且处于树的末端。一般在红黑树，
 *    B树等中的所有节点的空子节点（指针）指向外部节点，以便进行分析和操作。比如一个叶节
 *    点的两个子节点指针都是空的，则可以将其指向外部节点。
 *
 *
 *
 *
 *
 *					    2016年10月21日
 *
 */


#define _DEBUG_CLOSE_
#include "../PublicForAlgorithms.h"

typedef enum{RED=0xff0000,BLACK=0xffffff,}Color;

#define NIL_FLAG 0xfffffff

typedef int ElementType;

//最小红黑树节点数据结构
typedef struct Node
{
    ElementType  element; //数据
    Color        color;   //颜色
    struct Node* parent;  //父节点指针
    struct Node* lchild;  //左子节点指针
    struct Node* rchild;  //右子结点指针

}RBTNode,*RBT,*P_RBTNode;

//RBT森林数据结构
//这里只会用到森林的一个节点，也方便操作RBT树的root节点
typedef struct
{
    P_RBTNode rbt_root; //指向一颗RBT树的根节点
    int       id;       //树标识
    int       count;    //统计RBT树的节点数

}RBT_ForestNode,*P_RBT_Forest,*P_RBT_ForestNode;

/* 
 * 1.为操作方便，设立NIL哨兵为全局变量，在main中初始化
 * 2.默认为黑色
 * 3.所有节点有CreateRBTNode产生，parent/lchild/rchild默认都
 *   指向此哨兵，若CreateRBTNode生产失败，则默认返回此哨兵，
 *   即此哨兵代表：树的向上/下遍历的结束、不予处理的节点
 * 3.RBT_ForestNode的rbt_root默认指向此哨兵
 */
P_RBTNode NIL_Sentry;

//生成一个RBT节点
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
 * 旋转
 * 1.方向针对与C点来说的旋转，C点向树的上一层旋转。涉及到G P
 *
 *   ①           ②           ③          ④
 *   G            G            G           G
 *    \            \          /           /
 *     P            P        P           P
 *      \          /          \         /
 *       C        C            C       C
 * 右-右-左    右-左-右   左-右-左    左-左-右
 *   RRL         RLR        LRL         LLR
 *
 * 2.命名规则：C child P parent g grandparent, A-B-C
 * A和B方向分别代表P与G、N与P的左右关系，左代表左子节点，右代表右子节点
 * C方向代表N向P旋转的方向（如C为P的左子节点，则C通过逆时针方向可旋转到P位
 * 置，这里定义逆时针方向为向左）
 * 3.其中②和④对节点的操作一致，只是G对于C的连接有左右之差，只需在一个函数中
 *   增加一个判断P是G的左子节点还是右子节点即可，根据旋转方向，定义为右旋转
 *   （C为P的左子节点，顺时针，C旋转到P的位置）。①和③同理，定义为左旋转
 * 4.旋转只在Fix中使用，Roll中至少C/P是存在的，G则可能是哨兵。因为Fix程序中
 *   的N/P/G是确定存在的，传递给Roll函数的参数为N或P。
 *
 * 注意：使用Roll时要注意对照要旋转的点，到底程序中哪个点（实际要向上走一层的点）
 *       对应图中的C点！即注意RBTNode_Left_Roll与RBTNode_Right_Roll中G/P/C
 *       与RBT_Insert_Fix()中G/P/N的区别
 * 
 *
 */
//①③
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
	//分支到此处说明P是红黑树根节点
	forest_node->rbt_root = C;
    }
    P->parent   = C;
    P->rchild   = C->lchild;
    if(C->lchild != NIL_Sentry){ C->lchild->parent = P->rchild; }
    C->parent   = G;
    C->lchild   = P;
}

//②④
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
	//分支到此处说明P是红黑树根节点
	forest_node->rbt_root = C;
    }
    P->parent   = C;
    P->lchild   = C->rchild;
    if(C->rchild != NIL_Sentry){ C->rchild->parent = P; }
    C->parent   = G;
    C->rchild   = P;
}

/*
 * 插入操作Fix程序：对于插入的红色后，对红黑树进行Fix，
 *                  使树维护红黑树的5条性质
 * 1.N，插入的节点
 * 2.forest_node：维护红黑树根节点的森林节点
 * 3.在红黑树的5条性质中，进入Insert_Fix的只可能破坏 根节点是黑色
 *   和 红色节点的子节点必须是黑色 这两条性质，且只可能同时破坏其
 *   中的一条。
 * 4.这里利用循环进行向上层处理，效率较递归要高
 * 注意：根据RBT_Insert，则能够进入Insert_Fix的满足
 *       N->parent不为空 和 N->parent->color==RED
 *       因为N->parent->color==RED，则G节点一定存在且为BLACK
 * 5.分析的时候只需要根据G P U N四个节点的布局和着色进行情况讨论，
 * 然后进行向上循环即可，直到处理到根节点。
 *   插入的基本思路：因插入的是红色节点，因此只可能违反红黑树不能连
 * 红的性质。因此在处理连红时，P或者旋转N到P位置成为的新P肯定是要变
 * 黑，P或新P变黑，则经过此点路径多了一个黑点，要设法根据U的情况，
 * 将P或N旋转到G位置，相应调整U，这样经过P或新P路径上就会少一个黑点。
 * 若U是红色，则只能向上层循环处理。
 */
void RBT_Insert_Loop_Fix(P_RBT_ForestNode forest_node,P_RBTNode N)
{
    /* 处理插入节点的父节点如果是红色的话，要循环处理下去
     * 1.如果循环到N->parent 是根节点，则根节点是黑色，循环肯定就此停止，
     *   如果循环到N->parent 是根节点的子节点，即此时根节点是N的G节点，
     *   则根节点经过调整将变为红色，经过N=G再次循环是N->parent为哨兵节
     *   点，默认为黑色，也会结束循环.因此循环条件N->parent->color==RED
     *   不会存在访问空指针的问题
     * 2.在Fix过程中，只看经过旋转/换色操作，最终位于原G节点位置的节点的
     *   颜色是红色还是黑色，若仍为黑色，则不用在循环了，可当即break，若
     *   为红色，需要将此节点作为新的N节点进行向上层循环，看看新的N节点的
     *   parent是否为RED
     */
    while(N->parent->color == RED)
    {
	//G-grandparent P-parent N-now正在处理的节点
	P_RBTNode G = N->parent->parent;
	P_RBTNode P = N->parent;

	//G left to P and P left to N
	if(G->lchild == P && P->lchild == N)
	{
	    LINE_DEBUG("G left to P and P left to N");
	    P_RBTNode U = G->rchild;
	    //因为是 || ，所以会先验证其是否为空，如果不为空则再验证颜色
	    if(U == NIL_Sentry || U->color == BLACK)
	    {
		//P变为黑色，G变为红色，将P置到原来G的位置，G做P的右子节点
		P->color = BLACK;
		G->color = RED;
		//P是最终要向上走一层的点，所以传P而非N
		RBTNode_Right_Roll(forest_node,P);

		break;
	    }
	    else
	    {
		//此时，U为红色，将G变为红色，P/U变为黑色即可
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
	    //确定叔父节点
	    P_RBTNode U = G->rchild;

	    //向左旋转，即变为上case2的情况
	    RBTNode_Left_Roll(forest_node,N);

	    if(U == NIL_Sentry || U->color == BLACK)
	    {
		LINE_DEBUG("U == NIL_Sentry || U->color == BLACK");
		N->color = BLACK;
		G->color = RED;
		//这里，变成N是要向上走一层的点，因此传递N
		RBTNode_Right_Roll(forest_node,N);

		break;
	    }
	    else
	    {
		//将G变为红色，P/U变为黑色即可
		G->color = RED;
		N->color = BLACK;
		U->color = BLACK;

		N = G;
	    }
	}
	//G right to P and P right to N
	//case4:参照case2，与case2对称
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
	//case5:参照case3，与case3对称
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
    
    //存在一直向上层循环最终将根节点变为红色的情况
    //在此无论根节点是否变为红色都置黑一下，确保红黑树性质
    forest_node->rbt_root->color = BLACK;
}

/*
 * 递归形式的Insert_Fix
 * 1.将分支形式改变
 * 2.使用递归
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
	//在保证同Insert进入Insert_Fix的条件下，向上层递归进行Fix
	if(G->parent != NIL_Sentry && G->parent->color == RED)
	    RBT_Insert_Recursion_Fix(forest_node,G);
    }
   
    forest_node->rbt_root->color = BLACK;
}

/*
 * Insert操作
 * 参数：
 * forest_node:指向要操作的红黑树的森林节点
 * node：      要插入的节点，必须是由CreateRBTNode函数生成
 *
 * 说明：
 * 根据具体的5种情况，用if进行分支，进行不同的操作
 * case1:RTB root为空，则直接插入，但要将插入节点的颜色变为BLACK
 * case2-case5:P节点为红色，进入Fix的四种case
 *
 */
bool RBT_Insert(P_RBT_ForestNode forest_node,P_RBTNode node)
{
    if(node == NIL_Sentry)
    {
	LINE_DEBUG("RBT_Insert Failed: Node Is NULL");
	return false;
    }
    //不允许插入黑色节点
    if(node->color == BLACK)
    {
	LINE_DEBUG("RBT_Insert Failed: Node Is BLACK");
	return false;
    }
    
    P_RBTNode temp_node = forest_node->rbt_root;
    P_RBTNode temp_parent = temp_node;
    //①向下循环到要插入的节点
    while(temp_node != NIL_Sentry)
    {
	temp_parent = temp_node;
	if(node->element < temp_node->element)
	    temp_node = temp_node->lchild;
	else
	    temp_node = temp_node->rchild;
    }
    
    //②插入操作
    //此时实际是红黑树为空或只有一个根节点的情况
    /*****************************插入case1*****************************/
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
     * ③ 插入修补。也可将Fix放入到上面的if分支中，则Fix的分支可以相应的改变减少
     * 这里把Fix拉出来，单独进行Fix，情况用if分支分开，较为全面独立清楚
     * 1.如果父节点为黑色，则不违反任何红黑树的性质，则不变。否则就要调用Fix操作
     * 2.node->parent != NIL_Sentry的判断条件可不要，因为哨兵默认是黑色
     * 3.两种形式的Fix方法，任用一种
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
 * DeleteAssist操作
 * 1.因为N最多有一个子节点。子节点设为M节点。N的兄弟节点设为S，父节点设为P。
 *   如果N没有子节点，可以认哨兵NIL_Sentry做干儿子。需要做的操作是将M点直接
 *   替代（包括颜色）N作为新的N点，然后根据新N的颜色做情况分析，其中涉及到
 *   S的子节点Sl和Sr，若S不存在子节点，则也认NIL_Sentry做干儿子。因此，M Sl
 *   Sr都可能是真实存储数据的内部节点，也可能是不存储数据的叶节点，即NIL_Se
 *   ntry。
 *        P                  P              P               P
 *       / \                / \            /                 \
 *      N   S      或      S   N    或    N          或       N
 *       \                    /
 *        M                  M
 * 2.DeleteAssist的情况
 *   删除的基本思路：删除N，如N自身就是红色，则直接删除。若不是但是N自己有子节
 *   点(必为红)，则用子节点替代N并置黑。若N也没有子节点，则只能看P和S有没有红色
 *   可以借来转化为黑色来弥补因删除了N而少了一个黑色节点的损失。如果P S和其儿子
 *   都没有红色可以借，则只能通过减少S方向的黑色来解决问题，满足性质。所以情况分
 *   为：P有(自身)有红色，S有(自身)红色，S的儿子有红色，没有红色。而借出的方法
 *   的基本思路细就是将P/S部分中的红色变黑后将一个黑点腾挪到P的位置。
 *   ① 当N是红色，则N肯定是非根节点且无子节点。则可以直接删除N。
 *   ② 当N是黑色，且存在一个红色子节点M，则将M替换N并将M置黑，删除M点。
 *   ③ 当N是黑色，但是不存在(红色)子节点，则情况比较麻烦。
 *      此时S必定存在。基本情况细分如下：
 *      注意：S为末节点且为黑时，Sl Sr若存在，则必为红。若Sl Sr为黑则指的是其并
 *      不存在，只是用认的干儿子或者说叶节点NIL_Sentry(黑色)来代替的。
 *      (1) N为根节点，则直接删除，树变为空。
 *      (2) S为黑，但是P为红，此时N向P借黑：则简单的将P置黑，将S置红(不会造成S与
 *          Sl Sr连红的情况)。
 *      (3) S为黑，Sl或Sr存在一红或都为红，此时N向Sl或Sr借黑：通过两步旋转Sl或Sr
 *          到原P的位置(谁存在旋转谁)，设Sl是红色，旋转的规则：N与P的关系方向应与
 *          S与Sl的关系相反。若相反，则可直接将S点旋转到P位置，S置为P的颜色，P置
 *          黑，Sl置黑；若不相反，则须先旋转Sl至S位置，Sl与S互换颜色，此时Sl变为原
 *          S，S变为Sl的红子节点，然后再将Sl旋转到P的位置，Sl置为P的颜色，P置黑，
 *          S置黑。
 *      (4) S为红色(则Sl Sr必存在必为黑色，P必为黑)，若N为P的左子节点，此时N向S借
 *          黑：将S做左旋转升至原来的P处，此时Sl变为P的新子节点。将S置黑，Sl置红。
 *      (5) S为黑，Sl Sr(不存在)为黑，P为黑。即P没有红色，S也没有红色，则不能通过
 *          借红转黑的途径解决问题，只能是通过的减少S方向的黑色来解决问题。则S置为
 *          红，经过P的所有路径都达到平衡且少1，则将P作为新的N点从(1)开始进行处理。
 *      经过(1)-(5)情况的的处理后，直接free掉N节点即可。
 *   ④ 将③的五种情况作为delete_case1...delete_case5单独列出。除delete_case1外，
 *      由于N存在迭代问题，因此将N的释放问题放在调用delete_case之后统一进行释放
 *      Original_N。
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
	//S的lchild为红或者lchild/rchild都为红会进入此分支
	//S_l(为红)与S的关系方向与N与P的关系相同，都是lchild
	if(S_l->color == RED)
	{
	    RBTNode_Right_Roll(forest_node,S_l);
	    RBTNode_Left_Roll(forest_node,S_l);
	    S_l->color = P->color;
	    P->color   = BLACK;
	}
	//S的rchild为红
	//S_l(为红)与S的关系方向与N与P的关系相反
	else
	{
	    RBTNode_Left_Roll(forest_node,S);
	    S->color   = P->color;
	    P->color   = BLACK;
	    S_r->color = BLACK;
	}
    }
    //镜像情况
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
    //① 直接删除N
    if(N->color == RED)
    {
	LINE_DEBUG("圈1");
	if(P->lchild == N)
	    P->lchild = NIL_Sentry;
	else
	    P->rchild = NIL_Sentry;
	SAFE_FREE(N);
    }
    //② 用M替换N，这里直接用element替换，就不会涉及P、颜色和根节点了
    else if(N->lchild != NIL_Sentry)
    {
	LINE_DEBUG("圈2");
	N->element = N->lchild->element;
	SAFE_FREE(N->lchild);
	N->lchild = NIL_Sentry;
    }
    else if(N->rchild != NIL_Sentry)
    {
	LINE_DEBUG("圈2");
	N->element = N->rchild->element;
	SAFE_FREE(N->rchild);
	N->rchild = NIL_Sentry;
    }
    //③ N为黑且无子节点
    else
    {
	//(1)
	if(N->parent == NIL_Sentry)
	{
	    LINE_DEBUG("delete_case1");
	    RBT_Delete_Case1(forest_node,N);
	    return true;
	}

	//备份原始N
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
	    //(5) 唯一会产生向树的上层迭代的情况
	    else if(P->color == BLACK && S->color == BLACK && S->lchild->color == BLACK && S->rchild->color == BLACK)
	    {
		LINE_DEBUG("delete_case5");
		RBT_Delete_Case5(N);
		//迭代
		N = P;
	    }
	}//while end
	
	//释放原始N
	if(Original_N == Original_N->parent->lchild)
	    Original_N->parent->lchild = NIL_Sentry;
	else
	    Original_N->parent->rchild = NIL_Sentry;

	SAFE_FREE(Original_N);
    }//if(N->color == RED) end
    
    return true;
} 

/*
 * Delete操作
 * forest_node：RBT森林节点，表示一个连向一棵红黑树的节点
 * element：要删除的含有元素element的红黑树节点，这里假设红黑树中的节点具有唯一性
 * 1.普通二叉树的删除操作一般采用寻找一个要删除节点D的左子树的最大节点Lmax或右子树的最
 *   小节点Rmin进行替换，然后删除Lmax或Rmin，直接替换后，D节点也不会改变红黑树的性质，因此
 *   Delete的操作变为删除Lmax或Rmin节点的问题，这里采用删除Rmin的方法，即Delete_Assist要解
 *   决的问题。
 * 2.当D点至多有一个子节点时，直接将D当作要处理的点N传递给Delete_Assist，当D有两个子节点时
 *   ，将Rmin点作为要处理的N点传递给Delete_Assist。
 *   
 */
bool RBT_Delete(P_RBT_ForestNode forest_node,ElementType element)
{
    if(forest_node->rbt_root == NIL_Sentry)
    {
	LINE_DEBUG("The RBT is NULL");
	return false;    
    }
    //寻找element所在节点
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
    
    /* 要删除的节点有左、右子树，选择将右子树的最小值替换节点并将其作为N点
     * 传递给Delete_Assist
     */
    if(temp_node->lchild != NIL_Sentry && temp_node->rchild != NIL_Sentry)
    {
	//寻找要替代的点N并替代包含element所在的节点
	P_RBTNode temp_right_min_node = temp_node->rchild;
	while(temp_right_min_node->lchild != NIL_Sentry)
	{
	    temp_right_min_node = temp_right_min_node->lchild;
	}
	//替换
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
	printf("红色");
    else
	printf("黑色");
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


    //要设置成黑色哨兵，以配合红黑树的增删操作
    //如何配合可参看Insert和Insert_Fix函数
    NIL_Sentry = (RBT)malloc(sizeof(RBTNode));
    if(NIL_Sentry == NULL)
    {
	printf("NIL Sentry malloc failed\n");
	return -1;
    }
    NIL_Sentry->color = BLACK;

    //初始化红黑森林
    RBT_ForestNode RBT_FOREST[5];
    Init_RBT_Forest(RBT_FOREST,5);
    
    //测试CreateRBTNode
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
    
    //手工写组织一棵红黑树
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
    
    //insert测试
    P_RBTNode node6 = CreateRBTNode(6,RED);
    if(node6) DEBUG("create success!\n");
    
    //插入一个6节点
    RBT_Insert(&(RBT_FOREST[0]),node6);
    
    RBT_Show(RBT_FOREST[0].rbt_root);

    P_RBTNode node8 = CreateRBTNode(8,RED);
    if(node8) DEBUG("create success!\n");

    //插入一个8节点
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
    
    //delete测试
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

