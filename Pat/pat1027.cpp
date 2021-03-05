#include <iostream>
#include <cmath>
using namespace std;

void space( int n )
{
    for( int i=0; i<n; i++ ) cout<<" ";
}
void star( int n,char c )
{
    for( int i=0; i<(2*n-1); i++ ) putchar(c);
}
int main()
{
    int N,n;
    char c;
    cin>>N>>c;

    n = sqrt( (N+1)/2 );
    for( int i=n; i>=1; i-- ) {
        space( n-i );
        star( i,c );
        cout<<endl;
    }
    for( int i=2; i<=n; i++ ) {
        space( n-i );
        star( i,c );
        cout<<endl;
    }

    int rest = N-(2*n*n-1);
    cout<<rest;
    return 0;
}