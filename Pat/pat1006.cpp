#include <iostream>
using namespace std;
int getint( int n );
int main()
{
    int n,ge,shi,bai;
    cin>>n;
    ge = getint( n );
    n /=10;
    shi= getint( n );
    n /=10;
    bai= getint( n );
    for(;bai>0;bai--)
    {
        cout<<"B";
    }
    for(;shi>0;shi--)
    {
        cout<<'S';
    }
    for( int cnt = 1;cnt<=ge;cnt++ )
    {
        cout<<cnt;
    }
    return 0;
}
int getint( int n )
{
    int num;
    num = n%10;
    return num;
}