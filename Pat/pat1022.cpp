#include <iostream>
using namespace std;
int main()
{
    const int x = 32;
    int A,B,n,D;
    int i = 0;
    int num[x] = {0};
    cin>>A>>B>>D;

    n = A+B;
    do {
        num[i++] = n%D;
        n /= D;
    } while( n>=D );
    
    if( n!=0 ) num[i] = n;
    else i--;

    for( ; i>=0; i-- ) cout<<num[i];

    return 0;
}