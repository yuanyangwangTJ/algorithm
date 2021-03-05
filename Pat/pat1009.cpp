#include <iostream>
using namespace std;
int main()
{
    const int x = 81;
    char str[x],substr[x];
    cin.getline(str,x);
    char *p = str,*subp = substr,*p2;
    for( ; *p!='\0';p++) ;

    while( p!=str ) {
        for( ;*p!=' ' && p!=str;p-- ) ;
        if( *p==' ' ) p2=p+1;
        else  p2 = p;
        for( ;*p2!='\0'&& *p2!=' ';p2++ ) *(subp++) = *p2;
        if( *p==' ' ) { 
            *(subp++) = ' ';
            p--;
        }
        if( *(p+1)==' '&&p==str ) for( p2=p;*p2!='\0'&&*p2!=' ';p2++ ) *(subp++) = *p2;
    }
    
    *subp = '\0';
    cout<<substr;
    return 0;
}