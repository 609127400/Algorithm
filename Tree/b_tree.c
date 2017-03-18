/*
 *
 *                                      B 树
 *  1.m阶B树，就是m路的平衡搜索树（相当于每logm代二叉树合并成一个节点所形成的B树）。
 *    给定了一棵B树超级节点的上限和下线。
 *    上限：至多有m路分支和m-1个关键码。
 *    下限：除根节点外，至少有m/2个分支和m/2-1个关键码，其中m/2取上限（如5/2=3）
 *          根节点在特殊情况下可以最少有两个分支和1个关键码。
 *    因此可以用B树分支的上下限给B树命名，如m=5，则称(3,5)树。其中，(2,4)树就是红黑
 *    树的影子。
 *    超级节点：每个超级节点都有限制内的关键码和分支组成，关键码就是所谓存储的数据。
 *      5  10  15       或者   5  10  15 
 *    5l 5r  10r 15r         5l  10l 15l 15r
 *  2.所有B树的叶节点和外部节点都是统一在同一层的，即深度统一。B树在多级存储结构中
 *    有比较有意义的应用。如内存之于硬盘的批量I/O访问。分级存储的基本概念就是将更需
 *    要的存储在更快的存储器中。而B树的超级节点的特性可以使内存一次读取多个数据（批
 *    量）。一般被设计用于内存操作与外存操作(I/O)相结合操作之中，是内外存操作尽可能
 *    的接近。如果B树仅仅是用在同一存储介质中的算法，其效率可能并没有其它BBST效率高。
 *  3.B树的高度是从根节点到外部节点间的高度。当总共有N个关键码时，其树的高度较二叉树
 *    可以降低为1/7左右。
 *  4.B树的Insert操作
 *    插入操作会造成m阶B树违反其最多只能有m路分支的规定，称为上溢，此时超级节点拥有m
 *    个关键码。对上溢做出调整，使之恢复B树性质，成为分裂。
 *    分裂规则：设上溢的超级节点为 K1,K2...Km,取超级节点关键码的中位数，即位于m/2(取
 *    下限，如5/2=2)的位置s的关键码Ks，由此超级节点被分为三部分，左边K1,K2...Ks-1,中
 *    间的Ks，右边的Ks+1,Ks+1...Km。将Ks上升一层，交由其父超级节点管理，并将左部分作
 *    为Ks的左子节点，右部分作为Ks的右子节点。
 *    如：
 *    一个5阶B树的一个超级节点原为 2 6 8 9，现插入一个5变为 2 5 6 8 9，溢出，则将位于
 *    中位的6上升一层，交由其父节点管理。2 5 作为6的左子节点，8 9 作为6的右子节点。
 *    
 *    插入的子节点，子节点发生上溢，对子节点分裂操作，可能也会引发父节点的上溢，只要依
 *    次同样处理即可，直至到达根节点。根节点的上溢，同样将中位数Ks上升，此时中位数成为
 *    B树新的根且只有两个分支。也仅在根发生上溢时，B树的高度才会增加一层。
 *  5.B树的Delete操作
 *    依旧同二叉搜索树一样，B树的删除，若删除的关键码是叶节点中的，则直接删除关键码及
 *    对应连接的外部节点，如果不是，需要找子树的Max或Min关键码进行替换，然后删除这个
 *    后继的关键码及外部连接。
 *    无论是直接删除还是间接删除，都会导致超级节点破环B树分支的下限，成为下溢，此时这个
 *    超级节点存在m/2-1个分支和m/2-2个关键码。对下溢做出调整，使之恢复B树性质，有两种方
 *    法：借贷和合并，且首先进行借贷操作(左顾右盼)，若没有借贷条件，再进行合并。
 *    (1) 借贷规则：若发生下溢的节点相邻的的左兄弟节点或右兄弟节点拥有至少m/2个关键码，
 *    即其可以借出一个后仍剩余m/2-1个关键码而不违反B树的性质，则可以通过向兄弟借贷而修
 *    补下溢。但因要保证搜素树 左<中<右，假设下溢节点的左兄弟节点满足条件，则借贷的过程
 *    是左子节点的max关键码借给父节点替换相应父关键码，右子节点将父节点中对应的父关键
 *    码借来弥补下溢。此时注意插入到下溢节点的父关键码的左子节点要为NIL_Sentry。使右子
 *    节点的关键码数达到最小的m/2-1个。借出去的关键码对应的childs要补到下溢节点处。
 *    (2) 合并规则：若发生下溢的节点没有兄弟节点或者兄弟节点已达到下限，只有m/2-1个关
 *    键码，则此时需要进行合并操作。将左子节点的0个或m/2-1个关键码、父节点的父关键码、
 *    右子节点的m/2-2个关键码合并成一个含有m/2-1 + 1 + m/2-2 = m-2或0 + 1 + m/2-2 = m/2-1
 *    个关键码的超级节点，使得新的超级节点的关键码不会超出上下限。
 *    合并操作相当于从父节点删除了一个关键码，因此使父节点同样存在下溢的可能，若此，做
 *    相同处理即可，直至根节点，通过合并形成新的根，树的高度降低一层。
 *
 *
 *
 *
 *
 *
 *
 *
 *                                                            2016年10月31日
 *
 *
 *
 *
 *
 */


