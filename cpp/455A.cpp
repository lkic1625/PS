#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;

int n;
long long a[100001];
long long cache[100001];

long long dp(int n) {
	if (n <= 0) return 0;

	long long& ret = cache[n];
	if (ret != -1) return ret;

	ret = max(ret, n * a[n] + dp(n - 2));
	ret = max(ret, dp(n - 1));

	return ret;
}

int main() {
	cin >> n;
	int temp, start = -1;
	memset(cache, -1, sizeof(cache));
	for (int i = 0; i < n; i++) {
		cin >> temp;
		start = max(start, temp);
		a[temp]++;
	}
	cout << dp(start);
}



