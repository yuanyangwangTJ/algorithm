#include <iostream>
using namespace std;
const int x = 100;

void reverse( int a[],int left,int right ) 
{
    int temp;
    for( int i=left;i<=(left+right)/2;i++ )
    {
        temp = a[i];
        a[i] = a[left+right-i];
        a[left+right-i] = temp;
    }
}

int main()
{
    int N,M;
    int num[x];
    cin>>N>>M;
    for( int i=0;i<N;i++ ) cin>>num[i];
    M = M%N;
    reverse( num,N-M,N-1 );
    reverse( num,0,N-M-1 );
    reverse( num,0,N-1 );
    for( int i=0;i<N;i++ )
    {
        cout<<num[i];
        if( i<N-1 ) cout<<" ";
    }
    return 0;
}