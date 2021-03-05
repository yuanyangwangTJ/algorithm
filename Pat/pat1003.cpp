#include <iostream>
using namespace std;
bool Judge( char str[100] );
int main()
{
    int n;
    cout<<"please input n:"<<endl;
    cin>>n;
    char str[10][100];
    for( int i=0;i<n;i++ )
    {
        cin.getline(str[i],100);
    }


    
    return 0;
}

bool Judge( char str[100] )
{
    bool flag;
    char *p = str;
    for( ;*p!='\0';p++ )
    {
        if(*p!='P'&&*p!='A'&&*p!='T')  return false;
    }

    for( p=str;*p!='\0';p++ )
    {
        if(*p=='P')
        {
            if( *(p+1)=='A'&&*(p+2)=='T' )
            {
                for( int i=3;*(p+i)!='\0';i++ )
                {
                    if(*(p+i)!='A') return false;
                }
                return true;
            }
            else  return false;
        }
        else return false;
    }

}