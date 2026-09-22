#include<stdio.h>

typedef int ElemType;

typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void visit(BiTNode *t);  // 访问函数：为了保证算法正确占位用，这里不做实现，可根据需要填写具体的代码

void PreOrder(BiTree T);    // 先序遍历（DFS）
void InOrder(BiTree T);     // 中序遍历
void PostOrder(BiTree T);   // 后序遍历
void LevelOrder(BiTree T);  // 层次遍历（BFS）

// 先序、中序、后序遍历都采用递归写法，区别只是visit函数的位置
// 时间复杂度为O(n)，空间复杂度为O(h)（借助了程序栈；h是树的高度）
// 这三种遍历都是DFS，但如果按照后续图章节DFS的定义，只有先序遍历对应

void PreOrder(BiTree T) {
    // 注意这里指针探到空的时候是递归出口
    // 同时记得这里是if判断，千万不要写循环，非常容易出现死循环
    if (T != NULL) {
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T) {
    if (T != NULL) {
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}

void PostOrder(BiTree T) {
    if (T != NULL) { 
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }
}

// 层序遍历也叫BFS

// 需要借助一个辅助队列存储当前被访问结点的孩子结点
// 这里直接从 ep3_stack_queue_array\queue.cpp 借鉴定义，保证语法正确，不具体实现
// 注意这里队列里的数据都是树结点
#define MaxSize 100
typedef struct Queue {
    BiTNode *data[MaxSize];
    int front, rear;
} Queue;

void InitQueue(Queue &Q);  // 初始化队列
void EnQueue(Queue &Q, BiTNode *t);  // 树结点入队
void DeQueue(Queue &Q, BiTNode *&t);  // 树节点出队，并将出队结点用t带回
bool IsEmpty(Queue Q);  // 队列判空

void LevelOrder(BiTree T) {
    // 初始化辅助队列并让树T的根节点（指针）入队
    Queue Q;
    InitQueue(Q);
    EnQueue(Q, T);

    // 一层一层遍历
    BiTNode *t;
    while (!IsEmpty(Q)) {
        DeQueue(Q, t);
        visit(t);
        if (t->lchild != NULL) EnQueue(Q, t->lchild);
        if (t->rchild != NULL) EnQueue(Q, t->rchild);
    }
}