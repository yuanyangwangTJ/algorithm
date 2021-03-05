#include <iostream>
#include <cmath>
using namespace std;

bool isPrime( int n ) {
    bool flag = true;
    for( int i=2;i<=sqrt(n);i++ ) {
        if( n%i==0 ){
            flag = false;
            break;
        }
    }
    return flag;
}

int main()
{
    int M,N;
    cin>>M>>N;
    int cnt=0,count=0;
    int i;
    for( i=2;cnt<M-1;i++ ) {
        if( isPrime(i) ) cnt++;
    }
    for( ;cnt<N;i++ ) {
        if( isPrime(i) ) {
            cout<<i;
            cnt++;
            count++;
            if( count==10 ) {
                cout<<endl;
                count=0;
            }
            else if( cnt<N ) cout<<" ";    
        }
        
    }

    return 0;
}