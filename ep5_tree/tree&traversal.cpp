#include<iostream>
#include<stack>
#include<queue>
using namespace std;

typedef int ElemType;
typedef struct BiTNode
{
	ElemType data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

bool InitTree(BiTree &root);
bool InsertNode(BiTNode* parent, ElemType e); // 完全二叉树
void visit(BiTNode* t);
void PreOrder(BiTree t); // 递归
void PreOrder(BiTree T); // 递推
void LevelOrder(BiTree T);



int main()
{


	return 0;
}



bool InitTree(BiTree &root)
{
	root = (BiTree)malloc(sizeof(BiTNode));
	if (!root) return false;
	root->data = NULL;
	root->lchild = nullptr;
	root->rchild = nullptr;
	return true;
}

bool InsertNode(BiTNode* parent, ElemType e) // 完全二叉树
{
	if (parent->lchild && parent->rchild) return false;
	BiTNode* child = (BiTNode*)malloc(sizeof(BiTNode));
	if (!child) return false;
	child->data = e;
	child->lchild = child->rchild = nullptr;
	if (parent->lchild) parent->rchild = child;
	else parent->lchild = child;
	return true;
}

void visit(BiTNode* t)
{
	printf("%d", t->data);
}

void PreOrder(BiTree t) // 递归
{
	if (t)
	{
		visit(t);
		PreOrder(t->lchild);
		PreOrder(t->rchild);
	}
}

void PreOrder(BiTree T) // 递推
{
	stack<BiTNode*> s;
	BiTNode* p = T;
	while (p || !s.empty())
	{
		if (p)
		{
			visit(p);
			s.push(p);
			p = p->lchild;
		}
		else
		{
			p = s.top();
			s.pop();
			// 中序将visit()改到这里，后序详见p151(3)
			p = p->rchild;
		}
	}
}

void LevelOrder(BiTree T)
{
	queue<BiTNode*> q;
	BiTNode* t = T;
	q.push(t);
	while (!q.empty())
	{
		t = q.front(); q.pop();
		visit(t);
		if (t->lchild) q.push(t->lchild);
		if (t->rchild) q.push(t->rchild);
	}
}
