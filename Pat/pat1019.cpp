#include <iostream>
using namespace std;

void Rank( int num[] ) 
{
    int i,j;
    for( i=0; i<3; i++ )
    for( j=0; j<3-i; j++ ) {
        if( num[j]>num[j+1] ) {
            int t = num[j];
            num[j] = num[j+1];
            num[j+1] = t;
        }
    }
}

int main()
{
    int num[4];
    int max=0,min=0,n;
    cin>>n;
    for( int i=0; i<4; i++ ) {
        num[i] = n%10;
        n /= 10;
    }
    do {
        Rank( num );
        max = 0;
        min = 0;
        for( int i=0; i<4; i++ ) {
            max = 10*max + num[3-i];
            min = 10*min + num[i];
        }
        printf( "%04d - %04d = %04d\n",max,min,max-min );
        int result = max-min;
        for( int i=0; i<4; i++ ) {
            num[i] = result%10;
            result /= 10;
        }
    } while( (max-min)!=0 && (max-min)!= 6174 );

    return 0;
}