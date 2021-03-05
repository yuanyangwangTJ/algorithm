#include <iostream>
#include <string>

using namespace std;

int main()

{
	int i;
	cin >> i;
    cout << i;
	string str = to_string(i);
	cout << str << endl;
	if (str.find('7') != string::npos) cout << 1;
	else cout << 0;

	return 0;
}