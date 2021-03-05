#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    const int x=100000;
    int head,N,K;
    int Adress,Data[x],Next[x],number[x];
    cin>>head>>N>>K;
    for( int i=0; i<N; i++ ) {
        cin>>Adress;
        cin>>Data[Adress]>>Next[Adress];
    }

    int cnt = 0;
    while( head!=-1 ) {
        number[cnt++] = head;
        head = Next[head];
    }

    for( int i=0; i<(cnt-cnt%K); i+=K ) {
        reverse(begin(number) + i, begin(number) + i + K);
    }

    for( int i=0; i<cnt-1; i++ ) {
        printf( "%05d %d %05d\n",number[i],Data[number[i]],number[i+1] );
    }
    printf( "%05d %d -1",number[cnt-1],Data[number[cnt-1]] );
    return 0;
}