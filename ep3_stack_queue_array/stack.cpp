#include<stdio.h>
#include<stdlib.h>

#define MaxSize 100
typedef int ElemType;

// 顺序栈
typedef struct {
    ElemType data[MaxSize];
    int top;
} SqStack;

void InitStack(SqStack &S);           // 初始化栈
bool StackEmpty(SqStack S);           // 判栈空
bool Push(SqStack &S, ElemType x);    // 压栈
bool Pop(SqStack &S, ElemType &x);    // 弹栈，并用一个外部的变量接受栈顶元素
bool GetTop(SqStack S, ElemType &x);  // 读取栈顶元素
void DestroyStack(SqStack &S);        // 销毁栈

// 初始化时栈顶指针是-1
// 压栈时top先自增再存数据，弹栈时先返回数据top再自减
// 那么栈空时top是-1，满时是MaxSize-1
// 当前栈长是top+1

void InitStack(SqStack &S) {
    S.top = -1;
}

bool StackEmpty(SqStack S) {
    return S.top == -1;
}

bool Push(SqStack &S, ElemType x) {
    if (S.top == MaxSize-1) return false;
    // 压栈弹栈当然也可以按照书上写成一句，这里拆开写只是为了更清晰
    S.top++;
    S.data[S.top] = x;
    return true;
}

bool Pop(SqStack &S, ElemType &x) {
    if (S.top == -1) return false;
    x = S.data[S.top];
    S.top--;
    return true;
}

bool GetTop(SqStack S, ElemType &x) {
    if (S.top == -1) return false;
    x = S.data[S.top];
    return true;
}

void DestroyStack(SqStack &S) {
    // data是结构体内部直接包含的定长数组，并非单独动态申请，因此不能单独free
    // 将top置为-1实际效果是清空栈；静态顺序栈本身不需要专门释放内部存储空间
    S.top = -1;
}
/*------------------------------------------------------------------------*/

// 共享栈
typedef struct {
    ElemType data[MaxSize];
    int top0;
    int top1;
} SharedStack;

void InitSharedStack(SharedStack &S) {
    S.top0 = -1;
    S.top1 = MaxSize - 1;
}

// 共享栈其实两个栈共享一个数组：0号栈从低地址向高地址方向增长；1号栈从高地址向低地址方向增长
// 判空：top0 == -1 && top1 == MaxSize - 1；如果单看某个栈，则只需判断对应的top即可
// 判满：top1 - top0 == 1；此时两个指针相邻了，各自都无法再增长了
// 两个栈各自的弹栈压栈逻辑都跟顺序栈一样，只不过两个栈的弹栈压栈top的变化是相反的，这个要注意
// 共享栈的优点是能更灵活利用数组空间
/*------------------------------------------------------------------------*/

// 链栈
typedef struct LSNode{
    ElemType data;
    struct LSNode *next;
}LSNode, *LinkedStack;

// 链栈的优点是几乎不存在栈溢出，能更灵活利用内存。头结点的next指向栈顶元素。
// 链栈不存在顺序栈那种固定容量导致的栈满问题，只要系统还有可用内存，就可以继续申请结点。
// （带头结点的）链栈本质就是只用头插和头删的单链表，弹栈压栈就是在头节点的next上删除和插入结点。
/*------------------------------------------------------------------------*/