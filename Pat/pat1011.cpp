#include <iostream>
using namespace std;
int main()
{
    int K;
    long long int x,y,z;
    cin>>K;
    for( int i=0;i<K;i++ ) {
        cin>>x>>y>>z;
        cout<<"Case #"<<i+1<<": ";
        if( x+y>z ) cout<<"true"<<endl;
        else cout<<"false"<<endl;
    }
    return 0;
}