#define _DEBUG_CLOSE_
#include "../PublicForAlgorithms.h"

//定义B树的阶
#define M 5
#define KEYS_NUM (M-1)
//定义B树关键码的上下限，关键码更直观一点
#define KEYS_UP_LIMIT (M-1)
#define KEYS_LOW_LIMIT (((M%2)?(M/2+1):(M/2)) - 1)

typedef int ElementType;

typedef struct Node
{
    struct Node* parent;
    /* 
     * elements与childs的对应关系：
     * 寻找某一关键码的lchild时坐标不变，rchild时坐标+1
     * 如elements[1]的lchild是childs[1],rchild是childs[1+1];
     * 将elements设计为最多m个，是为了上溢时操作方便，但是
     * capacity的最大值只能是KEYS_NUM
     * 设计成数组，访问方便，但是在插入删除关键码时很麻烦，这
     * 里设计不算太合理，设计成链表之类的可能在插入删除操作时
     * 更方便
     */
    ElementType  elements[M];
    struct Node* childs[M+1];
    /*当前elements的所含element的数量*/
    int          capacity;
}BTNode,*P_BTNode,*B_Tree;

//B树森林，这里简单定义5棵，只用其中的BTrees[0]
typedef struct Forest
{
    P_BTNode B_Trees[5];
    int      capacity;
}BT_Forest,*P_BT_Forest;

//哨兵，作为所有的外部节点，在main中初始化
//通过CreateBTNode生产出来的节点，parent、childs默认都指向哨兵
//要注意，其他成员需要哨兵，只是需要哨兵这个地址而已，其本身不
//存储数据，若存储数据，可以做一些其他的标识。让其吹号。
//哨兵的parent\childs默认为NULL，elements和capacity默认为0；
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

