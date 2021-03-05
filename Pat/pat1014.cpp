#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    const int x=61;
    int day,hour,min;
    int flag = 0;
    char str[4][x];
    string week[7]={ "MON","TUE","WED","THU","FRI","SAT","SUN" };
    
    for( int i=0;i<4;i++ ) cin.getline(str[i],x);

    char *p1=str[0],*p2=str[1],*p3=str[2],*p4=str[3];

    for( ; *p1!='\0';p1++,p2++ ) {
        if( *p1>='A'&&*p1<='G'&&*p1==*p2 ) {  
            day = *p1-'A';
            p1++;
            p2++;
            break;
        }
    }

    for( ; *p1!='\0';p1++,p2++ ) {
        if( *p1>='A'&&*p1<='N'&&*p1==*p2 )  {
            hour = *p1-'A'+10;
            flag = 1;
        }
        else if( *p1>='0'&&*p1<='9'&&*p1==*p2 )  {
            hour = *p1-'0';
            flag = 1;
        }
        if( flag ) break;
    }

    for( min=0; *p3!='\0';p3++,p4++ ) {
        if( ((*p3>='a'&&*p3<='z')||(*p3>='A'&&*p3<='Z'))&&*p3==*p4 ) break;
        else min++;
    }
    cout<<week[day];
    printf(" %02d:%02d", hour, min);
    return 0;
}