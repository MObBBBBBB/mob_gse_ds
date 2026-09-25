#include<stdio.h>

typedef int ElemType;

typedef struct ThreadNode {
    ElemType data;
    struct ThreadNode *lchild, *rchild;
	int ltag, rtag;  // tag为1，代表是线索；tag为0，代表是孩子
} ThreadNode, *ThreadTree;

// 中序线索化一个线索二叉树；其实就是执行一次中序遍历，在遍历途中处理
void InThread(ThreadNode *&p, ThreadNode *&pre);  // 线索化处理二叉树，遍遍历遍线索化，即中序遍历+visit函数
void CreatInThread(ThreadTree &T);                // 外部构建函数，用来做初始化和收尾处理

// 按照中序线索遍历二叉树
// 从前往后，得到中序遍历序列（如果是先序线索，只能用这一组遍历函数）
ThreadNode* Firstnode(ThreadNode *p);    // 找到最左下节点，即每个子树的第一个节点
ThreadNode* Nextnode(ThreadNode *p);     // 结合线索找到下一个节点
void InOrder(ThreadTree T);              // 中序线索前向遍历函数
// 从后往前，这里得到的是逆中序序列（如果是后序线索，只能用这一组遍历函数）
ThreadNode* Firstnode_R(ThreadNode *p);  // 找到最右下节点，即每个子树的最后一个节点
ThreadNode* Nextnode_R(ThreadNode *p);   // 结合线索找到上一个节点
void InOrder_R(ThreadTree T);            // 中序线索后向遍历函数

void visit(ThreadNode *p);  // 用于通过线索遍历的占位visit处理函数，这里不做实现，结合实际需要进行实现

// 默认二叉树已经存在且合法，只是没有构建线索
// 调用顺序：先用CreatInThread创建线索二叉树，再用InOrder或InOrder_R利用线索进行遍历

/*------------------------------------------------------------------------*/
// 构建中序线索二叉树

void InThread(ThreadNode *&p, ThreadNode *&pre) {
	if (p != NULL) {
		// 线索化p的左子树
		InThread(p->lchild, pre);  // 先序中，这条语句要判断p->ltag==0，防止死循环，中序和后序则不用处理
		
		// 线索化p, 即visit当前节点
		// 线索化p的左孩子
		if (p->lchild == NULL) {
			p->lchild = pre;
			p->ltag = 1;
		}
		// 线索化pre的右孩子
		if (pre != NULL && pre->rchild == NULL) {
			pre->rchild = p;
			pre->rtag = 1;
		}
		// pre挪到p的位置
		pre = p;

		// 线索化p的右子树
		InThread(p->rchild, pre);
	}
}

void CreatInThread(ThreadTree &T) {
	// 创建一个用于存储当前处理节点前一个遍历节点的指针
	ThreadNode *pre = NULL;
	// 这句判空必须要加，如果不加且T空，下面的pre指针会解引用NULL
	if (T != NULL) {
		// 调用中序线索化函数
		InThread(T, pre);
		// 此时pre指向中序遍历的最后一个节点，做一个收尾处理
		pre->rchild = NULL;  // 中序末结点无右孩子；若改为后序线索化，末结点仅在右孩子为空时设置空后继线索
		pre->rtag = 1;
	}
}

/*------------------------------------------------------------------------*/
// 前向遍历得到正常中序遍历序列
// 注意这里的遍历能用tag就用tag
// 如果是先序线索二叉树，则得到先序遍历序列

ThreadNode* Firstnode(ThreadNode *p) {
	// 找到节点最左下角的节点，即中序遍历的第一个节点
	while (p->ltag == 0) p = p->lchild;
	return p;
}

ThreadNode* Nextnode(ThreadNode *p) {
	// 判断右孩子是不是线索，如果是，直接跳转；如果不是，找到右子树的最左下角节点
	if (p->rtag == 0) return Firstnode(p->rchild);
	else return p->rchild;
}

void InOrder(ThreadTree T) {
	// 利用线索进行中序遍历
	for (ThreadNode* p = Firstnode(T); p != NULL; p = Nextnode(p)) 
		visit(p);
}

/*------------------------------------------------------------------------*/
// 反向遍历得到逆序中序遍历序列
// 注意这里的遍历能用tag就用tag
// 如果是后序线索二叉树，则得到逆序后序遍历序列

ThreadNode* Firstnode_R(ThreadNode *p) {
	// 找到节点最右下角的节点，即中序遍历的最后一个节点
	while (p->rtag == 0) p = p->rchild;
	return p;
}

ThreadNode* Nextnode_R(ThreadNode *p) {
	// 判断左孩子是不是线索，如果是，直接跳转；如果不是，找到左子树的最右下角节点
	if (p->ltag == 0) return Firstnode_R(p);
	else return p->lchild;
}

void InOrder_R(ThreadTree T) {
	// 利用线索进行逆中序遍历
	for (ThreadNode* p = Firstnode_R(T); p != NULL; p = Nextnode_R(p)) {
		visit(p);
	}
}