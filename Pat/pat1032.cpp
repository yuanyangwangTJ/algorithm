// 挖掘机技术哪家强

#include <iostream>

using namespace std;

struct player {
    int no;
    int score;
};

int main()
{
    int N, max = 0;
    
    cin >> N;
    //可以设置单次接收，节省空间
    struct player* sch = new(nothrow) player[N];

    for (int i = 0; i < N; i++) {
        cin >> sch[i].no >> sch[i].score;
    }

    int* grade = new(nothrow) int[N+1];

    for (int i = 0; i < N+1; i++) {
        grade[i] = 0;
    }

    for (int i = 0; i < N; i++) {
        grade[sch[i].no] += sch[i].score;
    }

    for (int i = 1; i < N+1; i++) {
        if (grade[max] <= grade[i]) {
            max = i;
        }
    }

    cout << max << ' ' << grade[max];

    delete[] sch;
    return 0;
}