#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>

using namespace std;

const int MAX_N = 100, MAX_K = 100000;

int N, W, V, K, cache[MAX_N][MAX_K];
vector<pair<int, int>> v;

int dp(int i, int w) {
	//i: index of current node
	//w: remaining weight of the knapsack

	//basis cases
	if (w < 0) {//If there is no capacity left, return the minimum value.
		return -1 * MAX_N * MAX_K;
	}
	if (i == N) {//If we've checked all the items, return zero.
		return 0;
	}

	//memoization
	int &ret = cache[i][w];
	if (ret != -1) return ret;

	//get properties
	int weight = v[i].first;
	int value = v[i].second;

	return ret = max(dp(i + 1, w), value + dp(i + 1, w - weight));

}


int main() {
	//fast I/O
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//input
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> W >> V;
		v.push_back({ W, V });
	}

	//init cache
	memset(cache, -1, sizeof(cache));

	//output
	cout << dp(0, K) << '\n';

	return 0;

}