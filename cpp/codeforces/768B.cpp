#include<iostream>
#include<math.h>
using namespace std;

long long n, l, r;


long long cache[51];

int dp(long long n, long long  pos, long long targ) {
	if (n / 2 == 0) return n;
	if (pos == targ) return 1;
	if (n / 2 == 1) return targ - pos == 1 ? (n % 2) : 1;

	int idx = log2(n / 2);
	if (cache[idx] + pos > targ) return dp(n / 2, pos, targ);
	else if (cache[idx] + pos == targ) return n % 2;
	else return dp(n / 2, pos + cache[idx] + 1, targ);

}
//203 40 124
// 7 2 5

int main() {
	int ans = 0;
	cache[0] = 1;
	for (int i = 1; i <= 50; i++)
		cache[i] = cache[i - 1] * 2 + 1;
	cin >> n >> l >> r;
	
	for (long long i = l - 1; i <= r - 1; i++) {
		ans += dp(n, 0, i) ? 1 : 0;
	}
	cout << ans;

}