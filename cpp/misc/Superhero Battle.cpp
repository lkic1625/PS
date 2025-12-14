//https://codeforces.com/contest/1141/problem/E
#include<iostream>
#include<algorithm>
using namespace std;
int n, d[200001];
long long H;
int main() {
	cin >> H >> n;
	int sum = 0;
	int mn = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &d[i]);
		sum += d[i];
		mn = min(mn, sum);
	}
	long long h = H;
	if (sum >= 0 && -mn < H) cout << -1;
	
}