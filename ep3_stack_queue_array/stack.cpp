#include<iostream>
#include<memory.h>
#define MAXSIZE 10
using namespace std;
typedef int ElemType;

typedef struct
{
	ElemType data[MAXSIZE];
	int top;
} SqStack;

bool InitStack(SqStack &S);
bool Push(SqStack &S, ElemType x);
bool Pop(SqStack &S, ElemType &x);
ElemType GetTop(SqStack S);


int main()
{
	// 共享栈就是两个栈顶指针，一个从底扫一个顶扫
	// 栈满 top0 + 1 == top1

	// 链栈 只用头插和头删的单链表

	return 0;
}


bool InitStack(SqStack &S)
{
	memset(S.data, 0, sizeof(S.data));
	S.top = -1;
	return true;
}

bool Push(SqStack &S, ElemType x)
{
	if (S.top >= MAXSIZE - 1 || S.top < -1) return false;
	S.data[++S.top] = x;
	return true;
}

bool Pop(SqStack &S, ElemType &x)
{
	if (S.top < 0 || S.top > MAXSIZE - 1) return false;
	x = S.data[S.top--];
	return true;
}

ElemType GetTop(SqStack S)
{
	if (S.top < 0 || S.top > MAXSIZE - 1) return false;
	return S.data[S.top];
}