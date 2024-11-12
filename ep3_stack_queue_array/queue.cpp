#include<iostream>
#include<memory.h>
#define MAXSIZE 10
using namespace std;
typedef int ElemType;

typedef struct SqQueue
{
	ElemType data[MAXSIZE];
	int front, rear, size;
} SqQueue;

// 链队
typedef struct LinkedQueueNode
{
	ElemType data;
	LinkedQueueNode* next;
} LinkedQueueNode;
typedef struct
{
	LinkedQueueNode *front, *rear;
} LinkedQueue;

bool initQueue(SqQueue &q);
bool Empty(SqQueue q);
bool EnQueue(SqQueue &q, ElemType x);
bool DeQueue(SqQueue &q, ElemType &x);
ElemType GetHead(SqQueue q);



int main()
{
	// 链队 头删尾插的单链表
	// 双端队列 头尾均可插入删除的线性表

	return 0;
}



bool initQueue(SqQueue &q)
{
	memset(q.data, 0, sizeof(q.data));
	q.front = q.rear = q.size = 0;
	return true;
}

bool Empty(SqQueue q)
{
	return q.size == 0;
}

bool EnQueue(SqQueue &q, ElemType x)
{
	if (q.size == MAXSIZE) return false;
	q.data[q.rear] = x;
	q.rear = (q.rear + 1) % MAXSIZE;
	q.size++;
	return true;
}

bool DeQueue(SqQueue &q, ElemType &x)
{
	if (q.size == 0) return false;
	x = q.data[q.front];
	q.front = (q.front + 1) % MAXSIZE;
	q.size--;
	return true;
}

ElemType GetHead(SqQueue q)
{
	if (q.size == 0) return NULL;
	return q.data[q.front];
}
