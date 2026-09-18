// 王道书版详见截图
// 本质是个树形结构
#include<iostream>
using namespace std;

const int N = 13;

int p[N];  // p[x]存储x的父节点

void initial()
{
	for (int i = 0; i < N; i++) p[i] = i;  // 初始化，每个元素的父节点都是自己
}

int find(int x)
{
	if (p[x] != x) p[x] = find(p[x]);  // 求集合编号（根节点是哪个元素），顺带着路径压缩
	return p[x];
}

void merge(int root1, int root2)
{
	p[find(root1)] = find(root2);  // 把1合并到2上
}

int main()
{


	return 0;
}



// 朴素并查集
/*
#include<iostream>

using namespace std;

const int N = 1e5 + 10;

int p[N];  // 存储每个点的父节点

int find(int x)  // 寻找根节点 + 路径压缩；p[x] = x 为根节点
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i <= n; ++i) p[i] = i;  // 初始化

    while (m--)
    {
        char op[2];
        int a, b;
        scanf("%s %d %d", op, &a, &b);
        if (op[0] == 'M') p[find(a)] = find(b);  // 合并两个集合，将 a 的根结点接到 b 的根结点下面
        else if (op[0] == 'Q') find(a) == find(b) ? puts("Yes") : puts("No");  // 查询两个数是否在一个集合中，看根节点是否相同
    }

    return 0;
}
*/

/*

一共有n个数，编号是1∼n，最开始每个数各自在一个集合中。

input:
4 5
M 1 2
M 3 4
Q 1 2
Q 1 3
Q 3 4

output:
Yes
No
Yes

*/


// 带集合个数的并查集
/*
#include<iostream>

using namespace std;

const int N = 1e5 + 10;

int p[N], size[N];  // size存储每个集合的元素个数，只有根节点的size有意义

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i <= n; ++i)
    {
        p[i] = i;
        size[i] = 1;  // 初始化时将每个点的size初始化为1
    }

    while (m--)
    {
        char op[3];
        int a, b;
        scanf("%s", op);

        if (op[0] == 'C') 
        {
            scanf("%d %d", &a, &b);
            if (find(a) == find(b)) continue;  // 如果不跳过size会翻倍
            size[find(b)] += size[find(a)];  // 合并集合时将集合个数也相加
            p[find(a)] = find(b);
        }
        else if (op[1] == '1') 
        {
            scanf("%d %d", &a, &b);
            find(a) == find(b) ? puts("Yes") : puts("No");
        }
        else if (op[1] == '2')
        {
            scanf("%d", &a);
            printf("%d\n", size[find(a)]);
        }
    }

    return 0;
}
*/

/*

给定一个包含 n 个点（编号为 1∼n ）的无向图，初始时图中没有边。

现在要进行 m 个操作，操作共有三种：

C a b，在点 a 和点 b 之间连一条边，a 和 b 可能相等；
Q1 a b，询问点 a 和点 b 是否在同一个连通块中，a 和 b 可能相等；
Q2 a，询问点 a 所在连通块中点的数量；

input:
5 5
C 1 2
Q1 1 2
Q2 1
C 2 5
Q2 5

output:
Yes
2
3

*/
