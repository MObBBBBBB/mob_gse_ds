#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode* next;
}LNode, *LinkList;

void InitList(LinkList &L);                              // 初始化链表
int Length(LinkList L);                                  // 查表长
LNode* GetNode(LinkList L, int pos);                     // 按序号查找结点
LNode* GetNodebyVal(LinkList L, ElemType val);           // 按值查找结点
bool ListInsert(LinkList &L, int pos, ElemType e);       // 在指定位置插入指定数值的结点
bool ListDelete(LinkList &L, int pos, ElemType &e);      // 删除指定位置的结点并返回它的数值
void List_HeadInsert(LinkList &L, ElemType a[], int n);  // 头插法建立链表
void List_TailInsert(LinkList &L, ElemType a[], int n);  // 尾插法建立链表
// 题中算法总结
void ReverseList(LinkList &L);  // 反转链表

// 后续的算法使用的都是带头结点的单链表，
// 后续称第0个结点/序号为0的结点，都是指头结点
// （这个结点理论上来讲是不能访问的，但为了插入和删除算法的正确性，让其可以被访问）；
// 后续称第1个结点/序号为1的结点，都是指第一个真正存数据的结点。

// 传入参数如果是L，代表只用链表的数据，不修改链表本身；&L代表修改链表本身
// （虽然从链表的角度来讲它们其实是一样的，这里主要是为了符合408）

void InitList(LinkList &L) {
    // L = NULL  // 不带头结点直接用这句创建
    // 下面是带头结点的
    L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
}

int Length(LinkList L) {
    // 前提：L已初始化
    int len = 0;
    // 直接从第一个数据结点开始遍历，跳过头结点
    LNode *p = L->next;
    while(p != NULL) {
        p = p->next;
        len ++;
    }
    return len;
}

LNode* GetNode(LinkList L, int pos) {
    // 头结点不是第 0 个数据元素，真正的数据从第一个位置开始，
    // 但为了统一插入、删除等操作，可以允许 pos == 0 时返回头结点
    if (pos < 0) return NULL;
    LNode *p = L;
    int i = 0;
    while (p != NULL && i < pos) {
        p = p->next;
        i++;
    }
    // 返回pos位置上的结点，或者返回NULL代表位置非法/没找到
    return p;
}

LNode* GetNodebyVal(LinkList L, ElemType val) {
    // 头结点不存数据，所以从第一个结点开始匹配
    LNode *p = L->next;
    // 这里while的两个循环条件不能写反，
    // 先判断p是否存在才能保证后续访问结点数据时合法
    while(p != NULL && p->data != val) p = p->next;
    // 找到就返回对应结点，没找到返回NULL
    return p;
}

bool ListInsert(LinkList &L, int pos, ElemType e) {
    // 调用GetNode，传入pos-1用以找到插入位置前一个位置的结点
    LNode *p = GetNode(L, pos-1);
    if (p == NULL) return false;
    LNode *s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    // 下面两句顺序不能反，反了会断链
    s->next = p->next;
    p->next = s;
    // 插入成功返回true，位置非法返回false
    return true;
}

bool ListDelete(LinkList &L, int pos, ElemType &e) {
    // 写法一：按删除逻辑删除，复杂度为O(n)
    // 调用GetNode，传入pos-1用以找到删除位置前一个位置的结点
    LNode *p = GetNode(L, pos-1);
    // 这里要注意，如果 **p的后继** 不存在，也就是指定位置的结点不存在，是位置非法。
    // 如果p不存在，也就是要删除位置的结点的前驱都不存在，或者是想删头节点跳到-1位置上了，
    // 如果此时只使用p->next进行判断，则会直接导致代码出错。
    if (p == NULL || p->next == NULL) return false;
    LNode *q = p->next;
    e = q->data;
    // 真正的删除操作就下面两行
    p->next = q->next;
    free(q);

    // 写法二：通过复制+删除后继的写法，复杂度为O(1)
    // 缺点是无法删除尾结点，
    // 而且需要改造函数传入需要删除的具体结点，
    // 要不仍然需要寻找到具体结点位置再处理，复杂度仍然是O(n)
    // 如果是按位置找到结点，则
    // // 额外判断是因为GetNode可以接受0作为位置参数，但是这里是直接删除结点，头节点不应被删除
    // if (pos < 1) return false;
    // LNode *p = GetNode(L, pos);
    // // 如果改造函数并传入了要删除的结点p，则直接从这里开始
    // // 这里的p==NULL是防止位置非法，p->next==NULL是防止删尾结点，跟写法一意义不同
    // if (p == NULL || p->next == NULL) return false;
    // LNode *q = p->next;
    // e = p->data;  // 注意这里p才是在逻辑上被删除的结点
    // // 复制后继结点的数据，之后删除后继结点
    // p->data = q->data;
    // p->next = q->next;
    // free(q);

    // 删除成功返回true，并由e接收被删除结点的数值；位置非法返回false
    return true;
}

// 书本上的api实在是太蠢了，这里我改成了接收数组来建立链表的方式
// 也可以像课本一样只传入创建好的头指针，但是返回值用bool或void，在函数内部用scanf/cin等输入函数构建
// 前提：L已初始化且为空表
void List_HeadInsert(LinkList &L, ElemType a[], int n) {
    // 每次都从头节点后面插入，所以头插法天然有逆向插入的特征

    // n代表数组有效元素个数，这里直接从外部传入
    // 数组作为函数参数时会退化为指针，函数内部无法直接获得原数组长度，
    // 因此通常需要额外传入长度n，或者事先约定特殊的结束标志。
    for (int i = 0; i < n; i++)
        // 插入位置1始终合法，且按算法题约定不考虑动态内存分配失败，
        // 因此这里无需判断ListInsert的返回值。
        ListInsert(L, 1, a[i]);
}

// 前提：L已初始化且为空表
void List_TailInsert(LinkList &L, ElemType a[], int n) {
    // 用一个始终指向链表尾结点的指针来实现尾插法
    // 如果像头插法一样调用ListInsert，则会导致每次插入都需要遍历整个链表，
    // 时间复杂度会涨到O(n^2)，所以这里不调用，直接重写，这样能保证O(n)
    LNode *t = L;
    for (int i = 0; i < n; i++) {
        LNode *s = (LNode*)malloc(sizeof(LNode));
        s->data = a[i];
        s->next = NULL;
        t->next = s;
        t = s;
    }
}

/*------------------------------------------------------------------------*/
// 从这里开始就是从题中总结的算法，不是课本内容

/*反转链表*/
// 创建三个指针，cur指向当前要反转的结点，pre指向上一个结点，nxt指向下一个结点
// 先用pre存储cur，之后cur挪到nxt，nxt向后遍历一个
// （由于处理完当前节点会导致断链，所以提前用一个nxt指向下一个结点）
// 让cur的next指向pre，就完成了单个结点的反转
// 之后以类似的方法处理完整个链表，直到nxt指向NULL，代表处理到最后一个结点
// 最后让L指向的头节点指向原链表的最后一个结点，也就是cur指向的位置，就完成了反转
void ReverseList(LinkList &L) {
    LNode *cur, *nxt, *pre;
    nxt = L->next;
    cur = pre = NULL;
    while (nxt != NULL) {
        pre = cur;
        cur = nxt;
        nxt = nxt->next;
        cur->next = pre;
    }
    L->next = cur;
}