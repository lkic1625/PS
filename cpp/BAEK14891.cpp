#include<iostream>
#include<string>
#define CLOCKWISE 1

using namespace std;

int k, n, r, ans;
string gear[6];
pair<int, int> s[6];

void rotate(int n, int r, int propagtion) {
	int right = s[n].first;
	int left = s[n].second;

	s[n].first -= r;
	s[n].first %= 8;
	s[n].second -= r;
	s[n].second %= 8;

	if (propagtion && gear[n][right] != gear[n + 1][s[n + 1].second] ) {
		rotate(n + 1, -r, propagtion);
	}
	
	else if (!propagtion && gear[n][left] != gear[n - 1][s[n - 1].first]) {
		rotate(n - 1, -r, propagtion);
	}
	
}

int main() {
	gear[0] = gear[5] = "########";
	for (int i = 1; i < 5; i++) {
		s[i] = make_pair(2, 6);
		cin >> gear[i];
	}
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> n >> r;
		rotate(n, r, 1);
		rotate(n, r, 0);
	}
	for (int i = 1; i <= 4; i++) {
		if (gear[i][s[i].second + 2 % 8] == '1')
			ans += pow(2, i);
	}
	cout << ans << endl;

}