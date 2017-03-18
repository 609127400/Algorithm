
/*
 *         回溯算法
 *  1.实质是先序遍历一个状态树，算是利用程序对解进行试探穷举
 *  2.状态数：其实也就是一般的树，只是这个树的一层代表一个元素，每一个分支代表
 *    这个元素的一个状态。下一层代表下一个元素，每一个分支代表下一个元素上一层
 *    基础元素基础上的一个状态。
 *    如：
 *                             []                         //初始状态为空
 *                      /             \
 *                  A状态1           A状态2
 *                 /     \          /     \
 *            B状态1    B状态2   B状态1   B状态2
 *          ...    ... ...  ... ... ...  ... ... 
 *
 *  3.状态树不是事先生成的，而是存在于遍历之中
 *  4.适用于问题分解的过程中每一步固定存在n种状态
 *  5.回溯算法的性能由于问题的原因，一般较差，但也是相对而言，主要看解决什么样的
 *    问题
 *
 *
 *
 *			2016年10月14日
 */

#define _DEBUG_CLOSE_
#include "PublicForAlgorithms.h"

typedef int ElementType;
typedef int bool;
#define true 1
#define false 0

/*
 * 例1
 * 求集合A的幂集，即由集合A任意子集作为一个元素形成的集合，也即求出集合A的所有子集
 * 1.如A = {1，2，3}
 *   A中每个元素都有两种状态：在子集中(true)和不在子集中(false)，因此可以利用树的两个分支来表
 *   示这两种状态,左分支代表该元素不在子集中，右分支代表该元素在子集中，因此所有叶子节点即为
 *   所有子集的解
 *                  []             //初始状态为空
 *            [1]        []        //1存在或者不存在于子集中的两种状态
 *       [1,2]   [1]   [2]  []     //在1状态的基础上，2存在或者不存在于子集中的两种状态
 *   ....                          //在2状态的基础上，3存在或者不存在于子集中的两种状态
 * 2.这个体现了回溯算法的一个特性，树并不是事先存在的，而是隐藏在遍历中的。解最初状态为空，一
 *   点点的向下探寻，过程中的节点只是为了探寻回溯，真正需要的也是能得出问题的解的集合的是叶子
 *   节点。
 * 3.所有叶子节点都是A幂集的合法解，例2中的回溯则不是所有的分支都满足条件，不满足条件的分支将
 *   被“砍掉”
 * 4.e_arr    原集合
 *   len      集合元素数量
 *   i        当前要处理的元素下标
 *   temp_box 临时存放解的box
 *   temp_box 临时box的长度
 */

inline void DisplaySubClass(ElementType arr[],int len)
{
    int i = 0;
    while( i < len )
    {
	if(arr[i] == true)
	    printf("%d",i+1);
	++i;
    }
    printf("\n");
}

//链表数据类型
//用一个链表表示A的一个子集
typedef struct Node
{
    ElementType e;
    struct Node* next;

}LNode,*P_List;

//初始化一个链表
//此链表头不做实际操作用，只做一个哨兵位置，方便增删改,位置记作0，
P_List InitListHead()
{
    P_List head = (P_List)malloc(sizeof(LNode));
    if(!head) return NULL;
    head->e = -1;
    head->next = NULL;

    return head;
}

//链表的长度，即子集的长度
int GetListLength(P_List l)
{
    if(l == NULL) return 0;
    int couter = 0;
    while(l->next){ ++couter; l=l->next; }
    return couter;
}


//把A集合设置为数组，则可不需要此函数
bool GetListElement(P_List l,int pos,ElementType *e)
{
    if(l == NULL) return false;
    if(pos < 1) return false;

    int i = 0;
    while( i<pos  && l )
    {
	l = l->next;
	++i;
    }

    LINE_DEBUG("i=%d",i);
    if( i<=pos && (!l) ) return false;
    *e = l->e;
    return true;
}

//在指定位置插入一个集合A的元素
//链表位置从1开始
bool InsertElement(P_List l,int pos,ElementType e)
{
    if(l == NULL) return false;
    if(pos < 1) return false;

    int i = 0;
    while( (i<pos-1) && l )
    {
	l = l->next;
	++i;
    }
    if( i<=(pos-1) && (!l) ) return false;

    P_List new = (P_List)malloc(sizeof(LNode));
    if(new == NULL) return false;
    
    new->e = e;
    LINE_DEBUG("1");
    new->next = l->next;
    LINE_DEBUG("2");
    l->next = new;
    return true;
}

