#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
/*------------------------------------------------------------------------*/

// 双链表
typedef struct DNode {
    ElemType data;
    struct DNode *prior, *next;
} DNode, *DLinkList;

bool DListInsert(DLinkList &L, int pos, ElemType e);  // 在指定位置插入结点
bool DListDelete(DLinkList &L, int pos);              // 在指定位置删除结点

bool DListInsert(DLinkList &L, int pos, ElemType e) {
    // 寻找指定位置的前一个结点
    if (pos < 1) return false;
    DNode *p = L;
    int i = 0;
    while(p != NULL && i < pos-1) {
        p = p->next;
        i++;
    }
    if (p == NULL) return false;

    // 在其之后插入
    DNode *s = (DNode*)malloc(sizeof(DNode));
    s->data = e;
    // 打上标记的两条语句不能换顺序，换序会导致断链，其他可酌情调整
    // 其实宗旨就是，要保证任何一个结点都有一个可操作的指针指向，且任何指针指向的都可操作
    s->next = p->next;  //
    s->prior = p;
    p->next = s;  //
    // 如果插入位置是表尾，需要靠下面的判断逻辑防止对NULL进行指针解引用
    if(s->next != NULL) s->next->prior = s;
    return true;
}

bool DListDelete(DLinkList &L, int pos) {
    // 寻找指定位置的前一个结点
    if (pos < 1) return false;
    DNode *p = L;
    int i = 0;
    while(p != NULL && i < pos-1) {
        p = p->next;
        i++;
    }
    // p不是NULL但p->next是，代表删除的结点从逻辑上来说是尾结点后的一个空位置，这个位置是非法的
    if (p == NULL || p->next == NULL) return false;

    // 在其之后删除
    DNode *s = p->next;
    // 下面两句在顺序上没有要求
    p->next = s->next;
    // 删除位置是尾结点需要做特判
    if(s->next != NULL) s->next->prior = p;
    free(s);
    return true;
}
/*------------------------------------------------------------------------*/

// 循环单链表
typedef struct CSNode {
    ElemType data;
    struct CSNode *next;
} CSNode, *CSLinkList;

void InitCSLinkList(CSLinkList &T) {
    // 初始化时尾指针实际上指向头结点，头结点next指向自身
    T = (CSNode*)malloc(sizeof(CSNode));
    T->next = T;
}

// 这里仅使用尾指针T，这样可以使表头插入、表头删除和表尾插入均为O(1)
// 但表尾删除仍需寻找尾结点的前驱，时间复杂度为O(n)

// 具体代码不再详细写出，只给出重要逻辑
// 判空：T->next == T
// 在表尾插入新节点s，记得更新尾指针的位置到s；在表头插入，头指针用T->next即可
/*------------------------------------------------------------------------*/

// 循环双链表
typedef struct CDNode {
    ElemType data;
    struct CDNode *prior, *next;
} CDNode, *CDLinkList;

void InitCDLinkList(CDLinkList &L) {
    // 初始化时头结点的前驱和后继都指向自身
    L = (CDNode*)malloc(sizeof(CDNode));
    L->next = L;
    L->prior = L;
}

// 重要逻辑
// 判空：L->next == L && L->prior == L
// （其实只有L->next == L就够，合法循环双链表空表必定二者都满足，判定一个就可以）
/*------------------------------------------------------------------------*/

// 静态链表
#define MAXSIZE 100
typedef struct StaticNode {
    ElemType data;
    // 本质是用线性表模拟链表，所以定义更接近于线性表的定义
    // 这里不用指针了，用next索引数组下标来找到下一个结点
    int next;
} StaticLinkList[MAXSIZE];
/*------------------------------------------------------------------------*/