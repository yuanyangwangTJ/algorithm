//°Â°ÍÂíÑ§±à³Ì

#include <iostream>
#include <cmath>

using namespace std;

void out_side(int N, char ch)
{
    for (int i = 0; i < N; i++) cout << ch;
    cout << endl;
}

void out_mid(int N, char ch)
{
    cout << ch;
    for (int i = 0; i < N-2; i++) cout << ' ';
    cout << ch << endl;
}

int main()
{
    int N;
    char ch;
    cin >> N >> ch;

    out_side(N, ch);
    int row = round(N/2.0) - 2;
    for (int i = 0; i < row; i++) out_mid(N, ch);
    out_side(N, ch);
    
    return 0;
}