#include <iostream>
#include <fstream>
#include <ctime>

#define NUM 10
using namespace std;

int main()
{
    ifstream fp("D://test/input1.txt", ios::out);
    if (fp) {
        cout << "error" << endl;
    }

    srand((unsigned)time(NULL));
    
    for (int i = 1; i <= NUM; i++) {
        int a;
        fp >> a;
        cout << a << ' ';
    }

    return 0;
}