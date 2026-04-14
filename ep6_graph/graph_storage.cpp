#include<iostream>
using namespace std;

#define INF 2e30

const int MaxVertexNum = 1e2;

typedef int VertexType;
typedef int EdgeType;
typedef struct
{
	VertexType vertex[MaxVertexNum];
	EdgeType edge[MaxVertexNum][MaxVertexNum]; // 邻接矩阵  稠密图
	int vexnum, edgenum;
} MGraph;

// 邻接表  稀疏图
typedef struct ArcNode
{
	int adjvex;
	struct ArcNode* next;
	// weight or etc.
} ArcNode;

typedef struct VexNode
{
	VertexType vertex;
	ArcNode* first;
} VexNode, AdjList[MaxVertexNum];

typedef struct
{
	AdjList vertices;
	int vexnum, edgenum;
} ALGraph;
//

// 十字链表（有向图），邻接多重表（无向图）

int main()
{

	return 0;
}



