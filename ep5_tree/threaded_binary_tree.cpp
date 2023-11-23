#include<iostream>
using namespace std;

typedef int ElemType;
typedef struct ThreadNode
{
	ElemType data;
	struct ThreadNode *lchild, *rchild;
	int ltag, rtag;
	ThreadNode(ElemType x): data(x), lchild(nullptr), rchild(nullptr), ltag(0), rtag(0) {};
} ThreadNode, *ThreadTree;

ThreadNode* pre = NULL; // 辅助变量，记录构建时当前节点的前一个结点
void CreateInThreadTree(ThreadTree &T);
void InThreaded(ThreadNode *p);
void visit(ThreadNode *p);



int main()
{


	return 0;
}



// 构建中序线索二叉树
void visit(ThreadNode *p)
{
	if (!p->lchild)
	{
		p->lchild = pre;
		p->ltag = 1;
	}
	if (pre && !pre->rchild)
	{
		pre->rchild = p;
		pre->rtag = 1;
	}
	pre = p;
}

void InThreaded(ThreadNode *p)
{
	if (p)
	{
		InThreaded(p->lchild); // 先序中，这条语句要判断p->ltag==0，防止死循环，中序和后序则不用处理
		visit(p);
		InThreaded(p->rchild);
	}
}

void CreateInThreadTree(ThreadTree &T)
{
	if (T)
	{
		InThreaded(T);
		if(!pre->rchild) pre->rtag = 1;
	}
}

/*----------------------------------------------------------------------------------------------------*/

//通过中序线索二叉树进行中序遍历
ThreadNode* FirstNode(ThreadNode* p)
{
	while (p->ltag == 0) p = p->lchild;
	return p;
}

ThreadNode* NextNode(ThreadNode* p)
{
	if (p->rtag == 0) p = FirstNode(p->rchild);
	return p->rchild;
}

void visit_t(ThreadNode* p)
{
	printf("%d", p->data);
}

void InOrder(ThreadTree T)
{
	for (ThreadNode *p = FirstNode(T); p; p = NextNode(p))
		visit_t(p);
}