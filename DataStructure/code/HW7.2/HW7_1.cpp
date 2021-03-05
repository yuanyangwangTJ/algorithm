// 最小生成树
#include <iostream>

#define MAX_VERTEX_NUM  500
using namespace std;

// 下面使用邻接矩阵来表示图
typedef int VRType;
typedef int VertexType;
// 邻接矩阵
typedef VRType **AdjMatrix;

typedef struct {
    VertexType *vex;        //顶点向量
    AdjMatrix arcs;         //邻接矩阵
    int vexnum, arcnum;     //图的当前顶点数和弧数
} MGraph;

// 辅助数组
struct closeNode{
    int adjvex;             // 具有最小权值的边在集合U中的关联点
    int lowcost;            // 最小权值
} *closedge;

// 初始化邻接矩阵
void InitMGraph (MGraph &G) 
{
    G.vex = new VertexType[G.vexnum];
    G.arcs = new VRType*[G.vexnum];
    for (int i = 0; i < G.vexnum; i++) G.arcs[i] = new VRType[G.vexnum];
}// InitMGraph

// 创建无向图
void CreatMGraph (MGraph &G)
{
    cin >> G.vexnum;
    InitMGraph(G);
    int u, v;
    for (u = 0; u < G.vexnum; u++) {
        G.vex[u] = u;
        for (v = 0; v < G.vexnum; v++) {
            cin >> G.arcs[u][v];
        }
    }
}// CreatMGraph

// 返回最小权的边
int minimum (closeNode* cd, int n)
{
    int i, min = 0;
    for (min = 0; !cd[min].lowcost; min++);
    for (i = 1; i < n; i++) {
        if (cd[i].lowcost && cd[i].lowcost < cd[min].lowcost) min = i;
    }
    return min;
}// minimum

// Prime算法
void MiniSpanTree_PRIM (MGraph G, VertexType u)
{
    int k, j, i, minCost = 0;
    k = u;              // k是顶点编号

    closedge = new closeNode[G.vexnum];
    for (j = 0; j < G.vexnum; j++) {
        if (j != k) {
            closedge[j].adjvex = u;
            closedge[j].lowcost = G.arcs[u][j];
        }
    }
    closedge[k].lowcost = 0;            // 表示k顶点已经在集合U中
    for (i = 1; i < G.vexnum; i++) {    // 其余顶点处理
        k = minimum(closedge, G.vexnum);  // 找到不在T中的权值最小的边
        minCost += closedge[k].lowcost;

        closedge[k].lowcost = 0;        // 第k顶点并入U集
        for (j = 0; j < G.vexnum; j++) {
            if (G.arcs[k][j] < closedge[j].lowcost) {   // 重新选择最小边
                closedge[j].adjvex = G.vex[k];
                closedge[j].lowcost = G.arcs[k][j];
            }
        }
    }
    cout << minCost << endl;

}// MiniSpanTree_PRIM

int main()
{
    MGraph G;
    CreatMGraph(G);
    MiniSpanTree_PRIM(G, 0);

    return 0;
}