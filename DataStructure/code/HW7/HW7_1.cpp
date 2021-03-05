// 图的邻接矩阵和邻接表
#include <iostream>

using namespace std;

// 有向图，有向网，无向图，无向网
typedef enum {DG = 1, DN, UDG, UDN} GraphKind;

typedef int VRType;
typedef int InfoType;
typedef char VertexType;
// 邻接矩阵
typedef VRType **AdjMatrix;

typedef struct {
    VertexType *vex;        //顶点向量
    AdjMatrix arcs;         //邻接矩阵
    int vexnum, arcnum;     //图的当前顶点数和弧数
    int kind;               //图的种类标志
} MGraph;

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
} ALGraph;

int LocateVex (MGraph G, char u)
{
    int i;
    for (i = 0; i < G.vexnum; i++) {
        if (u == G.vex[i]) return i;
    }
    if (i == G.vexnum) {
        cout << "Error u!\n";
        exit(1);
    }
    return 0;
}

int LocateVex (ALGraph G, char u)
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
}

// 初始化邻接矩阵
void InitMGraph (MGraph &G) 
{
    G.vex = new VertexType[G.vexnum];
    G.arcs = new VRType*[G.vexnum];
    for (int i = 0; i < G.vexnum; i++) G.arcs[i] = new VRType[G.vexnum];
}

// 初始化邻接表
void InitALGraph (ALGraph &G)
{
    G.vertices = new VNode[G.vexnum];
}

// 初始化两种图
void InitGraph (MGraph &MG, ALGraph &AG)
{
    cin >> MG.vexnum >> MG.arcnum;
    AG.vexnum = MG.vexnum;
    AG.arcnum = MG.arcnum;
    InitMGraph(MG);
    InitALGraph(AG);
}

// 创建图
void CreatGraph (MGraph &MG, ALGraph &AG)
{
    int i, j, k, _i, _j, w;
    char v1, v2;
    for (i = 0; i < MG.vexnum; i++) {
        cin >> MG.vex[i];
        AG.vertices[i].data = MG.vex[i];
    }

    for (i = 0; i < MG.vexnum; i++) {
        for (j = 0; j <AG.vexnum; j++) {
            MG.arcs[i][j] = 0;
        }
        AG.vertices[i].firstarc = NULL;
    }

    int kind = MG.kind;
    switch (kind) {
        case DG: {// 有向图
            for (k = 0; k < MG.arcnum; k++) {
                cin >> v1 >> v2;
                i = LocateVex(MG, v1);
                j = LocateVex(MG, v2);
                _i = LocateVex(AG, v1);
                _j = LocateVex(AG, v2);
                MG.arcs[i][j] = 1;
                ArcNode* p = new ArcNode;
                p->adjvex = _j;
                p->nextarc = AG.vertices[_i].firstarc;
                AG.vertices[_i].firstarc = p;
            }
            break;
        }
        case DN: {// 有向网
            for (k = 0; k < MG.arcnum; k++) {
                cin >> v1 >> v2 >> w;
                i = LocateVex(MG, v1);
                j = LocateVex(MG, v2);
                _i = LocateVex(AG, v1);
                _j = LocateVex(AG, v2);
                MG.arcs[i][j] = w;
                ArcNode* p = new ArcNode;
                p->adjvex = _j;
                p->nextarc = AG.vertices[_i].firstarc;
                p->info = w;
                AG.vertices[_i].firstarc = p;
            }
            break;
        }
        case UDG: {// 无向图
            for (k = 0; k < MG.arcnum; k++) {
                cin >> v1 >> v2;
                i = LocateVex(MG, v1);
                j = LocateVex(MG, v2);
                _i = LocateVex(AG, v1);
                _j = LocateVex(AG, v2);
                MG.arcs[i][j] = 1;
                MG.arcs[j][i] = 1;
                ArcNode* p = new ArcNode;
                p->adjvex = _j;
                p->nextarc = AG.vertices[_i].firstarc;
                AG.vertices[_i].firstarc = p;
                ArcNode* q = new ArcNode;
                q->adjvex = _i;
                q->nextarc = AG.vertices[_j].firstarc;
                AG.vertices[_j].firstarc = q;
            }
            break;
        }
        case UDN: {// 无向网
            for (k = 0; k < MG.arcnum; k++) {
                cin >> v1 >> v2 >> w;
                i = LocateVex(MG, v1);
                j = LocateVex(MG, v2);
                _i = LocateVex(AG, v1);
                _j = LocateVex(AG, v2);
                MG.arcs[i][j] = w;
                MG.arcs[j][i] = w;
                ArcNode* p = new ArcNode;
                p->adjvex = _j;
                p->nextarc = AG.vertices[_i].firstarc;
                p->info = w;
                AG.vertices[_i].firstarc = p;
                ArcNode* q = new ArcNode;
                q->adjvex = _i;
                q->nextarc = AG.vertices[_j].firstarc;
                q->info = w;
                AG.vertices[_j].firstarc = q;
            }
            break;
        }
        default: ;
    }
}

// 输出邻接矩阵
void PrintMGraph (MGraph G)
{
    int i, j;
    for (i = 0; i < G.vexnum; i++) {
        for (j = 0; j < G.vexnum; j++) {
            printf("%4d", G.arcs[i][j]);
        }
        printf("\n");
    }
}

// 输出邻接表
void PrintALGraph (ALGraph G)
{
    ArcNode *p;
    for (int i = 0; i < G.vexnum; i++) {
        cout << G.vertices[i].data << "-->";
        if (G.vertices[i].firstarc) {
            p = G.vertices[i].firstarc;
            switch (G.kind) {
                case DG:
                case UDG: {
                    while (p) {
                        cout << p->adjvex << ' ';
                        p = p->nextarc;
                    }
                    break;
                }
                case DN:
                case UDN: {
                    while (p) {
                        cout << p->adjvex << ',' << p->info << ' ';
                        p = p->nextarc;
                    }
                    break;
                }
                default: ;
            }
        }
        cout << endl;
    }
}

//输出顶点向量
void PrintVex (MGraph G) 
{
    for (int i = 0; i < G.vexnum; i++) {
        cout << G.vex[i] << ' ';
    }
    cout << endl;
}

int main()
{
    MGraph MG;
    ALGraph AG;
    int kind;
    cin >> kind;
    MG.kind = AG.kind = kind;
    InitGraph(MG, AG);
    CreatGraph(MG, AG);

    PrintVex(MG);
    PrintMGraph(MG);
    PrintALGraph(AG);

    return 0;       
}