//创建B树节点
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
 * B树的Search操作
 * bt B树
 * key 要查询的关键码
 * 注意：
 * ① 查找成功返回包含key的B树超级节点，查找失败则返回搜索的最后一
 * 个超级节点，以辅助Insert和Delete操作。
 * ② 这样设计综合来讲还是划算的，因为超级节点的
 * 遍历总是在内存中的，速度很快，避免插入操作在搜索一遍发现key不在B树
 * 后还需要逐级再遍历一遍去寻找要插入的点。
 * ③ 这里用哨兵吹号来标识查找结果：若查找失败返回的last_super_node，
 * 则将哨兵的capacity置为-1，若成功则保持哨兵的初始化值0不变。这点与
 * 哨兵的初始化值有关联。判断完毕后及时让哨兵灭号。
 * ④ 这样设计可能存在的问题：因为哨兵是全局变量，因此在多线程下应该会
 * 出现问题。
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
	//超级节点内部搜索
	while(i < bt->capacity)
	{
	    if(key == bt->elements[i])
	    {
		LINE_DEBUG("Find the Key");
		return bt;
	    }
	    /*一旦发现当前超级节点有一个比key还大的关键码，立刻
	     *转到该关键码的左孩子上，然后break，进入其左孩子的
	     *搜索
	     */
	    else if(key < bt->elements[i])
	    {
		last_super_node = bt;
		bt = bt->childs[i];
		break;
	    }
	    ++i;
	    /*当前超级节点搜索完了还没找到比key大的关键码，则
	     *转到当前节点最右的子节点中去继续搜索
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
    //哨兵吹号
    NIL_Sentry->capacity = -1;
    return last_super_node;
}

/*
 * Insert辅助程序
 * 功能：在超级节点中插入一个关键码，并在childs相应位置插入关键码的左右子节点
 * super_node 要被插入关键码的超级节点
 * key 要插入的关键码
 * lchild/rchild 插入关键码连接的左右儿子
 * 返回插入key的坐标
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
 * B树Insert操作
 * 
 * bf B树森林：只对第一棵B树bf->B_Trees[0]进行操作
 * key 要插入的关键码
 * 这里修补上溢问题的功能没有单独提出来，而是放在
 * 了一个while中。
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
	//哨兵灭号
	NIL_Sentry->capacity = 0;
    }
    
    int i = 0;
    P_BTNode lchild = NIL_Sentry;
    P_BTNode rchild = NIL_Sentry;
    //上溢节点的中间位置和值
    int center_pos;
    ElementType center_element;
    /*
     * 能走到这里说明key可以进行插入操作
     * 循环结束条件：一直处理到根节点或者当前超级节点插入后未发生上溢
     * 循环过程：将key插入search返回的超级节点，判断该节点是否上溢，若
     *           未上溢，则break，若上溢，则进行分裂操作并更新要插入的
     *           超级节点re和要插入的元素key/lchild/rchild。
     *           当原来的根节点re上溢时，要创建新的根节点并作相应迭代。
     */

    while(re != NIL_Sentry)
    {
	InsertKey(re,key,lchild,rchild);
	if(re->capacity <= KEYS_UP_LIMIT)
	{
	    break;
	}
	//插入后将发生上溢,capacity == M;
	else
	{
	    LINE_DEBUG("节点发生上溢");
	    center_pos = M/2;
	    //进行分裂处理
	    //迭代lchild/rchild/center_element，将原超级节点分为三部分
	    //原节点作为左儿子，右儿子新建
	    //左：这里的处理方法是直接截断capacity即可
	    re->capacity = M/2;
	    lchild = re;
	    //中
	    center_element = re->elements[center_pos];
	    //右边，创建新的节点，将原节点右部分的elements和childs复制
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
	    //不能忘了最后一个childs
	    rchild->childs[i] = re->childs[center_pos];

	    //迭代 key 和 re
	    key = center_element;
	    if(re->parent != NIL_Sentry)
	    {
		re  = re->parent;
	    }
	    //当re是root时
	    else
	    {
		//分裂出新根
		P_BTNode new_root = CreateBTNode();
		re = new_root;
		
		bf->B_Trees[0] = new_root;
	    }
	}
    }//while end
    
    return true;
}

