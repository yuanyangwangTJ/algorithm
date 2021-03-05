#include <iostream>
using namespace std;
const int x=100000;

int rank1[3][x]={0},rank2[3][x]={0},rank3[3][x]={0},rank4[3][x]={0};

void scanf( int num,int virtue,int talent,int rank[3][x],int j )
{
    for( int k=0; k<3; k++ ) {
        rank[0][j] = num;
        rank[1][j] = virtue;
        rank[2][j] = talent;
    }
}

void swap( int rankn[3][x],int j )
{
    for( int k=0; k<3; k++ ) {
        int t = rankn[k][j];
        rankn[k][j] = rankn[k][j+1];
        rankn[k][j+1] = t;
    }
}

void Rank( int rankn[3][x],int n ) {
    for( int i=0; i<n-1; i++ ) 
    for( int j=0; j<n-1-i; j++ ) {
        if( rankn[1][j]+rankn[2][j] < rankn[1][j+1]+rankn[2][j+1] ) {
            swap( rankn,j );
        } else if( rankn[1][j]+rankn[2][j] == rankn[1][j+1]+rankn[2][j+1] ) {
            if( rankn[1][j] < rankn[1][j+1] ) {
                swap( rankn,j );
            } else if( rankn[1][j] == rankn[1][j+1] ) {
                if( rankn[0][j] > rankn[0][j+1] ) {
                    swap( rankn,j );
                }
            }

        }
    }
    for( int i=0;i<n;i++ )
    for( int j=0;j<3;j++ ) {
         cout<<rankn[j][i];
         if( j==2 ) cout<<endl;
         else cout<<" ";
    }
}

int main()
{
    int N,L,H;
    int num,talent,virtue;
    
    int i1=0,i2=0,i3=0,i4=0;
    cin>>N>>L>>H;

    for( int i=0; i<N; i++ ) {
        cin>>num>>virtue>>talent;
        if( virtue>=L && talent>=L ) {
            if( virtue>=H && talent>=H )
                scanf( num,virtue,talent,rank1,i1++ );
            else if( virtue>=H && talent<H )
                scanf( num,virtue,talent,rank2,i2++ );
            else if( virtue<H && talent<H && virtue>=talent )
                scanf( num,virtue,talent,rank3,i3++ );
            else
                scanf( num,virtue,talent,rank4,i4++ );
        }
    }

    int cnt =i1+i2+i3+i4;
    cout<<cnt<<endl;
    
    Rank( rank1,i1 );
    Rank( rank2,i2 );
    Rank( rank3,i3 );
    Rank( rank4,i4 );

    return 0;
}