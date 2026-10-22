#define MaxSize 100

// 只有有向无环图（DAG）才能做拓扑排序（不要求图的连通）
// 这里采用邻接矩阵存储图，时间复杂度是O(|v|^2)
// 采用邻接表存储的话，时间复杂度是O(|v|+|E|)（教材用的邻接表）
// 空间复杂度都是O(|v|)
typedef struct
{
    int vex[MaxSize];
    int edge[MaxSize][MaxSize];
    int vexnum, arcnum;
} MGraph;
int FirstNeighbor(MGraph G, int x);        // 返回顶点x的第一个邻接点的下标；若x不存在或没有邻接点，返回-1
int NextNeighbor(MGraph G, int x, int y);  // y是x的一个邻接点，返回按既定扫描顺序排在y之后的下一个邻接点的下标；若不存在，返回-1

// 辅助数组
int indegree[MaxSize];  // 用于存储各个顶点的入度，方便后续快速查询和处理而不是反复查矩阵
int print[MaxSize];     // 用于记录排序好的顶点序列
// 辅助栈
// 用于临时存储当前所有入度为0的结点（用队列甚至是数组也可以，这里是为了与教材统一用了栈）
typedef struct {
    int data[MaxSize];
    int top;
} Stack;
void InitStack(Stack &S);
bool StackEmpty(Stack S);
bool Push(Stack &S, int x);
bool Pop(Stack &S, int &x);
Stack S;

// 函数签名
void Initialize(MGraph G);    // 用于构建入度数组和一些初始化处理
bool TopologicalSort(MGraph G);  // 拓扑排序

// 具体实现
void Initialize(MGraph G) {
    InitStack(S);
    for (int i = 0; i < G.vexnum; i++) {
        indegree[i] = 0;
        print[i] = -1;
    }
    // 默认G.edge[i][j]存储着顶点i指向j的边的情况
    // 那么检查一个顶点的入度只要扫列即可
    // 这里默认图是无权图；有权图只需根据情况调整即可
    for (int i = 0; i < G.vexnum; i++) {
        for (int j = 0; j < G.vexnum; j++) {
            if (G.edge[j][i] == 1) indegree[i] += 1;
        }
    }
}

// 核心思想：
// 将所有当前入度为0的顶点加入栈中。
// 每次从栈中取出一个顶点加入拓扑序列，
// 并逻辑删除该顶点及其所有出边；
// 若因此产生新的入度为0的顶点，则继续压栈。
// 重复直到栈空。
bool TopologicalSort(MGraph G) {
    // 将所有入度为0的顶点入栈
    // （孤立顶点的入度也为0，因此同样会入栈；图不要求连通，不同部分的顶点都会被处理）
    int i;
    for (i = 0; i < G.vexnum; i++) {
        if (indegree[i] == 0) Push(S, i);
    }
    // count用于记录有多少顶点排好序了，既能当作print数组的指针，也能用于判断是否有回路
    int count = 0;
    while (!StackEmpty(S)) {
        // 弹出栈顶已经确定加入拓扑排序序列的顶点，并加入序列，同时count自增1
        Pop(S, i);
        print[count] = i;
        count++;
        // 处理所有i顶点指向的顶点，让他们的入度全部减一；逻辑上等价于把i和它的出边删除
        // 如果入度减少了之后，某个顶点的入度为0了，则压栈
        for (int v = FirstNeighbor(G, i); v >= 0; v = NextNeighbor(G, i, v)) {
            indegree[v]--;
            if (indegree[v] == 0) Push(S, v);
        }
    }
    // 全部处理完毕后，如果count小于顶点数，则代表有回路，无法进行拓扑排序：
    // 因为while循环退出的逻辑是栈空，
    // 假如栈空且count小于顶点数，那么由于代码逻辑，此时图中剩余的顶点的入度都不为0，此时必定存在回路。
    // 全部处理完后count应该等于顶点数，此时print从0到(G.vexnum-1)的位置记录的就是拓扑排序序列。
    if (count < G.vexnum) return false;
    else return true;
}
// 拓扑序列可能不唯一，取决于图的结构、辅助结构、图的存储和拓扑排序代码实现
// 如果需要逆拓扑排序，则把上边的对入度的处理全部换成对出度的处理即可
// 另外也有用DFS进行拓扑排序的方法
//（提示：DFS本身的程序栈返回过程直接可以带回逆拓扑排序；
// 正拓扑排序逆序输出即可，或者也可用栈进行存储，逐个弹出就是正序列；
// 如果需要处理回路，则用标记数组记录每个结点的状态：在深度搜索时如果搜到一个结点已经被标记为正在搜索，就证明出现了回路）