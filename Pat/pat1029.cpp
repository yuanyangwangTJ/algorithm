//¾É¼üÅÌ

#include <iostream>
using namespace std;

void change(char *in) 
{
    if(*in >= 'a' && *in <= 'z') {
        *in -= 32;
    }
}

int main()
{
    char input[81], fact[81], bad[81];

    cin>>input;
    cin>>fact;

    char *in = input, *out = fact;
    int i = 0;
    for( ; *in != '\0'; in++) {
        if(*in != *out) {
            change(in);
            int flag = 0;
            for(int j=0; j<i; j++) {
                if(bad[j] == *in) {
                    flag = 1;
                    break;
                }
            }
            if(!flag) bad[i++] = *in;
        } else {
            out++;
        }
    }
    bad[i++] = '\0';

    cout<<bad;
    return 0;
}