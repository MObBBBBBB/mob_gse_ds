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
void PreOrder(BiTree T); // 递归
int treedepth(BiTree T);
void LevelOrder(BiTree T);
// 递推实现的前中后序遍历
void PreOrder(BiTree t);
void InOrder(BiTree t);
void PostOrder(BiTree t);



int main()
{


	return 0;
}



bool InitTree(BiTree &root)
{
	root = (BiTNode*)malloc(sizeof(BiTNode));
	if (!root) return false;
	root->data = NULL;
	root->lchild = nullptr;
	root->rchild = nullptr;
	return true;
}

bool InsertNode(BiTNode* parent, ElemType e) // 完全二叉树
{
	if (!parent || (parent->lchild && parent->rchild)) return false;
	BiTNode* child = (BiTNode*)malloc(sizeof(BiTNode));
	if (!child) return false;
	if (!parent->lchild) parent->lchild = child;
	else parent->rchild = child;
	child->data = e;
	child->lchild = child->rchild = nullptr;
	return true;
}

void visit(BiTNode* t)
{
	printf("%d", t->data);
}

void PreOrder(BiTree T) // 递归
{
	if (T) 
	{
		// 先序、后序、中序区别只在于调整以下三个语句的顺序
		visit(T);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

int treedepth(BiTree T)
{
	if (!T) return 0;
	int l = treedepth(T->lchild);
	int r = treedepth(T->rchild);
	return l>r ? l+1 : r+1;
}

void LevelOrder(BiTree T)
{
	if (!T) return;
	queue<BiTNode*> q;
	q.push(T);
	while (!q.empty())
	{
		BiTNode* t = q.front(); q.pop();
		visit(t);
		if (t->lchild) q.push(t->lchild);
		if (t->rchild) q.push(t->rchild);
	}
}

// 递推实现的前中后序遍历
void PreOrder(BiTree t) // 递推
{
	stack<BiTNode*> s;
	BiTNode* p = t;
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
			// 中序将visit()改到这里，后序详见p151(3)或PostOrder函数
			p = p->rchild;
		}
	}
}

// // 先序的另一种实现
// void PreOrder(BiTree t)
// {
// 	if (!t) return;
// 	stack<BiTNode*> s;
// 	while (t)
// 	{
// 		visit(t);
// 		if (t->lchild)
// 		{
// 			if (t->rchild) s.push(t->rchild);
// 			t = t->lchild;
// 		}
// 		else if (t->rchild) t = t->rchild;
// 		else
// 		{
// 			if (!s.empty())
// 			{
// 				t = s.top();
// 				s.pop();
// 			}
// 			else t = nullptr;
// 		}
// 	}
// }

void InOrder(BiTree t)
{
	if (!t) return;
	stack<BiTNode*> s;
	while (t || !s.empty())
	{
		if (t)
		{
			s.push(t);
			t = t->lchild;
		}
		else
		{
			t = s.top();
			s.pop();
			visit(t);
			t = t->rchild;
		}
	}
}

void PostOrder(BiTree t)
{
	if (!t) return;
	stack<BiTNode*> s;
	BiTNode* flag = nullptr;
	while (t)
	{
		if (t->lchild && flag != t->lchild && flag != t->rchild)
		{
			s.push(t);
			t = t->lchild;
		}
		else if (t->rchild && flag != t->rchild)
		{
			s.push(t);
			t = t->rchild;
		}
		else
		{
			visit(t);
			if (!s.empty())
			{
				flag = t;
				t = s.top();
				s.pop();
			}
			else t = nullptr;
		}
	}
}

