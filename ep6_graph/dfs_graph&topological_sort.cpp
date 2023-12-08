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
