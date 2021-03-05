//队的应用：寻找矩阵的四领域块数
//BFS算法求解

#include <iostream>

#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define OVERFLOW -2

using namespace std;

//寻找上下左右
const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

typedef struct {
    int x;
    int y;
} Pos;  //Pos

typedef struct {
    int num;
    bool visited;   //是否被访问
} Data;

typedef struct {
    Data** matrix;
    int row;
    int col;
} Matrix;       //定义矩阵


typedef int Status;
typedef Pos QElemType;

typedef struct QNode {
    QElemType     data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct {
    QueuePtr front;     //队头指针
    QueuePtr rear;      //队尾指针
} LinkQueue;


//矩阵初始化
Status InitMatrix (Matrix &M) {
    M.matrix = new(nothrow) Data*[M.row];
    for (int i = 0; i < M.row; i++) {
        M.matrix[i] = new(nothrow) Data[M.col];
    }
    return OK;
}

//队列初始化
Status InitQueue (LinkQueue &Q) {
    //构造一个空队列Q
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q.front) exit(OVERFLOW);
    Q.front->next = NULL;
    return OK;
}   //InitQueue

//插入元素在队尾
Status EnQueue (LinkQueue &Q, QElemType e) {
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if (!p) exit(OVERFLOW);
    p->data = e; p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}   //EnQueue

//删除队头元素
Status DeQueue (LinkQueue &Q, QElemType &e) {
    //判空
    if (Q.front == Q.rear) return ERROR;
    QueuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p) Q.rear = Q.front;
    free (p);
    return OK;
}   //DeQueue


//判断是否队空
Status QueueEmpty (LinkQueue Q) {
    return Q.front == Q.rear? TRUE : FALSE; 
}

//检验是否需要访问元素
Status NeedVisit(Data D) {
    if (D.num == 1 && D.visited == false) return TRUE;
    else return FALSE;
}

//边缘判断
Status SideJudge (Matrix M, Pos p) {
    if (p.x == 0 || p.x == M.row - 1 || p.y == 0 || p.y == M.col - 1) {
        return TRUE;
    } else return FALSE;
}

//BFS
Status BFS(Pos p, Matrix& M) {
    int notside_flag = 0;      //边缘判断，1表示存在不在边缘的数据
    LinkQueue Q;   QElemType e;
    InitQueue(Q);
    EnQueue(Q, p);
    while (!QueueEmpty(Q)) {
        Pos pos = Q.front->next->data;
        if (!notside_flag && !SideJudge(M, pos)) notside_flag = 1;

        M.matrix[pos.x][pos.y].visited = true;
        DeQueue(Q, e);

        for (int i = 0; i < 4; i++) {
            Pos pnew;
            pnew.x = pos.x + dx[i];
            pnew.y = pos.y + dy[i];
            if (pnew.x >= 0 && pnew.x < M.row && pnew.y >= 0 && pnew.y < M.col) {
                if (NeedVisit(M.matrix[pnew.x][pnew.y])) {
                    EnQueue(Q, pnew);
                }
            }
        }
    }
    if (notside_flag) return TRUE;
    else return FALSE;
}

//BFSTraverse
int BFSTraverse(Matrix &M) {
    int count = 0;
    for (int i = 0; i < M.row; i++)
    for (int j = 0; j < M.col; j++) {
        if (NeedVisit(M.matrix[i][j])) {
            Pos p; p.x = i; p.y = j;
            if (BFS(p, M)) count++;
        }
    }
    return count;
}

int main()
{
    Matrix M;
    cin >> M.row >> M.col;
    InitMatrix(M);
    for (int i = 0; i < M.row; i++) 
    for (int j = 0; j < M.col; j++) {
        cin >> M.matrix[i][j].num;
        if (M.matrix[i][j].num) M.matrix[i][j].visited = false; //设置为未访问
        else M.matrix[i][j].visited = true;                     //为0不需要访问
    }
    int count = BFSTraverse(M);
    cout << count << endl;

    return 0;
}