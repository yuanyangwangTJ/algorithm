// 拓扑排序
// 为区分与HW7_4的做法，此处使用栈的方式的另一种方式
#include <iostream>

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
        G.vertices[i].indegree = 0;
    }
}// InitALGraph

// 创建邻接表
void CreatALGraph (ALGraph &G)
{
    cin >> G.vexnum >> G.arcnum;
    InitALGraph(G);
    int i, j, w;
    for (int k = 0; k < G.arcnum; k++) {
        cin >> i >> j >> w;
        --i;    --j;                //从0排序，输入为从1开始
        G.vertices[j].indegree++;   //入度+1
        ArcNode *p;
        p = new ArcNode;
        p->adjvex = j;  p->info = w;
        p->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p;
    }
}// CreatALGraph

// 求是否具有拓扑结构
Status TopologicalOrder (ALGraph G)
{
    ArcNode *p;
    int count = 0, j, k;
    int top = -1;   //栈初始化
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].indegree == 0) {
            G.vertices[i].indegree = top;
            top = i;    //进栈
        }
    }

    while (top != -1) { // 代表栈不为空
        j = top;    top = G.vertices[top].indegree; //相当于出栈
        ++count;
        for (p = G.vertices[j].firstarc; p; p = p->nextarc) {
            k = p->adjvex;  
            --G.vertices[k].indegree;
            if (G.vertices[k].indegree == 0) {
                G.vertices[k].indegree = top;
                top = k;
            }
        }// end for
    }// end while
    
    if (count < G.vexnum)   return ERROR;
    return OK;
}// TopologicalOrder

int main()
{
    ALGraph G;
    
    CreatALGraph(G);
    if (TopologicalOrder(G)) {
        cout << 1;
    } else {
        cout << 0;
    }

    return 0;
}