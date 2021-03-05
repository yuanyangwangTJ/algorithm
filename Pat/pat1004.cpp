#include <iostream>
using namespace std;
const int x = 20;
void tj_copy( const char *name,char copy[x] )
{
    const char *p1;
    char *p2 = copy;
    p1 = name;
    for( ;*p1!='\0';p1++ )  *(p2++) = *p1;
    *p2 = '\0';
}

int main()
{
    int n,tmax,tmin;
    cin>>n;
    tmax = -1;
    tmin = 101;
    char max_name[x],max_num[x],min_name[x],min_num[x];
    for( int i=0;i<n;i++ ) 
    {
        char name[x],num[x];
        int score;
        cin>>name>>num>>score;
        if(score>tmax) {
            tmax = score;
            tj_copy(name,max_name);
            tj_copy(num,max_num);
        }
        if(score<tmin) {
            tmin = score;
            tj_copy(name,min_name);
            tj_copy(num,min_num);
        }
    }
    cout<<max_name<<" "<<max_num<<endl;
    cout<<min_name<<" "<<min_num<<endl;
    return 0;
}