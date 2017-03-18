#include "PublicForAlgorithm.h"


#define TABLE_SIZE 13

int Hash_1(int key)
{
	return key%TABLE_SIZE;
}

struct Node
{
	int value;
	struct Node* next;
};

typedef struct Node* Node;

void Insert_1(Node table[],int value)
{
	Node node = (Node)malloc(sizeof(struct Node));
	if(node)
	{
		int pos = Hash_1(value);
		node->value = value;
		if(table[pos])
			node->next = table[pos];
		else
			node->next = NULL;
		
		table[pos] = node;
	}
}

Node Find_1(Node table[],int value)
{
	int pos = Hash_1(value);
	Node temp = table[pos];
	while(temp != NULL)
	{
		if(temp->value == value)
			return temp;
		temp = temp->next;
	}

	return NULL;
}

//链表哈希表
Node HashTable_1[TABLE_SIZE] = {0};

//开放寻址散列表
//(h1(k) + i*h2(k))mod m
int HashTable_2[TABLE_SIZE];
inline int Hash_2(int key,int i)
{
	return key%TABLE_SIZE + i*(key%(TABLE_SIZE - 2));	
}

void Insert_2(int arr[],int value)
{
	int salt = 0;
	while(salt<TABLE_SIZE)
	{
		int pos = Hash_2(value,salt);
		if(pos >= TABLE_SIZE)
		    pos = pos%TABLE_SIZE;
		//printf("pos = %d\n",pos);
		if(arr[pos] < 0)//等于-1，代表为空
		{
			arr[pos] = value;
			return;
		}
		++salt;
	}
}

void PrintHash_2(int arr[])
{
	int i = 0;
	while(i<TABLE_SIZE)
	{
		printf("%d  ",arr[i]);
		++i;
	}
	printf("\n");
}

int main()
{
	int key = 15;
	Node node = Find_1(HashTable_1,key);
	if(node)
		printf("node->value = %d\n",node->value);
	else
		printf("can not find the key = %d\n",key);
	printf("---Insert_1 15 to HashTable_1,then Find_1---\n");
	Insert_1(HashTable_1,16);
	Insert_1(HashTable_1,326);
	Insert_1(HashTable_1,15);
	Insert_1(HashTable_1,19);
	Insert_1(HashTable_1,38);
	Insert_1(HashTable_1,48);
	Insert_1(HashTable_1,54);
	Insert_1(HashTable_1,54);
	Insert_1(HashTable_1,6);
	Insert_1(HashTable_1,7);
	Insert_1(HashTable_1,47);
	Insert_1(HashTable_1,54);
	Insert_1(HashTable_1,35);
	Insert_1(HashTable_1,102);
	Insert_1(HashTable_1,108);
	
	key = 109;
	node = Find_1(HashTable_1,key);
	if(node)
		printf("node->value = %d\n",node->value);
	else
		printf("can not find the key = %d\n",key);
	
	//开放寻址
	srand(time(NULL));
	int i = 0;
	while(i<TABLE_SIZE)
	{
	    HashTable_2[i] = -1;
	    ++i;
	}

	i = 0;

	while(i<TABLE_SIZE)
	{
	    int value = rand();
	    Insert_2(HashTable_2,value);    
	    ++i;
	}
	
	PrintHash_2(HashTable_2);

#ifdef _WINDOWS_
	system("pause");
#endif

	return 0;
}
