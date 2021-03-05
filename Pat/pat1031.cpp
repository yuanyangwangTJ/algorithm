//查验身份证

#include <cctype>
#include <cstring>
#include <iostream>

using namespace std;

int main()
{
    int agv[17] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };
    char verif[11] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2' };
    int N, flag = 1;
    cin >> N;

    string* str = new string[N];
    for (int i = 0; i < N; i++)
        cin >> str[i];

    for (int i = 0; i < N; i++) {
        int sum = 0, x_flag = 0;
        for (int j = 0; j < 17; j++) {
            if (isdigit(str[i][j])) {
                sum += (str[i][j] - '0') * agv[j];
            } else {
                flag = 0; //注意all passed 的输出flag
                x_flag = 1;
                break;
            }
        }
        if (x_flag) {
            cout << str[i] << endl;
            continue;
        }

        int code = sum % 11;
        if (verif[code] != str[i][str[i].length() - 1]) {
            cout << str[i] << endl;
            flag = 0;
        }
    }

    delete[] str;
    if (flag)
        cout << "All passed" << endl;

    return 0;
}