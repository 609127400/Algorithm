
/*
 *         �����㷨
 *  1.ʵ�����������һ��״̬�����������ó���Խ������̽���
 *  2.״̬������ʵҲ����һ�������ֻ���������һ�����һ��Ԫ�أ�ÿһ����֧����
 *    ���Ԫ�ص�һ��״̬����һ�������һ��Ԫ�أ�ÿһ����֧������һ��Ԫ����һ��
 *    ����Ԫ�ػ����ϵ�һ��״̬��
 *    �磺
 *                             []                         //��ʼ״̬Ϊ��
 *                      /             \
 *                  A״̬1           A״̬2
 *                 /     \          /     \
 *            B״̬1    B״̬2   B״̬1   B״̬2
 *          ...    ... ...  ... ... ...  ... ... 
 *
 *  3.״̬�������������ɵģ����Ǵ����ڱ���֮��
 *  4.����������ֽ�Ĺ�����ÿһ���̶�����n��״̬
 *  5.�����㷨���������������ԭ��һ��ϲ��Ҳ����Զ��ԣ���Ҫ�����ʲô����
 *    ����
 *
 *
 *
 *			2016��10��14��
 */

#define _DEBUG_CLOSE_
#include "PublicForAlgorithms.h"

typedef int ElementType;
typedef int bool;
#define true 1
#define false 0

/*
 * ��1
 * �󼯺�A���ݼ������ɼ���A�����Ӽ���Ϊһ��Ԫ���γɵļ��ϣ�Ҳ���������A�������Ӽ�
 * 1.��A = {1��2��3}
 *   A��ÿ��Ԫ�ض�������״̬�����Ӽ���(true)�Ͳ����Ӽ���(false)����˿�����������������֧����
 *   ʾ������״̬,���֧�����Ԫ�ز����Ӽ��У��ҷ�֧�����Ԫ�����Ӽ��У��������Ҷ�ӽڵ㼴Ϊ
 *   �����Ӽ��Ľ�
 *                  []             //��ʼ״̬Ϊ��
 *            [1]        []        //1���ڻ��߲��������Ӽ��е�����״̬
 *       [1,2]   [1]   [2]  []     //��1״̬�Ļ����ϣ�2���ڻ��߲��������Ӽ��е�����״̬
 *   ....                          //��2״̬�Ļ����ϣ�3���ڻ��߲��������Ӽ��е�����״̬
 * 2.��������˻����㷨��һ�����ԣ������������ȴ��ڵģ����������ڱ����еġ������״̬Ϊ�գ�һ
 *   ��������̽Ѱ�������еĽڵ�ֻ��Ϊ��̽Ѱ���ݣ�������Ҫ��Ҳ���ܵó�����Ľ�ļ��ϵ���Ҷ��
 *   �ڵ㡣
 * 3.����Ҷ�ӽڵ㶼��A�ݼ��ĺϷ��⣬��2�еĻ����������еķ�֧�����������������������ķ�֧��
 *   ����������
 * 4.e_arr    ԭ����
 *   len      ����Ԫ������
 *   i        ��ǰҪ�����Ԫ���±�
 *   temp_box ��ʱ��Ž��box
 *   temp_box ��ʱbox�ĳ���
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

//������������
//��һ�������ʾA��һ���Ӽ�
typedef struct Node
{
    ElementType e;
    struct Node* next;

}LNode,*P_List;

//��ʼ��һ������
//������ͷ����ʵ�ʲ����ã�ֻ��һ���ڱ�λ�ã�������ɾ��,λ�ü���0��
P_List InitListHead()
{
    P_List head = (P_List)malloc(sizeof(LNode));
    if(!head) return NULL;
    head->e = -1;
    head->next = NULL;

    return head;
}

//����ĳ��ȣ����Ӽ��ĳ���
int GetListLength(P_List l)
{
    if(l == NULL) return 0;
    int couter = 0;
    while(l->next){ ++couter; l=l->next; }
    return couter;
}


//��A��������Ϊ���飬��ɲ���Ҫ�˺���
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

//��ָ��λ�ò���һ������A��Ԫ��
//����λ�ô�1��ʼ
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
 * List_A ԭ����A��ÿ���ڵ�Ϊһ��Ԫ��
 * List_B ���ڴ洢�⣬��A��һ���Ӽ�������������֮�󣬼��ݹ鵽�˵�i>len_A����һ�㣬��������Ӽ�
 * i����ǰ�ݹ���Ʋ㣬Ҳ������ǰA�ĵ�i��Ԫ�ص�״̬
 * len_A List_A�ĳ��ȣ���A����Ԫ�ظ���
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
	InsertElement(List_B,k+1,element);//A�ĵ�i��Ԫ�ش������Ӽ���
	int test = 1;//for gdb
	ShowSubClass(i+1,List_A,len_A,List_B);
	DeleteElement(List_B,k+1,&element);//A�ĵ�i��Ԫ�ز������Ӽ���
	int testtest = 1;//for gdb
	ShowSubClass(i+1,List_A,len_A,List_B);
    }
}




/*
 *
 * ����2 n�ʺ�����
 * 1.����ڷ�n���ʺ�ʹ��n���ʺ�˴˲���ͬһ�У�ͬһ�л�ͬһб����
 * 2.Ҳ���������һ��״̬������ÿ�������������һ����֧
 * 3.�˱����ʽ����Ϊһ��Ļ����㷨��ʽ
 *
 */