/*
 * Delete辅助程序
 * 只适用于DeleteAssist程序中合并功能的删除key点工作
 * 删除超级节点node的关键码key，node节点必须含有关键码key，否则
 * 操作结果不确定。
 * ① 在DeleteAssist程序中，对应非末子节点和末子节点分别进行左合并和右合并，
 *    要删除的父节点的key是最后一个和非最后一个，两种情况下对节点的elements
 *    和childs处理方式是不同的。
 * 原父节点和子节点：
 *   10    20    30    40
 *  8/9  11/12 21/22  31/32  41/42  删除node的关键码21
 * 
 *   10    20      30       40        父节点中的30待删除
 * 8/9  11/12  22/30/31/32  NIL 41/42 其中NIL是在DeleteAssist中置NIL的节点
 * 因此DeleteKey删除30之后
 *   10      20      40
 * 8/9    11/12  22/30/31/32  41/42
 * 这样在节点合并的时候，父关键码直接放在40之后，childs不用处理，之后直接复
 * 制右边节点的element和child
 * ② 若node是最后一个节点，对应的要删除父节点中的最后一个key：
 * *   10    20    30    40
 *  8/9  11/12 21/22  31/32  41/42  删除node的关键码41
 * 
 *   10    20      30       40           父节点中的40待删除
 * 8/9  11/12    21/22  31/32/40/42  NIL 其中NIL是在DeleteAssist中置NIL的节点
 * 因此DeleteKey删除40之后
 *   10      20    30   
 * 8/9    11/12  21/22  31/32/40/42
 */

