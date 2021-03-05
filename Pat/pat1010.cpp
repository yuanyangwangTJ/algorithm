#include <iostream>
using namespace std;
int main()
{
    int t,n,flag = 0;
    while (1) {
        cin>>t>>n;
        char ch = getchar();

        if (n != 0) {
            if (flag == 1) cout << " ";
            cout << t * n << " " << n - 1;
            flag = 1;
        }
        if (ch == '\n') break;
    }
    if (flag == 0) cout << "0 0";

    return 0;
}