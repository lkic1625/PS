#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
#include<set>
#include<algorithm>
using namespace std;

int C, N;
long long K;

int n[503], cache[503];
long long cache2[503];

int LIS(int idx) {
	if (idx == N + 1) return 0;

	int &ret = cache[idx];
	if (ret != -1) return ret;

	for (int i = idx + 1; i <= N + 1; i++) {
		if (n[idx] < n[i])
			ret = max(ret, 1 + LIS(i));
	}
	return ret;
}

long long kth(int idx) {

	long long &ret = cache2[idx];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = idx + 1; i <= N + 1; i++) {
		if (n[idx] < n[i] && cache[idx] == cache[i] + 1)
			ret += min(kth(i), K);
	}

	return ret = ret == 0 ? 1 : ret;
}

void KLIS(int start, long long K, int length) {

	if (length == 0) return;
	int next = 100000000;
	set<pair<int, int>> s;
	for (int i = start + 1; i <= N; i++) {
		if (n[start] < n[i] && cache[i] == length) {
			s.insert({ n[i], i });
		}
	}
	for (auto iter = s.begin(); iter != s.end(); iter++) {
		auto cur = *iter;
		if (cache2[cur.second] >= K) {
			next = cur.second;
			cout << cur.first << " ";
			break;
		}
		else {
			K -= cache2[cur.second];
		}
	}
	return KLIS(next, K, length - 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> C;
	while (C-- > 0) {

		memset(cache, -1, sizeof(cache));
		for (int i = 0; i < 503; i++) {
			cache2[i] = -1;
		}
		cin >> N >> K;

		n[N + 1] = 10000000;
		for (int i = 1; i <= N; i++) {
			cin >> n[i];
		}

		LIS(0);
		kth(0);
		cout << cache[0] - 1 << "\n";
		KLIS(0, K, cache[0] - 1);
		cout << "\n";

	}
}