void DeleteKey(P_BTNode node,ElementType key)
{
    int i = 0;//确定key的位置
    int j = 0;
    while(i < node->capacity)
    {
	if(node->elements[i] == key) break;
	++i;
    }

    //如果删除的key不是最后一个，对elements和childs进行腾挪
    //若是删除的key是最后一个，则不处理，直接--(capacity)，相当于删除最后一个key
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
 * DeleteAssist功能：进行实际的删除工作并修复可能存在的下溢
 * bf：B树森林：只对第一棵B树bf->B_Trees[0]进行操作
 * node：待Fix的超级节点
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
    
    //结束条件在这里永远不会达到，因为处理到根节点的
    //这里只是要的其循环的效果，也可将条件写做1
    while(node != NIL_Sentry)
    {
	DeleteKey(node,key);

	/*当前处理节点删除key之后*/

	//这种情况是删除合并到只剩一个根节点时才会发生
	//处理的节点是根节点，因为根节点的LOW_LIMIT有修正条款，因此不受限制
	if(node->parent == NIL_Sentry)
	{
	    break;
	}
	//当处理的节点不是根节点且elements未少于下限的
	else if(node->capacity >= KEYS_LOW_LIMIT)
	{
	    break;
	}
	else
	{
	    LINE_DEBUG("节点发生下溢");
	    //处理下溢
	    int i = 0;
	    int j = 0;
	    P_BTNode P = node->parent;
	    P_BTNode S_l = NIL_Sentry;
	    P_BTNode S_r = NIL_Sentry;
	    //确定父关键码的位置，用i表示，注意这里是childs[i]
	    while(i <= P->capacity)
	    {
		if(P->childs[i] == node) break;
		++i;
	    }

	    /*
	     * 左顾右盼
	     * ①借贷不会发生所借或所接收的关键码的分支没地方放或者被覆盖的问题。
	     * ②经过叶节点的合并迭代到非叶节点层(只可能是经合并才迭代到非叶节点层)
	     *   假设借贷的非叶节点是A，兄弟节点是B，向B借B的min或max关键码，B借出后
	     *   关键码少了一个且是最后一个或者第一个，关键码的分支也应对应少一个，应
	     *   删去这个分支正好补到A的第一个或者最后一个key的分支上。然后对B的elements
	     *   和childs做相应调整
	     * ③借贷或者说旋转都是在同层节点发生的，不是由下层引起的，且不会发生实质
	     *   性的删除
	     * ④左顾要将兄弟节点max关键码赋值给父关键码，把父关键码赋值给下溢节点
	     *   elements[0],把最右的childs赋值给下溢节点childs[0]，最后把兄弟节点
	     *   的max关键码删除。
	     *   右盼要将兄弟节点min关键码赋值给父关键码，把父关键码赋值给下溢节点
	     *   elements[capacity],把最右的childs赋值给下溢节点childs[capacity+1]，
	     *   最后把兄弟节点的max关键码删除。
	     *  
	     */
	    //左顾
	    if(((i-1) >= 0) && (P->childs[i-1]->capacity > KEYS_LOW_LIMIT))
	    {
		S_l = P->childs[i-1];
		//移除一个位置，这里有优化的空间，因为DeleteKey刚移完，现在又移
		j = node->capacity;
		while(j >= 1)
		{ 
		    node->elements[j] = node->elements[j-1];
		    node->childs[j+1] = node->childs[j];
		    --j;
		}
		node->childs[j+1] = node->childs[j];
		//处理node节点
		node->elements[0] = P->elements[i-1];
		node->childs[0]   = S_l->childs[S_l->capacity];
		++(node->capacity);
		//处理P和左兄弟节点
		P->elements[i-1]  = S_l->elements[S_l->capacity - 1];
		--(S_l->capacity);
		
		break;
	    }
	    //右盼
	    if(((i+1) <= P->capacity) && (P->childs[i+1]->capacity > KEYS_LOW_LIMIT))
	    {
		S_r = P->childs[i+1];
		//处理node节点
		node->elements[node->capacity] = P->elements[i];
		node->childs[node->capacity + 1] = S_r->childs[0];
		++(node->capacity);
		//处理P和右兄弟节点
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
	    /* 合并操作，进行迭代
	     * ①处理方式：将node作为合并后的节点，parent在接触到根节点时要更新，右
	     *   节点要释放并将对应的父节点中的childs置NIL
	     * ②根据B树特点，合并不可能出现溢出越界
	     * ③一层节点被删除，肯定是下层合并引起的，借贷不可能引发删除
	     * ④左与中右合并，也有右与中左合并
	     * ⑤操作后的效果：若node不是P的末节点，则父关键码和右节点合并到node，若
	     *   node是P的末节点，则合并到S_l。P节点在当前迭代中只有对应childs被处理，
	     *   要删除的关键码要到下次迭代中进行处理。
	     */
	    if(i < P->capacity)
	    {
		S_r = P->childs[i+1];
		j = 0;
		node->elements[node->capacity] = P->elements[i];
		//插入父关键码,对应的childs不用处理
		++(node->capacity);
		//插入S_r关键码和childs
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
		//原node节点已经消失，这里要换成新的合并后的node
		node = S_l;
		P->childs[i] = NIL_Sentry;
	    }

	    //合并后的节点的父节点是否是根节点，若是，则更新根节点并释放原根节点
	    //此时B树高度降低
	    //只可能是通过合并，根节点才会消失
	    if((P->parent == NIL_Sentry) && (P->capacity == 1))
	    {
		LINE_DEBUG("New Root");
		SAFE_FREE(P);
		node->parent = NIL_Sentry;
		bf->B_Trees[0] = node;
		break;
	    }

	    //迭代，继续DeleteKey
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
 * B树Delete操作
 * bf：B树森林：只对第一棵B树bf->B_Trees[0]进行操作
 * key：要删除的关键码
 * 仍然采用右子树最小值替换的方法
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
	//哨兵灭号
	NIL_Sentry->capacity = 0;
	return false;
    }
    
    //如果是叶节点，则确定真正要处理的节点和key
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

	//值替换，对应的childs不变
	re->elements[i] = temp_node->elements[0];
	key = temp_node->elements[0];
	re = temp_node;
    }

    LINE_DEBUG("key=%d",key);
    //调用DeleteAssist删除节点并处理可能发生的下溢
    bool result = DeleteAssist(bf,re,key);

    if(result == true)
	printf("Delete Success\n");
    else
	printf("Delete Failed\n");
}

/*
 * B树Free操作
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
 * 显示B数所有的超级节点
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
    //手工建立一棵4阶B数
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
    
    //测试Search操作
    P_BTNode re = BT_Search(bt_forest->B_Trees[0],100);
    if(NIL_Sentry->capacity == 0)
    {
	printf("Search Success,BTree Node First key=%d\n",re->elements[0]);
    }
    else
    {
	printf("Search Failed,BTree Last Super Node First key=%d\n",re->elements[0]);
	//哨兵灭号
	NIL_Sentry->capacity = 0;
    }

    //测试Insert操作
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

