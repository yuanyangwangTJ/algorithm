#include <iostream>
using namespace std;
void read( int n,char num[10][5]);
int main()
{
    char num[10][5] = {"ling","yi","er","san","si","wu","liu","qi","ba","jiu"};
    cout<<"please input a num:"<<endl;
    int count = 0,n;
    int t = getchar();
    while( t !='\n' )
    {
        n = t - '0';
        count += n;
        t = getchar();
    }
    read( count,num );
    return 0;
}
void read( int n,char num[10][5] )
{
    int t;
    int cnt = 1;
    t = n;
    for( cnt=1;t>10; ) 
    {
        t /= 10;
        cnt *= 10;
    }
    int rest;
    for( ;cnt>0;)
    {
        rest = n/cnt;
        n %= cnt;
        cnt /= 10;
        cout<<num[rest];
        if(cnt>0) cout<<" "; 
    }

}