#include <iostream>

using namespace std;

int exgcd(int a, int b, int& x, int& y) {
    if(a < b) return exgcd(b, a, y, x);
    if(b == 0) {
        x = 1; y = 0;
        return a;
    } else {
        int x1;
        int d = exgcd(b, a % b, x1, x);
        y = x1 - a / b * x;
        return d;
    }
}

// int exgcd(int a, int b, int& x, int& y) {
//     if(a < b) return exgcd(b, a, y, x);
//     int m = 0, n = 1;
//     x = 1; y = 0;
//     while(b != 0) {
//         int d = a / b, t;
//         t = m; m = x - d * t; x = t;
//         t = n; n = y - d * t; y = t;
//         t = a % b; a = b; b = t;
//     }
//     return a;
// }

int inv(int n, int p) {
    int x, y;
    if(exgcd(n, p, x, y) == 1) {
        x = x % p;
        return x >= 0 ? x : p + x;
    } else {
        return -1;
    }
}

int main()
{
    int n, p;
    cout << "Input number and modulus: " << endl;
    while (1) {
        cin >> n >> p;
        int Inv = inv(n, p);
        printf ("Inv = %d\n", Inv);
    }
    return 0;
}