bool DeleteElement(P_List l,int pos,ElementType* e)
{
    if(l == NULL) return false;
    if(pos < 1) return false;

    int i = 0;
    while( (i<pos-1) && l )
    {
	l = l->next;
	++i;
    }
    if( i<=(pos-1) && (!l) ) return false;

    if(l->next == NULL) return false;
    P_List temp = l->next;
    *e = l->e;
    l->next = l->next->next;
    SAFE_FREE(temp);
    return true;
}

void ShowList(P_List l)
{
    if(l == NULL) return;
    while(l->next)
    {
	printf("%d  ",l->next->e);
	l = l->next;
    }
    printf("\n");
}

void FreeList(P_List l)
{
    if(l == NULL) return;
    l = l->next;
    P_List temp;
    while(l)
    {
	temp = l;
	l = l->next;
	SAFE_FREE(temp);
    }
}

/* 
 * List_A 原集合A，每个节点为一个元素
 * List_B 用于存储解，即A的一个子集，当满足条件之后，即递归到了第i>len_A的那一层，进行输出子集
 * i，当前递归控制层，也即处理当前A的第i个元素的状态
 * len_A List_A的长度，即A集合元素个数
 *
 */
void ShowSubClass(int i,P_List List_A,int len_A,P_List List_B)
{
    if(i > len_A)
    {
	ShowList(List_B);
    }
    else
    {
	ElementType element;
	GetListElement(List_A,i,&element);
	int k = GetListLength(List_B);
	InsertElement(List_B,k+1,element);//A的第i个元素存在在子集中
	int test = 1;//for gdb
	ShowSubClass(i+1,List_A,len_A,List_B);
	DeleteElement(List_B,k+1,&element);//A的第i个元素不存在子集中
	int testtest = 1;//for gdb
	ShowSubClass(i+1,List_A,len_A,List_B);
    }
}




/*
 *
 * 例子2 n皇后问题
 * 1.任意摆放n个皇后，使得n个皇后彼此不在同一行，同一列或同一斜线上
 * 2.也是先序遍历一个状态树，将每种情况当作树的一个分支
 * 3.此编码格式可作为一般的回溯算法格式
 *
 */

/* 4x4棋盘
 *
 *      * * * *
 *      * * * *
 *      * * * *
 *      * * * *    x
 *      ------------>
 */
#define CHESS_SIZE 5

bool ChessBoard[CHESS_SIZE][CHESS_SIZE] = {0};

//判断当前棋盘布局是否有效
bool BoardIsValid(bool board[][CHESS_SIZE])
{
    int y,x;
    for(y=0; y<CHESS_SIZE; ++y)
    {
	for(x=0; x<CHESS_SIZE; ++x)
	{
	    //按点搜寻，当当前点是一个棋子时，根据此点向6个方向搜索
	    //不会造成重复搜索，因为只要一遇到第一个错误，当即就返回了
	    if(board[y][x])
	    {
		//y+ x+方向
		int yy = y+1;
		int xx = x+1;
		while(yy<CHESS_SIZE && xx<CHESS_SIZE)
		{
		    if(board[yy][xx])
			return false;
		    ++yy; ++xx;
		}

		//y- x-方向
		yy = y-1;
		xx = x-1;
		while(yy>=0 && xx>=0)
		{
		    if(board[yy][xx])
			return false;
		    --yy; --xx;
		}
		
		//y+ x-方向
		yy = y+1;
		xx = x-1;
		while(yy<CHESS_SIZE && xx>=0)
		{
		    if(board[yy][xx])
			return false;
		    ++yy; --xx;
		}

		//y- x+方向
		yy = y-1;
		xx = x+1;
		while(yy>=0 && xx<CHESS_SIZE)
		{
		    if(board[yy][xx])
			return false;
		    --yy; ++xx;
		}
		//y方向
		yy = 0;
		xx = x;
		while(yy<CHESS_SIZE)
		{
		    if(board[yy][xx] && yy!=y)
			return false;
		    ++yy;
		}
		//x方向
		yy = y;
		xx = 0;
		while(xx<CHESS_SIZE)
		{
		    if(board[yy][xx] && xx!=x)
			return false;
		    ++xx;
		}
	    }//if
	}//内层for循环
    }//外层//for循环
    return true;
}

