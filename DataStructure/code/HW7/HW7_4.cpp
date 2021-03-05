// 关键路径
#include <iostream>
#include <stack>

#define OK      1
#define ERROR   0

using namespace std;

typedef int Status;
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
    int indegree;           //顶点的入度
} VNode, *AdjList;

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;     //图的当前顶点数和弧数
    int kind;
    int *visited;           //是否访问
} ALGraph;

// 初始化邻接表
void InitALGraph (ALGraph &G)
{
    G.vertices = new VNode[G.vexnum];
    for (int i = 0; i < G.vexnum; i++) {
        G.vertices[i].firstarc = NULL;
        G.vertices[i].data = i + 1;
        G.vertices[i].indegree = 0;
    }
}// InitALGraph

// 定位函数
int LocateVex (ALGraph G, int u)
{
    int i;
    for (i = 0; i < G.vexnum; i++) {
        if (u == G.vertices[i].data) return i;
    }
    if (i == G.vexnum) {
        cout << "Error u!\n";
        exit(1);
    }
    return 0;
}// LocateVex

// 创建邻接表
void CreatALGraph (ALGraph &G)
{
    InitALGraph(G);
    int i, j, w, v1, v2;
    for (int k = 0; k < G.arcnum; k++) {
        cin >> v1 >> v2 >> w;
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        G.vertices[j].indegree++;   //入度+1
        ArcNode *p;
        p = new ArcNode;
        p->adjvex = j;  p->info = w;
        p->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p;
    }
}// CreatALGraph

// 求各顶点事件的最早发生时间ve，栈T用来存放拓扑结构
Status TopologicalOrder (ALGraph &G, stack<int> &T, int *ve)
{
    stack<int> S;   //用来存放度为0的顶点
    ArcNode *p;
    int count = 0;
    for (int i = 0; i < G.vexnum; i++) {
        ve[i] = 0;  //初始化最早发生时间
        if (G.vertices[i].indegree == 0) {// 度为0入栈
            S.push(i);
        }
    }
    while (!S.empty()) {
        int j = S.top();    S.pop();
        T.push(j);          ++count;// j号顶点入栈并且计数
        for (p = G.vertices[j].firstarc; p; p = p->nextarc) {
            int k = p->adjvex;      //对j号顶点的入度减1
            if (--G.vertices[k].indegree == 0) S.push(k);
            if (ve[j] + p->info > ve[k]) {
                ve[k] = ve[j] + p->info;
            }
        }
    }// while

    if (count < G.vexnum)   return ERROR;
    return OK;
}// TopologicalOrder

// 关键路径，G为有向网
Status CriticalPath (ALGraph &G) 
{
    stack<int> T;
    ArcNode *p;
    int j, k, dut;
    int *ve = new int[G.vexnum];
    int *vl = new int[G.vexnum];

    if (!TopologicalOrder(G, T, ve)) return ERROR;
    for (int i = 0; i < G.vexnum; i++) {
        vl[i] = ve[G.vexnum - 1];
    }// 初始化vl                                                                                                                                                                                                                                                                                                                                                                                                 
    cout << endl;
    while (!T.empty()) {
        j = T.top();    T.pop();
        for (p = G.vertices[j].firstarc; p; p = p->nextarc) {
            k = p->adjvex;  dut = p->info;  // dut<j, k>
            if (vl[k] - dut < vl[j]) {
                vl[j] = vl[k] - dut;
            }
        }// for  
    }
    cout << vl[G.vexnum - 1] << endl;
    for (j = 0; j < G.vexnum; j++) {
        for (p = G.vertices[j].firstarc; p; p = p->nextarc) {
            k = p->adjvex;  dut = p->info;
            int ee = ve[j]; 
            int el = vl[k] - dut;
            if (ee == el)
                cout << G.vertices[j].data << "->" << G.vertices[k].data << endl;;
        }
    }
    return OK;
}// CriticalPath

int main()
{
    ALGraph G;
    cin >> G.vexnum >> G.arcnum;
    CreatALGraph(G);
    if (!CriticalPath(G)) cout << 0;

    return 0;
}