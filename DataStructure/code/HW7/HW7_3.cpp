// 图的遍历(邻接表)
#include <iostream>
#include <queue>

using namespace std;

typedef int VRType;
typedef int InfoType;
typedef int VertexType;

// 邻接表
typedef struct ArcNode {
    int adjvex;             //该弧所指向的顶点的位置
    struct ArcNode *nextarc;//指向下一条弧的指针
    InfoType info;          //指向弧相关信息的指针
} ArcNode;

typedef struct VNode {
    VertexType data;        //顶点信息
    ArcNode *firstarc;      //指向第一条依附该顶点的弧的指针
} VNode, *AdjList;

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;     //图的当前顶点数和弧数
    int kind;               //图的种类标志
    int *visited;           //是否访问
} ALGraph;

// 初始化邻接表
void InitALGraph (ALGraph &G)
{
    G.vertices = new VNode[G.vexnum];
    G.visited = new int[G.vexnum];
    for (int i = 0; i < G.vexnum; i++) {
        G.vertices[i].firstarc = NULL;
        G.vertices[i].data = i;
    }
}

void CreatALGraph (ALGraph &G)
{
    InitALGraph(G);
    int i, j;
    for (int k = 0; k < G.arcnum; k++) {
        cin >> i >> j;
        ArcNode *p, *q;
        p = new ArcNode;
        p->adjvex = j;
        p->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p;
        q = new ArcNode;
        q->adjvex = i;
        q->nextarc = G.vertices[j].firstarc;
        G.vertices[j].firstarc = q;
    }
}

// DFS
void DFS (ALGraph G, int v)
{
    cout << G.vertices[v].data;
    G.visited[v] = 1;
    ArcNode *p = G.vertices[v].firstarc;
    while (p) {
        if (!G.visited[p->adjvex]) {
            cout << ' ';
            DFS(G, p->adjvex);
        }
        p = p->nextarc;
    }
}// DFS

// DFS遍历
void DFSTraverse (ALGraph G)
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
void BFS(ALGraph G, int v) 
{
    queue<int> Q;
    ArcNode *p;
    cout << G.vertices[v].data;
    G.visited[v] = 1;
    Q.push(v);
    while (!Q.empty()) {
        v = Q.front(); Q.pop();
        p = G.vertices[v].firstarc;
        while (p) {
            if (!G.visited[p->adjvex]) {
                cout << ' ' << G.vertices[p->adjvex].data;;
                G.visited[p->adjvex] = 1;
                Q.push(p->adjvex);
            }
            p = p->nextarc;
        }
    }
}// BFS

// BFS遍历
void BFSTraverse (ALGraph G)
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
    ALGraph G;
    cin >> G.vexnum >> G.arcnum;
    CreatALGraph(G);
    DFSTraverse(G);
    BFSTraverse(G);
    return 0;
}