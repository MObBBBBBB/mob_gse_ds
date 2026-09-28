// 这里的实现不与王道书一致，但是函数签名和变量名称均一致
#define MaxSize 100
typedef int ElemType;

// S就是并查集；S[x]代表x的父节点
ElemType S[MaxSize];

void Initial(ElemType S[]);                      // 初始化并查集
int Find(ElemType S[], ElemType x);              // 查询所属集合，并路径压缩
void Union(ElemType S[], int Root1, int Root2);  // 合并集合

void Initial(ElemType S[]) {
    // 初始化时所有元素的根就是自己
    for (int i = 0; i < MaxSize; i++) S[i] = i;
}

int Find(ElemType S[], ElemType x) {
    // 查找x所在集合的根结点，并将本次查找路径上的所有结点直接连接到根结点，实现路径压缩
    // 将结点几乎都处理后，可以将树结构几乎做到一个根结点下连着展平的一层子结点
    // 只有执行Find时才会触发路径压缩
    if (S[x] != x) S[x] = Find(S, S[x]);
    return S[x];
}

void Union(ElemType S[], int Root1, int Root2) {
    // 将Root1代表的集合合并到Root2，Root2是合并后的树的根结点
    // 合并操作除了两个根节点以外都会触发压缩
    S[Find(S, Root1)] = Find(S, Root2);
}