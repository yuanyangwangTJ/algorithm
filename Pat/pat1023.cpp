#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int num[10] = {0};
    
    for( int i=0; i<10; i++ ) cin>>num[i];

    for( int i=1; i<10; i++ ) {
        if( num[i]!=0 ) {
            cout<<i;
            num[i]--;
            break;
        }
    }

    for( int i=0; i<10; i++ ) {
        if( num[i]!=0 ) {
            while( num[i]>0 ) {
                cout<<i;
                num[i]--;
            }
        }
    }

    return 0;
}