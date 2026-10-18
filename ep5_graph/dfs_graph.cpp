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

// 辅助数组，防止结点被重复访问
bool visited[MaxSize];

// 函数签名
void visit(int v);           // 访问函数，具体实现根据情况处理，这里仅做占位
void DFS(MGraph G, int v);   // DFS核心算法
void DFSTraverse(MGraph G);  // 做初始化准备以及保证所有顶点都被访问的封装函数

// 具体实现
void DFSTraverse(MGraph G) {
    // 所有结点初始状态都是未被访问
    for (int i = 0; i < G.vexnum; i++) visited[i] = false;
    // 调用DFS的次数就是无向图的连通分量数量，有向图则没有明显联系
    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) DFS(G, i);
    }
}

void DFS(MGraph G, int v) {
    visit(v);
    visited[v] = true;
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        // 这里直接用递归的方式去处理遍历，就可以实现深度遍历
        if (!visited[w]) DFS(G, w);
    }
}

// 对连通无向图，按照DFS首次发现顶点时经过的边可得到深度优先生成树；
// 对这颗树的DFS与对图的DFS序列是对应的（类似于树的先根遍历）
// 对非连通图，DFSTraverse最终得到深度优先生成森林；
// 对这森林中每一颗树的DFS序列拼接在一起与对图的DFS序列是对应的

// 对有向图，也可以根据DFS首次发现顶点时经过的边形成深度优先生成树/森林，
// 但DFS的调用次数与强连通分量数、弱连通分量数都没有简单对应关系，
// 且不同的起始顶点和顶点扫描顺序可能得到不同结果。