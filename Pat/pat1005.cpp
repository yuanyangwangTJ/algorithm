#include <iostream>
using namespace std;
const int x = 101;

void callaz( int n,int a[x] )
{
    if( n==1 ) return;
    else {
        if( n%2 )  n = (3*n+1)/2;
        else  n /= 2;
        if( n<x )  a[n]=0;
    }
    callaz( n,a );
}

int main()
{
    int K,number[x] = {0},result[x];
    cin>>K;
    for( int i=0;i<K;i++ )  {
        int n;
        cin>>n;
        number[n] = 1;
    }
    for( int i=0;i<x;i++ ) {
        if( number[i] ) callaz(i,number);
    }
    int j=0;
    for( int i=0;i<x;i++ ) {
        if( number[i]==1 ) result[j++]=i;
    }
    for( int i=j-1;i>=0;i-- ) {
        cout<<result[i];
        if(i) cout<<" ";
    }
    return 0;
}