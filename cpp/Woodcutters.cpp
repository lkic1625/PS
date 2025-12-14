#include<iostream>
#include<vector>
using namespace std;

int pos, h, n, ans = 2;
vector<pair<int, int>> x;

int main() {

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> pos;
		cin >> h;
		x.push_back(make_pair(pos, h));
	}
	ans = ans > 1 ? ans : 1;
	for (int i = 1; i < n - 1; i++) {
		if (x[i - 1].first < x[i].first - x[i].second) {
			ans++;
		}
		else if (x[i + 1].first > x[i].first + x[i].second) {
			x[i].first += x[i].second;
			ans++;
		}
	}
	cout << ans;
}