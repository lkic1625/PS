#include<iostream>
#include<algorithm>

using namespace std;

int a, b, c, n;
int cache[4001];

int dp(int n) {
	if (n < 0) return -40000;
	if (n == 0) return 0;	

	int& ret = cache[n];
	if (ret != -1) return ret;
	
	ret = max(ret, 1 + dp(n - a));
	ret = max(ret, 1 + dp(n - b));
	ret = max(ret, 1 + dp(n - c));
	
	return ret = ret == 0 ? -200 : ret;

}

int main() {
	cin >> n >> a >> b >> c;
	memset(cache, -1, sizeof(cache));
	cout << dp(n) << endl;
	
}