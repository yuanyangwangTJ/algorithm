#include <iostream>
#include <cmath>
using namespace std;
bool prime( int );
int main()
{
    int cnt = 0,n;
    cin>>n;
    for( int prime1 = 2;prime1<=n-2;prime1++ )
    {
        if( prime( prime1 ) )
        {
        int prime2 = prime1 + 2;
        if( prime ( prime2 ) ) cnt++;
        }
    }
    cout<<cnt;
    return 0;
}

bool prime( int n )
{
    int i;
    bool flag = true;
    int k = int (sqrt( n ));
    for( i = 2;i<=k;i++ )
    {
        if( n%i == 0 ) break;
    }
    if( i<=k ) flag = false;
    return flag;
}