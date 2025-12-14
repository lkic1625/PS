#include<iostream>
#include<algorithm>
using namespace std;

int a, b, c, d;

int main() {
	cin >> a >> b >> c >> d;
	long long ans = 0;
	int temp = 0;
	temp = min(a, c);
	temp = min(temp, d);
	ans += 256 * temp;
	a -= temp;
	temp = min(a, b);
	ans += 32 * temp;
	cout << ans;

}