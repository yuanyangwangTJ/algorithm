#include <iostream>
#include <iomanip>
using namespace std;
const int x =1000;

int main()
{
    int n;
    int num[x];
    bool flag[5] = {false};
    int sum1=0,sum2=0,fu=1,cnt=0,cnt3=0;
    int max = 0;
    double sum3=0;
    cin>>n;
    for( int i=0;i<n;i++ ) cin>>num[i];
    for( int i=0;i<n;i++ ) {
        switch(num[i]%5) {
            case 0:{
                if( num[i]%2==0 ) {
                    flag[0] = true;
                    sum1 +=num[i];
                }
            } break;
            case 1:{
                flag[1] = true;
                sum2 +=fu*num[i];
                fu = -fu;
            } break;
            case 2:{
                flag[2] = true;
                cnt++;
            } break;
            case 3:{
                flag[3] = true;
                sum3 +=num[i];
                cnt3++;
            } break;
            case 4:{
                flag[4] = true;
                if(num[i]>max) max = num[i];
            } break;
        }
    }
    for( int i=0;i<5;i++ ) {
        if(!flag[i]) cout<<"N";
        else {
            switch(i) {
                case 0:cout<<sum1;break;
                case 1:cout<<sum2;break;
                case 2:cout<<cnt; break;
                case 3:{
                    double avg = sum3/cnt3;
                    cout<<setiosflags(ios::fixed)<<setprecision(1)<<avg;
                } break;
                case 4:cout<<max; break;
            }
        }
        if(i<4) cout<<" ";
    }
    return 0;
}