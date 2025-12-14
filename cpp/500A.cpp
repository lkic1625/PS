#include<iostream>

using namespace std;

int a[30002], n, t;

void travel(int bef, int cur, int& ret) {
	if (cur == t) ret = true;
	if (cur > n - 1 || ret) return;
	travel(cur, cur + a[cur], ret);
}

int main() {
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	cout.tie(NULL);
	cin >> n >> t;
	for (int i = 0; i < n - 1; i++) {
		cin >> a[i + 1];
	}
	int ans = false;
	travel(0, 1, ans);
	cout << (ans ? "YES" : "NO");

}