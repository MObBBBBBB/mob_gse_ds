#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef struct BLNode
{
    ElemType data;
    struct BLNode* prior;
    struct BLNode* next;
}BLNode, *BioLinkList;

bool InitList(BioLinkList &L);
bool Empty(BioLinkList L);
int length(BioLinkList L);
bool BuildList_HeadInsert(BioLinkList &L);
bool BuildList_TailInsert(BioLinkList &L);
BLNode* GetElem(BioLinkList L, int pos);
BLNode* LocateElem(BioLinkList L, ElemType e);
bool InsertNextNode(BLNode* p, ElemType e);
bool InsertPriorNode(BLNode* p, ElemType e);
bool InsertNode(BioLinkList &L, int pos, ElemType e);
bool DeleteNode(BioLinkList &L, int pos, ElemType &e);
bool DeleteNode(BioLinkList &L, BLNode* p);


int main()
{
	BioLinkList L;
	InitList(L);
	printf("--E-N-D--");
	
    return 0;
}


bool InitList(BioLinkList &L)
{
	L = (BLNode*)malloc(sizeof(BLNode));
	if (!L) return false;
	L->data = -114514;
    L->prior = NULL;
	L->next = NULL;
	return true;
}

bool Empty(BioLinkList L)
{
	return (!L || !L->next || !L->prior);
}

int length(BioLinkList L)
{
	int i = 0;
	BLNode* p = L;
	while (p->next)
	{
		p = p->next;
		++i;
	}
	return i;
}

BLNode* GetElem(BioLinkList L, int pos)
{
	if (pos < 0) return NULL;
	BLNode* p = L;
	int j = 0;
	while (p && j < pos)
	{
		p = p->next;
		++j;
	}
	return p;
}

bool InsertNextNode(BLNode* p, ElemType e)
{
	if (!p) return false;
	BLNode* s = (BLNode*)malloc(sizeof(BLNode));
	if (!s) return false;
	s->data = e;
    s->prior = p;
	s->next = p->next;
	p->next = s;
	return true;
}

bool InsertPriorNode(BLNode* p, ElemType e)
{
	if (!p) return false;
	BLNode* s = (BLNode*)malloc(sizeof(BLNode));
	if (!s) return false;
	s->data = e;
    s->next = p;
	s->prior = p->prior;
	p->prior = s;
	return true;
}

// next start their
// next start their
// next start their
// remember to check

bool InsertNode(BioLinkList &L, int pos, ElemType e)
{
	if (pos < 1) return false;
	BLNode* p = GetElem(L, pos-1);
	return InsertNextNode(p, e);
}

bool DeleteNode(BioLinkList &L, int pos, ElemType &e)
{
	if (pos < 1) return false;
	BLNode* p = GetElem(L, pos-1);
	if (!p || !p->next) return false;
	BLNode* s = p->next;
	e = s->data;
	p->next = s->next;
	free(p);
	return true;
}

bool DeleteNode(BioLinkList &L, BLNode* p)
{
	if (!p) return false;
	if (!(p->next)) // test
	{
		BLNode* s = L;
		int j = 0;
		while (s->next->next) s = s->next;
		s->next = NULL;
		free(p);
	}
	else
	{
		BLNode* s = p->next;
		p->data = s->data;
		p->next = s->next;
		free(p);
	}
	return true;
}

BLNode* LocateElem(BioLinkList L, ElemType e)
{
	BLNode* p = L->next;
	while (p && p->data != e) p = p->next;
	return p;
}

bool BuildList_HeadInsert(BioLinkList &L)
{
	ElemType e;
	// if ElementType is modified.Remember to modify the format parameter of scanf()
	while (scanf("%d", &e))
	{
		if (InsertNextNode(L, e)) continue;
		else return false;
	}
	return true;
}

bool BuildList_TailInsert(BioLinkList &L)
{ 
	ElemType e;
	BLNode* t = L;
	while (scanf("%d", &e))
	{
		if (InsertNextNode(t, e)) t = t->next;
		else return false;
	}
	return true;
}

