//完美数列
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N;
    long long p;
    cin >> N >> p;
    vector<long long> vec(N);
    
    for(int i = 0; i < N; i++) cin >> vec[i];
    sort(vec.begin(), vec.end());

    int result = 0, temp = 0;

    for (int i = 0; i < N; i++) {
        for (int j = i+result; j < N; j++) {
            if (vec[j] <= vec[i]*p) {
                temp = j-i+1;
                if (result < temp) {
                    result = temp;
                }
            } else {
                break;
            }
        }
    }

    cout << result;

    return 0;
}