// 大整数乘法

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int n;
    string str1, str2;
    cin >> n;
    for (int k = 0; k < n; k++) {
        cin >> str1 >> str2;
        int n1 = str1.size(), n2 = str2.size();
        vector<int> v1, v2;
        for (int i = n1 - 1; i >= 0; --i) {
            v1.push_back(str1[i] - '0');
        }
        for (int i = n2 - 1; i >= 0; --i) {
            v2.push_back(str2[i] - '0');
        }
        vector<int> v(n1 + n2, 0);
        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < n2; ++j) {
                v[i + j] += v1[i] * v2[j];
            }
        }
        for (int i = 0; i < n1 + n2 - 1; ++i) {
            v[i + 1] += (v[i] / 10);
            v[i] = v[i] % 10;
        }
        string res;
        int m = n1 + n2 - 1;
        if (v[n1 + n2 - 1] == 0)
            m = n1 + n2 - 2;
        int flag = 1;
        for (int i = m; i >= 0; --i) {
            res += (v[i] + '0');
            if (v[i] != 0) {
                flag = 0;
            }
        }
        if(flag) cout << 0 <<endl;
        else cout << res << endl;
    }

    return 0;
}