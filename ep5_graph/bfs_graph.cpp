#define MaxSize 100

// 这里采用邻接矩阵存储图，时间复杂度是O(|v|^2)；序列唯一
// 采用邻接表存储的话，时间复杂度是O(|v|+|E|)；序列不唯一，与邻接表结构有关
// 空间复杂度都是O(|v|)
typedef struct
{
    int vex[MaxSize];
    int edge[MaxSize][MaxSize];
    int vexnum, arcnum;
} MGraph;
int FirstNeighbor(MGraph G, int x);        // 返回顶点x的第一个邻接点的下标；若x不存在或没有邻接点，返回-1
int NextNeighbor(MGraph G, int x, int y);  // y是x的一个邻接点，返回按既定扫描顺序排在y之后的下一个邻接点的下标；若不存在，返回-1

// 辅助队列，用于存储已经访问但尚未扫描其邻接点的顶点
typedef struct {
    int data[MaxSize];
    int front, rear;
} Queue;
void InitQueue(Queue &Q);
bool QueueEmpty(Queue Q);
bool EnQueue(Queue &Q, int x);
bool DeQueue(Queue &Q, int &x);
Queue Q;

// 辅助数组，防止结点被重复访问
bool visited[MaxSize];

// 函数签名
void visit(int v);           // 访问函数，具体实现根据情况处理，这里仅做占位
void BFS(MGraph G, int v);   // BFS核心算法
void BFSTraverse(MGraph G);  // 做初始化准备以及保证所有顶点都被访问的封装函数

// 具体实现
void BFSTraverse(MGraph G) {
    // 所有结点初始状态都是未被访问
    for (int i = 0; i < G.vexnum; i++) visited[i] = false;
    InitQueue(Q);
    // 调用BFS的次数就是无向图的连通分量数量，有向图则没有明显联系
    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) BFS(G, i);
    }
}

void BFS(MGraph G, int v) {
    // 先访问第一个指定结点并入队
    // 发现邻接点时立即标记visited，而不是等它出队以后再标记，否则同一个顶点可能被多个顶点重复入队
    visit(v);
    visited[v] = true;
    EnQueue(Q, v);
    // 将队列里的结点都处理
    while (!QueueEmpty(Q)) {
        // 取出队头顶点，准备扫描其所有邻接点
        DeQueue(Q, v);
        // 访问所有与v邻接的结点，并将它们标记后入队
        for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
            if (!visited[w]) {
                visit(w);
                visited[w] = true;
                EnQueue(Q, w);
            }
        }
    }
}

// 对连通无向图，按照BFS首次发现顶点时经过的边可得到广度优先生成树；
// 对这颗树的BFS与对图的BFS序列是对应的
// 对非连通图，BFSTraverse最终得到广度优先生成森林；
// 对这森林中每一颗树的BFS序列拼接在一起与对图的BFS序列是对应的

// 对有向图，也可以根据BFS首次发现顶点时经过的边形成BFS搜索树/森林，
// 但BFS的调用次数与强连通分量数、弱连通分量数都没有简单对应关系，
// 且不同的起始顶点和顶点扫描顺序可能得到不同结果。