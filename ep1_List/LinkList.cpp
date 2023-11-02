#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;

typedef struct LNode
{
	ElemType data;
	struct LNode* next;
}LNode, *LinkList; 

bool InitList(LinkList &L);
bool Empty(LinkList L);
int length(LinkList L);
bool BuildList_HeadInsert(LinkList &L);
bool BuildList_TailInsert(LinkList &L);
LNode* GetElem(LinkList L, int pos);
LNode* LocateElem(LinkList L, ElemType e);
bool InsertNextNode(LNode* p, ElemType e);
bool InsertPriorNode(LNode* p, ElemType e);
bool InsertNode(LinkList &L, int pos, ElemType e);
bool DeleteNode(LinkList &L, int pos, ElemType &e);
bool DeleteNode(LinkList &L, LNode* p);


int main()
{
	LinkList L;
	InitList(L);
	printf("--E-N-D--");
	
    return 0;
}


bool InitList(LinkList &L)
{
	L = (LNode*)malloc(sizeof(LNode));
	if (L == NULL) return false;
	L->data = -114514;
	L->next = NULL;
	return true;
}

bool Empty(LinkList L)
{
	return (!L || !L->next);
}

int length(LinkList L)
{
	int i = 0;
	LNode* p = L;
	while (p->next)
	{
		p = p->next;
		++i;
	}
	return i;
}

LNode* GetElem(LinkList L, int pos)
{
	if (pos < 0) return NULL;
	LNode* p = L;
	int j = 0;
	while (p && j < pos)
	{
		p = p->next;
		++j;
	}
	return p;
}

bool InsertNextNode(LNode* p, ElemType e)
{
	if (!p) return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (!s) return false;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}

bool InsertPriorNode(LNode* p, ElemType e)
{
	if (!p) return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (!s) return false;
	s->next = p->next;
	p->next = s;
	s->data = p->data;
	p->data = e;
	return true;
}

bool InsertNode(LinkList &L, int pos, ElemType e)
{
	if (pos < 1) return false;
	LNode* p = GetElem(L, pos-1);
	return InsertNextNode(p, e);
}

bool DeleteNode(LinkList &L, int pos, ElemType &e)
{
	if (pos < 1) return false;
	LNode* p = GetElem(L, pos-1);
	if (!p || !p->next) return false;
	LNode* s = p->next;
	e = s->data;
	p->next = s->next;
	free(p);
	return true;
}

bool DeleteNode(LinkList &L, LNode* p)
{
	if (!p) return false;
	if (!(p->next)) // test
	{
		LNode* s = L;
		int j = 0;
		while (s->next->next) s = s->next;
		s->next = NULL;
		free(p);
	}
	else
	{
		LNode* s = p->next;
		p->data = s->data;
		p->next = s->next;
		free(p);
	}
	return true;
}

LNode* LocateElem(LinkList L, ElemType e)
{
	LNode* p = L->next;
	while (p && p->data != e) p = p->next;
	return p;
}

bool BuildList_HeadInsert(LinkList &L)
{
	int e;
	// if ElementType is modified.Remember to modify the format parameter of scanf()
	while (scanf("%d", &e))
	{
		if (InsertNextNode(L, e)) continue;
		else return false;
	}
	return true;
}

bool BuildList_TailInsert(LinkList &L)
{ 
	int e;
	LNode* t = L;
	while (scanf("%d", &e))
	{
		if (InsertNextNode(t, e)) t = t->next;
		else return false;
	}
	return true;
}

