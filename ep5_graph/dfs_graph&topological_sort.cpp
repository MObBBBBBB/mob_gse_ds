#include<iostream>
using namespace std;

const int MaxVertexNum = 1e2;

typedef int VertexType;
typedef int EdgeType;
typedef struct
{
	VertexType vertex[MaxVertexNum];
	EdgeType edge[MaxVertexNum][MaxVertexNum];
	int vexnum, edgenum;
} Graph;

void visit(int v);

VertexType FirstNeighbor(Graph G, VertexType v);
VertexType NextNeighbor(Graph G, VertexType v, VertexType w);

// 拓扑排序用
// bool ringflag = false;  // 是否有环
// bool ispointed[MaxVertexNum]; // 该节点是否被指向过
// int time = 0;
// int FinishTime[MaxVertexNum];

bool visited[MaxVertexNum]; // 辅助数组
void DFSTraversal(Graph G); // 防止非连通图有未遍历的点和边
void dfs(Graph G, VertexType v);


int main()
{

	return 0;
}


void DFSTraversal(Graph G)
{
	// for (int i = 0; i < G.vexnum; i++) visited[i] = false;
	for (int i = 0; i < G.vexnum; i++) if (!visited[i]) dfs(G, i);
}

void dfs(Graph G, VertexType v)
{
	// if (ringflag) return;  // 判断环路
	visit(v);
	visited[v] = true;
	// ispointed[v] = false;
	for (VertexType w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w))
	{
		// ispointed[w] = true;
		if (!visited[w]) dfs(G, w);
	}
	// if (ispointed[v]) ringflag = true;

	// time++; FinishTime[v] = time;  
	// 按时间从大到小排序后，即为拓扑排序结果
	// 不计时，只将visit(v);放在计时这一句，即为逆拓扑排序
}

// 拓扑排序：正向递推版本
// topo 保存拓扑序列中的顶点下标。
// 返回 true：排序成功。
// 返回 false：图中有环，topo 中只有已处理的部分顶点。
bool TopologicalSort(const Graph &G, int topo[])
{
    int indegree[MaxVertexNum] = {0};

    // 普通数组队列：每个顶点最多入队一次
    int q[MaxVertexNum];
    int front = 0, rear = 0;
    int count = 0;

    // 1. 统计各顶点的入度
    for (int v = 0; v < G.vexnum; v++)
        for (int w = 0; w < G.vexnum; w++)
            if (G.edge[v][w] == 1)
                indegree[w]++;

    // 2. 所有入度为 0 的顶点入队
    for (int v = 0; v < G.vexnum; v++)
        if (indegree[v] == 0)
            q[rear++] = v;

    // 3. 不断取出入度为 0 的顶点
    while (front < rear)
    {
        int v = q[front++];
        topo[count++] = v;

        // 删除 v 的所有出边：将相邻顶点入度减 1
        for (int w = 0; w < G.vexnum; w++)
        {
            if (G.edge[v][w] == 1)
            {
                indegree[w]--;
                if (indegree[w] == 0)
                    q[rear++] = w;
            }
        }
    }

    // 所有顶点都被处理，说明不存在有向环
    return count == G.vexnum;
}