#include<iostream>
using namespace std;

typedef struct BSTNode
{
	int data;
	struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;

BSTNode* BST_Search(BSTree T, int k);
bool BST_Insert(BSTree &T, int k);
void Create_BST(BSTree T, int num[], int n);


int main()
{

	return 0;
}


BSTNode* BST_Search(BSTree T, int key)
{
	while (T || key != T->data)
	{
		if (key < T->data) T = T->lchild;
		else T = T->rchild;
	}
	return T;
}

bool BST_Insert(BSTree &T, int key)
{
	if (!T)
	{
		T = (BSTNode*)malloc(sizeof(BSTNode));
		T->data = key;
		T->lchild = T->rchild = NULL;
		return 1;
	}
	if (T->data == key) return 0;
	if (T->data < key) BST_Insert(T->lchild, key);
	else BST_Insert(T->rchild, key);
}

void Create_BST(BSTree T, int num[], int n)
{
	T = NULL;
	for (int i = 0; i < n; i++) BST_Insert(T, num[i]);
}