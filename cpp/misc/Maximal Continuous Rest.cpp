//https://codeforces.com/contest/1141/problem/B
#include<iostream>
#include<algorithm>

using namespace std;

int n, a[200001], temp = 0;

int main() {
	int ans = 0;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < 2 * n; i++) {
		if (a[i % n]) temp++;
		else temp = 0;
		ans = max(ans, temp);
	}
	cout << ans;
}