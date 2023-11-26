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

typedef struct{} Queue;

// 辅助队列
void InitQueue(Queue &Q);
void EnQueue(Queue &Q, int v);
void DeQueue(Queue &Q, int &v);
bool isEmpty(Queue Q);
void visit(int v);

int FirstNeighbor(Graph G, VertexType v);
int NextNeighbor(Graph G, VertexType v, VertexType w);

bool visited[MaxVertexNum]; // 辅助数组
Queue Q;
void BFSTraversal(Graph G); // 防止非连通图有未遍历的点和边
void bfs(Graph G, VertexType v);



int main()
{

	return 0;
}



void BFSTraversal(Graph G)
{
	// for (int i = 0; i < G.vexnum; ++i) visited[i] = false;
	InitQueue(Q);
	for (int i = 0; i < G.vexnum; i++)
	{
		if (!visited[G.vertex[i]]) bfs(G, G.vertex[i]);
	}
}

void bfs(Graph G, VertexType v)
{
	visit(v);
	EnQueue(Q, v);
	visited[v] = true;
	while (!isEmpty(Q))
	{
		DeQueue(Q, v);
		for (VertexType w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) // 这两个函数找不到存在的点时将返回-1
		{
			if (!visited[w])
			{
				visit(w);
				EnQueue(Q, w);
				visited[w] = true;
			}
		}
	}
}