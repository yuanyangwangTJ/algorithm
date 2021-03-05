#include <iostream>
using namespace std;

typedef long long int INT;

INT change( INT A,int a )
{
    int t;
    INT result = 0;
    while( A>0 ) {
        t = A%10;
        A = A/10;
        if( t==a ) {
            result = result*10+a;        
        }
    }
    return result;
}
int main()
{
    INT A,B;
    int a,b;
    cin>>A>>a>>B>>b;
    cout<<change(A,a)+change(B,b);
    return 0;
}
