#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    int n,cnt=0;
    string birth;
    string oldest = "2014/09/06",youngest = "1814/09/06";
    string name,old,young;

    cin>>n;
    for( int i=0; i<n; i++ ) {
        cin>>name>>birth;
        if( birth>="1814/09/06" && birth<="2014/09/06" ) {
            cnt++;
            if( oldest >= birth ) {
                oldest = birth;
                old = name;
            }
            if( youngest <= birth ) {
                youngest = birth;
                young = name;
            }
        }
    }

    cout<<cnt;
    if( cnt != 0 ) cout<<" "<<old<<" "<<young<<endl;
    return 0;
}