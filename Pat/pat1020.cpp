#include <iostream>
#include <iomanip>
using namespace std;

const int x = 1000;

int max( double single[],int N )
{
    double max = 0;
    int t = 0;
    for( int i=0; i<N; i++ ) {
        if( single[i]>max ) {
            max = single[i];
            t = i;
        }
    }

    return t;

}
int main()
{
    int N,D;
    double mooncake[2][x] = {0};
    double single[x] = {0};
    double sum = 0;
    double result = 0;
    cin>>N>>D;
    for( int i=0; i<2; i++ )
    for( int j=0; j<N; j++ )
    cin>>mooncake[i][j];

    for( int i=0; i<N; i++ )
    single[i] = mooncake[1][i]/mooncake[0][i];

    for( int i=0; i<N; i++ ) {
        sum += mooncake[0][i];
    }

    if( sum<D ) {
        for( int i=0; i<N; i++ ) {
            result += mooncake[1][i];
        }
    } else {
        while( D>0 ) {
            int t = max( single,N );
            if( mooncake[0][t]>D ) {
                result += single[t]*D;
            } else {
                result += mooncake[1][t];
            }
            D -= mooncake[0][t];
            single[t] = 0;
        }

    }
    cout<<setiosflags(ios::fixed)<<setprecision(2)<<result;
    return 0;
}