//显示棋盘，*代表空  O代表棋子
void ShowChessBoard(bool board[][CHESS_SIZE])
{
    printf("\n");
    int y,x;
    for(y=0; y<CHESS_SIZE; ++y)
    {
	for(x=0; x<CHESS_SIZE; ++x)
	{
	    if(board[y][x])
		printf("%c ",'O');
	    else
		printf("%c ",'*');
	}
	printf("\n");
    }
    printf("\n");
}

/* 
 * y 递归的层数，也即树的深度，也即棋盘的行数y，默认从0开始
 * chess_size 棋盘的大小，这里默认是正方形的
 * board 棋盘
 *
 */
void Queen(int y,int chess_size,bool board[][CHESS_SIZE])
{  
    LINE_DEBUG("aaa");
    //n皇后问题，chess_size最小只能是4，3的话最多只能放2个皇后
    if(chess_size < 4) return;

    if(y >= chess_size)
    {
	//如果到了这里，说明当前棋盘已经处理了chess_size-1行合理的布局
	//即整个棋盘的n个皇后布局是符合要求的，当即在此输出，然后返回
	//所以在回溯中，在else里面不需要考虑递归是否能得出正确的解，在某次
	//递归中如果出现符合条件的解，程序自然会到这里执行，或保存解，或输出解
	ShowChessBoard(board);
    }
    else
    {
	int x;//棋盘的x轴
	//for循环用来尝试探寻每种棋子放到x处的可能性，即在每一行棋子可能的每种状态
	for(x=0; x<chess_size; ++x)
	{
	    board[y][x] = true; //在当前位置放置棋子
	    //这点儿的if就相当于裁剪分支，如果当前的布局不合法，则不会进一步向深层递归试探
	    if(BoardIsValid(board))
	    {
		//如果当前布局合法，则递归到下一层，即棋盘的下一行进行试探，直到试探到第chess_size-1行，
		//尝试x从0到chess_size种情况，如果也合法了，则找到完整的布局的解，则会进入if处的对解进行输出
		Queen(y+1,chess_size,board);
	    }
	    //如果当前布局无效或下层的递归回来（无论存在不存在正确的布局），
	    //则拿走当前点的棋子，结束这一层的递归，返回到上一层继续尝试把棋子摆放到位置
	    board[y][x] = false;
	}
    }
}

int main()
{
    bool re = false;
    P_List List_A,List_B;
    List_A = InitListHead();
    List_B = InitListHead();
    
    re = InsertElement(List_A,1,1);
    if(re == false) printf("Insert Failed\n");
    re = InsertElement(List_A,2,2);
    if(re == false) printf("Insert Failed\n");
    re = InsertElement(List_A,3,3);
    if(re == false) printf("Insert Failed\n");
    //re = InsertElement(List_A,4,4);
    //if(re == false) printf("Insert Failed\n");
    //re = InsertElement(List_A,5,5);
    //if(re == false) printf("Insert Failed\n");    
    /*
    //测试链表用
    ElementType element;
    re = GetListElement(List,1,&element);
    if(re == false) printf("GetElement Failed\n");
    printf("Element=%d\n",element);
    re = GetListElement(List,2,&element);
    if(re == false) printf("GetElement Failed\n");
    printf("Element=%d\n",element);
    re = GetListElement(List,3,&element);
    if(re == false) printf("GetElement Failed\n");
    printf("Element=%d\n",element);

    re = DeleteElement(List,1,&element);
    if(re == false) printf("DeleteElement %d Failed\n",element);
    re = DeleteElement(List,2,&element);
    if(re == false) printf("DeleteElement %d Failed\n",element);
    re = DeleteElement(List,3,&element);
    if(re == false) printf("DeleteElement %d Failed\n",element);
    */


    ShowList(List_A);
    
    int len_a = GetListLength(List_A);
    ShowSubClass(1,List_A,len_a,List_B);

    FreeList(List_A);
    FreeList(List_B);
    SAFE_FREE(List_A);
    SAFE_FREE(List_B);

    //Test ChessBoard
    //ChessBoard[0][0] = true;
    //int testtest = 1; //for gdb
    //ChessBoard[1][2] = true;
    //int test = 1; //for gdb
    if(BoardIsValid(ChessBoard))
	printf("当前棋盘有效\n");
    else
	printf("当前棋盘无效\n");
    
    ShowChessBoard(ChessBoard);

    //Queen皇后回溯
    Queen(0,CHESS_SIZE,ChessBoard);


    PAUSE();

    return 0;
}
