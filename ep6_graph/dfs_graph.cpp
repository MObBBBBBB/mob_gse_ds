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
	visit(v);
	visited[v] = true;
	for (VertexType w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w))
	{
		if (!visited[w]) dfs(G, w);
	}
}
