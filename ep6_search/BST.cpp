#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;

// BST的结构：与链式二叉树完全一样
typedef struct BSTNode {
    ElemType data;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BiTree;

// 除创建函数外，这里的代码都用递归实现，插入和查找的基础逻辑一致，时间复杂度和空间复杂度都是O(h)，
// 即：最好/BST较为平衡：O(logn)；较差：O(n)；
// 改用递推能优化空间复杂度到O(1)，时间复杂度不变，
// 然后递推在代码实现上，查找就是把递归改循环就行，插入就是在查找的同时多留一个parent指针用于插入。
BSTNode* BST_Search(BiTree T, ElemType key);        // BST查找元素
bool BST_Insert(BiTree &T, ElemType e);             // 插入元素
void Create_BST(BiTree &T, ElemType a[], int len);  // 构建BST
// 删除一个结点的逻辑和处理较为复杂，这里暂无代码演示，已将逻辑记录在笔记中

BSTNode* BST_Search(BiTree T, ElemType key) {
    // 注意这里匹配成功和失败都要返回结果
    // 需要先判失败，要不然后续可能会解引用NULL
    if (T == NULL || key == T->data) return T;
    else if (key < T->data) return BST_Search(T->lchild, key);
    else return BST_Search(T->rchild, key);
}

// 这里必须使用引用，因为插入操作可能需要修改当前子树的根指针：
// 例如当前 T->lchild == NULL，且新结点应插入左子树，
// 递归调用 BST_Insert(T->lchild, e) 后，需要让 T->lchild 真正指向新结点。
// 如果形参只是 BiTree T，则函数修改的只是局部指针变量，
// 无法修改上一层结点中的 lchild / rchild 指针域。
bool BST_Insert(BiTree &T, ElemType e) {
    // 基本逻辑与查找一致
    if (T == NULL) {
        T = (BSTNode*)malloc(sizeof(BSTNode));
        T->data = e;
        T->lchild = T->rchild = NULL;
        return true;
    }
    // BST中不允许出现关键字相同的结点
    if (e == T->data) return false;
    else if (e < T->data) return BST_Insert(T->lchild, e);
    else return BST_Insert(T->rchild, e);
}

// 时间复杂度：最好/BST较为平衡：O(nlogn)；较差：O(n^2)
void Create_BST(BiTree &T, ElemType a[], int len) {
    // 创建一棵新的BST，先初始化为空树
    T = NULL;
    for (int i = 0; i < len; i++) BST_Insert(T, a[i]);
}