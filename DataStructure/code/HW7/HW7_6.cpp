/*----------------------
本题目实现欧拉路径的求解，
使用Hierholzer算法
柯尼斯堡七桥问题——一笔画问题
----------------------*/
#include <iostream>

using namespace std;

// 定义map结构
typedef struct {
    int vexnum, arcnum;
    int **map;
    int *degree;    //标记顶点的度
} Map;

// 创建Map
void CreatMap(Map &M)
{
    cin >> M.vexnum >> M.arcnum;
    int i, j, k;

    M.map = new int*[M.vexnum];
    M.degree = new int[M.vexnum];
    for (k = 0; k < M.vexnum; k++) {
        M.map[k] = new int[M.vexnum];
        M.degree[k] = 0;
        for (i = 0; i < M.vexnum; i++) {
            M.map[k][i] = 0;
        }
    }

    for (k = 0; k < M.arcnum; k++) {
        cin >> i >> j;
        --i;    --j;
        ++M.degree[i];  ++M.degree[j];
        M.map[i][j] = M.map[j][i] = 1;
    }
}// CreatMap

// 寻找欧拉路径(一笔画)
// s用来记录Euler Path
void EulerPath (Map M, int u, int s[], int temp, int &count)
{
    s[temp++] = u + 1;
    for (int v = 0; v < M.vexnum; v++) {
        if (M.map[u][v] > 0) {
            M.map[u][v]--;
            M.map[v][u]--;         
            
            EulerPath(M, v, s, temp, count);
            M.map[u][v]++;
            M.map[v][u]++;
        }
    }
    if (temp == M.arcnum + 1) {
        count++;
        for (int i = 0; i < temp; i++) {
            cout << s[i];
            if (i < temp - 1) cout << "--> ";
        }
        cout << endl;
    }
}// EulerPath

// 输出所有欧拉路径
// 此处有部分数学定理支撑
void PrintPath(Map M)
{
    int *s = new int[M.arcnum + 1];
    int oddDegree = 0;      //记录度为奇数的个数
    int temp, sum = 0;
    for (int i = 0; i < M.vexnum; i++) {
        if (M.degree[i] % 2) {
            ++oddDegree;
        }
    }
    if (oddDegree == 0 || oddDegree == 2) {
        for (int i = 0; i < M.vexnum; i++) {
            if (oddDegree == 0 || M.degree[i] % 2) {
                cout << "The solution that begin from " << i + 1 << " :" <<endl;
                temp = 0;
                int count = 0;  //记录次数
                EulerPath(M, i, s, temp, count);
                sum += count;
                printf("Begin from %d totally %d.\n\n", i + 1, count);
            }
        }
        printf("Totally %d route(s).\n", sum);
    } else {
        cout << "No solution!" <<endl;
    }
}// PrintPath

int main()
{
    Map M;
    CreatMap(M);
    PrintPath(M);

    return 0;
}
/*
5 8
1 2
1 3
1 5
2 3
2 5
3 4
3 5
4 5
*/