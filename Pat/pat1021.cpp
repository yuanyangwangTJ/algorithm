#include <iostream>
using namespace std;
int main()
{
    int num[10] = {0};
    int n;
    while(1) {
        n = getchar();
        if( n == '\n' ) break;
        else {
            int i = n-'0';
            num[i]++;
        }
    }
    for( int i=0; i<10; i++ ) {
        if( num[i]!=0 ) cout<<i<<":"<<num[i]<<endl;
    }
    return 0;
}