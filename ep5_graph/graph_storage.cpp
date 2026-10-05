#define MaxVertexNum 100

typedef char VertexType;  // 邻接顶点的名称类型
typedef int EdgeType;


// 邻接矩阵
typedef struct
{
    VertexType vex[MaxVertexNum];
    EdgeType edge[MaxVertexNum][MaxVertexNum];
    int vexnum, arcnum;
} MGraph;


// 邻接表

// 接在顶点表每一个元素后的链表：
// 无向图用于表示所有与这个顶点邻接的边和顶点，有向图只表示出边及其连接顶点
typedef struct ArcNode
{
    VertexType adjvex;  // 这里为了统一定义，用VertexType统一表示结点自己用什么类型的数据表示
    struct ArcNode *nextarc;
} ArcNode;
// 顶点表，其实这就是邻接表了
typedef struct VNode
{
    VertexType vex;
    ArcNode *firstarc;
} VNode, AdjList[MaxVertexNum];
// 邻接表外层封装，为了携带数量信息
typedef struct
{
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;


// 操作函数签名（邻接矩阵版本）
bool Adjacent(MGraph G, VertexType x, VertexType y);                     // 判断是否存在边 (x, y) 或弧 <x, y>
void Neighbors(MGraph G, VertexType x);                                  // 列出顶点 x 的所有邻接边
bool InsertVertex(MGraph &G, VertexType x);                              // 插入顶点 x
bool DeleteVertex(MGraph &G, VertexType x);                              // 删除顶点 x 及其相关的所有边
bool AddEdge(MGraph &G, VertexType x, VertexType y);                     // 添加边 (x, y) 或弧 <x, y>
bool RemoveEdge(MGraph &G, VertexType x, VertexType y);                  // 删除边 (x, y) 或弧 <x, y>
VertexType FirstNeighbor(MGraph G, VertexType x);                        // 返回顶点 x 的第一个邻接点的名称；若 x 不存在或没有邻接点，返回约定的无邻接点标记
VertexType NextNeighbor(MGraph G, VertexType x, VertexType y);           // y 是 x 的一个邻接点，返回按既定扫描顺序排在 y 之后的下一个邻接点的名称；若不存在，返回约定的无邻接点标记
EdgeType Get_edge_value(MGraph G, VertexType x, VertexType y);           // 获取已存在的边 (x, y) 或弧 <x, y> 的权值
bool Set_edge_value(MGraph &G, VertexType x, VertexType y, EdgeType v);  // 设置已存在的边 (x, y) 或弧 <x, y> 的权值为 v