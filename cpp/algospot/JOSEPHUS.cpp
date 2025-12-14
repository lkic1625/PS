#include<iostream>
#include<vector>
using namespace std;

int c, n, k, i;
vector<int> check;

void solve(int idx) {

	if (check.size() == 3) return;
	
	check.erase(check.begin() + idx);
	if (idx + k > check.size()) 
		idx = (idx + k )% check.size();
	else
		idx += k - 1;

	solve(idx);

}

int main() {
	cin >> c;
	while (c-- > 0) {
		cin >> n >> k;
		check.resize(n + 1);
		for (i = 1; i <= n; i++)
			check[i] = i;

		solve(1);
		for (i = 1; i <= 2; i++)
			cout << check[i] << " ";
		cout << endl;
		check.clear();
	}
}