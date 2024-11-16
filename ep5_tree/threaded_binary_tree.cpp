#include<iostream>
using namespace std;

typedef int ElemType;
typedef struct ThreadNode
{
	ElemType data;
	struct ThreadNode *lchild, *rchild;
	int ltag = 0, rtag = 0;
	// ThreadNode(ElemType x): data(x), lchild(nullptr), rchild(nullptr), ltag(0), rtag(0) {};
} ThreadNode, *ThreadTree;

ThreadNode* pre = NULL; // 辅助变量，记录构建时当前节点的前一个结点

// 构建中序线索二叉树
void CreateInThreadTree(ThreadTree &T);
void InThreaded(ThreadNode *p);
void visit(ThreadNode *p);

// 构建后，遍历用途函数，下列前驱后继指的是在三种遍历序列中的，不是树本身结构的
// 后继，往后搜
ThreadNode* FirstNode(ThreadNode* p);
ThreadNode* NextNode_b(ThreadNode* p);
// 前驱，往前搜
ThreadNode* LastNode(ThreadNode* p);
ThreadNode* NextNode_f(ThreadNode* p);
void visit_t(ThreadNode* p);
void InOrder(ThreadTree T);



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
		pre->rchild = nullptr; // 在构造后序线索时，应当在此处判断pre->rtag!=0，防止将原本的二叉树破坏
		pre->rtag = 1;
	}
}

/*----------------------------------------------------------------------------------------------------*/

//通过中序线索二叉树进行中序遍历
ThreadNode* FirstNode(ThreadNode* p)
{
	while (p->ltag == 0) p = p->lchild;
	return p;
}

ThreadNode* NextNode_b(ThreadNode* p)
{
	if (p->rtag == 0) return FirstNode(p->rchild);
	else return p->rchild; 
}

ThreadNode* LastNode(ThreadNode* p)
{
	while (p->rtag == 0) p = p->rchild;
	return p;
}

ThreadNode* NextNode_f(ThreadNode* p)
{
	if (p->ltag == 0) return LastNode(p->lchild);
	else return p->lchild;
}

void visit_t(ThreadNode* p)
{
	printf("%d", p->data);
}

void InOrder(ThreadTree T)
{
	for (ThreadNode* p = FirstNode(p); p; p = NextNode_b(p))
		visit_t(p);
}

