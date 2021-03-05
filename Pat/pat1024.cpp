#include <iostream>
using namespace std;
int main()
{
    const int x = 10001;
    char num[x];
    cin.getline( num,x );

    if( num[0]=='-' ) cout<<"-";

    char *str = &num[1];
    
    int flag = 1,index = 0;
    int e=1;
    for( ; *str!='E'; str++ ) e++;

    if( *(++str)=='-' ) flag = 0;
    for( str++; *str!='\0'; str++ ) {
        index = index*10+*str-'0';
    }

    if( flag ) {
        cout<<num[1];
        for( str=&num[3]; *str!='E'; str++ ) {
            if( index==0 ) cout<<".";
            index--;
            cout<<*str;
        }
        if( index>0 ) {
            while( index!=0 ) {
                cout<<"0";
                index--;
            }
        }
    } else {
        cout<<"0.";
        index--;
        while( index!=0 ) {
            cout<<"0";
            index--;
        }
        cout<<num[1];
        for( str=&num[3]; *str!='E'; str++ )  cout<<*str;
    }

    return 0;
}