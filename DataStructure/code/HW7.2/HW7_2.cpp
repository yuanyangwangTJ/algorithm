// Dijkstra算法求最短路径
#include <iostream>

#define TRUE    1
#define FALSE   0
#define INFINITY    INT32_MAX

using namespace std;

typedef long long PathType;
// 下面使用邻接矩阵来表示图
typedef int VRType;
typedef int VertexType;
// 邻接矩阵
typedef VRType** AdjMatrix;

typedef struct {
    VertexType* vex;        // 顶点向量
    AdjMatrix arcs;         // 邻接矩阵
    int vexnum, arcnum;     // 图的当前顶点数和弧数
} MGraph;

typedef int** PathMatrix;   // 最短路径数组
typedef PathType* ShortPathTable;// 最短路径长度

// 初始化邻接矩阵
void InitMGraph(MGraph& G)
{
    G.vex = new VertexType[G.vexnum];
    G.arcs = new VRType * [G.vexnum];
    for (int i = 0; i < G.vexnum; i++) G.arcs[i] = new VRType[G.vexnum];
}// InitMGraph

// 创建无向图
void CreatMGraph(MGraph& G)
{
    InitMGraph(G);
    int u, v, k;
    // 初始化
    for (int i = 0; i < G.vexnum; i++) {
        for (int j = 0; j < G.vexnum; j++) {
            G.arcs[i][j] = G.arcs[j][i] = INFINITY;
        }
        G.arcs[i][i] = 0;
    }

    // 输入
    for (k = 0; k < G.arcnum; k++) {
        cin >> u >> v;
        --u; --v;           // 0变为1计数
        cin >> G.arcs[u][v];
        G.arcs[v][u] = G.arcs[u][v];
    }
}// CreatMGraph

// Dijkstra算法求有向图G的v0顶点到其余顶点v的最短路径
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix& P, ShortPathTable& D)
{
    int* final = new int[G.vexnum];
    int w, v;
    for (v = 0; v < G.vexnum; v++) {
        final[v] = FALSE;
        D[v] = G.arcs[v0][v];
        for (w = 0; w < G.vexnum; w++) P[v][w] = FALSE; // 设空路径
        if (D[v] < INFINITY) {
            P[v][v0] = TRUE;
            P[v0][v] = TRUE;
            P[v][v] = TRUE;
        }
    }// for
    D[v0] = 0;
    final[v0] = TRUE;   // 初始化，v0顶点属于S集
    for (int i = 1; i < G.vexnum; i++) {
        int min = INFINITY;
        for (w = 0; w < G.vexnum; w++) {
            if (!final[w]) {
                if (D[w] < min) {
                    v = w; min = D[w];
                }
            }
        }
        final[v] = TRUE;
        for (w = 0; w < G.vexnum; w++) {
            PathType temp = min + (PathType)G.arcs[v][w];
            if (!final[w] && temp < D[w]) {
                D[w] = temp;
                if (D[w] > INFINITY) D[w] = INFINITY;
                P[w] = P[v];
                P[w][w] = TRUE;
            }// if
        }

    }// for

}// ShortestPath_DIJ

// 计算最短路径
void ShortPath(MGraph G, int v0)
{
    PathMatrix P = new int* [G.vexnum];
    for (int i = 0; i < G.vexnum; i++) P[i] = new int[G.vexnum];
    ShortPathTable D = new PathType[G.vexnum];
    ShortestPath_DIJ(G, v0, P, D);
    for (int i = 0; i < G.vexnum; i++) {
        cout << D[i] << ' ';
    }
    cout << endl;
}// ShortPath


int main()
{
    MGraph G;
    int s;
    cin >> G.vexnum >> G.arcnum >> s;
    CreatMGraph(G);
    --s;
    ShortPath(G, s);


    return 0;
}