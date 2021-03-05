#include <iostream>
using namespace std;
int main()
{
    int num[1000],B;
    char Input[1001];
    cin>>Input>>B;
    int i=0,j=0,input,remain;
    if( Input[1]!='\0' ) input = ( Input[0]-'0' )*10 + ( Input[1]-'0' );
    else input = Input[0]-'0';
    num[j++] = input/B;
    remain = input%B;

    if( Input[1]!='\0' ) {
        for( i=2; Input[i]!='\0'; i++ ) {
            input = remain*10 + Input[i] - '0';
            num[j++] = input/B;
            remain = input%B;
        }
    }
   
    num[j] = -1;
    for( int k=0; num[k]!=-1; k++ ) cout<<num[k];
    cout<<" "<<remain;

    return 0;
}