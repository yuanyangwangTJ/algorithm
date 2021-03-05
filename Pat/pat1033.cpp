#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
bool hashtable[256] = { false };
int main()
{
    int num = 0;
    string a, b;
    getline(cin, a);
    getline(cin, b);
    for (int i = 0; i < a.size(); i++) {
        hashtable[a[i]] = true;
        if (isupper(a[i]))
            hashtable[a[i] + 32] = true;
    }
    for (int i = 0; i < b.size(); i++) {
        if (isupper(b[i])) {
            if (hashtable[b[i]] == false && hashtable['+'] == false) {
                cout << b[i];
            }
        } else {
            if (hashtable[b[i]] == false)
                cout << b[i];
        }
    }
    printf("\n");

    return 0;
}