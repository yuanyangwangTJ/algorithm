#include <iostream>
using namespace std;

void max( int b,int c,int j ) 
{
    int max = b;
    int flag = 0;
    if( c>max ) max = c;
    if( j>max ) max = j;
    if( max==b ) {
        cout<<"B";
        flag = 1;
    }
    if( max==c ) {
        if( !flag ) cout<<"C";
        flag = 1;
    }
    if( max==j ) {
        if( !flag ) cout<<"J";
    }
}
int main()
{
    int N;
    int v1=0,p=0,d1=0;
    int c1=0,j1=0,b1=0,c2=0,j2=0,b2=0;
    char a,b;
    cin>>N;
    for( int i=0; i<N; i++ ) {
        cin>>a>>b;
        if( a=='C' ) {
            if( b=='C' ) {
                p++;
            } else if( b=='J' ) {
                v1++;
                c1++;
            } else {
                b2++;
                d1++;
            }
        } else if( a=='B' ) {
            if( b=='C' ) {
                b1++;
                v1++;
            } else if( b=='J' ) {
                j2++;
                d1++;
            } else {
                p++;
            }
        } else {
            if( b=='C' ) {
                c2++;
                d1++;
            } else if( b=='J' ) {
                p++;
            } else {
                j1++;
                v1++;
            }
        }
    }
    cout<<v1<<" "<<p<<" "<<d1<<endl;
    cout<<d1<<" "<<p<<" "<<v1<<endl;
    max( b1,c1,j1 );
    cout<<" ";
    max( b2,c2,j2 );

    return 0;
}