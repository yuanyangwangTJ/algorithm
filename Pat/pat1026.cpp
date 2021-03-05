#include <iostream>
using namespace std;
int main()
{
    int c1,c2;
    int hour,min,s;
    cin>>c1>>c2;
    double ss = (double)(c2-c1)/100;

    hour = ss/3600;
    min = (ss-3600*hour)/60;
    s = ss-3600*hour-60*min;
    if( (ss-3600*hour-60*min-s)>=0.5 ) s++;
    printf( "%02d:%02d:%02d",hour,min,s );
    return 0;
}