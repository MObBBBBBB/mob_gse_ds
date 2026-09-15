#include<stdio.h>
#include<stdlib.h>

#define MaxSize 100
typedef int ElemType;

// 顺序队列
typedef struct {
    ElemType data[MaxSize];
    int front, rear;
} SqQueue;

void InitQueue(SqQueue &Q);             // 初始化队列
bool QueueEmpty(SqQueue Q);             // 队列判空
bool EnQueue(SqQueue &Q, ElemType x);   // 入队
bool DeQueue(SqQueue &Q, ElemType &x);  // 出队，并带出队头元素
bool GetHead(SqQueue Q, ElemType &x);   // 读取队头元素

// 采用牺牲一个存储单元的设计来区分队空和队满，这样符合教材/408语境
// 同时采用循环队列的设计，防止“上溢”这种假溢出
// 补充：队列长度：(Q.rear - Q.front + MaxSize) % MaxSize

void InitQueue(SqQueue &Q) {
    // 初始化时头尾指针都指向内部数组的起始位置
    Q.front = Q.rear = 0;
}

bool QueueEmpty(SqQueue Q) {
    // 判空逻辑
    return Q.front == Q.rear;
}

bool EnQueue(SqQueue &Q, ElemType x) {
    // 下面这句就是判定队满的逻辑，空出一个位置永远不用
    // 队满时队尾指针一定与队头指针从逻辑上差一个位置
    if ((Q.rear+1) % MaxSize == Q.front) return false;
    // 入队时采用先向rear指向的位置存入数据，之后rear逻辑上自增1
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear+1) % MaxSize;
    return true;
}

bool DeQueue(SqQueue &Q, ElemType &x) {
    if (Q.front == Q.rear) return false;
    // 出队时采用先带出front指向的位置的数据，之后front逻辑上自增1
    x = Q.data[Q.front];
    Q.front = (Q.front+1) % MaxSize;
    return true;
}

bool GetHead(SqQueue Q, ElemType &x) {
    // 队空没有数据，无法返回
    if (Q.front == Q.rear) return false;
    // 只返回，不出队
    x = Q.data[Q.front];
    return true;
}
/*------------------------------------------------------------------------*/

// 链队
typedef struct LQNode {
    ElemType data;
    struct LQNode *next;
} LQNode;
typedef struct LinkQueue {
    LQNode *front, *rear;
} LinkQueue;

// 本质是头删尾插的单链表（带头结点）
// 逻辑基本上与顺序队列一致，只是不用牺牲一个存储单元，也不用非要做成循环形式

void InitLinkQueue(LinkQueue &Q);              // 初始化队列
bool LinkQueueEmpty(LinkQueue Q);              // 队列判空
void EnLinkQueue(LinkQueue &Q, ElemType x);    // 入队
bool DeLinkQueue(LinkQueue &Q, ElemType &x);   // 出队，并带出队头元素
bool GetLinkedHead(LinkQueue Q, ElemType &x);  // 读取队头元素

void InitLinkQueue(LinkQueue &Q) {
    Q.front = Q.rear = (LQNode*)malloc(sizeof(LQNode));
    Q.front->next = NULL;
}

bool LinkQueueEmpty(LinkQueue Q) {
    // 直接从地址上判断两个指针是否同时指向一个位置
    return Q.front == Q.rear;
}

void EnLinkQueue(LinkQueue &Q, ElemType x) {
    // 从算法逻辑上不用判断队满（链队不存在固定容量导致的队满，只要还能成功申请结点就能继续入队）
    LQNode *s = (LQNode*)malloc(sizeof(LQNode));
    s->data = x;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
}

bool DeLinkQueue(LinkQueue &Q, ElemType &x) {
    if (Q.front == Q.rear) return false;
    LQNode *s = Q.front->next;
    x = s->data;
    Q.front->next = s->next;
    // 必须加下面这条特殊判断，因为如果只剩最后一个数据结点s，
    // 删除s后rear仍然指向s（悬空指针），必须让rear重新指向头结点，与front重合。
    if (Q.rear == s) Q.rear = Q.front;
    free(s);
    return true;
}

bool GetLinkedHead(LinkQueue Q, ElemType &x) {
    if (Q.front == Q.rear) return false;
    x = Q.front->next->data;
    return true;
}
/*------------------------------------------------------------------------*/

// 双端队列
typedef struct {
    ElemType data[MaxSize];
    int front, rear;
} DSqQueue;

// 双端队列就是队头和队尾都允许插入和删除
/*------------------------------------------------------------------------*/