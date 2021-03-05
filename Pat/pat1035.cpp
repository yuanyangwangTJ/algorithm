//≤Â»Î”ÎπÈ≤¢

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int N, A[100], B[100];
    cin >> N;

    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];

    int p = 0, q = 0;
    for (; p < N-1 && B[p] <= B[p+1]; p++);
    for (q = p + 1; q < N && A[q] == B[q]; q++);

    if (q == N) {
        cout << "Insertion Sort" << endl;
        sort(A, A + p + 2);
    } else {
        cout << "Merge Sort" << endl;
        

    }

    for (int i = 0; i < N; i++) {
        if (i != 0) cout << " ";
        cout << A[i];
    }

    return 0;
}