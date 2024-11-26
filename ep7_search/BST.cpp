#include<iostream>
using namespace std;

typedef int ElemType;
typedef struct BSTNode
{
	ElemType data;
	struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;

BSTNode* BST_Search(BSTree T, ElemType key);
bool BST_Insert(BSTree &T, ElemType e);
void Create_BST(BSTree &T, ElemType num[], int numlen);


int main()
{

	return 0;
}


BSTNode* BST_Search(BSTree T, ElemType key)
{
	while (T)
	{
		if (key == T->data) return T;
		else if (key > T->data) T = T->rchild;
		else T = T->lchild;
	}
	return T;
}

bool BST_Insert(BSTree &T, ElemType e)
{
	BSTNode* t = T;
	if (!t)
	{
		t = (BSTNode*)malloc(sizeof(BSTNode));
		t->data = e;
		t->lchild = nullptr;
		t->rchild = nullptr;
		return true;
	}
	if (e == t->data) return false;
	if (e > t->data) BST_Insert(t->rchild, e);
	else BST_Insert(t->lchild, e);	
}

void Create_BST(BSTree &T, ElemType num[], int numlen)
{
	T = nullptr;
	BSTNode* t = T;
	for (int i = 0; i < numlen; i++) BST_Insert(t, num[i]);
}