/* 4x4����
 *
 *      * * * *
 *      * * * *
 *      * * * *
 *      * * * *    x
 *      ------------>
 */
#define CHESS_SIZE 5

bool ChessBoard[CHESS_SIZE][CHESS_SIZE] = {0};

//�жϵ�ǰ���̲����Ƿ���Ч
bool BoardIsValid(bool board[][CHESS_SIZE])
{
    int y,x;
    for(y=0; y<CHESS_SIZE; ++y)
    {
	for(x=0; x<CHESS_SIZE; ++x)
	{
	    //������Ѱ������ǰ����һ������ʱ�����ݴ˵���6����������
	    //��������ظ���������ΪֻҪһ������һ�����󣬵����ͷ�����
	    if(board[y][x])
	    {
		//y+ x+����
		int yy = y+1;
		int xx = x+1;
		while(yy<CHESS_SIZE && xx<CHESS_SIZE)
		{
		    if(board[yy][xx])
			return false;
		    ++yy; ++xx;
		}

		//y- x-����
		yy = y-1;
		xx = x-1;
		while(yy>=0 && xx>=0)
		{
		    if(board[yy][xx])
			return false;
		    --yy; --xx;
		}
		
		//y+ x-����
		yy = y+1;
		xx = x-1;
		while(yy<CHESS_SIZE && xx>=0)
		{
		    if(board[yy][xx])
			return false;
		    ++yy; --xx;
		}

		//y- x+����
		yy = y-1;
		xx = x+1;
		while(yy>=0 && xx<CHESS_SIZE)
		{
		    if(board[yy][xx])
			return false;
		    --yy; ++xx;
		}
		//y����
		yy = 0;
		xx = x;
		while(yy<CHESS_SIZE)
		{
		    if(board[yy][xx] && yy!=y)
			return false;
		    ++yy;
		}
		//x����
		yy = y;
		xx = 0;
		while(xx<CHESS_SIZE)
		{
		    if(board[yy][xx] && xx!=x)
			return false;
		    ++xx;
		}
	    }//if
	}//�ڲ�forѭ��
    }//���//forѭ��
    return true;
}

//��ʾ���̣�*�����  O��������
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
 * y �ݹ�Ĳ�����Ҳ��������ȣ�Ҳ�����̵�����y��Ĭ�ϴ�0��ʼ
 * chess_size ���̵Ĵ�С������Ĭ���������ε�
 * board ����
 *
 */
void Queen(int y,int chess_size,bool board[][CHESS_SIZE])
{  
    LINE_DEBUG("aaa");
    //n�ʺ����⣬chess_size��Сֻ����4��3�Ļ����ֻ�ܷ�2���ʺ�
    if(chess_size < 4) return;

    if(y >= chess_size)
    {
	//����������˵����ǰ�����Ѿ�������chess_size-1�к���Ĳ���
	//���������̵�n���ʺ󲼾��Ƿ���Ҫ��ģ������ڴ������Ȼ�󷵻�
	//�����ڻ����У���else���治��Ҫ���ǵݹ��Ƿ��ܵó���ȷ�Ľ⣬��ĳ��
	//�ݹ���������ַ��������Ľ⣬������Ȼ�ᵽ����ִ�У��򱣴�⣬�������
	ShowChessBoard(board);
    }
    else
    {
	int x;//���̵�x��
	//forѭ����������̽Ѱÿ�����ӷŵ�x���Ŀ����ԣ�����ÿһ�����ӿ��ܵ�ÿ��״̬
	for(x=0; x<chess_size; ++x)
	{
	    board[y][x] = true; //�ڵ�ǰλ�÷�������
	    //������if���൱�ڲü���֧�������ǰ�Ĳ��ֲ��Ϸ����򲻻��һ�������ݹ���̽
	    if(BoardIsValid(board))
	    {
		//�����ǰ���ֺϷ�����ݹ鵽��һ�㣬�����̵���һ�н�����̽��ֱ����̽����chess_size-1�У�
		//����x��0��chess_size����������Ҳ�Ϸ��ˣ����ҵ������Ĳ��ֵĽ⣬������if���ĶԽ�������
		Queen(y+1,chess_size,board);
	    }
	    //�����ǰ������Ч���²�ĵݹ���������۴��ڲ�������ȷ�Ĳ��֣���
	    //�����ߵ�ǰ������ӣ�������һ��ĵݹ飬���ص���һ��������԰����Ӱڷŵ�λ��
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
    //����������
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
	printf("��ǰ������Ч\n");
    else
	printf("��ǰ������Ч\n");
    
    ShowChessBoard(ChessBoard);

    //Queen�ʺ����
    Queen(0,CHESS_SIZE,ChessBoard);


    PAUSE();

    return 0;
}
