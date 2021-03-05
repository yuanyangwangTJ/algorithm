// 树的重构
#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

int main()
{
    int curDep, maxDep, curBTreeDep, maxBTreeDep, count = 0;

    string s;
    cin >> s;
    while (s != "#") {
        ++count;
        curDep = 0; maxDep = 0; 
        curBTreeDep = 0; maxBTreeDep = 0;
        stack<int> sk;
        int length = s.length();

        for (int i = 0; i < length; i++) {
            if (s[i] == 'd') {
                ++curDep;
                ++curBTreeDep;
                if (maxDep < curDep) maxDep = curDep;
                sk.push(curBTreeDep);
            } else if (s[i] == 'u') {
                --curDep;
                curBTreeDep = sk.top();
                sk.pop();
            }
            if (maxBTreeDep < curBTreeDep) maxBTreeDep = curBTreeDep;
        }

        printf("Tree %d: %d => %d\n", count, maxDep, maxBTreeDep);
        cin >> s;
    }

    return 0;
}