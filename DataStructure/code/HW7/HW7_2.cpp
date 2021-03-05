// 图的遍历(邻接矩阵)
#include <iostream>
#include <queue>

using namespace std;

typedef int VRType;
typedef char VertexType;
// 邻接矩阵
typedef VRType **AdjMatrix;

typedef struct {
    VertexType *vex;        //顶点向量
    AdjMatrix arcs;         //邻接矩阵
    int vexnum, arcnum;     //图的当前顶点数和弧数
    int *visited;           //是否访问
} MGraph;

// 初始化邻接矩阵
void InitMGraph (MGraph &G) 
{
    G.vex = new VertexType[G.vexnum];
    G.arcs = new VRType*[G.vexnum];
    for (int i = 0; i < G.vexnum; i++) G.arcs[i] = new VRType[G.vexnum];
    G.visited = new int[G.vexnum];
}// InitMGraph

// 创建无向图
void CreatMGraph (MGraph &G)
{
    InitMGraph(G);
    int i, j, k;
    for (k = 0; k < G.arcnum; k++) {
        cin >> i >> j;
        G.arcs[i][j] = 1;
        G.arcs[j][i] = 1;
    }
}// CreatMGraph

// DFS
void DFS (MGraph G, int v)
{
    cout << v;
    G.visited[v] = 1;
    for (int i = 0; i < G.vexnum; i++) {
        if (G.arcs[v][i] == 1) {
            if (!G.visited[i]) {
                cout << ' ';
                DFS(G, i);
            }
        }
    }
}// DFS

// DFS遍历
void DFSTraverse (MGraph G)
{
    for (int i = 0; i < G.vexnum; i++) {
        G.visited[i] = 0;
    }
    for (int v = 0; v < G.vexnum; v++) {
        if (!G.visited[v]) {
            cout << '{';
            DFS(G, v);
            cout << '}';
        }
    }
    cout << endl;
}// DFSTraverse

// BFS
void BFS(MGraph G, int v) 
{
    queue<int> Q;
    cout << v;
    G.visited[v] = 1;
    Q.push(v);
    while (!Q.empty()) {
        v = Q.front(); Q.pop();
        for (int i = 0; i < G.vexnum; i++) {
            if (G.arcs[v][i] == 1) {
                if (!G.visited[i]) {
                    cout << ' ' << i;
                    G.visited[i] = 1;
                    Q.push(i);
                }
            }
        }
    }
}// BFS

// BFS遍历
void BFSTraverse (MGraph G)
{
    for (int i = 0; i < G.vexnum; i++) {
        G.visited[i] = 0;
    }
    for (int v = 0; v < G.vexnum; v++) {
        if (!G.visited[v]) {
            cout << '{';
            BFS(G, v);
            cout << '}';
        }
    }
    cout << endl;
}// BFSTraverse

int main()
{
    MGraph G;
    cin >> G.vexnum >> G.arcnum;
    CreatMGraph(G);
    DFSTraverse(G);
    BFSTraverse(G);

    return 0;
}