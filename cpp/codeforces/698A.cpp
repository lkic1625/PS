#include<iostream>
#include<algorithm>
using namespace std;

#define MOD 1000160000316

int n;
int a[100];
int cache[100];
int dp(int days, int before) {
	if (days == n) return 0;

	int& ret = cache[days];
	if (ret != -1) return ret;
	ret = 0;
	
	if (a[days] == 0 || a[days] == before) return ret += 1 + dp(days + 1, 0);
	if (a[days] == 3) {
		if (before == 2) return ret += dp(days + 1, 1);
		else if(before == 1) return ret += dp(days + 1, 2);
		else return ret += min(dp(days + 1, 1), dp(days + 1, 2));
	}
	else return ret += dp(days + 1, a[days]);
	
}

long long mul(long long x, long long y) {
	long long ans = 1;
	while (y > 0) {
		if (y % 2 != 0) {
			ans *= x;
			ans %= MOD;
		}
		x *= x;
		x %= MOD;
		y /= 2;
	}
	return ans;
}


int main() {

	cin >> n;
	cout << (long long)mul(690834982208, 657454308337) << endl;
	cout << (long long)(79921 * 657454308337 % 1000160000316);
	for(int i = 0; i < 100; i++)
		cache[i] = -1;
	for (int i = 0; i < n; i++) {
		
		cin >> a[i];
	}
	cout << dp(0, -1) << endl;
	
}