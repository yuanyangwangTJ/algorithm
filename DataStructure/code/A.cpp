#include<iostream>
#include<math.h>
#define ll long long
using namespace std;
ll f(ll x)
{
	return x * x + 1;
}
ll gcd(ll a, int b)
{
	if (a < 0)
		a = -a;

	if (a % b == 0)
	{
		return b;
	}
	return gcd(b, a % b);
}
int main()
{
	int n;
	int i = 1;
	for (int k = 0; k < 3; k++)
	{
		switch (k)
		{
			case 0:
				n = 262063;
				break;
			case 1:
				n = 9420457;
				break;
			case 2:
				n = 181937053;
				break;
		}
		cout << "分解整数" << n << endl;
		ll x1 = 1;
		ll x2 = f(x1);
		ll p = gcd(x1 - x2, n);
		while (p == 1)
		{

			//cout << "第" << i << "次" << endl;
			i++;
			x1 = f(x1), x1 %= n;
			//cout << "x1=" << x1 << endl;
			x2 = f(x2), x2 %= n;
			//cout << "x2=" << x2 << endl;
			x2 = f(x2), x2 %= n;
			//cout << "x2=" << x2 << endl;
			p = gcd(x1 - x2, n);
			//cout << "p=" << p << endl;
			if (p == n)
				break;
		}
		if (p == n)
			cout << n << "为素数" << endl;
		else
			cout << "素因子p=" << p << endl;
		cout << "分解" << n << "一共需要迭代" << i << "次" << endl;
		cout << endl;
		i = 1;
	}
	return 0;
}